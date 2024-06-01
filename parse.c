/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parse.y"

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


#line 134 "parse.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parse.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INTEGER = 5,                    /* INTEGER  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_LOCAL = 17,                     /* LOCAL  */
  YYSYMBOL_TRUE = 18,                      /* TRUE  */
  YYSYMBOL_FALSE = 19,                     /* FALSE  */
  YYSYMBOL_NIL = 20,                       /* NIL  */
  YYSYMBOL_FUNCTION = 21,                  /* FUNCTION  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_ADD = 23,                       /* ADD  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MULTIPLICATION = 25,            /* MULTIPLICATION  */
  YYSYMBOL_DIVISION = 26,                  /* DIVISION  */
  YYSYMBOL_MODULO = 27,                    /* MODULO  */
  YYSYMBOL_EQUAL = 28,                     /* EQUAL  */
  YYSYMBOL_UNEQUAL = 29,                   /* UNEQUAL  */
  YYSYMBOL_INCREMENT = 30,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 31,                 /* DECREMENT  */
  YYSYMBOL_GREATER = 32,                   /* GREATER  */
  YYSYMBOL_LESS = 33,                      /* LESS  */
  YYSYMBOL_GREATEROREQUAL = 34,            /* GREATEROREQUAL  */
  YYSYMBOL_LESSOREQUAL = 35,               /* LESSOREQUAL  */
  YYSYMBOL_LEFT_CURLY_BRACE = 36,          /* LEFT_CURLY_BRACE  */
  YYSYMBOL_RIGHT_CURLY_BRACE = 37,         /* RIGHT_CURLY_BRACE  */
  YYSYMBOL_LEFT_SQUARE_BRACE = 38,         /* LEFT_SQUARE_BRACE  */
  YYSYMBOL_RIGHT_SQUARE_BRACE = 39,        /* RIGHT_SQUARE_BRACE  */
  YYSYMBOL_LEFT_PARENTHESIS = 40,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 41,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 43,                     /* COMMA  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_DOUBLE_COLON = 45,              /* DOUBLE_COLON  */
  YYSYMBOL_PERIOD = 46,                    /* PERIOD  */
  YYSYMBOL_DOUBLE_PERIOD = 47,             /* DOUBLE_PERIOD  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_list_of_stmts = 54,             /* list_of_stmts  */
  YYSYMBOL_expr = 55,                      /* expr  */
  YYSYMBOL_56_3 = 56,                      /* $@3  */
  YYSYMBOL_57_4 = 57,                      /* $@4  */
  YYSYMBOL_term = 58,                      /* term  */
  YYSYMBOL_assignexpr = 59,                /* assignexpr  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_primary = 62,                   /* primary  */
  YYSYMBOL_lvalue = 63,                    /* lvalue  */
  YYSYMBOL_member = 64,                    /* member  */
  YYSYMBOL_call = 65,                      /* call  */
  YYSYMBOL_callsufix = 66,                 /* callsufix  */
  YYSYMBOL_normallcall = 67,               /* normallcall  */
  YYSYMBOL_methodcall = 68,                /* methodcall  */
  YYSYMBOL_elist = 69,                     /* elist  */
  YYSYMBOL_objectdef = 70,                 /* objectdef  */
  YYSYMBOL_indexed = 71,                   /* indexed  */
  YYSYMBOL_indexedelem = 72,               /* indexedelem  */
  YYSYMBOL_block = 73,                     /* block  */
  YYSYMBOL_74_7 = 74,                      /* $@7  */
  YYSYMBOL_funcdef = 75,                   /* funcdef  */
  YYSYMBOL_76_8 = 76,                      /* @8  */
  YYSYMBOL_77_9 = 77,                      /* $@9  */
  YYSYMBOL_78_10 = 78,                     /* $@10  */
  YYSYMBOL_79_11 = 79,                     /* @11  */
  YYSYMBOL_80_12 = 80,                     /* $@12  */
  YYSYMBOL_81_13 = 81,                     /* $@13  */
  YYSYMBOL_const = 82,                     /* const  */
  YYSYMBOL_idlist = 83,                    /* idlist  */
  YYSYMBOL_N = 84,                         /* N  */
  YYSYMBOL_M = 85,                         /* M  */
  YYSYMBOL_ifprefix = 86,                  /* ifprefix  */
  YYSYMBOL_ifstmt = 87,                    /* ifstmt  */
  YYSYMBOL_elseprefix = 88,                /* elseprefix  */
  YYSYMBOL_whilestart = 89,                /* whilestart  */
  YYSYMBOL_whilecond = 90,                 /* whilecond  */
  YYSYMBOL_whilestmt = 91,                 /* whilestmt  */
  YYSYMBOL_forprefix = 92,                 /* forprefix  */
  YYSYMBOL_forstmt = 93,                   /* forstmt  */
  YYSYMBOL_94_14 = 94,                     /* $@14  */
  YYSYMBOL_returnstmt = 95,                /* returnstmt  */
  YYSYMBOL_96_15 = 96,                     /* $@15  */
  YYSYMBOL_97_16 = 97                      /* $@16  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
{
       0,   124,   124,   125,   129,   142,   143,   144,   145,   147,
     146,   156,   155,   163,   164,   165,   168,   169,   173,   174,
     183,   192,   201,   210,   219,   225,   231,   237,   243,   249,
     255,   255,   275,   275,   292,   296,   297,   303,   316,   334,
     353,   371,   389,   395,   399,   394,   443,   444,   445,   446,
     447,   451,   492,   520,   531,   535,   536,   543,   544,   548,
     549,   563,   572,   573,   577,   587,   596,   597,   598,   617,
     630,   645,   651,   667,   676,   675,   687,   706,   707,   686,
     736,   748,   749,   735,   766,   767,   768,   769,   770,   771,
     774,   775,   809,   845,   847,   850,   859,   863,   871,   879,
     886,   898,   912,   922,   921,   942,   941,   954,   953
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "STRING",
  "INTEGER", "REAL", "IF", "ELSE", "WHILE", "FOR", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NIL",
  "FUNCTION", "ASSIGN", "ADD", "MINUS", "MULTIPLICATION", "DIVISION",
  "MODULO", "EQUAL", "UNEQUAL", "INCREMENT", "DECREMENT", "GREATER",
  "LESS", "GREATEROREQUAL", "LESSOREQUAL", "LEFT_CURLY_BRACE",
  "RIGHT_CURLY_BRACE", "LEFT_SQUARE_BRACE", "RIGHT_SQUARE_BRACE",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON", "COMMA", "COLON",
  "DOUBLE_COLON", "PERIOD", "DOUBLE_PERIOD", "UMINUS", "$accept",
  "program", "stmt", "$@1", "$@2", "list_of_stmts", "expr", "$@3", "$@4",
  "term", "assignexpr", "$@5", "$@6", "primary", "lvalue", "member",
  "call", "callsufix", "normallcall", "methodcall", "elist", "objectdef",
  "indexed", "indexedelem", "block", "$@7", "funcdef", "@8", "$@9", "$@10",
  "@11", "$@12", "$@13", "const", "idlist", "N", "M", "ifprefix", "ifstmt",
  "elseprefix", "whilestart", "whilecond", "whilestmt", "forprefix",
  "forstmt", "$@14", "returnstmt", "$@15", "$@16", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-166)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-108)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

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
static const yytype_int8 yydefact[] =
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
static const yytype_uint8 yydefgoto[] =
{
       0,     1,   112,    55,    56,   113,    28,   121,   122,    29,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 4: /* stmt: expr SEMICOLON  */
