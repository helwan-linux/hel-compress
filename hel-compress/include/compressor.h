#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stddef.h>
#include <stdio.h>

typedef enum {
    ALGO_ZLIB,
    ALGO_GZIP,
    ALGO_BZIP2,
    ALGO_ZSTD,
    ALGO_TAR,
    ALGO_XZ,
    ALGO_7Z
} CompressionAlgo;

// دوال ضغط وفك ضغط الملفات الفردية
int compress_file(const char *input_path, const char *output_path, CompressionAlgo algo, int encrypt);
int decompress_file(const char *input_path, const char *output_path, CompressionAlgo algo, int decrypt);

// دوال ضغط واستخراج المجلدات بالمرور التراجعي (Recursive) وأرشفتها
int compress_directory(const char *dir_path, const char *archive_path, CompressionAlgo algo, int encrypt);
int extract_archive(const char *archive_path, const char *output_dir, CompressionAlgo algo, int decrypt);

// دوال مساعدة للتدفق الداخلي
int compress_single_file_stream(FILE *source, FILE *dest, CompressionAlgo algo);

#endif // COMPRESSOR_H
