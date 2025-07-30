//
// Created by bogdante on 30.07.25.
//

#include "lexer.h"
#define TOKEN_CAPACITY_INCREMENT 20
#define MAX_LITERAL_SIZE 512


void parse_error(char after, char unexpected) {
    fprintf(stderr, "[ERROR] Parse error unexpected token %c after %c\n", unexpected, after);
    exit(1);
}

void memory_error() {
    fprintf(stderr, "[ERROR] Memory allocation error\n");
    exit(1);
}

void null_pointer_error() {
    fprintf(stderr, "[ERROR] Null pointer error\n");
    exit(1);
}

Lexer *lexer_init(const char *text_ptr) {
    Lexer *lexer = malloc(sizeof(Lexer));
    if (lexer == NULL) {
        memory_error();
        exit(1);
    }
    lexer->raw_text = text_ptr;
    lexer->position = 0;
    lexer->raw_text_length = (int32_t)strlen(text_ptr);

    return lexer;
}

TokenList *token_list_init() {
    TokenList *token_list = malloc(sizeof(TokenList));
    if (token_list == NULL) {
        memory_error();
        exit(1);
    }

    token_list->tokens = malloc(sizeof(Token) * TOKEN_CAPACITY_INCREMENT);
    token_list->count = 0;
    token_list->capacity = TOKEN_CAPACITY_INCREMENT;

    return token_list;
}


void next(Lexer *lexer) {
    if (lexer->position < lexer->raw_text_length) {
        lexer->ch = lexer->raw_text[lexer->position++];
    } else {
        lexer->ch = '\0';
    }
}


void add_token(TokenList *token_list, char type, const char buffer[]) {
    Token token;
    token.type = type;
    if (buffer != NULL) {
        size_t buffer_size = strlen(buffer);
        token.value = malloc(sizeof(char) * (buffer_size + 1));
        memcpy(token.value, buffer, buffer_size);
        ((char *)token.value)[buffer_size] = '\0';
    } else {
        token.value = NULL;
    }

    if (token_list->count >= token_list->capacity) {
        token_list->capacity += TOKEN_CAPACITY_INCREMENT;
        Token* reallocated_tokens = realloc(token_list->tokens, token_list->capacity * sizeof(Token));

        if (reallocated_tokens == NULL) {
            memory_error();
        }

        token_list->tokens = reallocated_tokens;
    }

    token_list->tokens[token_list->count++] = token;
}


bool is_lower_char(const char c) {
    return (c >= 'a' && c <= 'z');
}

bool is_upper_char(const char c) {
    return (c >= 'A' && c <= 'Z');
}

bool is_character(const char c) {
    return is_lower_char(c) || is_upper_char(c) || c == '_';
}

bool is_word(char c) {
    return is_character(c) || isdigit(c);
}

char *read_word(Lexer *lexer) {
    char buffer[MAX_LITERAL_SIZE] = { 0 };
    int32_t buff_position = 0;

    while (is_word(lexer->ch) && buff_position < MAX_LITERAL_SIZE) {
        buffer[buff_position++] = lexer->ch;
        next(lexer);
    }

    char *result = malloc(sizeof(char) * (buff_position + 1));
    memcpy(result, buffer, buff_position);
    result[buff_position] = '\0';
    return result;
}

char get_word_type(const char *string) {
    if (strcmp(string, "if") == 0) return TK_KEYWORD_IF;
    if (strcmp(string, "else") == 0) return TK_KEYWORD_ELSE;
    if (strcmp(string, "while") == 0) return TK_KEYWORD_WHILE;
    if (strcmp(string, "for") == 0) return TK_KEYWORD_FOR;
    if (strcmp(string, "return") == 0) return TK_KEYWORD_RETURN;
    if (strcmp(string, "bool") == 0) return TK_KEYWORD_BOOL;
    if (strcmp(string, "U32") == 0) return TK_KEYWORD_U32;
    if (strcmp(string, "U64") == 0) return TK_KEYWORD_U64;
    if (strcmp(string, "I32") == 0) return TK_KEYWORD_I32;
    if (strcmp(string, "I64") == 0) return TK_KEYWORD_I64;
    if (strcmp(string, "F32") == 0) return TK_KEYWORD_F32;
    if (strcmp(string, "F64") == 0) return TK_KEYWORD_F64;
    if (strcmp(string, "U0") == 0) return TK_KEYWORD_U0;
    if (strcmp(string, "Byte") == 0) return TK_KEYWORD_BYTE;
    return TK_IDENTIFIER;
}


