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

#include "ComplexElement.h"
#include <axis/server/SoapSerializer.h>
#include <axis/server/GDefine.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ComplexElement::ComplexElement()
{
	m_pachPrefix = '\0';
	m_pachLocalName = '\0';
	m_pachURI = '\0';

	m_iNodeType= ELEMENT_NODE;
	iNoOfChildren = 0;
}

ComplexElement::ComplexElement(AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri)
{
	m_pachLocalName = (AxisChar*) malloc(strlen(pachLocalName)+1);
	strcpy(m_pachLocalName, pachLocalName);
	m_pachPrefix = (AxisChar*) malloc(strlen(pachPrefix)+1);
	strcpy(m_pachPrefix, pachPrefix);
	m_pachURI = (AxisChar*) malloc(strlen(pachUri)+1);
	strcpy(m_pachURI, pachUri);
}


ComplexElement::~ComplexElement()
{
	free(m_pachPrefix);
	free(m_pachLocalName);
	free(m_pachURI);

	/*
	 *Clear the children
	 */
	list<BasicNode*>::iterator itCurrChild= m_children.begin();
	while(itCurrChild != m_children.end()) {		
		delete (*itCurrChild);
		itCurrChild++;		
	}
	m_children.clear();
}

int ComplexElement::setPrefix(const AxisChar* pachPrefix)
{
	m_pachPrefix = (AxisChar*) malloc(strlen(pachPrefix)+1);
	strcpy(m_pachPrefix, pachPrefix);
	return AXIS_SUCCESS;
}

int ComplexElement::setLocalName(const AxisChar* pachLocalName)
{
	m_pachLocalName = (AxisChar*) malloc(strlen(pachLocalName)+1);
	strcpy(m_pachLocalName, pachLocalName);
	return AXIS_SUCCESS;
}

int ComplexElement::addChild(BasicNode *pBasicNode)
{
	m_children.push_back(pBasicNode);
	iNoOfChildren++;
	return AXIS_SUCCESS;
}

int ComplexElement::serialize(SoapSerializer& pSZ)
{
	int iStatus= AXIS_SUCCESS;
	do {
		if(isSerializable()) 
		{	
			pSZ.Serialize("<", NULL);	
			if(strlen(m_pachPrefix) != 0) {				
				pSZ.Serialize(m_pachPrefix, ":", NULL);
			}
			pSZ.Serialize(m_pachLocalName, NULL);
			if((strlen(m_pachPrefix) != 0) && (strlen(m_pachURI) != 0)) {
				pSZ.Serialize(" xmlns:", m_pachPrefix, "=\"", m_pachURI, "\"", NULL);
			}
			pSZ.Serialize(">", NULL);
			iStatus= serializeChildren(pSZ);
			if(iStatus==AXIS_FAIL) {
				break;
			}
			pSZ.Serialize("</", NULL);
			if(strlen(m_pachPrefix) != 0) {				
				pSZ.Serialize(m_pachPrefix, ":", NULL);
			}
			pSZ.Serialize(m_pachLocalName, ">", NULL);
			iStatus= AXIS_SUCCESS;
		} 
		else
		{
			iStatus= AXIS_FAIL;
		}
	} while(0);	
	return iStatus;
}

int ComplexElement::serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	int iStatus= AXIS_SUCCESS;
	do {
		if(isSerializable()) 
		{	
			bool blnIsNewNamespace = false;

			pSZ.Serialize("<", NULL);	
			if( (m_pachPrefix != NULL) && (strlen(m_pachPrefix) != 0)) {				
				pSZ.Serialize(m_pachPrefix, ":", NULL);
			} else if ( (m_pachURI != NULL) && (strlen(m_pachURI) != 0)) {
				const AxisChar* pachTmp = pSZ.GetNamespacePrefix(m_pachURI, blnIsNewNamespace);
				m_pachPrefix = (AxisChar*) malloc(strlen(pachTmp)+1);
				strcpy(m_pachPrefix , pachTmp);

				if (blnIsNewNamespace) {
					lstTmpNameSpaceStack.push_back(m_pachURI);
				}
				pSZ.Serialize(m_pachPrefix, ":", NULL);
			}

			pSZ.Serialize(m_pachLocalName, NULL);

			if(((m_pachPrefix != NULL) && (strlen(m_pachPrefix) != 0)) && 
					( (m_pachURI != NULL) && (strlen(m_pachURI) != 0)) && 
					(blnIsNewNamespace)) {
				pSZ.Serialize(" xmlns:", m_pachPrefix, "=\"", m_pachURI, "\"", NULL);
			}
			pSZ.Serialize(">", NULL);

			iStatus= serializeChildren(pSZ, lstTmpNameSpaceStack);
			if(iStatus==AXIS_FAIL) {
				break;
			}
			pSZ.Serialize("</", NULL);
			if((m_pachPrefix!=NULL) && (strlen(m_pachPrefix) != 0)) {				
				pSZ.Serialize(m_pachPrefix, ":", NULL);
			}
			pSZ.Serialize(m_pachLocalName, ">", NULL);
			iStatus= AXIS_SUCCESS;
		} 
		else
		{
			iStatus= AXIS_FAIL;
		}
	} while(0);	
	return iStatus;
}

bool ComplexElement::isSerializable()
{
	bool bStatus= true;

	do {
		if(strlen(m_pachLocalName) == 0) {
			bStatus= false;
			break;
		}
	}while(0);

	return bStatus;
}

int ComplexElement::setURI(const AxisChar* pachURI)
{
	m_pachURI = (AxisChar*) malloc(strlen(pachURI)+1);
	strcpy(m_pachURI, pachURI);
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

int ComplexElement::serializeChildren(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	while(itCurrBasicNode != m_children.end()) {
		if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE) {
			(*itCurrBasicNode)->serialize(pSZ, lstTmpNameSpaceStack);	
		} else {
			/* for CHARACTER_NODE */
			(*itCurrBasicNode)->serialize(pSZ);
		}
		itCurrBasicNode++;		
	}	

	return AXIS_SUCCESS;
}

NODE_TYPE ComplexElement::getNodeType() const
{
	return m_iNodeType;
}

const BasicNode* ComplexElement::getFirstChild() const
{
	list<BasicNode*>::const_iterator itCurrChild= m_children.begin();

	if (itCurrChild != m_children.end()) {		
		return (*itCurrChild);
	}	

	return NULL;
}

const BasicNode* ComplexElement::getLastChild() const
{
	list<BasicNode*>::const_reverse_iterator ritCurrChild= m_children.rbegin();

	if (ritCurrChild != m_children.rend()) {		
		return (*ritCurrChild);
	}	

	return NULL;
}

const BasicNode* ComplexElement::getChild(int iChildPosition) const
{
	if (iChildPosition > iNoOfChildren) {
		return NULL;
	} else {
		list<BasicNode*>::const_iterator itCurrChild= m_children.begin();
		/*The following is done since the previous line already takes the iterator one step forward */
		iChildPosition--;

		/*Takes the iterator to the relavent positon*/
		for (int i=0; i<iChildPosition; i++) {
			itCurrChild++;
		}

		if (itCurrChild != m_children.end()) {
			return *itCurrChild;
		} else {
			return NULL;
		}
	}
}

int ComplexElement::getNoOfChildren()
{
	return iNoOfChildren;
}
