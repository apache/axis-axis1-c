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
	for (list<SoapSerializer*>::iterator it = m_SZList.begin(); it != m_SZList.end(); it++)
	{
		delete (*it);
	}
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
		if (SUCCESS != (*ppSZ)->Init())
		{
			delete *ppSZ;
			*ppSZ = NULL;
			unlock();
			return FAIL;
		}
	}
	unlock();
	return SUCCESS;
}

int SerializerPool::PutInstance(SoapSerializer* pSZ)
{
	if (SUCCESS != pSZ->Init())
	{
		delete pSZ;
		return FAIL;
	}
	lock();
	m_SZList.push_back(pSZ);
	unlock();
	return SUCCESS;
}
