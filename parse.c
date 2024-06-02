/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parse.y" /* yacc.c:339  */

#include "alpha.h"
#include "alpha_lex.h"
#include "symTable.h"
#include "quad.h"
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);

extern int yylex(void);
extern int yylineno;
extern int tempcounter;
extern unsigned functionLocalOffset;
extern unsigned currQuad;
extern unsigned ORcounter;
extern unsigned ANDcounter;
extern char *yytext;
extern alpha_token_t *head;
extern alpha_token_t *temp;
extern alpha_token_t *temp_op;

alpha_token_t *temp_lvalue;
HashTable *table = NULL;
SymbolTableEntry_t *temp_symbol = NULL;
SymbolTableEntry_t *temp_test = NULL;
SymbolTableEntry_t *error_symbol = NULL;
expr *temp_expr;
expr* ORQuadNo = NULL;
expr* ANDQuadNo = NULL;
expr* tempQuad;
unsigned emits = 0 ; //dritsas
UIntStack *funcStack = NULL;
UIntStack *loopStack = NULL;
UIntStack *breakstacklist;
UIntStack *contstacklist;

bool local = false;
bool make = true;
bool lassignl = false;

unsigned funcNo = 0;
unsigned loopcounter = 0;
unsigned functionDepth = 0;
unsigned currentScope = 0; 
unsigned error_flag = 0;
unsigned key = 11;
unsigned num = 0;
unsigned Mlabel = 0; 
unsigned test = 0;
unsigned retLabel = 0 ; 

void enterScope(){
    currentScope++;
}

void exitScope(HashTable *table){
    hide_scope(table, currentScope);
    currentScope--;
}


#line 129 "parse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parse.h".  */
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
    DOUBLE_PERIOD = 302,
    UMINUS = 303
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
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "parse.y" /* yacc.c:355  */

  char* strVal;
  int   intVal;
  float floatVal;
  struct expr* enode;

