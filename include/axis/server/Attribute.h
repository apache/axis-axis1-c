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

// Attribute.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTRIBUTE_H__10ABD25E_AF15_4DE7_AA27_6AB96102087C__INCLUDED_)
#define AFX_ATTRIBUTE_H__10ABD25E_AF15_4DE7_AA27_6AB96102087C__INCLUDED_

#include <string>
#include <list>
#include "../common/GDefine.h"

using namespace std;

class SoapSerializer;
/**
    @class Attribute
    @brief interface for the Attribute class.




    @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
*/
class Attribute  
{
private:	
	bool isSerializable() const;
	AxisString m_localname;
	AxisString m_prefix;
	AxisString m_uri;
	AxisString m_value;
	//string m_strAttrSerialized;
public:		
#ifdef UNIT_TESTING_BUILD
	int initializeForTesting();
#endif
	int serialize(SoapSerializer& pSZ) const;
	int serialize(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
	//int serialize(string&);
	Attribute();	
	Attribute(const AxisChar* localname, const AxisChar* prefix, const AxisChar* uri, const AxisChar* value);
	virtual ~Attribute();

	void setValue(const AxisChar* value);
	void setUri(const AxisChar* uri);
	void setPrefix(const AxisChar* prefix);
	void setLocalName(const AxisChar* localname);	
};

#endif // !defined(AFX_ATTRIBUTE_H__10ABD25E_AF15_4DE7_AA27_6AB96102087C__INCLUDED_)
