#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    printf("mysh> ");
    fflush(stdout);

    while ((nread = getline(&line, &size, stdin)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);

        printf("mysh> ");
        fflush(stdout);
    }

    printf("\n");
    fflush(stdout);
    free(line);
    exit(EXIT_SUCCESS);
}