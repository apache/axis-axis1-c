// AppScopeHandlerPool.h: interface for the AppScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPSCOPEHANDLERPOOL_H__A94BE166_F35A_40B9_8B17_9ED3D1886503__INCLUDED_)
#define AFX_APPSCOPEHANDLERPOOL_H__A94BE166_F35A_40B9_8B17_9ED3D1886503__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedObject.h"
#include "../common/BasicHandler.h"

#include <map>
#include <list>
#include <string>

using namespace std;

class AppScopeHandlerPool : protected SharedObject 
{
public:
	AppScopeHandlerPool();
	virtual ~AppScopeHandlerPool();
private:
	map<int, list<BasicHandler*> > m_Handlers;
public:
	int GetInstance(BasicHandler** pHandler, int nLibId);
	int PutInstance(BasicHandler* pHandler, int nLibId);
};

#endif // !defined(AFX_APPSCOPEHANDLERPOOL_H__A94BE166_F35A_40B9_8B17_9ED3D1886503__INCLUDED_)
