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
 *    @author sanjaya singharage (sanjayas@opensource.lk)
 */

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include "../AnyElement.h"
#include <stdlib.h>
#include <map>
#include <string>
#include <axis/GDefine.hpp>

XERCES_CPP_NAMESPACE_USE

using namespace std;

class XercesHandler : public XERCES_CPP_NAMESPACE::DefaultHandler
{
public :
    void freeElement();
    inline int getStatus(){return m_nStatus;};
    XercesHandler();
    ~XercesHandler();
    const XML_Ch* ns4Prefix(const XML_Ch* prefix);
    const XML_Ch* prefix4NS(const XML_Ch* pcNS);
    AnyElement* getAnyElement();
	void setGetPrefixMappings(bool bValue);
	void reset();

private:
    /* -----------------------------------------------------------------------
     *  Handlers for the SAX DocumentHandler interface
     * -----------------------------------------------------------------------
     */
    void startElement(const XMLCh *const uri,const XMLCh *const localname,
        const XMLCh *const qname,const Attributes &attrs);
    void endElement (const XMLCh *const uri,const XMLCh *const localname,
        const XMLCh *const qname);
    void characters(const XMLCh* const chars, const unsigned int length);
    void startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri);
    void endPrefixMapping(const XMLCh* const prefix);
    void ignorableWhitespace(const XMLCh* const chars, 
        const unsigned int length);
    void resetDocument();


    /* -----------------------------------------------------------------------
     *  Implementations of the SAX ErrorHandler interface
     * -----------------------------------------------------------------------
     */
    void warning(const SAXParseException& exception);
    void error(const SAXParseException& exception);
    void fatalError(const SAXParseException& exception);

    int m_nStatus;
	bool m_bEndElementFollows;
    AnyElement* m_pNextElement;
    AnyElement* m_pPrefixMappingElement;
    AnyElement* m_pCurrElement;
    map<AxisXMLString, AxisXMLString> m_NsStack;
	map<const AxisChar*, const AxisChar*> m_CurrPrefixMappings;
	bool m_bGetPrefixMappings;
	bool m_bStartElementWaiting;
	void freeAttributes();
};