#line 272 "parse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 289 "parse.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   532

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   124,   124,   125,   129,   142,   143,   144,   145,   147,
     146,   155,   154,   162,   163,   164,   167,   168,   172,   173,
     182,   191,   200,   209,   218,   224,   230,   236,   242,   248,
     254,   254,   275,   275,   291,   295,   296,   302,   315,   333,
     352,   370,   388,   394,   398,   393,   440,   441,   442,   443,
     444,   448,   489,   517,   528,   532,   533,   540,   541,   545,
     546,   560,   569,   570,   574,   584,   593,   594,   595,   614,
     626,   640,   646,   662,   671,   670,   682,   701,   702,   681,
     731,   743,   744,   730,   761,   762,   763,   764,   765,   766,
     769,   770,   804,   840,   842,   845,   861,   865,   873,   881,
     888,   907,   921,   937,   936,   959,   958,   971,   970
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "INTEGER",
  "REAL", "IF", "ELSE", "WHILE", "FOR", "RETURN", "BREAK", "CONTINUE",
  "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL", "FUNCTION",
  "ASSIGN", "ADD", "MINUS", "MULTIPLICATION", "DIVISION", "MODULO",
  "EQUAL", "UNEQUAL", "INCREMENT", "DECREMENT", "GREATER", "LESS",
  "GREATEROREQUAL", "LESSOREQUAL", "LEFT_CURLY_BRACE", "RIGHT_CURLY_BRACE",
  "LEFT_SQUARE_BRACE", "RIGHT_SQUARE_BRACE", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON",
  "PERIOD", "DOUBLE_PERIOD", "UMINUS", "$accept", "program", "stmt", "$@1",
  "$@2", "list_of_stmts", "expr", "$@3", "$@4", "term", "assignexpr",
  "$@5", "$@6", "primary", "lvalue", "member", "call", "callsufix",
  "normallcall", "methodcall", "elist", "objectdef", "indexed",
  "indexedelem", "block", "$@7", "funcdef", "@8", "$@9", "$@10", "@11",
  "$@12", "$@13", "const", "idlist", "N", "M", "ifprefix", "ifstmt",
  "elseprefix", "whilestart", "whilecond", "whilestmt", "forprefix",
  "forstmt", "$@14", "returnstmt", "$@15", "$@16", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -166

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-166)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-108)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -166,   156,  -166,   -37,  -166,  -166,  -166,   -26,  -166,   -20,
     -14,  -166,  -166,   214,    34,  -166,  -166,  -166,    57,   214,
      44,    44,  -166,    88,   185,  -166,    61,  -166,   259,  -166,
    -166,  -166,    79,  -166,    75,  -166,  -166,  -166,  -166,    12,
    -166,    45,  -166,  -166,  -166,  -166,   214,    84,  -166,  -166,
    -166,   214,   214,   214,    48,    58,    69,  -166,  -166,  -166,
      56,    51,    78,     7,    75,     7,    12,   214,   457,    19,
      20,  -166,   325,    90,  -166,  -166,  -166,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   214,  -166,  -166,
    -166,   214,   113,   123,   214,   214,   117,   141,   214,    12,
     214,    54,   111,   347,   -38,   281,  -166,  -166,  -166,   112,
    -166,   114,    12,   116,   237,  -166,   214,  -166,   118,  -166,
     124,  -166,  -166,    51,    51,  -166,  -166,  -166,   484,   484,
     223,   223,   223,   223,   391,  -166,  -166,   413,    86,  -166,
    -166,    12,   369,  -166,    89,  -166,   214,  -166,  -166,  -166,
    -166,   155,   124,  -166,  -166,   214,   457,  -166,   214,   214,
     214,  -166,   214,  -166,  -166,  -166,  -166,  -166,    94,   214,
     155,  -166,    95,   435,    98,   471,   497,   457,  -166,  -166,
     303,   101,  -166,   167,  -166,  -166,    12,  -166,  -166,   136,
    -166,  -166,   136,  -166,  -166,  -166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    51,    86,    84,    85,     0,    99,     0,
     105,     9,    11,     0,     0,    88,    89,    87,    80,     0,
       0,     0,    74,    66,     0,    15,     0,     3,     0,    34,
      18,    42,    46,    54,    47,    48,    13,    14,    50,     0,
       5,     0,     6,    93,     7,     8,    66,     0,    60,    62,
      63,     0,    66,     0,     0,     0,     0,    37,    52,    76,
       0,    36,     0,    38,     0,    40,    17,     0,    67,     0,
       0,    71,     0,     0,    53,    30,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,    39,
      41,     0,     0,     0,     0,    66,     0,    96,     0,     0,
      66,     0,     0,     0,     0,     0,   108,    10,    12,     0,
      81,     0,    17,     0,     0,    69,     0,    70,     0,    35,
      49,    94,    94,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,    55,    44,     0,     0,    57,
      98,     0,     0,   101,     0,    64,    66,    95,    94,   106,
      77,    90,     0,    16,    75,     0,    68,    72,    66,     0,
       0,    56,     0,    58,    59,    97,   100,   103,     0,     0,
      90,    91,     0,     0,     0,    31,    33,    45,    93,    65,
       0,     0,    82,     0,    73,    61,     0,   102,    78,     0,
      92,    93,     0,    83,   104,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,    -1,  -166,  -166,    66,   -12,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,    60,  -166,   102,  -166,  -166,  -166,
     -44,  -166,  -166,    63,  -143,  -166,   -18,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,     9,  -165,  -113,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,   112,    55,    56,   113,    28,   121,   122,    29,
      30,    93,   162,    31,    32,    33,    34,    48,    49,    50,
      69,    35,    70,    71,    36,    66,    37,   109,   170,   192,
      60,   151,   189,    38,   172,   100,   159,    39,    40,   141,
      41,    99,    42,    43,    44,   178,    45,    53,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,    57,   101,    46,   148,   116,    73,    61,   104,   160,
      47,    68,    72,   186,    51,     3,     4,     5,     6,     7,
      52,     8,     9,    10,    11,    12,   194,    13,  -107,    14,
      15,    16,    17,    18,    68,   169,    19,    58,    97,   103,
      68,   105,    20,    21,   111,    91,   193,     3,    22,   195,
      23,   138,    24,    92,    25,   114,   144,    26,   115,   117,
      59,    14,   116,   118,    74,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    79,    80,    81,   134,
      63,    65,   137,    68,    62,    98,   142,   102,    68,    26,
     106,     3,     4,     5,     6,   145,   110,   116,   143,    18,
     107,   -43,   168,    13,   156,    14,    15,    16,    17,    89,
      90,   108,    19,    94,   174,    95,   135,    91,    20,    21,
     139,    96,    64,    64,    67,    92,    23,   164,    24,   116,
     167,   120,   116,    26,    68,   179,   182,   116,   183,   185,
     165,   116,   188,   173,   183,   136,    68,   175,   176,   140,
     177,   146,   150,   154,    67,   152,     2,   180,   171,     3,
       4,     5,     6,     7,   158,     8,     9,    10,    11,    12,
     190,    13,    22,    14,    15,    16,    17,    18,   153,   181,
      19,   157,     0,     0,     0,   191,    20,    21,     3,     4,
       5,     6,    22,     0,    23,     0,    24,     0,    25,     0,
      13,    26,    14,    15,    16,    17,    18,     0,     0,    19,
       0,     0,     0,     0,     0,    20,    21,     3,     4,     5,
       6,     0,     0,    23,     0,    24,     0,     0,     0,    13,
      26,    14,    15,    16,    17,     0,     0,     0,    19,     0,
       0,     0,     0,     0,    20,    21,    77,    78,    79,    80,
      81,    75,    23,    76,    24,  -108,  -108,  -108,  -108,    26,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87,    75,     0,    76,     0,     0,     0,     0,
       0,   155,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    84,    85,    86,    87,    75,     0,    76,     0,     0,
       0,    88,     0,     0,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    75,     0,    76,
       0,     0,     0,   149,     0,     0,    77,    78,    79,    80,
      81,    82,    83,     0,     0,    84,    85,    86,    87,    75,
       0,    76,     0,     0,     0,   187,     0,     0,    77,    78,
      79,    80,    81,    82,    83,     0,     0,    84,    85,    86,
      87,    75,     0,    76,     0,     0,   119,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87,    75,     0,    76,     0,     0,   147,     0,
       0,     0,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    84,    85,    86,    87,    75,     0,    76,     0,     0,
     166,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    75,     0,    76,
     161,     0,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,     0,     0,    84,    85,    86,    87,    75,
       0,    76,   163,     0,     0,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,     0,     0,    84,    85,    86,
      87,    75,   184,    76,     0,     0,     0,     0,     0,     0,
      77,    78,    79,    80,    81,    82,    83,    76,     0,    84,
      85,    86,    87,     0,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    77,    78,    79,
      80,    81,  -108,  -108,     0,     0,    84,    85,    86,    87,
      77,    78,    79,    80,    81,    82,    83,     0,     0,    84,
      85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       1,    13,    46,    40,    42,    43,    24,    19,    52,   122,
      47,    23,    24,   178,    40,     3,     4,     5,     6,     7,
      40,     9,    10,    11,    12,    13,   191,    15,    42,    17,
      18,    19,    20,    21,    46,   148,    24,     3,    39,    51,
      52,    53,    30,    31,    62,    38,   189,     3,    36,   192,
      38,    95,    40,    46,    42,    67,   100,    45,    39,    39,
       3,    17,    43,    43,     3,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    25,    26,    27,    91,
      20,    21,    94,    95,    40,    40,    98,     3,   100,    45,
      42,     3,     4,     5,     6,    41,    40,    43,    99,    21,
      42,    22,   146,    15,   116,    17,    18,    19,    20,    30,
      31,    42,    24,    38,   158,    40,     3,    38,    30,    31,
       3,    46,    20,    21,    36,    46,    38,    41,    40,    43,
      41,    41,    43,    45,   146,    41,    41,    43,    43,    41,
     141,    43,    41,   155,    43,    22,   158,   159,   160,     8,
     162,    40,    40,    37,    36,    41,     0,   169,     3,     3,
       4,     5,     6,     7,    40,     9,    10,    11,    12,    13,
       3,    15,    36,    17,    18,    19,    20,    21,   112,   170,
      24,   118,    -1,    -1,    -1,   186,    30,    31,     3,     4,
       5,     6,    36,    -1,    38,    -1,    40,    -1,    42,    -1,
      15,    45,    17,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,     3,     4,     5,
       6,    -1,    -1,    38,    -1,    40,    -1,    -1,    -1,    15,
      45,    17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    23,    24,    25,    26,
      27,    14,    38,    16,    40,    32,    33,    34,    35,    45,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    14,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    44,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    14,    -1,    16,    -1,    -1,
      -1,    42,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    14,    -1,    16,
      -1,    -1,    -1,    42,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    14,
      -1,    16,    -1,    -1,    -1,    42,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    14,    -1,    16,    -1,    -1,    41,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    14,    -1,    16,    -1,    -1,    41,    -1,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    14,    -1,    16,    -1,    -1,
      41,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    14,    -1,    16,
      39,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    14,
      -1,    16,    39,    -1,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    14,    37,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    16,    -1,    32,
      33,    34,    35,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,     0,     3,     4,     5,     6,     7,     9,    10,
      11,    12,    13,    15,    17,    18,    19,    20,    21,    24,
      30,    31,    36,    38,    40,    42,    45,    51,    55,    58,
      59,    62,    63,    64,    65,    70,    73,    75,    82,    86,
      87,    89,    91,    92,    93,    95,    40,    47,    66,    67,
      68,    40,    40,    96,    97,    52,    53,    55,     3,     3,
      79,    55,    40,    63,    65,    63,    74,    36,    55,    69,
      71,    72,    55,    75,     3,    14,    16,    23,    24,    25,
      26,    27,    28,    29,    32,    33,    34,    35,    42,    30,
      31,    38,    46,    60,    38,    40,    46,    51,    40,    90,
      84,    69,     3,    55,    69,    55,    42,    42,    42,    76,
      40,    75,    51,    54,    55,    39,    43,    39,    43,    41,
      41,    56,    57,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,     3,    22,    55,    69,     3,
       8,    88,    55,    51,    69,    41,    40,    41,    42,    42,
      40,    80,    41,    54,    37,    44,    55,    72,    40,    85,
      85,    39,    61,    39,    41,    51,    41,    41,    69,    85,
      77,     3,    83,    55,    69,    55,    55,    55,    94,    41,
      55,    83,    41,    43,    37,    41,    84,    42,    41,    81,
       3,    51,    78,    73,    84,    73
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    51,    51,    52,
      51,    53,    51,    51,    51,    51,    54,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    55,    57,    55,    55,    58,    58,    58,    58,    58,
      58,    58,    58,    60,    61,    59,    62,    62,    62,    62,
      62,    63,    63,    63,    63,    64,    64,    64,    64,    65,
      65,    65,    66,    66,    67,    68,    69,    69,    69,    70,
      70,    71,    71,    72,    74,    73,    76,    77,    78,    75,
      79,    80,    81,    75,    82,    82,    82,    82,    82,    82,
      83,    83,    83,    84,    85,    86,    87,    87,    88,    89,
      90,    91,    92,    94,    93,    96,    95,    97,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     0,
       3,     0,     3,     1,     1,     1,     2,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     5,     0,     5,     1,     3,     2,     2,     2,     2,
       2,     2,     1,     0,     0,     5,     1,     1,     1,     3,
       1,     1,     2,     2,     1,     3,     4,     3,     4,     4,
       2,     6,     1,     1,     3,     5,     0,     1,     3,     3,
       3,     1,     3,     5,     0,     4,     0,     0,     0,     9,
       0,     0,     0,     8,     1,     1,     1,     1,     1,     1,
       0,     1,     3,     0,     0,     4,     2,     4,     1,     1,
       3,     3,     7,     0,     8,     0,     4,     0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 130 "parse.y" /* yacc.c:1646  */
    {
      resettemp(); 
      (yyval.enode)=NULL;
      if(emits == 1){ //dritsas
        backPatch((yyvsp[-1].enode)->falseList, nextquadlabel()+2);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(0), NULL, currQuad, yylineno);
        make = true;
        emits = 0;
      }
    }
