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
# define	ID_original_namespace_name	380
# define	ID_namespace_alias	381
# define	ID_enum_name	382
# define	ID_class_name	383
# define	ID_template_name	384

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



#define	YYFINAL		152
#define	YYFLAG		-32768
#define	YYNTBASE	131

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 384 ? yytranslate[x] : 192)

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
     126,   127,   128,   129,   130
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
     122,   124,   126,   128,   130,   131,   138,   140,   144,   146,
     147,   149,   153,   155,   157,   161,   163,   164,   167,   169,
     172,   174,   179,   181,   184,   186,   191,   196,   199,   201,
     204,   206,   207,   209,   211,   213,   214,   217,   219,   221,
     222,   224,   225,   227,   231,   234,   239,   242,   246,   248,
     249,   251,   256,   259,   261,   262,   264,   268,   269,   275,
     279,   281,   284,   288,   290,   291,   292,   297,   299,   300,
     302,   306,   309,   312,   315,   317,   318,   321,   323,   324,
     326,   327,   330,   332,   336,   339,   341,   342,   344,   346,
     348,   350,   351,   353,   354,   356,   357,   359
};
static const short yyrhs[] =
{
     125,     0,   126,     0,   127,     0,   128,     0,   129,     0,
     124,     0,   125,     0,   194,     0,   195,     0,   126,     0,
     127,     0,   129,     0,   128,     0,     0,   134,   142,     0,
     136,     0,   124,     0,   132,     0,    96,   132,     0,   199,
      99,   198,     0,   197,     0,     0,   132,     0,   193,     0,
     138,     0,   137,    93,   138,     0,   137,     0,     0,    71,
       0,    71,     0,   139,     0,     0,   143,     0,   141,   143,
       0,   141,     0,     0,   144,     0,   145,     0,   148,   153,
      94,     0,   149,     0,   148,   146,     0,   147,     0,     0,
     150,     0,   173,     0,   162,     0,   151,     0,    33,     0,
      67,     0,    47,     0,    13,     0,     6,     0,    68,     0,
      10,     0,    15,     0,    69,     0,    11,     0,    22,     0,
      44,     0,     9,     0,    37,     0,    66,     0,   132,     0,
       0,    24,   214,   202,    77,   204,    78,     0,   205,     0,
     203,    93,   205,     0,   203,     0,     0,   206,     0,   206,
      88,   139,     0,   131,     0,   154,     0,   152,    93,   154,
       0,   152,     0,     0,   157,   169,     0,   156,     0,   159,
     155,     0,   163,     0,   156,    79,   140,    80,     0,   158,
       0,   159,   157,     0,   163,     0,   158,    75,   164,    76,
       0,   158,    79,   140,    80,     0,    83,   161,     0,    89,
       0,   162,   161,     0,   160,     0,     0,    43,     0,   135,
       0,   208,     0,     0,   149,   207,     0,   165,     0,   100,
       0,     0,   166,     0,     0,   167,     0,   166,    93,   167,
       0,   147,   155,     0,   147,   155,    88,   138,     0,    88,
     170,     0,    75,   137,    76,     0,   168,     0,     0,   138,
       0,    77,   172,   171,    78,     0,    77,    78,     0,    93,
       0,     0,   170,     0,   172,    93,   170,     0,     0,   175,
     174,    77,   178,    78,     0,   176,   131,   187,     0,    38,
       0,   179,   178,     0,   191,    95,   178,     0,   177,     0,
       0,     0,   180,   148,   181,    94,     0,    94,     0,     0,
     182,     0,   181,    93,   182,     0,   157,   184,     0,   157,
     186,     0,    88,    71,     0,   183,     0,     0,    88,   139,
       0,   185,     0,     0,   188,     0,     0,    95,   189,     0,
     190,     0,   189,    93,   190,     0,   191,   132,     0,    32,
       0,     0,    50,     0,    45,     0,    40,     0,   191,     0,
       0,    99,     0,     0,   131,     0,     0,   138,     0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   175,   176,   177,   178,   179,   181,   211,   215,   216,
     220,   224,   228,   233,   248,   248,   270,   276,   277,   280,
     294,   301,   302,   306,   307,   358,   360,   365,   366,   564,
     601,   609,   610,   720,   722,   727,   728,   732,   749,   762,
     769,   784,   792,   794,   822,   824,   830,   836,   843,   845,
     847,   849,   851,   853,   855,   857,   859,   861,   863,   865,
     867,   869,   871,   876,   893,   893,   901,   903,   908,   909,
     913,   915,   920,  1012,  1014,  1020,  1021,  1025,  1030,  1032,
    1041,  1046,  1057,  1059,  1068,  1074,  1083,  1092,  1094,  1101,
    1105,  1106,  1110,  1123,  1135,  1136,  1140,  1175,  1183,  1184,
    1188,  1189,  1193,  1198,  1206,  1213,  1247,  1249,  1254,  1256,
    1260,  1261,  1263,  1267,  1268,  1272,  1274,  1280,  1280,  1309,
    1326,  1333,  1335,  1341,  1342,  1346,  1346,  1365,  1366,  1370,
    1375,  1388,  1396,  1409,  1414,  1415,  1419,  1424,  1425,  1430,
    1431,  1435,  1439,  1444,  1451,  1469,  1470,  1474,  1476,  1478,
    1483,  1485,  1538,  1539,  1659,  1661,  1747,  1748
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
       0,   131,   131,   131,   131,   131,   131,   192,   193,   193,
     194,   195,   132,   196,   134,   133,   135,   136,   136,   136,
     197,   198,   198,   199,   199,   137,   137,   200,   200,   138,
     139,   140,   140,   141,   141,   142,   142,   143,   144,   145,
     146,   147,   148,   148,   149,   149,   149,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   202,   201,   203,   203,   204,   204,
     205,   205,   206,   152,   152,   153,   153,   154,   155,   155,
     156,   156,   157,   157,   158,   158,   158,   159,   159,   160,
     161,   161,   162,   163,   207,   207,   208,   164,   209,   209,
     165,   165,   166,   166,   167,   167,   168,   168,   169,   169,
     170,   170,   170,   171,   171,   172,   172,   174,   173,   175,
     176,   177,   177,   178,   178,   180,   179,   210,   210,   181,
     181,   182,   182,   183,   184,   184,   185,   186,   186,   187,
     187,   188,   189,   189,   190,   211,   211,   191,   191,   191,
     212,   212,   213,   213,   214,   214,   215,   215
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
       1,     1,     1,     1,     0,     6,     1,     3,     1,     0,
       1,     3,     1,     1,     3,     1,     0,     2,     1,     2,
       1,     4,     1,     2,     1,     4,     4,     2,     1,     2,
       1,     0,     1,     1,     1,     0,     2,     1,     1,     0,
       1,     0,     1,     3,     2,     4,     2,     3,     1,     0,
       1,     4,     2,     1,     0,     1,     3,     0,     5,     3,
       1,     2,     3,     1,     0,     0,     4,     1,     0,     1,
       3,     2,     2,     2,     1,     0,     2,     1,     0,     1,
       0,     2,     1,     3,     2,     1,     0,     1,     1,     1,
       1,     0,     1,     0,     1,     0,     1,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      14,    43,    43,    15,    33,    37,    38,    42,    76,    34,
      52,    60,    54,    57,    51,    55,    58,    48,    61,   120,
      92,    59,    50,    62,    49,    53,    56,    91,    88,     0,
      17,    12,    63,    93,    16,    41,    40,    44,    47,    75,
       0,    73,   109,    82,     0,    46,    84,    45,   117,     0,
      90,    87,    91,    19,     0,    39,     0,     0,   108,    77,
      43,    32,    18,    83,     0,     6,     1,     2,     3,     4,
       5,   140,    89,    74,    29,     0,    25,     0,   110,   106,
      42,     0,     0,    97,   100,   102,    30,    31,     0,   125,
       0,   119,   139,   107,     0,   112,   115,   114,   104,    78,
       0,    80,    63,    85,    43,    86,   149,   148,   147,   123,
       0,   125,    43,     0,   141,   142,     0,    26,   113,     0,
       0,    32,    79,   103,   118,   121,     0,   125,     0,   144,
     116,   111,   105,     0,   135,     0,   129,   122,   143,    81,
       0,   134,   131,   137,   132,     0,   126,    30,   136,   130,
       0,     0,     0
};

