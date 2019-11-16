#ifndef TOKEN_H
# define TOKEN_H

enum token_type
{
    // context 
    END_OF_FILE = 0,
    IONUMBER,
    WORD,
    HEREDOC,
    ASSIGNMENT_WORD,

    // control operators
    AMPERSAND,
    DOUBLE_AMPERSAND,
    DOUBLE_PIPE,
    PIPE,
    OPEN_PAR,
    CLOSE_PAR,
    SEMICOL,
    DOUBLE_SEMICOL,
    LINE_BREAK,

    // redirection operators
    CHEV_DOUBLE_R,
    CHEV_DOUBLE_L,
    CHEV_DOUBLE_H,
    CHEV_AMP_R,
    CHEV_AMP_L,
    CHEV_PIPE,
    LEFT_RIGHT,
    CHEV_SIMPLE_R,
    CHEV_SIMPLE_L,

    // reserved words
    WHILE,
    UNTIL,
    CASE,
    ESAC,
    IN,
    IF,
    FI,
    THEN,
    ELSE,
    ELIF,
    DO,
    DONE,
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    EXCLAMATION,
    FUNCTION
};


struct token
{
    char *value;
    enum token_type type;
    struct token *next;
};


struct token *init_token(void);
void token_free(struct token *token);

#endif