TokenList* lex(const char *input) {

    if (input == NULL) {
        null_pointer_error();
    }

    Lexer *lexer = lexer_init(input);
    TokenList *token_list = token_list_init();

    while (true) {
        next(lexer);
        loop_without_next_parse:

        if (lexer->ch == '\0') {
            add_token(token_list, TK_EOF, NULL);
            break;
        }

        if (is_word(lexer->ch)) {
            char *word = read_word(lexer);
            const char type = get_word_type(word);

            if (type == TK_IDENTIFIER) {
                add_token(token_list, type, word);
            } else {
                add_token(token_list, type, NULL);
            }

            free(word);
            goto loop_without_next_parse;
        }

        switch (lexer->ch) {
            case ' ':
            case '\t':
            case '\n': break;
            case '-': add_token(token_list, TK_OPERATOR_MINUS, NULL); break;
            case '+': add_token(token_list, TK_OPERATOR_PLUS, NULL); break;
            case '*': add_token(token_list, TK_OPERATOR_MULTIPLY, NULL); break;
            case '/': add_token(token_list, TK_OPERATOR_DIVIDE, NULL); break;
            case '(': add_token(token_list, TK_LEFT_PARENTHESES, NULL); break;
            case ')': add_token(token_list, TK_RIGHT_PARENTHESES, NULL); break;
            case '{': add_token(token_list, TK_LEFT_BRACE, NULL); break;
            case '}': add_token(token_list, TK_RIGHT_BRACE, NULL); break;
            case ';': add_token(token_list, TK_SEMICOLON, NULL); break;
            case ',': add_token(token_list, TK_COMMA, NULL); break;
            case '=': add_token(token_list, TK_OPERATOR_EQUAL, NULL); break;

            case '!':
                next(lexer);
                if (lexer->ch == '=') {
                    add_token(token_list, TK_OPERATOR_NOT_EQUAL, NULL);
                    break;
                }
                add_token(token_list, TK_OPERATOR_NOT, NULL);
                goto loop_without_next_parse;

            case '<':
                next(lexer);
                if (lexer->ch == '=') {
                    add_token(token_list, TK_OPERATOR_LESS_EQUAL, NULL);
                    break;
                }
                add_token(token_list, TK_OPERATOR_LESS, NULL);
                goto loop_without_next_parse;

            case '>':
                next(lexer);
                if (lexer->ch == '=') {
                    add_token(token_list, TK_OPERATOR_GREATER_EQUAL, NULL);
                    break;
                }
                add_token(token_list, TK_OPERATOR_GREATER, NULL);
                goto loop_without_next_parse;

            case '&':
                next(lexer);
                if (lexer->ch == '&') {
                    add_token(token_list, TK_OPERATOR_AND_AND, NULL);
                    break;
                }
                add_token(token_list, TK_OPERATOR_AND, NULL);
                goto loop_without_next_parse;

            case '|':
                next(lexer);
                if (lexer->ch == '|') {
                    add_token(token_list, TK_OPERATOR_OR_OR, NULL);
                    break;
                }
                add_token(token_list, TK_OPERATOR_OR, NULL);
                goto loop_without_next_parse;

            case '"':

                break;

            default:
                fprintf(stderr, "[ERROR] Syntax error unexpected token provided >%c<\n", lexer->ch);
        }
    }

    free(lexer);
    return token_list;
}