#line 130 "parse.y"
    {
      resettemp(); 
      (yyval.enode)=NULL;
      if(emits == 1 ){ //dritsas
        backPatch((yyvsp[-1].enode)->falseList, nextquadlabel()+2);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(1), NULL, currQuad, yylineno);
        emit(jump, newexpr_constnum(0), NULL, NULL, nextquadlabel()+2, yylineno);
        emit(assign, (yyvsp[-1].enode), newexpr_constbool(0), NULL, currQuad, yylineno);
        make = true;
        emits = 0 ;
      }
    }
#line 1435 "parse.c"
    break;

  case 5: /* stmt: ifstmt  */
#line 142 "parse.y"
             {resettemp(); (yyval.enode)=NULL;}
#line 1441 "parse.c"
    break;

  case 6: /* stmt: whilestmt  */
#line 143 "parse.y"
                {resettemp(); (yyval.enode)=NULL;}
#line 1447 "parse.c"
    break;

  case 7: /* stmt: forstmt  */
#line 144 "parse.y"
              {resettemp(); (yyval.enode)=NULL;}
#line 1453 "parse.c"
    break;

  case 8: /* stmt: returnstmt  */
#line 145 "parse.y"
                 {resettemp(); (yyval.enode)=NULL;}
#line 1459 "parse.c"
    break;

  case 9: /* $@1: %empty  */
