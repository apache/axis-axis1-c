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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__SoapParserExpat_H_INCLUDED__)
#define __SoapParserExpat_H_INCLUDED__

#include <expat/expat.h>
#include <axis/common/Packet.h>

#include "../xml/QName.h"
#include <axis/xml/AnyElement.h>
#include "../xml/Event.h"
#include <axis/xml/XMLParser.h>

#include <queue>
#include <map>
#include <string>

using namespace std;

class SoapParserExpat: public XMLParser
{
private:
	XML_Parser m_Parser;
	const Ax_soapstream* m_pInputStream;
	const char* m_pCurrentBuffer;
	axisxml::Event* m_pLastEvent;
	AnyElement m_Element;
	queue<axisxml::Event*> m_Events;
	map<AxisXMLString, AxisXMLString> m_NsStack;
	int m_nStatus;
	AXIS_TRANSPORT_STATUS m_nTransportStatus;
public:
	SoapParserExpat();
	~SoapParserExpat();
private:
	void startElement(const XMLCh *qname,const XMLCh **attrs);
	void endElement(const XMLCh *qname);
	void characters(const XMLCh *chars,int length);
	void startPrefixMapping(const XMLCh *prefix, const XMLCh *uri);
	void endPrefixMapping(const XMLCh *prefix);
	int ParseNext();

	inline static void XMLCALL s_startElement(void* p, const XMLCh *qname,const XMLCh **attrs)
	{((SoapParserExpat*)p)->startElement(qname,attrs);};
	inline static void XMLCALL s_endElement(void* p, const XMLCh *qname)
	{((SoapParserExpat*)p)->endElement(qname);};
	inline static void XMLCALL s_characters(void* p, const XMLCh *chars,int length)
	{((SoapParserExpat*)p)->characters(chars,length);};
	inline static void XMLCALL s_startPrefixMapping(void* p, const XMLCh *prefix, const XMLCh *uri)
	{((SoapParserExpat*)p)->startPrefixMapping(prefix, uri);};
	inline static void XMLCALL s_endPrefixMapping(void* p, const XMLCh *prefix)
	{((SoapParserExpat*)p)->endPrefixMapping(prefix);};

public:
	int SetInputStream(const Ax_soapstream* pInputStream);
	const Ax_soapstream* GetInputStream(){return m_pInputStream;};
	int Init();
	const XMLCh* GetNS4Prefix(const XMLCh* prefix);
	int GetStatus();
	const AnyElement* Next();
	AXIS_TRANSPORT_STATUS GetTransportStatus(){ return m_nTransportStatus;};
	void SetTransportStatus(AXIS_TRANSPORT_STATUS nStatus){ m_nTransportStatus = nStatus;};
};

#endif
