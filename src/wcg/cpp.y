%{
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
%}


%union  {  
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
}


/*** Keywords ***/
%token  KW_asm        KW_do           KW_inline            KW_short        KW_typeid
%token  KW_auto       KW_double       KW_int               KW_signed       KW_typename
%token  KW_bool       KW_dynamic_cast KW_long              KW_sizeof       KW_union
%token  KW_break      KW_else         KW_mutable           KW_static       KW_unsigned
%token  KW_case       KW_enum         KW_namespace         KW_static_cast  KW_using
%token  KW_catch      KW_explicit     KW_new               KW_struct       KW_virtual
%token  KW_char       KW_extern       KW_operator          KW_switch       KW_void
%token  KW_class      KW_false        KW_private           KW_template     KW_volatile
%token  KW_const      KW_float        KW_protected         KW_this         KW_wchar_t
%token  KW_const_cast KW_for          KW_public            KW_throw        KW_while
%token  KW_continue   KW_friend       KW_register          KW_true
%token  KW_default    KW_goto         KW_reinterpret_cast  KW_try
%token  KW_delete     KW_if           KW_return            KW_typedef
%token  KW_export
%token  KW_string

/*** Pseduo Keywords ***/

%token KW_unsigned_char KW_unsigned_short KW_unsigned_long KW_long_double

/*** Literals ***/
%token INTEGER_LITERAL CHARACTER_LITERAL FLOATING_LITERAL STRING_LITERAL 

/*** Axis specific ***/
%token ACCESSBEAN_MACRO

/*** Single-Character Operators ***/
%token LEFTPAREN  RIGHTPAREN        // ( )
%token LEFTBRACK  RIGHTBRACK        // { }
%token LEFTARRAY RIGHTARRAY         // [ ]
%token PLUS MINUS STAR DIVIDE MOD   // + - * / %
%token GREATER LESS EQUAL           // > < =
%token AND OR NOT XOR               // & | ! ^
%token COMMA SEMI COLON             // , ; :
%token COMPLEMENT DOT QUESTION      // ~ . ?          

/*** Multi-Character Operators ***/
%token COLCOL ELLIPSES
%token PLUSEQ MINUSEQ STAREQ DIVEQ MODEQ
%token XOREQ  ANDEQ   OREQ   LTLT  GTGT     GTGTEQ     LTLTEQ     EQEQ   NOTEQ
%token LEQ    GEQ     ANDAND OROR  PLUSPLUS MINUSMINUS DOTSTAR ARROWSTAR  ARROW


/*** The context-sensitive versions of IDENTIFIER ***/ 

%token IDENTIFIER 

%token ID_typedef_name 
%token ID_enum_name ID_class_name

%type <tokenvalue> KW_class KW_struct KW_union KW_enum KW_namespace KW_template
%type <tokenvalue> KW_protected KW_public KW_private
%type <tokenvalue> KW_typename KW_operator class_key COMMA COLON
%type <tokenvalue> colcol_opt ptr_operator
%type <tokenvalue> comma_opt virtual_opt cv_qualifier cv_qualifier_seq
%type <tokenvalue> cv_qualifier_seq_opt

//%type <> CHARACTER_LITERAL FLOATING_LITERAL
//%type <> STRING_LITERAL

%type <tokenvalue> access_specifier access_specifier_opt
//%type <> declaration block_declaration
//%type <> simple_declaration
%type <member_declarator_ptr> declarator direct_declarator
%type <member_declarator_ptr> member_declarator init_declarator
%type <param_declarator_ptr> parameter_declarator direct_parameter_declarator
//%type <> enumerator_definition 
%type <param_decl_ptr> parameter_declaration  
%type <param_decl_list_ptr> parameter_declaration_list parameter_declaration_list_opt parameter_declaration_clause
%type <expression_ptr> initializer initializer_opt initializer_clause assignment_expression
%type <tokenvalue> pure_specifier pure_specifier_opt
%type <expression_ptr> constant_expression constant_expression_opt
%type <expression_ptr> constant_initializer constant_initializer_opt
//%type <> initializer_list
%type <string_ptr> unqualified_id id_expression 
%type <string_ptr> class_name type_name declarator_id 
%type <string_ptr> simple_type_specifier type_specifier decl_specifier function_specifier
%type <ctype> type_specifier_seq
%type <ctype> type_specifier_seq_opt
%type <ctype> class_specifier
%type <class_head_ptr> class_head
%type <base_specifier_ptr> base_specifier
//%type <> expression_list expression_list_opt

%type <any_ptr> member_specification member_specification_opt
%type <any_ptr> member_declaration
%type <member_declarator_list_ptr> declaration_seq declaration_seq_opt 
%type <member_declarator_list_ptr> member_declarator_list
//%type <> enumerator_list enumerator_list_opt
%type <string_list_ptr> decl_specifier_seq decl_specifier_seq_opt 
%type <base_specifier_list_ptr> base_clause_opt base_clause base_specifier_list

%type <string_ptr> any_identifier 

%start translation_unit

%%

any_identifier
: ID_typedef_name {$$ = new string(yytext);}
//| ID_original_namespace_name {$$ = new string(yytext);}
//| ID_namespace_alias {$$ = new string(yytext);}
//| ID_enum_name {$$ = new string(yytext);}
| ID_class_name {$$ = new string(yytext);}
//| ID_template_name {$$ = new string(yytext);}
| IDENTIFIER {$$ = new string(yytext);}
;

//any_identifier_or_template :
//  any_identifier {}
//| template_id {}
//;

