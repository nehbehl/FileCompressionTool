#ifndef COMPRESS_H
#define COMPRESS_H
#include <stdio.h> 
void compress_file(const char *input_filename);
void compress_line(const char *line, FILE *output_file);
#endif