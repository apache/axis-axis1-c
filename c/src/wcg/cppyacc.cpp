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
# define	KW_unsigned_char	320
# define	KW_unsigned_short	321
# define	KW_unsigned_long	322
# define	KW_long_double	323
# define	INTEGER_LITERAL	324
# define	CHARACTER_LITERAL	325
# define	FLOATING_LITERAL	326
# define	STRING_LITERAL	327
# define	LEFTPAREN	328
# define	RIGHTPAREN	329
# define	LEFTBRACK	330
# define	RIGHTBRACK	331
# define	LEFTARRAY	332
# define	RIGHTARRAY	333
# define	PLUS	334
# define	MINUS	335
# define	STAR	336
# define	DIVIDE	337
# define	MOD	338
# define	GREATER	339
# define	LESS	340
# define	EQUAL	341
# define	AND	342
# define	OR	343
# define	NOT	344
# define	XOR	345
# define	COMMA	346
# define	SEMI	347
# define	COLON	348
# define	COMPLEMENT	349
# define	DOT	350
# define	QUESTION	351
# define	COLCOL	352
# define	ELLIPSES	353
# define	PLUSEQ	354
# define	MINUSEQ	355
# define	STAREQ	356
# define	DIVEQ	357
# define	MODEQ	358
# define	XOREQ	359
# define	ANDEQ	360
# define	OREQ	361
# define	LTLT	362
# define	GTGT	363
# define	GTGTEQ	364
# define	LTLTEQ	365
# define	EQEQ	366
# define	NOTEQ	367
# define	LEQ	368
# define	GEQ	369
# define	ANDAND	370
# define	OROR	371
# define	PLUSPLUS	372
# define	MINUSMINUS	373
# define	DOTSTAR	374
# define	ARROWSTAR	375
# define	ARROW	376
# define	IDENTIFIER	377
# define	ID_typedef_name	378
# define	ID_original_namespace_name	379
# define	ID_namespace_alias	380
# define	ID_enum_name	381
# define	ID_class_name	382
# define	ID_template_name	383

#line 1 "cpp.y"

  #define YYDELETEVAL(v,n) 
  #define YYDELETEPOSN(v,n)
  //  #define _PARSE_DEBUG 1
  #define TRUE 1

   extern int yyerror(char *);
   extern int yylex();
   extern int line_number, token_number;
   extern char* yytext;
   bool inTemplate = false;

   #include "actions.h"
   #include <iostream>
   using namespace std;
   extern int last_seen_cv;
   extern bool seen_const;
   extern bool seen_volatile;
   extern int last_seen;
	 
   extern int line_num_for_abs_decl;