// *********  Context-sensitive identifiers **********
// 
// ID_typedef_name 
//   : IDENTIFIER {} 
//   ; 
// ID_original_namespace_name 
//   : IDENTIFIER  {}
//   ; 

ID_namespace_alias 
   : IDENTIFIER  { }
   ;

// ID_enum_name 
//   : IDENTIFIER  {}
//   ; 
// ID_class_name 
//   : IDENTIFIER  {}
//   ;


// ********** 1.1  Keywords  [gram.key] **********

typedef_name
  : ID_typedef_name {}
  ;

namespace_name
  : 
//  original_namespace_name {}
//  | 
  namespace_alias	{ }
  ;

//original_namespace_name
// : ID_original_namespace_name	{}
//  ;

namespace_alias
  : ID_namespace_alias	{}
  ;

class_name
  : ID_class_name {$$ = new string(yytext);}
//  | template_id 	{}
  ;

//enum_name
//  : ID_enum_name {}
//  ;

//template_name
//  : ID_template_name {}
//  ;


// **********  1.2  Lexical conventions [gram.lex] **********


// **********  1.3  Basic concepts [gram.basic] **********
translation_unit
:		{  
   		translation_unit_start();
   	} 
    declaration_seq_opt
    {}
;


// **********    1.4  Expressions  [gram.expr] **********
//primary_expression
//  : INTEGER_LITERAL {} 
//  | CHARACTER_LITERAL {}
//  | FLOATING_LITERAL {}
//  | STRING_LITERAL {}
//  | KW_true {}
//  | KW_false {}
//  | KW_this {}
//  | LEFTPAREN expression RIGHTPAREN {}
//  | id_expression {}
//;

id_expression
  : unqualified_id {$$ = $1;}
//  | qualified_id {}
  ;

unqualified_id
   /* not any_identifier, cannot have :: */
  : IDENTIFIER {$$ = new string(yytext);}
  | class_name {$$ = $1;}
//  | operator_function_id	{}
//  | conversion_function_id {}
  | COMPLEMENT class_name 	{$$ = $2; g_bdestructor_seen = true;}
//  | template_id			{}
  ;

//qualified_id
//  : colcol_opt nested_name_specifier template_opt unqualified_id
//    {}
//    /* not any_identifier, must have :: */
//  | COLCOL IDENTIFIER           {}
//  | COLCOL operator_function_id {}
//  | COLCOL template_id		{}
//  ;

//nested_name_specifier
//  : class_or_namespace_name COLCOL nested_name_specifier_opt
//    {}
//  | class_or_namespace_name COLCOL KW_template nested_name_specifier
//    {}
//;

//nested_name_specifier_opt
//   : nested_name_specifier {}
//   | /* Empty */ {}
//   ;

//class_or_namespace_name
//  : class_name 		{}
//  | namespace_name 	{}
//  ;

//postfix_expression
//  : primary_expression
//    {}
//  | postfix_expression LEFTARRAY expression RIGHTARRAY 
//    {}
//  | postfix_expression 
//    {}
//    LEFTPAREN expression_list_opt RIGHTPAREN 
//    {}
//  | simple_type_specifier LEFTPAREN expression_list_opt RIGHTPAREN 
//    {}
//  | KW_typename colcol_opt nested_name_specifier any_identifier_or_template 
//    LEFTPAREN expression_list_opt RIGHTPAREN 
//    {}
//  | KW_typename colcol_opt nested_name_specifier template_opt template_id 
//    LEFTPAREN expression_list_opt RIGHTPAREN 
//    {}
//  | postfix_expression DOT template_opt id_expression 
//    {}
//  | postfix_expression ARROW template_opt id_expression 
//    {}
//  | postfix_expression DOT pseudo_destructor_name 
//    {}
//  | postfix_expression ARROW pseudo_destructor_name 
//    {}
//  | postfix_expression PLUSPLUS
//    {}
//  | postfix_expression MINUSMINUS
//    {}
//  | KW_dynamic_cast LESS type_id GREATER LEFTPAREN expression RIGHTPAREN 
//    {}
//  | KW_static_cast LESS type_id GREATER LEFTPAREN expression RIGHTPAREN 
//    {}
//  | KW_reinterpret_cast LESS type_id GREATER LEFTPAREN expression RIGHTPAREN 
//    {}
//  | KW_const_cast LESS type_id GREATER LEFTPAREN expression RIGHTPAREN 
//    {}
//  | KW_typeid LEFTPAREN expression RIGHTPAREN
//    {}
//  | KW_typeid LEFTPAREN type_id RIGHTPAREN
//    {}
//  ;
          
expression_list
  : assignment_expression 
      {}
  | expression_list COMMA assignment_expression 
      {}
  ;

//expression_list_opt
//  : expression_list {}
//  | /* Empty */ {}
//  ;

//pseudo_destructor_name
//  : colcol_opt nested_name_specifier_opt type_name COLCOL COMPLEMENT type_name
//  {}
//  | colcol_opt nested_name_specifier KW_template template_id COLCOL 
//	COMPLEMENT type_name
//	{}
//  | colcol_opt nested_name_specifier_opt COMPLEMENT type_name
//  {}
//  ;
          
//unary_expression
//  : postfix_expression
//    {}
//  | PLUSPLUS cast_expression
//    {}      
//  | MINUSMINUS cast_expression
//    {}
//  | STAR cast_expression
//    {}
//  | AND cast_expression
//    {}
//  | PLUS cast_expression
//    {}
//  | MINUS cast_expression
//    {}
//  | NOT cast_expression
//    {}
//  | COMPLEMENT cast_expression
//    {}
//  | KW_sizeof unary_expression
//    {}
//  | KW_sizeof LEFTPAREN type_id RIGHTPAREN
//    {}
//  | new_expression
//    {}
//  | delete_expression
//    {}
//  ;
                    
