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

#ifdef WIN32
#pragma warning(disable : 4786)
#endif

#if !defined(__WSDDDOCUMENTXERCES_H_OF_AXIS_INCLUDED__)
#define __WSDDDOCUMENTXERCES_H_OF_AXIS_INCLUDED__

#include "WSDDDocument.h"
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <string>
#include <map>

using namespace std;

XERCES_CPP_NAMESPACE_USE;

/*
 *  @class WSDDDocumentXerces
 *  @brief
 *  @author sanjaya sinharage(sanjaya@opensource.lk)
 *  @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 */
class WSDDDocumentXerces : public WSDDDocument, public DefaultHandler
{
private:
    const AxisChar* __XTRC(const XMLCh* pChar);
    void processAttributes(WSDDLevels ElementType, const Attributes &attrs);
    void getParameters(WSDDLevels ElementType, const Attributes &attrs);
    void addAllowedRolesToService(const AxisXMLCh* value);
    void addAllowedMethodsToService(const AxisXMLCh* value);
    int parseDocument(const AxisChar* sWSDD);

public:
    WSDDDocumentXerces(map<AxisString, int>* pLibNameIdMap);
    ~WSDDDocumentXerces();
    int getDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);
    int updateDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment);

    
    /*  Implementations of the SAX DocumentHandler interface */
    
    void startElement(const XMLCh *const uri, const XMLCh *const localname, 
        const XMLCh *const qname, const Attributes &attrs);
    void characters (const XMLCh *const chars, const unsigned int length);
    void endElement (const XMLCh *const uri, const XMLCh *const localname, 
        const XMLCh *const qname);
    void startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri);
    void endPrefixMapping(const XMLCh* const prefix);

    
    /*  Implementations of the SAX ErrorHandler interface */
    
    void warning(const SAXParseException& exception);
    void error(const SAXParseException& exception);
    void fatalError(const SAXParseException& exception);
};

#endif 