#line 147 "parse.y"
    {
      printf("%d  " , loopcounter);
      if(!loopcounter){yyerror("Use of 'break' while not in a loop");}
    }
#line 1468 "parse.c"
    break;

  case 10: /* stmt: BREAK $@1 SEMICOLON  */
#line 152 "parse.y"
    {
      emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);
    }
#line 1476 "parse.c"
    break;

  case 11: /* $@2: %empty  */
#line 156 "parse.y"
    {
      if(!loopcounter){yyerror("Use of 'continue' while not in a loop");}
    }
#line 1484 "parse.c"
    break;

  case 12: /* stmt: CONTINUE $@2 SEMICOLON  */
#line 160 "parse.y"
    {
      emit(jump, newexpr_constnum(0), (expr *)0, (expr *)0, currQuad, yylineno);
    }
#line 1492 "parse.c"
    break;

  case 13: /* stmt: block  */
#line 163 "parse.y"
            {resettemp(); (yyval.enode)=NULL;}
#line 1498 "parse.c"
    break;

  case 14: /* stmt: funcdef  */
#line 164 "parse.y"
              {resettemp(); (yyval.enode)=NULL;}
#line 1504 "parse.c"
    break;

  case 15: /* stmt: SEMICOLON  */
#line 165 "parse.y"
                {resettemp(); (yyval.enode)=NULL;}
#line 1510 "parse.c"
    break;

  case 16: /* list_of_stmts: stmt list_of_stmts  */
#line 168 "parse.y"
                                   {(yyval.enode) = (yyvsp[-1].enode);}
#line 1516 "parse.c"
    break;

  case 17: /* list_of_stmts: %empty  */
#line 169 "parse.y"
                  {(yyval.enode) = NULL;}
#line 1522 "parse.c"
    break;

  case 18: /* expr: assignexpr  */
#line 173 "parse.y"
                 {(yyval.enode)=(yyvsp[0].enode);}
#line 1528 "parse.c"
    break;

  case 19: /* expr: expr ADD expr  */
#line 175 "parse.y"
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(add, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1541 "parse.c"
    break;

  case 20: /* expr: expr MINUS expr  */
#line 184 "parse.y"
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table);
        emit(sub, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1554 "parse.c"
    break;

  case 21: /* expr: expr MULTIPLICATION expr  */
#line 193 "parse.y"
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(mul, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1567 "parse.c"
    break;

  case 22: /* expr: expr DIVISION expr  */
#line 202 "parse.y"
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(div_, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1580 "parse.c"
    break;

  case 23: /* expr: expr MODULO expr  */
#line 211 "parse.y"
    { 
      if(expr_checkType((yyvsp[-2].enode), (yyvsp[0].enode))){ 
        (yyval.enode) = newexpr(arithexpr_e); 
        (yyval.enode)->type = expr_retType((yyval.enode),(yyvsp[-2].enode),(yyvsp[0].enode));
        (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
        emit(mod, (yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), currQuad, yylineno);
      } 
    }
#line 1593 "parse.c"
    break;

  case 24: /* expr: expr EQUAL expr  */
#line 220 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_eq, yylineno);  
    }
#line 1603 "parse.c"
    break;

  case 25: /* expr: expr UNEQUAL expr  */
#line 226 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table);
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_noteq, yylineno); 
    }
#line 1613 "parse.c"
    break;

  case 26: /* expr: expr GREATER expr  */
#line 232 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_greater, yylineno);
    }
#line 1623 "parse.c"
    break;

  case 27: /* expr: expr LESS expr  */
#line 238 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_less, yylineno); 
    }
#line 1633 "parse.c"
    break;

  case 28: /* expr: expr GREATEROREQUAL expr  */
#line 244 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_greatereq, yylineno);
    }
#line 1643 "parse.c"
    break;

  case 29: /* expr: expr LESSOREQUAL expr  */
#line 250 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e); 
      (yyval.enode)->sym = returnTempName((yyvsp[-2].enode),(yyvsp[0].enode),table); 
      (yyval.enode) = relopEmit((yyval.enode), (yyvsp[-2].enode), (yyvsp[0].enode), if_lesseq, yylineno); 
    }