//new_expression
//  : colcol_opt KW_new new_placement_opt new_type_id new_initializer_opt
//    {}
//  | colcol_opt KW_new new_placement_opt LEFTPAREN type_id RIGHTPAREN 
//      new_initializer_opt
//    {}
//  ;
          
//new_placement
//  : LEFTPAREN expression_list RIGHTPAREN {}
//  ;

//new_placement_opt
//   : new_placement {}
//   | /* Empty */ {/*$$ = NULL; */}
//   ;

//new_type_id
//  : type_specifier_seq new_declarator_opt
//    {}
//  ;
          
//new_declarator
//  : ptr_operator new_declarator_opt  
//    {}
//  | direct_new_declarator
//    {}
//  ;

//new_declarator_opt
//  : new_declarator {}
//  | /* Empty */ {}
//  ;

//direct_new_declarator
//  : LEFTARRAY expression RIGHTARRAY
//    {}
//  | direct_new_declarator LEFTARRAY constant_expression RIGHTARRAY
//    {}
//  ;
          
//new_initializer
//  : LEFTPAREN expression_list_opt RIGHTPAREN {}
//  ;

//new_initializer_opt
//  : new_initializer {}
//  | /* Empty */ {}
//  ;
          
//delete_expression
//  : colcol_opt KW_delete cast_expression
//    {}
//  | colcol_opt KW_delete LEFTARRAY RIGHTARRAY cast_expression
//    {}
//  ;
          
//cast_expression
//  : unary_expression  {}
//  | LEFTPAREN type_id RIGHTPAREN cast_expression
//    {}
//  ;
          
//pm_expression
//  : cast_expression {}
//  | pm_expression DOTSTAR cast_expression
//    {}
//  | pm_expression ARROWSTAR cast_expression
//    {}
//  ;

//multiplicative_expression
//  : pm_expression {}
//  | multiplicative_expression STAR pm_expression 
//   {}
//  | multiplicative_expression DIVIDE pm_expression 
//   {}
//  | multiplicative_expression MOD pm_expression 
//   {}
//  ;        

//additive_expression
//  : multiplicative_expression {}
//  | additive_expression PLUS multiplicative_expression 
//   {}
//  | additive_expression MINUS multiplicative_expression 
//   {}
//  ;

//shift_expression
// : additive_expression	 {}
//  | shift_expression LTLT additive_expression 
//   {}
//  | shift_expression GTGT additive_expression 
//   {}
//  ;

//relational_expression
//  : shift_expression {}
//  | relational_expression LESS shift_expression 
//   {}
//  | relational_expression GREATER shift_expression 
//   {}
//  | relational_expression LEQ shift_expression
//   {}
//  | relational_expression GEQ shift_expression
//   {}
//  ;

//equality_expression
//  : relational_expression {}
//  | equality_expression EQEQ relational_expression 
//   {}
//  | equality_expression NOTEQ relational_expression 
//   {}
//  ;

//and_expression
// : equality_expression {}
//  | and_expression AND equality_expression 
//   {}
//  ;

//exclusive_or_expression
//  : and_expression {}
//  | exclusive_or_expression XOR and_expression 
//   {}
//  ;

//inclusive_or_expression
//  : exclusive_or_expression {}
//  | inclusive_or_expression OR exclusive_or_expression 
//   {}
//  ;

//logical_and_expression
// : inclusive_or_expression {}
//  | logical_and_expression ANDAND inclusive_or_expression 
//   {}
//  ;

//logical_or_expression
//  : logical_and_expression {}
//  | logical_or_expression OROR logical_and_expression 
//   {}
//  ;

//conditional_expression
//  : logical_or_expression {}
//  | logical_or_expression QUESTION expression COLON assignment_expression
//    {}
//  ;

assignment_expression
: INTEGER_LITERAL
  {
    $$ = new expression;
    $$->expr.n = atoi(yytext);
  }
//  conditional_expression {}
//  | logical_or_expression assignment_operator assignment_expression 
//    {}
//  | throw_expression {}
  ;

//assignment_operator
//  : EQUAL {}
//  | STAREQ {}
//  | DIVEQ {}
//  | MODEQ {}
//  | PLUSEQ {}
//  | MINUSEQ {}  
//  | GTGTEQ {}
//  | LTLTEQ {}
//  | ANDEQ {}
//  | XOREQ {}
//  | OREQ {}
//  ;
          
//expression
//  : assignment_expression  {}
//  | expression COMMA assignment_expression
//    {}
//  ;

//expression_opt
//  : expression {}
//  | /* Empty */ {}
//  ;

constant_expression
: INTEGER_LITERAL
  {
    $$ = new expression;
    $$->expr.n = atoi(yytext);     
  }
  ;

constant_expression_opt
  : constant_expression {$$ = $1;}
  | /* Empty */ {$$ = NULL;}
  ;


// **********   1.5  Statements [gram.stmt.stmt] **********
//statement
//  : labeled_statement {}
//  | expression_statement {}
//  | compound_statement {}
//  | selection_statement {}
//  | iteration_statement {}
//  | jump_statement {}
//  | declaration_statement {}
//  | try_block {}
//  ;
          
//labeled_statement
//  : any_identifier COLON statement
//    {}
//  | KW_case constant_expression COLON statement
//    {}
//  | KW_default COLON statement
//    {}
//  ;

