#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main() {
    int sourceFile, destinationFile;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUF_SIZE];

    // Open the source file for reading
    sourceFile = open("source.txt", O_RDONLY);
    if (sourceFile == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing (create if not exists, truncate to 0 if exists)
    if (destinationFile == -1) {
        perror("Error opening destination file");
        close(sourceFile);
        exit(EXIT_FAILURE);
    }

    // Read from the source file and write to the destination file
    while ((bytesRead = read(sourceFile, buffer, BUF_SIZE)) > 0) {
        bytesWritten = write(destinationFile, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFile);
            close(destinationFile);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
        close(sourceFile);
        close(destinationFile);
        exit(EXIT_FAILURE);
    }

    // Close the files
    close(sourceFile);
    close(destinationFile);

    printf("File copy successful!\n");

    return 0;
}

