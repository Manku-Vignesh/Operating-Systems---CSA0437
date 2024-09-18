#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
// Open a source file for reading
int source_fd = open("source.txt", O_RDONLY);
if (source_fd == -1) {
perror("Failed to open source.txt");
exit(1);

}

// Create or open a destination file for writing

int dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

if (dest_fd == -1) {

perror("Failed to open destination.txt");

close(source_fd); // Close the source file

exit(1);

}

// Read from the source file and write to the destination file

char buffer[4096]; // A buffer to hold data

ssize_t nread;

while ((nread = read(source_fd, buffer, sizeof(buffer))) > 0) {

if (write(dest_fd, buffer, nread) != nread) {

perror("Write error");

break;

}

}

// Check if there was an error during reading

if (nread < 0) {

perror("Read error");

}

// Close both files

close(source_fd);

close(dest_fd);

return 0;

}