#line 1653 "parse.c"
    break;

  case 30: /* $@3: %empty  */
#line 255 "parse.y"
              {logicEmit((yyvsp[-1].enode),yylineno);}
#line 1659 "parse.c"
    break;

  case 31: /* expr: expr AND $@3 M expr  */
#line 256 "parse.y"
    {
      (yyval.enode) = newexpr(boolexpr_e);  
      (yyval.enode)->sym = returnTempName((yyvsp[-4].enode), (yyvsp[0].enode), table);

			logicEmit((yyvsp[0].enode), yylineno);

			Mlabel = (yyvsp[0].enode)->trueList->label;
			backPatch((yyvsp[-4].enode)->trueList, Mlabel);
			backPatch((yyvsp[-4].enode)->falseList, (yyvsp[-4].enode)->falseList->label+2);

      if(ORcounter == 1){ //dritsas
				backPatch(tempQuad, Mlabel+2);
        ORcounter = 0 ;
			}
														
			(yyval.enode)->trueList = (yyvsp[0].enode)->trueList;
			(yyval.enode)->falseList = mergelist((yyvsp[-4].enode)->falseList, (yyvsp[0].enode)->falseList);
      emits = 1 ;
		}
#line 1683 "parse.c"
    break;

  case 32: /* $@4: %empty  */
#line 275 "parse.y"
                         {logicEmit((yyvsp[-1].enode), yylineno);}
#line 1689 "parse.c"
    break;

  case 33: /* expr: expr OR $@4 M expr  */
#line 276 "parse.y"
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
      emits = 1 ;

		}
#line 1710 "parse.c"
    break;

  case 34: /* expr: term  */
#line 292 "parse.y"
                {(yyval.enode)=(yyvsp[0].enode);}
#line 1716 "parse.c"
    break;

  case 35: /* term: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 296 "parse.y"
                                              {(yyval.enode)=(yyvsp[-1].enode);}
#line 1722 "parse.c"
    break;

  case 36: /* term: MINUS expr  */
#line 298 "parse.y"
    {
      (yyval.enode)=newexpr(arithexpr_e); 
      (yyval.enode)->sym = newtemp(table,0); 
      emit(uminus, (yyval.enode), (yyvsp[0].enode), (expr *) 0, currQuad, yylineno);
    }
#line 1732 "parse.c"
    break;

  case 37: /* term: NOT expr  */
#line 304 "parse.y"
    {
      (yyval.enode)=newexpr(boolexpr_e); 
      (yyval.enode)->sym = newtemp(table,0); 
			if((yyvsp[0].enode)->type!=boolexpr_e){
				(yyvsp[0].enode)->trueList = createTrueList(nextquadlabel());
				(yyvsp[0].enode)->falseList= createFalseList(nextquadlabel());  
				emit(if_eq, (yyvsp[0].enode)->falseList, (yyvsp[0].enode), newexpr_constbool(1), currQuad, yylineno);
				emit(jump, (yyvsp[0].enode)->trueList, NULL, NULL, currQuad, yylineno);
			}
			(yyval.enode)->trueList = (yyvsp[0].enode)->falseList; 
			(yyval.enode)->falseList = (yyvsp[0].enode)->trueList; 
    }
#line 1749 "parse.c"
    break;

  case 38: /* term: INCREMENT lvalue  */
#line 317 "parse.y"
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot increment function value\n");
      }
      if((yyvsp[0].enode)->type == tableitem_e){
        (yyval.enode) = emit_iftableitem((yyvsp[0].enode),table,yylineno);
        emit(add, (yyval.enode), (yyval.enode), newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem,  (yyvsp[0].enode), (yyvsp[0].enode)->index,(yyval.enode), currQuad, yylineno);
      }
      else{
        emit(add, (yyvsp[0].enode), (yyvsp[0].enode), newexpr_constnum(1), currQuad, yylineno);
        (yyval.enode) = newexpr(arithexpr_e);
        (yyval.enode)->sym = newtemp(table,0);
        emit(assign, (yyval.enode), (yyvsp[0].enode), NULL, currQuad, yylineno);
      }
    }
#line 1771 "parse.c"
    break;

  case 39: /* term: lvalue INCREMENT  */
#line 335 "parse.y"
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
#line 1794 "parse.c"
    break;

  case 40: /* term: DECREMENT lvalue  */
