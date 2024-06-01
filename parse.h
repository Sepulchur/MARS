/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    STRING = 259,                  /* STRING  */
    INTEGER = 260,                 /* INTEGER  */
    REAL = 261,                    /* REAL  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    WHILE = 264,                   /* WHILE  */
    FOR = 265,                     /* FOR  */
    RETURN = 266,                  /* RETURN  */
    BREAK = 267,                   /* BREAK  */
    CONTINUE = 268,                /* CONTINUE  */
    AND = 269,                     /* AND  */
    NOT = 270,                     /* NOT  */
    OR = 271,                      /* OR  */
    LOCAL = 272,                   /* LOCAL  */
    TRUE = 273,                    /* TRUE  */
    FALSE = 274,                   /* FALSE  */
    NIL = 275,                     /* NIL  */
    FUNCTION = 276,                /* FUNCTION  */
    ASSIGN = 277,                  /* ASSIGN  */
    ADD = 278,                     /* ADD  */
    MINUS = 279,                   /* MINUS  */
    MULTIPLICATION = 280,          /* MULTIPLICATION  */
    DIVISION = 281,                /* DIVISION  */
    MODULO = 282,                  /* MODULO  */
    EQUAL = 283,                   /* EQUAL  */
    UNEQUAL = 284,                 /* UNEQUAL  */
    INCREMENT = 285,               /* INCREMENT  */
    DECREMENT = 286,               /* DECREMENT  */
    GREATER = 287,                 /* GREATER  */
    LESS = 288,                    /* LESS  */
    GREATEROREQUAL = 289,          /* GREATEROREQUAL  */
    LESSOREQUAL = 290,             /* LESSOREQUAL  */
    LEFT_CURLY_BRACE = 291,        /* LEFT_CURLY_BRACE  */
    RIGHT_CURLY_BRACE = 292,       /* RIGHT_CURLY_BRACE  */
    LEFT_SQUARE_BRACE = 293,       /* LEFT_SQUARE_BRACE  */
    RIGHT_SQUARE_BRACE = 294,      /* RIGHT_SQUARE_BRACE  */
    LEFT_PARENTHESIS = 295,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 296,       /* RIGHT_PARENTHESIS  */
    SEMICOLON = 297,               /* SEMICOLON  */
    COMMA = 298,                   /* COMMA  */
    COLON = 299,                   /* COLON  */
    DOUBLE_COLON = 300,            /* DOUBLE_COLON  */
    PERIOD = 301,                  /* PERIOD  */
    DOUBLE_PERIOD = 302,           /* DOUBLE_PERIOD  */
    UMINUS = 303                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define STRING 259
#define INTEGER 260
#define REAL 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define AND 269
#define NOT 270
#define OR 271
#define LOCAL 272
#define TRUE 273
#define FALSE 274
#define NIL 275
#define FUNCTION 276
#define ASSIGN 277
#define ADD 278
#define MINUS 279
#define MULTIPLICATION 280
#define DIVISION 281
#define MODULO 282
#define EQUAL 283
#define UNEQUAL 284
#define INCREMENT 285
#define DECREMENT 286
#define GREATER 287
#define LESS 288
#define GREATEROREQUAL 289
#define LESSOREQUAL 290
#define LEFT_CURLY_BRACE 291
#define RIGHT_CURLY_BRACE 292
#define LEFT_SQUARE_BRACE 293
#define RIGHT_SQUARE_BRACE 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DOUBLE_COLON 300
#define PERIOD 301
#define DOUBLE_PERIOD 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "parse.y"

  char* strVal;
  int   intVal;
  float floatVal;
  struct expr* enode;

#line 170 "parse.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSE_H_INCLUDED  */