#line 25 "cpp.y"
#ifndef YYSTYPE
typedef union  {  
  void* id_sym;
  void* name;
  int tcount;
  void* dspec;
  void* decl;
  void* stmt;
  void* ctype;
  expression* expression_ptr;
  member_declarator* member_declarator_ptr;
  param_declarator* param_declarator_ptr;
  string* string_ptr;
  void* paramlist;
  void* init;
  void* tparm;
  member_declarator_list* member_declarator_list_ptr;
  void* expcont;
  void* newdecl;
  void* arrdims;
  string_list* string_list_ptr;
  void* enumcont;
  void* argcont;
  base_specifier_list* inhcont;
  base_specifier* bclass;
  void* typcont;
  void* handcont;
  void* memdecl;
  void* memdecls;
  void* tparmlist;
  void* cblock;
  void* cfcp;
  void* obj;
  void* endef;
  void* tspec;
  param_decl* param_decl_ptr;
  param_decl_list* param_decl_list_ptr;
  void* block;
  class_head* class_head_ptr;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		151
#define	YYFLAG		-32768
#define	YYNTBASE	130

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 383 ? yytranslate[x] : 191)

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
     126,   127,   128,   129
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     4,     6,     8,    10,    12,    14,    16,
      18,    20,    22,    24,    26,    27,    30,    32,    34,    36,
      39,    43,    45,    46,    48,    50,    52,    56,    58,    59,
      61,    63,    65,    66,    68,    71,    73,    74,    76,    78,
      82,    84,    87,    89,    90,    92,    94,    96,    98,   100,
     102,   104,   106,   108,   110,   112,   114,   116,   118,   120,
     122,   124,   126,   128,   129,   136,   138,   142,   144,   145,
     147,   151,   153,   155,   159,   161,   162,   165,   167,   170,
     172,   177,   179,   182,   184,   189,   194,   197,   199,   202,
     204,   205,   207,   209,   211,   212,   215,   217,   219,   220,
     222,   223,   225,   229,   232,   237,   240,   244,   246,   247,
     249,   254,   257,   259,   260,   262,   266,   267,   273,   277,
     279,   282,   286,   288,   289,   290,   295,   297,   298,   300,
     304,   307,   310,   313,   315,   316,   319,   321,   322,   324,
     325,   328,   330,   334,   337,   339,   340,   342,   344,   346,
     348,   349,   351,   352,   354,   355,   357
};
static const short yyrhs[] =
{
     124,     0,   125,     0,   126,     0,   127,     0,   128,     0,
     123,     0,   124,     0,   193,     0,   194,     0,   125,     0,
     126,     0,   128,     0,   127,     0,     0,   133,   141,     0,
     135,     0,   123,     0,   131,     0,    95,   131,     0,   198,
      98,   197,     0,   196,     0,     0,   131,     0,   192,     0,
     137,     0,   136,    92,   137,     0,   136,     0,     0,    70,
       0,    70,     0,   138,     0,     0,   142,     0,   140,   142,
       0,   140,     0,     0,   143,     0,   144,     0,   147,   152,
      93,     0,   148,     0,   147,   145,     0,   146,     0,     0,
     149,     0,   172,     0,   161,     0,   150,     0,    33,     0,
      66,     0,    47,     0,    13,     0,     6,     0,    67,     0,
      10,     0,    15,     0,    68,     0,    11,     0,    22,     0,
      44,     0,     9,     0,    37,     0,   131,     0,     0,    24,
     213,   201,    76,   203,    77,     0,   204,     0,   202,    92,
     204,     0,   202,     0,     0,   205,     0,   205,    87,   138,
       0,   130,     0,   153,     0,   151,    92,   153,     0,   151,
       0,     0,   156,   168,     0,   155,     0,   158,   154,     0,
     162,     0,   155,    78,   139,    79,     0,   157,     0,   158,
     156,     0,   162,     0,   157,    74,   163,    75,     0,   157,
      78,   139,    79,     0,    82,   160,     0,    88,     0,   161,
     160,     0,   159,     0,     0,    43,     0,   134,     0,   207,
       0,     0,   148,   206,     0,   164,     0,    99,     0,     0,
     165,     0,     0,   166,     0,   165,    92,   166,     0,   146,
     154,     0,   146,   154,    87,   137,     0,    87,   169,     0,
      74,   136,    75,     0,   167,     0,     0,   137,     0,    76,
     171,   170,    77,     0,    76,    77,     0,    92,     0,     0,
     169,     0,   171,    92,   169,     0,     0,   174,   173,    76,
     177,    77,     0,   175,   130,   186,     0,    38,     0,   178,
     177,     0,   190,    94,   177,     0,   176,     0,     0,     0,
     179,   147,   180,    93,     0,    93,     0,     0,   181,     0,
     180,    92,   181,     0,   156,   183,     0,   156,   185,     0,
      87,    70,     0,   182,     0,     0,    87,   138,     0,   184,
       0,     0,   187,     0,     0,    94,   188,     0,   189,     0,
     188,    92,   189,     0,   190,   131,     0,    32,     0,     0,
      50,     0,    45,     0,    40,     0,   190,     0,     0,    98,
       0,     0,   130,     0,     0,   137,     0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   174,   175,   176,   177,   178,   180,   210,   214,   215,
     219,   223,   227,   232,   247,   247,   269,   275,   276,   279,
     293,   300,   301,   305,   306,   357,   359,   364,   365,   563,
     600,   608,   609,   719,   721,   726,   727,   731,   748,   761,
     768,   783,   791,   793,   821,   823,   829,   835,   842,   844,
     846,   848,   850,   852,   854,   856,   858,   860,   862,   864,
     866,   868,   873,   890,   890,   898,   900,   905,   906,   910,
     912,   917,  1009,  1011,  1017,  1018,  1022,  1027,  1029,  1038,
    1043,  1054,  1056,  1065,  1071,  1080,  1089,  1091,  1098,  1102,
    1103,  1107,  1120,  1132,  1133,  1137,  1172,  1180,  1181,  1185,
    1186,  1190,  1195,  1203,  1210,  1244,  1246,  1251,  1253,  1257,
    1258,  1260,  1264,  1265,  1269,  1271,  1277,  1277,  1306,  1323,
    1330,  1332,  1338,  1339,  1343,  1343,  1362,  1363,  1367,  1372,
    1385,  1393,  1406,  1411,  1412,  1416,  1421,  1422,  1427,  1428,
    1432,  1436,  1441,  1448,  1466,  1467,  1471,  1473,  1475,  1480,
    1482,  1535,  1536,  1656,  1658,  1744,  1745
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
  "KW_if", "KW_return", "KW_typedef", "KW_export", "KW_unsigned_char", 
  "KW_unsigned_short", "KW_unsigned_long", "KW_long_double", 
  "INTEGER_LITERAL", "CHARACTER_LITERAL", "FLOATING_LITERAL", 
  "STRING_LITERAL", "LEFTPAREN", "RIGHTPAREN", "LEFTBRACK", "RIGHTBRACK", 
  "LEFTARRAY", "RIGHTARRAY", "PLUS", "MINUS", "STAR", "DIVIDE", "MOD", 
  "GREATER", "LESS", "EQUAL", "AND", "OR", "NOT", "XOR", "COMMA", "SEMI", 
  "COLON", "COMPLEMENT", "DOT", "QUESTION", "COLCOL", "ELLIPSES", 
  "PLUSEQ", "MINUSEQ", "STAREQ", "DIVEQ", "MODEQ", "XOREQ", "ANDEQ", 
  "OREQ", "LTLT", "GTGT", "GTGTEQ", "LTLTEQ", "EQEQ", "NOTEQ", "LEQ", 
  "GEQ", "ANDAND", "OROR", "PLUSPLUS", "MINUSMINUS", "DOTSTAR", 
  "ARROWSTAR", "ARROW", "IDENTIFIER", "ID_typedef_name", 
  "ID_original_namespace_name", "ID_namespace_alias", "ID_enum_name", 
  "ID_class_name", "ID_template_name", "any_identifier", "class_name", 
  "translation_unit", "@1", "id_expression", "unqualified_id", 
  "expression_list", "assignment_expression", "constant_expression", 
  "constant_expression_opt", "declaration_seq", "declaration_seq_opt", 
  "declaration", "block_declaration", "simple_declaration", 
  "decl_specifier", "decl_specifier_seq", "decl_specifier_seq_opt", 
  "type_specifier", "simple_type_specifier", "type_name", 
  "init_declarator_list", "init_declarator_list_opt", "init_declarator", 
  "parameter_declarator", "direct_parameter_declarator", "declarator", 
  "direct_declarator", "ptr_operator", "cv_qualifier_seq", 
  "cv_qualifier_seq_opt", "cv_qualifier", "declarator_id", 
  "parameter_declaration_clause", "parameter_declaration_list_opt", 
  "parameter_declaration_list", "parameter_declaration", "initializer", 
  "initializer_opt", "initializer_clause", "comma_opt", 
  "initializer_list", "class_specifier", "@3", "class_head", "class_key", 
  "member_specification", "member_specification_opt", 
  "member_declaration", "@4", "member_declarator_list", 
  "member_declarator", "pure_specifier", "pure_specifier_opt", 
  "constant_initializer", "constant_initializer_opt", "base_clause_opt", 
  "base_clause", "base_specifier_list", "base_specifier", 
  "access_specifier", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   130,   130,   130,   130,   130,   130,   191,   192,   192,
     193,   194,   131,   195,   133,   132,   134,   135,   135,   135,
     196,   197,   197,   198,   198,   136,   136,   199,   199,   137,
     138,   139,   139,   140,   140,   141,   141,   142,   143,   144,
     145,   146,   147,   147,   148,   148,   148,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   150,   201,   200,   202,   202,   203,   203,   204,
     204,   205,   151,   151,   152,   152,   153,   154,   154,   155,
     155,   156,   156,   157,   157,   157,   158,   158,   159,   160,
     160,   161,   162,   206,   206,   207,   163,   208,   208,   164,
     164,   165,   165,   166,   166,   167,   167,   168,   168,   169,
     169,   169,   170,   170,   171,   171,   173,   172,   174,   175,
     176,   176,   177,   177,   179,   178,   209,   209,   180,   180,
     181,   181,   182,   183,   183,   184,   185,   185,   186,   186,
     187,   188,   188,   189,   210,   210,   190,   190,   190,   211,
     211,   212,   212,   213,   213,   214,   214
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     1,     1,     2,
       3,     1,     0,     1,     1,     1,     3,     1,     0,     1,
       1,     1,     0,     1,     2,     1,     0,     1,     1,     3,
       1,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     0,     1,
       3,     1,     1,     3,     1,     0,     2,     1,     2,     1,
       4,     1,     2,     1,     4,     4,     2,     1,     2,     1,
       0,     1,     1,     1,     0,     2,     1,     1,     0,     1,
       0,     1,     3,     2,     4,     2,     3,     1,     0,     1,
       4,     2,     1,     0,     1,     3,     0,     5,     3,     1,
       2,     3,     1,     0,     0,     4,     1,     0,     1,     3,
       2,     2,     2,     1,     0,     2,     1,     0,     1,     0,
       2,     1,     3,     2,     1,     0,     1,     1,     1,     1,
       0,     1,     0,     1,     0,     1,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      14,    43,    43,    15,    33,    37,    38,    42,    75,    34,
      52,    60,    54,    57,    51,    55,    58,    48,    61,   119,
      91,    59,    50,    49,    53,    56,    90,    87,     0,    17,
      12,    62,    92,    16,    41,    40,    44,    47,    74,     0,
      72,   108,    81,     0,    46,    83,    45,   116,     0,    89,
      86,    90,    19,     0,    39,     0,     0,   107,    76,    43,
      32,    18,    82,     0,     6,     1,     2,     3,     4,     5,
     139,    88,    73,    29,     0,    25,     0,   109,   105,    42,
       0,     0,    96,    99,   101,    30,    31,     0,   124,     0,
     118,   138,   106,     0,   111,   114,   113,   103,    77,     0,
      79,    62,    84,    43,    85,   148,   147,   146,   122,     0,
     124,    43,     0,   140,   141,     0,    26,   112,     0,     0,
      32,    78,   102,   117,   120,     0,   124,     0,   143,   115,
     110,   104,     0,   134,     0,   128,   121,   142,    80,     0,
     133,   130,   136,   131,     0,   125,    30,   135,   129,     0,
       0,     0
};

