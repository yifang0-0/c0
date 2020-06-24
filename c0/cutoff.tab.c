/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "cutoff.y"

/*
#ifndef _UNISTD_H
#define _UNISTD_H 

#include <io.h> 
#include <process.h> 
#endif   */
# include <stdio.h>
# include "c.h"







/* Line 371 of yacc.c  */
#line 86 "cutoff.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "cutoff.tab.h".  */
#ifndef YY_YY_CUTOFF_TAB_H_INCLUDED
# define YY_YY_CUTOFF_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTNUM = 258,
     APPROXNUM = 259,
     STRINGNUM = 260,
     TYPE = 261,
     STRUCT = 262,
     TYPEDEF = 263,
     BREAK = 264,
     CONSTLEX = 265,
     UNION = 266,
     RETURN = 267,
     IF = 268,
     ELSE = 269,
     FOR = 270,
     WHILE = 271,
     NAME = 272,
     SPACE = 273,
     SEMI = 274,
     COMMA = 275,
     ASSIGN = 276,
     RELOP = 277,
     ADDLEX = 278,
     MODLEX = 279,
     SIZEOFLEX = 280,
     UNSIGNEDLEX = 281,
     SUBLEX = 282,
     STARLEX = 283,
     DIVLEX = 284,
     ANDLEX = 285,
     ORLEX = 286,
     BANDLEX = 287,
     BORLEX = 288,
     BXORLEX = 289,
     NOTLEX = 290,
     LP = 291,
     RP = 292,
     LB = 293,
     RB = 294,
     LSB = 295,
     RSB = 296,
     PS = 297,
     DS = 298,
     AERROR = 299,
     TRUE = 300,
     FALSE = 301,
     VOIDLEX = 302,
     CONTINUE = 303,
     DO = 304,
     ADDRESS = 305,
     SELFSUB = 306,
     SWITCH = 307,
     EOL = 308,
     FALSELEX = 309,
     TRUELEX = 310,
     DOT = 311
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 19 "cutoff.y"

struct ast* a;
double d;


