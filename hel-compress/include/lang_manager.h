#ifndef LANG_MANAGER_H
#define LANG_MANAGER_H

#include "compressor.h"

int is_compress_command(const char *cmd);
int is_decompress_command(const char *cmd);
CompressionAlgo detect_algo(const char *cmd);

#endif // LANG_MANAGER_H
