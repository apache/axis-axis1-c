#if !defined(AFX_SERVERHELPER_H__INCLUDED_)
#define AFX_SERVERHELPER_H__INCLUDED_

#include <string>

using namespace std;

int getSeperatedHTTPParts(string sClientReqStream, string& sHTTPHeaders, string& sHTTPBody);

#endif // !defined(AFX_SERVERHELPER_H__INCLUDED_)