//expression_statement
//  : expression SEMI  {}
//    // Was expression_opt, but this is covered by simple_declaration
//  ;

//compound_statement
//  : LEFTBRACK 
//    {}
//    statement_seq_opt
//    RIGHTBRACK 
//    {}
//  ;

//statement_seq
//  : statement
//    {}
// | statement_seq statement
//   {}
//  ;

//statement_seq_opt
//  : statement_seq {}
//  | /* Empty */ {}
//  ;

//selection_statement
//  : KW_if LEFTPAREN condition RIGHTPAREN statement
//    {}
//  | KW_if LEFTPAREN condition RIGHTPAREN statement KW_else statement
//    {}
//  | KW_switch LEFTPAREN condition RIGHTPAREN statement
//    {}
//  ;

//condition
//  : expression {}
//  | type_specifier_seq declarator EQUAL assignment_expression
//    {}
//  ;

//condition_opt
//  : condition {}
//  | /* Empty */ {}
//  ;

//iteration_statement
//  : KW_while LEFTPAREN condition RIGHTPAREN statement
//    {}
//  | KW_do statement KW_while LEFTPAREN expression RIGHTPAREN SEMI 
//    {}
//  | KW_for LEFTPAREN for_init_statement condition_opt SEMI  
//	expression_opt RIGHTPAREN statement
//    {}
//  ;

//for_init_statement
//  : expression_statement {}
//  | simple_declaration {}
//  ;

//jump_statement
//  : KW_break SEMI 
//    {}
//  | KW_continue SEMI 
//    {}
//  | KW_return expression_opt SEMI 
//    {}
//  | KW_goto any_identifier SEMI 
//    {}
//  ;

//declaration_statement
//  : block_declaration {}
//  ;


// **********  1.6  Declarations  [gram.dcl.dcl] **********

declaration_seq
  : declaration
    {}
  | declaration_seq declaration
    {}  
  ;

declaration_seq_opt
: declaration_seq {}
| /* Empty */ {}
  ;

declaration
  : block_declaration
    {}
 // | function_definition 
 //   {}
//  | template_declaration
//    {}
//  | explicit_instantiation
//    {}
//  | explicit_specialization
//    {}
//  | linkage_specification
//    {}
//  | namespace_definition
//    {}
  ;

block_declaration
  : simple_declaration
    {}
//  | asm_definition
//    {/* $$ = NULL;/*XXX*/ }
//  | namespace_alias_definition
//    {}
//  | using_declaration
//    {}
	| using_directive
	  { }
  ;

simple_declaration
  : decl_specifier_seq_opt 
  	init_declarator_list_opt // there can be global variable or extern declarations - Susantha.
    SEMI 
    {}
  ;

decl_specifier
  :
//   storage_class_specifier
//    {}
//  |
    type_specifier
    {}
  | function_specifier
    { $$ = $1;}  
//  | KW_friend	
//    {}
//  | KW_typedef
//    {}
  ;

decl_specifier_seq
  : decl_specifier_seq_opt decl_specifier
    {
		if ($2 != NULL) 
		{
			if ($$ == NULL) {$$ = new string_list;}
			$$->push_back($2);
		}
		else
		{	
			$$ = NULL;
		}
    }
  ;

decl_specifier_seq_opt
  : decl_specifier_seq
    {$$ = $1;}
  | /* Empty */ 
    {$$ = NULL;}
  ;

//storage_class_specifier
//  : KW_auto
//    {}
//  | KW_register
//    {}
//  | KW_static
//    {}
//  | KW_extern
//    {}
//  | KW_mutable
//    {}
//  ;

function_specifier
  : 
//  KW_inline
//    {}
//  | 
  KW_virtual
    { $$ = NULL;}
//  | KW_explicit
//    {}
  ;


type_specifier
  : simple_type_specifier
  {$$ = $1;}
  | class_specifier
  {}
//  | enum_specifier
//  {}
//  | elaborated_type_specifier
//  {}
  | cv_qualifier
  {}
  ;

/***** Multi word types ********/
simple_type_specifier
  :
//   colcol_opt nested_name_specifier_opt
   type_name 
    {$$ = $1;}
//  | colcol_opt nested_name_specifier KW_template template_id
//  {}
//  |
  | KW_char
    {$$ = new string("char");}
  | KW_unsigned_char
    {$$ = new string("unsigned char");}
  | KW_wchar_t
    {$$ = new string("wchar_t");}
  | KW_bool
    {$$ = new string("bool");}
  | KW_short
    {$$ = new string("short");}
  | KW_unsigned_short
    {$$ = new string("unsigned short");}
  | KW_int
    {$$ = new string("int");}
  | KW_long
    {$$ = new string("long");}
  | KW_unsigned_long
    {$$ = new string("unsigned long");}
  | KW_signed
    {$$ = new string("signed");}
  | KW_unsigned
    {$$ = new string("unsigned");}
  | KW_float
    {$$ = new string("float");}
  | KW_double
    {$$ = new string("double");}
  | KW_void
    {$$ = new string("void");}
  | KW_string
    {$$ = new string("string");}
  ;

type_name
  : class_name	{$$ = $1;}
//  | enum_name {}
//  | typedef_name {}
  ;

//elaborated_type_specifier
//  : class_key colcol_opt nested_name_specifier_opt any_identifier_or_template
//     {}
//  | KW_enum colcol_opt nested_name_specifier_opt any_identifier
//     {}
//  | KW_typename colcol_opt nested_name_specifier any_identifier
//     {}
//  | KW_typename colcol_opt nested_name_specifier template_opt template_id
//     {}
//  ;