#line 354 "parse.y"
    {
      SymbolTableEntry_t *t = H_Lookup(table, -1, temp_lvalue->content);
      if(t != NULL && t->type > 3){
        yyerror("Cannot decrement function value\n");
      }
      if((yyvsp[0].enode)->type == tableitem_e){
        (yyval.enode) = emit_iftableitem((yyvsp[0].enode),table,yylineno);
        emit(sub, (yyval.enode), (yyval.enode), newexpr_constnum(1), currQuad, yylineno);
        emit(tablesetelem,  (yyvsp[0].enode), (yyvsp[0].enode)->index,(yyval.enode), currQuad, yylineno);
      }
      else{
        emit(sub, (yyvsp[0].enode), (yyvsp[0].enode), newexpr_constnum(1), currQuad, yylineno);
        (yyval.enode) = newexpr(arithexpr_e);
        (yyval.enode)->sym = newtemp(table,0);
        emit(assign, (yyval.enode), (yyvsp[0].enode), NULL, currQuad, yylineno);
      }
    }
#line 1816 "parse.c"
    break;

  case 41: /* term: lvalue DECREMENT  */
#line 372 "parse.y"
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
        emit(tablesetelem,  (yyvsp[-1].enode), (yyvsp[-1].enode)->index,value, currQuad, yylineno);
      }
      else{
        emit(assign, (yyval.enode), (yyvsp[-1].enode), NULL, currQuad, yylineno);
        emit(sub, (yyvsp[-1].enode), (yyvsp[-1].enode), newexpr_constnum(1), currQuad, yylineno);
      }                  
    }
#line 1838 "parse.c"
    break;

  case 42: /* term: primary  */
#line 389 "parse.y"
             {(yyval.enode)=(yyvsp[0].enode);}
#line 1844 "parse.c"
    break;

  case 43: /* $@5: %empty  */
#line 395 "parse.y"
    {
      /*$1 = lvalue_expr(temp_test); */
    }
#line 1852 "parse.c"
    break;

  case 44: /* $@6: %empty  */
#line 399 "parse.y"
    {
      lassignl=true;
    }
#line 1860 "parse.c"
    break;

  case 45: /* assignexpr: lvalue $@5 ASSIGN $@6 expr  */
#line 403 "parse.y"
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
                printf("=");

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
#line 1902 "parse.c"
    break;

  case 46: /* primary: lvalue  */
#line 443 "parse.y"
            {(yyval.enode) = (yyvsp[0].enode);}
#line 1908 "parse.c"
    break;

  case 47: /* primary: call  */
#line 444 "parse.y"
           {}
#line 1914 "parse.c"
    break;

  case 48: /* primary: objectdef  */
#line 445 "parse.y"
                {}
#line 1920 "parse.c"
    break;

  case 49: /* primary: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS  */
#line 446 "parse.y"
                                                {(yyval.enode) = (yyvsp[-1].enode);}
#line 1926 "parse.c"
    break;

  case 50: /* primary: const  */
#line 447 "parse.y"
            {(yyval.enode) = (yyvsp[0].enode);}
#line 1932 "parse.c"
    break;

  case 51: /* lvalue: IDENTIFIER  */
#line 452 "parse.y"
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
#line 1977 "parse.c"
    break;

  case 52: /* lvalue: LOCAL IDENTIFIER  */
#line 493 "parse.y"
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
#line 2009 "parse.c"
    break;

  case 53: /* lvalue: DOUBLE_COLON IDENTIFIER  */
#line 521 "parse.y"
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
#line 2024 "parse.c"
    break;

  case 54: /* lvalue: member  */
#line 531 "parse.y"
                        {(yyval.enode) = (yyvsp[0].enode);}
#line 2030 "parse.c"
    break;

  case 55: /* member: lvalue PERIOD IDENTIFIER  */
#line 535 "parse.y"
                              {if((yyvsp[-2].enode) != NULL){(yyval.enode) = member_item((yyvsp[-2].enode), (yyvsp[0].strVal), table , yylineno);}}
#line 2036 "parse.c"
    break;

  case 56: /* member: lvalue LEFT_SQUARE_BRACE expr RIGHT_SQUARE_BRACE  */
#line 537 "parse.y"
    { 
      (yyvsp[-3].enode) = emit_iftableitem((yyvsp[-3].enode), table,yylineno); 
      (yyval.enode) = newexpr(tableitem_e); 
      (yyval.enode)->sym = (yyvsp[-3].enode)->sym; 
      (yyval.enode)->index = (yyvsp[-1].enode); 
    }
