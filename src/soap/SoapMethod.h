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

#include "../common/Param.h"
#include "../common/ISoapMethod.h"
#include "SoapSerializer.h"
#include <list>

AXIS_CPP_NAMESPACE_START

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
    list<Attribute*> m_attributes;
    bool isSerializable();    
    int serializeOutputParam(SoapSerializer& pSZ);
    AxisString m_strPrefix;
    AxisString m_strLocalname;
    AxisString m_strUri;
    list<Param*> m_OutputParams;

public:    
    int reset();
    int addAttribute(Attribute* pAttribute);
    const AxisChar* getMethodName();

  /**
    * This method return AXIS_SUCCESS if it serialize the SoapMethod successfully.
    * If not it returns AXIS_FAIL. The caller of this method has to deal in a 
    * appropriate manner after calling this method.
    */
    int serialize(SoapSerializer& pSZ);
    void addOutputParam(Param *param);
    void setURI(const AxisChar* uri);
    void setLocalName(const AxisChar* localname);
    void setPrefix(const AxisChar* prefix);
    SoapMethod();
    virtual ~SoapMethod();

    /** Method to clear up all the current out params in preparation of a new method call */
    void clearOutParams();
    
    /** Method to clear up all the current attributes in preparation of a new method call */
    void clearAttributes();
};

AXIS_CPP_NAMESPACE_END

#endif
