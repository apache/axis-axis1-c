// AppScopeHandlerPool.cpp: implementation of the AppScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "AppScopeHandlerPool.h"
#include "HandlerLoader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HandlerLoader g_HandlerLoader;

//this class does not do the object level blocking. Instead expects the 
//thread level blocking and waiting by the caller thread.
AppScopeHandlerPool::AppScopeHandlerPool()
{

}

AppScopeHandlerPool::~AppScopeHandlerPool()
{
	for (map<int, list<BasicHandler*> >::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++)
	{
		for (list<BasicHandler*>::iterator itr = (*it).second.begin(); itr != (*it).second.end(); itr++)
		{
			g_HandlerLoader.DeleteHandler(*itr, (*it).first);
		}
		(*it).second.clear();
	}
	m_Handlers.clear();
}

//this method does not block the object. Instead expects that the calling thread 
//MUST block itself and wait if the requested handler is not found.
int AppScopeHandlerPool::GetInstance(BasicHandler** pHandler, int nLibId)
{
	lock();
	int Status;
	if (m_Handlers.find(nLibId) != m_Handlers.end()) 
	{
		if (m_Handlers[nLibId].empty()) 
		// this means that the object is being used by some other thread
		// but we cannot create any more objects because this is an application
		// scope object. So just return HANDLER_BEING_USED
		{
			unlock();
			return HANDLER_BEING_USED;
		}
		else
		{
			*pHandler = m_Handlers[nLibId].front();
			m_Handlers[nLibId].pop_front();
			unlock();
			return SUCCESS;
		}
	}
	else //not even the handler DLL loaded
	{
		Status = g_HandlerLoader.CreateHandler(pHandler, nLibId);
		if (SUCCESS == Status)
		{
			//this just creates the entry in m_Handlers so that next time we know that the DLL is loaded
			m_Handlers[nLibId].clear();	
		}
		unlock();
		return Status;
	}
}

int AppScopeHandlerPool::PutInstance(BasicHandler* pHandler, int nLibId)
{
	lock();
	m_Handlers[nLibId].push_back(pHandler);
	unlock();
	return SUCCESS;
}