static const short yydefgoto[] =
{
      70,    61,   149,     1,    32,    33,    74,    77,    86,    87,
       2,     3,     4,     5,     6,    34,     7,     8,    35,    36,
      37,    38,    39,    40,    97,    98,    41,    42,    43,    49,
      50,    44,    45,    81,    82,    83,    84,    57,    58,    78,
     118,    96,    46,    63,    47,    48,   108,   109,   110,   111,
     134,   135,   140,   141,   142,   143,    90,    91,   113,   114,
     112
};

static const short yypact[] =
{
  -32768,    29,    44,-32768,-32768,-32768,-32768,-32768,    -6,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,    11,-32768,   -69,-32768,
  -32768,     1,-32768,-32768,-32768,-32768,-32768,-32768,   -26,   -15,
  -32768,   -22,   -48,   -31,-32768,-32768,-32768,-32768,   -14,-32768,
  -32768,    11,-32768,   -31,-32768,    13,   -42,-32768,-32768,    12,
      16,-32768,-32768,    -5,-32768,-32768,-32768,-32768,-32768,-32768,
     -13,-32768,-32768,-32768,   -50,-32768,    25,-32768,-32768,   -31,
       2,    21,-32768,    -1,-32768,-32768,-32768,    26,    27,    40,
  -32768,-32768,-32768,    13,-32768,-32768,     8,    19,    37,   -31,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    30,
      27,-32768,    22,    28,-32768,   -69,-32768,   -42,    42,    13,
      16,-32768,-32768,-32768,-32768,    -6,    27,    40,-32768,-32768,
  -32768,-32768,    45,    34,     6,-32768,-32768,-32768,-32768,    53,
  -32768,-32768,-32768,-32768,   -31,-32768,-32768,-32768,-32768,   125,
     126,-32768
};

