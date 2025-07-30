cmake_minimum_required(VERSION 3.31)
project(jc C)

set(CMAKE_C_STANDARD 11)

add_executable(jc main.c
        src/common/tokens.h
        src/lexer/lexer.h
        src/lexer/lexer.c
        src/test/test_lexer.h
        src/test/test_lexer.c)
