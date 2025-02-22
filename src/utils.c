/* Include any necessary libraries and header files */
#include "../header_files/utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// TODO: define necessary utility/helper functions
void copy_file(char *original_filename, char *new_filename)
{
    FILE *original_file = fopen(original_filename, "r"); // open original file for input
    if (original_file == NULL)
    {
        perror("Could not open source file");
        exit(EXIT_FAILURE);
    }

    FILE *new_file = fopen(new_filename, "w"); // open new file for output
    if (new_file == NULL)
    {
        perror("Could not create new file");
        fclose(original_file);
        exit(EXIT_FAILURE);
    }

    char c;
    while((c = fgetc(original_file)) != EOF) // copy file character by character
    {   
       
        if (fputc(c, new_file) == EOF)
        {
            perror("Could not write to new file");
            fclose(original_file);
            fclose(new_file);
            exit(EXIT_FAILURE);
        }
    }

    // close files when done
    fclose(original_file);
    fclose(new_file);
}
void display_help() {
    printf("Usage: ./fileCompressor -c <relative .txt file path>\n");
    printf("       ./fileCompressor -d <relative .txt file path>\n");
    printf("       ./fileCompressor -h\n");
    printf("\n");
    printf("Options:\n");
    printf("  -c <file>   Compress the specified text file and output to a .rle file.\n");
    printf("  -d <file>   Decompress the specified rle file and output to a .txt file.\n");
    
    printf("  -h          Display this help message.\n");

}

char * create_copy_filename(char *original_filename)
{
    // +6 for "_copy" and null terminator ('\0')
    int filename_length = strlen(original_filename) + 6;

    char *new_filename = (char*)malloc(filename_length * sizeof(char));
    if(new_filename == NULL)
    {
        perror("Memory allocation for new file name string failed");
        exit(EXIT_FAILURE); // terminate program
    }

    strcpy(new_filename, original_filename); // copy original file name
    strcat(new_filename, "_copy"); // add _copy 

    return new_filename;
}