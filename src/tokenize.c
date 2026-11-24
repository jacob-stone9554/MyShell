#include "tokenize.h"
#include <ctype.h>
#include <inttypes.h>
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

    while (line[pos] != '\0') {
        while (isspace((unsigned char)line[pos])) {
           pos++;
        }

        if(line[pos] == '\0') {
            break;
        }

        size_t start = pos;

        while (!isspace((unsigned char)line[pos]) && line[pos] != '\0') {
          pos++;
        }

        char* tok = strndup(line + start, pos - start);

        if(tok == NULL) {
            return -1;
        }

        int result = addToken(list, tok);

        if(result != 0){
            return -1;
        }
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