#line 2047 "parse.c"
    break;

  case 57: /* member: call PERIOD IDENTIFIER  */
#line 543 "parse.y"
                            {(yyval.enode) = NULL;}
#line 2053 "parse.c"
    break;

  case 58: /* member: call LEFT_SQUARE_BRACE expr RIGHT_SQUARE_BRACE  */
#line 544 "parse.y"
                                                    {(yyval.enode) = NULL;}
#line 2059 "parse.c"
    break;

  case 59: /* call: call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 548 "parse.y"
                                                   {(yyval.enode) = make_call((yyvsp[-3].enode), (yyvsp[-1].enode), table, yylineno);}
#line 2065 "parse.c"
    break;

  case 60: /* call: IDENTIFIER callsufix  */
#line 550 "parse.y"
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
#line 2083 "parse.c"
    break;

  case 61: /* call: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 564 "parse.y"
    {
			expr* func = newexpr(programfunc_e);
			func->sym = (yyvsp[-4].enode)->sym;
			(yyval.enode) = make_call(func, (yyvsp[-1].enode),table, yylineno);
		}
#line 2093 "parse.c"
    break;

  case 62: /* callsufix: normallcall  */
#line 572 "parse.y"
                 {(yyval.enode) = (yyvsp[0].enode);}
#line 2099 "parse.c"
    break;

  case 63: /* callsufix: methodcall  */
#line 573 "parse.y"
                {(yyval.enode) = (yyvsp[0].enode);}
#line 2105 "parse.c"
    break;

  case 64: /* normallcall: LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 578 "parse.y"
    {	
			(yyval.enode) = newexpr(nil_e);
			(yyval.enode)->next = (yyvsp[-1].enode);
			(yyval.enode)->strConst = NULL;
			(yyval.enode)->boolConst = false;
		}
#line 2116 "parse.c"
    break;

  case 65: /* methodcall: DOUBLE_PERIOD IDENTIFIER LEFT_PARENTHESIS elist RIGHT_PARENTHESIS  */
#line 588 "parse.y"
    {
			(yyval.enode) = newexpr(tableitem_e);
			(yyval.enode)->next = (yyvsp[-1].enode);
			(yyval.enode)->strConst = (yyvsp[-3].strVal);
			(yyval.enode)->boolConst = '1';
		}
#line 2127 "parse.c"
    break;

  case 66: /* elist: %empty  */
#line 596 "parse.y"
       {(yyval.enode) = NULL;}
#line 2133 "parse.c"
    break;

  case 67: /* elist: expr  */
#line 597 "parse.y"
           {(yyval.enode) = (yyvsp[0].enode);}
#line 2139 "parse.c"
    break;

  case 68: /* elist: elist COMMA expr  */
#line 599 "parse.y"
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
#line 2158 "parse.c"
    break;

  case 69: /* objectdef: LEFT_SQUARE_BRACE elist RIGHT_SQUARE_BRACE  */
#line 618 "parse.y"
    {
      int i = 0;
			expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while((yyvsp[-1].enode) != NULL){
        printf("elist");
				emit(tablesetelem,(yyvsp[-1].enode),node, newexpr_constnum(i++), currQuad, yylineno);
				(yyvsp[-1].enode) = (yyvsp[-1].enode)->next;
			}
			(yyval.enode) = node;
    }
#line 2175 "parse.c"
    break;

  case 70: /* objectdef: LEFT_SQUARE_BRACE indexed RIGHT_SQUARE_BRACE  */
#line 631 "parse.y"
    {
      expr *node = newexpr(newtable_e);
			node->sym = newtemp(table,0);
      printf("indexed");
			emit(tablecreate, node, NULL, NULL, currQuad, yylineno);
			while((yyvsp[-1].enode)!=NULL){
				emit(tablesetelem, (yyvsp[-1].enode),node, (yyvsp[-1].enode)->index, currQuad, yylineno);
				(yyvsp[-1].enode) = (yyvsp[-1].enode)->next;
			}
			(yyval.enode) = node;		
    }
#line 2191 "parse.c"
    break;

  case 71: /* indexed: indexedelem  */
#line 646 "parse.y"
    { 
      expr *node = (yyvsp[0].enode);
      node->next = NULL; 
      (yyval.enode) = node;
    }
