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

// SoapMethod.cpp: implementation of the SoapMethod class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/SoapMethod.h>
#include <axis/soap/Attribute.h>
#include <axis/common/GDefine.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SoapMethod::SoapMethod()
{
}

SoapMethod::~SoapMethod()
{
	list<Param*>::iterator itParam;
	for (list<Attribute*>::iterator it = m_attributes.begin(); it != m_attributes.end(); it++)
	{
		delete (*it);
	}
	for (itParam = m_OutputParams.begin(); itParam != m_OutputParams.end(); itParam++)
	{
		delete (*itParam);
	}
	m_OutputParams.clear();
}

void SoapMethod::setPrefix(const AxisChar* prefix)
{
	m_strPrefix = prefix;
}

void SoapMethod::setLocalName(const AxisChar* localname)
{
	m_strLocalname = localname;
}

void SoapMethod::setUri(const AxisChar* uri)
{
	m_strUri = uri;
}

void SoapMethod::AddOutputParam(Param *param)
{
	if (param)
	{
		m_OutputParams.push_back(param);
	}
}

/*
 *This method return AXIS_SUCCESS if it serialize the SoapMethod successfully.
 * If not it returns AXIS_FAIL. The caller of this method has to deal in a 
 * appropriate manner after calling this method.
 */
int SoapMethod::serialize(SoapSerializer& pSZ)
{	
	int iStatus= AXIS_SUCCESS;

	do {
		if(isSerializable()) {
					
			pSZ << "<" << m_strPrefix.c_str() << ":" << m_strLocalname.c_str() << " xmlns:" << m_strPrefix.c_str()
				<< "=\"" << m_strUri.c_str() << "\"";

			iStatus= serializeAttributes(pSZ);
			if(iStatus==AXIS_FAIL) {
				break;
			}
			
			pSZ << ">";

			iStatus= serializeOutputParam(pSZ);
			if(iStatus==AXIS_FAIL) {
				break;
			}
			
			pSZ << "</";

			if(m_strPrefix.length() != 0) {					
				pSZ<< m_strPrefix.c_str() << ":";
			}
			
			pSZ << m_strLocalname.c_str() << ">";

			iStatus= AXIS_SUCCESS;
		} else {
			iStatus= AXIS_FAIL;
		}
	} while(0);
			
	return iStatus;
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serialize(string& sSerialized)
{	
	
	int iStatus= AXIS_SUCCESS;

	do {
		if(isSerializable()) {

			sSerialized+= "<" + m_strPrefix+ ":"+ m_strLocalname+ " xmlns:"+ m_strPrefix+ 
				"=\""+ m_strUri+ "\"";
			
//			if(m_strPrefix.length() != 0) {
//				sSerialized+= m_strPrefix+ ":";
//			}

//			sSerialized+= m_strLocalname;

//			if(m_strPrefix.length() != 0) {
//				sSerialized+= " xmlns:"+ m_strPrefix+ "=\""+ m_strUri+ "\"";
//			}

			iStatus= serializeAttributes(sSerialized);
			if(iStatus==AXIS_FAIL) {
				break;
			}

			sSerialized+= ">";

			iStatus= serializeOutputParam(sSerialized);
			if(iStatus==AXIS_FAIL) {
				break;
			}

			sSerialized+= "</";

			if(m_strPrefix.length() != 0) {
				sSerialized+= m_strPrefix+ ":";			
			}

			sSerialized+= m_strLocalname+ ">"+ "\n";

			iStatus= AXIS_SUCCESS;
		} else {
			iStatus= AXIS_FAIL;
		}
	} while(0);
			
	return iStatus;
}
*/

int SoapMethod::serializeOutputParam(SoapSerializer& pSZ)
{	
	int nStatus;
	for (list<Param*>::iterator it = m_OutputParams.begin(); it != m_OutputParams.end(); it++)
	{
		if (AXIS_SUCCESS != (nStatus = (*it)->serialize(pSZ)))
		{
			return nStatus;
		}
	}
	return AXIS_SUCCESS;
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serializeOutputParam(string& sSerialized)
{	
	return m_pOutputParam->serialize(sSerialized);
}
*/

const AxisChar* SoapMethod::getMethodName()
{
	return m_strLocalname.c_str();
}

bool SoapMethod::isSerializable()
{
	bool bStatus= true;	

	//checking whether namespace qualified, if not return AXIS_FAIL
	do {
		if(m_strPrefix.length() == 0) {			
			bStatus= false;		
			break;
		} else if(m_strUri.length() == 0) {
			bStatus= false;
			break;
		}
	} while(0);

	return bStatus;
}

int SoapMethod::addAttribute(Attribute *pAttribute)
{
	m_attributes.push_back(pAttribute);

	return AXIS_SUCCESS;
}

int SoapMethod::serializeAttributes(SoapSerializer& pSZ)
{
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		(*itCurrAttribute)->serialize(pSZ);
		itCurrAttribute++;		
	}	

	return AXIS_SUCCESS;	
}

/*
comm on 11/7/2003 9.10am
int SoapMethod::serializeAttributes(string &sSerialized)
{
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		
		(*itCurrAttribute)->serialize(sSerialized);
		itCurrAttribute++;		
	}	

	return AXIS_SUCCESS;	
}
*/
