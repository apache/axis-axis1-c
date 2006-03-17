#include "AxisConfiguration.hpp"

int main( int argc, char * argv[])
{
	DLLNAMES		sDLLNames;
	int				iConfigInfoArray[eConfigMax];
	CHOICELIST		sChoiceList[] = { {PLATFORM_TRANSPORTHTTP_PATH,	"HTTP Transport library",											AXCONF_TRANSPORTHTTP_TAGNAME,		eHTTPTransport,		eClientAndServer},
									  {PLATFORM_CHANNEL_PATH,		"HTTP Channel library",												AXCONF_CHANNEL_HTTP_TAGNAME,		eHTTPChannel,		eClientAndServer},
									  {"HTTPSSLCHANNEL",			"HTTP SSL Channel library",											AXCONF_SSLCHANNEL_HTTP_TAGNAME,		eHTTPSSLChannel,	eClientAndServer},
									  {PLATFORM_XMLPARSER_PATH,		"Axis XML Parser library",											AXCONF_XMLPARSER_TAGNAME,			eXMLParser,			eClientAndServer},
									  {"SMTPTRANSPORT",				"SMTP Transport library",											AXCONF_TRANSPORTSMTP_TAGNAME,		eSMTPTransport,		eClientAndServer},
									  {"LOG",						"client trace log path (only required if you want client trace)",	AXCONF_CLIENTLOGPATH_TAGNAME,		eClientLog,			eClient},
									  {"WSDD",						"client WSDD path",													AXCONF_CLIENTWSDDFILEPATH_TAGNAME,	eClientWSDD,		eClient},
									  {"LOG",						"server trace log path (only required if you want server trace)",	AXCONF_LOGPATH_TAGNAME,				eServerLog,			eServer},
									  {"WSDD",						"server WSDD path",													AXCONF_WSDDFILEPATH_TAGNAME,		eServerWSDD,		eServer},
									  {"",							"",																	AXCONF_NODENAME_TAGNAME,			eUnknown,			eServer},
									  {"",							"",																	AXCONF_LISTENPORT_TAGNAME,			eUnknown,			eServer},
									  {"",							"",																	AXCONF_SECUREINFO_TAGNAME,			eUnknown,			eClientAndServer},
									  {"",							"Root directory",													0,									eUnknown,			eEmpty},
									  {"",							"library offset directory",											0,									eUnknown,			eEmpty}};
	bool			bSuccess = false;
	FILENAMELIST	sFileNameList;
	char *			psDefaultParamList[eConfigMax];

	Initialise( &sDLLNames, iConfigInfoArray, &sFileNameList, (char **) psDefaultParamList);

	switch( ReadConfigOptions( argc, argv, (char **) psDefaultParamList))
	{
		case eEmpty:
		{
			cout << "Usage:" << endl;
			cout << "AxisConfiguration Client [params1]\tConfigure the client side." << endl;
			cout << "AxisConfiguration Server [params2]\tConfigure the server side." << endl;
			cout << "AxisConfiguration Both [params3]\tConfigure the client and server side." << endl << endl;
			cout << "The param list is as follows:-" << endl;
			cout << "Client" << endl;
			cout << "-a  root directory of Axis download (AXISCPP_HOME)" << endl;
			cout << "-o  offset from AXISCPP_HOME to object files" << endl;
			cout << "-t  transport library name" << endl;
			cout << "-c  channel library name" << endl;
			cout << "-cs ssl channel library name" << endl;
			cout << "-x  xerces library name" << endl;
			cout << "-cl client log filename" << endl;
			cout << "-cw client WSDD filename" << endl;
			cout << "Server" << endl;
			cout << "" << endl;
			cout << "Both" << endl;
			cout << "" << endl;
			break;
		}

		case eClient:
		{
			char	szAxisCpp_Deploy[256];
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Client Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default, &sFileNameList, (char **) psDefaultParamList);

			int	iChoiceCount = 0;

			while( sChoiceList[iChoiceCount].eConfigType != eUnknown)
			{
				if( sChoiceList[iChoiceCount].eConfig & eClient)
				{
					if( sChoiceList[iChoiceCount].eConfigType == eClientLog ||
						sChoiceList[iChoiceCount].eConfigType == eServerLog)
					{
						if(sChoiceList[iChoiceCount].eConfigType == eClientLog)
						{
							cout << "Enter name of client trace/log file: ";
						}
						else
						{
							cout << "Enter name of server trace/log file: ";
						}

						CreateNewDLLNamesElement( &sDLLNames, &sFileNameList);

						char 	szLog[256];
						char	szFilename[512];

						cin >> szLog;
						
						sDLLNames.ppsDLLName[sDLLNames.iIndex]->pszDLLName = (char *) malloc( strlen( szLog) + 1);

						strcpy( sDLLNames.ppsDLLName[sDLLNames.iIndex]->pszDLLName, szLog);

						sprintf( szFilename, "%s\\%s", szAxisCpp_Deploy, szLog);

						sDLLNames.ppsDLLName[sDLLNames.iIndex]->pszDLLFilename = (char *) malloc( strlen( szFilename) + 1);

						strcpy( sDLLNames.ppsDLLName[sDLLNames.iIndex]->pszDLLFilename, szFilename);

						iConfigInfoArray[sChoiceList[iChoiceCount].eConfigType] = sDLLNames.iIndex;

						sDLLNames.ppsDLLName[iChoiceCount]->bAddToClientConfig = true;

						sDLLNames.iIndex++;

					}
					else
					{
						SelectFileFromList( sChoiceList, iChoiceCount, &sDLLNames, iConfigInfoArray, (char **) psDefaultParamList);
					}
				}

				iChoiceCount++;
			}

			bSuccess = true;

			break;
		}

		case eServer:
		{
			char	szAxisCpp_Deploy[256];
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Server Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default, &sFileNameList, (char **) psDefaultParamList);

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
		WriteAxisConfigFile( &sDLLNames, iConfigInfoArray, sChoiceList);
	}

	Destroy( &sDLLNames, &sFileNameList, (char *) psDefaultParamList);

	return (int) bSuccess;
}