#line 2201 "parse.c"
    break;

  case 72: /* indexed: indexed COMMA indexedelem  */
#line 652 "parse.y"
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
#line 2218 "parse.c"
    break;

  case 73: /* indexedelem: LEFT_CURLY_BRACE expr COLON expr RIGHT_CURLY_BRACE  */
#line 668 "parse.y"
    {
      (yyval.enode) = (yyvsp[-1].enode);
      (yyval.enode)->index = (yyvsp[-3].enode);
    }
#line 2227 "parse.c"
    break;

  case 74: /* $@7: %empty  */
#line 676 "parse.y"
    {
      enterScope();
    }
#line 2235 "parse.c"
    break;

  case 75: /* block: LEFT_CURLY_BRACE $@7 list_of_stmts RIGHT_CURLY_BRACE  */
#line 680 "parse.y"
    {
      exitScope(table);
    }
#line 2243 "parse.c"
    break;

  case 76: /* @8: %empty  */
#line 687 "parse.y"
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
#line 2267 "parse.c"
    break;

  case 77: /* $@9: %empty  */
#line 706 "parse.y"
                      {enterscopespace();}
#line 2273 "parse.c"
    break;

  case 78: /* $@10: %empty  */
#line 707 "parse.y"
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
#line 2294 "parse.c"
    break;

  case 79: /* funcdef: FUNCTION IDENTIFIER @8 LEFT_PARENTHESIS $@9 idlist RIGHT_PARENTHESIS $@10 block  */
#line 724 "parse.y"
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
#line 2310 "parse.c"
    break;

  case 80: /* @11: %empty  */
#line 736 "parse.y"
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
#line 2327 "parse.c"
    break;

  case 81: /* $@12: %empty  */
#line 748 "parse.y"
                      {enterscopespace();}
#line 2333 "parse.c"
    break;

  case 82: /* $@13: %empty  */
#line 749 "parse.y"
    {
      enterscopespace(); 
    }
#line 2341 "parse.c"
    break;

  case 83: /* funcdef: FUNCTION @11 LEFT_PARENTHESIS $@12 idlist RIGHT_PARENTHESIS $@13 block  */
#line 753 "parse.y"
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
#line 2356 "parse.c"
    break;

  case 84: /* const: INTEGER  */
#line 766 "parse.y"
              {(yyval.enode) = newexpr_constnum(yylval.intVal);}
#line 2362 "parse.c"
    break;

  case 85: /* const: REAL  */
#line 767 "parse.y"
                       {(yyval.enode) = newexpr_constnum(yylval.floatVal);}
#line 2368 "parse.c"
    break;

  case 86: /* const: STRING  */
#line 768 "parse.y"
                         {(yyval.enode) = newexpr_conststring(yylval.strVal);}
#line 2374 "parse.c"
    break;

  case 87: /* const: NIL  */
#line 769 "parse.y"
                      {(yyval.enode) = newexpr(nil_e);}
#line 2380 "parse.c"
    break;

  case 88: /* const: TRUE  */
#line 770 "parse.y"
                       {(yyval.enode) = newexpr_constbool(1);}
#line 2386 "parse.c"
    break;

  case 89: /* const: FALSE  */
#line 771 "parse.y"
                        {(yyval.enode) = newexpr_constbool(0);}
#line 2392 "parse.c"
    break;

  case 91: /* idlist: IDENTIFIER  */
#line 776 "parse.y"
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
#line 2430 "parse.c"
    break;

  case 92: /* idlist: idlist COMMA IDENTIFIER  */
#line 810 "parse.y"
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
#line 2468 "parse.c"
    break;

  case 93: /* N: %empty  */
#line 845 "parse.y"
        {(yyval.intVal) = nextquadlabel();emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);}
#line 2474 "parse.c"
    break;

  case 94: /* M: %empty  */
#line 847 "parse.y"
        {(yyval.intVal) = nextquadlabel();}
#line 2480 "parse.c"
    break;

  case 95: /* ifprefix: IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 851 "parse.y"
    {
      emit(if_eq, (yyvsp[-1].enode), newexpr_constbool(1), NULL, nextquad() + 2, yylineno);
      (yyval.intVal) = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);
    }
#line 2490 "parse.c"
    break;

  case 96: /* ifstmt: ifprefix stmt  */
#line 860 "parse.y"
    {
      patchlabel((yyvsp[-1].intVal), nextquad());
    }
