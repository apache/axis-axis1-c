#include "FileFunctions.hpp"
#include "AxisConfiguration.hpp"
#include "MissingCFunctions.hpp"
#include "AxisConfigurationLibraries.hpp"

// Client -a c:\wscc -o obj\bin -m on -th transport.dll -c channel.dll -cs sslChannel.dll -x xerces.dll -cl client.log

int main( int argc, char * argv[])
{
	LIST			sDLLNames;
	int				iConfigInfoArray[eConfigMax];
	CHOICELIST		sChoiceList[] = { {PLATFORM_TRANSPORTHTTP_PATH,	"HTTP Transport library",											AXCONF_TRANSPORTHTTP_TAGNAME,		eHTTPTransport,		eClientAndServer},
									  {PLATFORM_CHANNEL_PATH,		"HTTP Channel library",												AXCONF_CHANNEL_HTTP_TAGNAME,		eHTTPChannel,		eClientAndServer},
#if WIN32
									  {"HTTPSSLChannel.dll",		"HTTP SSL Channel library",											AXCONF_SSLCHANNEL_HTTP_TAGNAME,		eHTTPSSLChannel,	eClientAndServer},
#else
									  {"libhttp_channelssl.so",		"HTTP SSL Channel library",											AXCONF_SSLCHANNEL_HTTP_TAGNAME,		eHTTPSSLChannel,	eClientAndServer},
#endif
									  {PLATFORM_XMLPARSER_PATH,		"Axis XML Parser library",											AXCONF_XMLPARSER_TAGNAME,			eXMLParser,			eClientAndServer},
									  {"SMTPTRANSPORT",				"SMTP Transport library",											AXCONF_TRANSPORTSMTP_TAGNAME,		eSMTPTransport,		eClientAndServer},
									  {"LOG",						"client trace log path (only required if you want client trace)",	AXCONF_CLIENTLOGPATH_TAGNAME,		eClientLog,			eClient},
									  {"WSDD",						"client WSDD path",													AXCONF_CLIENTWSDDFILEPATH_TAGNAME,	eClientWSDD,		eClient},
									  {"LOG",						"server trace log path (only required if you want server trace)",	AXCONF_LOGPATH_TAGNAME,				eServerLog,			eServer},
									  {"WSDD",						"server WSDD path",													AXCONF_WSDDFILEPATH_TAGNAME,		eServerWSDD,		eServer},
									  {"",							"",																	AXCONF_NODENAME_TAGNAME,			eUnknown,			eServer},
									  {"",							"",																	AXCONF_LISTENPORT_TAGNAME,			eUnknown,			eServer},
									  {"",							"SSL Options",														AXCONF_SECUREINFO_TAGNAME,			eSSLOptions,		eClientAndServer},
									  {"",							"Root directory",													0,									eUnknown,			eEmpty},
									  {"",							"library offset directory",											0,									eUnknown,			eEmpty},
									  {"",							"volume of output",													0,									eUnknown,			eClientAndServer}};
	bool			bSuccess = false;
	LIST			sFileNameList;
	char *			psDefaultParamList[eConfigMax];
#if WIN32
	char			cSlash = '\\';
	char *			pszPackageName = "axis-c-1.6-Win32-bin\\bin";
#else
	char			cSlash = '/';
	char *			pszPackageName = "axis-c-1.6-Linux-bin/bin";
#endif
	char			szAxisCpp_Deploy[256];


	Initialise( &sDLLNames, iConfigInfoArray, &sFileNameList, (char **) psDefaultParamList);

	switch( ReadConfigOptions( argc, argv, (char **) psDefaultParamList, cSlash))
	{
		case eEmpty:
		{
			cout << "Usage:" << endl;
			cout << "AxisConfiguration Client [params1]\tConfigure the client side." << endl;
			cout << "AxisConfiguration Server [params2]\tConfigure the server side." << endl;
			cout << "AxisConfiguration Both [params3]\tConfigure the client and server side." << endl << endl;
			cout << "The param list is as follows:-" << endl;
			cout << "-a  root directory of Axis download (AXISCPP_HOME)" << endl;
#if WIN32
			cout << "    example: -a c:\\Axis" << endl;
#else
			cout << "    example: -a /home/userid/Axis" << endl;
#endif
			cout << "-o  directory offset from AXISCPP_HOME to object files" << endl;
#if WIN32
			cout << "    example: -o " << pszPackageName << endl;
#else
			cout << "    example: -o " << pszPackageName << endl;
#endif
			cout << "-th transport library name" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
#if WIN32
			cout << "    -th HTTPTransport.dll" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -th c:\\Axis\\" << pszPackageName << "\\HTTPTransport.dll" << endl;
#else
			cout << "    -th libhttp_transport.so" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -th /home/userid/Axis/" << pszPackageName << "/libhttp_transport.so" << endl;
#endif
			cout << "-c  channel library name" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
#if WIN32
			cout << "    -c HTTPChannel.dll" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -c c:\\Axis\\" << pszPackageName << "\\HTTPChannel.dll" << endl;
#else
			cout << "    -c libhttp_channel.so" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -c /home/userid/Axis/" << pszPackageName << "/libhttp_channel.so" << endl;
#endif
			cout << "-cs ssl channel library name" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
#if WIN32
			cout << "    -cs HTTPSSLChannel.dll" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -cs c:\\Axis\\" << pszPackageName << "\\HTTPSSLChannel.dll" << endl;
#else
			cout << "    -cs libhttp_channelssl.so" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -cs /home/userid/Axis/" << pszPackageName << "/libhttp_channelssl.so" << endl;
#endif
			cout << "-x  xerces library name" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
#if WIN32
			cout << "    -x AxisXMLParserXerces.dll" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -x c:\\Axis\\" << pszPackageName << "\\AxisXMLParserXerces.dll" << endl;
#else
			cout << "    -x libaxis_xerces.so" << endl;
			cout << "    example (without -a and -o defined): " << endl;
			cout << "    -x /home/userid/Axis/" << pszPackageName << "/libaxis_xerces.so" << endl;
#endif
			cout << "-m  merge with existing configuration file" << endl;
			cout << "    example: -m on|off (the default is 'off' meaning 'overwrite')" << endl;
			cout << "Client Specific" << endl;
			cout << "-cl client log filename" << endl;
			cout << "    if -a has been defined, then only the filename is required." << endl;
			cout << "    Otherwise the fully qualified path will be required." << endl;
			cout << "    (NB: You can still override the -a and -o definitions by using" << endl;
			cout << "    a fully qulified path).  To ignore the client log, using 'ignore'" << endl;
			cout << "    instead of a filename.  Example (with -a defined): " << endl;
			cout << "    -cl client.log" << endl;
			cout << "    example (without -a defined): " << endl;
#if WIN32
			cout << "    -cl c:\\Axis\\client.log" << endl;
#else
			cout << "    -cl /home/userid/Axis/client.log" << endl;
#endif
			cout << "-cw client WSDD filename" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
			cout << "    -cw client.wsdd" << endl;
			cout << "    example (without -a and -o defined): " << endl;
#if WIN32
			cout << "    -cw c:\\Axis\\WSDD\\client.wsdd" << endl;
#else
			cout << "    -cw /home/userid/Axis/WSDD/client.wsdd" << endl;
#endif
			cout << "Server Specific" << endl;
			cout << "-sl server log filename" << endl;
			cout << "    if -a has been defined, then only the filename is required." << endl;
			cout << "    Otherwise the fully qualified path will be required." << endl;
			cout << "    (NB: You can still override the -a and -o definitions by using" << endl;
			cout << "    a fully qulified path)." << endl;
			cout << "    example (with -a defined): " << endl;
			cout << "    -sl server.log" << endl;
			cout << "    example (without -a defined): " << endl;
#if WIN32
			cout << "    -sl c:\\Axis\\server.log" << endl;
#else
			cout << "    -sl /home/userid/Axis/server.log" << endl;
#endif
			cout << "-sw server WSDD filename" << endl;
			cout << "    if -a and -o have both already been defined, then only the" << endl;
			cout << "    filename is required.  Otherwise the fully qualified path will" << endl;
			cout << "    be required (NB: You can still override the -a and -o definitions" << endl;
			cout << "    by using a fully qulified path)." << endl;
			cout << "    example (with -a and -o defined): " << endl;
			cout << "    -sw server.wsdd" << endl;
			cout << "    example (without -a and -o defined): " << endl;
#if WIN32
			cout << "    -sw c:\\Axis\\WSDD\\server.wsdd" << endl;
#else
			cout << "    -sw /home/userid/Axis/WSDD/server.wsdd" << endl;
#endif
			break;
		}

		case eClient:
		{
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Client Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default, &sFileNameList, (char **) psDefaultParamList, pszPackageName);

			int	iChoiceCount = 0;

			while( sChoiceList[iChoiceCount].eConfigType != eUnknown)
			{
				if( sChoiceList[iChoiceCount].eConfig & eClient)
				{
					if( sChoiceList[iChoiceCount].eConfigType == eClientLog ||
						sChoiceList[iChoiceCount].eConfigType == eServerLog)
					{
						char	szLog[256];

						szLog[0] = '\0';

						if( sChoiceList[iChoiceCount].eConfigType == eClientLog)
						{
							if( psDefaultParamList[eClientLog] == NULL)
							{
								cout << "Enter name of client trace/log file: ";
							}
							else
							{
								strcpy( szLog, psDefaultParamList[eClientLog]);
							}
						}
						else
						{
							if( psDefaultParamList[eServerLog] == NULL)
							{
								cout << "Enter name of server trace/log file: ";
							}
							else
							{
								strcpy( szLog, psDefaultParamList[eServerLog]);
							}
						}

						char	szFilename[512];

						if( szLog[0] == '\0')
						{
							cin >> szLog;
						}

						if( StringCompare( "IGNORE", szLog))
						{
							iConfigInfoArray[sChoiceList[iChoiceCount].eConfigType] = PopulateNewDLLNameInfo( &sDLLNames, NULL, NULL, true);
						}
						else
						{
#if WIN32
							sprintf( szFilename, "%s\\%s", szAxisCpp_Deploy, szLog);
#else
							sprintf( szFilename, "%s/%s", szAxisCpp_Deploy, szLog);
#endif
							iConfigInfoArray[sChoiceList[iChoiceCount].eConfigType] = PopulateNewDLLNameInfo( &sDLLNames, szLog, szFilename, true);
						}
					}
					else
					{
						SelectFileFromList( sChoiceList, iChoiceCount, &sDLLNames, iConfigInfoArray, (char **) psDefaultParamList, &sFileNameList, szAxisCpp_Deploy);
					}
				}

				iChoiceCount++;
			}

			if( psDefaultParamList[eSSLOptions] != NULL)
			{
				iConfigInfoArray[eSSLOptions] = PopulateNewDLLNameInfo( &sDLLNames, NULL, psDefaultParamList[eSSLOptions], true);
			}

			if( psDefaultParamList[eAxisConfigDir] != NULL)
			{
				iConfigInfoArray[eAxisConfigDir] = PopulateNewDLLNameInfo( &sDLLNames, NULL, psDefaultParamList[eAxisConfigDir], true);
			}

			bSuccess = true;

			break;
		}

		case eServer:
		{
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Server Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default, &sFileNameList, (char **) psDefaultParamList, pszPackageName);

			bSuccess = true;

			break;
		}

		case eClientAndServer:
		{
			cout << "Axis Client and Server Configuration" << endl;

			bSuccess = true;
			break;
		}
	}

	if( bSuccess)
	{
		if( psDefaultParamList[eAxisConfigDir] == NULL)
		{
			WriteAxisConfigFile( &sDLLNames, iConfigInfoArray, sChoiceList, StringCompare( psDefaultParamList[eMerge], "on"), szAxisCpp_Deploy, cSlash, StringCompare( psDefaultParamList[eBackup], "true"));
		}
		else
		{
			WriteAxisConfigFile( &sDLLNames, iConfigInfoArray, sChoiceList, StringCompare( psDefaultParamList[eMerge], "on"), psDefaultParamList[eAxisConfigDir], cSlash, StringCompare( psDefaultParamList[eBackup], "true"));
		}
	}

	Destroy( &sDLLNames, &sFileNameList, (char **) psDefaultParamList);

	return (int) bSuccess;
}

