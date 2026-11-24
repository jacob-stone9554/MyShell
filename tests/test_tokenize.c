#include <string.h>
#include "tokenize.h"
#include "acutest.h"

void test_basic_split(void) {
    TokenList list;
    initTokenList(&list);

    TEST_CHECK(tokenize(&list, "ls -la /tmp\n") == 0);
    TEST_CHECK(list.size == 3);
    TEST_CHECK(strcmp(list.tokens[0], "ls") == 0);
    TEST_CHECK(list.tokens[3] == NULL);

    destroyTokenList(&list);
}

TEST_LIST = {
    { "basic split", test_basic_split },
        { NULL, NULL }
};
