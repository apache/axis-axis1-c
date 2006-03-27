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

#if WIN32
	sprintf( szFilename, "%s\\%s\\*.*", pszAxisCpp_Deploy, pszAxis_Bin);
#else
	sprintf( szFilename, "%s/%s/.", pszAxisCpp_Deploy, pszAxis_Bin);
#endif

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

#if WIN32
						sprintf( szFileDirAndName, "%s\\%s\\%s", pszAxisCpp_Deploy, pszAxis_Bin, (char *) psFileNameList->ppArray[iIndex]);
#else
						sprintf( szFileDirAndName, "%s/%s/%s", pszAxisCpp_Deploy, pszAxis_Bin, (char *) psFileNameList->ppArray[iIndex]);
#endif
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

void WriteAxisConfigFile( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, bool bMerge, char * pszAxisCpp_Deploy, char cSlash, bool bBackup)
{
	char	szFilename[256];

	sprintf( szFilename, "%s%caxiscpp.conf", pszAxisCpp_Deploy, cSlash);

	cout << endl << "Configuration complete." << endl << endl;

	if( bBackup)
	{
		BackUpExistingConfigFile( pszAxisCpp_Deploy, szFilename, cSlash);
	}

	if( bMerge)
	{
		char *	pszData = NULL;
		long	lFileLength = 0;
		
		if( (lFileLength = ReadFileContents( szFilename, &pszData)) > -1)
		{
			FILE *	pFile = fopen( szFilename, "w");

			if( lFileLength < 5)
			{
				char	szConfigData[512];

				sprintf( szConfigData, "# This header file was created by AxisConfiguration on %s", TimeNow());

				WriteLineToFile( pFile, szConfigData);

				WriteLineToFile( pFile, "# The comment character is '#'\n");
				WriteLineToFile( pFile, "# Available directives are as follows\n");
				WriteLineToFile( pFile, "#(Some of these directives may not be implemented yet)\n");
				WriteLineToFile( pFile, "#\n");
			}

			for( int ieConfigType = eHTTPTransport; ieConfigType < eConfigMax; ieConfigType++)
			{
				int	iChoiceIndex = GetChoiceIndexForConfigType( psChoiceList, (ECONFIGTYPE) ieConfigType);

				if( iChoiceIndex != -1)
				{
					char *	psTag = strstr( pszData, psChoiceList[iChoiceIndex].pszConfigName);

					if( psTag)
					{
						char *	psTagLineStart = strchr( psTag, ':');
						char *	psTagLineEnd = psTag;

						if( psTagLineStart != NULL)
						{
							psTagLineStart++;

							while( *psTagLineEnd != '\n' &&
								   *psTagLineEnd != '\r' &&
								   *psTagLineEnd != '\0' &&
								   psTagLineEnd - pszData < lFileLength)
							{
								psTagLineEnd++;
							}

							int		iTagValueLength = (int) (psTagLineEnd - psTagLineStart);
							char *	pszTagValue = GetTagValue( psDLLNames, piConfigInfoArray, (ECONFIGTYPE) ieConfigType);

							if( pszTagValue != NULL)
							{
								if( (int) strlen( pszTagValue) == iTagValueLength)
								{
									if( StringCompare( psTagLineStart, pszTagValue))
									{
										// No change
									}
									else
									{
										memcpy( psTagLineStart, pszTagValue, iTagValueLength);
									}
								}
								else if( (int) strlen( pszTagValue) > iTagValueLength)
								{
									// New tag value is longer than current tag.
									int	iTagValueLengthDiff = (int) strlen( pszTagValue) - iTagValueLength;
									int	iTagValueOffset = (int) (psTagLineStart - pszData);

									pszData = (char *) realloc( pszData, strlen( pszData) + iTagValueLengthDiff + 1);

									memmove( pszData + iTagValueOffset + iTagValueLength + iTagValueLengthDiff,
										     pszData + iTagValueOffset + iTagValueLength,
											 strlen( pszData + iTagValueOffset + iTagValueLength) + 1);
									memcpy( pszData + iTagValueOffset,
											pszTagValue,
											strlen( pszTagValue));
								}
								else
								{
									// New tag value is shorter than current tag.
									int	iTagValueLengthDiff = iTagValueLength - (int) strlen( pszTagValue);
									int	iTagValueOffset = (int) (psTagLineStart - pszData);

									memmove( pszData + iTagValueOffset + iTagValueLength - iTagValueLengthDiff,
											 pszData + iTagValueOffset + iTagValueLength,
											 strlen( pszData + iTagValueOffset + iTagValueLength) + 1);
									memcpy( pszData + iTagValueOffset,
											pszTagValue,
											strlen( pszTagValue));
								}
							}
						}
					}
					else
					{
						WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, (ECONFIGTYPE) ieConfigType));
					}
				}
				else
				{
					// No choice information
				}
			}
		
		WriteLineToFile( pFile, pszData);

		free( pszData);

		fclose( pFile);
		}
		else
		{
			cout << "Error - The existing configuration file (" << szFilename << ")" << endl
				<< "        could not be read/found.  The new configuration data has" << endl
				<< "        not been written." << endl;
		}
	}
	else
	{
		FILE *		pFile = fopen( szFilename, "w");
		char		szConfigData[512];

		sprintf( szConfigData, "# This header file was created by AxisConfiguration on %s", TimeNow());

		WriteLineToFile( pFile, szConfigData);

		WriteLineToFile( pFile, "# The comment character is '#'\n");
		WriteLineToFile( pFile, "# Available directives are as follows\n");
		WriteLineToFile( pFile, "#(Some of these directives may not be implemented yet)\n");
		WriteLineToFile( pFile, "#\n");
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eServerLog));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eServerWSDD));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eClientLog));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eClientWSDD));
		WriteLineToFile( pFile, "#Node name.\n");
		WriteLineToFile( pFile, "#NodeName: <not set>\n\n");
		WriteLineToFile( pFile, "#Listening port.\n");
		WriteLineToFile( pFile, "#ListenPort: <not set>\n\n");
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPTransport));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eSMTPTransport));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eXMLParser));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPChannel));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eHTTPSSLChannel));
		WriteLineToFile( pFile, CreateConfigElement( psDLLNames, piConfigInfoArray, psChoiceList, eSSLOptions));

		fclose( pFile);
	}
}
bool BackUpExistingConfigFile( char * pszAxisCpp_Deploy, char * pszFilename, char cSlash)
{
	bool	bSuccess = false;

	if( FileExists( pszFilename))
	{
		int		iBackCount = -1;
		char	szBackFilename[256];

		do
		{
			iBackCount++;

			sprintf( szBackFilename, "%s%caxiscpp.conf.backup_%04d", pszAxisCpp_Deploy, cSlash, iBackCount);

		} while( FileExists( szBackFilename));

		FILE *	pFileFrom = fopen( pszFilename, "r");
		FILE *	pFileTo = fopen( szBackFilename, "w");

		if( pFileFrom != NULL && pFileTo != NULL)
		{
			long		lFileLength = GetFileLength( pFileFrom);
			char		szBackupHeader[256];

			sprintf( szBackupHeader, "# This header file was automatically backed up by AxisConfiguration on %s", TimeNow());

			char *	pFileContent = (char *) malloc( lFileLength + strlen( szBackupHeader) + 2);

			pFileContent[lFileLength + strlen( szBackupHeader) + 1] = '\0';

			strcpy( pFileContent, szBackupHeader);

			fread( pFileContent + strlen( szBackupHeader), sizeof( char), lFileLength, pFileFrom);
			fwrite( pFileContent, sizeof( char), lFileLength + strlen(szBackupHeader) + 1, pFileTo);

			fclose( pFileFrom);
			fclose( pFileTo);

			pFileTo = NULL;
			pFileFrom = NULL;

			free( pFileContent);

			bSuccess = true;
		}

		if( pFileTo != NULL)
		{
			fclose( pFileTo);
		}

		if( pFileFrom != NULL)
		{
			fclose( pFileFrom);
		}
	}

	return bSuccess;
}

void WriteLineToFile( FILE * pFile, char * pszData)
{
	fwrite( pszData, sizeof( char), strlen( pszData), pFile);
}

long GetFileLength( FILE * pFile)
{
	fseek( pFile, 0, SEEK_END);

	long	lFileLength = ftell( pFile);

	rewind( pFile);

	return lFileLength;
}

long ReadFileContents( char * pszFilename, char ** ppszData)
{
	long	lFileLength = -1;

	if( FileExists( pszFilename))
	{
		FILE *	pFile = fopen( pszFilename, "r");

		if( pFile != NULL)
		{
			lFileLength = GetFileLength( pFile);
			
			*ppszData = (char *) malloc( lFileLength + 1);

			memset( *ppszData, 0, lFileLength + 1);

			fread( *ppszData, sizeof( char), lFileLength, pFile);

			fclose( pFile);
		}
	}

	return lFileLength;
}