ECONFIG	ReadConfigOptions( int iParamCount, char * pParamArray[], char ** ppsDefaultParamList)
{
	ECONFIG		eConfig = eEmpty;
	OPTIONLIST	sOptions[] = {{eHTTPTransport, "TH"},
							  {eHTTPChannel, "C"},
							  {eHTTPSSLChannel, "CS"},
							  {eXMLParser, "X"},
							  {eSMTPTransport, "TS"},
							  {eClientLog, "CL"},
							  {eClientWSDD, "CW"},
							  {eServerLog, "SL"},
							  {eRootDirectory, "A"},
							  {eOffsetToLibs, "O"},
							  {eServerWSDD, "SW"}};

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
			} while( iIndex < eConfigMax && !bOptionFound);

			if( bOptionFound)
			{
				if( ppsDefaultParamList[sOptions[iIndex].eConfType] != NULL)
				{
					free( (void *) ppsDefaultParamList[sOptions[iIndex].eConfType]);
				}

				iCount++;

				if( iCount < iParamCount)
				{
					ppsDefaultParamList[sOptions[iIndex].eConfType] = (char *) malloc( strlen( pParamArray[iCount]) + 1);

					strcpy( ppsDefaultParamList[sOptions[iIndex].eConfType], pParamArray[iCount]);
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
bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList)
{
	bool	bFound = false;

	if( strlen( pszAxis_Bin) < 2)
	{
		strcpy( pszAxis_Bin, pszAxis_Bin_Default);
	}

	char	szFilename[512];
	char	szFileDirAndName[512];

	sprintf( szFilename, "%s\\%s\\*.*", pszAxisCpp_Deploy, pszAxis_Bin);

	bFound = ReadFilenamesInaDirectory( szFilename, psFileNameList);

	int		iIndex = 0;

	do
	{
		char *	pExtn = psFileNameList->ppszListArray[iIndex];

		do
		{
			if( (pExtn = strchr( pExtn, '.')) != NULL)
			{
				pExtn++;

#if WIN32
				if( StringCompare( pExtn, "DLL"))
#else
				if( StringCompare( pExtn, "SO"))
#endif
				{
					CreateNewDLLNamesElement( psDLLNames, psFileNameList);

					psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName = (char *) malloc( strlen( psFileNameList->ppszListArray[iIndex]) + 1);

					strcpy( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName, psFileNameList->ppszListArray[iIndex]);

					StringToUpper( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName);

					sprintf( szFileDirAndName, "%s\\%s\\%s", pszAxisCpp_Deploy, pszAxis_Bin, psFileNameList->ppszListArray[iIndex]);

					psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLFilename = (char *) malloc( strlen( szFileDirAndName) + 1);

					strcpy( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLFilename, szFileDirAndName);

					psDLLNames->iIndex++;

					break;
				}
			}
		} while( pExtn != NULL);

		iIndex++;
	} while( iIndex < psFileNameList->iListCount);

	if( !bFound)
	{
		cout << "The directory " << pszAxis_Bin << " was not found." << endl;
	}

	return bFound;
}

const char * CreateConfigElement( DLLNAMES * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType)
{
	int					iIndex = 0;
	bool				bFound = false;
	char *				pszConfigName = "<unknown name>";
	static std::string	sReturn;

	while( iIndex < eConfigMax && !bFound)
	{
		if( psChoiceList[iIndex].eConfigType == eConfigType)
		{
			bFound = true;

			pszConfigName = psChoiceList[iIndex].pszConfigName;
		}
		else
		{
			iIndex++;
		}
	}

	if( bFound)
	{
		sReturn = "#Path to ";
		sReturn += psChoiceList[iIndex].pszElementDescription;
		sReturn += "\n";
	}
	else
	{
		sReturn = "#Path to an unknown element\n";
	}

	char	szReturn[256];

	if( piConfigInfoArray[eConfigType] != -1)
	{
		sprintf( szReturn, "%s:%s\n", pszConfigName, psDLLNames->ppsDLLName[piConfigInfoArray[eConfigType]]->pszDLLFilename);
	}
	else
	{
		sprintf( szReturn, "#%s:<not set>\n", pszConfigName);
	}

	sReturn += szReturn;

	return sReturn.c_str();
}

void GetHomeAndLibrary( DLLNAMES * psDLLNames, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, FILENAMELIST * psFileNameList, char ** ppsDefaultParamList)
{
	if( ppsDefaultParamList[eRootDirectory] == NULL)
	{
#if WIN32
		cout << "Type in full qualified directory path into which you downloaded Axis." << endl
			<< "(e.g. C:\\Axis).  Where C:\\Axis\\axis-c-1.6-Win32-trace-bin is the" << endl
			<< "directory created when Axis was unzipped (this directory must also" << endl
			<< "contain the axiscpp.conf file)." << endl;
#else
		cout << "Type in full qualified directory path into which you downloaded Axis." << endl
			<< "(e.g. /home/Axis).  Where /home/Axis/axis-c-1.6-Linux-trace-bin is the" << endl
			<< "directory created when Axis was untared (this directory must also" << endl
			<< "contain the etc/axiscpp.conf file)." << endl;
#endif
		cout << "AXISCPP_DEPLOY = ";
		cin >> pszAxisCpp_Deploy;
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

#if WIN32
	strcpy( pszAxis_Bin_Default, "\\axis-c-1.6-Win32-trace-bin\\bin");
#else
	strcpy( pszAxis_Bin_Default, "/axis-c-1.6-Linux-trace-bin/bin");
#endif

	if( ppsDefaultParamList[eOffsetToLibs] == NULL)
	{
		cout << endl << "Instruction:" << endl
			<< "You will need to create an environment variable called " << endl
			<< "\"AXISCPP_DEPLOY\" and set it to " << pszAxisCpp_Deploy << "." << endl
			<< "On the command line this would be:-" << endl
#if WIN32
			 << "SET AXISCPP_DEPLOY=" << pszAxisCpp_Deploy << endl << endl;
#else
			 << "EXPORT AXISCPP_DEPLOY=" << pszAxisCpp_Deploy << endl << endl;
#endif

		strcpy( pszAxis_Bin_Default, pszAxisCpp_Deploy);

		do
		{
#if WIN32
			cout << "Type in the directory where the Axis libraries (e.g. axis_client.dll) can be" << endl
					<< "found.  (The default directory is " << pszAxisCpp_Deploy << "\\axis-c-1.6-Win32-trace-bin\\bin)." << endl;
#else
			cout << "Type in the directory where the Axis libraries (e.g. axis_client.so) can be" << endl
					<< "found.  (The default directory is " << pszAxisCpp_Deploy << "/axis-c-1.6-Linux-trace-bin/bin)." << endl;
#endif
			cout << "Axis binaries directory = ";
			cin >> pszAxis_Bin;
		}
		while( !CheckAxisBinDirectoryExists( pszAxisCpp_Deploy, pszAxis_Bin, pszAxis_Bin_Default, psDLLNames, psFileNameList));
	}

	cout << endl << "Begin to configure the AXISCPP.CONF file." << endl;
}

void Initialise( DLLNAMES * psDLLNames, int * piConfigInfoArray, FILENAMELIST * psFileNameList, char ** ppsDefaultParamList)
{
	memset( psDLLNames, 0, sizeof( DLLNAMES));
	memset( psFileNameList, 0, sizeof( FILENAMELIST));

	for( int iCount = 0; iCount < eConfigMax; iCount++)
	{
		piConfigInfoArray[iCount] = -1;
		ppsDefaultParamList[iCount] = NULL;
	}
}

void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, DLLNAMES * psDLLNames, int * piConfigInfoArray, char ** ppsDefaultParamList)
{
	cout << endl << "Select the filename for the " << psChoiceList[iChoiceCount].pszElementDescription << "." << endl;

	int		iDLLCount = 0;
	int		iDLLListCount = 0;
	int		iDLLOffsetList[8];
	bool	bHTTPTransportFound = false;

	do
	{
		while( iDLLCount < psDLLNames->iIndex)
		{
			char *	pszUpper = new char[strlen( psChoiceList[iChoiceCount].pszElement) + 1];

			strcpy( pszUpper, psChoiceList[iChoiceCount].pszElement);

			StringToUpper( pszUpper);

			if( strstr( psDLLNames->ppsDLLName[iDLLCount]->pszDLLName, pszUpper) != NULL)
			{
				iDLLOffsetList[iDLLListCount] = iDLLCount;

				cout << ++iDLLListCount << ".\t" << psDLLNames->ppsDLLName[iDLLCount]->pszDLLFilename << endl;
			}

			iDLLCount++;

			free( pszUpper);
		}

		if( ppsDefaultParamList[iChoiceCount] != NULL)
		{
			if( iDLLListCount > 0)
			{
			}
			else
			{
//				psDLLNames->ppsDLLName[iDLLOffsetList[iChoice - 1]]->bAddToClientConfig = true;
//				piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = iDLLOffsetList[iChoice - 1];
			}
		}

		if( iDLLListCount > 0)
		{
			if( iDLLListCount > 1)
			{
				cout << "Select an index between 1 and " << iDLLListCount << " : ";

				int	iChoice;

				cin >> iChoice;

				if( iChoice < 1 || iChoice > iDLLListCount)
				{
					cout << "Number was out of range." << endl;
				}
				else
				{
					psDLLNames->ppsDLLName[iDLLOffsetList[iChoice - 1]]->bAddToClientConfig = true;
					piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = iDLLOffsetList[iChoice - 1];
					bHTTPTransportFound = true;
				}
			}
			else
			{
				cout << "Automatically selected " << psDLLNames->ppsDLLName[iDLLOffsetList[0]]->pszDLLFilename << endl;

				psDLLNames->ppsDLLName[iDLLOffsetList[0]]->bAddToClientConfig = true;
				piConfigInfoArray[psChoiceList[iChoiceCount].eConfigType] = iDLLOffsetList[0];
				bHTTPTransportFound = true;
			}
		}
		else
		{
			cout << "There are no recognised file names for the type of DLL." << endl << "You will have to modify the configuration file namually." << endl << endl;

			bHTTPTransportFound = true;
		}
	} while( !bHTTPTransportFound);
}

void WriteAxisConfigFile( DLLNAMES * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList)
{
	cout << "DLL selection complete" << endl << endl;

	cout << "AxisCPP.conf file now has the following information:-" << endl;

	cout << "# The comment character is '#'" << endl;
	cout << "#Available directives are as follows" << endl;
	cout << "#(Some of these directives may not be implemented yet)" << endl;
	cout << "#" << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eServerLog) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eServerWSDD) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eClientLog) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eClientWSDD) << endl;
	cout << "#Node name." << endl;
	cout << "#NodeName: <not set>" << endl << endl;
	cout << "#Listening port." << endl;
	cout << "#ListenPort: <not set>" << endl << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPTransport) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eSMTPTransport) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eXMLParser) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPChannel) << endl;
	cout << CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPSSLChannel) << endl;
	cout << endl;
}

