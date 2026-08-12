#include "lang_manager.h"
#include <string.h>

int is_compress_command(const char *cmd) {
    return (!strcmp(cmd, "compress") ||
            !strcmp(cmd, "ضغط") ||
            !strcmp(cmd, "comprimir") ||
            !strcmp(cmd, "压缩") ||
            !strcmp(cmd, "compresser") ||
            !strcmp(cmd, "komprimieren"));
}

int is_decompress_command(const char *cmd) {
    return (!strcmp(cmd, "decompress") ||
            !strcmp(cmd, "فك") ||
            !strcmp(cmd, "descomprimir") ||
            !strcmp(cmd, "解压") ||
            !strcmp(cmd, "decompresser") ||
            !strcmp(cmd, "entpacken"));
}

CompressionAlgo detect_algo(const char *cmd) {
    if (!strcmp(cmd, "--algo=gzip")) return ALGO_GZIP;
    if (!strcmp(cmd, "--algo=bzip2")) return ALGO_BZIP2;
    if (!strcmp(cmd, "--algo=zstd")) return ALGO_ZSTD;
    return ALGO_ZLIB;
}
