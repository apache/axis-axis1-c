// SessionScopeHandlerPool.cpp: implementation of the SessionScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4503)

#include "SessionScopeHandlerPool.h"
#include "HandlerLoader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HandlerLoader g_HandlerLoader;

SessionScopeHandlerPool::SessionScopeHandlerPool()
{

}

SessionScopeHandlerPool::~SessionScopeHandlerPool()
{
	for (map<int, SessionHandlers*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++)
	{
		SessionHandlers* pSH = (*it).second;
		for (SessionHandlers::iterator itr = pSH->begin(); itr != pSH->end(); itr++)
		{
			for (list<BasicHandler*>::iterator ite = (*itr).second.begin(); ite != (*itr).second.end(); ite++)
			{
				g_HandlerLoader.DeleteHandler(*ite, (*it).first);
			}
			(*itr).second.clear();
		}
		delete pSH;
	}
	m_Handlers.clear();
}

int SessionScopeHandlerPool::GetInstance(string& sSessionId, BasicHandler** pHandler, int nLibId)
{
	lock();
	int Status;
	if (m_Handlers.find(nLibId) != m_Handlers.end()) 
	{
		SessionHandlers* pSesHandlers = m_Handlers[nLibId];
		if (pSesHandlers->find(sSessionId) != pSesHandlers->end())
		{
			list<BasicHandler*> &HandlerList = ((*pSesHandlers)[sSessionId]);
			if (HandlerList.empty())
			{
				//check in the store for reuse
				if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty())
				{
					unlock();
					return g_HandlerLoader.CreateHandler(pHandler, nLibId);
				}
				else
				{
					*pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front();
					(*pSesHandlers)[SESSIONLESSHANDLERS].pop_front();
					unlock();
					return SUCCESS;
				}
			}
			else
			{
				*pHandler = HandlerList.front();
				HandlerList.pop_front();
				unlock();
				return SUCCESS;
			}
			unlock();
			return g_HandlerLoader.CreateHandler(pHandler, nLibId);
		}
		else //no handler list for this session id
		{
			//check in the store for reuse
			if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty())
			{
				unlock();
				return g_HandlerLoader.CreateHandler(pHandler, nLibId);
			}
			else
			{
				*pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front();
				(*pSesHandlers)[SESSIONLESSHANDLERS].pop_front();
				unlock();
				return SUCCESS;
			}
		}
	}
	else //not even the handler DLL loaded
	{
		Status = g_HandlerLoader.CreateHandler(pHandler, nLibId);
		if (SUCCESS == Status)
		{
			//this just creates the entry in m_Handlers so that next time we know that the DLL is loaded
			SessionHandlers* pNewSH = new SessionHandlers;
			pNewSH->clear();
			m_Handlers[nLibId] = pNewSH;	
		}
		unlock();
		return Status;
	}
}

int SessionScopeHandlerPool::PutInstance(string& sSessionId, BasicHandler* pHandler, int nLibId)
{
	lock();
	SessionHandlers* pSesHandlers;
	if (m_Handlers.find(nLibId) != m_Handlers.end())
	{
		pSesHandlers = m_Handlers[nLibId];
	}
	else // this is unexpected situation. anyway do it
	{
		pSesHandlers = new SessionHandlers;
		pSesHandlers->clear();
		m_Handlers[nLibId] = pSesHandlers;	
	}
	list<BasicHandler*> &HandlerList = ((*pSesHandlers)[sSessionId]);
	HandlerList.push_back(pHandler);
	unlock();
	return SUCCESS;
}

void SessionScopeHandlerPool::EndSession(string& sSessionId)
{
	//traverse all the lists and remove corresponding handlers if any and put to SESSIONLESSHANDLERS	
}
