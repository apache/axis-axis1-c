// SharedObject.h: interface for the SharedObject class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#if !defined(AFX_SHAREDOBJECT_H__0805D25C_2F7E_4B19_BECE_0A8BFE9F0830__INCLUDED_)
#define AFX_SHAREDOBJECT_H__0805D25C_2F7E_4B19_BECE_0A8BFE9F0830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SharedObject  
{
public:
	SharedObject();
	virtual ~SharedObject();
protected:
	int unlock();
	int lock();
private:
	volatile bool m_bLocked;
};

#endif // !defined(AFX_SHAREDOBJECT_H__0805D25C_2F7E_4B19_BECE_0A8BFE9F0830__INCLUDED_)