static const short yydefgoto[] =
{
      71,    62,   150,     1,    33,    34,    75,    78,    87,    88,
       2,     3,     4,     5,     6,    35,     7,     8,    36,    37,
      38,    39,    40,    41,    98,    99,    42,    43,    44,    50,
      51,    45,    46,    82,    83,    84,    85,    58,    59,    79,
     119,    97,    47,    64,    48,    49,   109,   110,   111,   112,
     135,   136,   141,   142,   143,   144,    91,    92,   114,   115,
     113
};

static const short yypact[] =
{
  -32768,    29,    34,-32768,-32768,-32768,-32768,-32768,    -6,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,    23,-32768,   -56,
  -32768,-32768,     0,-32768,-32768,-32768,-32768,-32768,-32768,    -4,
     -18,-32768,   -10,   -49,   -32,-32768,-32768,-32768,-32768,   -14,
  -32768,-32768,    23,-32768,   -32,-32768,    24,    14,-32768,-32768,
      20,    30,-32768,-32768,    25,-32768,-32768,-32768,-32768,-32768,
  -32768,    10,-32768,-32768,-32768,   -51,-32768,     9,-32768,-32768,
     -32,     2,    28,-32768,     7,-32768,-32768,-32768,    26,     3,
     -17,-32768,-32768,-32768,    24,-32768,-32768,    15,    19,    37,
     -32,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
      39,     3,-32768,    27,    31,-32768,   -56,-32768,    14,    42,
      24,    30,-32768,-32768,-32768,-32768,    -6,     3,   -17,-32768,
  -32768,-32768,-32768,    41,    38,     5,-32768,-32768,-32768,-32768,
      54,-32768,-32768,-32768,-32768,   -32,-32768,-32768,-32768,-32768,
     127,   128,-32768
};