static const short yypgoto[] =
{
  -32768,    -7,-32768,-32768,-32768,-32768,-32768,   -45,   -12,     9,
  -32768,-32768,   129,-32768,-32768,-32768,   -40,   -53,-32768,-32768,
  -32768,-32768,-32768,    75,    33,-32768,   -41,-32768,   -56,-32768,
      82,    -4,   -46,-32768,-32768,-32768,    31,-32768,-32768,   -62,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   -90,-32768,-32768,
  -32768,    -9,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    10,
     -71
};


#define	YYLAST		137


static const short yytable[] =
{
      10,    31,    62,    11,    12,    13,    80,    14,    10,    15,
      75,    11,    12,    13,    95,    14,    16,    15,   115,    79,
     124,    52,    51,    99,    16,    92,    59,    17,    73,   -36,
      60,    18,    19,   100,    76,    17,   136,    20,    21,    18,
      19,    22,    93,    99,   -35,    20,    21,    51,   116,    22,
      80,    26,    55,   100,    20,   129,   115,    27,   125,    30,
      23,    24,    25,    79,    28,    56,    53,   105,    23,    24,
      25,    88,   106,   101,   131,   -18,    26,   107,    54,   -18,
     105,    89,    27,    73,   133,   106,    85,  -100,   -18,    28,
     107,   103,    29,   -18,   -18,    73,   102,    30,   144,   145,
     117,    76,    94,   133,  -123,   104,   119,   123,   128,    64,
      65,    66,    67,    68,    69,   120,   126,    29,    31,   130,
     127,   139,    30,   146,   138,   150,   151,   147,    72,   132,
      30,     9,   121,    71,   122,   148,     0,   137
};

