// ArrayBean.h: interface for the ArrayBeanI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_)
#define AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IArrayBean.h"

#include <list>
using namespace std;

class AccessBean;
//This class is used inside Param class and wrapper classes only.
class ArrayBean : public IArrayBean
{
public:
	ArrayBean();
	virtual ~ArrayBean();
	virtual int DeSerialize(IWrapperSoapDeSerializer *pDZ);
	virtual int Serialize(IWrapperSoapSerializer& pSZ);
	int GetArraySize();
private:
	int GetArrayBlockSize(list<int>::iterator it);
//	void DeleteArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim);
//	int SerializeArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim, string& sSerialized);
//	int DeSerializeArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim, SoapDeSerializer *pDZ);

public:
	XSDTYPE m_type; //array element type
	list<int> m_size; //array size only one dimensional arrays
	string m_ItemName;//name of an item like <item>34</item>
	union uAValue //this is useful only when Param is used as a return parameter
	{
		void* sta; //simple type array
		AccessBean* cta; //complex type array
	}m_value;	
	string m_TypeName;
	string m_URI;
public: //IArrayBean Interface
	void AddDimension(int nDim);
	void SetItemName(char* sName);
};

#endif // !defined(AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_)
