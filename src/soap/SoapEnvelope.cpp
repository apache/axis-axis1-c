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

// SoapEnvelope.cpp: implementation of the SoapEnvelope class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapEnvelope.h>
#include <axis/common/GDefine.h>
#include <axis/soap/SoapSerializer.h>

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapEnvelope::SoapEnvelope()
{
	m_pSoapHeader= NULL;
	m_pSoapBody= NULL;
}

SoapEnvelope::~SoapEnvelope()
{
	//deletion of attributes
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		delete *itCurrAttribute;
		itCurrAttribute++;
	}

	m_attributes.clear();

	//deletion of namespace declerations
	list<Attribute*>::iterator itCurrNamespaceDecls= m_namespaceDecls.begin();

	while(itCurrNamespaceDecls != m_namespaceDecls.end()) {		
		delete *itCurrNamespaceDecls;
		itCurrNamespaceDecls++;
	}

	m_namespaceDecls.clear();

	//deletion of soap header
	if(m_pSoapHeader) {
		delete m_pSoapHeader;
	}

	//deletion of soap body
	if(m_pSoapBody) {
		delete m_pSoapBody;
	}
}

void SoapEnvelope::setSoapHeader(SoapHeader* soapHeader)
{
	m_pSoapHeader= soapHeader;
}

void SoapEnvelope::setSoapBody(SoapBody* soapBody)
{
	m_pSoapBody= soapBody;
}

int SoapEnvelope::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{	
	int iStatus= AXIS_SUCCESS;
	do {			
		pSZ << "<" << gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix << ":" << gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE];			
		serializeStandardNamespaceDecl(pSZ);
		serializeNamespaceDecl(pSZ);
		serializeAttributes(pSZ);
		pSZ << ">";
		if(m_pSoapHeader!=NULL) {
			iStatus= m_pSoapHeader->serialize(pSZ, eSoapVersion);
			if(iStatus == AXIS_FAIL) {
				break;
			}
		}
		if(m_pSoapBody!=NULL) {
			iStatus= m_pSoapBody->serialize(pSZ, eSoapVersion);
			if(iStatus == AXIS_FAIL) {
				break;
			}
		} else {
			//throw exception
			//iStatus = AXIS_FAIL;
		}
				
		pSZ << "</" << gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix << ":" << gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE] << ">";
	} while(0);

	return iStatus;
}

/*
commented on 10Jul2003
int SoapEnvelope::serialize(string &sSerialized, SOAP_VERSION eSoapVersion)
{	
	
	int iStatus= AXIS_SUCCESS;

	do {
		sSerialized= "<"+ string(gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix) + ":"+ gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE];

		serializeNamespaceDecl(sSerialized);
		serializeAttributes(sSerialized);

		sSerialized= sSerialized + ">"+ "\n";

		if(m_pSoapHeader!=NULL) {
			iStatus= m_pSoapHeader->serialize(sSerialized, eSoapVersion);
			if(iStatus == AXIS_FAIL) {
				break;
			}
		}

		if(m_pSoapBody!=NULL) {
			iStatus= m_pSoapBody->serialize(sSerialized, eSoapVersion);
			if(iStatus == AXIS_FAIL) {
				break;
			}
		} else {
			//throw exception
			//iStatus = AXIS_FAIL;
		}
		
		sSerialized+= "</"+ string(gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix) + ":"+ gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_ENVELOPE]+ ">";	
	} while(0);

	return iStatus;
}*/

/*
 *The added attrubute will be deleted by the destructor of this 
 * SoapEnvelope.
 */
int SoapEnvelope::addAttribute(Attribute *pAttribute)
{
	m_attributes.push_back(pAttribute);

	return AXIS_SUCCESS;
}

/*
 *The added NamespaceDecl will be deleted by the destructor of this 
 * SoapEnvelope.
 */
int SoapEnvelope::addNamespaceDecl(Attribute *pAttribute)
{
	m_namespaceDecls.push_back(pAttribute);

	return AXIS_SUCCESS;
}

int SoapEnvelope::serializeAttributes(SoapSerializer& pSZ)
{	
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		(*itCurrAttribute)->serialize(pSZ);
		itCurrAttribute++;		
	}	

	return AXIS_SUCCESS;	
}

/*
commented on 10Jul2003 3.30 pm
int SoapEnvelope::serializeAttributes(string& sSerialized)
{	
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		(*itCurrAttribute)->serialize(sSerialized);
		itCurrAttribute++;		
	}	

	return AXIS_SUCCESS;	
}
*/

int SoapEnvelope::serializeNamespaceDecl(SoapSerializer& pSZ)
{	

	list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

	while(itCurrNamespaceDecl != m_namespaceDecls.end()) {			

		(*itCurrNamespaceDecl)->serialize(pSZ);
		itCurrNamespaceDecl++;		
	}	

	return AXIS_SUCCESS;
}

/*
commented on 10Jul2003 3.30 pm
int SoapEnvelope::serializeNamespaceDecl(string& sSerialized)
{	

	list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

	while(itCurrNamespaceDecl != m_namespaceDecls.end()) {			

		(*itCurrNamespaceDecl)->serialize(sSerialized);
		itCurrNamespaceDecl++;		
	}	

	return AXIS_SUCCESS;
}
*/

/*
 * This method is needed in the situation where we create and fill a 
 * SoapEnvelope object when deserializing a incoming soap request.
 * But this method is not needed in serializing a soap request, because
 * the version specific prefix is taken from the SoapEnvVersions.h at 
 * that time.
 */
int SoapEnvelope::setPrefix(const AxisChar* prefix)
{
	m_sPrefix= prefix;

	return AXIS_SUCCESS;
}

int SoapEnvelope::addStandardNamespaceDecl(const Attribute *pAttribute)
{
	m_StandardNamespaceDecls.push_back(pAttribute);
	return AXIS_SUCCESS;
}

int SoapEnvelope::serializeStandardNamespaceDecl(SoapSerializer &pSZ)
{
	list<const Attribute*>::iterator itCurrNamespaceDecl= m_StandardNamespaceDecls.begin();
	while(itCurrNamespaceDecl != m_StandardNamespaceDecls.end()) 
	{			
		(*itCurrNamespaceDecl)->serialize(pSZ);
		itCurrNamespaceDecl++;		
	}	
	return AXIS_SUCCESS;
}
