// AxisSocketUtils.cpp: implementation of the AxisSocketUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "AxisSocketUtils.h"
#include "GDefine.h"
#include <stdio.h>
#ifdef WIN32
#include <winsock.h>    /* for socket(),... */
#else //Linux
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AxisSocketUtils::AxisSocketUtils()
{

}

AxisSocketUtils::~AxisSocketUtils()
{

}

int AxisSocketUtils::printSocketErrorDescription()
{
	#ifdef WIN32
		int iError = WSAGetLastError();		

		if (iError == WSANOTINITIALISED) {
			printf("%s\n", "WSANOTINITIALISED");
		} else if (iError == WSAENETDOWN) {
			printf("%s\n", "WSAENETDOWN");
		} else if (iError == WSAEFAULT) {
			printf("%s\n", "WSAEFAULT");
		} else if (iError == WSAEINTR) {
			printf("%s\n", "WSAEINTR");
		} else if (iError == WSAEINPROGRESS) {
			printf("%s\n", "WSAEINPROGRESS");
		} else if (iError == WSAEINVAL) {
			printf("%s\n", "WSAEINVAL");
		} else if (iError == WSAEMFILE) {
			printf("%s\n", "WSAEMFILE");
		} else if (iError == WSAENOBUFS) {
			printf("%s\n", "WSAENOBUFS");
		} else if (iError == WSAENOTSOCK) {
			printf("%s\n", "WSAENOTSOCK");
		} else if (iError == WSAEOPNOTSUPP) {
			printf("%s\n", "WSAEOPNOTSUPP");
		} else if (iError == WSAEWOULDBLOCK) {
			printf("%s\n", "WSAEWOULDBLOCK");
		} 
	#else //Linux
	#endif

	return SUCCESS;
}
