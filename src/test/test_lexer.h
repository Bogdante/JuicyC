//
// Created by bogdante on 31.07.25.
//

#ifndef TEST_LEXER_H
#define TEST_LEXER_H

#include "../lexer/lexer.h"

const char *token_type_to_string(TokenTypes type);
void print_token_stream(const TokenList *token_stream);

#endif //TEST_LEXER_H
