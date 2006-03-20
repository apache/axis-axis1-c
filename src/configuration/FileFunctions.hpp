#if WIN32
#include <io.h>
#else
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#include "AxisConfiguration.hpp"

bool ReadFilenamesInaDirectory( char * pszDirName, LIST * psFileNameList);
void WriteAxisConfigFile( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList);
