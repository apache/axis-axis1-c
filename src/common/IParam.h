// IParam.h: interface for the IParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_)
#define AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IAccessBean.h"
#include "TypeMapping.h"
#include <string>
using namespace std;

typedef union uParamValue
{
	int nValue;
	float fValue;
	double dValue;
	//all basic types should come here
	class ArrayBean* pArray; //this is used to hold arrays
	class IArrayBean* pIArray; //used by wrapper classes
	class AccessBean* pBean; //this is used to hold user types
	class IAccessBean* pIBean; //used by wrapper classes
	//following is used by the wrapper class to set return value in case of strings	
	const char* pStrValue; 
} uParamValue;

class IParam  
{
public:
	IParam(){};
	virtual ~IParam(){};
	virtual int GetInt()=0;
	virtual float GetFloat()=0;
	virtual const string& GetString()=0;
	virtual const string& GetHexString()=0;
	virtual const string& GetBase64String()=0;
	virtual int GetArraySize()=0;
	virtual int SetArrayElements(void* pElements)=0;
	virtual int SetUserType(IAccessBean* pObject)=0;
	virtual void SetName(char* sName)=0;
};

#endif // !defined(AFX_IPARAM_H__25C278BB_5875_49E6_A3EC_B6AD3E543D69__INCLUDED_)
