// DeserializerPool.cpp: implementation of the DeserializerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "DeserializerPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DeserializerPool::DeserializerPool()
{

}

DeserializerPool::~DeserializerPool()
{
	for (list<SoapDeSerializer*>::iterator it = m_DZList.begin(); it != m_DZList.end(); it++)
	{
		delete (*it);
	}
}

int DeserializerPool::GetInstance(SoapDeSerializer** ppDZ)
{
	lock();
	if (!m_DZList.empty())
	{
		*ppDZ = m_DZList.front();
		m_DZList.pop_front();
	}
	else
	{
		*ppDZ = new SoapDeSerializer();
		if (SUCCESS != (*ppDZ)->Init())
		{
			delete *ppDZ;
			*ppDZ = NULL;
			unlock();
			return FAIL;
		}
	}
	unlock();
	return SUCCESS;
}

int DeserializerPool::PutInstance(SoapDeSerializer* pDZ)
{
	if (SUCCESS != pDZ->Init())
	{
		delete pDZ;
		return FAIL;
	}
	lock();
	m_DZList.push_back(pDZ);
	unlock();
	return SUCCESS;
}
