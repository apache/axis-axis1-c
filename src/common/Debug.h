#ifndef __AXISLOG_H_INCLUDED_
#define __AXISLOG_H_INCLUDED_

#include "GDefine.h"
#include <list>
#include <string>
#include <fstream>

#define DEBUG
#if defined(DEBUG)
  #define DEBUG1(X) debugger.debug(X,__FILE__,__LINE__);  
  #define DEBUG2(X,Y) debugger.debug(X,Y,__FILE__,__LINE__);
#endif
#if !defined(DEBUG)
  #define DEBUG1(X) "";
  #define DEBUG2(X,Y) ""; 
#endif

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

  int debug(const string &sLog, string arg2, int arg3);
  int debug(const string &sLog1, const string &sLog2, string arg3, int arg4);

};

static Debug debugger;

#endif