#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#ifndef __ACTIONS_H_INCLUDED__
#define __ACTIONS_H_INCLUDED__
//this file contains all auxiliary structures needed to parse web service declaration files
#include "TranslationUnit.h"

#include <list>
#include <map>
#include <string>

using namespace std;

extern map<string,int> lexer_keys; //keyword map in the lexical analyzer.

//auxiliary enums used by the parser
enum CLASSTYPE {WSCLASS=1, BEANCLASS};

//auxiliary structs and type definitions used by the parser.

typedef list<int> token_list;
typedef list<string*> string_list;

struct expression
{
  union
  {
    int n;
  } expr;
};

typedef list<expression*> expression_list;

struct param_declarator
{
  token_list ptr_ops;        //optional
  string decl_id;    //must;
  expression_list arr_dim; //optional
};

struct param_decl
{
  string_list* decl_specs; //must
  param_declarator* param; //must
  bool bdef; //true if there is a default value
  expression* defval;
};

typedef list<param_decl*> param_decl_list;

struct base_specifier
{
	int access;
	string* class_name;
};

typedef list<base_specifier*> base_specifier_list;

struct class_head
{
	string* class_name;
	base_specifier_list* baselist;
};

struct member_declarator
{
	string* declarator_id;    //must
	param_decl_list* params;  //optional
  expression_list array_indexes;  //optional
  token_list ptr_ops;       //optional
  bool bpure;               //optional
  bool bdestructor;					//optional true if this is a destructor
  bool method;              //must
  expression* expr;         //optional
};

typedef list<member_declarator*> member_declarator_list;

//global functions used by the parser
void translation_unit_start();
bool is_defined_class(const char* identifier);
bool is_webservice_class(const char* classname);
void add_member_declaration(string_list* decl_specs, member_declarator_list* member_decl_list);

//global variables used by the parser
extern TranslationUnit* g_pTranslationUnit; //ultimate container of parsed information
extern string g_classname; //this holds the class name while the body of a class is being parsed.
extern list<string> g_classesfound;
extern int g_currentclasstype;
extern WSClass* g_pCurrentWSClass;
extern BeanClass* g_pCurrentBeanClass;
extern int g_currentaccessspecifier;
extern bool g_bdestructor_seen;

#endif //__ACTIONS_H_INCLUDED__
