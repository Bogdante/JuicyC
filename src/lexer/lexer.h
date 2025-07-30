//
// Created by bogdante on 30.07.25.
//

#ifndef LEXER_H
#define LEXER_H

#include "stdint.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../common/tokens.h"

typedef struct {
    char type;
    void *value;
}Token;

typedef struct {
    Token *tokens;
    int32_t count;
    int32_t capacity;
}TokenList;

typedef struct {
    int32_t raw_text_length;
    int32_t position;
    const char *raw_text;
    char ch;
}Lexer;

TokenList* lex(const char *input);

#endif //LEXER_H
