// Deploy.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include "TranslationUnit.h"
#include "File.h"
#include <string>
#include <map>
#include <iostream>
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

string g_sServiceFile = "";
string g_sWsFileName = "";
list<string> g_sLibraryPaths;
list<string> g_sAxisIncludePaths;
list<string> g_sCompiledLibs;
bool bDontDeleteSourceFiles;

void usage();
bool got_all_options();
bool is_parameters_valid();
bool is_webservice_header_compilable();

const char* VCCOMPILECOMMAND = "cl *.cpp /c /ML /W3 /GX /O2 ";
const char* VCLINKERCOMMAND = "link *.obj /dll /pdb:none /machine:I386 ";

#ifdef WIN32
#define OPTIONTAG '/'
#define DELETECOMMAND "del "
#else
#define OPTIONTAG '-'
#define DELETECOMMAND "rm -f "
#endif

#define COMPLILER_FAILED 2

#define DIRPATHLENGTH 256

int main(int argc, char* argv[])
{
	char currentdir[DIRPATHLENGTH];
	string arg;
	char opt;
	string optval = "";
	if (argc == 1) usage();
	bDontDeleteSourceFiles = false;
	for (int n=1; n<argc; n++)
	{
		arg = argv[n];
		if (arg[0] == OPTIONTAG)
		{
			if (!arg[1]) usage();
			opt = arg[1];
			optval = arg.substr(2);
			if ((opt != 'D') && (optval == "")) usage();
			switch (opt)
			{
			case 'I':
				g_sAxisIncludePaths.push_back(optval);
				break;
			case 'L':
				g_sLibraryPaths.push_back(optval);
				break;
			case 'l':
				g_sCompiledLibs.push_back(optval);
				break;
			case 'o':
				g_sServiceFile = optval;
				break;
			case 'D':
				bDontDeleteSourceFiles = true;
				break;
			default:
				usage();
			}
		}
		else if ((n+1) == argc)
		{
			if (g_sWsFileName != "") usage();
			g_sWsFileName = arg;	
		}
		else
		{
			cout << "too many parameters " << arg << endl << endl; 	
			usage();
		}
	}

	if (!got_all_options()) usage();
	cout << "Checking for validity of the parameters ..." ;
	if (!is_parameters_valid()) 
	{
		cout << "Invalid" << endl;
		exit(0); //at least one parameter is invalid
	}
	cout << "Valid" << endl;
	cout << "Checking web service header file ..." ;
	if (!is_webservice_header_compilable())
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Success" << endl;

	cout << "Parsing web service header file ..." ; 
	init_keyword_map();
	//add predefined classes to the list so that parser recognizes them
	g_classesfound.push_back("IAccessBean");
	//Change directory to the directory where the initial web service header file is 
	getcwd(currentdir, DIRPATHLENGTH);
	chdir(g_sWsFileName.substr(0, g_sWsFileName.find_last_of('/')).c_str());
	//parse wsdd files
	//parse web service header files
	if (parse_header_file(g_sWsFileName.c_str()))
	{
		cout << "Failed" << endl;
		exit(0);
	}
	chdir(currentdir);
	//here we have to continue parsing wsdd file
	cout << "Done" << endl;
	g_pTranslationUnit->SetWsFileName(g_sWsFileName.c_str());
	cout << "Generating Wrapper class declaration file ...";
	if (g_pTranslationUnit->GenerateWrapperClassDef()) 
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Done" << endl;
	cout << "Generating Wrapper class implimentation file ...";
	if (g_pTranslationUnit->GenerateWrapperClassImpl())
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Done" << endl;
	cout << "Generating Export functions file ...";
	if (g_pTranslationUnit->GenerateServiceFile(g_sServiceFile))
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Done" << endl;
	string command;
	list<string>::iterator sit;

	command = VCCOMPILECOMMAND;
	for (sit = g_sAxisIncludePaths.begin(); sit != g_sAxisIncludePaths.end(); sit++)
	{
		command += "-I" + (*sit) + " ";
	}	

	cout << "Compiling ...";
	if (system(command.c_str()) == -1)
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Done" << endl;
	
	command = VCLINKERCOMMAND;
	for (sit = g_sLibraryPaths.begin(); sit != g_sLibraryPaths.end(); sit++)
	{
		command += "/libpath:\"" + (*sit) + "\" ";
	}
	command += "/out:\"" + g_sServiceFile + ".dll\" ";
	for (sit = g_sCompiledLibs.begin(); sit != g_sCompiledLibs.end(); sit++)
	{
		command += (*sit) + " ";
	}
	cout << "Linking ...";
	if (system(command.c_str()) == -1)
	{
		cout << "Failed" << endl;
		exit(0);
	}
	cout << "Done" << endl;

	cout << "Deleting temporary files ...";
	command = DELETECOMMAND;
	command += "*.obj ";
	if (!bDontDeleteSourceFiles)
	{
		command += "*.cpp *.hpp";
	}
	system(command.c_str());
	cout << "Done" << endl;
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

void usage()
{
	cout << "Generates the depoyable web services for Axis C++" << endl;
	cout << "Usage: wcg " << endl;
//	cout << "\t/c<Compiler to use>" << endl;
	cout << "\t/I<path to axis include directory>" << endl;
	cout << "\t/L<path to web service library directory" << endl;
	cout << "\t/l<web service library file>" << endl;
	cout << "\t/o<output file>" << endl;
	cout << "\t<web service header file>" << endl;
	cout << endl;
	cout << "Axis Wrapper Class Generator (www.opensource.lk)" << endl;
	exit(0);
}

bool got_all_options()
{
	if (g_sServiceFile == "") return false;
	if (g_sWsFileName == "") return false;
	if (g_sLibraryPaths.empty()) return false;
	if (g_sAxisIncludePaths.empty()) return false;
	if (g_sCompiledLibs.empty()) return false;
	return true;
}

//we have to check the validity of the parameters here
//such as whether the include path exists, libraries exists etc.
//also should print the appropriate error message here
bool is_parameters_valid()
{
	cout << "did not check - assuming they are correct .. :)" << endl;
	return true;
}

bool is_webservice_header_compilable()
{
	//create a dummy cpp file that includes the given header file
	string filename = "Opensource_lk";
	File file(filename + ".cpp");
	file << "#include \"" << g_sWsFileName << "\"" << endl;
	file << "class Opensource { public: int axis;};" << endl;
	file.close();

	string command = "cl /c /w ";

	for (list<string>::iterator sit = g_sAxisIncludePaths.begin(); sit != g_sAxisIncludePaths.end(); sit++)
	{
		command += "-I" + (*sit) + " ";
	}	

	command += filename + ".cpp";
	if (system(command.c_str()) == COMPLILER_FAILED)
	{
		command = DELETECOMMAND;
		command += filename + ".*";
		system(command.c_str());
		return false;
	}
	command = DELETECOMMAND;
	command += filename + ".*";
	system(command.c_str());
	return true;
}


//cl *.cpp -I../../ -I../../../ -I../../../common /c /ML /W3 /GX /O2

//link *.obj Ws.lib /dll /pdb:none /machine:I386 /out:"Service.dll" /libpath:"" 

//gcc *.cpp -I../includepath -I/incpath2 -c -Wall -Wshadow -fPIC -O2

//gcc -shared -Wl,-soname,libmyservice.so -o libmyservice.so *.o Ws.a -lstdc++