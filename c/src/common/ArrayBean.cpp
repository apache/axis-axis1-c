/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
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
	m_ItemName = L"";
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
int ArrayBean::DeSerialize(IWrapperSoapDeSerializer *pDZ)
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
			AxisString* a = (AxisString*)m_value.sta;
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
				pSZ << m_BTSZ.serialize(m_ItemName.c_str(), *pInt);
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
				pSZ << m_BTSZ.serialize(m_ItemName.c_str(), *pFloat);
				pFloat++;
			}
		}
		break;
	case XSD_STRING:
		{
			AxisString* pStr = (AxisString*)m_value.sta;
			list<int>::iterator it = m_size.begin();
			int blocksize = GetArrayBlockSize(it);
			for (int ix=0;ix<blocksize;ix++)
			{
				pSZ << m_BTSZ.serialize(m_ItemName.c_str(), pStr->c_str());
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

void ArrayBean::SetItemName(const AxisChar* sName)
{
	m_ItemName = sName;
}