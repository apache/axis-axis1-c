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

int DeserializerPool::GetInstance(SoapDeSerializer** ppSZ)
{
	//TODO
	*ppSZ = new SoapDeSerializer();
	return SUCCESS;
}

int DeserializerPool::PutInstance(SoapDeSerializer* pSZ)
{
	//TODO
	delete pSZ;
	return SUCCESS;
}