bool ReadFilenamesInaDirectory( char * pszDirName, FILENAMELIST * psFileNameList)
{
	bool				bSuccess = false;

#if WIN32
	intptr_t			lFindFile;
	struct _finddata_t	sFindData;

	if( (lFindFile = _findfirst( pszDirName, &sFindData)) != -1)
	{
		if( sFindData.name[0] == '.' && sFindData.attrib & _A_SUBDIR)
		{
			bSuccess = true;
		}

		do
		{
			if( !(sFindData.attrib & _A_SUBDIR))
			{
				AddFilenameToList( psFileNameList, sFindData.name);
			}
		} while( _findnext( lFindFile, &sFindData) == 0);

		_findclose( lFindFile);
	}
#else
	DIR *				psDIR;
	struct dirent*		pDirEnt;
	int					iFilenameCount = 0;

	if( (psDIR = opendir( pszDirName)) == NULL)
	{
		return bSuccess;
	}

	while( (pDirEnt = readdir( psDIR)) != NULL)
	{
		AddFilenameToList( psFileNameList, pDirEnt->d_name);
	}

	if( closedir( psDIR) == -1)
	{
		return bSuccess;
	}
	else
	{
		bSuccess = true;
	}
#endif

	return bSuccess;
}

void AddFilenameToList( FILENAMELIST * psFileNameList, char * pszFilename)
{
	if( psFileNameList->iListMax == 0)
	{
		psFileNameList->iListMax = 1;

		psFileNameList->ppszListArray = (char **) malloc( sizeof( char *));
	}
	else if( psFileNameList->iListCount >= psFileNameList->iListMax)
	{
		psFileNameList->iListMax *= 2;

		psFileNameList->ppszListArray = (char **) realloc( psFileNameList->ppszListArray, sizeof( char *) * psFileNameList->iListMax);
	}

	psFileNameList->ppszListArray[psFileNameList->iListCount] = (char *) malloc( strlen( pszFilename) + 1);

	strcpy( psFileNameList->ppszListArray[psFileNameList->iListCount], pszFilename);

	psFileNameList->iListCount++;
}

