// ArrayBean.cpp: implementation of the ArrayBeanI class.
//
//////////////////////////////////////////////////////////////////////
#include "AccessBean.h"
#include "ArrayBean.h"
#include "BasicTypeSerializer.h"
#include "Param.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ArrayBean::ArrayBean()
{
	m_type = XSD_UNKNOWN;
	m_ItemName = "";
	m_value.sta = NULL;
}

ArrayBean::~ArrayBean()
{
	switch (m_type)
	{
	case XSD_INT:
		{
			int* a = (int*)m_value.sta;
			delete [] a;
		}
		break;
	case XSD_FLOAT:
		{
			float* a = (float*)m_value.sta;
			delete [] a;
		}
		break;
	case XSD_STRING:
		{
			string* a = (string*)m_value.sta;
			delete [] a;
		}
		break;
		//continue this for all basic types
	case USER_TYPE: //array of user types
		{
			AccessBean* pItem;
			int itemsize = m_value.cta->GetSize();
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta);
			for (int x=0; x<blocksize; x++)
			{
				pItem = reinterpret_cast<AccessBean*>(ptrval+x*itemsize);
				delete pItem;
			}
		}
		break;
	default:;
	}	
}

int ArrayBean::GetArraySize()
{
	list<int>::iterator it = m_size.begin();	
	return GetArrayBlockSize(it);
}

int ArrayBean::GetArrayBlockSize(list<int>::iterator it)
{
	int size = *it;
	it++;
	if (it != m_size.end())
	{
		return size*GetArrayBlockSize(it);	
	}
	else
	{
		return size;
	}
}
/*
void ArrayBean::DeleteArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim)
{
	AccessBean* p;
	nDim--;
	if (nDim > 0)
	{	
		int curdim = *it;
		it++;
		for (int d=0; d<curdim; d++) //do for each dimension
		{
			DeleteArray(it,nItemOffset + GetArrayBlockSize(it)*d,nItemSize,nDim);
		}
		return;
	}
	unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta) + nItemOffset*nItemSize;
	for (int x=0; x<*it; x++)
	{
		p = reinterpret_cast<AccessBean*>(ptrval+x*nItemSize);
		delete p;
	}
}
*/
int ArrayBean::DeSerialize(ISoapDeSerializer *pDZ)
{
	Param* p;
	if ((XSD_UNKNOWN == m_type) ||(0==m_size.size())||(!m_value.sta)) return FAIL;
	switch (m_type)
	{
	case XSD_INT:
		{
			int* a = (int*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				p = (Param*)pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetInt();
			}
		}
		break;
	case XSD_FLOAT:
		{
			float* a = (float*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				p = (Param*)pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetFloat();
			}
		}
		break;
	case XSD_STRING:
		{
			string* a = (string*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				p = (Param*)pDZ->GetParam();
				if (!p) return FAIL;
				a[ix] = p->GetString();
			}
		}
		break;
		//continue this for all basic types
	case USER_TYPE: //array of user types
		{
			IAccessBean* pItem;
			int itemsize = m_value.cta->GetSize();
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta);
			for (int x=0; x<blocksize; x++)
			{
				pDZ->GetParam(); //discard outer param corresponding to custom type - get only inner members
				pItem = reinterpret_cast<IAccessBean*>(ptrval+x*itemsize);
				pItem->DeSerialize(pDZ);
			}
		}
		break;
	default:;
	}
	return SUCCESS;
}
/*
int ArrayBean::DeSerializeArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim, SoapDeSerializer *pDZ)
{
	AccessBean* p;
	nDim--;
	if (nDim > 0)
	{	
		int curdim = *it;
		it++;
		for (int d=0; d<curdim; d++) //do for each dimension
		{
			DeSerializeArray(it,nItemOffset + GetArrayBlockSize(it)*d,nItemSize,nDim,pDZ);
		}
		return SUCCESS;
	}
	unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta) + nItemOffset*nItemSize;
	for (int x=0; x<*it; x++)
	{
		p = reinterpret_cast<AccessBean*>(ptrval+x*nItemSize);
		p->DeSerialize(pDZ);
	}
	return SUCCESS;
}
*/
int ArrayBean::Serialize(IWrapperSoapSerializer& pSZ)
{	
	switch (m_type)
	{
	case XSD_INT:
		{
			int* pInt = (int*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				pSZ << BasicTypeSerializer::serialize(m_ItemName, *pInt).c_str();
				pInt++;
			}
		}
		break;
	case XSD_FLOAT:
		{
			float* pFloat = (float*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				pSZ << BasicTypeSerializer::serialize(m_ItemName, *pFloat).c_str();
				pFloat++;
			}
		}
		break;
	case XSD_STRING:
		{
			string* pStr = (string*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				pSZ << BasicTypeSerializer::serialize(m_ItemName, *pStr).c_str();
				pStr++;
			}
		}
		break;
	case USER_TYPE:
		{
			AccessBean* pItem;
			int itemsize = m_value.cta->GetSize();
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta);
			for (int x=0; x<blocksize; x++)
			{
				pItem = reinterpret_cast<AccessBean*>(ptrval+x*itemsize);
				pItem->Serialize(pSZ);
			}
		}
		break;
	default:;
	}
	return SUCCESS;
}
/*
int ArrayBean::SerializeArray(list<int>::iterator it, int nItemOffset, int nItemSize, int nDim, string& sSerialized)
{
	AccessBean* p;
	nDim--;
	if (nDim > 0)
	{	
		int curdim = *it;
		it++;
		for (int d=0; d<curdim; d++) //do for each dimension
		{
			SerializeArray(it,nItemOffset + GetArrayBlockSize(it)*d,nItemSize,nDim,sSerialized);
		}
		return SUCCESS;
	}
	unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta) + nItemOffset*nItemSize;
	for (int x=0; x<*it; x++)
	{
		p = reinterpret_cast<AccessBean*>(ptrval+x*nItemSize);
		p->Serialize(sSerialized);
	}
	return SUCCESS;
}
*/
void ArrayBean::AddDimension(int nDim)
{
	m_size.push_back(nDim);
}

void ArrayBean::SetItemName(char* sName)
{
	m_ItemName = sName;
}