#line 1589 "parse.c" /* yacc.c:1646  */
    break;

  case 5:
#line 142 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1595 "parse.c" /* yacc.c:1646  */
    break;

  case 6:
#line 143 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1601 "parse.c" /* yacc.c:1646  */
    break;

  case 7:
#line 144 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1607 "parse.c" /* yacc.c:1646  */
    break;

  case 8:
#line 145 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1613 "parse.c" /* yacc.c:1646  */
    break;

  case 9:
#line 147 "parse.y" /* yacc.c:1646  */
    {
      if(!loopcounter){yyerror("Use of 'break' while not in a loop");}
    }
#line 1621 "parse.c" /* yacc.c:1646  */
    break;

  case 10:
#line 151 "parse.y" /* yacc.c:1646  */
    {
      emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
    }
#line 1629 "parse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "parse.y" /* yacc.c:1646  */
    {
      if(!loopcounter){yyerror("Use of 'continue' while not in a loop");}
    }
#line 1637 "parse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 159 "parse.y" /* yacc.c:1646  */
    {
      emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
    }
#line 1645 "parse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 162 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1651 "parse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 163 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1657 "parse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 164 "parse.y" /* yacc.c:1646  */
    {resettemp(); (yyval.enode)=NULL;}
#line 1663 "parse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[-1].enode);}
#line 1669 "parse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 168 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = NULL;}
#line 1675 "parse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 172 "parse.y" /* yacc.c:1646  */
    {(yyval.enode)=(yyvsp[0].enode);}
