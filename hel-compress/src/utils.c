#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_usage() {
    printf("الاستخدام:\n");
    printf("  hel-compress ضغط <input> <output> [خيارات]\n");
    printf("  hel-compress فك <input> <output> [خيارات]\n");
    printf("خيارات:\n");
    printf("  --algo=gzip     استخدام gzip\n");
    printf("  --algo=bzip2    استخدام bzip2\n");
    printf("  --algo=zstd     استخدام zstd\n");
    printf("  --encrypt       تشفير AES-256 بعد الضغط\n");
    printf("  --decrypt       فك التشفير قبل فك الضغط\n");
    printf("  --extract       استخراج أرشيف كامل\n");
    printf("  --list          عرض محتويات الأرشيف\n");
}

void print_error(const char *msg) {
    fprintf(stderr, "خطأ: %s\n", msg);
}

void print_compression_ratio(size_t original_size, size_t compressed_size) {
    if (original_size == 0) {
        printf("لا يمكن حساب نسبة الضغط.\n");
        return;
    }
    double ratio = (1.0 - ((double)compressed_size / (double)original_size)) * 100.0;
    printf("نسبة الضغط: %.2f%%\n", ratio);
}

void print_time_elapsed(clock_t start, clock_t end) {
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("الوقت المستغرق: %.3f ثانية\n", elapsed);
}
