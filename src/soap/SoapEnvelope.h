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

#if !defined(AXIS_SOAPENVELOPE_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPENVELOPE_H__OF_AXIS_INCLUDED_

#include "SoapHeader.h"
#include "SoapBody.h"
#include <axis/SoapEnvVersions.hpp>

/*
 * @class SoapEnvelope
 * @brief interface for the SoapEnvelope class.
 *
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk)
 */

AXIS_CPP_NAMESPACE_START

class SoapEnvelope  
{
friend class SoapSerializer;

private:
    int serializeStandardNamespaceDecl(SoapSerializer& pSZ);
    int addStandardNamespaceDecl(const Attribute* pAttribute);
    int serializeNamespaceDecl(SoapSerializer& pSZ);
    /* int serializeNamespaceDecl(string&); */
    int serializeAttributes(SoapSerializer& pSZ);
    /* int serializeAttributes(string&); */
    SoapHeader *m_pSoapHeader;
    SoapBody *m_pSoapBody;
    /* string m_strEnvelopSerialized; */
    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;
    list<const Attribute*> m_StandardNamespaceDecls;
    AxisString m_sPrefix;    

public:    

#ifdef UNIT_TESTING_ON
    int initializeForTesting(SOAP_VERSION eSoapVersion);
#endif
    int setPrefix(const AxisChar* prefix);
    int addNamespaceDecl(Attribute* pAttribute);
    int addAttribute(Attribute* pAttribute);    
    int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);
    /* int serialize(string &sSerialized, SOAP_VERSION eSoapVersion); */
    void setSoapBody(SoapBody* soapBody);
    void setSoapHeader(SoapHeader* soapHeader);
    SoapEnvelope();
    virtual ~SoapEnvelope();
};

AXIS_CPP_NAMESPACE_END

#endif