//enum_specifier
//  : KW_enum identifier_opt 
//    {}
//    LEFTBRACK  enumerator_list_opt RIGHTBRACK 
//    {}
//  ;


//enumerator_list
//  : enumerator_definition
//    {}
//  | enumerator_list COMMA enumerator_definition
//    {}
//  ;

//enumerator_list_opt
//  : enumerator_list {}
//  | /* Empty */ {}
//  ;

//enumerator_definition
//  : enumerator
//    {}
//  | enumerator EQUAL constant_expression
//    {}
//  ;

//enumerator
//  : any_identifier {}
//  ;


//namespace_definition
//  : named_namespace_definition {}
//  | unnamed_namespace_definition {}
//  ;


//named_namespace_definition
//  : original_namespace_definition {}
//  | extension_namespace_definition {}
//  ;


//original_namespace_definition
//  : KW_namespace any_identifier
//    {}
//    LEFTBRACK  namespace_body RIGHTBRACK 
//    {}
//  ;


//extension_namespace_definition
//  : KW_namespace original_namespace_name 
//    {}
//    LEFTBRACK  namespace_body RIGHTBRACK 
//    {}
//  ;


//unnamed_namespace_definition
//  : KW_namespace 
//    {}
//    LEFTBRACK  namespace_body RIGHTBRACK 
//   {}
//  ;


//namespace_body
//  : declaration_seq_opt {}
//  ;


//namespace_alias_definition
//  : KW_namespace any_identifier EQUAL qualified_namespace_specifier SEMI 
//    {}
//  ;


//qualified_namespace_specifier
//  : colcol_opt nested_name_specifier_opt namespace_name
//    {/* $$ = $3; */}
//  ;

//using_declaration
//  : KW_using KW_typename colcol_opt nested_name_specifier any_unqualified_id 
//    SEMI 
//    {}   
//  | KW_using  colcol_opt nested_name_specifier any_unqualified_id 
//    SEMI 
//    {}   
//  | KW_using COLCOL  any_unqualified_id 
//    SEMI 
//    {}   
//  ;

using_directive
  : KW_using KW_namespace 
  //colcol_opt nested_name_specifier_opt 
	namespace_name 
	SEMI 
	{ }
  ;

//asm_definition
//  : KW_asm LEFTPAREN STRING_LITERAL RIGHTPAREN SEMI 
//  {}
//  ;

//linkage_specification
//  : KW_extern STRING_LITERAL LEFTBRACK  declaration_seq_opt RIGHTBRACK 
//    {}
//  | KW_extern STRING_LITERAL declaration
//    {}
//  ;



// **********  1.7  Declarators [gram.dcl.decl] **********

init_declarator_list
  : init_declarator
    {}
  | init_declarator_list
    COMMA init_declarator
    {}
  ;

init_declarator_list_opt
  : init_declarator_list {}
    | /* Empty */ {}
  ;

init_declarator
  : declarator initializer_opt
    {}
  ;

parameter_declarator
  : direct_parameter_declarator
    {$$=$1;}
  | ptr_operator
    parameter_declarator
    {
      $$=$2;
      $$->ptr_ops.push_back($1);
    }
  ;

direct_parameter_declarator
  : declarator_id
    {
      $$ = new param_declarator;
      $$->decl_id = $1->c_str();
    }
  | direct_parameter_declarator LEFTARRAY constant_expression_opt RIGHTARRAY
    {
      $$ = $1;
      if ($3 != 0)
	    {
	      $$->arr_dim.push_back($3);
	    }
    }
  ;
    
declarator
  : direct_declarator
    {$$ = $1;}
  | ptr_operator
    declarator
    {
        $$ = $2;
        $$->ptr_ops.push_back($1);
    }
  ;

direct_declarator
  : declarator_id
    {
        $$ = new member_declarator;
		$$->method = false;
        $$->declarator_id = $1;
    }
  | direct_declarator
    LEFTPAREN 
    parameter_declaration_clause RIGHTPAREN 
//  cv_qualifier_seq_opt
//  exception_specification_opt 
    {
        $$->params = $3;
        $$->method = true;
    }
  | direct_declarator LEFTARRAY constant_expression_opt RIGHTARRAY
    {
        $$->array_indexes.push_back($3);
    }
//  | LEFTPAREN declarator RIGHTPAREN
//  {}
  ;

ptr_operator
  : STAR cv_qualifier_seq_opt
    {$$ = STAR;}
  | AND
    {$$ = AND;}
//  | colcol_opt nested_name_specifier STAR cv_qualifier_seq_opt
//  {}
  ;

cv_qualifier_seq
  : cv_qualifier cv_qualifier_seq_opt {/* $$ = $1 + $2; */}
  ;

cv_qualifier_seq_opt
: cv_qualifier_seq {}
| /* Empty */ {/* $$ = 0; */}
  ;

cv_qualifier
  : KW_const
    {
    }
//  | KW_volatile
//  {}
  ;

declarator_id
  : id_expression 
    {$$ = $1;}
//  | colcol_opt nested_name_specifier_opt type_name
//    {/* $$ = $3; */}
  ;

//type_id
//  : type_specifier_seq abstract_declarator_opt 
//    {}
//  ;

type_specifier_seq_opt
  : type_specifier_seq  {}
  | /* Empty */  {}
  ;

type_specifier_seq
  : type_specifier type_specifier_seq_opt  
      {}
  ;

//abstract_declarator
//  : ptr_operator abstract_declarator_opt
//    {}
//  | direct_abstract_declarator {}
//  ;