ECONFIG	ReadConfigOptions( int iParamCount, char * pParamArray[], char ** ppsDefaultParamList, char cSlash)
{
	ECONFIG		eConfig = eEmpty;
	OPTIONLIST	sOptions[] = {{eHTTPTransport,	"TH"},
							  {eHTTPChannel,	"C"},
							  {eHTTPSSLChannel,	"CS"},
							  {eXMLParser,		"X"},
							  {eSMTPTransport,	"TS"},
							  {eClientLog,		"CL"},
							  {eClientWSDD,		"CW"},
							  {eServerLog,		"SL"},
							  {eRootDirectory,	"A"},
							  {eOffsetToLibs,	"O"},
							  {eServerWSDD,		"SW"},
							  {eSSLOptions,		"SO"},
							  {eVolume,			"V"},
							  {eAxisConfigDir,	"ACD"},
							  {eBackup,			"B"},
							  {eMerge,			"M"}};

	ppsDefaultParamList[eMerge] = (char *) malloc( strlen( "off "));
	ppsDefaultParamList[eVolume] = (char *) malloc( strlen( "normal "));
	ppsDefaultParamList[eBackup] = (char *) malloc( strlen( "true "));

	strcpy( ppsDefaultParamList[eMerge], "off");
	strcpy( ppsDefaultParamList[eVolume], "normal");
	strcpy( ppsDefaultParamList[eBackup], "true");

	for( int iCount = 0; iCount < iParamCount; iCount++)
	{
		if( StringCompare( pParamArray[iCount], "Client"))
		{
			eConfig = (ECONFIG)((int) eConfig | eClient);
		}
		else if( StringCompare( pParamArray[iCount], "Server"))
		{
			eConfig = (ECONFIG)((int) eConfig | eServer);
		}
		else if( StringCompare( pParamArray[iCount], "Both"))
		{
			eConfig = (ECONFIG)((int) eConfig | eClientAndServer);
		}

		if( *pParamArray[iCount] == '-')
		{
			bool	bOptionFound = false;
			int		iIndex = 0;

			do
			{
				if( !(bOptionFound = StringCompare( (pParamArray[iCount] + 1), sOptions[iIndex].pszOption)))
				{
					iIndex++;
				}
			} while( iIndex < (eConfigMax - 1) && !bOptionFound);

			if( bOptionFound)
			{
				if( ppsDefaultParamList[sOptions[iIndex].eConfType] != NULL)
				{
					free( (void *) ppsDefaultParamList[sOptions[iIndex].eConfType]);
				}

				iCount++;

				if( iCount < iParamCount)
				{
					if( ppsDefaultParamList[eOffsetToLibs] != NULL &&
						ppsDefaultParamList[eRootDirectory] != NULL &&
						!(sOptions[iIndex].eConfType == eClientLog || 
						  sOptions[iIndex].eConfType == eServerLog ||
						  sOptions[iIndex].eConfType == eBackup ||
						  sOptions[iIndex].eConfType == eSSLOptions) &&
						strchr( pParamArray[iCount], cSlash) == NULL)
					{
						char	szLocation[512];

						sprintf( szLocation, "%s%c%s%c%s", ppsDefaultParamList[eRootDirectory], cSlash, ppsDefaultParamList[eOffsetToLibs], cSlash, pParamArray[iCount]);

						ppsDefaultParamList[sOptions[iIndex].eConfType] = (char *) malloc( strlen( szLocation) + 1);

						strcpy( ppsDefaultParamList[sOptions[iIndex].eConfType], szLocation);
					}
					else
					{
						ppsDefaultParamList[sOptions[iIndex].eConfType] = (char *) malloc( strlen( pParamArray[iCount]) + 1);

						strcpy( ppsDefaultParamList[sOptions[iIndex].eConfType], pParamArray[iCount]);
					}
				}
			}
			else
			{
				cout << "Option: " << pParamArray[iCount] << " has been ignored." << endl;
			}
		}
	}

	return eConfig;
}