/* Line 387 of yacc.c  */
#line 191 "cutoff.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_CUTOFF_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 219 "cutoff.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  158

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    10,    13,    18,    22,
      27,    33,    38,    40,    43,    45,    47,    53,    56,    62,
      65,    69,    72,    73,    76,    78,    80,    83,    87,    93,
     101,   107,   115,   121,   124,   127,   130,   132,   136,   141,
     145,   148,   152,   154,   157,   161,   165,   167,   169,   173,
     175,   180,   184,   187,   190,   193,   196,   200,   204,   208,
     212,   216,   220,   224,   228,   232,   236,   240,   244,   248,
     253,   257,   262,   264,   266,   268,   270,   274
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    -1,    59,    -1,    60,    59,    -1,    -1,
      61,    19,    -1,    61,    17,    69,    64,    -1,    61,    72,
      19,    -1,    61,    17,    69,    19,    -1,    10,    61,    17,
      69,    64,    -1,    10,    61,    72,    19,    -1,     6,    -1,
      26,     6,    -1,    62,    -1,    63,    -1,     7,    17,    40,
      67,    41,    -1,     7,    17,    -1,    11,    17,    40,    67,
      41,    -1,    11,    17,    -1,    38,    65,    39,    -1,    66,
      65,    -1,    -1,    75,    19,    -1,    64,    -1,    67,    -1,
      12,    19,    -1,    12,    75,    19,    -1,    13,    36,    75,
      37,    66,    -1,    13,    36,    75,    37,    66,    14,    66,
      -1,    16,    36,    75,    37,    66,    -1,    49,    66,    16,
      36,    75,    37,    19,    -1,    52,    36,    17,    37,    66,
      -1,     9,    19,    -1,    48,    19,    -1,    68,    67,    -1,
      68,    -1,    61,    72,    19,    -1,    10,    61,    72,    19,
      -1,    36,    70,    37,    -1,    36,    37,    -1,    71,    20,
      70,    -1,    71,    -1,    61,    74,    -1,    10,    61,    74,
      -1,    73,    20,    72,    -1,    73,    -1,    74,    -1,    74,
      21,    75,    -1,    17,    -1,    74,    40,     3,    41,    -1,
      74,    40,    41,    -1,    28,    75,    -1,    27,    75,    -1,
      35,    75,    -1,    25,    75,    -1,    75,    28,    75,    -1,
      75,    29,    75,    -1,    75,    24,    75,    -1,    75,    23,
      75,    -1,    75,    27,    75,    -1,    75,    22,    75,    -1,
      75,    50,    75,    -1,    75,    34,    75,    -1,    75,    33,
      75,    -1,    75,    30,    75,    -1,    75,    31,    75,    -1,
      75,    21,    75,    -1,    36,    75,    37,    -1,    17,    36,
      76,    37,    -1,    17,    36,    37,    -1,    17,    40,     3,
      41,    -1,    17,    -1,     3,    -1,     4,    -1,     5,    -1,
      75,    20,    76,    -1,    75,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    60,    64,    65,    68,    69,    70,    71,
      72,    73,    80,    81,    82,    83,    85,    86,    88,    89,
      92,    94,    95,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   114,   115,   118,   119,   121,
     122,   125,   126,   128,   129,   134,   135,   137,   138,   140,
     141,   142,   148,   150,   151,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   176,   177
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTNUM", "APPROXNUM", "STRINGNUM",
  "TYPE", "STRUCT", "TYPEDEF", "BREAK", "CONSTLEX", "UNION", "RETURN",
  "IF", "ELSE", "FOR", "WHILE", "NAME", "SPACE", "SEMI", "COMMA", "ASSIGN",
  "RELOP", "ADDLEX", "MODLEX", "SIZEOFLEX", "UNSIGNEDLEX", "SUBLEX",
  "STARLEX", "DIVLEX", "ANDLEX", "ORLEX", "BANDLEX", "BORLEX", "BXORLEX",
  "NOTLEX", "LP", "RP", "LB", "RB", "LSB", "RSB", "PS", "DS", "AERROR",
  "TRUE", "FALSE", "VOIDLEX", "CONTINUE", "DO", "ADDRESS", "SELFSUB",
  "SWITCH", "EOL", "FALSELEX", "TRUELEX", "DOT", "$accept", "Program",
  "ExtDefList", "ExtDef", "Specifire", "StructSpecifire", "UnionSpecifire",
  "Compst", "STATELIST", "STATE", "DefList", "Def", "FunDecList",
  "fDecList", "fDecVar", "VarList", "DecVar", "Var", "Exp", "Args", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    58,    59,    59,    60,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     0,     2,     4,     3,     4,
       5,     4,     1,     2,     1,     1,     5,     2,     5,     2,
       3,     2,     0,     2,     1,     1,     2,     3,     5,     7,
       5,     7,     5,     2,     2,     2,     1,     3,     4,     3,
       2,     3,     1,     2,     3,     3,     1,     1,     3,     1,
       4,     3,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     4,     1,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    12,     0,     0,     0,     0,     0,     3,     5,     0,
      14,    15,    17,     0,    19,    13,     1,     4,    49,     6,
       0,    46,    47,     0,    49,     0,     0,     0,     0,     8,
       0,     0,     0,     0,     0,     0,    36,     0,    11,     0,
       0,    40,     0,     0,    42,     9,    22,     7,    49,    45,
      73,    74,    75,    72,     0,     0,     0,     0,     0,    48,
       0,    51,     0,     0,    16,    35,    10,    18,     0,    43,
      39,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,    22,    25,     0,     0,     0,    55,    53,    52,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,    37,    44,    41,    33,    26,
       0,     0,     0,    34,     0,     0,    20,    21,    23,    70,
      77,     0,     0,    68,    67,    61,    59,    58,    60,    56,
      57,    65,    66,    64,    63,    62,    38,    27,     0,     0,
       0,     0,     0,    69,    71,     0,     0,     0,     0,    76,
      28,    30,     0,    32,     0,     0,    29,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,    34,    10,    11,    79,    80,    81,
      82,    36,    28,    43,    44,    20,    21,    22,    83,   121
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int16 yypact[] =
{
      95,   -73,   -11,   143,    27,    43,    18,   -73,    95,    20,
     -73,   -73,    19,    35,    37,   -73,   -73,   -73,    21,   -73,
      39,    36,   -18,   118,    21,    56,   118,     6,    -8,   -73,
      62,   153,    -1,   143,    62,    42,   118,    46,   -73,    49,
     143,   -73,    62,    59,    77,   -73,    82,   -73,   -73,   -73,
     -73,   -73,   -73,    15,   153,   153,   153,   153,   153,   283,
      63,   -73,    62,    81,   -73,   -73,   -73,   -73,    62,    72,
     -73,   351,    84,   136,    83,    86,   104,    82,    90,   -73,
      93,    82,   -73,   163,   110,   130,   283,   -14,    -3,    -3,
     211,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   -73,   117,   -73,    72,   -73,   -73,   -73,
     181,   153,   153,   -73,   126,   131,   -73,   -73,   -73,   -73,
     196,   106,   111,   -73,   283,   283,   -14,   283,   -14,    -3,
      -3,   313,   326,   296,   283,   283,   -73,   -73,   229,   247,
     115,   122,   153,   -73,   -73,    82,    82,   153,    82,   -73,
     146,   -73,   265,   -73,    82,   147,   -73,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   154,   -73,     1,   -73,   -73,    17,    87,   -72,
      12,   -73,   141,    96,   -73,    16,   -73,   -35,   -31,    31
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      59,     9,    60,    31,    13,   114,    12,    69,    92,     9,
      94,    45,     1,     2,    96,    97,    40,     4,    16,    92,
     101,    94,    32,    86,    87,    88,    89,    90,    42,    25,
      46,   101,     5,   106,    62,    35,   102,    18,    39,    19,
      61,    68,   110,    41,    14,    47,    49,   102,    65,    15,
      63,    84,    24,   120,    66,    85,    30,    27,    29,    23,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,    42,   150,   151,    38,   153,    26,   104,    48,
     138,   139,   156,    64,    46,    50,    51,    52,     1,     2,
      67,    72,    33,     4,    73,    74,    70,    71,    75,    53,
     105,     1,     2,   108,   103,     3,     4,    54,     5,    55,
      56,   120,    32,    50,    51,    52,   152,    57,    58,   111,
      46,     5,   112,   113,     1,     2,   115,    53,    33,     4,
      76,    77,   116,   122,    78,    54,   136,    55,    56,    50,
      51,    52,   140,   143,     5,    57,    58,   119,   141,     1,
       2,   147,   144,    53,     4,   109,    50,    51,    52,   148,
     154,    54,    17,    55,    56,    37,   157,   107,   117,     5,
      53,    57,    58,   149,     0,     0,     0,     0,    54,     0,
      55,    56,   118,     0,    91,    92,    93,    94,    57,    58,
      95,    96,    97,    98,    99,     0,   100,   101,     0,     0,
     137,     0,    91,    92,    93,    94,     0,     0,    95,    96,
      97,    98,    99,   102,   100,   101,   142,    91,    92,    93,
      94,     0,     0,    95,    96,    97,    98,    99,     0,   100,
     101,   102,    91,    92,    93,    94,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,   102,     0,   123,     0,
      91,    92,    93,    94,     0,     0,    95,    96,    97,    98,
      99,   102,   100,   101,     0,     0,   145,     0,    91,    92,
      93,    94,     0,     0,    95,    96,    97,    98,    99,   102,
     100,   101,     0,     0,   146,     0,    91,    92,    93,    94,
       0,     0,    95,    96,    97,    98,    99,   102,   100,   101,
       0,     0,   155,     0,    91,    92,    93,    94,     0,     0,
      95,    96,    97,    98,    99,   102,   100,   101,    92,    93,
      94,     0,     0,    95,    96,    97,    98,    99,     0,     0,
     101,     0,     0,   102,     0,    92,    93,    94,     0,     0,
      95,    96,    97,     0,    99,     0,   102,   101,    92,    93,
      94,     0,     0,    95,    96,    97,     0,     1,     2,     0,
     101,    40,     4,   102,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     5
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      31,     0,     3,    21,     3,    77,    17,    42,    22,     8,
      24,    19,     6,     7,    28,    29,    10,    11,     0,    22,
      34,    24,    40,    54,    55,    56,    57,    58,    27,    13,
      38,    34,    26,    68,    33,    23,    50,    17,    26,    19,
      41,    40,    73,    37,    17,    28,    30,    50,    36,     6,
      34,    36,    17,    84,    37,    40,    20,    36,    19,    40,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    71,   145,   146,    19,   148,    40,    62,    17,
     111,   112,   154,    41,    38,     3,     4,     5,     6,     7,
      41,     9,    10,    11,    12,    13,    37,    20,    16,    17,
      19,     6,     7,    19,    41,    10,    11,    25,    26,    27,
      28,   142,    40,     3,     4,     5,   147,    35,    36,    36,
      38,    26,    36,    19,     6,     7,    36,    17,    10,    11,
      48,    49,    39,     3,    52,    25,    19,    27,    28,     3,
       4,     5,    16,    37,    26,    35,    36,    37,    17,     6,
       7,    36,    41,    17,    11,    19,     3,     4,     5,    37,
      14,    25,     8,    27,    28,    24,    19,    71,    81,    26,
      17,    35,    36,   142,    -1,    -1,    -1,    -1,    25,    -1,
      27,    28,    19,    -1,    21,    22,    23,    24,    35,    36,
      27,    28,    29,    30,    31,    -1,    33,    34,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    27,    28,
      29,    30,    31,    50,    33,    34,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    50,    21,    22,    23,    24,    -1,    -1,    27,    28,
      29,    30,    31,    -1,    33,    34,    50,    -1,    37,    -1,
      21,    22,    23,    24,    -1,    -1,    27,    28,    29,    30,
      31,    50,    33,    34,    -1,    -1,    37,    -1,    21,    22,
      23,    24,    -1,    -1,    27,    28,    29,    30,    31,    50,
      33,    34,    -1,    -1,    37,    -1,    21,    22,    23,    24,
      -1,    -1,    27,    28,    29,    30,    31,    50,    33,    34,
      -1,    -1,    37,    -1,    21,    22,    23,    24,    -1,    -1,
      27,    28,    29,    30,    31,    50,    33,    34,    22,    23,
      24,    -1,    -1,    27,    28,    29,    30,    31,    -1,    -1,
      34,    -1,    -1,    50,    -1,    22,    23,    24,    -1,    -1,
      27,    28,    29,    -1,    31,    -1,    50,    34,    22,    23,
      24,    -1,    -1,    27,    28,    29,    -1,     6,     7,    -1,
      34,    10,    11,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    26
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    10,    11,    26,    58,    59,    60,    61,
      62,    63,    17,    61,    17,     6,     0,    59,    17,    19,
      72,    73,    74,    40,    17,    72,    40,    36,    69,    19,
      20,    21,    40,    10,    61,    67,    68,    69,    19,    67,
      10,    37,    61,    70,    71,    19,    38,    64,    17,    72,
       3,     4,     5,    17,    25,    27,    28,    35,    36,    75,
       3,    41,    61,    72,    41,    67,    64,    41,    61,    74,
      37,    20,     9,    12,    13,    16,    48,    49,    52,    64,
      65,    66,    67,    75,    36,    40,    75,    75,    75,    75,
      75,    21,    22,    23,    24,    27,    28,    29,    30,    31,
      33,    34,    50,    41,    72,    19,    74,    70,    19,    19,
      75,    36,    36,    19,    66,    36,    39,    65,    19,    37,
      75,    76,     3,    37,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    19,    19,    75,    75,
      16,    17,    20,    37,    41,    37,    37,    36,    37,    76,
      66,    66,    75,    66,    14,    37,    66,    19
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 59 "cutoff.y"
    {printf("no input");treefree((yyval.a));}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 60 "cutoff.y"
    {printf("syntax tree:\n");eval_print((yyval.a),0);printf("syntax tree!\n\n");}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 64 "cutoff.y"
    {(yyval.a)=createListL("ExtDefList",(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 65 "cutoff.y"
    {(yyval.a)=createListL("ExtDefList",NULL,NULL);}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 68 "cutoff.y"
    {(yyval.a)=newast("ExtDef",2,(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 69 "cutoff.y"
    {(yyval.a)=funcDef((yyvsp[(1) - (4)].a),(yyvsp[(2) - (4)].a),(yyvsp[(3) - (4)].a),0,(yyvsp[(4) - (4)].a)) ; exitscope( );identificaionOffset=0;}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 70 "cutoff.y"
    {(yyval.a)=varDec( (yyvsp[(1) - (3)].a),(yyvsp[(2) - (3)].a), 0 );identificaionOffset=0;}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 71 "cutoff.y"
    {(yyval.a)=funcDef((yyvsp[(1) - (4)].a),(yyvsp[(2) - (4)].a),(yyvsp[(3) - (4)].a),0,NULL);identificaionOffset=0;}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 72 "cutoff.y"
    {(yyval.a)=funcDef((yyvsp[(1) - (5)].a),(yyvsp[(2) - (5)].a),(yyvsp[(3) - (5)].a),1,(yyvsp[(4) - (5)].a)); exitscope( );identificaionOffset=0;}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 73 "cutoff.y"
    {(yyval.a)=varDec( (yyvsp[(1) - (4)].a), (yyvsp[(2) - (4)].a), 1 );identificaionOffset=0;}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 80 "cutoff.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 81 "cutoff.y"
    {(yyval.a)=changeToUnsigned((yyvsp[(1) - (2)].a));}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 82 "cutoff.y"
    {(yyval.a)=newast("Specifire",1,(yyvsp[(1) - (1)].a));}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 83 "cutoff.y"
    {(yyval.a)=newast("Specifire",1,(yyvsp[(1) - (1)].a));}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 85 "cutoff.y"
    {(yyval.a)=newast("StructSpecifire",5,(yyvsp[(1) - (5)].a),(yyvsp[(2) - (5)].a),(yyvsp[(3) - (5)].a),(yyvsp[(4) - (5)].a),(yyvsp[(5) - (5)].a));}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 86 "cutoff.y"
    {(yyval.a)=newast("StructSpecifire",2,(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 88 "cutoff.y"
    {(yyval.a)=newast("UnionSpecifire",5,(yyvsp[(1) - (5)].a),(yyvsp[(2) - (5)].a),(yyvsp[(3) - (5)].a),(yyvsp[(4) - (5)].a),(yyvsp[(5) - (5)].a));}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 89 "cutoff.y"
    {(yyval.a)=newast("UnionSpecifire",2,(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 92 "cutoff.y"
    {(yyval.a)=(yyvsp[(2) - (3)].a); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 94 "cutoff.y"
    {(yyval.a)=createListL("STATELIST",(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 95 "cutoff.y"
    {(yyval.a)=createListL("STATELIST",NULL,NULL);}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 98 "cutoff.y"
    {(yyval.a)=(yyvsp[(1) - (2)].a);temp=0;}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 99 "cutoff.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a); exitscope( );}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 100 "cutoff.y"
    {(yyval.a)=createListL("STATE",(yyvsp[(1) - (1)].a),NULL);}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 101 "cutoff.y"
    {(yyval.a)=Return((yyvsp[(1) - (2)].a),NULL);}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 102 "cutoff.y"
    {(yyval.a)=Return((yyvsp[(1) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 103 "cutoff.y"
    {(yyval.a)=ifStatement((yyvsp[(5) - (5)].a),(yyvsp[(3) - (5)].a),NULL);}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 104 "cutoff.y"
    {(yyval.a)=ifStatement((yyvsp[(5) - (7)].a),(yyvsp[(3) - (7)].a),(yyvsp[(7) - (7)].a));}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 114 "cutoff.y"
    {(yyval.a)=createList("DefList",(yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 115 "cutoff.y"
    {(yyval.a)=createList( "DefList",(yyvsp[(1) - (1)].a),NULL);}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 118 "cutoff.y"
    {(yyval.a)=varDec( (yyvsp[(1) - (3)].a), (yyvsp[(2) - (3)].a), 0 );}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 119 "cutoff.y"
    {(yyval.a)=varDec( (yyvsp[(2) - (4)].a), (yyvsp[(3) - (4)].a), 1 );}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 121 "cutoff.y"
    {(yyval.a)=(yyvsp[(2) - (3)].a);}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 122 "cutoff.y"
    {(yyval.a)=NULL;}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 125 "cutoff.y"
    {(yyval.a)=createList("funcDecList",(yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a));}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 126 "cutoff.y"
    {(yyval.a)=createList( "funcDec", (yyvsp[(1) - (1)].a),NULL);}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 128 "cutoff.y"
    {(yyval.a)=funcVarDec( (yyvsp[(2) - (2)].a),(yyvsp[(1) - (2)].a),0 ) ;}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 129 "cutoff.y"
    {(yyval.a)=funcVarDec( (yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a),1 );}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 134 "cutoff.y"
    {(yyval.a)=createList("varList", (yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a) );}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 135 "cutoff.y"
    {(yyval.a)=createListL( "varList", (yyvsp[(1) - (1)].a),NULL);}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 137 "cutoff.y"
    {(yyval.a)=createListL( "Var", (yyvsp[(1) - (1)].a),NULL);;}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 138 "cutoff.y"
    {(yyval.a)=exprOPDouble( (yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a), (yyvsp[(2) - (3)].a) );}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 140 "cutoff.y"
    {(yyval.a)=(yyvsp[(1) - (1)].a);}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 141 "cutoff.y"
    {(yyval.a)=createList( "Array", (yyvsp[(1) - (4)].a),(yyvsp[(3) - (4)].a));}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 142 "cutoff.y"
    {(yyval.a)=createList( "Array",(yyvsp[(1) - (3)].a),NULL);}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 148 "cutoff.y"
    {(yyval.a)=exprOPSingle((yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 150 "cutoff.y"
    {(yyval.a)=exprOPSingle((yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 151 "cutoff.y"
    {(yyval.a)=exprOPSingle((yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 154 "cutoff.y"
    {(yyval.a)=exprOPSingle((yyvsp[(1) - (2)].a),(yyvsp[(2) - (2)].a));}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 155 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 156 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 157 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 158 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 159 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 160 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 161 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 162 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 163 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 164 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 165 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 166 "cutoff.y"
    {(yyval.a)=exprOPDouble((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a),(yyvsp[(2) - (3)].a));}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 167 "cutoff.y"
    {(yyval.a)=(yyvsp[(2) - (3)].a);}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 168 "cutoff.y"
    {(yyval.a)=getFuncName((yyvsp[(1) - (4)].a),(yyvsp[(3) - (4)].a));}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 169 "cutoff.y"
    {(yyval.a)=getFuncName((yyvsp[(1) - (3)].a),NULL);}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 170 "cutoff.y"
    {(yyval.a)=getArrayName((yyvsp[(1) - (4)].a),(yyvsp[(3) - (4)].a));}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 171 "cutoff.y"
    {(yyval.a)=getVarName((yyvsp[(1) - (1)].a));}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 172 "cutoff.y"
    {(yyval.a)=setConstants((yyvsp[(1) - (1)].a));}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 173 "cutoff.y"
    {(yyval.a)=setConstants((yyvsp[(1) - (1)].a));}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 174 "cutoff.y"
    {(yyval.a)=setConstants((yyvsp[(1) - (1)].a));}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 176 "cutoff.y"
    {(yyval.a)=setArgs((yyvsp[(1) - (3)].a),(yyvsp[(3) - (3)].a)); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 177 "cutoff.y"
    {(yyval.a)=setArgs((yyvsp[(1) - (1)].a),NULL);}
    break;


/* Line 1792 of yacc.c  */
#line 2016 "cutoff.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 179 "cutoff.y"

 
int main(int ac,char **av)
{
	
	Initial( ) ;
	//yyrestart("")
    yyparse();
}
 
