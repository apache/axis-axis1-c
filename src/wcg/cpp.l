%{
  #include <map>
  #include <string>
  #include <iostream>
  
  using namespace std;

  #include "cppyacc.hpp"

  static int check_keyword(const char* name);
  int yyerror(char * msg);
  extern int yyparse();
  void do_newline();

  int line_number = 1;
  
  #define MAX_INCLUDE_DEPTH 10
  YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
  int include_stack_ptr = 0;  
%}

/***** Start state for comments *****/

%x COMMENT
%x PREPROCESSOR
/* the "incl" state is used for picking up the name
 * of an include file
 */
%x INCLUDE
/***** DEFINITIONS *****/

/* Whitespace */

NEWLINE         [\n]

WHITEC          ([ \t\f])

/* Integer Literals */

DEC_LIT     [1-9][0-9]*

OCT_LIT     0[0-7]*

HEX_DIGIT       [0-9A-Fa-f]

HEX_LIT     0[xX]{HEX_DIGIT}+

INT_SUFFIX      ([uU][lL]?)|([lL][uU]?)

INT_LIT     ({DEC_LIT}|{OCT_LIT}|{HEX_LIT}){INT_SUFFIX}?


/* Float Literals */

DIGIT_SEQ       [0-9]+

FRACT_CONST     ({DIGIT_SEQ}?\.{DIGIT_SEQ})|({DIGIT_SEQ}\.)

EXPONENT        [eE][+-]?{DIGIT_SEQ}

FLOAT_SUFFIX    [fFlL]

FLOAT_LIT   ({FRACT_CONST}{EXPONENT}?{FLOAT_SUFFIX}?)|({DIGIT_SEQ}{EXPONENT}{FLOAT_SUFFIX}?)


/* Characters and Strings */

HEX_QUAD        {HEX_DIGIT}{4}

UNI_CHAR        (\\[u]{HEX_QUAD})|(\\[U]{HEX_QUAD}{HEX_QUAD})

