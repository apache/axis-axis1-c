/* A Bison parser, made from cpp.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	KW_asm	257
# define	KW_do	258
# define	KW_inline	259
# define	KW_short	260
# define	KW_typeid	261
# define	KW_auto	262
# define	KW_double	263
# define	KW_int	264
# define	KW_signed	265
# define	KW_typename	266
# define	KW_bool	267
# define	KW_dynamic_cast	268
# define	KW_long	269
# define	KW_sizeof	270
# define	KW_union	271
# define	KW_break	272
# define	KW_else	273
# define	KW_mutable	274
# define	KW_static	275
# define	KW_unsigned	276
# define	KW_case	277
# define	KW_enum	278
# define	KW_namespace	279
# define	KW_static_cast	280
# define	KW_using	281
# define	KW_catch	282
# define	KW_explicit	283
# define	KW_new	284
# define	KW_struct	285
# define	KW_virtual	286
# define	KW_char	287
# define	KW_extern	288
# define	KW_operator	289
# define	KW_switch	290
# define	KW_void	291
# define	KW_class	292
# define	KW_false	293
# define	KW_private	294
# define	KW_template	295
# define	KW_volatile	296
# define	KW_const	297
# define	KW_float	298
# define	KW_protected	299
# define	KW_this	300
# define	KW_wchar_t	301
# define	KW_const_cast	302
# define	KW_for	303
# define	KW_public	304
# define	KW_throw	305
# define	KW_while	306
# define	KW_continue	307
# define	KW_friend	308
# define	KW_register	309
# define	KW_true	310
# define	KW_default	311
# define	KW_goto	312
# define	KW_reinterpret_cast	313
# define	KW_try	314
# define	KW_delete	315
# define	KW_if	316
# define	KW_return	317
# define	KW_typedef	318
# define	KW_export	319
# define	KW_string	320
# define	KW_unsigned_char	321
# define	KW_unsigned_short	322
# define	KW_unsigned_long	323
# define	KW_long_double	324
# define	INTEGER_LITERAL	325
# define	CHARACTER_LITERAL	326
# define	FLOATING_LITERAL	327
# define	STRING_LITERAL	328
# define	LEFTPAREN	329
# define	RIGHTPAREN	330
# define	LEFTBRACK	331
# define	RIGHTBRACK	332
# define	LEFTARRAY	333
# define	RIGHTARRAY	334
# define	PLUS	335
# define	MINUS	336
# define	STAR	337
# define	DIVIDE	338
# define	MOD	339
# define	GREATER	340
# define	LESS	341
# define	EQUAL	342
# define	AND	343
# define	OR	344
# define	NOT	345
# define	XOR	346
# define	COMMA	347
# define	SEMI	348
# define	COLON	349
# define	COMPLEMENT	350
# define	DOT	351
# define	QUESTION	352
# define	COLCOL	353
# define	ELLIPSES	354
# define	PLUSEQ	355
# define	MINUSEQ	356
# define	STAREQ	357
# define	DIVEQ	358
# define	MODEQ	359
# define	XOREQ	360
# define	ANDEQ	361
# define	OREQ	362
# define	LTLT	363
# define	GTGT	364
# define	GTGTEQ	365
# define	LTLTEQ	366
# define	EQEQ	367
# define	NOTEQ	368
# define	LEQ	369
# define	GEQ	370
# define	ANDAND	371
# define	OROR	372
# define	PLUSPLUS	373
# define	MINUSMINUS	374
# define	DOTSTAR	375
# define	ARROWSTAR	376
# define	ARROW	377
# define	IDENTIFIER	378
# define	ID_typedef_name	379
# define	ID_enum_name	380
# define	ID_class_name	381

#line 1 "cpp.y"

   #include "actions.h"
   #include <iostream>

   extern int yyerror(char *);
   extern int yylex();
   extern int line_number, token_number;
   extern char* yytext;

   using namespace std;
   extern int last_seen_cv;
   extern bool seen_const;
   extern bool seen_volatile;
   extern int last_seen;	 
   extern int line_num_for_abs_decl;

#line 19 "cpp.y"
#ifndef YYSTYPE
typedef union  {  
  int tokenvalue;
  expression* expression_ptr;
  member_declarator* member_declarator_ptr;
  param_declarator* param_declarator_ptr;
  string* string_ptr;
  member_declarator_list* member_declarator_list_ptr;
  string_list* string_list_ptr;
  base_specifier_list* base_specifier_list_ptr;
  base_specifier* base_specifier_ptr;
  void* any_ptr;
  param_decl* param_decl_ptr;
  param_decl_list* param_decl_list_ptr;
  class_head* class_head_ptr;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		159
#define	YYFLAG		-32768
#define	YYNTBASE	128

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 381 ? yytranslate[x] : 194)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const short yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     6,     8,    10,    12,    14,    16,
      17,    20,    22,    24,    26,    29,    31,    35,    37,    39,
      41,    42,    44,    47,    49,    50,    52,    54,    56,    60,
      62,    64,    67,    69,    70,    72,    74,    76,    78,    80,
      82,    84,    86,    88,    90,    92,    94,    96,    98,   100,
     102,   104,   106,   108,   110,   112,   117,   119,   123,   125,
     126,   129,   131,   134,   136,   141,   143,   146,   148,   153,
     158,   161,   163,   166,   168,   169,   171,   173,   175,   176,
     179,   181,   183,   184,   186,   187,   189,   193,   196,   201,
     204,   208,   210,   211,   213,   218,   221,   223,   224,   226,
     230,   231,   237,   241,   243,   246,   250,   252,   253,   254,
     259,   261,   262,   264,   268,   271,   274,   277,   279,   280,
     283,   285,   286,   288,   289,   292,   294,   298,   301,   303,
     304,   306,   308,   310,   312,   313,   315,   316,   318,   319,
     321
};
static const short yyrhs[] =
{
     125,     0,   127,     0,   124,     0,   124,     0,   125,     0,
     131,     0,   129,     0,   127,     0,     0,   134,   142,     0,
     136,     0,   124,     0,   132,     0,    96,   132,     0,   138,
       0,   137,    93,   138,     0,    71,     0,    71,     0,   139,
       0,     0,   143,     0,   141,   143,     0,   141,     0,     0,
     144,     0,   145,     0,   153,     0,   148,   155,    94,     0,
     150,     0,   149,     0,   148,   146,     0,   147,     0,     0,
      32,     0,   151,     0,   175,     0,   164,     0,   152,     0,
      33,     0,    67,     0,    47,     0,    13,     0,     6,     0,
      68,     0,    10,     0,    15,     0,    69,     0,    11,     0,
      22,     0,    44,     0,     9,     0,    37,     0,    66,     0,
     132,     0,    27,    25,   130,    94,     0,   156,     0,   154,
      93,   156,     0,   154,     0,     0,   159,   171,     0,   158,
       0,   161,   157,     0,   165,     0,   158,    79,   140,    80,
       0,   160,     0,   161,   159,     0,   165,     0,   160,    75,
     166,    76,     0,   160,    79,   140,    80,     0,    83,   163,
       0,    89,     0,   164,   163,     0,   162,     0,     0,    43,
       0,   135,     0,   196,     0,     0,   150,   195,     0,   167,
       0,   100,     0,     0,   168,     0,     0,   169,     0,   168,
      93,   169,     0,   147,   157,     0,   147,   157,    88,   138,
       0,    88,   172,     0,    75,   137,    76,     0,   170,     0,
       0,   138,     0,    77,   174,   173,    78,     0,    77,    78,
       0,    93,     0,     0,   172,     0,   174,    93,   172,     0,
       0,   177,   176,    77,   180,    78,     0,   178,   128,   189,
       0,    38,     0,   181,   180,     0,   193,    95,   180,     0,
     179,     0,     0,     0,   182,   148,   183,    94,     0,    94,
       0,     0,   184,     0,   183,    93,   184,     0,   159,   186,
       0,   159,   188,     0,    88,    71,     0,   185,     0,     0,
      88,   139,     0,   187,     0,     0,   190,     0,     0,    95,
     191,     0,   192,     0,   191,    93,   192,     0,   193,   132,
       0,    32,     0,     0,    50,     0,    45,     0,    40,     0,
     193,     0,     0,    99,     0,     0,   128,     0,     0,   138,
       0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   136,   140,   142,   160,   174,   178,   189,   193,   211,
     211,   233,   239,   240,   243,   317,   319,   521,   558,   566,
     567,   671,   673,   678,   679,   683,   700,   708,   713,   720,
     726,   735,   750,   752,   770,   782,   784,   790,   796,   803,
     805,   807,   809,   811,   813,   815,   817,   819,   821,   823,
     825,   827,   829,   831,   836,   949,   973,   975,   981,   982,
     986,   991,   993,  1002,  1007,  1018,  1020,  1029,  1035,  1044,
    1053,  1055,  1062,  1066,  1067,  1071,  1079,  1091,  1092,  1096,
    1129,  1137,  1138,  1142,  1143,  1147,  1152,  1160,  1167,  1201,
    1203,  1208,  1210,  1214,  1215,  1217,  1221,  1222,  1226,  1228,
    1234,  1234,  1276,  1293,  1300,  1302,  1308,  1309,  1313,  1313,
    1335,  1336,  1340,  1345,  1358,  1366,  1379,  1384,  1385,  1389,
    1394,  1395,  1400,  1401,  1405,  1409,  1414,  1421,  1439,  1440,
    1444,  1446,  1448,  1453,  1455,  1508,  1509,  1615,  1617,  1697,
    1698
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "KW_asm", "KW_do", "KW_inline", "KW_short", 
  "KW_typeid", "KW_auto", "KW_double", "KW_int", "KW_signed", 
  "KW_typename", "KW_bool", "KW_dynamic_cast", "KW_long", "KW_sizeof", 
  "KW_union", "KW_break", "KW_else", "KW_mutable", "KW_static", 
  "KW_unsigned", "KW_case", "KW_enum", "KW_namespace", "KW_static_cast", 
  "KW_using", "KW_catch", "KW_explicit", "KW_new", "KW_struct", 
  "KW_virtual", "KW_char", "KW_extern", "KW_operator", "KW_switch", 
  "KW_void", "KW_class", "KW_false", "KW_private", "KW_template", 
  "KW_volatile", "KW_const", "KW_float", "KW_protected", "KW_this", 
  "KW_wchar_t", "KW_const_cast", "KW_for", "KW_public", "KW_throw", 
  "KW_while", "KW_continue", "KW_friend", "KW_register", "KW_true", 
  "KW_default", "KW_goto", "KW_reinterpret_cast", "KW_try", "KW_delete", 
  "KW_if", "KW_return", "KW_typedef", "KW_export", "KW_string", 
  "KW_unsigned_char", "KW_unsigned_short", "KW_unsigned_long", 
  "KW_long_double", "INTEGER_LITERAL", "CHARACTER_LITERAL", 
  "FLOATING_LITERAL", "STRING_LITERAL", "LEFTPAREN", "RIGHTPAREN", 
  "LEFTBRACK", "RIGHTBRACK", "LEFTARRAY", "RIGHTARRAY", "PLUS", "MINUS", 
  "STAR", "DIVIDE", "MOD", "GREATER", "LESS", "EQUAL", "AND", "OR", "NOT", 
  "XOR", "COMMA", "SEMI", "COLON", "COMPLEMENT", "DOT", "QUESTION", 
  "COLCOL", "ELLIPSES", "PLUSEQ", "MINUSEQ", "STAREQ", "DIVEQ", "MODEQ", 
  "XOREQ", "ANDEQ", "OREQ", "LTLT", "GTGT", "GTGTEQ", "LTLTEQ", "EQEQ", 
  "NOTEQ", "LEQ", "GEQ", "ANDAND", "OROR", "PLUSPLUS", "MINUSMINUS", 
  "DOTSTAR", "ARROWSTAR", "ARROW", "IDENTIFIER", "ID_typedef_name", 
  "ID_enum_name", "ID_class_name", "any_identifier", "ID_namespace_alias", 
  "namespace_name", "namespace_alias", "class_name", "translation_unit", 
  "@1", "id_expression", "unqualified_id", "expression_list", 
  "assignment_expression", "constant_expression", 
  "constant_expression_opt", "declaration_seq", "declaration_seq_opt", 
  "declaration", "block_declaration", "simple_declaration", 
  "decl_specifier", "decl_specifier_seq", "decl_specifier_seq_opt", 
  "function_specifier", "type_specifier", "simple_type_specifier", 
  "type_name", "using_directive", "init_declarator_list", 
  "init_declarator_list_opt", "init_declarator", "parameter_declarator", 
  "direct_parameter_declarator", "declarator", "direct_declarator", 
  "ptr_operator", "cv_qualifier_seq", "cv_qualifier_seq_opt", 
  "cv_qualifier", "declarator_id", "parameter_declaration_clause", 
  "parameter_declaration_list_opt", "parameter_declaration_list", 
  "parameter_declaration", "initializer", "initializer_opt", 
  "initializer_clause", "comma_opt", "initializer_list", 
  "class_specifier", "@2", "class_head", "class_key", 
  "member_specification", "member_specification_opt", 
  "member_declaration", "@3", "member_declarator_list", 
  "member_declarator", "pure_specifier", "pure_specifier_opt", 
  "constant_initializer", "constant_initializer_opt", "base_clause_opt", 
  "base_clause", "base_specifier_list", "base_specifier", 
  "access_specifier", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   128,   128,   128,   129,   194,   130,   131,   132,   134,
     133,   135,   136,   136,   136,   137,   137,   138,   139,   140,
     140,   141,   141,   142,   142,   143,   144,   144,   145,   146,
     146,   147,   148,   148,   149,   150,   150,   150,   151,   151,
     151,   151,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   151,   151,   151,   152,   153,   154,   154,   155,   155,
     156,   157,   157,   158,   158,   159,   159,   160,   160,   160,
     161,   161,   162,   163,   163,   164,   165,   195,   195,   196,
     166,   197,   197,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   172,   173,   173,   174,   174,
     176,   175,   177,   178,   179,   179,   180,   180,   182,   181,
     198,   198,   183,   183,   184,   184,   185,   186,   186,   187,
     188,   188,   189,   189,   190,   191,   191,   192,   199,   199,
     193,   193,   193,   200,   200,   201,   201,   202,   202,   203,
     203
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     1,     1,     2,     1,     3,     1,     1,     1,
       0,     1,     2,     1,     0,     1,     1,     1,     3,     1,
       1,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     1,     0,
       2,     1,     2,     1,     4,     1,     2,     1,     4,     4,
       2,     1,     2,     1,     0,     1,     1,     1,     0,     2,
       1,     1,     0,     1,     0,     1,     3,     2,     4,     2,
       3,     1,     0,     1,     4,     2,     1,     0,     1,     3,
       0,     5,     3,     1,     2,     3,     1,     0,     0,     4,
       1,     0,     1,     3,     2,     2,     2,     1,     0,     2,
       1,     0,     1,     0,     2,     1,     3,     2,     1,     0,
       1,     1,     1,     1,     0,     1,     0,     1,     0,     1,
       0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       9,    33,     0,    33,    10,    21,    25,    26,    32,    59,
      27,     0,    22,    43,    51,    45,    48,    42,    46,    49,
      34,    39,    52,   103,    75,    50,    41,    53,    40,    44,
      47,    74,    71,     0,    12,     8,    54,    76,    11,    31,
      30,    29,    35,    38,    58,     0,    56,    92,    65,     0,
      37,    67,    36,   100,     0,     4,     7,     0,     6,    73,
      70,    74,    14,     0,    28,     0,     0,    91,    60,    33,
      20,    13,    66,     0,     3,     1,     2,   123,    55,    72,
      57,    17,     0,    15,     0,    93,    89,    32,     0,     0,
      80,    83,    85,    18,    19,     0,   108,     0,   102,   122,
      90,     0,    95,    98,    97,    87,    61,     0,    63,    54,
      68,    33,    69,   132,   131,   130,   106,     0,   108,    33,
       0,   124,   125,     0,    16,    96,     0,     0,    20,    62,
      86,   101,   104,     0,   108,     0,   127,    99,    94,    88,
       0,   118,     0,   112,   105,   126,    64,     0,   117,   114,
     120,   115,     0,   109,    18,   119,   113,     0,     0,     0
};

static const short yydefgoto[] =
{
      77,    56,    57,    58,    71,   157,     1,    37,    38,    82,
      85,    94,    95,     3,     4,     5,     6,     7,    39,     8,
       9,    40,    41,    42,    43,    10,    44,    45,    46,   105,
     106,    47,    48,    49,    59,    60,    50,    51,    89,    90,
      91,    92,    67,    68,    86,   126,   104,    52,    73,    53,
      54,   116,   117,   118,   119,   142,   143,   148,   149,   150,
     151,    98,    99,   121,   122,   120
};

static const short yypact[] =
{
  -32768,    30,   -14,    48,-32768,-32768,-32768,-32768,-32768,    -5,
  -32768,   -80,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    13,-32768,   -46,-32768,-32768,    10,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   -10,    -6,-32768,   -20,     1,   -31,
  -32768,-32768,-32768,-32768,   -17,-32768,-32768,    -4,-32768,-32768,
  -32768,    13,-32768,   -31,-32768,    28,    29,-32768,-32768,    33,
      40,-32768,-32768,    35,-32768,-32768,-32768,    18,-32768,-32768,
  -32768,-32768,   -56,-32768,    24,-32768,-32768,   -31,     3,    39,
  -32768,    23,-32768,-32768,-32768,    37,   -19,    47,-32768,-32768,
  -32768,    28,-32768,-32768,    25,    32,    42,   -31,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    45,   -19,-32768,
      31,    34,-32768,   -46,-32768,    29,    50,    28,    40,-32768,
  -32768,-32768,-32768,    -5,   -19,    47,-32768,-32768,-32768,-32768,
      49,    43,   -71,-32768,-32768,-32768,-32768,    54,-32768,-32768,
  -32768,-32768,   -31,-32768,-32768,-32768,-32768,   132,   133,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,    -9,-32768,-32768,-32768,-32768,-32768,
     -50,   -12,     6,-32768,-32768,   134,-32768,-32768,-32768,   -62,
     -66,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    73,    36,
  -32768,   -47,-32768,   -53,-32768,    77,    12,   -13,-32768,-32768,
  -32768,    38,-32768,-32768,   -65,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   -52,-32768,-32768,-32768,   -11,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,     4,   -68
};


#define	YYLAST		149


static const short yytable[] =
{
      36,    13,    72,    88,    14,    15,    16,    87,    17,    13,
      18,    11,    14,    15,    16,    83,    17,    19,    18,   103,
     100,   113,   152,   153,    62,    19,   114,    20,    21,   123,
     -24,   115,    22,    23,   107,    20,    21,   101,    24,    25,
      22,    23,    26,    61,    55,    88,    24,    25,   -23,    87,
      26,   124,    31,   133,   107,    65,    24,     2,    32,  -107,
     137,    27,    28,    29,    30,    33,   132,   123,    66,    27,
      28,    29,    30,    61,   108,     2,    69,   139,    31,   109,
      70,    35,   144,    63,    32,   -13,   141,   113,    64,   -13,
      78,    33,   114,    34,   108,    81,    35,   115,   -13,    81,
      81,    84,   102,   -13,   -13,   141,    84,    74,    75,   -84,
      76,    93,    96,    97,   136,   110,   111,   112,   125,    34,
     127,   128,    35,   131,    36,   154,   134,   135,   138,   146,
      35,   147,   158,   159,   140,   155,    80,    12,    79,   145,
       0,   156,     0,   129,     0,     0,     0,     0,     0,   130
};

static const short yycheck[] =
{
       9,     6,    49,    69,     9,    10,    11,    69,    13,     6,
      15,    25,     9,    10,    11,    65,    13,    22,    15,    84,
      76,    40,    93,    94,    33,    22,    45,    32,    33,    97,
       0,    50,    37,    38,    87,    32,    33,    93,    43,    44,
      37,    38,    47,    31,   124,   111,    43,    44,     0,   111,
      47,   101,    83,   119,   107,    75,    43,    27,    89,    78,
     125,    66,    67,    68,    69,    96,   118,   135,    88,    66,
      67,    68,    69,    61,    87,    27,    75,   127,    83,    88,
      79,   127,   134,    93,    89,    75,   133,    40,    94,    79,
      94,    96,    45,   124,   107,    71,   127,    50,    88,    71,
      71,    77,    78,    93,    94,   152,    77,   124,   125,    76,
     127,    71,    77,    95,   123,    76,    93,    80,    93,   124,
      88,    79,   127,    78,   133,    71,    95,    93,    78,    80,
     127,    88,     0,     0,   128,   147,    63,     3,    61,   135,
      -1,   152,    -1,   107,    -1,    -1,    -1,    -1,    -1,   111
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


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
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
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

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 136 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 2:
#line 140 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 3:
#line 142 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 4:
#line 160 "cpp.y"
{ ;
    break;}
case 5:
#line 174 "cpp.y"
{;
    break;}
case 6:
#line 181 "cpp.y"
{ ;
    break;}
case 7:
#line 189 "cpp.y"
{;
    break;}
case 8:
#line 193 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 9:
#line 211 "cpp.y"
{  
   		translation_unit_start();
   	;
    break;}
case 10:
#line 215 "cpp.y"
{;
    break;}
case 11:
#line 233 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 12:
#line 239 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 13:
#line 240 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 14:
#line 243 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr; g_bdestructor_seen = true;;
    break;}
case 15:
#line 318 "cpp.y"
{;
    break;}
case 16:
#line 320 "cpp.y"
{;
    break;}
case 17:
#line 522 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);
  ;
    break;}
case 18:
#line 559 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);     
  ;
    break;}
case 19:
#line 566 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 20:
#line 567 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 21:
#line 672 "cpp.y"
{;
    break;}
case 22:
#line 674 "cpp.y"
{;
    break;}
case 23:
#line 678 "cpp.y"
{;
    break;}
case 24:
#line 679 "cpp.y"
{;
    break;}
case 25:
#line 684 "cpp.y"
{;
    break;}
case 26:
#line 701 "cpp.y"
{;
    break;}
case 27:
#line 709 "cpp.y"
{ ;
    break;}
case 28:
#line 716 "cpp.y"
{;
    break;}
case 29:
#line 725 "cpp.y"
{;
    break;}
case 30:
#line 727 "cpp.y"
{ yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 31:
#line 736 "cpp.y"
{
		if (yyvsp[0].string_ptr != NULL) 
		{
			if (yyval.string_list_ptr == NULL) {yyval.string_list_ptr = new string_list;}
			yyval.string_list_ptr->push_back(yyvsp[0].string_ptr);
		}
		else
		{	
			yyval.string_list_ptr = NULL;
		}
    ;
    break;}
case 32:
#line 751 "cpp.y"
{yyval.string_list_ptr = yyvsp[0].string_list_ptr;;
    break;}
case 33:
#line 753 "cpp.y"
{yyval.string_list_ptr = NULL;;
    break;}
case 34:
#line 775 "cpp.y"
{ yyval.string_ptr = NULL;;
    break;}
case 35:
#line 783 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 36:
#line 785 "cpp.y"
{;
    break;}
case 37:
#line 791 "cpp.y"
{;
    break;}
case 38:
#line 799 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 39:
#line 804 "cpp.y"
{yyval.string_ptr = new string("char");;
    break;}
case 40:
#line 806 "cpp.y"
{yyval.string_ptr = new string("unsigned char");;
    break;}
case 41:
#line 808 "cpp.y"
{yyval.string_ptr = new string("wchar_t");;
    break;}
case 42:
#line 810 "cpp.y"
{yyval.string_ptr = new string("bool");;
    break;}
case 43:
#line 812 "cpp.y"
{yyval.string_ptr = new string("short");;
    break;}
case 44:
#line 814 "cpp.y"
{yyval.string_ptr = new string("unsigned short");;
    break;}
case 45:
#line 816 "cpp.y"
{yyval.string_ptr = new string("int");;
    break;}
case 46:
#line 818 "cpp.y"
{yyval.string_ptr = new string("long");;
    break;}
case 47:
#line 820 "cpp.y"
{yyval.string_ptr = new string("unsigned long");;
    break;}
case 48:
#line 822 "cpp.y"
{yyval.string_ptr = new string("signed");;
    break;}
case 49:
#line 824 "cpp.y"
{yyval.string_ptr = new string("unsigned");;
    break;}
case 50:
#line 826 "cpp.y"
{yyval.string_ptr = new string("float");;
    break;}
case 51:
#line 828 "cpp.y"
{yyval.string_ptr = new string("double");;
    break;}
case 52:
#line 830 "cpp.y"
{yyval.string_ptr = new string("void");;
    break;}
case 53:
#line 832 "cpp.y"
{yyval.string_ptr = new string("string");;
    break;}
case 54:
#line 836 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 55:
#line 953 "cpp.y"
{ ;
    break;}
case 56:
#line 974 "cpp.y"
{;
    break;}
case 57:
#line 977 "cpp.y"
{;
    break;}
case 58:
#line 981 "cpp.y"
{;
    break;}
case 59:
#line 982 "cpp.y"
{;
    break;}
case 60:
#line 987 "cpp.y"
{;
    break;}
case 61:
#line 992 "cpp.y"
{yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;;
    break;}
case 62:
#line 995 "cpp.y"
{
      yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;
      yyval.param_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tokenvalue);
    ;
    break;}
case 63:
#line 1003 "cpp.y"
{
      yyval.param_declarator_ptr = new param_declarator;
      yyval.param_declarator_ptr->decl_id = yyvsp[0].string_ptr->c_str();
    ;
    break;}
case 64:
#line 1008 "cpp.y"
{
      yyval.param_declarator_ptr = yyvsp[-3].param_declarator_ptr;
      if (yyvsp[-1].expression_ptr != 0)
	    {
	      yyval.param_declarator_ptr->arr_dim.push_back(yyvsp[-1].expression_ptr);
	    }
    ;
    break;}
case 65:
#line 1019 "cpp.y"
{yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;;
    break;}
case 66:
#line 1022 "cpp.y"
{
        yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;
        yyval.member_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tokenvalue);
    ;
    break;}
case 67:
#line 1030 "cpp.y"
{
        yyval.member_declarator_ptr = new member_declarator;
		yyval.member_declarator_ptr->method = false;
        yyval.member_declarator_ptr->declarator_id = yyvsp[0].string_ptr;
    ;
    break;}
case 68:
#line 1040 "cpp.y"
{
        yyval.member_declarator_ptr->params = yyvsp[-1].param_decl_list_ptr;
        yyval.member_declarator_ptr->method = true;
    ;
    break;}
case 69:
#line 1045 "cpp.y"
{
        yyval.member_declarator_ptr->array_indexes.push_back(yyvsp[-1].expression_ptr);
    ;
    break;}
case 70:
#line 1054 "cpp.y"
{yyval.tokenvalue = STAR;;
    break;}
case 71:
#line 1056 "cpp.y"
{yyval.tokenvalue = AND;;
    break;}
case 72:
#line 1062 "cpp.y"
{/* $$ = $1 + $2; */;
    break;}