static const short yycheck[] =
{
       6,     8,    43,     9,    10,    11,    59,    13,     6,    15,
      55,     9,    10,    11,    76,    13,    22,    15,    89,    59,
     110,    28,    26,    79,    22,    75,    74,    33,    70,     0,
      78,    37,    38,    79,    76,    33,   126,    43,    44,    37,
      38,    47,    92,    99,     0,    43,    44,    51,    93,    47,
     103,    82,    74,    99,    43,   117,   127,    88,   111,   128,
      66,    67,    68,   103,    95,    87,    92,    40,    66,    67,
      68,    76,    45,    80,   119,    74,    82,    50,    93,    78,
      40,    94,    88,    70,   125,    45,    70,    75,    87,    95,
      50,    92,   123,    92,    93,    70,    75,   128,    92,    93,
      92,    76,    77,   144,    77,    79,    87,    77,   115,   123,
     124,   125,   126,   127,   128,    78,    94,   123,   125,    77,
      92,    87,   128,    70,    79,     0,     0,   139,    53,   120,
     128,     2,    99,    51,   103,   144,    -1,   127
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
#line 174 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 2:
#line 175 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 3:
#line 176 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 4:
#line 177 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 5:
#line 178 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 6:
#line 180 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 7:
#line 210 "cpp.y"
{/* $$ = $1; */;
    break;}
case 8:
#line 214 "cpp.y"
{/* $$ = $1; */;
    break;}
case 9:
#line 215 "cpp.y"
{/* $$ = $1; */;
    break;}
case 10:
#line 219 "cpp.y"
{/* $$ = $1; */;
    break;}
case 11:
#line 223 "cpp.y"
{/* $$ = $1; */;
    break;}
case 12:
#line 227 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 13:
#line 232 "cpp.y"
{/* $$ = $1; */;
    break;}
case 14:
#line 247 "cpp.y"
{  
   		translation_unit_start();
   	;
    break;}
case 15:
#line 251 "cpp.y"
{;
    break;}
case 16:
#line 269 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 17:
#line 275 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 18:
#line 276 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 19:
#line 279 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr; g_bdestructor_seen = true;;
    break;}
case 20:
#line 294 "cpp.y"
{/* $$ = nested_name_specifier( $1, false, $3 ); */;
    break;}
case 21:
#line 300 "cpp.y"
{/* $$ = $1; */;
    break;}
case 22:
#line 301 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 23:
#line 305 "cpp.y"
{/* $$ = $1; */;
    break;}
case 24:
#line 306 "cpp.y"
{/* $$ = class_or_namespace_name( $1 ); */;
    break;}
case 25:
#line 358 "cpp.y"
{/* $$ = expression_list_start( $1 ); */;
    break;}
case 26:
#line 360 "cpp.y"
{/* $$ = expression_list_continue( $1, $3 ); */;
    break;}
case 27:
#line 364 "cpp.y"
{/* $$ = $1; */;
    break;}
case 28:
#line 365 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 29:
#line 564 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);
  ;
    break;}
case 30:
#line 601 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);     
  ;
    break;}
case 31:
#line 608 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 32:
#line 609 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 33:
#line 720 "cpp.y"
{/* $$ = declaration_seq_1( $1 ); */;
    break;}
case 34:
#line 722 "cpp.y"
{/* $$ = declaration_seq_2( $2, $1 ); */;
    break;}
case 35:
#line 726 "cpp.y"
{/* $$ = $1; */;
    break;}
case 36:
#line 727 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 37:
#line 732 "cpp.y"
{/* $$ = $1; */;
    break;}
case 38:
#line 749 "cpp.y"
{/* $$ = $1; */;
    break;}
case 39:
#line 764 "cpp.y"
{/* $$ = simple_declaration( $1, $2 ); */;
    break;}
case 40:
#line 773 "cpp.y"
{/* $$ = decl_specifier_type( $1 ); */;
    break;}
case 41:
#line 784 "cpp.y"
{
      if (yyval.string_list_ptr == NULL) {yyval.string_list_ptr = new string_list;}
      yyval.string_list_ptr->push_back(yyvsp[0].string_ptr);
    ;
    break;}
case 42:
#line 792 "cpp.y"
{yyval.string_list_ptr = yyvsp[0].string_list_ptr;;
    break;}
case 43:
#line 794 "cpp.y"
{yyval.string_list_ptr = NULL;;
    break;}
case 44:
#line 822 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 45:
#line 824 "cpp.y"
{/* $$ = $1; */;
    break;}
case 46:
#line 830 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 47:
#line 838 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 48:
#line 843 "cpp.y"
{yyval.string_ptr = new string("char");;
    break;}
case 49:
#line 845 "cpp.y"
{yyval.string_ptr = new string("unsigned char");;
    break;}
case 50:
#line 847 "cpp.y"
{yyval.string_ptr = new string("wchar_t");;
    break;}
case 51:
#line 849 "cpp.y"
{yyval.string_ptr = new string("bool");;
    break;}
case 52:
#line 851 "cpp.y"
{yyval.string_ptr = new string("short");;
    break;}
case 53:
#line 853 "cpp.y"
{yyval.string_ptr = new string("unsigned short");;
    break;}
case 54:
#line 855 "cpp.y"
{yyval.string_ptr = new string("int");;
    break;}
