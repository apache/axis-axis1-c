#include <io.h>
#include <iostream>
#include "platforms\PlatformAutoSense.hpp"
#include "common\AxisConfig.h"

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

ECONFIG	ReadConfigOptions( int iParamCount, char * pszParamArray[]);
bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, DLLNAMES * psDLLNames);
const char * CreateConfigElement( DLLNAMES * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType);
void GetHomeAndLibrary( DLLNAMES * psDLLNames, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default);
void Initialise( DLLNAMES * psDLLNames, int * piConfigInfoArray);
void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, DLLNAMES * psDLLNames, int * piConfigInfoArray);
