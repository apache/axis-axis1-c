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

// HeaderBlock.cpp: implementation of the HeaderBlock class.
//
//////////////////////////////////////////////////////////////////////

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <axis/soap/HeaderBlock.h>
#include <axis/soap/SoapSerializer.h>
#include <axis/common/GDefine.h>
#include <axis/soap/BasicNode.h>
#include <axis/soap/ComplexElement.h>
#include <axis/soap/CharacterElement.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HeaderBlock::HeaderBlock()
{

}

HeaderBlock::~HeaderBlock()
{
	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		delete (*itCurrAttribute);
		itCurrAttribute++;		
	}
	
	m_attributes.clear();
}

void HeaderBlock::setLocalName(const AxisChar* localname)
{
	m_localname= localname;
}

void HeaderBlock::setPrefix(const AxisChar* prefix)
{
	m_prefix= prefix;
}

void HeaderBlock::setUri(const AxisChar* uri)
{
	m_uri= uri;
}

void HeaderBlock::addAttribute(Attribute* attr)
{
	m_attributes.push_back(attr);
}

void HeaderBlock::setValue(const AxisChar* value)
{
	//m_value= value;

	/* I think that now this method is not needed, roshan */
}

int HeaderBlock::serialize(SoapSerializer& pSZ)
{
	/*
	 *In the code we don't look whether the m_prefix is available or
	 *	not. Instead directly insert it. The reason is that the SOAP
	 *  1.1 spec says that "All immediate child elements of the SOAP 
	 *  Header element MUST be namespace-qualified".
	 */

	int iStatus= AXIS_SUCCESS;

	list<AxisChar*> lstTmpNameSpaceStack;
	bool blnIsNewNamespace = false;

	do {
		/*
		TO DO: ReWrite the following logic to deal with name spaces
		*/

		pSZ.Serialize("<", NULL);

		if(m_prefix.length() == 0) {
			m_prefix = pSZ.GetNamespacePrefix(m_uri.c_str(), blnIsNewNamespace);
			if (blnIsNewNamespace) {
				lstTmpNameSpaceStack.push_back((AxisChar*)m_uri.c_str());
			}
		}

		pSZ.Serialize(m_prefix.c_str(), ":", m_localname.c_str(),
			" xmlns:", m_prefix.c_str(), "=\"", m_uri.c_str(), "\"", NULL);

		iStatus= attrSerialize(pSZ, lstTmpNameSpaceStack);
		if(iStatus==AXIS_FAIL) {
			break;
		}

		iStatus= serializeNamespaceDecl(pSZ);
		if(iStatus==AXIS_FAIL) {
			break;
		}
		
		pSZ.Serialize(">", NULL);

		iStatus= serializeChildren(pSZ, lstTmpNameSpaceStack);
		if(iStatus==AXIS_FAIL) {
			break;
		}

		pSZ.Serialize("</", m_prefix.c_str(), ":", m_localname.c_str(), ">", NULL);

		/*
		 *Removing the namespace list of this headerblock from the stack.
		 */
		list<AxisChar*>::iterator itCurrentNamespace = lstTmpNameSpaceStack.begin();
		while (itCurrentNamespace != lstTmpNameSpaceStack.end()) {
			pSZ.RemoveNamespacePrefix(*itCurrentNamespace);
			itCurrentNamespace++;
		}
			
	} while(0);

	return iStatus;
}

int HeaderBlock::attrSerialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	int iStatus= AXIS_SUCCESS;

	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		iStatus= (*itCurrAttribute)->serialize(pSZ, lstTmpNameSpaceStack);
		if(iStatus==AXIS_FAIL) {
			break;
		}
		itCurrAttribute++;
	}

	return iStatus;
}

/*
comm on 10/7/2003 6.00pm
int HeaderBlock::attrSerialize(string& sSerialized)
{
	int iStatus= AXIS_SUCCESS;

	list<Attribute*>::iterator itCurrAttribute= m_attributes.begin();

	while(itCurrAttribute != m_attributes.end()) {		

		iStatus= (*itCurrAttribute)->serialize(sSerialized);
		if(iStatus==AXIS_FAIL) {
			break;
		}
		itCurrAttribute++;		
	}	

	return iStatus;
}
*/

