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
	//TODO
	*ppSZ = new SoapSerializer();
	return SUCCESS;
}

int SerializerPool::PutInstance(SoapSerializer* pSZ)
{
	//TODO
	delete pSZ;
	return SUCCESS;
}
