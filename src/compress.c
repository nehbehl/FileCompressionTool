/* Include any necessary libraries and header files */
#include "../header_files/compress.h"
#include "../header_files/utils.h"
#include "../header_files/constants.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void compress_line(const char *line, FILE *output_file) {
    int count = 1; // Initialize count for the first character
    char current_char = line[0]; // Start with the first character

    for (int i = 1; line[i] != '\0'; i++) {

        if (line[i] == current_char) {
            count++; // Increment count if the same character is found
        } else if(line[i]=='\n'){
            continue;
        }
        else {
            // Write the current character and its count to the output file
            if(current_char==' '){
                fprintf(output_file, "%c", current_char);
            } else {
                fprintf(output_file, "%c%d", current_char, count);
            }            
                        
            current_char = line[i]; // Update current character
            count = 1; // Reset count for the new character
        }
    }
    // Write the last character and its count
    fprintf(output_file, "%c%d\n", current_char,count);    
}

void compress_file(const char *input_filename) {
    // TODO: write compression solution
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    // Create output filename by replacing .txt with .rle
    char base_output_filename[MAX_LINE_LENGTH];
    strncpy(base_output_filename, input_filename, strlen(input_filename) - 4); // Copy input filename without extension
    base_output_filename[strlen(input_filename) - 4] = '\0'; // Remove .txt
    strcat(base_output_filename, ".rle"); // Append .rle

    // Check if the output file already exists and modify the name if necessary
    char output_filename[MAX_LINE_LENGTH];
    strcpy(output_filename, base_output_filename); // Start with the base name
    int file_index = 1;

    FILE *output_file;
    while ((output_file = fopen(output_filename, "r")) != NULL) {
        fclose(output_file); // Close the file if it exists
        // Create a new filename with an incremented suffix
        snprintf(output_filename, sizeof(output_filename), "%s_%d.rle", base_output_filename, file_index);
        file_index++;
    }   

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }
    
    char line[MAX_LINE_LENGTH]; // Buffer to hold each line
    printf("Initiated compressing");
    printf(input_filename);
    printf("\n");
    while (fgets(line, sizeof(line), input_file)) {
        compress_line(line, output_file); // Compress the current line and write to output file
    }

    fclose(input_file);  // Close the input file
    fclose(output_file); // Close the output file
}
