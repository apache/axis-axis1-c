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
 */

// ComplexElement.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEXELEMENT_H__558543B0_B076_404C_A7FE_830E13C1785A__INCLUDED_)
#define AFX_COMPLEXELEMENT_H__558543B0_B076_404C_A7FE_830E13C1785A__INCLUDED_

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <list>
#include <axis/soap/BasicNode.h>

using namespace std;
/**
    @class ComplexElement
    @brief interface for the ComplexElement class.


    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class ComplexElement : public BasicNode
{
public:
	ComplexElement(AxisChar* pachLocalName, AxisChar* pachPrefix, AxisChar* pachUri);
	/**
	 * Returns the number of child elements of this ComplexElement.
	 * @return The number of child elements of this ComplexElement.
	 */
	int getNoOfChildren();
	const BasicNode* getChild(int iChildPosition) const;
	const BasicNode* getLastChild() const;
	const BasicNode* getFirstChild() const;
	NODE_TYPE getNodeType() const;
	int setURI(const AxisChar* pachURI);
	int addChild(BasicNode* pBasicNode);
	int setLocalName(const AxisChar* pachLocalName);
	int setPrefix(const AxisChar* pachPrefix);
	int serialize(SoapSerializer& pSZ);
	int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
	ComplexElement();
	virtual ~ComplexElement();

	/**
	 * This method is overridden to do nothing always because this is 
	 *  a Complex Element. Instead of using this method, a user of a 
	 *  ComplexElement must get the childeren of this ComplexElement and
	 *  has to traverse through the childrean in a appropriate manner
	 *  in order to set there values.
	 *  A user of a ComplexElement should not use this method.
	 * @param
	 * @return Always return fail (AXIS_FAIL).
	 */
	int setValue(const AxisChar* pachValue) {return AXIS_FAIL;}

	/**
	 * This method is overridden to return NULL always because this is 
	 *  a Complex Element. Instead of using this method, a user of a 
	 *  ComplexElement must get the childeren of this ComplexElement and
	 *  has to traverse through the childrean in a appropriate manner
	 *  in order to get there values.
	 *  A user of a ComplexElement should not use this method.
	 * @param
	 * @return Always return NULL to indicate unsuccessful.
	 */
	const AxisChar* getValue() const {return NULL;}

private:
	int iNoOfChildren;
	int serializeChildren(SoapSerializer& pSZ);
	int serializeChildren(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
	bool isSerializable();
	list<BasicNode*> m_children;
	AxisChar* m_pachPrefix;
	AxisChar* m_pachLocalName;
	AxisChar* m_pachURI;
};

#endif // !defined(AFX_COMPLEXELEMENT_H__558543B0_B076_404C_A7FE_830E13C1785A__INCLUDED_)
