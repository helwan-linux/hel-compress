#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <time.h>

void print_usage();
void print_error(const char *msg);
void print_compression_ratio(size_t original_size, size_t compressed_size);
void print_time_elapsed(clock_t start, clock_t end);

#endif // UTILS_H
