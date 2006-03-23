#include "AxisConfigurationLibraries.hpp"

char * CreateConfigElement( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType)
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
		if( eConfigType == eSSLOptions)
		{
			sReturn = "# ";
			sReturn += psChoiceList[iIndex].pszElementDescription;
			sReturn += "\n";
		}
		else
		{
			sReturn = "# Path to ";
			sReturn += psChoiceList[iIndex].pszElementDescription;
			sReturn += "\n";
		}
	}
	else
	{
		sReturn = "# Path to an unknown element\n";
	}

	char	szReturn[256];

	if( piConfigInfoArray[eConfigType] != -1)
	{
		sprintf( szReturn, "%s:%s\n\n", pszConfigName, ((DLLNAMEINFO *)(psDLLNames->ppArray[piConfigInfoArray[eConfigType]]))->pszDLLFilename);
	}
	else
	{
		sprintf( szReturn, "#%s:<not set>\n\n", pszConfigName);
	}

	sReturn += szReturn;

	return (char *) sReturn.c_str();
}

char * GetTagValue( LIST * psDLLNames, int * piConfigInfoArray, ECONFIGTYPE eConfigType)
{
	char *	pszTagValue = NULL;

	if( piConfigInfoArray[eConfigType] != -1)
	{
		pszTagValue = ((DLLNAMEINFO *)(psDLLNames->ppArray[piConfigInfoArray[eConfigType]]))->pszDLLFilename;
	}

	return pszTagValue;
}

void Initialise( LIST * psDLLNames, int * piConfigInfoArray, LIST * psFileNameList, char ** ppsDefaultParamList)
{
	memset( psDLLNames, 0, sizeof( LIST));
	memset( psFileNameList, 0, sizeof( LIST));

	for( int iCount = 0; iCount < eConfigMax; iCount++)
	{
		piConfigInfoArray[iCount] = -1;
		ppsDefaultParamList[iCount] = NULL;
	}
}

void Destroy( LIST * psDLLNames, LIST * psFileNameList, char ** ppsDefaultParamList)
{
	int iCount;

	for( iCount = 0; iCount < psDLLNames->iCount; iCount++)
	{
		free( ((DLLNAMEINFO *) psDLLNames->ppArray[iCount])->pszDLLFilename);
		free( ((DLLNAMEINFO *) psDLLNames->ppArray[iCount])->pszDLLName);
		free( psDLLNames->ppArray[iCount]);
	}

	for( iCount = 0; iCount < psFileNameList->iCount; iCount++)
	{
		free( psFileNameList->ppArray[iCount]);
	}

	free( psDLLNames->ppArray);
	free( psFileNameList->ppArray);

	for( iCount = 0; iCount < eConfigMax; iCount++)
	{
		if( ppsDefaultParamList[iCount] != NULL)
		{
			free( (void *) ppsDefaultParamList[iCount]);
		}
	}
}

int PopulateNewDLLNameInfo( LIST * psDLLNames, char * pszName, char * pszFilename, bool bAddToClientConfig)
{
	DLLNAMEINFO *	psDLLNameInfo = (DLLNAMEINFO *) GetNextListElement( psDLLNames, sizeof( DLLNAMEINFO));

	if( pszName != NULL)
	{
		psDLLNameInfo->pszDLLName = (char *) malloc( strlen( pszName) + 1);

		strcpy( psDLLNameInfo->pszDLLName, pszName);
	}

	if( pszFilename != NULL)
	{
		psDLLNameInfo->pszDLLFilename = (char *) malloc( strlen( pszFilename) + 1);

		strcpy( psDLLNameInfo->pszDLLFilename, pszFilename);
	}

	psDLLNameInfo->bAddToClientConfig = bAddToClientConfig;

	return psDLLNames->iCount - 1;
}

int GetChoiceIndexForConfigType( CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType)
{
	int					iIndex = 0;
	bool				bFound = false;

	while( iIndex < eConfigMax && !bFound)
	{
		if( psChoiceList[iIndex].eConfigType == eConfigType)
		{
			bFound = true;
		}
		else
		{
			iIndex++;
		}
	}

	if( !bFound)
	{
		iIndex = -1;
	}

	return iIndex;
}