static const short yypgoto[] =
{
  -32768,    -7,-32768,-32768,-32768,-32768,-32768,   -38,   -11,    11,
  -32768,-32768,   131,-32768,-32768,-32768,   -50,   -54,-32768,-32768,
  -32768,-32768,-32768,    76,    35,-32768,   -42,-32768,   -33,-32768,
      82,    -8,   -28,-32768,-32768,-32768,    32,-32768,-32768,   -63,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   -91,-32768,-32768,
  -32768,    -5,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    13,
     -69
};


#define	YYLAST		141


static const short yytable[] =
{
      10,    32,    63,    11,    12,    13,    81,    14,    10,    15,
      80,    11,    12,    13,    96,    14,    16,    15,    76,    52,
     125,   116,    53,   106,    16,    93,    60,    17,   107,   -36,
      61,    18,    19,   108,   -35,    17,   137,    20,    21,    18,
      19,    22,    94,   106,    52,    20,    21,   100,   107,    22,
      81,    27,   101,   108,    80,   130,   117,    28,   126,   116,
      23,    24,    25,    26,    29,    56,    20,   100,    23,    24,
      25,    26,   101,    31,   102,   -18,    55,    27,    57,   -18,
      74,  -124,   132,    28,   134,    74,    77,    95,   -18,    54,
      29,    77,    30,   -18,   -18,    74,  -101,    31,   145,   146,
     104,    86,    89,   134,   103,    90,   105,   120,   118,   129,
      65,    66,    67,    68,    69,    70,   121,   124,    30,    32,
     131,   139,   127,    31,   128,   147,   140,   151,   152,   148,
      73,    31,   133,     9,    72,   122,   123,     0,     0,     0,
     149,   138
};

