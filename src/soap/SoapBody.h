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

#if !defined(AXIS_SOAPBODY_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPBODY_H__OF_AXIS_INCLUDED_

#include "SoapMethod.h"
#include "SoapFault.h"
#include <axis/SoapEnvVersions.hpp>


AXIS_CPP_NAMESPACE_START

class Attribute;

/*
 *  @class SoapBody
 *  @brief    The SOAP Body of a SOAP Envelope according to SOAP 1.2 specification.
 *
 *    The SOAP Body of a SOAP Envelope according to SOAP 1.2 specification.
 *
 *    A SOAP body provides a mechanism for transmitting information to an ultimate SOAP receiver.
 *  The Body element information item has:
 *        - A [local name] of Body .
 *        - A [namespace name] of "http://www.w3.org/2003/05/soap-envelope".
 *        - Zero or more namespace qualified attribute information items in its [attributes] property.
 *        - Zero or more namespace qualified element information items in its [children] property.
 *
 *  The Body element information item MAY have any number of character information item children whose
 *  character code is amongst the white space characters as defined by XML 1.0 [XML 1.0]. These are
 *  considered significant.
 *
 *  SOAP Body child Element:
 *  All child element information items of the SOAP Body element information item:
 *        - SHOULD have a [namespace name] property which has a value, that is the name of the element
 *          SHOULD be namespace qualified.
 *        - MAY have any number of character information item children. Child character information
 *          items whose character code is amongst the white space characters as defined by XML 1.0 [XML 1.0]
 *          are considered significant.
 *        - MAY have any number of element information item children. Such element information items MAY be
 *          namespace qualified.
 *        - MAY have zero or more attribute information items in its [attributes] property. Among these MAY
 *          be the following, which has special significance for SOAP processing:
 *            - encodingStyle attribute information item
 *  SOAP defines one particular direct child of the SOAP body, the SOAP fault, which is used for reporting
 *  errors
 */

class SoapBody  
{
friend class SoapSerializer;

private:
    int serializeAttributes(SoapSerializer& pSZ);
    int serializeNamespaceDecl(SoapSerializer& pSZ);

    list<Attribute*> m_attributes;
    list<Attribute*> m_namespaceDecls;
    SoapMethod *m_pSoapMethod;
    SoapFault *m_pSoapFault;

public:    

    /**
     * Add attribute to the SOAP body.
     *
     * @param attr The Attribute pointer which points to an attribute.
     */
    void addAttribute(Attribute* attr);

    /**
      * Sets the namespace declaration of the Soap body.  Object will be owned by the class.
      *
      * @param pAttribute The Attribute pointer which points to a valid namespace declaration Attribute.
      * @return AXIS_SUCCESS to indicate successfull operation. Return AXIS_FAIL to indicate unsuccessfull operation.
      */
    int addNamespaceDecl(Attribute* pAttribute);

    /**
     * Serialize SOAP body.
     */
    int serialize(SoapSerializer& pSZ, SOAP_VERSION eSoapVersion);

    void setSoapFault(SoapFault* pSoapFault);
    void setSoapMethod(SoapMethod* ptrSoapMethod);

    /**
     * Constructor.
     */
    SoapBody();

    /**
     * Destructor.
     */
    virtual ~SoapBody();
    
    /**
     * Returns SoapMethod.
     */
    SoapMethod *getSoapMethod() { return m_pSoapMethod; }

    /**
     * Clears all previously set information by calling 
     * clearAttributes() and clearNamespaceDecls().
     */
    void clear();

    /**
     * Clears any attributes by actually deleting the objects representing the attributes.
     */
    void clearAttributes();

    /**
     * Clears any namespace declarations by deleting the objects representing the namespace
     * declarations.
     */
    void clearNamespaceDecls();
};

AXIS_CPP_NAMESPACE_END

#endif