case 73:
#line 1066 "cpp.y"
{;
    break;}
case 74:
#line 1067 "cpp.y"
{/* $$ = 0; */;
    break;}
case 75:
#line 1072 "cpp.y"
{
    ;
    break;}
case 76:
#line 1080 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 77:
#line 1091 "cpp.y"
{;
    break;}
case 78:
#line 1092 "cpp.y"
{;
    break;}
case 79:
#line 1097 "cpp.y"
{;
    break;}
case 80:
#line 1131 "cpp.y"
{yyval.param_decl_list_ptr = yyvsp[0].param_decl_list_ptr;;
    break;}
case 81:
#line 1137 "cpp.y"
{;
    break;}
case 82:
#line 1138 "cpp.y"
{;
    break;}
case 83:
#line 1142 "cpp.y"
{;
    break;}
case 84:
#line 1143 "cpp.y"
{yyval.param_decl_list_ptr = NULL;;
    break;}
case 85:
#line 1148 "cpp.y"
{ 
      yyval.param_decl_list_ptr = new param_decl_list;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 86:
#line 1153 "cpp.y"
{
      yyval.param_decl_list_ptr = yyvsp[-2].param_decl_list_ptr;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 87:
#line 1161 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-1].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[0].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = false; 
    ;
    break;}
case 88:
#line 1168 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-3].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[-2].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = true;
      yyval.param_decl_ptr->defval = yyvsp[0].expression_ptr;
    ;
    break;}