case 55:
#line 857 "cpp.y"
{yyval.string_ptr = new string("long");;
    break;}
case 56:
#line 859 "cpp.y"
{yyval.string_ptr = new string("unsigned long");;
    break;}
case 57:
#line 861 "cpp.y"
{yyval.string_ptr = new string("signed");;
    break;}
case 58:
#line 863 "cpp.y"
{yyval.string_ptr = new string("unsigned");;
    break;}
case 59:
#line 865 "cpp.y"
{yyval.string_ptr = new string("float");;
    break;}
case 60:
#line 867 "cpp.y"
{yyval.string_ptr = new string("double");;
    break;}
case 61:
#line 869 "cpp.y"
{yyval.string_ptr = new string("void");;
    break;}
case 62:
#line 873 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 63:
#line 891 "cpp.y"
{/* enum_specifier_1($2,$1); */;
    break;}
case 64:
#line 893 "cpp.y"
{/* $$ = enum_specifier_2( $5 ); */;
    break;}
case 65:
#line 899 "cpp.y"
{/* $$ = enumerator_list_1( $1 ); */;
    break;}
case 66:
#line 901 "cpp.y"
{/* $$ = enumerator_list_2( $1, $3 ); */;
    break;}
case 67:
#line 905 "cpp.y"
{/* $$ = $1; */;
    break;}
case 68:
#line 906 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 69:
#line 911 "cpp.y"
{/* $$ = enumerator_definition( $1, NULL ); */;
    break;}
case 70:
#line 913 "cpp.y"
{/* $$ = enumerator_definition( $1, $3 ); */;
    break;}
case 71:
#line 917 "cpp.y"
{/* $$ = $1; */;
    break;}
case 72:
#line 1010 "cpp.y"
{/* $$ = init_declarator_list( $1, NULL ); */;
    break;}
case 73:
#line 1013 "cpp.y"
{/* $$ = init_declarator_list( $3, $1 ); */;
    break;}
case 74:
#line 1017 "cpp.y"
{/* $$ = $1; */;
    break;}
case 75:
#line 1018 "cpp.y"
{/* typedef_list.clear(); $$ = NULL; */;
    break;}
case 76:
#line 1023 "cpp.y"
{/* $$ = init_declarator( $1, $2 ); */;
    break;}
case 77:
#line 1028 "cpp.y"
{yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;;
    break;}
case 78:
#line 1031 "cpp.y"
{
      yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;
      yyval.param_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tcount);
    ;
    break;}
case 79:
#line 1039 "cpp.y"
{
      yyval.param_declarator_ptr = new param_declarator;
      yyval.param_declarator_ptr->decl_id = yyvsp[0].string_ptr->c_str();
    ;
    break;}
case 80:
#line 1044 "cpp.y"
{
      yyval.param_declarator_ptr = yyvsp[-3].param_declarator_ptr;
      if (yyvsp[-1].expression_ptr != 0)
	    {
	      yyval.param_declarator_ptr->arr_dim.push_back(yyvsp[-1].expression_ptr);
	    }
    ;
    break;}
case 81:
#line 1055 "cpp.y"
{yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;;
    break;}
case 82:
#line 1058 "cpp.y"
{
        yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;
        yyval.member_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tcount);
    ;
    break;}
case 83:
#line 1066 "cpp.y"
{
        yyval.member_declarator_ptr = new member_declarator;
		yyval.member_declarator_ptr->method = false;
        yyval.member_declarator_ptr->declarator_id = yyvsp[0].string_ptr;
    ;
    break;}
case 84:
#line 1076 "cpp.y"
{
        yyval.member_declarator_ptr->params = yyvsp[-1].param_decl_list_ptr;
        yyval.member_declarator_ptr->method = true;
    ;
    break;}
case 85:
#line 1081 "cpp.y"
{
        yyval.member_declarator_ptr->array_indexes.push_back(yyvsp[-1].expression_ptr);
    ;
    break;}
case 86:
#line 1090 "cpp.y"
{yyval.tcount = STAR;;
    break;}
case 87:
#line 1092 "cpp.y"
{yyval.tcount = AND;;
    break;}
case 88:
#line 1098 "cpp.y"
{/* $$ = $1 + $2; */;
    break;}
case 89:
#line 1102 "cpp.y"
{/* $$ = $1; */;
    break;}
case 90:
#line 1103 "cpp.y"
{/* $$ = 0; */;
    break;}
case 91:
#line 1108 "cpp.y"
{
  /* seen_const = true;
     $$ = 1;*/
;
    break;}
case 92:
#line 1121 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 93:
#line 1132 "cpp.y"
{/* $$ = $1; */;
    break;}
case 94:
#line 1133 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 95:
#line 1138 "cpp.y"
{/* $$ = ($1 != NULL ? $1 : $2); */;
    break;}
