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
 */

// Param.h:
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_)
#define AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_

#include <axis/common/IParam.h>
#include <axis/common/BasicTypeSerializer.h>
#include "AxisTime.h"

#include <string>
using namespace std;

class ArrayBean;
/**
    @class Param
    @brief interface for the Param class.


    @author Susantha Kumara (skumara@virtusa.com)
*/
class Param : public IParam
{
	friend class SoapSerializer;
public:
	Param(){ m_Type = USER_TYPE;}; //if there is no attribute that says the type
	virtual ~Param();

private:
	uParamValue m_Value;
	AxisString m_sName; //Name of the parameter
	XSDTYPE m_Type; //Type of the parameter

private:
	AxisString m_strPrefix; //needed in serialization only
	AxisString m_strUri; //needed in serialization only

public: 
	int SetValue(XSDTYPE nType, uParamValue Value);
	int serialize(SoapSerializer& pSZ);
	void setPrefix(const AxisChar* prefix);
	void setUri(const AxisChar* uri);
	int SetArrayElements(void* pElements);
	int SetArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct);
	int SetUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct);
	void SetName(const AxisChar* sName);
};

#endif // !defined(AFX_PARAM_H__351B13BB_5D03_40C5_93F5_56D17295A8BD__INCLUDED_)
