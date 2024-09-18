#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void lsSimulation(const char *directoryPath) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(directoryPath);

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *directoryPath;

    if (argc < 2) {
        // No directory specified, list the current directory
        directoryPath = ".";
    } else {
        directoryPath = argv[1];
    }

    lsSimulation(directoryPath);

    return 0;
}

