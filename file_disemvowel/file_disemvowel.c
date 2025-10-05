#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

void addChar(char *str, char c, int *length) {
    str[(*length)++] = c; // Add character at the end
    str[*length] = '\0'; // Replace null pointer
}

bool is_vowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
       c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') { 
      return true; // True if vowel
    }
    return false; // False if not
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int length = 0; // Track length of out_buf
    out_buf[0] = '\0'; // Initialize as empty string

    for(int i = 0; i < num_chars; i++) { // Loop through in_buf
        if (!is_vowel(in_buf[i])) { // Check if character is NOT a vowel
            // If char is NOT a vowel, then:
            addChar(out_buf, in_buf[i], &length); // Add char to out_buf (length incremented inside)
        }
    }
    return length; // Return the length (number of copied chars)
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    // Input and output buffers
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];

    int num_written;

    while (fgets(in_buf, BUF_SIZE, inputFile) != NULL) {
        num_written = copy_non_vowels(strlen(in_buf), in_buf, out_buf); // Copy non-vowels to out_buf
        fwrite(out_buf, sizeof(char), num_written, outputFile); // Write out_buf to outputFile
    }
}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile;
    FILE *outputFile;

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.
    switch (argc){
    case 1: // No parameters, use stdin & stdout
        //puts("Case 1");
        inputFile = stdin;
        outputFile = stdout;
        break;

    case 2: // One parameter, use input file & stdout
        //puts("Case 2");
        if((inputFile = fopen(argv[1], "r")) == NULL){
            //puts("Can't open input file, exiting");
            exit(0);
        }
        outputFile = stdout;
        break;

    case 3: // Two parameters, use input & output files
        //puts("Case 3");
        if((inputFile = fopen(argv[1], "r")) == NULL){
            //puts("Can't open input file, exiting");
            exit(0);
        }
        if((outputFile = fopen(argv[2], "w")) == NULL){
            //puts("Can't open output file, exiting");
            exit(0);
        }
        break;

    default: // More than two parameters, error
        //puts("Too many parameters, exiting");
        exit(0);
    }

    disemvowel(inputFile, outputFile);

    // Close any files (not stdin/stdout) that got opened
    if (inputFile != stdin) {
        fclose(inputFile);
    }
    if (outputFile != stdout) {
        fclose(outputFile);
    }

    return 0;
}