SIMPLE_ESC      \\['"?\\abfnrtv]
OCTAL_ESC       \\[0-7]{1,3}
HEX_ESC         \\x{HEX_DIGIT}+

ESC_SEQ         {SIMPLE_ESC}|{OCTAL_ESC}|{HEX_ESC}

C_CHAR          [^'\\\n]|{ESC_SEQ}|{UNI_CHAR}

CHAR_LIT    [L]?'{C_CHAR}+'

S_CHAR          [^"\\\n]|{ESC_SEQ}|{UNI_CHAR}

STRING_LIT  [L]?\"{S_CHAR}+\"


/* Identifiers */

NONDIGIT        {UNI_CHAR}|[_a-zA-Z]

IDENT           {NONDIGIT}({NONDIGIT}|[0-9])*


/***** LEXICAL RULES *****/


%%

"/*"      	         { BEGIN(COMMENT); }
<COMMENT>"*/"		 { BEGIN(0); }
<COMMENT>\n		 { do_newline(); }
<COMMENT>.		 { ; }

"//".*			 { ; }
 
"#"                      { BEGIN(PREPROCESSOR); }
<PREPROCESSOR>include    { BEGIN(INCLUDE); }
<PREPROCESSOR>\\\n       { do_newline(); }
<PREPROCESSOR>\n         { do_newline(); BEGIN(0); }
<PREPROCESSOR>.          { ; }
<INCLUDE>[ \t]*      		 /* eat the whitespace */
<INCLUDE>[^ \t\n]+   	{
        					if (include_stack_ptr >= MAX_INCLUDE_DEPTH)
            				{
            					cout << "Includes nested too deeply";
            					exit(1);
            				}
                  			string incfile = yytext;
							if (incfile.find('<') == string::npos) //open only from local path 
							{
        						include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
        						yyin = fopen(incfile.substr(1,incfile.length()-2).c_str(), "r");
        						if (!yyin)
                  				{
            						cout << "File included from "<< yytext << " is not found on path"<<endl;
                      				exit(1);
                           		}
        						yy_switch_to_buffer(yy_create_buffer( yyin, YY_BUF_SIZE ));
        						BEGIN(0);
        					}
							else
							{
								BEGIN(0);
							}
						}

<<EOF>> 				{
        					if ( --include_stack_ptr < 0 )
            				{
            					yyterminate();
            				}
        					else
            				{
            					yy_delete_buffer( YY_CURRENT_BUFFER );
            					yy_switch_to_buffer(include_stack[include_stack_ptr]);
            				}
        				}

"("                      { return LEFTPAREN; }
")"                      { return RIGHTPAREN; }
"{"                      { return LEFTBRACK; }
"}"                      { return RIGHTBRACK; }
"["                      { return LEFTARRAY; }
"]"                      { return RIGHTARRAY; }
"+"                      { return PLUS; }
"-"                      { return MINUS; }
"*"                      { return STAR; }
"/"                      { return DIVIDE; }
"%"                      { return MOD; }
">"                      { return GREATER; }
"<"                      { return LESS; }
"="                      { return EQUAL; }
"&"                      { return AND; }
"|"                      { return OR; }
"!"                      { return NOT; }
"^"                      { return XOR; }
","                      { return COMMA; }
";"                      { return SEMI; }
":"                      { return COLON; }
"~"                      { return COMPLEMENT; }
"."                      { return DOT; }
"?"                      { return QUESTION; }

"*="                      { return STAREQ; }
"/="                      { return DIVEQ; }
"%="                      { return MODEQ; }
"+="                      { return PLUSEQ; }
"-="                      { return MINUSEQ; }
"<<="                     { return LTLTEQ; }
">>="                     { return GTGTEQ; }
"&="                      { return ANDEQ; }
"^="                      { return XOREQ; }
"|="                      { return OREQ; }
"||"                      { return OROR; }
"&&"                      { return ANDAND; }
"=="                      { return EQEQ; }
"!="                      { return NOTEQ; }
"<="                      { return LEQ; }
">="                      { return GEQ; }
"<<"                      { return LTLT; }
">>"                      { return GTGT; }
".*"                      { return DOTSTAR; }
"->*"                     { return ARROWSTAR; }
"++"                      { return PLUSPLUS; }
"--"                      { return MINUSMINUS; }
"->"                      { return ARROW; }
"::"                      { return COLCOL; }
"..."                     { return ELLIPSES; }

{INT_LIT}		  { 
				return INTEGER_LITERAL; 
			  }
{FLOAT_LIT}               { return FLOATING_LITERAL; }
{CHAR_LIT}                { return CHARACTER_LITERAL; }
{STRING_LIT}              { return STRING_LITERAL; }

{IDENT}                   { return check_keyword(yytext); }

{WHITEC}                  ;
{NEWLINE}                 { do_newline(); }

.                         { yyerror("Lexical Error"); }

%%

void init_keyword_map()
{
    lexer_keys["and"]=ANDAND;
    lexer_keys["and_eq"]=ANDEQ;
    lexer_keys["asm"]=KW_asm;
    lexer_keys["auto"]=KW_auto;
    lexer_keys["bitand"]=AND;
    lexer_keys["bitor"]=OR;
    lexer_keys["bool"]=KW_bool;
    lexer_keys["break"]=KW_break;
    lexer_keys["case"]=KW_case;
    lexer_keys["catch"]=KW_catch;
    lexer_keys["char"]=KW_char;
    lexer_keys["class"]=KW_class;
    lexer_keys["compl"]=COMPLEMENT;
    lexer_keys["const"]=KW_const;
    lexer_keys["const_cast"]=KW_const_cast;
    lexer_keys["continue"]=KW_continue;
    lexer_keys["default"]=KW_default;
    lexer_keys["delete"]=KW_delete;
    lexer_keys["do"]=KW_do;
    lexer_keys["double"]=KW_double;
    lexer_keys["dynamic_cast"]=KW_dynamic_cast;
    lexer_keys["else"]=KW_else;
    lexer_keys["enum"]=KW_enum;
    lexer_keys["explicit"]=KW_explicit;
    lexer_keys["export"]=KW_export;
    lexer_keys["extern"]=KW_extern;
    lexer_keys["false"]=KW_false;
    lexer_keys["float"]=KW_float;
    lexer_keys["for"]=KW_for;
    lexer_keys["friend"]=KW_friend;
    lexer_keys["goto"]=KW_goto;
    lexer_keys["if"]=KW_if;
    lexer_keys["inline"]=KW_inline;
    lexer_keys["int"]=KW_int;
    lexer_keys["long"]=KW_long;
    lexer_keys["mutable"]=KW_mutable;
    lexer_keys["namespace"]=KW_namespace;
    lexer_keys["new"]=KW_new;
    lexer_keys["not"]=NOT;
    lexer_keys["not_eq"]=NOTEQ;
    lexer_keys["operator"]=KW_operator;
    lexer_keys["or"]=OROR;
    lexer_keys["or_eq"]=OREQ;
    lexer_keys["private"]=KW_private;
    lexer_keys["protected"]=KW_protected;
    lexer_keys["public"]=KW_public;
    lexer_keys["register"]=KW_register;
    lexer_keys["reinterpret_cast"]=KW_reinterpret_cast;
    lexer_keys["return"]=KW_return;
    lexer_keys["short"]=KW_short;
    lexer_keys["signed"]=KW_signed;
    lexer_keys["sizeof"]=KW_sizeof;
    lexer_keys["static"]=KW_static;
    lexer_keys["static_cast"]=KW_static_cast;
    lexer_keys["struct"]=KW_struct;
    lexer_keys["switch"]=KW_switch;
    lexer_keys["template"]=KW_template;
    lexer_keys["this"]=KW_this;
    lexer_keys["throw"]=KW_throw;
    lexer_keys["true"]=KW_true;
    lexer_keys["try"]=KW_try;
    lexer_keys["typedef"]=KW_typedef;
    lexer_keys["typeid"]=KW_typeid;
    lexer_keys["typename"]=KW_typename;
    lexer_keys["union"]=KW_union;
    lexer_keys["unsigned"]=KW_unsigned;
    lexer_keys["using"]=KW_using;
    lexer_keys["virtual"]=KW_virtual;
    lexer_keys["void"]=KW_void;
    lexer_keys["volatile"]=KW_volatile;
    lexer_keys["wchar_t"]=KW_wchar_t;
    lexer_keys["while"]=KW_while;
    lexer_keys["xor"]=XOR;
    lexer_keys["xor_eq"]=XOREQ;
	//following are added and considered basic types for Axis WCG. 
    lexer_keys["string"]=KW_string;
};  

int yywrap() 
{
   line_number = 0;
   return 1;
};

void do_newline()
{
  line_number++; 
}

//***********************************************************************/
//      check_keyword -- check for keyword or identifier
//***********************************************************************/

static int check_keyword(const char* name) 
{
  int tok = IDENTIFIER;
  string sname = name;
  if (!sname.empty())
  {
    //cout << sname.c_str() << endl;
    if (lexer_keys.find(sname) != lexer_keys.end())
    {
      tok = lexer_keys[sname];
    }
    else if (is_defined_class(sname.c_str()))
    {
    	//cout << sname.c_str() << " is recognized as a class"<<endl;
			tok = ID_class_name;
    }
	else if (is_accessbean_macro(sname))
	{
		tok = ACCESSBEAN_MACRO;
	}
  }
  return tok;
}


//***********************************************************************/
//      yyerror -- give the text and line number
//***********************************************************************/

int yyerror(char * msg) 
{
  printf("%s at line number: %d\t", msg, line_number);
  printf(yytext);
  return 0;
}
