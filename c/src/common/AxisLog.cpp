                                                                                    //////////////////////////////////////////////////////////////////////
#include "AxisLog.h"
#include <time.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AxisLog::AxisLog()
{
  sFileName = "/usr/local/apache/logs/AxisLog";
  if(!sFileName.empty())
  {
    FileName = sFileName.c_str();
    fout = new ofstream(FileName,ios::app);  // open for writing
  }
}

AxisLog::~AxisLog()
{
  fout->close();
  fout = NULL;
}

int AxisLog::writeLog(const string &sLog)
{
  if(fout)
  {
    time_t ltime;
    time(&ltime);
    *fout << "time:" << ctime(&ltime) << ":" << sLog.c_str() << endl;
    return SUCCESS;
  }
  else
  {
    return FAIL;
  } 
}

int AxisLog::writeLog(const string &sLog1, const string &sLog2)
{
    if(fout)
    {
        time_t ltime;
	time(&ltime);
	*fout << "time:" << ctime(&ltime) << ":" << sLog1.c_str() << " " << sLog2.c_str() << endl;
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
  objAxisLog.writeLog("damitha*****************");
  return 0;
}
*/
