// SessionScopeHandlerPool.h: interface for the SessionScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SESSIONSCOPEHANDLERPOOL_H__8F0188D8_B30B_43F9_8F06_8E209D7B8ABE__INCLUDED_)
#define AFX_SESSIONSCOPEHANDLERPOOL_H__8F0188D8_B30B_43F9_8F06_8E209D7B8ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SESSIONLESSHANDLERS	"0aaaaa"

#include "SharedObject.h"
#include "../common/BasicHandler.h"

#include <map>
#include <list>
#include <string>

using namespace std;

class SessionScopeHandlerPool : protected SharedObject  
{
public:
	SessionScopeHandlerPool();
	virtual ~SessionScopeHandlerPool();
private:
	typedef map<string, list<BasicHandler*> > SessionHandlers;
	map<int, SessionHandlers*> m_Handlers;
public:
	int GetInstance(string& sSessionId, BasicHandler** pHandler, int nLibId);
	int PutInstance(string& sSessionId, BasicHandler* pHandler, int nLibId);
	void EndSession(string& sSessionId);
};

#endif // !defined(AFX_SESSIONSCOPEHANDLERPOOL_H__8F0188D8_B30B_43F9_8F06_8E209D7B8ABE__INCLUDED_)
