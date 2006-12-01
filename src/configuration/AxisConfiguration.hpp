#if !defined(__AXIS_CONFIG__)

#define __AXIS_CONFIG__

#include <iostream>
#include "platforms/PlatformAutoSense.hpp"
#include "common/AxisConfig.h"
#include "ListMethods.hpp"
#include "Instructions.hpp"

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
	eSSLOptions,
	eProgressInfo,
	eMerge,
	eAxisConfigDir,
	eBackup,
	eQueryMissingFiles,
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
	char *			pszElement;
	char *			pszElementDescription;
	char *			pszConfigName;
	ECONFIGTYPE		eConfigType;
	ECONFIG			eConfig;
} CHOICELIST;

typedef struct
{
	ECONFIGTYPE		eConfType;
	char *			pszOption;
} OPTIONLIST;

ECONFIG	ReadConfigOptions( int iParamCount, char * pszParamArray[], char ** ppsDefaultParamList, char cSlash);
bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, LIST * psLIST, LIST * psFileNameList);
void GetHomeAndLibrary( LIST * psLIST, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, LIST * psFileNameList, char ** ppsDefaultParamList, char * pszPackageName);
void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, LIST * psLIST, int * piConfigInfoArray, char ** ppsDefaultParamList, LIST * psFileNameList, char * pszAxisCpp_Deploy);
void AddFilenameToList( LIST * psFileNameList, char * pszFilename);
bool FileExists( char * pszFilename);

#endif
