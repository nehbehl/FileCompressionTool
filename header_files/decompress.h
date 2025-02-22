#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <stdio.h>
void decompress(const char *input_filename);
void decompress_line(const char *line, FILE *output_file);

#endif