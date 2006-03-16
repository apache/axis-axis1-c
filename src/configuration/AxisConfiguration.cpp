#include "AxisConfiguration.hpp"

void main( int argc, char * argv[])
{
	DLLNAMES	sDLLNames;
	int			iConfigInfoArray[eConfigMax];
	CHOICELIST	sChoiceList[] = { {PLATFORM_TRANSPORTHTTP_PATH,	"HTTP Transport library",											AXCONF_TRANSPORTHTTP_TAGNAME,		eHTTPTransport,		eClientAndServer},
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
								  {"",							"",																	AXCONF_SECUREINFO_TAGNAME,			eUnknown,			eClientAndServer}};

	Initialise( &sDLLNames, iConfigInfoArray);

	switch( ReadConfigOptions( argc, argv))
	{
		case eEmpty:
		{
			cout << "Usage:" << endl;
			cout << "Client\tConfigure the client side." << endl;
			cout << "Server\tConfigure the server side." << endl;
			cout << "Both\tConfigure the client and server side." << endl;
			break;
		}

		case eClient:
		{
			char	szAxisCpp_Deploy[256];
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Client Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default);

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

						cin >> sDLLNames.ppsDLLName[iChoiceCount]->pszDLLName;

						sprintf( sDLLNames.ppsDLLName[iChoiceCount]->pszDLLFilename, "%s\\%s", szAxisCpp_Deploy, sDLLNames.ppsDLLName[iChoiceCount]->pszDLLName);

						iConfigInfoArray[sChoiceList[iChoiceCount].eConfigType] = iChoiceCount;

						sDLLNames.ppsDLLName[iChoiceCount]->bAddToClientConfig = true;
					}
					else
					{
						SelectFileFromList( sChoiceList, iChoiceCount, &sDLLNames, iConfigInfoArray);
					}
				}

				iChoiceCount++;
			}

			break;
		}

		case eServer:
		{
			char	szAxisCpp_Deploy[256];
			char	szAxis_Bin[256];
			char	szAxis_Bin_Default[256];

			cout << "Axis Server Configuration" << endl;
			cout << "=========================" << endl;

			GetHomeAndLibrary( &sDLLNames, szAxisCpp_Deploy, szAxis_Bin, szAxis_Bin_Default);

			break;
		}

		case eClientAndServer:
		{
			cout << "Axis Client and Server Configuration" << endl;
			break;
		}
	}

	cout << "DLL selection complete" << endl << endl;

	cout << "AxisCPP.conf file now has the following information:-" << endl;

	cout << "# The comment character is '#'" << endl;
	cout << "#Available directives are as follows" << endl;
	cout << "#(Some of these directives may not be implemented yet)" << endl;
	cout << "#" << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eServerLog) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eServerWSDD) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eClientLog) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eClientWSDD) << endl;
	cout << "#Node name." << endl;
	cout << "#NodeName: <not set>" << endl << endl;
	cout << "#Listening port." << endl;
	cout << "#ListenPort: <not set>" << endl << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eHTTPTransport) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eSMTPTransport) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eXMLParser) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eHTTPChannel) << endl;
	cout << CreateConfigElement( &sDLLNames, (int *) iConfigInfoArray, sChoiceList, eHTTPSSLChannel) << endl;
	cout << endl;
}

ECONFIG	ReadConfigOptions( int iParamCount, char * pParamArray[])
{
	ECONFIG	eConfig = eEmpty;

	for( int iCount = 0; iCount < iParamCount; iCount++)
	{
		if( !stricmp( pParamArray[iCount], "Client"))
		{
			eConfig = (ECONFIG)((int) eConfig | eClient);
		}
		else if( !stricmp( pParamArray[iCount], "Server"))
		{
			eConfig = (ECONFIG)((int) eConfig | eServer);
		}
		else if( !stricmp( pParamArray[iCount], "Both"))
		{
			eConfig = (ECONFIG)((int) eConfig | eClientAndServer);
		}
	}

	return eConfig;
}
bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, DLLNAMES * psDLLNames)
{
	bool	bFound = false;

	if( strlen( pszAxis_Bin) < 2)
	{
		strcpy( pszAxis_Bin, pszAxis_Bin_Default);
	}

	intptr_t			lFindFile;
	struct _finddata_t	sFindData;
	char				szFilename[512];
	char				szFileDirAndName[512];

	sprintf( szFilename, "%s\\%s\\*.*", pszAxisCpp_Deploy, pszAxis_Bin);

	if( (lFindFile = _findfirst( szFilename, &sFindData)) != -1)
	{
		if( sFindData.name[0] == '.' && sFindData.attrib & _A_SUBDIR)
		{
			bFound = true;
		}

		do
		{
			if( !(sFindData.attrib & _A_SUBDIR))
			{
				char *	pExtn = sFindData.name;

				do
				{
					if( (pExtn = strchr( pExtn, '.')) != NULL)
					{
						pExtn++;

						if( !stricmp( pExtn, "DLL"))
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

							psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName = (char *) malloc( strlen( sFindData.name) + 1);

							strcpy( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName, sFindData.name);

							strupr( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLName);

							sprintf( szFileDirAndName, "%s\\%s\\%s", pszAxisCpp_Deploy, pszAxis_Bin, sFindData.name);

							psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLFilename = (char *) malloc( strlen( szFileDirAndName) + 1);

							strcpy( psDLLNames->ppsDLLName[psDLLNames->iIndex]->pszDLLFilename, szFileDirAndName);

							psDLLNames->iIndex++;

							break;
						}
					}
				} while( pExtn != NULL);
			}
			else if( strcmp( sFindData.name, ".") && strcmp( sFindData.name, ".."))
			{
				break;
			}

		} while( _findnext( lFindFile, &sFindData) == 0);

		_findclose( lFindFile);
	}

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

void GetHomeAndLibrary( DLLNAMES * psDLLNames, char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default)
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

#if WIN32
	strcat( pszAxis_Bin_Default, "\\axis-c-1.6-Win32-trace-bin\\bin");
#else
	strcat( pszAxis_Bin_Default, "/axis-c-1.6-Linux-trace-bin/bin");
#endif

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
	while( !CheckAxisBinDirectoryExists( pszAxisCpp_Deploy, pszAxis_Bin, pszAxis_Bin_Default, psDLLNames));

	cout << endl << "Begin to configure the AXISCPP.CONF file." << endl;
}

void Initialise( DLLNAMES * psDLLNames, int * piConfigInfoArray)
{
	memset( psDLLNames, 0, sizeof( DLLNAMES));
	
	for( int iCount = 0; iCount < eConfigMax; iCount++)
	{
		piConfigInfoArray[iCount] = -1;
	}
}

void SelectFileFromList( CHOICELIST * psChoiceList, int iChoiceCount, DLLNAMES * psDLLNames, int * piConfigInfoArray)
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
			strupr( pszUpper);

			if( strstr( psDLLNames->ppsDLLName[iDLLCount]->pszDLLName, pszUpper) != NULL)
			{
				iDLLOffsetList[iDLLListCount] = iDLLCount;

				cout << ++iDLLListCount << ".\t" << psDLLNames->ppsDLLName[iDLLCount]->pszDLLFilename << endl;
			}

			iDLLCount++;

			delete [] pszUpper;
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