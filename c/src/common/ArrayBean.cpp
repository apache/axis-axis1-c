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
// ArrayBean.cpp: implementation of the ArrayBean class.
//
//////////////////////////////////////////////////////////////////////
#include <axis/common/Param.h>
#include <axis/common/ArrayBean.h>
#include <axis/common/BasicTypeSerializer.h>
#include <axis/engine/AxisEngine.h>

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
	if (USER_TYPE == m_type)
	{
		if (m_value.cta)
		{
			if (m_value.cta->pObject)
			{
				if (AxisEngine::m_bServer)
				{
					m_value.cta->pDelFunct(m_value.cta->pObject, true, m_nSize);
				}
				/* make sure that the ComplexObjectHandler's destructor does not try to delete the objects again */
				m_value.cta->pObject = NULL;
			}
			delete m_value.cta;
		}
	}
	else if (AxisEngine::m_bServer && m_value.sta)
	{
		switch (m_type)
		{
		case XSD_BYTE:
		case XSD_UNSIGNEDBYTE:
			{
				char* a = (char*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_SHORT:
		case XSD_UNSIGNEDSHORT:
			{
				short* a = (short*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_INT:
		case XSD_UNSIGNEDINT:
		case XSD_BOOLEAN:
			{
				int* a = (int*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_LONG:
		case XSD_UNSIGNEDLONG:
		case XSD_INTEGER:
		case XSD_DURATION:		
			{
				long* a = (long*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_FLOAT:
			{
				float* a = (float*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_DOUBLE:
		case XSD_DECIMAL:
			{
				double* a = (double*)m_value.sta;
				delete [] a;
			}
			break;
		case XSD_STRING:
		case XSD_ANYURI:
		case XSD_QNAME:
		case XSD_NOTATION:			
			{
				AxisChar** a = (AxisChar**)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					free(*a);
					a++;
				}
				free(m_value.sta);
			}
			break;
		case XSD_HEXBINARY:
			{
				xsd__hexBinary* a = (xsd__hexBinary*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					free(a->__ptr);
					a++;
				}
				free(m_value.sta);
			}
			break;
		case XSD_BASE64BINARY:
			{
				xsd__base64Binary* a = (xsd__base64Binary*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					free(a->__ptr);
					a++;
				}
				free(m_value.sta);
			}
			break;
		case XSD_DATETIME:
		case XSD_TIME:
		case XSD_DATE:
		case XSD_YEARMONTH:
		case XSD_YEAR:
		case XSD_MONTHDAY:
		case XSD_DAY:
		case XSD_MONTH:
			{
				tm* a = (tm*)m_value.sta;
				delete [] a;
			}
			break;
			//continue this for all basic types
		default:;
		}	
	}
}

int ArrayBean::GetArraySize()
{	
	return m_nSize;
}

int ArrayBean::Serialize(SoapSerializer& pSZ)
{	
	if (USER_TYPE == m_type)
	{
		void* pItem;
		AXIS_BINDING_STYLE nStyle = pSZ.GetStyle();
		int itemsize = m_value.cta->pSizeFunct();
		unsigned long ptrval = reinterpret_cast<unsigned long>(m_value.cta->pObject);
		if (DOC_LITERAL == nStyle) 
		/* Serialize functions for doc/lit services do not know the instance name and 
		will not serialize outer element for the type */ 
		{
			for (int x=0; x<m_nSize; x++)
			{
				pItem = reinterpret_cast<void*>(ptrval+x*itemsize);
				pSZ.Serialize("<", m_ItemName.c_str(), NULL); /* note : ">" is not serialized to enable the type's serializer to add attributes */
				m_value.cta->pSZFunct(pItem, &pSZ, true); /* no matter true or false is passed */
				pSZ.Serialize("</", m_ItemName.c_str(), ">", NULL);
			}
		}
		else 
		/* Serialize functions for RPC-encoded services will serialize outer element 
		for the type. Also the type information is not added to the outer element as
		this object is part of an array (serialize function knows that when the 3rd
		parameter is 'true'. */
		{
			for (int x=0; x<m_nSize; x++)
			{
				pItem = reinterpret_cast<void*>(ptrval+x*itemsize);
				m_value.cta->pSZFunct(pItem, &pSZ, true);
			}
		}
	}
	else
	{
		AXIS_BINDING_STYLE nStyle = pSZ.GetStyle();
		/* this is to prevent serializing type information for basic array elements */ 
		if (RPC_ENCODED == nStyle) pSZ.SetStyle(RPC_LITERAL); 
		switch (m_type)
		{
		case XSD_BYTE:
		case XSD_UNSIGNEDBYTE:
			{
				char* p = (char*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_SHORT:
		case XSD_UNSIGNEDSHORT:
			{
				short* p = (short*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_LONG:
		case XSD_UNSIGNEDLONG:
		case XSD_INTEGER:
		case XSD_DURATION:		
			{
				long* p = (long*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_DOUBLE:
		case XSD_DECIMAL:
			{
				double* p = (double*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_DATETIME:
		case XSD_TIME:
		case XSD_DATE:
		case XSD_YEARMONTH:
		case XSD_YEAR:
		case XSD_MONTHDAY:
		case XSD_DAY:
		case XSD_MONTH:
			{
				tm* p = (tm*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_INT:
		case XSD_UNSIGNEDINT:
		case XSD_BOOLEAN:
			{
				int* p = (int*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_FLOAT:
			{
				float* p = (float*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_STRING:
		case XSD_ANYURI:
		case XSD_QNAME:
		case XSD_NOTATION:			
			{
				AxisChar** p = (AxisChar**)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_HEXBINARY:
			{
				xsd__hexBinary* p = (xsd__hexBinary*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		case XSD_BASE64BINARY:
			{
				xsd__base64Binary* p = (xsd__base64Binary*)m_value.sta;
				for (int ix=0;ix<m_nSize;ix++)
				{
					pSZ.SerializeAsElement(m_ItemName.c_str(), (void*)p, m_type);
					p++;
				}
			}
			break;
		}
		/* restore Serializer's style after array serialization is finished */
		if (RPC_ENCODED == nStyle) pSZ.SetStyle(RPC_ENCODED);
	}
	return AXIS_SUCCESS;
}

void ArrayBean::SetDimension(int nDim)
{
	m_nSize = nDim;
}

void ArrayBean::SetItemName(const AxisChar* sName)
{
	m_ItemName = sName;
}

void ArrayBean::SetTypeName(const AxisChar* sName)
{
	m_TypeName = sName;
}

void ArrayBean::SetUri(const AxisChar* sURI)
{
	m_URI = sURI;
}
/**
 * Used to remove the pointer to the object array. Mostly to avoid deletion
 * by the destructor.
 */
void ArrayBean::RemoveArrayPointer()
{
	if (USER_TYPE == m_type)
	{
		if (m_value.cta)
		{
			m_value.cta->pObject = NULL;	
		}
	}
	else
	{
		m_value.sta = NULL;
	}
}
