/* -*- C++ -*- */

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
// AccessBean.h: interface for the AccessBean class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSBEAN_H__DAFED24B_0423_4501_BD9C_8EE072651FFF__INCLUDED_)
#define AFX_ACCESSBEAN_H__DAFED24B_0423_4501_BD9C_8EE072651FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//this is a trick :-)
#define ACCESSBEAN_SERIALIZABLE int DeSerialize(SoapDeSerializer *pDZ);string& Serialize();

#include <string>
#include "../common/GDefine.h"
#include "../soap/TypeMapping.h"

using namespace std;

class SoapDeSerializer;
class SoapSerializer;

class AccessBean  
{
public:
	AccessBean();
	virtual ~AccessBean(){};
	virtual int DeSerialize(SoapDeSerializer *pDZ);
	virtual string& Serialize();
public:
	string m_TypeName;//array type name in case of complex type arrays 
	string m_URI;
	string m_sSZ; //Used for serialization
};

//This class is used inside Param class and wrapper classes only.
class ArrayBean : public AccessBean
{
public:
	ArrayBean();
	virtual ~ArrayBean();
	virtual int DeSerialize(SoapDeSerializer *pDZ);
	virtual string& Serialize();
public:
	XSDTYPE t; //array element type
	int s; //array size only one dimensional arrays
	string m_ItemName;//name of an item like <item>34</item>
	union uAValue //this is useful only when Param is used as a return parameter
	{
		void* so; //for simple types
		AccessBean** co; //for complex types
	}v;	
};

#endif // !defined(AFX_ACCESSBEAN_H__DAFED24B_0423_4501_BD9C_8EE072651FFF__INCLUDED_)
