#include "compressor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <zstd.h>
#include <bzlib.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define CHUNK 65536

typedef struct {
    long offset;
    unsigned int name_len;
    unsigned long original_size;
    unsigned long compressed_size;
    int algo_type;
} CentralDirectoryEntry;

int encrypt_buffer(unsigned char *in, int in_len, unsigned char *out, const unsigned char *key, const unsigned char *iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, out_len;
    if (!ctx) return -1;
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1 ||
        EVP_EncryptUpdate(ctx, out, &len, in, in_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    out_len = len;
    if (EVP_EncryptFinal_ex(ctx, out + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    out_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return out_len;
}

int decrypt_buffer(unsigned char *in, int in_len, unsigned char *out, const unsigned char *key, const unsigned char *iv) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len, out_len;
    if (!ctx) return -1;
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1 ||
        EVP_DecryptUpdate(ctx, out, &len, in, in_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    out_len = len;
    if (EVP_DecryptFinal_ex(ctx, out + len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    out_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return out_len;
}

int compress_file(const char *input_path, const char *output_path, CompressionAlgo algo, int encrypt) {
    FILE *source = fopen(input_path, "rb");
    FILE *dest = fopen(output_path, "wb");
    if (!source || !dest) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        return -1;
    }

    fseek(source, 0, SEEK_END);
    long f_size = ftell(source);
    fseek(source, 0, SEEK_SET);

    unsigned char *in_buf = malloc(f_size);
    fread(in_buf, 1, f_size, source);
    fclose(source);

    unsigned char *comp_buf = NULL;
    long comp_size = 0;

    unsigned char key[32];
    unsigned char iv[16];
    if (encrypt) {
        memset(key, 'A', 32);
        RAND_bytes(iv, sizeof(iv));
        fwrite(iv, 1, sizeof(iv), dest);
    }

    if (algo == ALGO_ZSTD) {
        size_t max_zstd = ZSTD_compressBound(f_size);
        comp_buf = malloc(max_zstd);
        comp_size = ZSTD_compress(comp_buf, max_zstd, in_buf, f_size, 3);
        if (ZSTD_isError(comp_size)) {
            free(in_buf);
            free(comp_buf);
            fclose(dest);
            return -1;
        }
    } else if (algo == ALGO_BZIP2) {
        unsigned int dest_len = f_size + 600;
        comp_buf = malloc(dest_len);
        BZ2_bzBuffToBuffCompress((char*)comp_buf, &dest_len, (char*)in_buf, f_size, 9, 0, 0);
        comp_size = dest_len;
    } else {
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        deflateInit(&strm, Z_DEFAULT_COMPRESSION);
        comp_buf = malloc(f_size + 1024);
        strm.avail_in = f_size;
        strm.next_in = in_buf;
        strm.avail_out = f_size + 1024;
        strm.next_out = comp_buf;
        deflate(&strm, Z_FINISH);
        comp_size = (f_size + 1024) - strm.avail_out;
        deflateEnd(&strm);
    }

    if (encrypt) {
        unsigned char *enc_buf = malloc(comp_size + EVP_MAX_BLOCK_LENGTH);
        int enc_len = encrypt_buffer(comp_buf, comp_size, enc_buf, key, iv);
        fwrite(enc_buf, 1, enc_len, dest);
        free(enc_buf);
    } else {
        fwrite(comp_buf, 1, comp_size, dest);
    }

    free(in_buf);
    free(comp_buf);
    fclose(dest);
    return 0;
}

int decompress_file(const char *input_path, const char *output_path, CompressionAlgo algo, int decrypt) {
    FILE *source = fopen(input_path, "rb");
    FILE *dest = fopen(output_path, "wb");
    if (!source || !dest) {
        if (source) fclose(source);
        if (dest) fclose(dest);
        return -1;
    }

    unsigned char key[32];
    unsigned char iv[16];
    memset(key, 'A', 32);
    if (decrypt) {
        fread(iv, 1, sizeof(iv), source);
    }

    fseek(source, 0, SEEK_END);
    long source_len = ftell(source);
    long data_len = decrypt ? source_len - 16 : source_len;
    fseek(source, decrypt ? 16 : 0, SEEK_SET);

    unsigned char *read_buf = malloc(data_len);
    fread(read_buf, 1, data_len, source);
    fclose(source);

    unsigned char *processed_buf = read_buf;
    long processed_len = data_len;

    if (decrypt) {
        unsigned char *dec_buf = malloc(data_len + EVP_MAX_BLOCK_LENGTH);
        int dec_len = decrypt_buffer(read_buf, data_len, dec_buf, key, iv);
        free(read_buf);
        processed_buf = dec_buf;
        processed_len = dec_len;
    }

    unsigned long decompressed_max = 50 * 1024 * 1024;
    unsigned char *decomp_buf = malloc(decompressed_max);

    if (algo == ALGO_ZSTD) {
        long real_size = ZSTD_decompress(decomp_buf, decompressed_max, processed_buf, processed_len);
        fwrite(decomp_buf, 1, real_size, dest);
    } else if (algo == ALGO_BZIP2) {
        unsigned int real_size = decompressed_max;
        BZ2_bzBuffToBuffDecompress((char*)decomp_buf, &real_size, (char*)processed_buf, processed_len, 0, 0);
        fwrite(decomp_buf, 1, real_size, dest);
    } else {
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = processed_len;
        strm.next_in = processed_buf;
        inflateInit(&strm);
        do {
            strm.avail_out = decompressed_max;
            strm.next_out = decomp_buf;
            inflate(&strm, Z_NO_FLUSH);
            long have = decompressed_max - strm.avail_out;
            fwrite(decomp_buf, 1, have, dest);
        } while (strm.avail_out == 0);
        inflateEnd(&strm);
    }

    free(processed_buf);
    free(decomp_buf);
    fclose(dest);
    return 0;
}

static void recursive_collect(const char *base_path, const char *current_path, FILE *archive, CentralDirectoryEntry **index, int *count, CompressionAlgo algo) {
    char full_path[1024];
    struct dirent *entry;
    DIR *dir = opendir(current_path);
    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", current_path, entry->d_name);
        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                recursive_collect(base_path, full_path, archive, index, count, algo);
            } else if (S_ISREG(st.st_mode)) {
                FILE *f_in = fopen(full_path, "rb");
                if (!f_in) continue;

                fseek(f_in, 0, SEEK_END);
                long f_size = ftell(f_in);
                fseek(f_in, 0, SEEK_SET);

                unsigned char *buf = malloc(f_size);
                fread(buf, 1, f_size, f_in);
                fclose(f_in);

                unsigned char *comp_buf = malloc(f_size + 1024);
                long comp_size = 0;

                if (algo == ALGO_ZSTD) {
                    comp_size = ZSTD_compress(comp_buf, f_size + 1024, buf, f_size, 3);
                } else if (algo == ALGO_BZIP2) {
                    unsigned int d_len = f_size + 600;
                    BZ2_bzBuffToBuffCompress((char*)comp_buf, &d_len, (char*)buf, f_size, 9, 0, 0);
                    comp_size = d_len;
                } else {
                    z_stream strm;
                    strm.zalloc = Z_NULL;
                    strm.zfree = Z_NULL;
                    strm.opaque = Z_NULL;
                    deflateInit(&strm, Z_DEFAULT_COMPRESSION);
                    strm.avail_in = f_size;
                    strm.next_in = buf;
                    strm.avail_out = f_size + 1024;
                    strm.next_out = comp_buf;
                    deflate(&strm, Z_FINISH);
                    comp_size = (f_size + 1024) - strm.avail_out;
                    deflateEnd(&strm);
                }

                const char *rel_path = full_path + strlen(base_path) + 1;
                long current_offset = ftell(archive);

                unsigned int name_len = strlen(rel_path);
                fwrite(rel_path, 1, name_len, archive);
                fwrite(comp_buf, 1, comp_size, archive);

                *index = realloc(*index, (*count + 1) * sizeof(CentralDirectoryEntry));
                (*index)[*count].offset = current_offset;
                (*index)[*count].name_len = name_len;
                (*index)[*count].original_size = f_size;
                (*index)[*count].compressed_size = comp_size;
                (*index)[*count].algo_type = (algo == ALGO_ZSTD) ? 1 : (algo == ALGO_BZIP2 ? 2 : 0);
                (*count)++;

                free(buf);
                free(comp_buf);
            }
        }
    }
    closedir(dir);
}

int compress_directory(const char *dir_path, const char *archive_path, CompressionAlgo algo, int encrypt) {
    FILE *archive = fopen(archive_path, "wb");
    if (!archive) return -1;

    CentralDirectoryEntry *index = NULL;
    int index_count = 0;

    recursive_collect(dir_path, dir_path, archive, &index, &index_count, algo);

    long index_start = ftell(archive);
    fwrite(&index_count, sizeof(int), 1, archive);
    for (int i = 0; i < index_count; i++) {
        fwrite(&index[i], sizeof(CentralDirectoryEntry), 1, archive);
    }
    fwrite(&index_start, sizeof(long), 1, archive);

    fclose(archive);
    free(index);
    return 0;
}

int extract_archive(const char *archive_path, const char *output_dir, CompressionAlgo algo, int decrypt) {
    FILE *archive = fopen(archive_path, "rb");
    if (!archive) return -1;

    fseek(archive, -sizeof(long), SEEK_END);
    long index_start;
    fread(&index_start, sizeof(long), 1, archive);

    fseek(archive, index_start, SEEK_SET);
    int index_count;
    fread(&index_count, sizeof(int), 1, archive);

    CentralDirectoryEntry *index = malloc(index_count * sizeof(CentralDirectoryEntry));
    fread(index, sizeof(CentralDirectoryEntry), index_count, archive);

    for (int i = 0; i < index_count; i++) {
        fseek(archive, index[i].offset, SEEK_SET);

        char *filename = malloc(index[i].name_len + 1);
        fread(filename, 1, index[i].name_len, archive);
        filename[index[i].name_len] = '\0';

        unsigned char *comp_buf = malloc(index[i].compressed_size);
        fread(comp_buf, 1, index[i].compressed_size, archive);

        char out_filepath[2048];
        snprintf(out_filepath, sizeof(out_filepath), "%s/%s", output_dir, filename);

        char tmp_path[2048];
        snprintf(tmp_path, sizeof(tmp_path), "%s", out_filepath);
        for (char *p = tmp_path + 1; *p; p++) {
            if (*p == '/') {
                *p = '\0';
                mkdir(tmp_path, 0777);
                *p = '/';
            }
        }

        unsigned char *decomp_buf = malloc(index[i].original_size);
        if (index[i].algo_type == 1) {
            ZSTD_decompress(decomp_buf, index[i].original_size, comp_buf, index[i].compressed_size);
        } else if (index[i].algo_type == 2) {
            unsigned int d_len = index[i].original_size;
            BZ2_bzBuffToBuffDecompress((char*)decomp_buf, &d_len, (char*)comp_buf, index[i].compressed_size, 0, 0);
        } else {
            z_stream strm;
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;
            strm.avail_in = index[i].compressed_size;
            strm.next_in = comp_buf;
            strm.avail_out = index[i].original_size;
            strm.next_out = decomp_buf;
            inflateInit(&strm);
            inflate(&strm, Z_FINISH);
            inflateEnd(&strm);
        }

        FILE *f_out = fopen(out_filepath, "wb");
        if (f_out) {
            fwrite(decomp_buf, 1, index[i].original_size, f_out);
            fclose(f_out);
        }

        free(filename);
        free(comp_buf);
        free(decomp_buf);
    }

    free(index);
    fclose(archive);
    return 0;
}
