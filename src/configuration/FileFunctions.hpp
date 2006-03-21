#if WIN32
#include <io.h>
#else
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#include "AxisConfiguration.hpp"
#include <time.h>

bool ReadFilenamesInaDirectory( char * pszDirName, LIST * psFileNameList);
void WriteAxisConfigFile( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, bool bMerge, char * pszAxisCpp_Deploy, char cSlash);
bool BackUpExistingConfigFile( char * pszAxisCpp_Deploy, char * pszFilename, char cSlash);
void WriteLineToFile( FILE * pFile, char * pszData);
long GetFileLength( FILE * pFile);
long ReadFileContents( char * pszFilename, char ** ppszData);