static const short yycheck[] =
{
       6,     8,    44,     9,    10,    11,    60,    13,     6,    15,
      60,     9,    10,    11,    77,    13,    22,    15,    56,    27,
     111,    90,    29,    40,    22,    76,    75,    33,    45,     0,
      79,    37,    38,    50,     0,    33,   127,    43,    44,    37,
      38,    47,    93,    40,    52,    43,    44,    80,    45,    47,
     104,    83,    80,    50,   104,   118,    94,    89,   112,   128,
      66,    67,    68,    69,    96,    75,    43,   100,    66,    67,
      68,    69,   100,   129,    81,    75,    94,    83,    88,    79,
      71,    78,   120,    89,   126,    71,    77,    78,    88,    93,
      96,    77,   124,    93,    94,    71,    76,   129,    93,    94,
      93,    71,    77,   145,    76,    95,    80,    88,    93,   116,
     124,   125,   126,   127,   128,   129,    79,    78,   124,   126,
      78,    80,    95,   129,    93,    71,    88,     0,     0,   140,
      54,   129,   121,     2,    52,   100,   104,    -1,    -1,    -1,
     145,   128
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
#line 175 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 2:
#line 176 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 3:
#line 177 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 4:
#line 178 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 5:
#line 179 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 6:
#line 181 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 7:
#line 211 "cpp.y"
{/* $$ = $1; */;
    break;}
case 8:
#line 215 "cpp.y"
{/* $$ = $1; */;
    break;}
case 9:
#line 216 "cpp.y"
{/* $$ = $1; */;
    break;}
case 10:
#line 220 "cpp.y"
{/* $$ = $1; */;
    break;}
case 11:
#line 224 "cpp.y"
{/* $$ = $1; */;
    break;}
case 12:
#line 228 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 13:
#line 233 "cpp.y"
{/* $$ = $1; */;
    break;}
case 14:
#line 248 "cpp.y"
{  
   		translation_unit_start();
   	;
    break;}
case 15:
#line 252 "cpp.y"
{;
    break;}
case 16:
#line 270 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 17:
#line 276 "cpp.y"
{yyval.string_ptr = new string(yytext);;
    break;}
case 18:
#line 277 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 19:
#line 280 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr; g_bdestructor_seen = true;;
    break;}
case 20:
#line 295 "cpp.y"
{/* $$ = nested_name_specifier( $1, false, $3 ); */;
    break;}
case 21:
#line 301 "cpp.y"
{/* $$ = $1; */;
    break;}
case 22:
#line 302 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 23:
#line 306 "cpp.y"
{/* $$ = $1; */;
    break;}
case 24:
#line 307 "cpp.y"
{/* $$ = class_or_namespace_name( $1 ); */;
    break;}
case 25:
#line 359 "cpp.y"
{/* $$ = expression_list_start( $1 ); */;
    break;}
case 26:
#line 361 "cpp.y"
{/* $$ = expression_list_continue( $1, $3 ); */;
    break;}
case 27:
#line 365 "cpp.y"
{/* $$ = $1; */;
    break;}
case 28:
#line 366 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 29:
#line 565 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);
  ;
    break;}
case 30:
#line 602 "cpp.y"
{
    yyval.expression_ptr = new expression;
    yyval.expression_ptr->expr.n = atoi(yytext);     
  ;
    break;}
case 31:
#line 609 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 32:
#line 610 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 33:
#line 721 "cpp.y"
{/* $$ = declaration_seq_1( $1 ); */;
    break;}
case 34:
#line 723 "cpp.y"
{/* $$ = declaration_seq_2( $2, $1 ); */;
    break;}
case 35:
#line 727 "cpp.y"
{/* $$ = $1; */;
    break;}
case 36:
#line 728 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 37:
#line 733 "cpp.y"
{/* $$ = $1; */;
    break;}
case 38:
#line 750 "cpp.y"
{/* $$ = $1; */;
    break;}
case 39:
#line 765 "cpp.y"
{/* $$ = simple_declaration( $1, $2 ); */;
    break;}
case 40:
#line 774 "cpp.y"
{/* $$ = decl_specifier_type( $1 ); */;
    break;}
case 41:
#line 785 "cpp.y"
{
      if (yyval.string_list_ptr == NULL) {yyval.string_list_ptr = new string_list;}
      yyval.string_list_ptr->push_back(yyvsp[0].string_ptr);
    ;
    break;}
case 42:
#line 793 "cpp.y"
{yyval.string_list_ptr = yyvsp[0].string_list_ptr;;
    break;}
case 43:
#line 795 "cpp.y"
{yyval.string_list_ptr = NULL;;
    break;}
case 44:
#line 823 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 45:
#line 825 "cpp.y"
{/* $$ = $1; */;
    break;}
case 46:
#line 831 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 47:
#line 839 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 48:
#line 844 "cpp.y"
{yyval.string_ptr = new string("char");;
    break;}
case 49:
#line 846 "cpp.y"
{yyval.string_ptr = new string("unsigned char");;
    break;}
case 50:
#line 848 "cpp.y"
{yyval.string_ptr = new string("wchar_t");;
    break;}