#line 2498 "parse.c"
    break;

  case 97: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 864 "parse.y"
    {
      patchlabel((yyvsp[-3].intVal), (yyvsp[-1].intVal) + 1);
      patchlabel((yyvsp[-1].intVal), nextquad());
    }
#line 2507 "parse.c"
    break;

  case 98: /* elseprefix: ELSE  */
#line 872 "parse.y"
    {
      (yyval.intVal) = nextquadlabel();
      emit(jump, newexpr_constnum(0), NULL, NULL, 0, yylineno);
    }
#line 2516 "parse.c"
    break;

  case 99: /* whilestart: WHILE  */
#line 880 "parse.y"
    {
      (yyval.intVal) = nextquadlabel();
    }
#line 2524 "parse.c"
    break;

  case 100: /* whilecond: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 887 "parse.y"
    {
      ++loopcounter;	
			push(breakstacklist, 0); 
      push(contstacklist, 0); 
			emit(if_eq, newexpr_constnum(nextquadlabel()+2), (yyvsp[-1].enode), newexpr_constbool('1'), currQuad, yylineno); 
		  (yyval.intVal) = nextquadlabel();   
			emit(jump, newexpr_constnum(0), NULL, NULL, currQuad, yylineno);
    }
#line 2537 "parse.c"
    break;

  case 101: /* whilestmt: whilestart whilecond stmt  */
#line 899 "parse.y"
    {
      --loopcounter;	
			emit(jump, newexpr_constnum((yyvsp[-2].intVal)), NULL, NULL, currQuad, yylineno);   
			patchlabel((yyvsp[-1].intVal), nextquadlabel());   

			patchBreakContinue(breakstacklist, nextquadlabel());
			pop(breakstacklist);
			patchBreakContinue(contstacklist, (yyvsp[-2].intVal));
			pop(contstacklist);
    }
#line 2552 "parse.c"
    break;

  case 102: /* forprefix: FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON  */
#line 913 "parse.y"
    {
      (yyval.intVal) = nextquadlabel();
      test = (yyvsp[-2].intVal);
			emit(if_eq, newexpr_constnum(1), (yyvsp[-1].enode), newexpr_constbool('1'), currQuad, yylineno);
		}
#line 2562 "parse.c"
    break;

  case 103: /* $@14: %empty  */
#line 922 "parse.y"
    { 
      ++loopcounter;
			push(breakstacklist, 0);
      push(contstacklist, 0); 
		}
#line 2572 "parse.c"
    break;

  case 104: /* forstmt: forprefix N elist RIGHT_PARENTHESIS $@14 N stmt N  */
#line 928 "parse.y"
    {
			--loopcounter; 
			patchlabel((yyvsp[-7].intVal), (yyvsp[-2].intVal)+1);
			patchlabel((yyvsp[-6].intVal), nextquadlabel());
			patchlabel((yyvsp[-2].intVal), test);
			patchlabel((yyvsp[0].intVal), (yyvsp[-6].intVal)+1);

			patchBreakContinue(breakstacklist, nextquadlabel());
			patchBreakContinue(contstacklist, (yyvsp[-6].intVal)+1);
		}
#line 2587 "parse.c"
    break;

  case 105: /* $@15: %empty  */
#line 942 "parse.y"
    {
			if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    }
#line 2597 "parse.c"
    break;

  case 106: /* returnstmt: RETURN $@15 expr SEMICOLON  */
#line 948 "parse.y"
    { 
      emit(ret, (yyvsp[-1].enode), NULL, NULL, currQuad, yylineno); 
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);
    }
#line 2607 "parse.c"
    break;

  case 107: /* $@16: %empty  */
#line 954 "parse.y"
    {
      if(!functionDepth){
        yyerror("expected identifier or '(' before 'return'");
      }
    }
#line 2617 "parse.c"
    break;

  case 108: /* returnstmt: RETURN $@16 SEMICOLON  */
#line 960 "parse.y"
    {
      emit(ret, NULL, NULL, NULL, currQuad, yylineno);
      retLabel = currQuad ; 
      emit(jump , newexpr_constnum(0) , NULL  , NULL , currQuad ,yylineno);      
    }
#line 2627 "parse.c"
    break;


#line 2631 "parse.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 966 "parse.y"


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
		if(!(yyin = fopen(argv[1], "r"))){
			fprintf(stdout, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	else
		yyin = stdin;
  }

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
