#ifndef BISON_CPPYACC_HPP
# define BISON_CPPYACC_HPP

#include <axis/wcg/actions.h>

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


extern YYSTYPE yylval;

#endif /* not BISON_CPPYACC_HPP */