//abstract_declarator_opt
//: abstract_declarator {}
//  | /* Empty */ {}
//  ;

//direct_abstract_declarator
//  : direct_abstract_declarator_opt LEFTPAREN 
//    {}
//    parameter_declaration_clause RIGHTPAREN cv_qualifier_seq_opt 
//   exception_specification_opt
//    {}
//  | direct_abstract_declarator_opt LEFTARRAY constant_expression_opt RIGHTARRAY
//    {}
//  | LEFTPAREN abstract_declarator RIGHTPAREN
//    {}
//  ;

//direct_abstract_declarator_opt
//  : direct_abstract_declarator {}
//  | /* Empty */ {}
//  ;

parameter_declaration_clause
  : parameter_declaration_list_opt 
// ellipses_opt //we probably never support this - Susantha
{$$ = $1;}
//  | parameter_declaration_list COMMA ELLIPSES
//{}
  ;

ellipses_opt
  : ELLIPSES {}
  | /* Empty */ {}
  ;

parameter_declaration_list_opt
: parameter_declaration_list {}
| /* Empty */ {$$ = NULL;}
  ;

parameter_declaration_list
  : parameter_declaration
    { 
      $$ = new param_decl_list;
      $$->push_back($1);
    }
  | parameter_declaration_list COMMA parameter_declaration
    {
      $$ = $1;
      $$->push_back($3);
    }
  ;

parameter_declaration
  : decl_specifier_seq parameter_declarator
    {
      $$ = new param_decl;
      $$->decl_specs = $1;
      $$->param = $2;
      $$->bdef = false; 
    }
  | decl_specifier_seq parameter_declarator EQUAL assignment_expression
    {
      $$ = new param_decl;
      $$->decl_specs = $1;
      $$->param = $2;
      $$->bdef = true;
      $$->defval = $4;
    }
//  | decl_specifier_seq abstract_declarator_opt
//    {}
//  | decl_specifier_seq abstract_declarator_opt EQUAL assignment_expression
//    {}
  ;

//function_definition
//  : decl_specifier_seq_opt
//    declarator 
//    {}
//    ctor_initializer_opt
//    {}
//    function_body
//    {}
//  | decl_specifier_seq_opt 
//    declarator
//    {}
//    function_try_block
//    {}
//  ;

//function_body
//  : compound_statement {/*$$ = $1; */}
//  ;

initializer
  : EQUAL initializer_clause
    {}
  | LEFTPAREN expression_list RIGHTPAREN
    {}
  ;

initializer_opt
  : initializer 
    {}
  | /* Empty */ {}
  ;

initializer_clause
  : assignment_expression {}
  | LEFTBRACK  initializer_list comma_opt RIGHTBRACK 
    {/* $$ = $3; */}
  | LEFTBRACK RIGHTBRACK  {}
  ;

comma_opt
  : COMMA {/* $$ = 1; */}
  | /* Empty */ {/* $$ = 0; */}
  ;

initializer_list
  : initializer_clause
    {}
  | initializer_list COMMA initializer_clause
    {}
  ;

/**********  1.8  Classes [gram.class] **********/
class_specifier
  : class_head
  //add to defined classes list
  	{
	  if (!is_defined_class($1->class_name->c_str()))
	  {
		  //check if this class should be wrapped or not depending on wsdd information
		  if (is_bean_class($1->baselist)) //bean class
		  {
					BeanClass* pBeanClass = new BeanClass();
					pBeanClass->SetClassName(*($1->class_name));
					g_pTranslationUnit->AddBeanClass(pBeanClass);
					g_pCurrentBeanClass = pBeanClass;
					g_currentclasstype = BEANCLASS;
					g_baccessbeanmacrofound = false;
					//following line adds default namespace for this complex type. 
					//This should be removed when we get the namespace from the wsdd.
					string defns = "http://www.opensource.lk/" + (*($1->class_name));
					g_ClassNamespaces[*($1->class_name)] = defns;
		  }
		  else // we assume that this is the webservice class - there cannot be 2 web service classes
		  {
					WSClass* pWSClass = new WSClass();
					pWSClass->SetClassName(*($1->class_name));
					g_pTranslationUnit->SetWSClass(pWSClass);
					g_pCurrentWSClass = pWSClass;
					g_currentclasstype = WSCLASS;
					g_baccessbeanmacrofound = false;
					//following line adds default namespace for this web service. 
					//This should be removed when we get the namespace from the wsdd.
					string defns = "http://www.opensource.lk/" + (*($1->class_name));
					g_ClassNamespaces[*($1->class_name)] = defns;
		  }   
  		  g_classesfound.push_back(g_classname);
	   }
  	}
  	LEFTBRACK member_specification_opt RIGHTBRACK
  	{
			g_classname = ""; //end of class scope
   	}
  ;

class_head
  : class_key any_identifier
    base_clause_opt
    {
    	g_classname = $2->c_str();
    	$$ = new class_head;
     	$$->class_name = $2;
			$$->baselist = $3; //may be NULL
    }
//  | class_key nested_name_specifier any_identifier 
//    {}
//    base_clause_opt {}
//  | class_key nested_name_specifier_opt template_id
//    {}
//    base_clause_opt {}
  ;

class_key
  : KW_class {}
// We dont support structs and unions for the moment - Susantha.  
//  | KW_struct {}
//  | KW_union {}
  ;

member_specification
  : member_declaration member_specification_opt
    {}
  | access_specifier
    COLON member_specification_opt
    {}
  ;

member_specification_opt
  : member_specification {}
  | /* Empty */ {}
  ;