bool HeaderBlock::isSerializable()
{
	//bool blnStatus= true;

	//return blnStatus;

	bool bStatus= true;	

	if(m_localname.length() == 0) {
		bStatus= false;
	} else {
		if(m_prefix.length() == 0) {
			if(m_uri.length() != 0) {
				bStatus= false;
			}
		} else {
			if(m_uri.length() == 0) {
				bStatus= false;
			}
		}
	}

	return bStatus;
}

int HeaderBlock::addChild(BasicNode *pBasicNode)
{
	m_children.push_back(pBasicNode);

	return AXIS_SUCCESS;
}

int HeaderBlock::serializeChildren(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack)
{
	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	while(itCurrBasicNode != m_children.end()) {
		if ((*itCurrBasicNode)->getNodeType() == ELEMENT_NODE) {
			(*itCurrBasicNode)->serialize(pSZ, lstTmpNameSpaceStack);
		} else {
			/* for CHARACTER_NODE types */
			(*itCurrBasicNode)->serialize(pSZ);
		}
		itCurrBasicNode++;
	}

	return AXIS_SUCCESS;
}

/*
comm on 10/7/2003 6.00pm
int HeaderBlock::serializeChildren(string &sSerialized)
{
	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	while(itCurrBasicNode != m_children.end()) {		
		(*itCurrBasicNode)->serialize(sSerialized);
		itCurrBasicNode++;		
	}	

	return AXIS_SUCCESS;
}
*/

int HeaderBlock::addNamespaceDecl(Attribute *pAttribute)
{
	m_namespaceDecls.push_back(pAttribute);

	return AXIS_SUCCESS;
}

int HeaderBlock::serializeNamespaceDecl(SoapSerializer &pSZ)
{
	list<Attribute*>::iterator itCurrNamespaceDecl= m_namespaceDecls.begin();

	while(itCurrNamespaceDecl != m_namespaceDecls.end()) {		
		(*itCurrNamespaceDecl)->serialize(pSZ);
		itCurrNamespaceDecl++;		
	}	

	return AXIS_SUCCESS;
}

BasicNode* HeaderBlock::getFirstChild()
{
	list<BasicNode*>::iterator itCurrBasicNode= m_children.begin();

	if (itCurrBasicNode != m_children.end()) {		
		return (*itCurrBasicNode);
	}	

	return NULL;
}

BasicNode* HeaderBlock::createChild(NODE_TYPE eNODE_TYPE)
{
	BasicNode* pBasicNode = NULL;

	if(eNODE_TYPE==CHARACTER_NODE) {
		pBasicNode = new CharacterElement();
	} else if (eNODE_TYPE==ELEMENT_NODE) {
		//do some thing appropriate
	}

	return pBasicNode;
}

#ifdef UNIT_TESTING_BUILD
int HeaderBlock::initializeForTesting()
{
	setPrefix("m");
	setLocalName("reservation");
	setUri("http://travelcompany.example.org/reservation");

	Attribute* pAttribute2 = new Attribute();
	pAttribute2->setPrefix("SOAP-ENV");
	pAttribute2->setLocalName("role");
	pAttribute2->setValue("http://www.w3.org/2003/05/soap-envelope/role/next");

	Attribute* pAttribute3 = new Attribute();
	pAttribute3->setPrefix("SOAP-ENV");
	pAttribute3->setLocalName("mustUnderstand");
	pAttribute3->setValue("true");

	addAttribute(pAttribute2);
	addAttribute(pAttribute3);

	ComplexElement* pComplexElement = new ComplexElement();
	pComplexElement->setPrefix("m");
	pComplexElement->setLocalName("reference");
	pComplexElement->addChild(new CharacterElement("abcdefgh"));

	ComplexElement* pComplexElement2 = new ComplexElement();
	pComplexElement2->setPrefix("m");
	pComplexElement2->setLocalName("dateAndTime");
	pComplexElement2->addChild(new CharacterElement("2001-11-29T13:20:00.000-05:00"));

	addChild(pComplexElement);
	addChild(pComplexElement2);

	return AXIS_SUCCESS;	
}
#endif

bool HeaderBlock::operator ==( const HeaderBlock &objHeaderBlock)
{
	/*
	 *TODO : the logic
	 */
	return true;
}