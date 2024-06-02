/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING = 259,
    INTEGER = 260,
    REAL = 261,
    IF = 262,
    ELSE = 263,
    WHILE = 264,
    FOR = 265,
    RETURN = 266,
    BREAK = 267,
    CONTINUE = 268,
    AND = 269,
    NOT = 270,
    OR = 271,
    LOCAL = 272,
    TRUE = 273,
    FALSE = 274,
    NIL = 275,
    FUNCTION = 276,
    ASSIGN = 277,
    ADD = 278,
    MINUS = 279,
    MULTIPLICATION = 280,
    DIVISION = 281,
    MODULO = 282,
    EQUAL = 283,
    UNEQUAL = 284,
    INCREMENT = 285,
    DECREMENT = 286,
    GREATER = 287,
    LESS = 288,
    GREATEROREQUAL = 289,
    LESSOREQUAL = 290,
    LEFT_CURLY_BRACE = 291,
    RIGHT_CURLY_BRACE = 292,
    LEFT_SQUARE_BRACE = 293,
    RIGHT_SQUARE_BRACE = 294,
    LEFT_PARENTHESIS = 295,
    RIGHT_PARENTHESIS = 296,
    SEMICOLON = 297,
    COMMA = 298,
    COLON = 299,
    DOUBLE_COLON = 300,
    PERIOD = 301,
    DOUBLE_PERIOD = 302
  };
#endif
/* Tokens.  */
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "parse.y" /* yacc.c:1909  */

  char* strVal;
  int   intVal;
  float floatVal;
  struct expr* enode;

#line 155 "parse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_H_INCLUDED  */