case 89:
#line 1202 "cpp.y"
{;
    break;}
case 90:
#line 1204 "cpp.y"
{;
    break;}
case 91:
#line 1209 "cpp.y"
{;
    break;}
case 92:
#line 1210 "cpp.y"
{;
    break;}
case 93:
#line 1214 "cpp.y"
{;
    break;}
case 94:
#line 1216 "cpp.y"
{/* $$ = $3; */;
    break;}
case 95:
#line 1217 "cpp.y"
{;
    break;}
case 96:
#line 1221 "cpp.y"
{/* $$ = 1; */;
    break;}
case 97:
#line 1222 "cpp.y"
{/* $$ = 0; */;
    break;}
case 98:
#line 1227 "cpp.y"
{;
    break;}
case 99:
#line 1229 "cpp.y"
{;
    break;}
case 100:
#line 1236 "cpp.y"
{
	  if (!is_defined_class(yyvsp[0].class_head_ptr->class_name->c_str()))
	  {
		  //check if this class should be wrapped or not depending on wsdd information
		  if (!is_webservice_class(yyvsp[0].class_head_ptr->class_name->c_str())) //bean class
		  {
					BeanClass* pBeanClass = new BeanClass();
					pBeanClass->SetClassName(*(yyvsp[0].class_head_ptr->class_name));
					g_pTranslationUnit->AddBeanClass(pBeanClass);
					g_pCurrentBeanClass = pBeanClass;
					g_currentclasstype = BEANCLASS;
//					g_baccessbeanmacrofound = false;
					//following line adds default namespace for this complex type. 
					//This should be removed when we get the namespace from the wsdd.
					string defns = "http://www.opensource.lk/" + (*(yyvsp[0].class_head_ptr->class_name));
					g_ClassNamespaces[*(yyvsp[0].class_head_ptr->class_name)] = defns;
		  }
		  else // this is the webservice class - there cannot be 2 web service classes
		  {
					WSClass* pWSClass = new WSClass();
					pWSClass->SetClassName(*(yyvsp[0].class_head_ptr->class_name));
					g_pTranslationUnit->SetWSClass(pWSClass);
					g_pCurrentWSClass = pWSClass;
					g_currentclasstype = WSCLASS;
//					g_baccessbeanmacrofound = false;
					//following line adds default namespace for this web service. 
					//This should be removed when we get the namespace from the wsdd.
					string defns = "http://www.opensource.lk/" + (*(yyvsp[0].class_head_ptr->class_name));
					g_ClassNamespaces[*(yyvsp[0].class_head_ptr->class_name)] = defns;
		  }   
  		  g_classesfound.push_back(g_classname);
	   }
  	;
    break;}
