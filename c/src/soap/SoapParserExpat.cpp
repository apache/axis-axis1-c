/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include "../xml/Event.h"
#include "../xml/SimpleAttribute.h"
#include "../xml/StartElement.h"

#include "SoapParserExpat.h"

#define EXPAT_BUFFER_SIZE 1024

SoapParserExpat::SoapParserExpat()
{
    m_pLastEvent = NULL;
    m_Parser = XML_ParserCreateNS(NULL, NAMESPACESEPARATOR);
    m_nTransportStatus = TRANSPORT_IN_PROGRESS;
	m_pCurrentBuffer = 0;
}

SoapParserExpat::~SoapParserExpat()
{
    if (m_pLastEvent) delete m_pLastEvent;
    XML_ParserFree(m_Parser);
}

void SoapParserExpat::startElement(const XML_Ch *qname,const XML_Ch **attrs)
{
    QName qn;
    qn.splitQNameString(qname, NAMESPACESEPARATOR);
    StartElement *pSE = new StartElement();
    pSE->m_NameOrValue = qn.localname;
    pSE->m_Namespace  = qn.uri ? qn.uri : "";
    qn.mergeQNameString(NAMESPACESEPARATOR);
    SimpleAttribute *pAt = NULL;
    for (int i = 0; attrs[i]; i += 2) 
    {
        qn.splitQNameString(attrs[i], NAMESPACESEPARATOR);
        pAt = new SimpleAttribute();
        pAt->m_Name = qn.localname;
        pAt->m_Namespace = qn.uri ? qn.uri : "";
        qn.mergeQNameString(NAMESPACESEPARATOR);
        pAt->m_Value = attrs[i+1];
        pSE->m_Attributes.push_back(pAt);
    }
    m_Events.push(pSE);
}

void SoapParserExpat::endElement(const XML_Ch *qname)
{
    QName qn;
    qn.splitQNameString(qname, NAMESPACESEPARATOR);
    EndElement *pEE = new EndElement();
    pEE->m_NameOrValue = qn.localname;
    pEE->m_Namespace  = qn.uri ? qn.uri : "";
    m_Events.push(pEE);
    qn.mergeQNameString(NAMESPACESEPARATOR);
}

void  SoapParserExpat::characters(const XML_Ch *chars, int length)
{

    XML_Ch* pTemp = const_cast<XML_Ch*>(chars);
    XML_Ch replacedchar = pTemp[length];
    /* copy and keep existing char at length position */
    pTemp[length] = '\0';
    /* putting nul charactor so that chars can be used safely */
    Event* pLastEvent;
    if (!m_Events.empty()) 
    {
        pLastEvent = m_Events.back();
        if (CHARACTER_ELEMENT == pLastEvent->getType())
        /* continuing same character node */
        {
            pLastEvent->m_NameOrValue += pTemp;
            pTemp[length] = replacedchar;
            /* put back the character that was there before putting nul 
             * charactor 
             */
            return;
        }
    }
    pLastEvent = new CharElement();
    pLastEvent->m_NameOrValue = pTemp;
    m_Events.push(pLastEvent);
    pTemp[length] = replacedchar;
    /* put back the character that was there before putting nul charactor */
}

void SoapParserExpat::startPrefixMapping(const XML_Ch *prefix, 
                                         const XML_Ch *uri)
{
    if (prefix && uri)
    {
        StartPrefix* pEvent = new StartPrefix();
        pEvent->m_NameOrValue = prefix;
        pEvent->m_Namespace = uri;
        m_Events.push(pEvent);
    }
}

void SoapParserExpat::endPrefixMapping(const XML_Ch *prefix)
{
    if (!prefix) return;
    EndPrefix* pEvent = new EndPrefix();
    pEvent->m_NameOrValue = prefix;
    m_Events.push(pEvent);
}

const XML_Ch* SoapParserExpat::getNS4Prefix(const XML_Ch* prefix)
{
    if (m_NsStack.find(prefix) != m_NsStack.end())
    {
        return m_NsStack[prefix].c_str();
    }
    return NULL;
}

/**
 * This method returning NULL means that there is something wrong with the
 * stream and hence parsing should be finished or aborted.
 * @param isCharData - say that Deserializer is expecting a character data event.
 */
