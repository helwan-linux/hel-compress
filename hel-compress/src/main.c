#include "compressor.h"
#include "lang_manager.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        return 1;
    }

    const char *command = argv[1];
    const char *input = argv[2];
    const char *output = (argc > 3) ? argv[3] : "output.dat";

    CompressionAlgo algo = ALGO_ZLIB;
    int encrypt = 0, decrypt = 0;

    for (int i = 4; i < argc; i++) {
        if (!strcmp(argv[i], "--algo=gzip")) algo = ALGO_GZIP;
        else if (!strcmp(argv[i], "--algo=bzip2")) algo = ALGO_BZIP2;
        else if (!strcmp(argv[i], "--algo=zstd")) algo = ALGO_ZSTD;
        else if (!strcmp(argv[i], "--encrypt")) encrypt = 1;
        else if (!strcmp(argv[i], "--decrypt")) decrypt = 1;
    }

    clock_t start = clock();

    if (is_compress_command(command)) {
        if (compress_file(input, output, algo, encrypt) == 0)
            printf("تم ضغط الملف بنجاح: %s\n", output);
        else
            print_error("فشل في ضغط الملف");
    } else if (is_decompress_command(command)) {
        if (decompress_file(input, output, algo, decrypt) == 0)
            printf("تم فك ضغط الملف بنجاح: %s\n", output);
        else
            print_error("فشل في فك ضغط الملف");
    } else if (!strcmp(command, "--extract")) {
        if (extract_archive(input, output, algo, decrypt) == 0)
            printf("تم استخراج الأرشيف بنجاح إلى: %s\n", output);
        else
            print_error("فشل في استخراج الأرشيف");
    } else if (!strcmp(command, "--compress-dir")) {
        if (compress_directory(input, output, algo, encrypt) == 0)
            printf("تم ضغط المجلد بنجاح: %s\n", output);
        else
            print_error("فشل في ضغط المجلد");
    } else {
        print_error("أمر غير معروف");
        print_usage();
    }

    clock_t end = clock();
    print_time_elapsed(start, end);

    return 0;
}
