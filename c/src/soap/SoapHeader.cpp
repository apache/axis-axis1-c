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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

// SoapHeader.cpp: implementation of the SoapHeader class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapHeader.h>
#include <axis/soap/SoapSerializer.h>
#include <axis/common/GDefine.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapHeader::SoapHeader()
{

}

SoapHeader::~SoapHeader()
{
	//deletion of Header Entries
	list<HeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();

	while(itCurrHeaderBlock != m_headerBlocks.end()) {		
		delete *itCurrHeaderBlock;
		itCurrHeaderBlock++;
	}

	m_headerBlocks.clear();

	//deletion of attributes
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		delete *itCurrAttribute;
		itCurrAttribute++;
	}

	m_attributes.clear();
}

void SoapHeader::addHeaderBlock(HeaderBlock* headerBlock)
{
	m_headerBlocks.push_back(headerBlock);
}

int SoapHeader::serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion)
{	
	int iStatus= SUCCESS;

	do {
		
		pSZ.Serialize("<", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER], NULL);

		iStatus= serializeNamespaceDecl(pSZ);
		iStatus= serializeAttributes(pSZ);

		if(iStatus==FAIL) {
			break;
		}
		
		pSZ.Serialize(">", NULL);

		list<HeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();

		while(itCurrHeaderBlock != m_headerBlocks.end()) {
			iStatus= (*itCurrHeaderBlock)->serialize(pSZ);
			if(iStatus==FAIL) {
				break;
			}
			itCurrHeaderBlock++;			
		}

		if(iStatus==FAIL) {
			break;
		}
		
		pSZ.Serialize("</", gs_SoapEnvVersionsStruct[eSoapVersion].pchPrefix, ":", gs_SoapEnvVersionsStruct[eSoapVersion].pchWords[SKW_HEADER], ">", NULL);
		
	} while(0);

	return iStatus;

}

int SoapHeader::addAttribute(Attribute *pAttribute)
{
	m_attributes.push_back(pAttribute);

	return SUCCESS;
}


int SoapHeader::serializeAttributes(SoapSerializer& pSZ)
{
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		(*itCurrAttribute)->serialize(pSZ);
		itCurrAttribute++;		
	}	

	return SUCCESS;	
}

int SoapHeader::addNamespaceDecl(Attribute *pAttribute)
{
	m_namespaceDecls.push_back(pAttribute);

	return SUCCESS;
}

int SoapHeader::serializeNamespaceDecl(SoapSerializer& pSZ)
{
	list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

	while(itCurrNamespaceDecl != m_namespaceDecls.end()) {			

		(*itCurrNamespaceDecl)->serialize(pSZ);
		itCurrNamespaceDecl++;		
	}	

	return SUCCESS;
}

IHeaderBlock* SoapHeader::getHeaderBlock()
{
	list<HeaderBlock*>::iterator itCurrHeaderBlock= m_headerBlocks.begin();

	if(itCurrHeaderBlock != m_headerBlocks.end()) {			

		/*
		 *Actually a dynamic cast is not needed here. But it
		 * is done for safe side.
		 */
		return dynamic_cast<IHeaderBlock*>(*itCurrHeaderBlock);
	}

	return NULL;

}
