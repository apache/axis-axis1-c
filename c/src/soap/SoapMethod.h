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


#if !defined(AXIS_SOAPMETHOD_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPMETHOD_H__OF_AXIS_INCLUDED_

#include <axis/server/Param.h>
#include "../common/ISoapMethod.h"
#include <axis/server/SoapSerializer.h>
#include <list>

class Attribute;

using namespace std;

/*
    @class SoapMethod
    @brief    The SOAP Body of a SOAP Envelope according to 
    SOAP 1.2 specification.

    The SOAP method.

    SOAP Body child Element:
    All child element information items of the SOAP Body element information 
    item:
         - SHOULD have a [namespace name] property which has a value, that is
           the name of the element SHOULD be namespace qualified.
         - MAY have any number of character information item children. Child 
           character information items whose character code is amongst the
           white space characters as defined by XML 1.0 [XML 1.0] are 
           considered significant.
         - MAY have any number of element information item children. Such
           element information items MAY be namespace qualified.
         - MAY have zero or more attribute information items in its
           [attributes] property. Among these MAY be the following, which has
           special significance for SOAP processing:
             - encodingStyle attribute information item



    @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
*/

class SoapMethod : public ISoapMethod
{

private:
    int serializeAttributes(SoapSerializer& pSZ, list<AxisChar*>& lstTmpNameSpaceStack);
    /* int serializeAttributes(string& sSerialized); */
    list<Attribute*> m_attributes;
    bool isSerializable();    
    int serializeOutputParam(SoapSerializer& pSZ);
    /* int serializeOutputParam(string&); */
    AxisString m_strPrefix;
    AxisString m_strLocalname;
    AxisString m_strUri;
    list<Param*> m_OutputParams;
    /* string m_strMethodSerialized; */
    /* test line */

public:    
    /*
     * Initializes the member variables for testing.
     * @return The status indicating success (AXIS_SUCCESS) or failure
     * (AXIS_FAIL).
     */

    int initializeForTesting();

    int reset();
    int addAttribute(Attribute* pAttribute);
    const AxisChar* getMethodName();
    int serialize(SoapSerializer& pSZ);
    /* int serialize(string&); */
    void addOutputParam(Param *param);
    void setUri(const AxisChar* uri);
    void setLocalName(const AxisChar* localname);
    void setPrefix(const AxisChar* prefix);
    SoapMethod();
    virtual ~SoapMethod();
};

#endif
