#include "FileFunctions.hpp"
#include "MissingCFunctions.hpp"
#include "AxisConfigurationLibraries.hpp"

bool ReadFilenamesInaDirectory( char * pszDirName, LIST * psFileNameList)
{
	bool				bSuccess = false;

#if WIN32									// Start WINDOWS code
#if defined(_MSC_VER) && _MSC_VER >= 1300	// Start MSVC verison number > 7.0
	intptr_t			lFindFile;
#else										// Else !(MSVC verison number > 7.0)
	long				lFindFile;
#endif										// End MSVC verison number
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
#else									// Else !(WINDOWS code)
	DIR *				psDIR;
	struct dirent*		pDirEnt;
	int					iFilenameCount = 0;

	cout << "pszDirName=" << pszDirName << endl;

	if( (psDIR = opendir( pszDirName)) == NULL)
	{
		return bSuccess;
	}

	cout << "2" << endl;

	while( (pDirEnt = readdir( psDIR)) != NULL)
	{
		cout << "pDirEnt->d_name=" << pDirEnt->d_name << endl;

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
#endif									// End WINDOWS code

	return bSuccess;
}

bool CheckAxisBinDirectoryExists( char * pszAxisCpp_Deploy, char * pszAxis_Bin, char * pszAxis_Bin_Default, LIST * psDLLNames, LIST * psFileNameList)
{
	bool	bFound = false;

	if( strlen( pszAxis_Bin) < 2)
	{
		strcpy( pszAxis_Bin, pszAxis_Bin_Default);
	}

	char	szFilename[512];
	char	szFileDirAndName[512];

	sprintf( szFilename, "%s\\%s\\*.*", pszAxisCpp_Deploy, pszAxis_Bin);

	if( (bFound = ReadFilenamesInaDirectory( szFilename, psFileNameList)) == true)
	{
		int		iIndex = 0;

		do
		{
			char *	pExtn = (char *) psFileNameList->ppArray[iIndex];

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
						DLLNAMEINFO * psDLLNameInfo = (DLLNAMEINFO *) GetNextListElement( psDLLNames, sizeof( DLLNAMEINFO));

						psDLLNameInfo->pszDLLName = (char *) malloc( strlen( (char *) psFileNameList->ppArray[iIndex]) + 1);

						strcpy( psDLLNameInfo->pszDLLName, (char *) psFileNameList->ppArray[iIndex]);

						StringToUpper( psDLLNameInfo->pszDLLName);

						sprintf( szFileDirAndName, "%s\\%s\\%s", pszAxisCpp_Deploy, pszAxis_Bin, (char *) psFileNameList->ppArray[iIndex]);

						psDLLNameInfo->pszDLLFilename = (char *) malloc( strlen( szFileDirAndName) + 1);

						strcpy( psDLLNameInfo->pszDLLFilename, szFileDirAndName);

						break;
					}
				}
			} while( pExtn != NULL);

			iIndex++;
		} while( iIndex < psFileNameList->iCount);
	}

	if( !bFound)
	{
		cout << endl << "The directory " << pszAxis_Bin << " was not found." << endl << endl;
	}

	return bFound;
}

void WriteAxisConfigFile( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList)
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
