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
 * @author Roshan
 *
 */

// SoapFault.cpp: implementation of the SoapFault class.
//
//////////////////////////////////////////////////////////////////////

#include "SoapFault.h"
#include "SoapEnvVersions.h"
#include "../common/GDefine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

map<int, SoapFaultStruct> SoapFault::m_sFaultMap;
bool SoapFault::m_bInit = false;

SoapFault::SoapFault()
{

}

SoapFault::~SoapFault()
{

}

/*int SoapFault::setFaultcode(const string& sFaultcode)
{
	m_sFaultcode= sFaultcode;

	return SUCCESS;
}*/

/*int SoapFault::setFaultstring(const string& sFaultstring)
{
	m_sFaultstring= sFaultstring;

	return SUCCESS;
}*/

/*int SoapFault::setFaultactor(const string& sFaultactor)
{
	m_sFaultactor= sFaultactor;

	return SUCCESS;
}*/

/*int SoapFault::setDetail(const string& sDetail)
{
	m_sDetail= sDetail;

	return SUCCESS;
}*/

int SoapFault::serialize(string& sSerialized)
{
	//written according to SOAP Version 1.1

	int iStatus= SUCCESS;
	
	sSerialized= sSerialized+ "<SOAP-ENV:Fault>" + "\n";
	sSerialized= sSerialized+ "<faultcode>"+ m_sFaultcode+ "</faultcode>"+ "\n";
	sSerialized= sSerialized+ "<faultstring>"+m_sFaultstring+"</faultstring>"+ "\n";

	if(!m_sFaultactor.empty()) {
		sSerialized= sSerialized+ "<faultactor>"+ m_sFaultactor +"</faultactor>"+ "\n";
	}

	if(!m_sDetail.empty()) {
		sSerialized= sSerialized+ "<detail>"+ m_sDetail +"</detail>"+ "\n";
	}

	sSerialized= sSerialized+ "</SOAP-ENV:Fault>" + "\n";

	return iStatus;
}

/*string& SoapFault::serialize()
{
	//written according to SOAP Version 1.2 Part 1 specification 
	// 17 December 2001 Working Draft.
    
	m_sFaultSerialized="";

	m_sFaultSerialized= "<faultcode>"+ m_sFaultcode+ "</faultcode>"+
		"<faultstring>"+m_sFaultstring+"</faultstring>";

	if(!m_sFaultactor.empty()) {
		m_sFaultSerialized+= "<faultactor>"+ m_sFaultactor +"</faultactor>";
	}

	if(!m_sDetail.empty()) {
		m_sFaultSerialized+= "<detail>"+ m_sDetail +"</detail>";
	}

	return m_sFaultSerialized;
}*/

void SoapFault::initialize()
{
	if (!m_bInit)
	{
		for (int sf=0; sf < FAULT_LAST; sf++)
		{
			m_sFaultMap[sf] = g_sObjSoapFaultStruct[sf];
		}
		m_bInit = true;
	}
}

/*the caller of the SoapFault::getSoapFault(int) has to delete the 
 * returned SoapFault pointer
 */
SoapFault* SoapFault::getSoapFault(int intFaultNo)
{	
	map<int, SoapFaultStruct>::iterator itSoapFault= m_sFaultMap.find(intFaultNo);
	SoapFault* pSoapFault= NULL;

	if(itSoapFault != m_sFaultMap.end()) {
		//fill the soap fault object
		pSoapFault= new SoapFault();
		
		//TO DO ************************************************
		//the soap envelope namespace prefix to be obtained from g_sObjSoapEnvVersionsStruct shoud depend on the relavent SOAP VERSION
		pSoapFault->m_sFaultcode= string(g_sObjSoapEnvVersionsStruct[SOAP_VER_1_1].pchEnvelopePrefix) + ":" +(*itSoapFault).second.pchFaultcode;
		pSoapFault->m_sFaultstring= (*itSoapFault).second.pchFaultstring;
		pSoapFault->m_sFaultactor= (*itSoapFault).second.pchFaultactor;
		pSoapFault->m_sDetail= (*itSoapFault).second.pchDetail;		
	} else {
		//throw exception
	}
	
	return pSoapFault;
}
