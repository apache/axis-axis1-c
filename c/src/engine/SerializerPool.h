// SerializerPool.h: interface for the SerializerPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALIZERPOOL_H__45283A27_9196_4ACF_952F_88C564A4BD40__INCLUDED_)
#define AFX_SERIALIZERPOOL_H__45283A27_9196_4ACF_952F_88C564A4BD40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedObject.h"
#include "../soap/SoapSerializer.h"
#include "../common/GDefine.h"
#include <list>

using namespace std;

class SerializerPool : protected SharedObject  
{
public:
	SerializerPool();
	virtual ~SerializerPool();
private:
	list<SoapSerializer*> m_SZList;
public:
	int GetInstance(SoapSerializer** ppSZ);
	int PutInstance(SoapSerializer* pSZ);
};

#endif // !defined(AFX_SERIALIZERPOOL_H__45283A27_9196_4ACF_952F_88C564A4BD40__INCLUDED_)
