// RequestScopeHandlerPool.h: interface for the RequestScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REQUESTSCOPEHANDLERPOOL_H__310FD607_517E_4644_8922_0B1CFDE9E5BE__INCLUDED_)
#define AFX_REQUESTSCOPEHANDLERPOOL_H__310FD607_517E_4644_8922_0B1CFDE9E5BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedObject.h"
#include "../common/BasicHandler.h"

#include <map>
#include <list>
#include <string>

using namespace std;

class RequestScopeHandlerPool : protected SharedObject  
{
public:
	RequestScopeHandlerPool();
	virtual ~RequestScopeHandlerPool();
private:
	map<int, list<BasicHandler*> > m_Handlers;
public:
	int GetInstance(BasicHandler** pHandler, int nLibId);
	int PutInstance(BasicHandler* pHandler, int nLibId);
};

#endif // !defined(AFX_REQUESTSCOPEHANDLERPOOL_H__310FD607_517E_4644_8922_0B1CFDE9E5BE__INCLUDED_)
