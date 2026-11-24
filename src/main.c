#include <stdio.h>
#include <stdlib.h>
#include "tokenize.h"

int main(void) {
    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    printf("mysh> ");
    fflush(stdout);

    while ((nread = getline(&line, &size, stdin)) != -1) {
        // init token list
        TokenList list;

        initTokenList(&list);

        // tokenize the input
        int result = tokenize(&list, line);

        if(result != 0) {
            exit(EXIT_FAILURE);
        }

        // parse/execute the command (print it for now)

        for(size_t i = 0; i < list.size; i++) {
            printf("[%s]\n", list.tokens[i]);
        }

        //printf("Retrieved line of length %zd:\n", nread);
        //fwrite(line, nread, 1, stdout);

        destroyTokenList(&list);

        printf("mysh> ");
        fflush(stdout);
    }

    printf("\n");
    fflush(stdout);
    free(line);
    exit(EXIT_SUCCESS);
}
