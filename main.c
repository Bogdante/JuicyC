#include <stdio.h>
#include "src/lexer/lexer.h"
#include "src/test/test_lexer.h"

char* read_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    const long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Could not allocate space for file input!\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);
    return buffer;
}

void check_file_stream(const FILE *file, const char *provided_path) {
    if (file == NULL) {
        fprintf(stderr, "Could not open file. Provided path %s\n", provided_path);
        exit(1);
    }
}

void check_extension(const char *path) {
    const size_t len = strlen(path);
    if (len < 3 || strcmp(path + len - 3, ".jc") != 0) {
        fprintf(stderr, "Compiler supports only .jc inputs %s\n", path);
        exit(1);
    }
}


int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    check_file_stream(file, argv[1]);
    check_extension(argv[1]);
    const char *input = read_file(file);
    TokenList *tokens = lex(input);
    print_token_stream(tokens);
    return 0;
}