#line 1681 "parse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 174 "parse.y" /* yacc.c:1646  */
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(add, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1694 "parse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 183 "parse.y" /* yacc.c:1646  */
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table);
        emit(sub, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1707 "parse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 192 "parse.y" /* yacc.c:1646  */
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(mul, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1720 "parse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 201 "parse.y" /* yacc.c:1646  */
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(div_, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1733 "parse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 210 "parse.y" /* yacc.c:1646  */
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(mod, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1746 "parse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 219 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_eq, yylineno);  
    }
#line 1756 "parse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 225 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table);
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_noteq, yylineno); 
    }
#line 1766 "parse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 231 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_greater, yylineno);
    }
#line 1776 "parse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 237 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_less, yylineno); 
    }
#line 1786 "parse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 243 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_greatereq, yylineno);
    }
#line 1796 "parse.c" /* yacc.c:1646  */
    break;

  case 29:
#line 249 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e); 
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_lesseq, yylineno); 
    }
#line 1806 "parse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 254 "parse.y" /* yacc.c:1646  */
    {logicEmit((yyvsp[-1].enode),yylineno);}
#line 1812 "parse.c" /* yacc.c:1646  */
    break;

  case 31:
#line 255 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-4].enode), (yyvsp[0].enode), table);

			logicEmit((yyvsp[0].enode), yylineno);

			Mlabel = (yyvsp[0].enode)->trueList->label;
      printf("263");
			backPatch((yyvsp[-4].enode)->trueList, Mlabel);
			backPatch((yyvsp[-4].enode)->falseList, (yyvsp[-4].enode)->falseList->label+2);

      if(ORcounter == 1){ //dritsas
				backPatch(tempQuad, Mlabel+2);
        ORcounter = 0;
			}
														
			(yyval.enode)->trueList = (yyvsp[0].enode)->trueList;
			(yyval.enode)->falseList = mergelist((yyvsp[-4].enode)->falseList, (yyvsp[0].enode)->falseList);
      emits = 1;
		}
#line 1837 "parse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 275 "parse.y" /* yacc.c:1646  */
    {logicEmit((yyvsp[-1].enode), yylineno);}
#line 1843 "parse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 276 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-4].enode), (yyvsp[0].enode), table); 
      logicEmit((yyvsp[0].enode), yylineno);
			Mlabel=(yyvsp[0].enode)->trueList->label;
			backPatch((yyvsp[-4].enode)->falseList, Mlabel);
			backPatch((yyvsp[-4].enode)->trueList, (yyvsp[-4].enode)->trueList->numConst+2);

			tempQuad = cloneList((yyvsp[-4].enode)->trueList); //dritsas

			(yyval.enode)->trueList = mergelist((yyvsp[-4].enode)->trueList, (yyvsp[0].enode)->trueList);
			(yyval.enode)->falseList = (yyvsp[0].enode)->falseList;
      ORcounter = 1;
      emits = 1;
		}
#line 1863 "parse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 291 "parse.y" /* yacc.c:1646  */
    {(yyval.enode)=(yyvsp[0].enode);}
#line 1869 "parse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 295 "parse.y" /* yacc.c:1646  */
    {(yyval.enode)=(yyvsp[-1].enode);}
#line 1875 "parse.c" /* yacc.c:1646  */
    break;

  case 36:
#line 297 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode)=newexpr(arithexpr_e); 
      (yyval.enode)->sym = newtemp(table,0); 
      emit(uminus, (yyval.enode), (yyvsp[0].enode), (expr *) 0, currQuad, yylineno);
    }
#line 1885 "parse.c" /* yacc.c:1646  */
    break;

  case 37:
#line 303 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode)=newexpr(boolexpr_e); 
      (yyval.enode)->sym = newtemp(table,0); 
			if((yyvsp[0].enode)->type!=boolexpr_e){
				(yyvsp[0].enode)->trueList = createTrueList(nextquadlabel());
				(yyvsp[0].enode)->falseList= createFalseList(nextquadlabel());  
				emit(if_eq, (yyvsp[0].enode)->falseList, (yyvsp[0].enode), newexpr_constbool(1), currQuad+2, yylineno);
				emit(jump, (yyvsp[0].enode)->trueList, NULL, NULL, currQuad+1, yylineno);
			}
			(yyval.enode)->trueList = (yyvsp[0].enode)->falseList; 
			(yyval.enode)->falseList = (yyvsp[0].enode)->trueList; 
    }
#line 1902 "parse.c" /* yacc.c:1646  */
    break;

  case 38:
#line 316 "parse.y" /* yacc.c:1646  */
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot increment function value\n");
      }
      if((yyvsp[0].enode)->type == tableitem_e){
        (yyval.enode) = emit_iftableitem((yyvsp[0].enode),table,yylineno);
        emit(add, (yyval.enode), (yyval.enode), newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, (yyvsp[0].enode), (yyvsp[0].enode)->index,(yyval.enode), currQuad, yylineno);
      }
      else{
        emit(add, (yyvsp[0].enode), (yyvsp[0].enode), newexpr_constnum(1), currQuad, yylineno);
        (yyval.enode) = newexpr(arithexpr_e);
        (yyval.enode)->sym = newtemp(table,0);
        emit(assign, (yyval.enode), (yyvsp[0].enode), NULL, currQuad, yylineno);
      }
    }
#line 1924 "parse.c" /* yacc.c:1646  */
    break;

  case 39:
#line 334 "parse.y" /* yacc.c:1646  */
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot increment function value\n");
      }
      (yyval.enode) = newexpr(var_e); 
      (yyval.enode)->sym = newtemp(table,0);
      if((yyvsp[-1].enode)->type == tableitem_e){
        expr * value = emit_iftableitem((yyvsp[-1].enode),table,yylineno);
        emit(assign, (yyval.enode), value, NULL, currQuad, yylineno);
        emit(add, value, value, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, (yyvsp[-1].enode), (yyvsp[-1].enode)->index,value, currQuad, yylineno);
      }
      else{
        emit(assign, (yyval.enode), (yyvsp[-1].enode), NULL, currQuad, yylineno);
        emit(add, (yyvsp[-1].enode), (yyvsp[-1].enode), newexpr_constnum(1), currQuad, yylineno);
      }
    }
