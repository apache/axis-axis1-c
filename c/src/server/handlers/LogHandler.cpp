//////////////////////////////////////////////////////////////////////

#include "LogHandler.h"
#include "../soap/SoapDeSerializer.h"
#include "../soap/SoapSerializer.h"
#include <fstream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogHandler::LogHandler()
{

}

LogHandler::~LogHandler()
{

}
// Implementation of BasicHandler interface.
int LogHandler::Invoke(MessageData* md)
{
  int iNumAccess = 0;
  WSDDService* oService =  md->GetService();
  if(oService)
  {
    string sFileName = oService->GetOption("logAccessCountFile");
    if(!sFileName.empty())
    {   
      string sNumAccess = oService->GetOption("num_access");      
      if(sNumAccess.empty())
      {
        iNumAccess = 0;
      }
      else
      {
        iNumAccess = atoi(sNumAccess.c_str());
      }
      
      iNumAccess++;
      sNumAccess = iNumAccess;
    
      const char * FileName = sFileName.c_str();
      ofstream fout(FileName);  // open for writing
      fout << "service accessed " << iNumAccess << "times";
  
      oService->SetOption("num_access", sNumAccess);
      return SUCCESS;
    }
    else
    {
      return FAIL;
    }
  }
  else
  {
    return FAIL;
  }
}

void LogHandler::OnFault(MessageData* mc)
{

}


