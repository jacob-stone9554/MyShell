#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

// ------------ Helpers ------------
static int growTokenList(TokenList* list) {
    if (list->capacity == 0) {
        char ** temp = realloc(list->tokens, sizeof(char*) * (list->capacity + 8));

        if (temp == NULL) {
            return -1;
        }

        list->capacity = 8;
        list->tokens = temp;

        return 0;
    }

    char ** tempList = realloc(list->tokens, sizeof(char*) * (list->capacity * 2));

    if (tempList == NULL) {
        return -1;
    }

    list->tokens = tempList;
    list->capacity = list->capacity * 2;

    return 0;
}

static int addToken(TokenList* list, char* token) {

    if (list->size + 1 >= list->capacity) {
        int result = growTokenList(list);

        if (result != 0) {
            free(token);
            return -1;
        }
    }

    list->tokens[list->size] = token;
    list->size++;

    list->tokens[list->size] = NULL;

    return 0;
}

void initTokenList(TokenList* list) {
    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
}

// ------------ Implementations ------------
int tokenize(TokenList* list, const char* line) {
    size_t pos = 0;
    char* currTok = NULL;

    while (line[pos] != '\0') {
        *currTok = line[pos];

        if (*currTok == ' ') {
            pos++;
            continue;
        }
        else {
            addToken(list, currTok);
        }

        pos++;
    }

    return 0;
}

void destroyTokenList(TokenList* list) {

    for (size_t i = 0; i < list->size; i++) {
        free(list->tokens[i]);
    }

    free(list->tokens);
    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
}



