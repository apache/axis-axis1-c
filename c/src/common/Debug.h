#ifndef __DEBUG_H_INCLUDED_
#define __DEBUG_H_INCLUDED_

#include "AxisLog.h"
//#include <string>

using namespace std;

#define DEBUG

#define DEBUG_INCLUDE extern unsigned char chEBuf[1024];

#define DEBUG_ONE_PARA_LEVEL(X) \
sprintf((char*)chEBuf,X); \
objAxisLog.writeLog(X);

#define DEBUG_TWO_PARA_LEVEL(X,Y) \
sprintf((char*)chEBuf,X,Y); \
objAxisLog.writeLog(X,Y);	
//objAxisLog.writeLog(X);

#endif