#line 1947 "parse.c" /* yacc.c:1646  */
    break;

  case 40:
#line 353 "parse.y" /* yacc.c:1646  */
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot decrement function value\n");
      }
      if((yyvsp[0].enode)->type == tableitem_e){
        (yyval.enode) = emit_iftableitem((yyvsp[0].enode),table,yylineno);
        emit(sub, (yyval.enode), (yyval.enode), newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, (yyvsp[0].enode), (yyvsp[0].enode)->index,(yyval.enode), currQuad, yylineno);
      }
      else{
        emit(sub, (yyvsp[0].enode), (yyvsp[0].enode), newexpr_constnum(1), currQuad, yylineno);
        (yyval.enode) = newexpr(arithexpr_e);
        (yyval.enode)->sym = newtemp(table,0);
        emit(assign, (yyval.enode), (yyvsp[0].enode), NULL, currQuad, yylineno);
      }
    }
#line 1969 "parse.c" /* yacc.c:1646  */
    break;

  case 41:
#line 371 "parse.y" /* yacc.c:1646  */
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot decrement function value\n");
      }
      (yyval.enode) = newexpr(var_e); (yyval.enode)->sym = newtemp(table,0);
      if((yyvsp[-1].enode)->type == tableitem_e){
        expr * value = emit_iftableitem((yyvsp[-1].enode),table,yylineno);
        emit(assign, (yyval.enode), value, NULL, currQuad, yylineno);
        emit(sub, value, value, newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem, (yyvsp[-1].enode), (yyvsp[-1].enode)->index,value, currQuad, yylineno);
      }
      else{
        emit(assign, (yyval.enode), (yyvsp[-1].enode), NULL, currQuad, yylineno);
        emit(sub, (yyvsp[-1].enode), (yyvsp[-1].enode), newexpr_constnum(1), currQuad, yylineno);
      }                  
    }
#line 1991 "parse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 388 "parse.y" /* yacc.c:1646  */
    {(yyval.enode)=(yyvsp[0].enode);}
#line 1997 "parse.c" /* yacc.c:1646  */
    break;

  case 43:
#line 394 "parse.y" /* yacc.c:1646  */
    {
      /*$1 = lvalue_expr(temp_test); */
    }
#line 2005 "parse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 398 "parse.y" /* yacc.c:1646  */
    {
      lassignl=true;
    }