member_declaration
  : { g_bdestructor_seen = false;}
  	decl_specifier_seq_opt
    member_declarator_list
    SEMI
    {
      add_member_declaration($2, $3);
    }
 // | function_definition
 //   {}
 //   semi_opt
 // | colcol_opt nested_name_specifier template_opt unqualified_id SEMI 
 //   {}
 // | using_declaration
 //   {}
 // | template_declaration
 //   {}
 // ************** Axis Specific *************
	| ACCESSBEAN_MACRO
	  { g_baccessbeanmacrofound = true;}
  ;

semi_opt
  : SEMI  
  | 
  ;

member_declarator_list
  : member_declarator
    {
      $$ = new member_declarator_list;
      $$->push_back($1);
    }
  | member_declarator_list COMMA member_declarator
    {
      $$ = $1;
      $$->push_back($3);
    }
  ;

//member_declarator_list_opt
//  : member_declarator_list {}
//  |  /* Empty */ {}
//  ;

member_declarator
  : declarator pure_specifier_opt
    {
      $$ = $1;
      if ($1 != 0) //there is a pure specifier
      {
        $$->bpure = true;  
      }
    }
  | declarator constant_initializer_opt
    {
      $$ = $1;
      if ($2 != NULL)
      {
        $$->expr = $2;
      }
    }
//  | identifier_opt COLON constant_expression
//    {}
  ;

pure_specifier
  : EQUAL INTEGER_LITERAL  /* Should be "0" */
    {$$ = 1;}
  ;

pure_specifier_opt
  : pure_specifier {$$ = $1;}
  | /* Empty */ {$$ = 0;}
  ;

constant_initializer
  : EQUAL constant_expression
  {$$ = $2;}
  ;

constant_initializer_opt
  : constant_initializer {$$ = $1;}
  | /* Empty */ {$$ = NULL;}
  ;

/**********  1.9  Derived classes [gram.class.derived] **********/
base_clause_opt
  : base_clause {$$ = $1;}
 | /* Empty */ {$$ = NULL;}
  ;

base_clause
  : COLON base_specifier_list {$$ = $2;}
  ;

base_specifier_list
  : base_specifier
    {
    	$$ = new base_specifier_list;
     	$$->push_back($1);
    }
  | base_specifier_list COMMA base_specifier
    {
    	$$->push_back($3);
    }
  ;

base_specifier
  :
//   colcol_opt nested_name_specifier_opt class_name
//  {}
//  | KW_virtual access_specifier_opt colcol_opt nested_name_specifier_opt 
//	class_name
//  {}
//  |
  	access_specifier
//  virtual_opt colcol_opt nested_name_specifier_opt
		class_name
    {
    	$$ = new base_specifier;
     	$$->access = $1;
      $$->class_name = $2;
    }
  ;

virtual_opt
  : KW_virtual {/*$$ = 1; */}
 | /* Empty */ {/* $$ = 0; */}
  ;

access_specifier
  : KW_public
		{$$ = $1; g_currentaccessspecifier = $1;}
	| KW_protected
		{$$ = $1; g_currentaccessspecifier = $1;}
  | KW_private
		{$$ = $1; g_currentaccessspecifier = $1;}
  ;

access_specifier_opt
  : access_specifier
  	{$$=$1;}
  | /* Empty */ {$$ = 0;}
  ;

/**********  1.10  Special member functions [gram.special] **********/
//conversion_function_id
//  : KW_operator conversion_type_id	
//    {}
//  ;

//conversion_type_id
//  : type_specifier_seq conversion_declarator_opt
//    {}
//  ;

//conversion_declarator
//  : ptr_operator conversion_declarator_opt
//    {}
//  ;

//conversion_declarator_opt
//  : conversion_declarator {}
//  | /* Empty */ {}
//  ;

//ctor_initializer
//  : COLON mem_initializer_list
//    {}
//  ;

//ctor_initializer_opt
//  : ctor_initializer {}
//  | /* Empty */ {}
//  ;

//mem_initializer_list
//  : mem_initializer
//    {}
//  | mem_initializer COMMA mem_initializer_list
//    {}
//  ;
//mem_initializer
//  : mem_initializer_id LEFTPAREN expression_list_opt RIGHTPAREN
//    {}
//  ;

//mem_initializer_id
//  : colcol_opt nested_name_specifier_opt class_name
//    {}
//  | any_identifier
//    {}
//  ;

colcol_opt
  : COLCOL {}
  | /* Empty */ {}
  ;


// **********  1.11  Overloading [gram.over] **********
//operator_function_id
//  : KW_operator an_operator
//    {}
//  ;