case 101:
#line 1270 "cpp.y"
{
			g_classname = ""; //end of class scope
   	;
    break;}
case 102:
#line 1278 "cpp.y"
{
    	g_classname = yyvsp[-1].string_ptr->c_str();
    	yyval.class_head_ptr = new class_head;
     	yyval.class_head_ptr->class_name = yyvsp[-1].string_ptr;
			yyval.class_head_ptr->baselist = yyvsp[0].base_specifier_list_ptr; //may be NULL
    ;
    break;}
case 103:
#line 1293 "cpp.y"
{;
    break;}
case 104:
#line 1301 "cpp.y"
{;
    break;}
case 105:
#line 1304 "cpp.y"
{;
    break;}
case 106:
#line 1308 "cpp.y"
{;
    break;}
case 107:
#line 1309 "cpp.y"
{;
    break;}
case 108:
#line 1313 "cpp.y"
{ g_bdestructor_seen = false;;
    break;}
case 109:
#line 1317 "cpp.y"
{
      add_member_declaration(yyvsp[-2].string_list_ptr, yyvsp[-1].member_declarator_list_ptr);
    ;
    break;}
case 112:
#line 1341 "cpp.y"
{
      yyval.member_declarator_list_ptr = new member_declarator_list;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 113:
#line 1346 "cpp.y"
{
      yyval.member_declarator_list_ptr = yyvsp[-2].member_declarator_list_ptr;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 114:
#line 1359 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[-1].member_declarator_ptr != 0) //there is a pure specifier
      {
        yyval.member_declarator_ptr->bpure = true;  
      }
    ;
    break;}
case 115:
#line 1367 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[0].expression_ptr != NULL)
      {
        yyval.member_declarator_ptr->expr = yyvsp[0].expression_ptr;
      }
    ;
    break;}