void GetHomeAndLibrary( LIST * psDLLNames, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, LIST * psFileNameList, char ** ppsDefaultParamList, char * pszPackageName)
{
	char *	pszCurrentAxisCppDeployEnv = getenv( "AXISCPP_DEPLOY");

	if( ppsDefaultParamList[eAxisConfigDir] == NULL)
	{
		if( ppsDefaultParamList[eRootDirectory] == NULL)
		{
#if WIN32
			cout << "Type in the Axis fully qualified directory path (e.g. C:\\Axis)" << endl
				<< "used when Axis was unzipped (NB: this directory must also contain the" << endl
				<< "axiscpp.conf file).";
#else
			cout << "Type in the Axis fully qualified directory path (e.g. /home/Axis)" << endl
				<< "used when Axis was unzipped (NB: this directory must also contain the" << endl
				<< "etc/axiscpp.conf file).";
#endif
			if( pszCurrentAxisCppDeployEnv != NULL)
			{
				cout << "  Type '*' to used the existing value of the environment" << endl;
				cout << "variable (i.e. '" << pszCurrentAxisCppDeployEnv << "').";
			}

			cout << endl << "AXISCPP_DEPLOY = ";
			cin >> pszAxisCpp_Deploy;

			if( *pszAxisCpp_Deploy == '*' && pszCurrentAxisCppDeployEnv != NULL)
			{
				strcpy( pszAxisCpp_Deploy, pszCurrentAxisCppDeployEnv);
			}
		}
		else
		{
			strcpy( pszAxisCpp_Deploy, ppsDefaultParamList[eRootDirectory]);
		}

		if( ppsDefaultParamList[eOffsetToLibs] != NULL)
		{
			strcpy( pszAxis_Bin, ppsDefaultParamList[eOffsetToLibs]);

			if( !CheckAxisBinDirectoryExists( pszAxisCpp_Deploy, pszAxis_Bin, pszAxis_Bin_Default, psDLLNames, psFileNameList))
			{
				cout << "Axis binaries directory not found." << endl;

				free( (void *) ppsDefaultParamList[eOffsetToLibs]);

				ppsDefaultParamList[eOffsetToLibs] = NULL;
			}
		}

		strcpy( pszAxis_Bin_Default, pszPackageName);

		if( ppsDefaultParamList[eOffsetToLibs] == NULL)
		{
			if( pszCurrentAxisCppDeployEnv == NULL)
			{
				cout << endl << "Instruction:" << endl
					 << "You will need to create an environment variable called " << endl
					 << "\"AXISCPP_DEPLOY\" and set it to " << pszAxisCpp_Deploy << "." << endl
					 << "On the command line this would be:-" << endl
#if WIN32
					 << "SET AXISCPP_DEPLOY=" << pszAxisCpp_Deploy << endl;
#else
					 << "EXPORT AXISCPP_DEPLOY=" << pszAxisCpp_Deploy << endl;
#endif
			}

			cout << endl;

			do
			{
#if WIN32
				cout << "Type in the directory where the Axis libraries (e.g. axis_client.dll) can be" << endl
					<< "found.  (If you type '*', it will use the default '" << pszAxis_Bin_Default << "')." << endl;
#else
				cout << "Type in the directory where the Axis libraries (e.g. axis_client.so) can be" << endl
					<< "found.  (If you type '*', it will use the default '" << pszAxis_Bin_Default << "')." << endl;
#endif
				cout << "Axis binaries directory = ";
				cin >> pszAxis_Bin;

				if( !strcmp( pszAxis_Bin, "*"))
				{
					strcpy( pszAxis_Bin, pszAxis_Bin_Default);
				}
			} while( !CheckAxisBinDirectoryExists( pszAxisCpp_Deploy, pszAxis_Bin, pszAxis_Bin_Default, psDLLNames, psFileNameList));
		}
	}

	cout << endl << "Begin to configure the AXISCPP.CONF file." << endl;
}

