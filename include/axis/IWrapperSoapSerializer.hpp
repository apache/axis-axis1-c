/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED TO THE        */
/* C-EQUIVALENT HEADER FILE IN SUPPORT OF THE C-BINDING INTERFACES.   */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


#if !defined(_IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPSERIALIZER_H____OF_AXIS_INCLUDED_

/**
 * @file IWrapperSoapSerializer.hpp
 */

#include <axis/AxisUserAPI.hpp>
#include <axis/TypeMapping.hpp>
#include <axis/WSDDDefines.hpp>
#include <axis/ISoapAttachment.hpp>
#include <stdarg.h>
#include <cctype>

/**
 *  @class IWrapperSoapSerializer
 *  @brief interface for the IWrapperSoapSerializer class.
 *
 *
 *  @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

AXIS_CPP_NAMESPACE_START

class IWrapperSoapSerializer
{
public:
    /**
     * Destructor
     */
    virtual ~IWrapperSoapSerializer(){};

    /**
     * Create new SOAP method, ie the first nested element within a SOAP Body.
     * 
     * @param sLocalName local name of the method
     * @param sURI namespace URI of the method
     * @return status
     */
    virtual int AXISCALL createSoapMethod(const AxisChar* sLocalName, 
                                          const AxisChar* sURI)=0;

    /**
     * Create a new SOAP Fault within the SOAP Body.
     * 
     * This creates a SOAP Fault with no detail element, this can be added later
     * using:
     * 
     * IWrapperSoapSerializer::addFaultDetail(const AxisChar*) for character detail, or
     * 
     * IWrapperSoapSerializer::addFaultDetail(void*, void*, void*, const AxisChar*, const AxisChar*) for complex detail
     * 
     * @param sLocalName local name for the SOAP Fault.
     * @param sURI namespace URI for the SOAP Fault.
     * @param sFaultCode fault code for the SOAP Fault.
     * @param sFaultString fault string for the SOAP Fault.
     * @return status
     */
    virtual int AXISCALL createSoapFault(const AxisChar* sLocalName, 
                                         const AxisChar* sURI, 
                                         const AxisChar* sFaultCode,
                                         const AxisChar* sFaultString)=0;

    /**
     * Returns the corrosponding namespace prefix.
     * @param pNamespace The namespace.
     * @return The corrosponding prefix.
     */
    virtual const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace)=0;
    
    /**
     * Returns the corrosponding namespace prefix. This method is 
     * called when the caller also wants to know whether this is a new 
     * namespace or not as appose to its overloaded other member.
     * @param pNamespace The namespace.
     * @param blnIsNewPrefix The boolean which behaves as 
     * an out parameter to indicate whether this is a new namespace or not.
     * @return The corrosponding prefix.
     */
    virtual const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace,
                                                        bool& blnIsNewPrefix)=0;
    
    /**
     * Remove the prefix for specified namespace.
     * @param pNamespace namespace URI for which the corresponding prefix will be removed.
     */
    virtual void AXISCALL removeNamespacePrefix(const AxisChar* pNamespace)=0;

    /**
     * Add a basic element, ie a SOAP element containing an XSD simple type,
     * to outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * @param pchName local name for SOAP element.
     * @param pValue value for element data.
     * @param type XSD type of data.
     * @return status
     */
    virtual int AXISCALL addOutputParam(const AxisChar* pchName, 
                                        void* pValue, 
                                        XSDTYPE type)=0;

    /**
     * Add an array of complex type to the outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pArray Axis_Array containing complex type elements.
     * @param pSZFunct function pointer to complex type serialize method.
     * @param pDelFunct function pointer to complex type delete method.
     * @param pName local name for array elements.
     * @param pNamespace namespace URI for array elements.
     * @return status
     */
    virtual int AXISCALL addOutputCmplxArrayParam(const Axis_Array* pArray, 
                                                  void* pSZFunct, 
                                                  void* pDelFunct, 
                                                  const AxisChar* pName, 
                                                  const AxisChar* pNamespace)=0;

    /**
     * Add an array of basic type to outgoing SOAP message.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pArray Axis_Array containing basic type elements.
     * @param nType XSD type for data.
     * @param pName local name for array elements.
     * @return status
     */
    virtual int AXISCALL addOutputBasicArrayParam(const Axis_Array* pArray, 
                                                  XSDTYPE nType, 
                                                  const AxisChar* pName)=0;

    /**
     * Add a complex type element to the outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pObject complex type object.
     * @param pSZFunct function pointer to complex type serialize method.
     * @param pDelFunct function pointer to complex type delete method.
     * @param pName local name for complex type element.
     * @param pNamespace namespace URI for complex type element.
     * @return status
     */
    virtual int AXISCALL addOutputCmplxParam(void* pObject, 
                                             void* pSZFunct,
                                             void* pDelFunct, 
                                             const AxisChar* pName, 
                                             const AxisChar* pNamespace) = 0;

    /**
     * Use this method to add complex detail to a SOAP Fault.
     * 
     * The SOAP fault must be created before using this method, by using: 
     * IWrapperSoapSerializer::createSoapFault(const AxisChar*, const AxisChar*, const AxisChar*, const AxisChar*)
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pObject complex detail object.
     * @param pSZFunct function pointer to serialize method.
     * @param pDelFunct function pointer to delete method.
     * @param pName local name for detail element
     * @param pNamespace namespace URI for detail element.
     * @return status
     */
    virtual int AXISCALL addFaultDetail(void* pObject, 
                                        void* pSZFunct, 
                                        void* pDelFunct, 
                                        const AxisChar* pName, 
                                        const AxisChar* pNamespace) = 0;

    /**
     * Use this method to add simple, ie text, detail to a SOAP fault.
     * 
     * The SOAP fault must be created before using this method, by using: 
     * IWrapperSoapSerializer::createSoapFault(const AxisChar*, const AxisChar*, const AxisChar*, const AxisChar*)
     * 
     * @param pDetail The text to be used for the detail element of the SOAP fault.
     * @return indicates success or failure of adding fault detail
     */
    virtual int AXISCALL addFaultDetail( const AxisChar * pDetail) = 0;

    /**
     * Serialize an array of complex type to the outgoing SOAP message.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * @param pArray Axis_Array containing complex type elements.
     * @param pSZFunct function pointer to complex type serialize method.
     * @param pDelFunct function pointer to complex type delete method.
     * @param pName local name for array elements.
     * @param pNamespace namespace URI for array elements.
     * @return status
     */
    virtual int AXISCALL serializeCmplxArray(const Axis_Array* pArray,
                                             void* pSZFunct, 
                                             void* pDelFunct, 
                                             const AxisChar* pName, 
                                             const AxisChar* pNamespace)=0;

    /**
     * Serialize an array of basic type to outgoing SOAP message.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * @param pArray Axis_Array containing basic type elements.
     * @param nType XSD type for data.
     * @param pName local name for array elements.
     * @return status
     */
    virtual int AXISCALL serializeBasicArray(const Axis_Array* pArray, 
                                             XSDTYPE nType, 
                                             const AxisChar* pName)=0;

    /**
     * Serialize an array of basic type to outgoing SOAP message.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * @param pArray Axis_Array containing basic type elements.
     * @param pNamespace namespace URI for array elements.
     * @param nType XSD type for data.
     * @param pName local name for array elements.
     * @return status
     */
    virtual int AXISCALL serializeBasicArray(const Axis_Array* pArray, 
                                             const AxisChar* pNamespace, 
                                             XSDTYPE nType, 
                                             const AxisChar* pName)=0;

    /**
     * Serialize a basic element, ie a SOAP element containing an XSD simple type,
     * to outgoing SOAP message.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * @param sName local name for SOAP element.
     * @param pValue value for element data.
     * @param type XSD type of data.
     * @return status
     */
    virtual int AXISCALL serializeAsElement(const AxisChar* sName,
                                            void* pValue, 
                                            XSDTYPE type)=0;

    /**
     * Serialize a basic element, ie a SOAP element containing an XSD simple type,
     * to outgoing SOAP message.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * @param sName local name for SOAP element.
     * @param pNamespace namespace URI for SOAP element
     * @param pValue value for element data.
     * @param type XSD type of data.
     * @return status
     */
    virtual int AXISCALL serializeAsElement(const AxisChar* sName, 
                                            const AxisChar* pNamespace,
                                            void* pValue, 
                                            XSDTYPE type)=0;

    /**
     * Serialize aa attribute to outgoing SOAP message.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * See AxisUserAPI.hpp for full list of XSD built-in simple types.
     * 
     * @param sName local name for SOAP attribute.
     * @param pNamespace namespace URI for SOAP attribute.
     * @param pValue value for attribute data.
     * @param type XSD type of data.
     * @return status
     */
    virtual int AXISCALL serializeAsAttribute(const AxisChar* sName,
                                              const AxisChar* pNamespace, 
                                              void* pValue, 
                                              XSDTYPE type)=0;

    /**
     * Serialize an array of strings.
     * 
     * The strings will be serialized "as-is", no validation will take place.
     * Primary use is by the C-bindings interface.
     * 
     * @param pFirst first string to be serialized.
     * @param args ptr to va_list of strings to be serialized.
     */
    virtual void AXISCALL serializeVargs(const char* pFirst, va_list args)=0;
    
    /**
     * Serialize strings.  All arguments must be strings (char *).
     * The final argument must be NULL.
     * 
     * The strings will be serialized "as-is", no validation will take place.
     * 
     * @param pFirst first string to be serialized.
     */
    virtual void AXISCALL serialize(const char* pFirst, ...)=0;

    /**
     * Serialize start element tag for complex type.
     * This is only used for rpc/encoded style web services.
     * 
     * @param pName local name of element.
     * @param pNamespace namespace URI of element.
     * @param pPrefix prefix to be used with namespace URI.
     */
    virtual void AXISCALL serializeStartElementOfType(const AxisChar* pName, 
                                                      const AxisChar* pNamespace, 
                                                      const AxisChar* pPrefix)=0;

    /**
     * Serialize end element tag for complex type.
     * This is only used for rpc/encoded style web services.
     * 
     * @param pName local name of element.
     */
    virtual void AXISCALL serializeEndElementOfType(const AxisChar* pName)=0;

    /**
     * Get and return the current provider type being used by the SOAP Serializer.
     * 
     * @return provider type.
     */
    virtual PROVIDERTYPE getCurrentProviderType()=0;

    /**
     * Set the current provider type to be used by the SOAP serializer.
     * 
     * @param nType provider type to be used.
     */
    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;    

    /**
     * Add an AnyType object to the outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pAnyObject an AnyType object containing valid XML.
     * @return status.
     */
    virtual int addOutputAnyObject(AnyType* pAnyObject)=0;

    /**
     * Serialize an AnyType object to the outgoing SOAP message.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * @param pAnyObject an AnyType object containing valid XML.
     * @return status.
     */
    virtual int serializeAnyObject(AnyType* pAnyObject)=0;

    /**
     * Serialize an XML simple type.  Care must be taken to ensure this is correctly
     * placed within an element or attribute.
     * 
     * This method would normally be used by the serialize methods in complex types.
     * 
     * @param pValue value to be serialized.
     * @param type XSD type of the data.
     * @return status
     */
    virtual int serializeAsChardata(void* pValue, 
                                    XSDTYPE type)=0;

    /**
     * Add an attachment to the outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param achId attachment ID.
     * @param objAttach SOAP attachment.
     */
    virtual void addAttachment(const AxisChar* achId, 
                               ISoapAttachment* objAttach)=0;

    /**
     * Add attachments to the outgoing SOAP message.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param pAttach array of ISoapAttachment
     * @param iAttchArraySize number of attachments to be added.
     */
    virtual void addAttachments(ISoapAttachment** pAttach, 
                                int iAttchArraySize)=0;

    /**
     * Add attachment body to the outgoing SOAP message.
     * If an attachment already exists for the given ID the body will be added to it,
     * otherwise a new attachment will be created.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param achId attachment ID.
     * @param pAttchBody body for SOAP attachment.
     */
    virtual void addAttachmentBody(const AxisChar* achId, 
                                   xsd__base64Binary* pAttchBody)=0;

    /**
     * Add attachment header to the outgoing SOAP message.
     * If an attachment already exists for the given ID the header will be added to it,
     * otherwise a new attachement will be created.
     * 
     * This method would normally be used in client stubs or service wrappers.
     * 
     * @param achId attachment ID.
     * @param achHeaderName attachment header name.
     * @param achHeaderValue attachment header value.
     */
    virtual void addAttachmentHeader(const AxisChar* achId, 
                                     const AxisChar* achHeaderName, 
                                     const AxisChar* achHeaderValue)=0;

    /**
     * creates and returns a SoapAttachment object to the caller of this methods.
     *  The user can use this object and fill in the attachment details. This
     *  method doesn't add the created SoapAttachment object to the Serializer.
     *  The user will have to add this object explictly by calling the addAttachment 
     *  method of the IWrapperSoapSerializer interface   
     */
    virtual ISoapAttachment* createSoapAttachment()=0;

    /**
     * This method will clear up all the current out params in preparation of a 
     * new method call
     */
    virtual void reset() = 0;
};

AXIS_CPP_NAMESPACE_END

#endif

