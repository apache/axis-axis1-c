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

// ArrayBean.h: interface for the ArrayBeanI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_)
#define AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_

#include "IArrayBean.h"
#include "IParam.h"
#include "BasicTypeSerializer.h"

#include <list>
using namespace std;

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

public:
	XSDTYPE m_type; //array element type
	list<int> m_size; //array size only one dimensional arrays
	AxisString m_ItemName;//name of an item like <item>34</item>
	union uAValue //this is useful only when Param is used as a return parameter
	{
		void* sta; //simple type array
		ComplexObjectHandler* cta; //complex type array
	}m_value;	
	AxisString m_TypeName;
	AxisString m_URI;
public: //IArrayBean Interface
	void AddDimension(int nDim);
	void SetItemName(const AxisChar* sName);
	void SetTypeName(const AxisChar* sName);
	void SetUri(const AxisChar* sURI);
	void RemoveArrayPointer();
private:
	BasicTypeSerializer m_BTSZ;
};

#endif // !defined(AFX_ARRAYBEAN_H__374BEDCF_E850_4907_9CF0_F2EBC61E54CF__INCLUDED_)
