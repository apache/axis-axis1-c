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

#include "../xml/Event.h"
#include "../xml/SimpleAttribute.h"
#include "../xml/StartElement.h"
using namespace axisxml;

#include "SoapParserExpat.h"

SoapParserExpat::SoapParserExpat()
{
	m_pLastEvent = NULL;
	m_Parser = XML_ParserCreateNS(NULL, NAMESPACESEPARATOR);
	m_nTransportStatus = TRANSPORT_IN_PROGRESS;
}

SoapParserExpat::~SoapParserExpat()
{
	if (m_pLastEvent) delete m_pLastEvent;
	XML_ParserFree(m_Parser);
}

void SoapParserExpat::startElement(const XMLCh *qname,const XMLCh **attrs)
{
	QName qn;
	qn.SplitQNameString(qname, NAMESPACESEPARATOR);
	StartElement *pSE = new StartElement();
	pSE->m_NameOrValue = qn.localname;
	pSE->m_Namespace  = qn.uri ? qn.uri : "";
	qn.MergeQNameString(NAMESPACESEPARATOR);
	Attribute *pAt = NULL;
	for (int i = 0; attrs[i]; i += 2) 
	{
		qn.SplitQNameString(attrs[i], NAMESPACESEPARATOR);
		pAt = new Attribute();
		pAt->m_Name = qn.localname;
		pAt->m_Namespace = qn.uri ? qn.uri : "";
		qn.MergeQNameString(NAMESPACESEPARATOR);
		pAt->m_Value = attrs[i+1];
		pSE->m_Attributes.push_back(pAt);
	}
	m_Events.push(pSE);
}

void SoapParserExpat::endElement(const XMLCh *qname)
{
	QName qn;
	qn.SplitQNameString(qname, NAMESPACESEPARATOR);
	EndElement *pEE = new EndElement();
	pEE->m_NameOrValue = qn.localname;
	pEE->m_Namespace  = qn.uri ? qn.uri : "";
	m_Events.push(pEE);
	qn.MergeQNameString(NAMESPACESEPARATOR);
}

void  SoapParserExpat::characters(const XMLCh *chars, int length)
{

	XMLCh* pTemp = const_cast<XMLCh*>(chars);
	XMLCh replacedchar = pTemp[length]; //copy and keep existing char at length position
	pTemp[length] = '\0'; //putting nul charactor so that chars can be used safely
	Event* pLastEvent;
	if (!m_Events.empty()) 
	{
		pLastEvent = m_Events.back();
		if (CHARACTER_ELEMENT == pLastEvent->GetType()) /* continuing same character node */
		{
			pLastEvent->m_NameOrValue += pTemp;
			pTemp[length] = replacedchar; //put back the character that was there before putting nul charactor
			return;
		}
	}
	pLastEvent = new CharacterElement();
	pLastEvent->m_NameOrValue = pTemp;
	m_Events.push(pLastEvent);
	pTemp[length] = replacedchar; //put back the character that was there before putting nul charactor
}

void SoapParserExpat::startPrefixMapping(const XMLCh *prefix, const XMLCh *uri)
{
	if (prefix && uri)
	{
		StartPrefix* pEvent = new StartPrefix();
		pEvent->m_NameOrValue = prefix;
		pEvent->m_Namespace = uri;
		m_Events.push(pEvent);
	}
}

void SoapParserExpat::endPrefixMapping(const XMLCh *prefix)
{
	if (!prefix) return;
	EndPrefix* pEvent = new EndPrefix();
	pEvent->m_NameOrValue = prefix;
	m_Events.push(pEvent);
}

const XMLCh* SoapParserExpat::GetNS4Prefix(const XMLCh* prefix)
{
	if (m_NsStack.find(prefix) != m_NsStack.end())
	{
		return m_NsStack[prefix].c_str();
	}
	return NULL;
}

/**
 * This method returning NULL means that there is something wrong with the stream
 * and hence parsing should be finished or aborted.
 */
