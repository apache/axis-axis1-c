                                                                                    //////////////////////////////////////////////////////////////////////
#include "Debug.h"
#include <time.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Debug::Debug()
{
  sFileName = "/usr/local/axiscpp/axis/logs/Debug";
  if(!sFileName.empty())
  {
    FileName = sFileName.c_str();
    fout = new ofstream(FileName,ios::app);  // open for writing
  }
}

Debug::~Debug()
{
  fout->close();
  fout = NULL;
}

int Debug::debug(const string &sLog,string arg2, int arg3)
{
  if(fout)
  {
    time_t ltime;
    time(&ltime);
    //*fout << "time:" << ctime(&ltime) << ":" << sLog.c_str() << endl;
    *fout << "time:" << ctime(&ltime) \
    << " :file:"<< arg2 << " :line:" << arg3 << ":" << endl \    
    << sLog.c_str() << endl \
    << "-------------------------------------------------" << endl;
    sprintf((char*)chEBuf,sLog.c_str());
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

int Debug::debug(const string &sLog1, const string &sLog2,string arg3, int arg4)
{
  if(fout)
  {
    time_t ltime;
    time(&ltime);
    //*fout << "time:" << ctime(&ltime) << ":" << sLog1.c_str() << " " << sLog2.c_str() << endl;
    *fout << "time:" << ctime(&ltime) \
    << " :file:"<< arg3 << " :line:" << arg4 << endl \    
    << sLog1.c_str() << " " << sLog2.c_str() << endl \
    << "-------------------------------------------------" << endl;
    sprintf((char*)chEBuf,sLog1.c_str(), sLog2.c_str());
    return SUCCESS;
  }
  else
  {
    return FAIL;
  }
}

/*
int main(int argc, char* argv[])
{
  debugger.debug("damitha");
  return 0;
}
*/