case 96:
#line 1174 "cpp.y"
{yyval.param_decl_list_ptr = yyvsp[0].param_decl_list_ptr;;
    break;}
case 97:
#line 1180 "cpp.y"
{;
    break;}
case 98:
#line 1181 "cpp.y"
{;
    break;}
case 99:
#line 1185 "cpp.y"
{/* $$ = $1; */;
    break;}
case 100:
#line 1186 "cpp.y"
{yyval.param_decl_list_ptr = NULL;;
    break;}
case 101:
#line 1191 "cpp.y"
{ 
      yyval.param_decl_list_ptr = new param_decl_list;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 102:
#line 1196 "cpp.y"
{
      yyval.param_decl_list_ptr = yyvsp[-2].param_decl_list_ptr;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 103:
#line 1204 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-1].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[0].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = false; 
    ;
    break;}
case 104:
#line 1211 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-3].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[-2].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = true;
      yyval.param_decl_ptr->defval = yyvsp[0].expression_ptr;
    ;
    break;}
case 105:
#line 1245 "cpp.y"
{/* $$ = $2; */;
    break;}
case 106:
#line 1247 "cpp.y"
{/* $$ = $2; */;
    break;}
case 107:
#line 1252 "cpp.y"
{/* $$ = $1; */;
    break;}
case 108:
#line 1253 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 109:
#line 1257 "cpp.y"
{/* $$ = $1; */;
    break;}
case 110:
#line 1259 "cpp.y"
{/* $$ = $3; */;
    break;}
case 111:
#line 1260 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 112:
#line 1264 "cpp.y"
{/* $$ = 1; */;
    break;}
case 113:
#line 1265 "cpp.y"
{/* $$ = 0; */;
    break;}
case 114:
#line 1270 "cpp.y"
{/* $$ = initializer_list( $1, NULL ); */;
    break;}
case 115:
#line 1272 "cpp.y"
{/* $$ = initializer_list( $3, $1 ); */;
    break;}
case 116:
#line 1279 "cpp.y"
{
      //check if this class should be wrapped or not depending on wsdd information
      if (is_bean_class(yyvsp[0].class_head_ptr->baselist)) //bean class
      {
				BeanClass* pBeanClass = new BeanClass();
				pBeanClass->SetClassName(*(yyvsp[0].class_head_ptr->class_name));
				g_pTranslationUnit->AddBeanClass(pBeanClass);
				g_pCurrentBeanClass = pBeanClass;
				g_currentclasstype = BEANCLASS;
      }
      else // we assume that this is the webservice class - there cannot be 2 web service classes
      {
				WSClass* pWSClass = new WSClass();
				pWSClass->SetClassName(*(yyvsp[0].class_head_ptr->class_name));
				g_pTranslationUnit->SetWSClass(pWSClass);
				g_pCurrentWSClass = pWSClass;
				g_currentclasstype = WSCLASS;
      }   
  		g_classesfound.push_back(g_classname);
  	;
    break;}
case 117:
#line 1300 "cpp.y"
{
			g_classname = ""; //end of class scope
   	;
    break;}
case 118:
#line 1308 "cpp.y"
{
    	g_classname = yyvsp[-1].string_ptr->c_str();
    	yyval.class_head_ptr = new class_head;
     	yyval.class_head_ptr->class_name = yyvsp[-1].string_ptr;
			yyval.class_head_ptr->baselist = yyvsp[0].inhcont; //may be NULL
    ;
    break;}
case 119:
#line 1323 "cpp.y"
{/* next_access = Access::Private; $$ = AT_CLASS; */;
    break;}
case 120:
#line 1331 "cpp.y"
{;
    break;}
case 121:
#line 1334 "cpp.y"
{;
    break;}
case 122:
#line 1338 "cpp.y"
{;
    break;}
case 123:
#line 1339 "cpp.y"
{;
    break;}
case 124:
#line 1343 "cpp.y"
{ g_bdestructor_seen = false;;
    break;}
case 125:
#line 1347 "cpp.y"
{
      add_member_declaration(yyvsp[-2].string_list_ptr, yyvsp[-1].member_declarator_list_ptr);
    ;
    break;}
case 128:
#line 1368 "cpp.y"
{
      yyval.member_declarator_list_ptr = new member_declarator_list;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 129:
#line 1373 "cpp.y"
{
      yyval.member_declarator_list_ptr = yyvsp[-2].member_declarator_list_ptr;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 130:
#line 1386 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[-1].member_declarator_ptr != 0) //there is a pure specifier
      {
        yyval.member_declarator_ptr->bpure = true;  
      }
    ;
    break;}
case 131:
#line 1394 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[0].expression_ptr != NULL)
      {
        yyval.member_declarator_ptr->expr = yyvsp[0].expression_ptr;
      }
    ;
    break;}
