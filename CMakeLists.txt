cmake_minimum_required(VERSION 3.10)

project(42sh VERSION 0.1)

set(CMAKE_C_FLAGS "-Werror -Wextra -Wall -pedantic -g -lreadline")

set(SRCS
    src/main.c
    src/lexer/lexer.c
    src/lexer/token.c
    src/lexer/token_rec.c
    src/parser/ast.c
    src/option/option.c
    )

set(HEADERS
    src/lexer/lexer.h
    src/lexer/token.h
    src/lexer/token_rec.h
    src/parser/ast.h
    src/parser/parser.h
    src/option/option.c
    )

add_executable(42sh ${SRCS} ${HEADERS})
set_property(TARGET 42sh PROPERTY C_STANDARD 99)
target_link_libraries(42sh readline)
