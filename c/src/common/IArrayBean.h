// IArrayBean.h: interface for the IArrayBean class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IARRAYBEAN_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_)
#define AFX_IARRAYBEAN_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IArrayBean  
{
public:
	IArrayBean(){};
	virtual ~IArrayBean(){};
	//API needed for the Wrapper class to manipulate ArrayBeans
	virtual void AddDimension(int nDim)=0;
	virtual void SetItemName(char* sName)=0;
};

#endif // !defined(AFX_IARRAYBEAN_H__6E27008D_DCA0_4F28_AC82_FEEBE1A1CBBB__INCLUDED_)
