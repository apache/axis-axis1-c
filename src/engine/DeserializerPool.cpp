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
	}
	if (!(*ppDZ))
	{
		unlock();
		return FAIL;		
	}
	if (SUCCESS != (*ppDZ)->Init())
	{
		m_DZList.push_back(*ppDZ);
		*ppDZ = NULL;
		unlock();
		return FAIL;
	}
	unlock();
	return SUCCESS;
}

int DeserializerPool::PutInstance(SoapDeSerializer* pDZ)
{
	lock();
	m_DZList.push_back(pDZ);
	unlock();
	return SUCCESS;
}