void Destroy( DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList, char * psDefaultParamList)
{
	int iCount;

	for( iCount = 0; iCount < psDLLNames->iIndex; iCount++)
	{
		free( psDLLNames->ppsDLLName[iCount]->pszDLLFilename);
		free( psDLLNames->ppsDLLName[iCount]->pszDLLName);
		free( psDLLNames->ppsDLLName[iCount]);
	}

	for( iCount = 0; iCount < psFileNameList->iListCount; iCount++)
	{
		free( psFileNameList->ppszListArray[iCount]);
	}

	free( psDLLNames->ppsDLLName);
	free( psFileNameList->ppszListArray);

	for( iCount = 0; iCount < eConfigMax; iCount++)
	{
		if( psDefaultParamList[iCount] != NULL)
		{
			free( (void *) psDefaultParamList[iCount]);
		}
	}
}

bool StringCompare( char * pszString1, char * pszString2)
{
	bool	bSame = false;

	if( pszString1 == NULL || pszString2 == NULL)
	{
		return bSame;
	}

	if( strlen( pszString1) != strlen( pszString2))
	{
		return bSame;
	}

	if( strlen( pszString1) == 0)
	{
		bSame = true;
	}
	else
	{
		char *	psString1 = pszString1;
		char *	psString2 = pszString2;

		do
		{
			bSame = (toupper( *psString1++) == toupper( *psString2++));
		} while( bSame && *psString1 != '\0');
	}

	return bSame;
}

