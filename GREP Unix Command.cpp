#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void grepSimulation(FILE *file, const char *pattern) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            // Pattern found in the line, print the line
            printf("%s", line);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <pattern> [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pattern = argv[1];
    FILE *file;

    if (argc == 2) {
        // No file specified, read from standard input
        grepSimulation(stdin, pattern);
    } else {
        // Read from the specified file
        file = fopen(argv[2], "r");

        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        grepSimulation(file, pattern);

        // Close the file
        fclose(file);
    }

    return 0;
}

