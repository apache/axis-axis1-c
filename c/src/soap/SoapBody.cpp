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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 *
 */

// SoapBody.cpp: implementation of the SoapBody class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapBody.h>
#include <axis/soap/SoapSerializer.h>
#include <axis/common/GDefine.h>
#include <axis/soap/Attribute.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapBody::SoapBody()
{
	m_pSoapMethod= NULL;
	m_pSoapFault= NULL;
}

SoapBody::~SoapBody()
{
	if(m_pSoapMethod) {
		delete m_pSoapMethod;
	}

	if(m_pSoapFault) {
		delete m_pSoapFault;
	}
}

void SoapBody::setSoapMethod(SoapMethod* ptrSoapMethod)
{
	m_pSoapMethod= ptrSoapMethod;
}

void SoapBody::setSoapFault(SoapFault *ptrSoapFault)
{
	m_pSoapFault= ptrSoapFault;
}

int SoapBody::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{
	int iStatus= SUCCESS;

	do {		
		pSZ.Serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY], NULL);
		iStatus= serializeAttributes(pSZ);
		if(iStatus==FAIL) {
			break;
		}
		
		pSZ.Serialize(">", NULL);

		if(m_pSoapMethod!=NULL) {
			iStatus= m_pSoapMethod->serialize(pSZ);
			if(iStatus==FAIL) {
				break;
			}
		} 
		else if(m_pSoapFault!=NULL) 
		{		
			iStatus= m_pSoapFault->serialize(pSZ);
			if(iStatus==FAIL) {
				break;
			}
		}
		else
		{
			m_pSoapFault = SoapFault::getSoapFault(SF_WEBSERVICEFAILED);
			if(m_pSoapFault!=NULL) 
			{		
				iStatus= m_pSoapFault->serialize(pSZ);
				if(iStatus==FAIL) 
					break;
			}
		}
		
		pSZ.Serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_BODY], ">", NULL);
	} while(0);

	return iStatus;
}

void SoapBody::addAttribute(Attribute *attr)
{
	m_attributes.push_back(attr);
}

int SoapBody::serializeAttributes(SoapSerializer& pSZ)
{
	int iStatus= SUCCESS;

	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		iStatus= (*itCurrAttribute)->serialize(pSZ);
		if(iStatus==FAIL) {
			break;
		}
		itCurrAttribute++;		
	}	

	return iStatus;
}
