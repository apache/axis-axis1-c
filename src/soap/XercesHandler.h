/* -*- C++ -*- */
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
 *	@author sanjaya singharage (sanjayas@opensource.lk)
 */

#include    <xercesc/sax/HandlerBase.hpp>
#include    <xercesc/sax2/DefaultHandler.hpp>
#include <axis/server/AnyElement.h>
#include <stdlib.h>
#include <map>
#include <string>
#include "../../include/axis/server/GDefine.h"

XERCES_CPP_NAMESPACE_USE

using namespace std;

class XercesHandler : public XERCES_CPP_NAMESPACE::DefaultHandler
{
public :
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    XercesHandler();
    ~XercesHandler();


    // -----------------------------------------------------------------------
    //  Handlers for the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
	void startElement(const XMLCh *const uri,const XMLCh *const localname,const XMLCh *const qname,const Attributes &attrs);
	void endElement (const XMLCh *const uri,const XMLCh *const localname,const XMLCh *const qname);
    void characters(const XMLCh* const chars, const unsigned int length);
	void startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri);
	void endPrefixMapping(const XMLCh* const prefix);
    void ignorableWhitespace(const XMLCh* const chars, const unsigned int length);
    void resetDocument();


    // -----------------------------------------------------------------------
    //  Implementations of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exception);
    void error(const SAXParseException& exception);
    void fatalError(const SAXParseException& exception);

	const XML_Ch* XercesHandler::NS4Prefix(const XML_Ch* prefix);

	int getTest()
	{
		return test;
	}

	AnyElement* getAnyElement()
	{
		return Nelement;
	}

private:
	int test;
	AnyElement * Nelement;
	map<AxisXMLString, AxisXMLString> m_NsStack;
	void initAnyElement()
	{
		Nelement->m_pchNameOrValue = NULL;
		Nelement->m_pchNamespace = NULL;
	}

};