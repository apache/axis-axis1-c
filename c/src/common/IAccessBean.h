// IAccessBean.h: interface for the IAccessBean class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IACCESSBEAN_H__63D8C61C_7F96_4E01_89BB_0EB528DADB00__INCLUDED_)
#define AFX_IACCESSBEAN_H__63D8C61C_7F96_4E01_89BB_0EB528DADB00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//this is a trick :-)
#define ACCESSBEAN_SERIALIZABLE int DeSerialize(IWrapperSoapDeSerializer *pDZ);int Serialize(IWrapperSoapSerializer& pSZ); int GetSize();

#include "IWrapperSoapSerializer.h"
#include "IWrapperSoapDeSerializer.h"

class IAccessBean  
{
	friend class Param;
	friend class XMLStreamHandler;
public:
	IAccessBean(){};
	virtual ~IAccessBean(){};
	virtual int DeSerialize(IWrapperSoapDeSerializer *pDZ) = 0;
	virtual int Serialize(IWrapperSoapSerializer& pSZ) = 0;
	virtual int GetSize() = 0;
protected:
	string m_TypeName;
	string m_URI;
};

#endif // !defined(AFX_IACCESSBEAN_H__63D8C61C_7F96_4E01_89BB_0EB528DADB00__INCLUDED_)
