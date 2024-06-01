%{
    #define YY_DECL int yylex (void* yyval)
    #include <string.h>
    #include <stdio.h>
	#include <stdlib.h>
    #include "alpha.h"
    #include "parse.h"

    unsigned int numToken = 0;

    alpha_token_t *head = NULL;
    alpha_token_t *temp = NULL;
    alpha_token_t *temp_op = NULL;
%}

%option yylineno
%option noyywrap
%option header-file="alpha_lex.h"

IF 					"if"
ELSE 				"else"
WHILE 				"while"
FOR 				"for"
RETURN 				"return"
BREAK 				"break"
CONTINUE 			"continue"
AND 				"and"
NOT 				"not"
OR 					"or"
LOCAL 				"local"
TRUE 				"true"
FALSE 				"false"
NIL 				"nil"
FUNCTION 			"function"

ASSIGN 				"="
ADD 				"+"
MINUS 				"-"
MULTIPLICATION 		"*"
DIVISION 			"/"
MODULO 				"%"
EQUAL 				"=="
UNEQUAL 			"!="
INCREMENT 			"++"
DECREMENT 			"--"
GREATER 			">"
LESS 				"<"
GREATEROREQUAL 		">="
LESSOREQUAL 		"<="

INTEGER 	    [0-9][0-9]*
REAL 		    [0-9]+\.?[0-9]*
IDENTIFIER 		[a-zA-Z][a-zA-Z0-9_]*

LEFT_CURLY_BRACE	 	"{"
RIGHT_CURLY_BRACE		"}"
LEFT_SQUARE_BRACE	 	"["
RIGHT_SQUARE_BRACE	    "]"
LEFT_PARENTHESIS		"("
RIGHT_PARENTHESIS		")"
SEMICOLON				";"
COMMA					","
COLON					":"
DOUBLE_COLON			"::"
PERIOD					"\."
DOUBLE_PERIOD			"\.\."
SINGLE_LINE_COMMENT		"//"[^\n]*

MULTIPLE_LINE_COMMENT   "/*"

STRING                  "\""

%%

{IF} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return IF;}
{ELSE} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return ELSE;}
{WHILE} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return WHILE;}
{FOR} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return FOR;}
{RETURN} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return RETURN;}
{BREAK} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return BREAK;}
{CONTINUE} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return CONTINUE;}
{AND} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return AND;}
{NOT} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return NOT;}
{OR} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return OR;}
{LOCAL} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return LOCAL;}
{TRUE} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return TRUE;}
{FALSE} 		{temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return FALSE;}
{NIL} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return NIL;}
{FUNCTION} 		{/*yytext[strlen(yytext) - 1] = '\0';*/temp=L_Insert(&head,yylineno,++numToken,yytext,"KEYWORD");return FUNCTION;}
\n              {}

{ASSIGN} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return ASSIGN;}
{INCREMENT} 		{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return INCREMENT;}
{DECREMENT} 		{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return DECREMENT;}
{ADD} 		        {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return ADD;}
{MINUS} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return MINUS;}
{MULTIPLICATION}    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return MULTIPLICATION;}
{DIVISION} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return DIVISION;}
{MODULO} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return MODULO;}
{EQUAL} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return EQUAL;}
{UNEQUAL} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return UNEQUAL;}
{GREATER} 		    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return GREATER;}
{LESS} 		        {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return LESS;}
{GREATEROREQUAL}    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return GREATEROREQUAL;}
{LESSOREQUAL} 		{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"OPERATOR");return LESSOREQUAL;}

{INTEGER} 	    {temp=L_Insert(&head,yylineno,++numToken,yytext,"INTEGER");yylval.intVal = atoi(yytext);return INTEGER;}
{REAL} 		    {temp=L_Insert(&head,yylineno,++numToken,yytext,"REAL");yylval.floatVal = atof(yytext);return REAL;}
{IDENTIFIER} 	{temp=L_Insert(&head,yylineno,++numToken,yytext,"IDENTIFIER");yylval.strVal = strdup(yytext);return IDENTIFIER;}

{LEFT_CURLY_BRACE}	    {temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return LEFT_CURLY_BRACE;}
{RIGHT_CURLY_BRACE}	    {temp_op=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return RIGHT_CURLY_BRACE;}
{LEFT_SQUARE_BRACE}	    {temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return LEFT_SQUARE_BRACE;}
{RIGHT_SQUARE_BRACE}	{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return RIGHT_SQUARE_BRACE;}
{LEFT_PARENTHESIS}		{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return LEFT_PARENTHESIS;}
{RIGHT_PARENTHESIS}		{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return RIGHT_PARENTHESIS;}
{SEMICOLON}				{temp_op=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return SEMICOLON;}
{COMMA}					{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return COMMA;}
{COLON}					{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return COLON;}
{DOUBLE_COLON}			{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return DOUBLE_COLON;}

