#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <fstream>

#define DEBUG
extern unsigned char chEBuf[1024];
using namespace std;
class Debug
{
public:
	Debug();
	virtual ~Debug();
  string sFileName;
  const char * FileName;
  ofstream* fout;

  int debug(const string &sLog);
  int debug(const string &sLog1, const string &sLog2);

};

static Debug debugger;

#endif