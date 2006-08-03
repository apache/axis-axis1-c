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
#ifndef IWRAPPERSOAPSERIALIZER_INCLUDED
#define IWRAPPERSOAPSERIALIZER_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif



/**
 * @file IWrapperSoapSerializer.hpp
 */

#include <axis/AxisUserAPI.h>
#include <axis/TypeMapping.h>
#include <axis/WSDDDefines.h>
#include <axis/ISoapAttachment.h>
#include <stdarg.h>

/**
 *  @class IWrapperSoapSerializer
 *  @brief interface for the IWrapperSoapSerializer class.
 *
 *
 *
 */
/**
 * Destructor
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerDestroy(AXISCHANDLE wrapperSoapSerializer);

/**
 * Create new SOAP method, ie the first nested element within a SOAP Body.
 *
 * @param sLocalName local name of the method
 * @param sURI namespace URI of the method
 * @return status
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerCreateSoapMethod(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerCreateSoapFault(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sLocalName, 
	const AxiscChar * sURI, 
	const AxiscChar * sFaultCode, 
	const AxiscChar * sFaultString);

/**
 * Returns the corrosponding namespace prefix. This method is
 * called when the caller also wants to know whether this is a new
 * namespace or not as appose to its overloaded other member.
 * @param pNamespace The namespace.
 * @param blnIsNewPrefix The boolean which behaves as
 * an out parameter to indicate whether this is a new namespace or not.
 * @return The corrosponding prefix.
 */
AXISC_STORAGE_CLASS_INFO
const AxiscChar * axiscSoapSerializerGetNamespacePrefix(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace, 
	AxiscBool * blnIsNewPrefix);

/**
 * Remove the prefix for specified namespace.
 * @param pNamespace namespace URI for which the corresponding prefix will be removed.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerRemoveNamespacePrefix(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pNamespace);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddOutputParam(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pchName, 
	void * pValue, 
	AXISC_XSDTYPE type);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddOutputCmplxArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddOutputBasicArrayParam(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	AXISC_XSDTYPE nType, 
	const AxiscChar * pName);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddOutputCmplxParam(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddFaultDetail(AXISCHANDLE wrapperSoapSerializer, void * pObject, 
	void * pSZFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeCmplxArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	void * pSZFunct, 
	void * pDelFunct, 
	const AxiscChar * pName, 
	const AxiscChar * pNamespace);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeBasicArray(AXISCHANDLE wrapperSoapSerializer, const Axisc_Array * pArray, 
	const AxiscChar * pNamespace, 
	AXISC_XSDTYPE nType, 
	const AxiscChar * pName);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeAsElement(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, 
	void * pValue, 
	AXISC_XSDTYPE type);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeAsAttribute(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * sName, 
	const AxiscChar * pNamespace, 
	void * pValue, 
	AXISC_XSDTYPE type);

/**
 * Serialize strings.  All arguments must be strings (char *).
 * The final argument must be NULL.
 *
 * The strings will be serialized "as-is", no validation will take place.
 *
 * @param pFirst first string to be serialized.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerSerialize(AXISCHANDLE wrapperSoapSerializer, const char * pFirst, 
	... );

/**
 * Serialize start element tag for complex type.
 * This is only used for rpc/encoded style web services.
 *
 * @param pName local name of element.
 * @param pNamespace namespace URI of element.
 * @param pPrefix prefix to be used with namespace URI.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerSerializeStartElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName, 
	const AxiscChar * pNamespace, 
	const AxiscChar * pPrefix);

/**
 * Serialize end element tag for complex type.
 * This is only used for rpc/encoded style web services.
 *
 * @param pName local name of element.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerSerializeEndElementOfType(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * pName);

/**
 * Get and return the current provider type being used by the SOAP Serializer.
 *
 * @return provider type.
 */
AXISC_STORAGE_CLASS_INFO
AXISC_PROVIDERTYPE axiscSoapSerializerGetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer);

/**
 * Set the current provider type to be used by the SOAP serializer.
 *
 * @param nType provider type to be used.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerSetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer, AXISC_PROVIDERTYPE nType);

/**
 * Add an AnyType object to the outgoing SOAP message.
 *
 * This method would normally be used in client stubs or service wrappers.
 *
 * @param pAnyObject an AnyType object containing valid XML.
 * @return status.
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerAddOutputAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject);

/**
 * Serialize an AnyType object to the outgoing SOAP message.
 *
 * This method would normally be used by the serialize methods in complex types.
 *
 * @param pAnyObject an AnyType object containing valid XML.
 * @return status.
 */
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeAnyObject(AXISCHANDLE wrapperSoapSerializer, AxiscAnyType * pAnyObject);

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
AXISC_STORAGE_CLASS_INFO
int axiscSoapSerializerSerializeAsChardata(AXISCHANDLE wrapperSoapSerializer, void * pValue, 
	AXISC_XSDTYPE type);

/**
 * Add an attachment to the outgoing SOAP message.
 *
 * This method would normally be used in client stubs or service wrappers.
 *
 * @param achId attachment ID.
 * @param objAttach SOAP attachment.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerAddAttachment(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	AXISCHANDLE objAttach);

/**
 * Add attachments to the outgoing SOAP message.
 *
 * This method would normally be used in client stubs or service wrappers.
 *
 * @param pAttach array of ISoapAttachment
 * @param iAttchArraySize number of attachments to be added.
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerAddAttachments(AXISCHANDLE wrapperSoapSerializer, AXISCHANDLE pAttach, 
	int iAttchArraySize);

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
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerAddAttachmentBody(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	xsdc__base64Binary * pAttchBody);

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
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerAddAttachmentHeader(AXISCHANDLE wrapperSoapSerializer, const AxiscChar * achId, 
	const AxiscChar * achHeaderName, 
	const AxiscChar * achHeaderValue);

/**
 * creates and returns a SoapAttachment object to the caller of this methods.
 *  The user can use this object and fill in the attachment details. This
 *  method doesn't add the created SoapAttachment object to the Serializer.
 *  The user will have to add this object explictly by calling the addAttachment
 *  method of the IWrapperSoapSerializer interface
 */
AXISC_STORAGE_CLASS_INFO
AXISCHANDLE axiscSoapSerializerCreateSoapAttachment(AXISCHANDLE wrapperSoapSerializer);

/**
 * This method will clear up all the current out params in preparation of a
 * new method call
 */
AXISC_STORAGE_CLASS_INFO
void axiscSoapSerializerReset(AXISCHANDLE wrapperSoapSerializer);


#ifdef __cplusplus
 }
#endif

#endif /* IWRAPPERSOAPSERIALIZER_INCLUDED */