const AnyElement* SoapParserExpat::next(bool isCharData)
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
            nStatus = parseNext();
            if (TRANSPORT_FAILED == nStatus) return NULL;
            if ((TRANSPORT_FINISHED == nStatus) && m_Events.empty())
                return NULL;
            if (AXIS_FAIL == m_nStatus) return NULL;
        }

        if (!m_Events.empty())
        {
            m_pLastEvent = m_Events.front();
            XML_NODE_TYPE type = m_pLastEvent->getType();
            m_Events.pop();
            if ((CHARACTER_ELEMENT == type) && m_Events.empty())
            /* current character element may not be parsed completly */
            {
                m_Events.push(m_pLastEvent);
                nStatus = parseNext();
                if (TRANSPORT_FAILED == nStatus) return NULL;
                if ((TRANSPORT_FINISHED == nStatus) && m_Events.empty()) 
                    return NULL;
            }
            else
            {
                int i = 0;
                switch(type)
                {
                case START_ELEMENT:
                    {
                        for (list<SimpleAttribute*>::iterator it = 
                            ((StartElement*)m_pLastEvent)->m_Attributes.begin()
                            ; it != ((StartElement*)m_pLastEvent)->
                            m_Attributes.end(); it++)
                        {
                            m_Element.m_pchAttributes[i+0] = 
                                (*it)->m_Name.c_str();
                            m_Element.m_pchAttributes[i+1] = 
                                (*it)->m_Namespace.c_str();
                            m_Element.m_pchAttributes[i+2] = 
                                (*it)->m_Value.c_str();
                            i+=3;
                        }
                        m_Element.m_pchAttributes[i+0] = NULL;
                        m_Element.m_pchAttributes[i+1] = NULL;
                        m_Element.m_pchAttributes[i+2] = NULL;
                    }
                    /* no break */
                case END_ELEMENT:
                    m_Element.m_pchNamespace = ((StartElement*)m_pLastEvent)->
                        m_Namespace.c_str();
                    /* no break */
                case CHARACTER_ELEMENT:
                    m_Element.m_pchNameOrValue = m_pLastEvent->
                        m_NameOrValue.c_str();
                    m_Element.m_type = type;
					if (!isCharData && (CHARACTER_ELEMENT == type))
					{ /* ignorable white space */
						delete m_pLastEvent;
						m_pLastEvent = NULL;
						break;						
					}
                    return &m_Element;
                case START_PREFIX:
                    m_NsStack[m_pLastEvent->m_NameOrValue] = 
                        ((StartPrefix*)m_pLastEvent)->m_Namespace;
                    /* I think the same prifix cannot repeat ??? */
                    delete m_pLastEvent;
                    m_pLastEvent = NULL;
                    break;
                case END_PREFIX:
                    m_NsStack.erase(m_pLastEvent->m_NameOrValue);
                    /* I think the same prifix cannot repeat ??? */
                    delete m_pLastEvent;
                    m_pLastEvent = NULL;
                    break;
                }
            }
        }
    } while (TRANSPORT_FAILED != nStatus);
    return NULL;
}

int SoapParserExpat::parseNext()
{
    int nChars = EXPAT_BUFFER_SIZE;
	m_pCurrentBuffer = (char*) XML_GetBuffer(m_Parser, EXPAT_BUFFER_SIZE);
	if (m_pCurrentBuffer)
	{
		m_nTransportStatus = m_pInputStream->getBytes(m_pCurrentBuffer, &nChars);
		if (nChars > 0)
		{
			if (XML_STATUS_ERROR == XML_ParseBuffer(m_Parser, nChars, false))
				m_nStatus = AXIS_FAIL;
		}
		if (TRANSPORT_FAILED == m_nTransportStatus) XML_ParseBuffer(m_Parser, 0, true);
	}
    /* end of parsing */
    return m_nTransportStatus;
}

int SoapParserExpat::getStatus()
{
    m_nStatus = AXIS_SUCCESS; /*TODO:Check if an error occured in expat */
    return m_nStatus;
}

/**
 * Resets SoapParserExpat object 
 */
int SoapParserExpat::init()
{
    XML_ParserReset(m_Parser, NULL);
    XML_SetUserData(m_Parser, this);
    XML_SetNamespaceDeclHandler(m_Parser, s_startPrefixMapping, 
        s_endPrefixMapping);
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

int SoapParserExpat::setInputStream(SOAPTransport* pInputStream)
{
    m_pInputStream = pInputStream;
    return AXIS_SUCCESS;
}
