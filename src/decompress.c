/* Include any necessary libraries and header files */
#include "../header_files/decompress.h"

#include "../header_files/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void decompress_line(const char *line, FILE *output_file) {
     for (int i = 0; line[i] != '\0'; i++) {

        //Check for space
        if(line[i]==' ') {
            fputc(line[i], output_file);
            continue;
        }

        char current_char = line[i]; // Get the character
        i++; // Move to the next character which should be a digit

        int count = 0;
        int j=i;
        // Read the number that follows the character
        while (line[j] >= '0' && line[j] <= '9') {
            count = count * 10 + (line[j] - '0'); // Convert char to int
            j++;
        }
        // Write the character 'count' times to the output file
        for (int j = 0; j < count; j++) {
            fputc(current_char, output_file);
        }

        
    }
    fputc('\n', output_file); // Add a newline after each decompressed line
}


void decompress(const char *input_filename) {
 // TODO: write decompression solution    
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    // Create output filename by replacing .rle with .txt
    char base_output_filename[MAX_LINE_LENGTH];
    strncpy(base_output_filename, input_filename, strlen(input_filename) - 4); // Copy input filename without extension
    base_output_filename[strlen(input_filename) - 4] = '\0'; // Remove .rle
    strcat(base_output_filename, ".txt"); // Append .txt

    // Check if the output file already exists and modify the name if necessary
    char output_filename[MAX_LINE_LENGTH];
    strcpy(output_filename, base_output_filename); // Start with the base name
    int file_index = 1;

    FILE *output_file;
    while ((output_file = fopen(output_filename, "r")) != NULL) {
        fclose(output_file); // Close the file if it exists
        // Create a new filename with an incremented suffix
        snprintf(output_filename, sizeof(output_filename), "%s_%d.txt", base_output_filename, file_index);
        file_index++;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    char line[256]; // Buffer to hold each line
    printf("Initiated decompressing");
    printf(input_filename);
    printf("\n");

    while (fgets(line, sizeof(line), input_file)) {
        decompress_line(line, output_file); // Decompress the current line and write to output file
    }

    fclose(input_file);  // Close the input file
    fclose(output_file); // Close the output file
}
