cmake_minimum_required(VERSION 3.10)

project(42sh VERSION 0.1)

set(CMAKE_C_FLAGS "-Werror -Wextra -Wall -pedantic")

set(SRCS
    src/main.c
    src/lexer/lexer.c
    src/lexer/helper.c
    src/parser/ast.c
    )

set(HEADERS
    src/lexer/lexer.h
    src/lexer/helper.h
    src/parser/ast.h
    src/parser/parser.h
    )

add_executable(42sh ${SRCS} ${HEADERS})
set_property(TARGET 42sh PROPERTY C_STANDARD 99)