case 51:
#line 850 "cpp.y"
{yyval.string_ptr = new string("bool");;
    break;}
case 52:
#line 852 "cpp.y"
{yyval.string_ptr = new string("short");;
    break;}
case 53:
#line 854 "cpp.y"
{yyval.string_ptr = new string("unsigned short");;
    break;}
case 54:
#line 856 "cpp.y"
{yyval.string_ptr = new string("int");;
    break;}
case 55:
#line 858 "cpp.y"
{yyval.string_ptr = new string("long");;
    break;}
case 56:
#line 860 "cpp.y"
{yyval.string_ptr = new string("unsigned long");;
    break;}
case 57:
#line 862 "cpp.y"
{yyval.string_ptr = new string("signed");;
    break;}
case 58:
#line 864 "cpp.y"
{yyval.string_ptr = new string("unsigned");;
    break;}
case 59:
#line 866 "cpp.y"
{yyval.string_ptr = new string("float");;
    break;}
case 60:
#line 868 "cpp.y"
{yyval.string_ptr = new string("double");;
    break;}
case 61:
#line 870 "cpp.y"
{yyval.string_ptr = new string("void");;
    break;}
case 62:
#line 872 "cpp.y"
{yyval.string_ptr = new string("string");;
    break;}
case 63:
#line 876 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 64:
#line 894 "cpp.y"
{/* enum_specifier_1($2,$1); */;
    break;}
case 65:
#line 896 "cpp.y"
{/* $$ = enum_specifier_2( $5 ); */;
    break;}
case 66:
#line 902 "cpp.y"
{/* $$ = enumerator_list_1( $1 ); */;
    break;}
case 67:
#line 904 "cpp.y"
{/* $$ = enumerator_list_2( $1, $3 ); */;
    break;}
case 68:
#line 908 "cpp.y"
{/* $$ = $1; */;
    break;}
case 69:
#line 909 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 70:
#line 914 "cpp.y"
{/* $$ = enumerator_definition( $1, NULL ); */;
    break;}
case 71:
#line 916 "cpp.y"
{/* $$ = enumerator_definition( $1, $3 ); */;
    break;}
case 72:
#line 920 "cpp.y"
{/* $$ = $1; */;
    break;}
case 73:
#line 1013 "cpp.y"
{/* $$ = init_declarator_list( $1, NULL ); */;
    break;}
case 74:
#line 1016 "cpp.y"
{/* $$ = init_declarator_list( $3, $1 ); */;
    break;}
case 75:
#line 1020 "cpp.y"
{/* $$ = $1; */;
    break;}
case 76:
#line 1021 "cpp.y"
{/* typedef_list.clear(); $$ = NULL; */;
    break;}
case 77:
#line 1026 "cpp.y"
{/* $$ = init_declarator( $1, $2 ); */;
    break;}
case 78:
#line 1031 "cpp.y"
{yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;;
    break;}
case 79:
#line 1034 "cpp.y"
{
      yyval.param_declarator_ptr=yyvsp[0].param_declarator_ptr;
      yyval.param_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tcount);
    ;
    break;}
case 80:
#line 1042 "cpp.y"
{
      yyval.param_declarator_ptr = new param_declarator;
      yyval.param_declarator_ptr->decl_id = yyvsp[0].string_ptr->c_str();
    ;
    break;}
case 81:
#line 1047 "cpp.y"
{
      yyval.param_declarator_ptr = yyvsp[-3].param_declarator_ptr;
      if (yyvsp[-1].expression_ptr != 0)
	    {
	      yyval.param_declarator_ptr->arr_dim.push_back(yyvsp[-1].expression_ptr);
	    }
    ;
    break;}
case 82:
#line 1058 "cpp.y"
{yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;;
    break;}
case 83:
#line 1061 "cpp.y"
{
        yyval.member_declarator_ptr = yyvsp[0].member_declarator_ptr;
        yyval.member_declarator_ptr->ptr_ops.push_back(yyvsp[-1].tcount);
    ;
    break;}
case 84:
#line 1069 "cpp.y"
{
        yyval.member_declarator_ptr = new member_declarator;
		yyval.member_declarator_ptr->method = false;
        yyval.member_declarator_ptr->declarator_id = yyvsp[0].string_ptr;
    ;
    break;}