case 116:
#line 1380 "cpp.y"
{yyval.tokenvalue = 1;;
    break;}
case 117:
#line 1384 "cpp.y"
{yyval.tokenvalue = yyvsp[0].tokenvalue;;
    break;}
case 118:
#line 1385 "cpp.y"
{yyval.tokenvalue = 0;;
    break;}
case 119:
#line 1390 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 120:
#line 1394 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 121:
#line 1395 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 122:
#line 1400 "cpp.y"
{yyval.base_specifier_list_ptr = yyvsp[0].base_specifier_list_ptr;;
    break;}
case 123:
#line 1401 "cpp.y"
{yyval.base_specifier_list_ptr = NULL;;
    break;}
case 124:
#line 1405 "cpp.y"
{yyval.base_specifier_list_ptr = yyvsp[0].base_specifier_list_ptr;;
    break;}
case 125:
#line 1410 "cpp.y"
{
    	yyval.base_specifier_list_ptr = new base_specifier_list;
     	yyval.base_specifier_list_ptr->push_back(yyvsp[0].base_specifier_ptr);
    ;
    break;}
case 126:
#line 1415 "cpp.y"
{
    	yyval.base_specifier_list_ptr->push_back(yyvsp[0].base_specifier_ptr);
    ;
    break;}
case 127:
#line 1431 "cpp.y"
{
    	yyval.base_specifier_ptr = new base_specifier;
     	yyval.base_specifier_ptr->access = yyvsp[-1].tokenvalue;
      yyval.base_specifier_ptr->class_name = yyvsp[0].string_ptr;
    ;
    break;}
