// DeserializerPool.h: interface for the DeserializerPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESERIALIZERPOOL_H__702116EF_3134_4ED4_8252_BEC1FC30E825__INCLUDED_)
#define AFX_DESERIALIZERPOOL_H__702116EF_3134_4ED4_8252_BEC1FC30E825__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SharedObject.h"
#include "../soap/SoapDeSerializer.h"
#include "../common/GDefine.h"
#include <list>

using namespace std;

class DeserializerPool : protected SharedObject  
{
public:
	DeserializerPool();
	virtual ~DeserializerPool();
private:
	list<SoapDeSerializer*> m_DZList;
public:
	int GetInstance(SoapDeSerializer** ppDZ);
	int PutInstance(SoapDeSerializer* pDZ);
};

#endif // !defined(AFX_DESERIALIZERPOOL_H__702116EF_3134_4ED4_8252_BEC1FC30E825__INCLUDED_)