{SINGLE_LINE_COMMENT}	{temp=L_Insert(&head,yylineno,++numToken,yytext,"COMMENT");}

{MULTIPLE_LINE_COMMENT} {__comment_handler();}

{STRING}                {yylval.strVal = __string_handler();return STRING;}

{DOUBLE_PERIOD}			{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return DOUBLE_PERIOD;}
{PERIOD}				{temp=L_Insert(&head,yylineno,++numToken,yytext,"PUNCTUATION");return PERIOD;}

\t                      {}
" "                     {}

.                       {fprintf(stderr, "\x1b[31mundefined input : %s in line %d\n \x1b[0m", yytext, yylineno);}

%%

void __comment_handler(){
	int c = input();
    char t = c;
    size_t len;
    char *b = (char *) malloc(2 * sizeof(char));
    b[0] = t;
    b[1] = '\0';

	while(c != 0){
		if(c == '*'){
			c = input();
			if(c == '/'){
                b[strlen(b) - 1] = '\0';
                L_Insert(&head,yylineno,++numToken,b,"COMMENT");
                free(b);
				return;
			}
            else{
                t = c;
                len = strlen(b);
                b = (char *) realloc(b, (len * sizeof(char)) + 2);
                b[len] = t;
                b[len + 1] = '\0';
            }
		}
		else if(c == '/'){
			c = input();
			if(c == '*'){
				__comment_handler();
			}
		}
		else{
			c = input();
            t = c;
            len = strlen(b);
            b = (char *) realloc(b, (len * sizeof(char)) + 2);
            b[len] = t;
            b[len + 1] = '\0';
		}
	}
    fprintf(stderr, "\x1b[31munterminated comment\n \x1b[0m");  
}

char * __string_handler(){
	int c = input();
    int flag = 1;
    char t = c;
    size_t len;
    char *b = (char *) malloc(3 * sizeof(char));
    b[0] = '"';
    b[1] = t;
    b[2] = '\0';

	while(c != 0){
		if(c == '"'){
            L_Insert(&head,yylineno,++numToken,b,"STRING");
            /* free(b); */
            len = strlen(b);
            memmove(b, b + 1, len - 2);
            b[len - 2] = '\0'; 
			return b;
		}
        else if(c == '\\'){
            c = input();
            len = strlen(b);
            if(c == 'n')  {
				b = (char *) realloc(b, (len * sizeof(char)) + 1);
                b[len-1] = '\n';
                b[len] = '\0';
			}
			else if(c == 't') {
				b = (char *) realloc(b, (len * sizeof(char)) + 1);
                b[len-1] = '\t';
                b[len] = '\0';
			}
			else if(c == '\\') {
				b = (char *) realloc(b, (len * sizeof(char)) + 1);
                b[len-1] = '\\';
                b[len] = '\0';
                c = input();
                flag = 0; 
			}
			else if(c == 'r') {
				b = (char *) realloc(b, (len * sizeof(char)) + 1);
                b[len-1] = '\r';
                b[len] = '\0';
			}
            else{
                fprintf(stderr, "\x1b[31munknown escape sequence: '\\%c' in line %d \n \x1b[0m", (char) c, yylineno);  
                t = c;
                b = (char *) realloc(b, (len * sizeof(char)) + 2);
                b[len] = t;
                b[len + 1] = '\0';
            }
        }
		else{
            if(flag){
			    c = input();
            }
            else flag = 1;
            t = c;
            len = strlen(b);
            b = (char *) realloc(b, (len * sizeof(char)) + 2);
            b[len] = t;
            b[len + 1] = '\0';
		}
	}
    fprintf(stderr, "\x1b[31mmissing terminating \" character\n \x1b[0m");  
    return NULL;
}

alpha_token_t * L_Insert(alpha_token_t **h, unsigned int numline, unsigned int numToken, char *content, char *type){
    alpha_token_t *current_token = *h;
    alpha_token_t *new_token;
    new_token = (alpha_token_t *) malloc(sizeof(alpha_token_t));

    while(current_token != NULL && current_token->yylex != NULL) {
        current_token = current_token->yylex;
    }

    new_token->numline = numline;
    new_token->numToken = numToken;
    new_token->content = strdup(content);
    new_token->type = type;
    new_token->yylex = NULL;

    if(current_token == NULL) 
        *h = new_token;
    else 
        current_token->yylex = new_token; 
    
    return new_token;
}   

void L_print(alpha_token_t *h){
    printf("\n-------------------\tLexical Analysis\t-------------------\n");    
    printf("\nline-\tnumOfToken-Content-Type\n");    
    while(h != NULL) {
        printf("%d\t#%d\t%s\t%s\n",  h->numline, h->numToken, h->content, h->type);
        h = h->yylex;
    }
}

void free_all(alpha_token_t *h){
    alpha_token_t *next_token = h;
    while(h != NULL){
        next_token = h->yylex;
        free(h->content);
        free(h);
        h = next_token;
    }
}
