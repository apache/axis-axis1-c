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
 * @author Susantha Kumara (susantha@opensource.lk)
 */


#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "XMLParserAxis.hpp"
 #include "AxisInputStream.hpp"
 
XMLParserAxis::XMLParserAxis()
{
	m_bEndElementFollows = false;	
	m_pParser = NULL;
    m_pInputStream = NULL;
}

XMLParserAxis::~XMLParserAxis()
{
    if (m_pParser)
        delete m_pParser;
	if (m_pInputStream)
    	delete m_pParser;
}

int XMLParserAxis::setInputStream(AxisIOStream* pInputStream)
{
	m_bEndElementFollows = false;
    if (m_pInputStream)
        delete m_pInputStream;
    m_pInputStream = new AxisInputStream(pInputStream);
	//TODO : Reusing the same parser object should be possible. Improve the
	// parser and then remove the following.
	if (m_pParser)
		delete m_pParser;
	m_pParser = new XmlPullParser(m_pInputStream);
    return AXIS_SUCCESS;
}

const XML_Ch* XMLParserAxis::getNS4Prefix(const XML_Ch* prefix)
{
	//TODO : implement this correctly
    return NULL;
}

int XMLParserAxis::getStatus()
{
	//TODO : implement this correctly
    return AXIS_SUCCESS;
}

void XMLParserAxis::freeElement()
{
	if (m_bEndElementFollows) // free only attributes list if available.
	{
		m_Element.m_type = END_ELEMENT;
	}
	else // free all inner strings 
	{
		if (m_Element.m_pchNameOrValue)
		{
			free (const_cast<void*>((const void*)m_Element.m_pchNameOrValue));
			m_Element.m_pchNameOrValue = 0;
		}
		if (m_Element.m_pchNamespace)
		{
			free (const_cast<void*>((const void*)m_Element.m_pchNamespace));
			m_Element.m_pchNamespace = 0;
		}
	}
	freeAttributes();
}

void XMLParserAxis::freeAttributes()
{
	for (int ix=0; m_Element.m_pchAttributes[ix]; ix+=3)
	{
		if (m_Element.m_pchAttributes[ix])
		{
			free (const_cast<void*>((const void*)m_Element.m_pchAttributes[ix]));
			if (m_Element.m_pchAttributes[ix+1])
				free (const_cast<void*>((const void*)m_Element.m_pchAttributes[ix+1]));
			if (m_Element.m_pchAttributes[ix+2])
				free (const_cast<void*>((const void*)m_Element.m_pchAttributes[ix+2]));
		}
	}
	m_Element.m_pchAttributes[0] = 0;
}

void XMLParserAxis::setAttributes()
{
	int iAttribIx=0;
	int iAttrib = m_pParser->getAttributeCount();
	m_Element.m_pchAttributes[iAttrib*3]=0;
	for (int ix = 0; ix < iAttrib; ix++) 
	{
		iAttribIx=ix*3;
		m_Element.m_pchAttributes[iAttribIx] = m_pParser->getAttributeName(ix);
		m_Element.m_pchAttributes[iAttribIx+1] =
m_pParser->getAttributeNamespaceUri(ix);
		m_Element.m_pchAttributes[iAttribIx+2] = m_pParser->getAttributeValue(ix);
	}				
}

const AnyElement* XMLParserAxis::next(bool isCharData)
{
	int nType;
	freeElement();
	if (m_bEndElementFollows)
	{
		m_bEndElementFollows = false;
		return &m_Element;
	}
	while (true)
		{
			if ((nType= m_pParser->next()) != -1) 
			{
				if (!isCharData && (XmlPullParser::Content == nType))
				{ // ignorable white space
					continue;
				}			
				switch (nType)
				{
				case XmlPullParser::STag:
					m_Element.m_type = START_ELEMENT;
					m_Element.m_pchNameOrValue = m_pParser->getName();
					m_Element.m_pchNamespace = m_pParser->getNamespaceUri();
					setAttributes();
					break;
				case XmlPullParser::EmptyElemTag:
					m_Element.m_type = START_ELEMENT;
					m_Element.m_pchNameOrValue = m_pParser->getName();
					m_Element.m_pchNamespace = m_pParser->getNamespaceUri();
					setAttributes();
					m_bEndElementFollows = true;
					break;
				case XmlPullParser::ETag:
					m_Element.m_type = END_ELEMENT;
					m_Element.m_pchNameOrValue = m_pParser->getName();
					m_Element.m_pchNamespace = m_pParser->getNamespaceUri();
					break;
				case XmlPullParser::Content:
					m_Element.m_type = CHARACTER_ELEMENT;
					m_Element.m_pchNameOrValue = m_pParser->getCharData();
					break;
				default:;
				}
				return &m_Element;
			}
			else 
			{
				return NULL;
			}
		}
}

const AnyElement* XMLParserAxis::anyNext()
{
	//TODO : not implemented. I dont think that this ever need to be implemented
	//because we are not using this any more in Axis.
	return NULL;
}

const XML_Ch* XMLParserAxis::getPrefix4NS(const XML_Ch* pcNS)
{
	//TODO : implement this correctly
    return NULL;
}

