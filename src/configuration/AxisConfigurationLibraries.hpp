#include "AxisConfiguration.hpp"

char * CreateConfigElement( LIST * psDLLNames, int * piConfigInfoArray, CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType);
void Initialise( LIST * psDLLNames, int * piConfigInfoArray, LIST * psFileNameList, char ** ppsDefaultParamList, char * pszAxisCpp_Deploy, int iAxisCpp_Deploy);
void Destroy( LIST * psDLLNames, LIST * psFileNameList, char ** psDefaultParamList);
int PopulateNewDLLNameInfo( LIST * psDLLNames, char * pszName, char * pszFilename, bool bAddToClientConfig);
char * GetTagValue( LIST * psDLLNames, int * piConfigInfoArray, ECONFIGTYPE eConfigType);
int GetChoiceIndexForConfigType( CHOICELIST * psChoiceList, ECONFIGTYPE eConfigType);
