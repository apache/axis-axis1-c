// Deploy.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "TranslationUnit.h"
#include <string>
#include <map>
using namespace std;

extern TranslationUnit* g_pTranslationUnit;
extern int yyparse();
extern void init_keyword_map();
int parse_header_file(const char *filename);
extern FILE *yyin;
extern list<string> g_classesfound;
//this map is populated with the type mapping and the services informaiion
//by the WSDD parser
map<string, string> g_ClassNamespaces; 

int main(int argc, char* argv[])
{
	init_keyword_map();
	//add predefined classes to the list so that parser recognizes them
	g_classesfound.push_back("IAccessBean");
	//parse wsdd files
	g_ClassNamespaces["webservice"] = "http://www.opensource.lk/webservice";
	g_ClassNamespaces["root"] = "http://www.opensource.lk/root";
	//parse web service header files
	if (!parse_header_file("ws.h"))
	{
		g_pTranslationUnit->GenerateWrapperClassDef();
		g_pTranslationUnit->GenerateWrapperClassImpl();
	}
	return 0;
}

int parse_header_file(const char *filename)
{
	int error = 0;
	if (filename) {
		if (yyin = fopen( filename, "r" )) {
			error = yyparse();
			if ( error ) { fclose(yyin); return 1;}
			fclose(yyin);
			return 0;
		}
		else {
			return 2;
		}
	}
	else {
		return 3;
	}
}