//an_operator
//    : KW_new {/* $$ = new string("new"); */}
//    | KW_delete {/* $$ = new string("delete"); */}
//    | KW_new LEFTARRAY RIGHTARRAY {/* $$ = new string("new[]"); */}
//    | KW_delete LEFTARRAY RIGHTARRAY {/* $$ = new string("delete[]"); */}
//    | PLUS {/* $$ = new string("+"); */}
//    | MINUS {/* $$ = new string("-"); */}
//    | STAR {/* $$ = new string("*"); */}
//    | DIVIDE {/* $$ = new string("/"); */}
//    | MOD {/* $$ = new string("%"); */}
//    | XOR {/* $$ = new string("^"); */}
//    | AND {/* $$ = new string("&"); */}
//    | OR {/* $$ = new string("|"); */}
//    | COMPLEMENT {/* $$ = new string("~"); */}
//    | NOT {/* $$ = new string("!"); */}
//    | EQUAL {/* $$ = new string("="); */}
//    | LESS {/* $$ = new string("<"); */}
//    | GREATER {/* $$ = new string(">"); */}
//    | PLUSEQ {/* $$ = new string("+="); */}
//    | MINUSEQ {/* $$ = new string("-="); */}
//    | STAREQ {/* $$ = new string("*="); */}
//    | DIVEQ {/* $$ = new string("/="); */}
//    | MODEQ {/* $$ = new string("%="); */}
//    | XOREQ {/* $$ = new string("^="); */}
//    | ANDEQ {/* $$ = new string("&="); */}
//    | OREQ {/* $$ = new string("|="); */}
//    | LTLT {/* $$ = new string("<<"); */}
//    | GTGT {/* $$ = new string(">>"); */}
//    | GTGTEQ {/* $$ = new string(">>="); */}
//    | LTLTEQ {/* $$ = new string("<<="); */}
//    | EQEQ {/* $$ = new string("=="); */}
//    | NOTEQ {/* $$ = new string("!="); */}
//    | LEQ {/* $$ = new string("<="); */}
//    | GEQ {/* $$ = new string(">="); */}
//    | ANDAND {/* $$ = new string("&&"); */}
//    | OROR {/* $$ = new string("||"); */}
//    | PLUSPLUS {/* $$ = new string("++"); */}
//    | MINUSMINUS {/* $$ = new string("--"); */}
//    | COMMA {/* $$ = new string(","); */}
//    | ARROWSTAR {/* $$ = new string("->*"); */}
//    | ARROW {/* $$ = new string("->"); */}
//    | LEFTPAREN RIGHTPAREN {/* $$ = new string("()"); */}
//    | LEFTARRAY RIGHTARRAY {/* $$ = new string("[]"); */}
//  ;


// **********  1.12  Templates [gram.temp] **********
//template_declaration
//    : export_opt KW_template LESS
//    {}
//    template_parameter_list GREATER
//    {}
//    declaration 
//    {} 
//  ;

//export_opt
//: KW_export {}
//| /* Empty */ {}
//  ;

//template_parameter_list
//  : template_parameter 
//    {}
//  | template_parameter_list COMMA template_parameter 
//    {}
//  ;

//template_parameter
//  : type_parameter {}
//  | parameter_declaration 	
//    {}
//  ;

//template_opt
//: KW_template {}
//| /* Empty */ {}
//  ;

//type_parameter
//  : KW_class identifier_opt		
//    {}
//  | KW_class identifier_opt EQUAL type_id 
//    {}
//  | KW_typename identifier_opt	
//    {}
//  | KW_typename identifier_opt EQUAL type_id
//    {}
//  | KW_template LESS template_parameter_list GREATER KW_class  identifier_opt
//    {}
//  | KW_template LESS template_parameter_list GREATER KW_class  
//	identifier_opt EQUAL any_id_expression
//    {}
//  ;

identifier_opt
  : any_identifier
	{}
  | /* Empty */ {}
  ;

//template_id
//  : template_name LESS
//    template_argument_list_opt GREATER
//    {}
//  ;


//template_argument_list
//  : template_argument
//    {}
//  | template_argument_list COMMA template_argument
//    {}
//  ;

//template_argument_list_opt
//  : template_argument_list {}
//  |  /* Empty */ {}
//  ;

//template_argument
//  : assignment_expression {}
//  | type_id {}
//  | id_expression {}
//  ;

//explicit_instantiation
//  : KW_template declaration {}
//  ;

//explicit_specialization
//  : KW_template LESS GREATER declaration {}
//  ;


// **********  1.13  Exception handling [gram.except] **********
//try_block
//  : KW_try compound_statement handler_seq
//    {}
//  ;

//
//  : KW_try ctor_initializer_opt function_body handler_seq
//    {}
//  ;

//handler_seq
//  : handler handler_seq_opt
//  {}
//  ;

//handler_seq_opt
//  : handler_seq {}
//  | /* Empty */ {}
//  ;

//handler
//  : KW_catch LEFTPAREN exception_declaration RIGHTPAREN compound_statement
//    {}
//  ;

//exception_declaration
//  : type_specifier_seq declarator
//    {}
//  | type_specifier_seq abstract_declarator
//    {}
//  | type_specifier_seq
//    {}
//  | ELLIPSES
//    {}
//  ;

//throw_expression
//: KW_throw assignment_expression_opt
//  {}
//  ;

assignment_expression_opt
: assignment_expression {}
| /* Empty */ {}
  ;

//exception_specification
//  : KW_throw LEFTPAREN type_id_list_opt RIGHTPAREN
//    {}
//  ;

//exception_specification_opt
//  : exception_specification {}
//  | /* Empty */ {}
//  ;

//type_id_list
//  : type_id
//    {}
//  | type_id_list COMMA type_id
//    {}
//  ;

//type_id_list_opt
//  : type_id_list {}
//  | /* Empty */ {}
//  ;

// **********  Our hack **********

//any_id_expression
//  : any_unqualified_id {}
//  | any_qualified_id {}
//  ;

//any_unqualified_id
//  : any_identifier {}
//  | operator_function_id {}
//  | conversion_function_id {}
//  | COMPLEMENT class_name 	
//    {
//    }
//  | template_id {}
//  ;

//any_qualified_id
//  : colcol_opt nested_name_specifier template_opt any_unqualified_id
//	    {}
//  | COLCOL any_identifier {}
//  | COLCOL operator_function_id {}
//  | COLCOL template_id {}
//  ;

// **********  1.14  Preprocessing directives [gram.cpp] **********

%%