case 128:
#line 1439 "cpp.y"
{/*$$ = 1; */;
    break;}
case 129:
#line 1440 "cpp.y"
{/* $$ = 0; */;
    break;}
case 130:
#line 1445 "cpp.y"
{yyval.tokenvalue = yyvsp[0].tokenvalue; g_currentaccessspecifier = yyvsp[0].tokenvalue;;
    break;}
case 131:
#line 1447 "cpp.y"
{yyval.tokenvalue = yyvsp[0].tokenvalue; g_currentaccessspecifier = yyvsp[0].tokenvalue;;
    break;}
case 132:
#line 1449 "cpp.y"
{yyval.tokenvalue = yyvsp[0].tokenvalue; g_currentaccessspecifier = yyvsp[0].tokenvalue;;
    break;}
case 133:
#line 1454 "cpp.y"
{yyval.tokenvalue=yyvsp[0].tokenvalue;;
    break;}
case 134:
#line 1455 "cpp.y"
{yyval.tokenvalue = 0;;
    break;}
case 135:
#line 1508 "cpp.y"
{;
    break;}
case 136:
#line 1509 "cpp.y"
{;
    break;}
case 137:
#line 1616 "cpp.y"
{;
    break;}
case 138:
#line 1617 "cpp.y"
{;
    break;}
case 139:
#line 1697 "cpp.y"
{;
    break;}
case 140:
#line 1698 "cpp.y"
{;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

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

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1750 "cpp.y"

