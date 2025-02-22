#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header_files/utils.h"
#include "../header_files/compress.h"
#include "../header_files/decompress.h"

#include "../header_files/constants.h"


void compress_file(const char *input_filename, const char *output_filename);
void decompress_file(const char *input_filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        display_help();
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        const char *input_filename = argv[2];
        char output_filename[256];
        compress_file(input_filename);
    } else if (strcmp(argv[1], "-d") == 0) {
        const char *input_filename = argv[2];
        decompress(input_filename);
    } else {
        fprintf(stderr, "Invalid option. Use -c for compression or -d for decompression.\n");
        return 1;
    }

    return 0;
}