void StringToUpper( char * pszString)
{
	if( pszString != NULL)
	{
		char *	pc = pszString;

		while( *pc != '\0')
		{
			*pc = toupper( *pc);

			pc++;
		}
	}
}

void CreateNewDLLNamesElement( DLLNAMES * psDLLNames, FILENAMELIST * psFileNameList)
{
	if( psDLLNames->iIndex >= psDLLNames->iMaxCount)
	{
		psDLLNames->iMaxCount = psDLLNames->iMaxCount * 2 + 1;

		if( psDLLNames->ppsDLLName == NULL)
		{
			psDLLNames->ppsDLLName = (DLLNAMEINFO **) malloc( sizeof( void *) * psDLLNames->iMaxCount);
		}
		else
		{
			psDLLNames->ppsDLLName = (DLLNAMEINFO **) realloc( psDLLNames->ppsDLLName, sizeof( void *) * psDLLNames->iMaxCount);
		}

		for( int iNewIndex = psDLLNames->iIndex; iNewIndex < psDLLNames->iMaxCount; iNewIndex++)
		{
			psDLLNames->ppsDLLName[iNewIndex] = NULL;
		}
	}

	psDLLNames->ppsDLLName[psDLLNames->iIndex] = (DLLNAMEINFO *) malloc( sizeof( DLLNAMEINFO));

	memset( psDLLNames->ppsDLLName[psDLLNames->iIndex], 0, sizeof( DLLNAMEINFO));
}