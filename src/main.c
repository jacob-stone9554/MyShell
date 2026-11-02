#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    while ((nread = getline(&line, &size, stdin)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
    }

    free(line);
    exit(EXIT_SUCCESS);
}