case 132:
#line 1407 "cpp.y"
{yyval.tcount = 1;;
    break;}
case 133:
#line 1411 "cpp.y"
{yyval.tcount = yyvsp[0].tcount;;
    break;}
case 134:
#line 1412 "cpp.y"
{yyval.tcount = 0;;
    break;}
case 135:
#line 1417 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 136:
#line 1421 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 137:
#line 1422 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 138:
#line 1427 "cpp.y"
{yyval.inhcont = yyvsp[0].inhcont;;
    break;}
case 139:
#line 1428 "cpp.y"
{yyval.inhcont = NULL;;
    break;}
case 140:
#line 1432 "cpp.y"
{yyval.inhcont = yyvsp[0].inhcont;;
    break;}
case 141:
#line 1437 "cpp.y"
{
    	yyval.inhcont = new base_specifier_list;
     	yyval.inhcont->push_back(yyvsp[0].bclass);
    ;
    break;}
case 142:
#line 1442 "cpp.y"
{
    	yyval.inhcont->push_back(yyvsp[0].bclass);
    ;
    break;}
case 143:
#line 1458 "cpp.y"
{
    	yyval.bclass = new base_specifier;
     	yyval.bclass->access = yyvsp[-1].tcount;
      yyval.bclass->class_name = yyvsp[0].string_ptr;
    ;
    break;}
case 144:
#line 1466 "cpp.y"
{/*$$ = 1; */;
    break;}
case 145:
#line 1467 "cpp.y"
{/* $$ = 0; */;
    break;}
case 146:
#line 1472 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 147:
#line 1474 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 148:
#line 1476 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 149:
#line 1481 "cpp.y"
{yyval.tcount=yyvsp[0].tcount;;
    break;}
case 150:
#line 1482 "cpp.y"
{yyval.tcount = 0;;
    break;}
case 151:
#line 1535 "cpp.y"
{/* $$ = 1; */;
    break;}
case 152:
#line 1536 "cpp.y"
{/* $$ = 0; */;
    break;}
case 153:
#line 1657 "cpp.y"
{ /*$$ = $1;*/;
    break;}
case 154:
#line 1658 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 155:
#line 1744 "cpp.y"
{/* $$ = $1; */;
    break;}
case 156:
#line 1745 "cpp.y"
{/* $$ = NULL; */;
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
#line 1800 "cpp.y"

/*
string
makeOperatorName( int op ) {
  switch( op ) {
  case PLUS: return string("operator+");
  case MINUS: return string("operator-");
  case STAR: return string("operator*");
  case DIVIDE: return string("operator/");
  case MOD: return string("operator%");
  case GREATER: return string("operator>");
  case LESS: return string("operator<");
  case EQUAL: return string("operator=");
  case AND: return string("operator&");
  case OR: return string("operator|");
  case NOT: return string("operator!");
  case XOR: return string("operator^");
  case COMMA: return string("operator,");
  case COMPLEMENT: return string("operator~");
  case PLUSEQ: return string("operator+=");
  case MINUSEQ: return string("operator-=");
  case STAREQ: return string("operator*=");
  case DIVEQ: return string("operator/=");
  case MODEQ: return string("operator%=");
  case XOREQ: return string("operator^=");
  case ANDEQ: return string("operator&=");
  case OREQ: return string("operator|=");
  case LTLT: return string("operator<<");
  case GTGT: return string("operator>>");
  case GTGTEQ: return string("operator>>=");
  case LTLTEQ: return string("operator<<=");
  case EQEQ: return string("operator==");
  case NOTEQ: return string("operator!=");
  case LEQ: return string("operator>=");
  case ANDAND: return string("operator||");
  case PLUSPLUS: return string("operator++");
  case MINUSMINUS: return string("operator--");
  case ARROW: return string("operator->");
  }
  return string("");
}

NameDeclaration *
checkAnon(NameDeclaration *decl, int line)
{
  if (decl == NULL)
    return facade.makeAnonIdent(line,0); 
  return decl;
}

NameDeclaration *
checkAnonParm(NameDeclaration* decl, int line, int parm_num ) {
  if( decl == NULL )
    return facade.makeAnonParmIdent(line,0,parm_num);
  return decl;
}

NameDeclaration *
checkAnonNS(NameDeclaration *decl, int line)
{
  if (decl == NULL)
    return facade.makeAnonNSIdent(line,0); 
  return decl;
}

NameDeclaration *
checkBinOp(int op, NameDeclaration *d1, NameDeclaration *d2)
{
  string s = makeOperatorName(op);
  return facade.lookupBinOp( &s, d1, d2 );
}

NameDeclaration *
checkUnaryOp(int op, NameDeclaration *d)
{
  string s = makeOperatorName(op);
  return facade.lookupUnaryOp(&s, d);
}
*/

