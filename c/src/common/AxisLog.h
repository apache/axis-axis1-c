#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <fstream>
using namespace std;
class AxisLog
{
public:
	AxisLog();
	virtual ~AxisLog();
  string sFileName;
  const char * FileName;
  ofstream* fout;
  
  int writeLog(const string &sLog);
  int writeLog(const string &sLog1, const string &sLog2);

};

static AxisLog objAxisLog;
#endif
