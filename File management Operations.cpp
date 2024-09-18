#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char fileName[] = "example.txt";

    // Open file for writing (creates a new file or truncates an existing file)
    file = fopen(fileName, "w");

    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    fprintf(file, "Hello, File Management!\n");

    // Close the file
    fclose(file);

    // Open file for reading
    file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // Read and print data from the file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    // Close the file
    fclose(file);

    return 0;
}