#line 2013 "parse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 402 "parse.y" /* yacc.c:1646  */
    {
      if(emits ==1){ //dritsas
        backPatch((yyvsp[0].enode)->falseList, nextquadlabel()+2); 
        emit(assign, (yyvsp[0].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, (yyvsp[0].enode), newexpr_constbool(0), NULL, currQuad, yylineno);
        emits = 0 ;
      }

      lassignl=false;
      if(local){
        local = false;
      }
      else{
        SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
        if(t != NULL && t->type > 3){
          yyerror("Cannot assign value to function at line ");
        }
      }
			if((yyvsp[-4].enode) != NULL && (yyvsp[-4].enode)->type == tableitem_e){
        if((yyvsp[0].enode) != NULL){
        (yyval.enode) =  emit_iftableitem((yyvsp[0].enode), table,yylineno);
        }
				emit(tablesetelem, (yyvsp[-4].enode),  (yyvsp[-4].enode)->index , (yyval.enode) , currQuad , yylineno);

				(yyval.enode) = emit_iftableitem((yyvsp[-4].enode), table,yylineno);
				(yyval.enode)->type = assignexpr_e;
			}
      else{
				emit(assign, (yyvsp[-4].enode), (yyvsp[0].enode), NULL, currQuad, yylineno); 
				(yyval.enode) = newexpr(assignexpr_e); 
				(yyval.enode)->sym = newtemp(table,var_s); 
				emit(assign, (yyval.enode), (yyvsp[-4].enode), NULL, currQuad, yylineno); 
			}
		}
#line 2053 "parse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 440 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2059 "parse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 441 "parse.y" /* yacc.c:1646  */
    {}
#line 2065 "parse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 442 "parse.y" /* yacc.c:1646  */
    {}
#line 2071 "parse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 443 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[-1].enode);}
#line 2077 "parse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 444 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2083 "parse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 449 "parse.y" /* yacc.c:1646  */
    {
      temp_lvalue = temp;
      temp_lvalue->content = (yyvsp[0].strVal);
      SymbolTableEntry_t *new;
      SymbolTableEntry_t *temp_s = NULL;
      if(currentScope){
        new = create_entry(key+1,LOCALVAR,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      else{
        new = create_entry(key+1,GLOBAL,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      if(H_Search(table, currentScope, temp_lvalue->content)!= -1 ){
        yyerror("doesnt have acccess");
        free(new);
      }
      else if(checkLib(table,new)){
        yyerror("Conflicting name with library function");
        free(new);
      }
      else if(!(temp_s = H_Lookup(table, currentScope, temp_lvalue->content))){
        if(!0){
          temp_s = H_Insert(&table, new);
          H_insertExtras(temp_s);
          key++;
        }
        else{
          free(new);
        }
      }
      else{
        free(new);
      }
      if(temp_s == NULL){
        (yyval.enode) = NULL;
      }
      else{
        temp_test = temp_s;/*what's up danger*/
        (yyval.enode) = lvalue_expr(temp_s);
      }
    }
#line 2128 "parse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 490 "parse.y" /* yacc.c:1646  */
    {
      local = true;
      temp_lvalue=temp;
      SymbolTableEntry_t *new;
      SymbolTableEntry_t *temp = NULL;
      SymbolTableEntry_t *temp_s = NULL;
      if(currentScope){
        new = create_entry(key+1,LOCALVAR,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      else{
        new = create_entry(key+1,GLOBAL,createPassport(temp_lvalue->content, currentScope), temp_lvalue->numline);
      }
      if(checkLib(table,new)){
        yyerror("Conflicting name with library function");
      }
      else if(H_Lookup(table, currentScope, temp_lvalue->content)==NULL){
        key++;
        temp_s = H_Insert(&table, new);
        H_insertExtras(temp_s);
      }
      if(temp_s == NULL){
        (yyval.enode) = NULL;
      }
      else{
        (yyval.enode) = lvalue_expr(temp_s);
      }
    }
#line 2160 "parse.c" /* yacc.c:1646  */
    break;

  case 53:
#line 518 "parse.y" /* yacc.c:1646  */
    {
      temp_lvalue=temp;
      SymbolTableEntry_t *temp_s = H_Lookup(table, 0, temp_lvalue->content);
			if(temp_s == NULL && currentScope != 0){
        yyerror("Undefined GLOBAL variable");   
			}
      else{
        (yyval.enode) = lvalue_expr(temp_s);
      }
    }
#line 2175 "parse.c" /* yacc.c:1646  */
    break;

  case 54:
#line 528 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2181 "parse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 532 "parse.y" /* yacc.c:1646  */
    {if((yyvsp[-2].enode) != NULL){(yyval.enode) = member_item((yyvsp[-2].enode), (yyvsp[0].strVal), table , yylineno);}}
#line 2187 "parse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 534 "parse.y" /* yacc.c:1646  */
    { 
      (yyvsp[-3].enode) = emit_iftableitem((yyvsp[-3].enode), table,yylineno); 
      (yyval.enode) = newexpr(tableitem_e); 
      (yyval.enode)->sym = (yyvsp[-3].enode)->sym; 
      (yyval.enode)->index = (yyvsp[-1].enode); 
    }
#line 2198 "parse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 540 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = NULL;}
#line 2204 "parse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 541 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = NULL;}
#line 2210 "parse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 545 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = make_call((yyvsp[-3].enode), (yyvsp[-1].enode), table, yylineno);}
#line 2216 "parse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 547 "parse.y" /* yacc.c:1646  */
    {
      //SymbolTableEntry_t *new = create_entry(0,USERFUNC,createPassport($1, currentScope), yylineno);
      SymbolTableEntry_t *new = H_Lookup(table, -1, (yyvsp[-1].strVal));
      H_insertExtras(new);
      expr *temp_lvalue_expr = lvalue_expr(new);
			if((yyvsp[0].enode)->boolConst == '1'){
        expr *self = temp_lvalue_expr;
        temp_lvalue_expr = emit_iftableitem(member_item(self, (yyvsp[0].enode)->strConst, table , yylineno),table,yylineno);
        self->next = (yyvsp[0].enode)->next; 
        (yyvsp[0].enode) = self;
			}
			(yyval.enode) = make_call(temp_lvalue_expr, (yyvsp[0].enode), table, yylineno);
		}
#line 2234 "parse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 561 "parse.y" /* yacc.c:1646  */
    {
			expr* func = newexpr(programfunc_e);
			func->sym = (yyvsp[-4].enode)->sym;
			(yyval.enode) = make_call(func, (yyvsp[-1].enode),table, yylineno);
		}
#line 2244 "parse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 569 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2250 "parse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 570 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2256 "parse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 575 "parse.y" /* yacc.c:1646  */
    {	
			(yyval.enode) = newexpr(nil_e);
			(yyval.enode)->next = (yyvsp[-1].enode);
			(yyval.enode)->strConst = NULL;
			(yyval.enode)->boolConst = false;
		}
#line 2267 "parse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 585 "parse.y" /* yacc.c:1646  */
    {
			(yyval.enode) = newexpr(tableitem_e);
			(yyval.enode)->next = (yyvsp[-1].enode);
			(yyval.enode)->strConst = (yyvsp[-3].strVal);
			(yyval.enode)->boolConst = '1';
		}
#line 2278 "parse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 593 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = NULL;}
#line 2284 "parse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 594 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = (yyvsp[0].enode);}
#line 2290 "parse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 596 "parse.y" /* yacc.c:1646  */
    {
      expr *new_node = (yyvsp[0].enode); 
      expr *temp2 = (yyvsp[-2].enode);    
      if(temp2 != NULL){
        while (temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = new_node;
      } 
      else{
          (yyval.enode) = new_node;
      }
      new_node->next = NULL; 
    }
#line 2309 "parse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 615 "parse.y" /* yacc.c:1646  */
    {
      int i = 0;
			expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while((yyvsp[-1].enode) != NULL){
				emit(tablesetelem, node, newexpr_constnum(i++), (yyvsp[-1].enode), currQuad, yylineno);
				(yyvsp[-1].enode) = (yyvsp[-1].enode)->next;
			}
			(yyval.enode) = node;
    }
#line 2325 "parse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 627 "parse.y" /* yacc.c:1646  */
    {
      expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while((yyvsp[-1].enode)!=NULL){
				emit(tablesetelem, node, (yyvsp[-1].enode)->index, (yyvsp[-1].enode), currQuad, yylineno);
				(yyvsp[-1].enode) = (yyvsp[-1].enode)->next;
			}
			(yyval.enode) = node;		
    }
#line 2340 "parse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 641 "parse.y" /* yacc.c:1646  */
    { 
      expr *node = (yyvsp[0].enode);
      node->next = NULL; 
      (yyval.enode) = node;
    }
#line 2350 "parse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 647 "parse.y" /* yacc.c:1646  */
    {
      expr *node = (yyvsp[0].enode);
      expr *temp = (yyvsp[-2].enode);

      while (temp->next != NULL) {
          temp = temp->next;
      }
      temp->next = node; 
      node->next = NULL; 

      (yyval.enode) = (yyvsp[-2].enode);
    }
#line 2367 "parse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 663 "parse.y" /* yacc.c:1646  */
    {
      (yyval.enode) = (yyvsp[-1].enode);
      (yyval.enode)->index = (yyvsp[-3].enode);
    }
#line 2376 "parse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 671 "parse.y" /* yacc.c:1646  */
    {
      enterScope();
    }
#line 2384 "parse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 675 "parse.y" /* yacc.c:1646  */
    {
      exitScope(table);
    }
#line 2392 "parse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 682 "parse.y" /* yacc.c:1646  */
    {
      functionDepth++;
      SymbolTableEntry_t *new = create_entry(key+1,USERFUNC,createPassport(temp->content, currentScope), temp->numline); 
      if(!validity_check(table, new,true)){
        temp_symbol = H_Insert(&table, new);
        key++;
        (yyval.enode) = lvalue_expr(temp_symbol);
				(yyval.enode)->sym->address = nextquadlabel();
				funcNo = nextquadlabel();
				emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, temp->numline);
				emit(funcstart, (yyval.enode), NULL, NULL, currQuad, temp->numline);
				push(funcStack, functionLocalOffset);
				temp_expr = (yyval.enode);
      }
      else{
        error_symbol = create_entry(key+1,USERFUNC,createPassport(temp->content, currentScope), temp->numline); 
      }
      resetformalargsoffset();
    }
#line 2416 "parse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 701 "parse.y" /* yacc.c:1646  */
    {enterscopespace();}
#line 2422 "parse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 702 "parse.y" /* yacc.c:1646  */
    {
        enterscopespace(); 
        resetfunctionlocalsoffset(); 
        push(loopStack, loopcounter); 
        loopcounter = 0;
        if(error_symbol != NULL){
          ArgList *atemp, *atemp2;
          atemp = error_symbol->argList;
          while(atemp){
            atemp2 = atemp;
            atemp = atemp->next;
            free(atemp2);
          }
          free(error_symbol);
        }
      }
#line 2443 "parse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 719 "parse.y" /* yacc.c:1646  */
    {
      functionDepth--;
 			exitscopespace(); 
      exitscopespace();
			(yyval.enode) = temp_expr;
		  functionLocalOffset = pop(funcStack);
			emit(funcend, (yyval.enode), NULL, NULL, currQuad, yylineno);
			patchlabel(retLabel, currQuad-1); 
			patchlabel(funcNo, nextquadlabel());
			loopcounter = pop(loopStack);
    }
#line 2459 "parse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 731 "parse.y" /* yacc.c:1646  */
    {
      functionDepth++;
      SymbolTableEntry_t *new = create_entry(++key,USERFUNC,createFuncName(currentScope, ++num), temp->numline);
      temp_symbol = H_Insert(&table, new);
      (yyval.enode) = lvalue_expr(temp_symbol);
			funcNo = nextquadlabel();
			emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, yylineno);
			emit(funcstart, (yyval.enode), NULL, NULL, currQuad, yylineno);
			push(funcStack, functionLocalOffset);
			temp_expr = (yyval.enode);
			resetformalargsoffset();
    }
#line 2476 "parse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 743 "parse.y" /* yacc.c:1646  */
    {enterscopespace();}
#line 2482 "parse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 744 "parse.y" /* yacc.c:1646  */
    {
      enterscopespace(); 
    }
#line 2490 "parse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 748 "parse.y" /* yacc.c:1646  */
    {
      functionDepth--;
      exitscopespace(); 
      exitscopespace();
 			(yyval.enode) = temp_expr;
		  functionLocalOffset = pop(funcStack);
		  emit(funcend, (yyval.enode), NULL, NULL, currQuad, yylineno);
			patchlabel(retLabel, currQuad-1); 
		  patchlabel(funcNo, nextquadlabel());
    }
#line 2505 "parse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 761 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr_constnum(yylval.intVal);}
#line 2511 "parse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 762 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr_constnum(yylval.floatVal);}
#line 2517 "parse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 763 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr_conststring(yylval.strVal);}
#line 2523 "parse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 764 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr(nil_e);}
#line 2529 "parse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 765 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr_constbool(1);}
#line 2535 "parse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 766 "parse.y" /* yacc.c:1646  */
    {(yyval.enode) = newexpr_constbool(0);}
#line 2541 "parse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 771 "parse.y" /* yacc.c:1646  */
    {
      passport_t v = createPassport(temp->content, currentScope+1); 
      if(error_symbol == NULL){
        if(AL_Insert(&temp_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
      else{
        if(AL_Insert(&error_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
    }
#line 2579 "parse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 805 "parse.y" /* yacc.c:1646  */
    {
      passport_t v = createPassport(temp->content, currentScope+1); 
      if(error_symbol == NULL){
        if(AL_Insert(&temp_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
      else{
        if(AL_Insert(&error_symbol->argList, v) == NULL){
          yyerror("Redifinition of formal");
        }
        else{
          SymbolTableEntry_t *new = create_entry(key,FORMAL,v,yylineno);
          if(checkLib(table, new)){
            yyerror("Argument causes 'Conflicting name with library function'");
          }
          else{
            key++;
            H_Insert(&table, new);
          }
        }
      }
    }
#line 2617 "parse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 840 "parse.y" /* yacc.c:1646  */
    {(yyval.intVal) = nextquadlabel();emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);}
#line 2623 "parse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 842 "parse.y" /* yacc.c:1646  */
    {(yyval.intVal) = nextquadlabel();}
#line 2629 "parse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 846 "parse.y" /* yacc.c:1646  */
    {
      if(emits){
        backPatch((yyvsp[-1].enode)->falseList, nextquadlabel()+2);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(0), NULL, currQuad, yylineno); 
        emits = 0;
      }
      emit(if_eq, newexpr_constnum(nextquadlabel()+2), (yyvsp[-1].enode), newexpr_constbool('1'), currQuad, yylineno); 
      (yyval.intVal) = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);    
    }
#line 2646 "parse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 862 "parse.y" /* yacc.c:1646  */
    {
      patchlabel((yyvsp[-1].intVal), nextquad());
    }
#line 2654 "parse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 866 "parse.y" /* yacc.c:1646  */
    {
      patchlabel((yyvsp[-3].intVal), (yyvsp[-1].intVal) + 1);
      patchlabel((yyvsp[-1].intVal), nextquad());
    }
#line 2663 "parse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 874 "parse.y" /* yacc.c:1646  */
    {
      (yyval.intVal) = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);
    }
#line 2672 "parse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 882 "parse.y" /* yacc.c:1646  */
    {
      (yyval.intVal) = nextquadlabel();
    }
#line 2680 "parse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 889 "parse.y" /* yacc.c:1646  */
    {
      if(emits){
        backPatch((yyvsp[-1].enode)->falseList, nextquadlabel()+2);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(0), NULL, currQuad, yylineno);
        emits = 0;
      }
      ++loopcounter;	
			push(breakstacklist, 0); 
      push(contstacklist, 0);
			emit(if_eq, newexpr_constnum(nextquadlabel()+2), (yyvsp[-1].enode), newexpr_constbool('1'), currQuad+2, yylineno); 
		  (yyval.intVal) = nextquadlabel();   
			emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, yylineno);
    }
#line 2700 "parse.c" /* yacc.c:1646  */
    break;

  case 101:
#line 908 "parse.y" /* yacc.c:1646  */
    { 
      --loopcounter;
			emit(jump, newexpr_constnum(0), NULL, NULL, (yyvsp[-2].intVal), yylineno);   
			patchlabel((yyvsp[-1].intVal), nextquadlabel());   

			//patchBreakContinue(breakstacklist, nextquadlabel());
			pop(breakstacklist);
			//patchBreakContinue(contstacklist, $1);
			pop(contstacklist);
    }
#line 2715 "parse.c" /* yacc.c:1646  */
    break;

  case 102:
#line 922 "parse.y" /* yacc.c:1646  */
    {
      emits = 0;
      backPatch((yyvsp[-1].enode)->falseList, nextquadlabel()+2);
      emit(assign, (yyvsp[-1].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
      emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
      emit(assign, (yyvsp[-1].enode), newexpr_constbool(0), NULL, currQuad, yylineno); 

      (yyval.intVal) = nextquadlabel();
      test = (yyvsp[-2].intVal);
			emit(if_eq, newexpr_constnum(1), (yyvsp[-1].enode), newexpr_constbool('1'), currQuad, yylineno);
		}
#line 2731 "parse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 937 "parse.y" /* yacc.c:1646  */
    { 
      ++loopcounter;
			push(breakstacklist, 0);
      push(contstacklist, 0); 
		}
#line 2741 "parse.c" /* yacc.c:1646  */
    break;

  case 104:
#line 943 "parse.y" /* yacc.c:1646  */
    {
			--loopcounter; 
			patchlabel((yyvsp[-7].intVal), (yyvsp[-2].intVal)+1);
			patchlabel((yyvsp[-6].intVal), nextquadlabel());
			patchlabel((yyvsp[-2].intVal), test);
			patchlabel((yyvsp[0].intVal), (yyvsp[-6].intVal)+1);

			patchBreakContinue(breakstacklist, nextquadlabel());
      //pop(breakstacklist);
			patchBreakContinue(contstacklist, (yyvsp[-6].intVal)+1);
      //pop(contstacklist);
		}
#line 2758 "parse.c" /* yacc.c:1646  */
    break;

  case 105:
#line 959 "parse.y" /* yacc.c:1646  */
    {
			if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    }
#line 2768 "parse.c" /* yacc.c:1646  */
    break;

  case 106:
#line 965 "parse.y" /* yacc.c:1646  */
    { 
      emit(ret, (yyvsp[-1].enode), NULL, NULL, currQuad, yylineno); 
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);
    }
#line 2778 "parse.c" /* yacc.c:1646  */
    break;

  case 107:
#line 971 "parse.y" /* yacc.c:1646  */
    {
      if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    }
#line 2788 "parse.c" /* yacc.c:1646  */
    break;

  case 108:
#line 977 "parse.y" /* yacc.c:1646  */
    {
      emit(ret, NULL, NULL, NULL, currQuad, yylineno);
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);      
    }
#line 2798 "parse.c" /* yacc.c:1646  */
    break;


#line 2802 "parse.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 983 "parse.y" /* yacc.c:1906  */


void yyerror(char *s){
  error_flag = 1;
  fprintf(stdout, "\x1b[31mError: %s at line : %d\n \x1b[0m", s , yylineno);
}

int main(int argc, char **argv){
  FILE *f = fopen("IntermediateCode.txt", "w");

  funcStack = malloc(sizeof(UIntStack));
  initializeStack(funcStack);
  loopStack = malloc(sizeof(UIntStack));
  initializeStack(loopStack);
  breakstacklist = malloc(sizeof(UIntStack));
	initializeStack(breakstacklist);
	contstacklist = malloc(sizeof(UIntStack));
	initializeStack(contstacklist);
  table = createHashTable();
  if(table == NULL){
    printf("Failed to create hash table\n");
    return -1;
  }
  
  if(argc > 1){
    yyin = fopen(argv[1], "r");
    if(!yyin){
      fprintf(stdout, "Cannot read file: %s\n", argv[1]);
      return 1;
    }
  }
  else 
    yyin = stdin; 

	yyparse();
  
  PrintHashTable(table);
  if(argc > 1) {
     fclose(yyin);
  }

	if(!error_flag)
		printQuads(f);

  fclose(f);
  /*The queue is important*/
  free(loopStack->items);
  free(loopStack);
  free(funcStack->items);
  free(funcStack);
  free(breakstacklist->items);
  free(breakstacklist);
  free(contstacklist->items);
  free(contstacklist);
  freeHashTable(table);
  free_all(head);
  yylex_destroy();

	return 0;
}
