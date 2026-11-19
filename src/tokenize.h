#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stddef.h>
#include <stdlib.h>

typedef struct TokenList {
    size_t size;
    size_t capacity;
    char ** tokens;
} TokenList;

// create tokenList
void initTokenList(TokenList* list);

// process input into the list of tokens
int tokenize(TokenList* list, const char* line);

// destroy tokenList
void destroyTokenList(TokenList* list);

#endif