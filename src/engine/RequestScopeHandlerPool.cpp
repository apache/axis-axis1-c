// RequestScopeHandlerPool.cpp: implementation of the RequestScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "RequestScopeHandlerPool.h"
#include "HandlerLoader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HandlerLoader g_HandlerLoader;

RequestScopeHandlerPool::RequestScopeHandlerPool()
{

}

RequestScopeHandlerPool::~RequestScopeHandlerPool()
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

int RequestScopeHandlerPool::GetInstance(BasicHandler** pHandler, int nLibId)
{
	lock();
	int Status;
	if (m_Handlers.find(nLibId) != m_Handlers.end()) 
	{
		if (m_Handlers[nLibId].empty())
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

int RequestScopeHandlerPool::PutInstance(BasicHandler* pHandler, int nLibId)
{
	lock();
	m_Handlers[nLibId].push_back(pHandler);
	unlock();
	return SUCCESS;
}
