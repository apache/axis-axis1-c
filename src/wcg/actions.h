/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#ifndef __ACTIONS_H_OF_AXIS_INCLUDED__
#define __ACTIONS_H_OF_AXIS_INCLUDED__
/* this file contains all auxiliary structures needed to parse web service 
 * declaration files
 */
#include "TranslationUnit.h"

#include <list>
#include <map>
#include <string>

using namespace std;

extern map<string,int> lexer_keys; /* keyword map in the lexical analyzer. */

/* auxiliary enums used by the parser */
enum CLASSTYPE {WSCLASS=1, BEANCLASS};

/* auxiliary structs and type definitions used by the parser. */

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
  token_list ptr_ops;        /* optional */
  string decl_id;    /* must; */
  expression_list arr_dim; /* optional */
};

struct param_decl
{
  string_list* decl_specs; /* must */
  param_declarator* param; /* must */
  bool bdef; /* true if there is a default value */
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
    string* declarator_id;    /* must */
    param_decl_list* params;  /* optional */
  expression_list array_indexes;  /* optional */
  token_list ptr_ops;       /* optional */
  bool bpure;               /* optional */
  bool bdestructor;         /* optional true if this is a destructor */
  bool method;              /* must */
  expression* expr;         /* optional */
};

typedef list<member_declarator*> member_declarator_list;

/* global functions used by the parser */
void translation_unit_start();
bool is_defined_class(const char* identifier);
bool is_webservice_class(const char* classname);
void add_member_declaration(string_list* decl_specs, 
                            member_declarator_list* member_decl_list);

/* global variables used by the parser */
extern TranslationUnit* g_pTranslationUnit;
/* ultimate container of parsed information */
extern string g_classname;
/* this holds the class name while the body of a class is being parsed. */
extern list<string> g_classesfound;
extern int g_currentclasstype;
extern WSClass* g_pCurrentWSClass;
extern BeanClass* g_pCurrentBeanClass;
extern int g_currentaccessspecifier;
extern bool g_bdestructor_seen;

#endif