case 85:
#line 1079 "cpp.y"
{
        yyval.member_declarator_ptr->params = yyvsp[-1].param_decl_list_ptr;
        yyval.member_declarator_ptr->method = true;
    ;
    break;}
case 86:
#line 1084 "cpp.y"
{
        yyval.member_declarator_ptr->array_indexes.push_back(yyvsp[-1].expression_ptr);
    ;
    break;}
case 87:
#line 1093 "cpp.y"
{yyval.tcount = STAR;;
    break;}
case 88:
#line 1095 "cpp.y"
{yyval.tcount = AND;;
    break;}
case 89:
#line 1101 "cpp.y"
{/* $$ = $1 + $2; */;
    break;}
case 90:
#line 1105 "cpp.y"
{/* $$ = $1; */;
    break;}
case 91:
#line 1106 "cpp.y"
{/* $$ = 0; */;
    break;}
case 92:
#line 1111 "cpp.y"
{
  /* seen_const = true;
     $$ = 1;*/
;
    break;}
case 93:
#line 1124 "cpp.y"
{yyval.string_ptr = yyvsp[0].string_ptr;;
    break;}
case 94:
#line 1135 "cpp.y"
{/* $$ = $1; */;
    break;}
case 95:
#line 1136 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 96:
#line 1141 "cpp.y"
{/* $$ = ($1 != NULL ? $1 : $2); */;
    break;}
case 97:
#line 1177 "cpp.y"
{yyval.param_decl_list_ptr = yyvsp[0].param_decl_list_ptr;;
    break;}
case 98:
#line 1183 "cpp.y"
{;
    break;}
case 99:
#line 1184 "cpp.y"
{;
    break;}
case 100:
#line 1188 "cpp.y"
{/* $$ = $1; */;
    break;}
case 101:
#line 1189 "cpp.y"
{yyval.param_decl_list_ptr = NULL;;
    break;}
case 102:
#line 1194 "cpp.y"
{ 
      yyval.param_decl_list_ptr = new param_decl_list;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 103:
#line 1199 "cpp.y"
{
      yyval.param_decl_list_ptr = yyvsp[-2].param_decl_list_ptr;
      yyval.param_decl_list_ptr->push_back(yyvsp[0].param_decl_ptr);
    ;
    break;}
case 104:
#line 1207 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-1].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[0].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = false; 
    ;
    break;}
case 105:
#line 1214 "cpp.y"
{
      yyval.param_decl_ptr = new param_decl;
      yyval.param_decl_ptr->decl_specs = yyvsp[-3].string_list_ptr;
      yyval.param_decl_ptr->param = yyvsp[-2].param_declarator_ptr;
      yyval.param_decl_ptr->bdef = true;
      yyval.param_decl_ptr->defval = yyvsp[0].expression_ptr;
    ;
    break;}
case 106:
#line 1248 "cpp.y"
{/* $$ = $2; */;
    break;}
case 107:
#line 1250 "cpp.y"
{/* $$ = $2; */;
    break;}
case 108:
#line 1255 "cpp.y"
{/* $$ = $1; */;
    break;}
case 109:
#line 1256 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 110:
#line 1260 "cpp.y"
{/* $$ = $1; */;
    break;}
case 111:
#line 1262 "cpp.y"
{/* $$ = $3; */;
    break;}
case 112:
#line 1263 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 113:
#line 1267 "cpp.y"
{/* $$ = 1; */;
    break;}
case 114:
#line 1268 "cpp.y"
{/* $$ = 0; */;
    break;}
case 115:
#line 1273 "cpp.y"
{/* $$ = initializer_list( $1, NULL ); */;
    break;}
case 116:
#line 1275 "cpp.y"
{/* $$ = initializer_list( $3, $1 ); */;
    break;}
case 117:
#line 1282 "cpp.y"
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
case 118:
#line 1303 "cpp.y"
{
			g_classname = ""; //end of class scope
   	;
    break;}
case 119:
#line 1311 "cpp.y"
{
    	g_classname = yyvsp[-1].string_ptr->c_str();
    	yyval.class_head_ptr = new class_head;
     	yyval.class_head_ptr->class_name = yyvsp[-1].string_ptr;
			yyval.class_head_ptr->baselist = yyvsp[0].inhcont; //may be NULL
    ;
    break;}
