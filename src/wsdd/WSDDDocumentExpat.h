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
#ifdef WIN32
#pragma warning(disable : 4786)
#endif

#if !defined(__WSDDDOCUMENTEXPAT_H_INCLUDED__)
#define __WSDDDOCUMENTEXPAT_H_INCLUDED__

#include "WSDDDocument.h"
#include <expat/expat.h>
#include <string>
#include <map>

using namespace std;

/**
    @class WSDDDocumentExpat
    @brief
    @author sanjaya sinharage(sanjaya@opensource.lk)
    @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
*/
class WSDDDocumentExpat : public WSDDDocument
{
private:
	void ProcessAttributes(WSDDLevels ElementType, const XML_Ch **attrs);
	void GetParameters(WSDDLevels ElementType, const XML_Ch **attrs);
	void AddAllowedRolesToService(const AxisXMLCh* value);
	void AddAllowedMethodsToService(const AxisXMLCh* value);
	int ParseDocument(const AxisChar* sWSDD);

public:
	WSDDDocumentExpat(map<AxisString, int>* pLibNameIdMap);
	~WSDDDocumentExpat();
	int GetDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);
	int UpdateDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);

	void startElement(const XML_Ch *qname,const XML_Ch **attrs);
	void endElement(const XML_Ch *qname);
	void characters(const XML_Ch *chars,int length);
	void startPrefixMapping(const XML_Ch *prefix, const XML_Ch *uri);
	void endPrefixMapping(const XML_Ch *prefix);

	inline static void XMLCALL s_startElement(void* p, const XML_Ch *qname,const XML_Ch **attrs)
	{((WSDDDocumentExpat*)p)->startElement(qname,attrs);};
	inline static void XMLCALL s_endElement(void* p, const XML_Ch *qname)
	{((WSDDDocumentExpat*)p)->endElement(qname);};
	inline static void XMLCALL s_characters(void* p, const XML_Ch *chars,int length)
	{((WSDDDocumentExpat*)p)->characters(chars,length);};
	inline static void XMLCALL s_startPrefixMapping(void* p, const XML_Ch *prefix, const XML_Ch *uri)
	{((WSDDDocumentExpat*)p)->startPrefixMapping(prefix, uri);};
	inline static void XMLCALL s_endPrefixMapping(void* p, const XML_Ch *prefix)
	{((WSDDDocumentExpat*)p)->endPrefixMapping(prefix);};
};

#endif //__WSDDDOCUMENTEXPAT_H_INCLUDED__
