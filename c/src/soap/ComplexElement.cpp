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

// ComplexElement.cpp: implementation of the ComplexElement class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/soap/ComplexElement.h>
#include <axis/soap/SoapSerializer.h>
#include <axis/common/GDefine.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ComplexElement::ComplexElement()
{
	m_iNodeType= ELEMENT_NODE;
}

ComplexElement::~ComplexElement()
{

}

int ComplexElement::setPrefix(const AxisChar* sPrefix)
{
	m_sPrefix= sPrefix;
	return AXIS_SUCCESS;
}

int ComplexElement::setLocalName(const AxisChar* sLocalName)
{
	m_sLocalName= sLocalName;
	return AXIS_SUCCESS;
}

int ComplexElement::addChild(BasicNode *pBasicNode)
{
	m_children.push_back(pBasicNode);
	return AXIS_SUCCESS;
}

int ComplexElement::serialize(SoapSerializer& pSZ)
{
	int iStatus= AXIS_SUCCESS;
	do {
		if(isSerializable()) 
		{	
			pSZ << "<";	
			if(m_sPrefix.length() != 0) {				
				pSZ<< m_sPrefix.c_str() << ":";
			}
			pSZ<< m_sLocalName.c_str();
			if((m_sPrefix.length() != 0) && (m_sURI.length() != 0)) {
				pSZ<< " xmlns:" << m_sPrefix.c_str() << "=\"" << m_sURI.c_str() << "\"";
			}
			pSZ<< ">";
			iStatus= serializeChildren(pSZ);
			if(iStatus==AXIS_FAIL) {
				break;
			}
			pSZ<< "</";
			if(m_sPrefix.length() != 0) {				
				pSZ<< m_sPrefix.c_str() << ":";
			}
			pSZ<< m_sLocalName.c_str() << ">";
			iStatus= AXIS_SUCCESS;
		} 
		else
		{
			iStatus= AXIS_FAIL;
		}
	} while(0);	
	return iStatus;
}

/*
comm on 10/7/2003 6.20pm
int ComplexElement::serialize(string &sSerialized)
{
	int iStatus= AXIS_SUCCESS;

	do {
		if(isSerializable()) {

			sSerialized+= "<";
			
			if(m_sPrefix.length() != 0) {
				sSerialized+= m_sPrefix+ ":";
			}

			sSerialized+= m_sLocalName;						  

			if((m_sPrefix.length() != 0) && (m_sURI.length() != 0)) {
				sSerialized+= " xmlns:"+ m_sPrefix+ "=\""+ m_sURI+ "\"";
			}

			sSerialized+= ">";

			iStatus= serializeChildren(sSerialized);
			if(iStatus==AXIS_FAIL) {
				break;
			}

			sSerialized+= "</";

			if(m_sPrefix.length() != 0) {
				sSerialized+= m_sPrefix+ ":";			
			}

			sSerialized+= m_sLocalName+ ">"+ "\n";

			iStatus= AXIS_SUCCESS;
		} else {
			iStatus= AXIS_FAIL;
		}
	} while(0);
			
	return iStatus;
}
*/

bool ComplexElement::isSerializable()
{
	bool bStatus= true;

	do {
		if(m_sURI.length()!=0) {
			if(m_sPrefix.length()==0) {
				bStatus= false;
				break;
			}
		}

		if(m_sLocalName.length()==0) {
			bStatus= false;
			break;
		}
	}while(0);

	return bStatus;
}

int ComplexElement::setURI(const AxisChar* sURI)
{
	m_sURI= sURI;
	return AXIS_SUCCESS;
}

int ComplexElement::serializeChildren(SoapSerializer& pSZ)
{

	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	while(itCurrBasicNode != m_children.end()) {		
		(*itCurrBasicNode)->serialize(pSZ);
		itCurrBasicNode++;		
	}	

	return AXIS_SUCCESS;
}

/*
comm on 10/7/2003 6.20pm
int ComplexElement::serializeChildren(string &sSerialized)
{

	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	while(itCurrBasicNode != m_children.end()) {		
		(*itCurrBasicNode)->serialize(sSerialized);
		itCurrBasicNode++;		
	}	

	return AXIS_SUCCESS;
}
*/

NODE_TYPE ComplexElement::getNodeType()
{
	return m_iNodeType;
}

/*
 *This method is overridden to return a blank string always because this is 
 * a Complex Element. Instead of using this method, a user of a 
 * ComplexElement must get the childeren of this ComplexElement and
 * has to traverse through the childrean in a appropriate manner
 * in order to get there values.
 */
const AxisString& ComplexElement::getValue()
{
	return m_sValue;
}

/*
 *This method is overridden to do nothing always because this is 
 * a Complex Element. Instead of using this method, a user of a 
 * ComplexElement must get the childeren of this ComplexElement and
 * has to traverse through the childrean in a appropriate manner
 * in order to set there values.
 */
int ComplexElement::setValue(const AxisChar* sValue)
{
	return AXIS_SUCCESS;
}
