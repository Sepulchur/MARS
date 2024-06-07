#include <stdlib.h>
    
struct alpha_token{
    unsigned int         numline;
    unsigned int         numToken;
    char                 *content;
    char                 *type;
    struct alpha_token   *yylex;
};

typedef struct alpha_token alpha_token_t;

alpha_token_t * L_Insert(alpha_token_t **h, unsigned int numline, unsigned int numToken, char *content, char *type); 

void L_print(alpha_token_t *h);

void free_all(alpha_token_t *h);

void __comment_handler();

char * __string_handler();
