//
// Created by bogdante on 31.07.25.
//

#include "test_lexer.h"


const char *token_type_to_string(TokenTypes type) {
    switch (type) {
        case TK_LITERAL_INT: return "TK_LITERAL_INT";
        case TK_LITERAL_FLOAT: return "TK_LITERAL_FLOAT";
        case TK_LITERAL_CHAR: return "TK_LITERAL_CHAR";
        case TK_LITERAL_BOOL: return "TK_LITERAL_BOOL";
        case TK_LITERAL_STRING: return "TK_LITERAL_STRING";

        case TK_KEYWORD_U16: return "TK_KEYWORD_U16";
        case TK_KEYWORD_U32: return "TK_KEYWORD_U32";
        case TK_KEYWORD_U64: return "TK_KEYWORD_U64";
        case TK_KEYWORD_I16: return "TK_KEYWORD_I16";
        case TK_KEYWORD_I32: return "TK_KEYWORD_I32";
        case TK_KEYWORD_I64: return "TK_KEYWORD_I64";
        case TK_KEYWORD_F32: return "TK_KEYWORD_F32";
        case TK_KEYWORD_F64: return "TK_KEYWORD_F64";
        case TK_KEYWORD_U0: return "TK_KEYWORD_U0";
        case TK_KEYWORD_BYTE: return "TK_KEYWORD_BYTE";
        case TK_KEYWORD_BOOL: return "TK_KEYWORD_BOOL";
        case TK_KEYWORD_IF: return "TK_KEYWORD_IF";
        case TK_KEYWORD_ELSE: return "TK_KEYWORD_ELSE";
        case TK_KEYWORD_WHILE: return "TK_KEYWORD_WHILE";
        case TK_KEYWORD_FOR: return "TK_KEYWORD_FOR";
        case TK_KEYWORD_RETURN: return "TK_KEYWORD_RETURN";

        case TK_OPERATOR_PLUS: return "TK_OPERATOR_PLUS";
        case TK_OPERATOR_MINUS: return "TK_OPERATOR_MINUS";
        case TK_OPERATOR_MULTIPLY: return "TK_OPERATOR_MULTIPLY";
        case TK_OPERATOR_DIVIDE: return "TK_OPERATOR_DIVIDE";
        case TK_OPERATOR_ASSIGN: return "TK_OPERATOR_ASSIGN";
        case TK_OPERATOR_EQUAL: return "TK_OPERATOR_EQUAL";
        case TK_OPERATOR_GREATER: return "TK_OPERATOR_GREATER";
        case TK_OPERATOR_GREATER_EQUAL: return "TK_OPERATOR_GREATER_EQUAL";
        case TK_OPERATOR_LESS: return "TK_OPERATOR_LESS";
        case TK_OPERATOR_LESS_EQUAL: return "TK_OPERATOR_LESS_EQUAL";
        case TK_OPERATOR_NOT_EQUAL: return "TK_OPERATOR_NOT_EQUAL";
        case TK_OPERATOR_NOT: return "TK_OPERATOR_NOT";
        case TK_OPERATOR_AND: return "TK_OPERATOR_AND";
        case TK_OPERATOR_OR: return "TK_OPERATOR_OR";
        case TK_OPERATOR_AND_AND: return "TK_OPERATOR_AND_AND";
        case TK_OPERATOR_OR_OR: return "TK_OPERATOR_OR_OR";

        case TK_IDENTIFIER: return "TK_IDENTIFIER";
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_COMMA: return "TK_COMMA";
        case TK_LEFT_BRACE: return "TK_LEFT_BRACE";
        case TK_RIGHT_BRACE: return "TK_RIGHT_BRACE";
        case TK_LEFT_PARENTHESES: return "TK_LEFT_PARENTHESES";
        case TK_RIGHT_PARENTHESES: return "TK_RIGHT_PARENTHESES";
        case TK_EOF: return "TK_EOF";

        default: return "UNKNOWN_TOKEN";
    }
}


void print_token_stream(const TokenList *token_stream) {

    for (size_t i = 0; i < token_stream->count; i++) {
        char token_type = token_stream->tokens[i].type;
        const char *token = token_type_to_string(token_type);
        if (token_stream->tokens[i].value != NULL) {
            printf("[%s : %s]", token, (char *)token_stream->tokens[i].value);
        } else {
            printf("[%s]", token);
        }
    }
    printf("\n");
}