void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, LIST * psDLLNames, int * piConfigInfoArray, char ** ppsDefaultParamList, LIST * psFileNameList, char * pszAxisCpp_Deploy)
{
	cout << endl << "Select the filename for the " << psChoiceList[iChoiceCount].pszElementDescription << "." << endl;

	int		iDLLCount = 0;
	LIST	sDLLOffsetList;
	bool	bHTTPTransportFound = false;

	memset( &sDLLOffsetList, 0, sizeof( LIST));

	do
	{
		char *	pszUpper = new char[strlen( psChoiceList[iChoiceCount].pszElement) + 1];

		strcpy( pszUpper, psChoiceList[iChoiceCount].pszElement);

		StringToUpper( pszUpper);

		char *	pszExtn = strchr( pszUpper, '.');

		if( pszExtn != NULL)
		{
			*pszExtn = '\0';
		}

		while( iDLLCount < psDLLNames->iCount)
		{
			DLLNAMEINFO *	pszDLLNameInfo = ((DLLNAMEINFO *) psDLLNames->ppArray[iDLLCount]);

			if( pszDLLNameInfo->pszDLLName != NULL &&
				strstr( pszDLLNameInfo->pszDLLName, pszUpper) != NULL)
			{
				int *	piDLLOffset = (int *) GetNextListElement( &sDLLOffsetList, sizeof( int));

				*piDLLOffset = iDLLCount;

				cout << sDLLOffsetList.iCount << ".\t" << pszDLLNameInfo->pszDLLFilename << endl;
			}

			iDLLCount++;
		}

		free( pszUpper);

		if( ppsDefaultParamList[psChoiceList[iChoiceCount].eConfigType] != NULL &&
			FileExists( ppsDefaultParamList[psChoiceList[iChoiceCount].eConfigType]))
		{
			piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = PopulateNewDLLNameInfo( psDLLNames, NULL, ppsDefaultParamList[psChoiceList[iChoiceCount].eConfigType], true);

			bHTTPTransportFound = true;

			cout << "Choices have been overridden by input parameter." << endl;
		}
		else
		{
			if( sDLLOffsetList.iCount > 0)
			{
				if( sDLLOffsetList.iCount > 1)
				{
					cout << "Select an index between 1 and " << sDLLOffsetList.iCount << " : ";

					int	iChoice;

					cin >> iChoice;

					if( iChoice < 1 || iChoice > sDLLOffsetList.iCount)
					{
						cout << "Number was out of range." << endl;
					}
					else
					{
						((DLLNAMEINFO *) psDLLNames->ppArray[*((int *) sDLLOffsetList.ppArray[iChoice - 1])])->bAddToClientConfig = true;
						piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = *((int *) sDLLOffsetList.ppArray[iChoice - 1]);
						bHTTPTransportFound = true;
					}
				}
				else
				{
					cout << "Automatically selected " << ((DLLNAMEINFO *) psDLLNames->ppArray[*((int *) sDLLOffsetList.ppArray[0])])->pszDLLFilename << endl;

					((DLLNAMEINFO *) psDLLNames->ppArray[*((int *) sDLLOffsetList.ppArray[0])])->bAddToClientConfig = true;
					piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = *((int *) sDLLOffsetList.ppArray[0]);
					bHTTPTransportFound = true;
				}
			}
			else
			{
				cout << "There are no recognised file names for the type of file/library." << endl << "You will have to modify the configuration file namually." << endl << endl;

				bHTTPTransportFound = true;
			}
		}
	} while( !bHTTPTransportFound);

	for( int iCount = 0; iCount < sDLLOffsetList.iCount; iCount++)
	{
		free( sDLLOffsetList.ppArray[iCount]);
	}
}

void AddFilenameToList( LIST * psFileNameList, char * pszFilename)
{
	char *	psList = (char *) GetNextListElement( psFileNameList, (int) strlen( pszFilename) + 1);

	strcpy( psList, pszFilename);
}

bool FileExists( char * pszFilename)
{
	FILE *	fp = fopen( pszFilename, "r");
	bool	bSuccess = false;

	if( fp != NULL)
	{
		fclose( fp);

		bSuccess = true;
	}
	
	return bSuccess;
}
