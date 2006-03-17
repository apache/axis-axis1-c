#if WIN32
#include <io.h>
#else
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#include <iostream>
#include "platforms/PlatformAutoSense.hpp"
#include "common/AxisConfig.h"

#undef _DEBUG

using namespace std;

typedef enum
{
	eEmpty,
	eClient,
	eServer,
	eClientAndServer
} ECONFIG;

typedef enum
{
	eUnknown,
	eHTTPTransport,
	eHTTPChannel,
	eHTTPSSLChannel,
	eXMLParser,
	eSMTPTransport,
	eClientLog,
	eClientWSDD,
	eServerLog,
	eServerWSDD,
	eRootDirectory,
	eOffsetToLibs,
	eConfigMax
} ECONFIGTYPE;

typedef struct
{
	char *	pszDLLName;
	char *	pszDLLFilename;
	bool	bAddToClientConfig;
} DLLNAMEINFO;

typedef struct
{
	int				iIndex;
	int				iMaxCount;
	DLLNAMEINFO **	ppsDLLName;
} DLLNAMES;

typedef struct
{
	char *			pszElement;
	char *			pszElementDescription;
	char *			pszConfigName;
	ECONFIGTYPE		eConfigType;
	ECONFIG			eConfig;
} CHOICELIST;

typedef struct
{
	int				iListCount;
	int				iListMax;
	char **			ppszListArray;
} FILENAMELIST;

typedef struct
{
	ECONFIGTYPE		eConfType;
	char *			pszOption;
} OPTIONLIST;

ECONFIG	ReadConfigOptions( int iParamCount, char * pszParamArray[], char ** ppsDefaultParamList);
bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList);
const char * CreateConfigElement( DLLNAMES * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType);
void GetHomeAndLibrary( DLLNAMES * psDLLNames, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, FILENAMELIST * psFileNameList, char ** ppsDefaultParamList);
void Initialise( DLLNAMES * psDLLNames, int * piConfigInfoArray, FILENAMELIST * psFileNameList, char ** ppsDefaultParamList);
void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, DLLNAMES * psDLLNames, int * piConfigInfoArray, char ** ppsDefaultParamList, FILENAMELIST * psFileNameList, char * pszAxisCpp_Deploy);
void WriteAxisConfigFile( DLLNAMES * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList);
bool ReadFilenamesInaDirectory( char * pszDirName, FILENAMELIST * psFileNameList);
void AddFilenameToList( FILENAMELIST * psFileNameList, char * pszFilename);
void Destroy( DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList, char ** psDefaultParamList);
bool StringCompare( char * pszString1, char * pszString2);
void StringToUpper( char * pszString);
void CreateNewDLLNamesElement( DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList);

