// SerializerPool.cpp: implementation of the SerializerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "SerializerPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SerializerPool::SerializerPool()
{

}

SerializerPool::~SerializerPool()
{

}

//pooling should be implemented
int SerializerPool::GetInstance(SoapSerializer** ppSZ)
{
	lock();
	if (!m_SZList.empty())
	{
		*ppSZ = m_SZList.front();
		m_SZList.pop_front();
	}
	else
	{
		*ppSZ = new SoapSerializer();
	}
	if (!(*ppSZ))
	{
		unlock();
		return FAIL;		
	}
	if (SUCCESS != (*ppSZ)->Init())
	{
		m_SZList.push_back(*ppSZ);
		*ppSZ = NULL;
		unlock();
		return FAIL;
	}
	unlock();
	return SUCCESS;
}

int SerializerPool::PutInstance(SoapSerializer* pSZ)
{
	lock();
	m_SZList.push_back(pSZ);
	unlock();
	return SUCCESS;
}