const AnyElement* SoapParserExpat::Next()
{
	int nStatus = TRANSPORT_IN_PROGRESS;
	if (m_pLastEvent)
	{
		delete m_pLastEvent;
		m_pLastEvent = NULL;
	}
	do
	{
		if (m_Events.empty())
		{
			nStatus = ParseNext();
			if (TRANSPORT_FAILED == nStatus) return NULL;
			if (AXIS_FAIL == m_nStatus) return NULL;
		}

		if (!m_Events.empty())
		{
			m_pLastEvent = m_Events.front();
			XML_NODE_TYPE type = m_pLastEvent->GetType();
			m_Events.pop();
			if ((CHARACTER_ELEMENT == type) && m_Events.empty()) /* current character element may not be parsed completly */
			{
				m_Events.push(m_pLastEvent);
				nStatus = ParseNext();
				if (TRANSPORT_FAILED == nStatus) return NULL;
			}
			else
			{
				int i = 0;
				switch(type)
				{
				case START_ELEMENT:
					{
						for (list<Attribute*>::iterator it = ((StartElement*)m_pLastEvent)->m_Attributes.begin()
							; it != ((StartElement*)m_pLastEvent)->m_Attributes.end(); it++)
						{
							m_Element.m_pchAttributes[i+0] = (*it)->m_Name.c_str();
							m_Element.m_pchAttributes[i+1] = (*it)->m_Namespace.c_str();
							m_Element.m_pchAttributes[i+2] = (*it)->m_Value.c_str();
							i+=3;
						}
						m_Element.m_pchAttributes[i+0] = NULL;
						m_Element.m_pchAttributes[i+1] = NULL;
						m_Element.m_pchAttributes[i+2] = NULL;
					}
					/* no break */
				case END_ELEMENT:
					m_Element.m_pchNamespace = ((StartElement*)m_pLastEvent)->m_Namespace.c_str();
					/* no break */
				case CHARACTER_ELEMENT:
					m_Element.m_pchNameOrValue = m_pLastEvent->m_NameOrValue.c_str();
					m_Element.m_type = type;
					return &m_Element;
				case START_PREFIX:
					m_NsStack[m_pLastEvent->m_NameOrValue] = ((StartPrefix*)m_pLastEvent)->m_Namespace; //I think the same prifix cannot repeat ???
					delete m_pLastEvent;
					m_pLastEvent = NULL;
					break;
				case END_PREFIX:
					m_NsStack.erase(m_pLastEvent->m_NameOrValue); //I think the same prifix cannot repeat ??? */
					delete m_pLastEvent;
					m_pLastEvent = NULL;
					break;
				}
			}
		}
	} while (TRANSPORT_FAILED != nStatus);
	return NULL;
}

int SoapParserExpat::ParseNext()
{
	int nChars = 0;
	m_nTransportStatus = m_pInputStream->transport.pGetFunct(&m_pCurrentBuffer, &nChars, m_pInputStream);
	if ((nChars > 0) && m_pCurrentBuffer) /* there can be a buffer or not */
	{
		if (XML_STATUS_ERROR == XML_Parse(m_Parser, m_pCurrentBuffer, nChars, false))
			m_nStatus = AXIS_FAIL;
		m_pInputStream->transport.pRelBufFunct(m_pCurrentBuffer, m_pInputStream);
	}
	if (TRANSPORT_FAILED == m_nTransportStatus) XML_Parse(m_Parser, NULL, 0, true); /* end of parsing */
	return m_nTransportStatus;
}

int SoapParserExpat::GetStatus()
{
	m_nStatus = AXIS_SUCCESS; /*TODO:Check if an error occured in expat */
	return m_nStatus;
}

/**
 * Resets SoapParserExpat object 
 */
int SoapParserExpat::Init()
{
	XML_ParserReset(m_Parser, NULL);
	XML_SetUserData(m_Parser, this);
	XML_SetNamespaceDeclHandler(m_Parser, s_startPrefixMapping, s_endPrefixMapping);
	XML_SetElementHandler(m_Parser, s_startElement, s_endElement);
	XML_SetCharacterDataHandler(m_Parser, s_characters);
	m_nStatus = AXIS_SUCCESS; /*TODO:Check if an error occured in expat */
	m_NsStack.clear(); /* this will also delete any strings there */
	if (m_pLastEvent) delete m_pLastEvent;
	while (!m_Events.empty())
	{
		m_pLastEvent = m_Events.front();
		m_Events.pop();
		delete m_pLastEvent;
	}
	m_pLastEvent = NULL;
	m_nTransportStatus = TRANSPORT_IN_PROGRESS;
	return m_nStatus;
}

int SoapParserExpat::SetInputStream(const Ax_soapstream* pInputStream)
{
	m_pInputStream = pInputStream;
	return AXIS_SUCCESS;
}