case 120:
#line 1326 "cpp.y"
{/* next_access = Access::Private; $$ = AT_CLASS; */;
    break;}
case 121:
#line 1334 "cpp.y"
{;
    break;}
case 122:
#line 1337 "cpp.y"
{;
    break;}
case 123:
#line 1341 "cpp.y"
{;
    break;}
case 124:
#line 1342 "cpp.y"
{;
    break;}
case 125:
#line 1346 "cpp.y"
{ g_bdestructor_seen = false;;
    break;}
case 126:
#line 1350 "cpp.y"
{
      add_member_declaration(yyvsp[-2].string_list_ptr, yyvsp[-1].member_declarator_list_ptr);
    ;
    break;}
case 129:
#line 1371 "cpp.y"
{
      yyval.member_declarator_list_ptr = new member_declarator_list;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 130:
#line 1376 "cpp.y"
{
      yyval.member_declarator_list_ptr = yyvsp[-2].member_declarator_list_ptr;
      yyval.member_declarator_list_ptr->push_back(yyvsp[0].member_declarator_ptr);
    ;
    break;}
case 131:
#line 1389 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[-1].member_declarator_ptr != 0) //there is a pure specifier
      {
        yyval.member_declarator_ptr->bpure = true;  
      }
    ;
    break;}
case 132:
#line 1397 "cpp.y"
{
      yyval.member_declarator_ptr = yyvsp[-1].member_declarator_ptr;
      if (yyvsp[0].expression_ptr != NULL)
      {
        yyval.member_declarator_ptr->expr = yyvsp[0].expression_ptr;
      }
    ;
    break;}
case 133:
#line 1410 "cpp.y"
{yyval.tcount = 1;;
    break;}
case 134:
#line 1414 "cpp.y"
{yyval.tcount = yyvsp[0].tcount;;
    break;}
case 135:
#line 1415 "cpp.y"
{yyval.tcount = 0;;
    break;}
case 136:
#line 1420 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 137:
#line 1424 "cpp.y"
{yyval.expression_ptr = yyvsp[0].expression_ptr;;
    break;}
case 138:
#line 1425 "cpp.y"
{yyval.expression_ptr = NULL;;
    break;}
case 139:
#line 1430 "cpp.y"
{yyval.inhcont = yyvsp[0].inhcont;;
    break;}
case 140:
#line 1431 "cpp.y"
{yyval.inhcont = NULL;;
    break;}
case 141:
#line 1435 "cpp.y"
{yyval.inhcont = yyvsp[0].inhcont;;
    break;}
case 142:
#line 1440 "cpp.y"
{
    	yyval.inhcont = new base_specifier_list;
     	yyval.inhcont->push_back(yyvsp[0].bclass);
    ;
    break;}
case 143:
#line 1445 "cpp.y"
{
    	yyval.inhcont->push_back(yyvsp[0].bclass);
    ;
    break;}
case 144:
#line 1461 "cpp.y"
{
    	yyval.bclass = new base_specifier;
     	yyval.bclass->access = yyvsp[-1].tcount;
      yyval.bclass->class_name = yyvsp[0].string_ptr;
    ;
    break;}
case 145:
#line 1469 "cpp.y"
{/*$$ = 1; */;
    break;}
case 146:
#line 1470 "cpp.y"
{/* $$ = 0; */;
    break;}
case 147:
#line 1475 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 148:
#line 1477 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 149:
#line 1479 "cpp.y"
{yyval.tcount = yyvsp[0].tcount; g_currentaccessspecifier = yyvsp[0].tcount;;
    break;}
case 150:
#line 1484 "cpp.y"
{yyval.tcount=yyvsp[0].tcount;;
    break;}
case 151:
#line 1485 "cpp.y"
{yyval.tcount = 0;;
    break;}
case 152:
#line 1538 "cpp.y"
{/* $$ = 1; */;
    break;}
case 153:
#line 1539 "cpp.y"
{/* $$ = 0; */;
    break;}
case 154:
#line 1660 "cpp.y"
{ /*$$ = $1;*/;
    break;}
case 155:
#line 1661 "cpp.y"
{/* $$ = NULL; */;
    break;}
case 156:
#line 1747 "cpp.y"
{/* $$ = $1; */;
    break;}
case 157:
#line 1748 "cpp.y"
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
#line 1803 "cpp.y"

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

