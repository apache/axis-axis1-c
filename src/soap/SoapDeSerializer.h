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

#if !defined(_SOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _SOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

#include <axis/IHandlerSoapDeSerializer.hpp>
#include "HeaderBlock.h"
#include "../xml/XMLParser.h"
#include "../platforms/PlatformAutoSense.hpp"
#include "../common/AxisUtils.h"

AXIS_CPP_NAMESPACE_START

class SoapFault;
class SoapMethod;
class SoapBody;
class SoapEnvelope;
class SoapHeader;
class IHeaderBlock;

using namespace std;
/*
 *  @class SoapDeSerializer
 *  @brief interface for the SoapDeSerializer class.
 *  @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *  @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

/*
 * Revision 1.1  2004/11/27 roshan
 * Added the implementation of the setNewSoapBody() method. For the same 
 * purpose added the new class "DeSerializerMemBufInputStream".
 */

class SoapDeSerializer : public IHandlerSoapDeSerializer
{
private:
    SoapEnvelope* m_pEnv;
    SoapHeader* m_pHeader;
    XMLParser* m_pParser;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;
    /* Last procesed node needed when the attributes are processed and to determine if empty element */
    const AnyElement* m_pCurrNode;
    const AnyElement* m_pNode;
    SOAP_VERSION m_nSoapVersion;
    AxisChar* m_pEndptr; 
    /* used as a parameter to strtoXX conversion functionss */
    int m_nStatus;
    /* Provider type of current service that uses this DeSerializer object */
    PROVIDERTYPE m_ProviderType;
    SOAPTransport* m_pInputStream;

    string m_strMethodNameToInvoke;

private:
    int AXISCALL getArraySize(const AnyElement* pElement);
public:
    int init();
    int getVersion();
    SoapEnvelope* getEnvelope();
    int getHeader();
    int getBody();
    const char* getMethodNameToInvoke();
    void setMethodNameToInvoke(const char*);
    
    bool isCurrentElementEmpty();
	/**
	* This method allows to peek for the name of the next element in XML stream.
	* Useful in supporting "all" & "choice" WSDL constructs.
	* @return Name of the next element in XML stream 
	*/
	const char* peekNextElementName(); 
	
    int flushInputStream();
    PROVIDERTYPE getCurrentProviderType() { return m_ProviderType;};
    void setCurrentProviderType(PROVIDERTYPE nType) { m_ProviderType = nType;};
    /*
     * Methods to manipulate entire body when the body is compressed or 
     * encrypted 
     * These functions are provided for handlers to manipulate entire soap body.
     */
    xsd__hexBinary AXISCALL getBodyAsHexBinary();
    xsd__base64Binary AXISCALL getBodyAsBase64Binary();
    AxisChar* AXISCALL getBodyAsChar();
    int AXISCALL setNewSoapBody(AxisChar* pNewSoapBody);
    bool isAnyMustUnderstandHeadersLeft();
    int AXISCALL checkMessageBody(const AxisChar* pName, 
        const AxisChar* pNamespace);
    void* AXISCALL checkForFault(const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* to get any header blocks left in the Deserializer */
    HeaderBlock* getHeaderBlock();
    /* to add a header block to the Deserializer. Probably a handler */
    int AXISCALL addHeaderBlock(IHeaderBlock* pBlk);
    /* to get a named header blcok from the Deserializer */
    IHeaderBlock* getHeaderBlock(const AxisChar* pName, 
        const AxisChar* pNamespace);
    int setInputStream(SOAPTransport* pInputStream);
    SoapDeSerializer();
    virtual ~SoapDeSerializer();
    /* Method used by wrappers to get a deserialized Array of complex types 
     * Note:  returned Axis_Array object is the same object as passed in to this
     * method. */
    Axis_Array* AXISCALL getCmplxArray(Axis_Array* pArray, void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized Array of basic types */
    Axis_Array* AXISCALL getBasicArray(XSDTYPE nType, const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized single 
     * object of complex type 
     */
    void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
    
    const char* AXISCALL getCmplxFaultObjectName();
    void* AXISCALL getCmplxFaultObject(void* pDZFunct, void* pCreFunct,
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);

    /* Methods used by wrappers to get a deserialized value of basic types */
    void getElement (const AxisChar* pName, const AxisChar* pNamespace, 
        IAnySimpleType* pSimpleType, bool isArrayElement = false);
    xsd__int * AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__boolean * AXISCALL getElementAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedInt * AXISCALL getElementAsUnsignedInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__short * AXISCALL getElementAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedShort * AXISCALL getElementAsUnsignedShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__byte * AXISCALL getElementAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedByte * AXISCALL getElementAsUnsignedByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__long * AXISCALL getElementAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__integer * AXISCALL getElementAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedLong * AXISCALL getElementAsUnsignedLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__float * AXISCALL getElementAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__double * AXISCALL getElementAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__decimal * AXISCALL getElementAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__string AXISCALL getElementAsString(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__anyURI AXISCALL getElementAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__QName AXISCALL getElementAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__hexBinary * AXISCALL getElementAsHexBinary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__base64Binary * AXISCALL getElementAsBase64Binary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__dateTime * AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__date * AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__time * AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__duration * AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gYearMonth * AXISCALL getElementAsGYearMonth(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gYear * AXISCALL getElementAsGYear(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gMonthDay * AXISCALL getElementAsGMonthDay(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gDay* AXISCALL getElementAsGDay(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gMonth * AXISCALL getElementAsGMonth(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__nonPositiveInteger * AXISCALL getElementAsNonPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__negativeInteger * AXISCALL getElementAsNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__nonNegativeInteger * AXISCALL getElementAsNonNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__positiveInteger * AXISCALL getElementAsPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__normalizedString AXISCALL getElementAsNormalizedString(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__token AXISCALL getElementAsToken(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__language AXISCALL getElementAsLanguage(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__Name AXISCALL getElementAsName(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NCName AXISCALL getElementAsNCName(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__ID AXISCALL getElementAsID(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__IDREF AXISCALL getElementAsIDREF(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__IDREFS AXISCALL getElementAsIDREFS(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__ENTITY AXISCALL getElementAsENTITY(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__ENTITIES AXISCALL getElementAsENTITIES(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NMTOKEN AXISCALL getElementAsNMTOKEN(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NMTOKENS AXISCALL getElementAsNMTOKENS(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NOTATION AXISCALL getElementAsNOTATION(const AxisChar* pName,
        const AxisChar* pNamespace);

	void getAttribute(const AxisChar* pName, const AxisChar* pNamespace,
        IAnySimpleType* pSimpleType);
    xsd__int * AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__boolean * AXISCALL getAttributeAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedInt * AXISCALL getAttributeAsUnsignedInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__short * AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedShort * AXISCALL getAttributeAsUnsignedShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__byte * AXISCALL getAttributeAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedByte * AXISCALL getAttributeAsUnsignedByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__long * AXISCALL getAttributeAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__integer * AXISCALL getAttributeAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__nonPositiveInteger * AXISCALL getAttributeAsNonPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__negativeInteger * AXISCALL getAttributeAsNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__nonNegativeInteger * AXISCALL getAttributeAsNonNegativeInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__positiveInteger * AXISCALL getAttributeAsPositiveInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__unsignedLong * AXISCALL getAttributeAsUnsignedLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__float * AXISCALL getAttributeAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__double * AXISCALL getAttributeAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__decimal * AXISCALL getAttributeAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__NOTATION AXISCALL getAttributeAsNOTATION(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__string AXISCALL getAttributeAsString(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__normalizedString AXISCALL getAttributeAsNormalizedString(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__token AXISCALL getAttributeAsToken(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__language AXISCALL getAttributeAsLanguage(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NMTOKEN AXISCALL getAttributeAsNMTOKEN(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NMTOKENS AXISCALL getAttributeAsNMTOKENS(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__Name AXISCALL getAttributeAsName(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__NCName AXISCALL getAttributeAsNCName(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__ID AXISCALL getAttributeAsID(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__IDREF AXISCALL getAttributeAsIDREF(const AxisChar* pName,
        const AxisChar* pNamespace);    
    xsd__IDREFS AXISCALL getAttributeAsIDREFS(const AxisChar* pName,
        const AxisChar* pNamespace);    
    xsd__ENTITY AXISCALL getAttributeAsENTITY(const AxisChar* pName,
        const AxisChar* pNamespace);    
    xsd__ENTITIES AXISCALL getAttributeAsENTITIES(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__anyURI AXISCALL getAttributeAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__QName AXISCALL getAttributeAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__hexBinary * AXISCALL getAttributeAsHexBinary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__base64Binary * AXISCALL getAttributeAsBase64Binary
        (const AxisChar* pName, const AxisChar* pNamespace);
    xsd__dateTime * AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__date * AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__time * AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__gDay* AXISCALL getAttributeAsGDay(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__gMonth* AXISCALL getAttributeAsGMonth(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__gMonthDay* AXISCALL getAttributeAsGMonthDay(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__gYear* AXISCALL getAttributeAsGYear(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__gYearMonth* AXISCALL getAttributeAsGYearMonth(const AxisChar* pName,
        const AxisChar* pNamespace);
    xsd__duration * AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace);
    
    void setStyle(AXIS_BINDING_STYLE nStyle){ m_nStyle = nStyle;};
    AXIS_BINDING_STYLE getStyle(){return m_nStyle;};    
    XSDTYPE getXSDType(const AnyElement* pElement);
    int AXISCALL getStatus(){return m_nStatus;};
	AnyType* AXISCALL getAnyObject();
    void serializeTag(AxisString& xmlStr, const AnyElement* node, AxisString& nsDecls);
    void getChardataAs(void** pValue, XSDTYPE type);

    /**
      *Returns the attachemtn object for the given id.
      */
    ISoapAttachment* getAttachment(const char* pcAttachmentid);
    ISoapAttachment** getAllAttachments(int *pAttchArraySize);

	/**
	 * Returns a complex fault as an XML string 
	 */
	xsd__string getFaultAsXMLString();

    /*
     *This class is used by the DeSerializer to set the input stream back to 
     * the parser in following situations:
     *  - The SOAPHeaders change the SOAPBody and want to set it back to the
     *     DeSerializer.
     */
    class DeSerializerMemBufInputStream : public AxisIOStream
        {
        private:
                const char* m_pcDeSeriaMemBuffer;
        public:
                DeSerializerMemBufInputStream(const char* pcDeSeriaMemBuffer)
                {m_pcDeSeriaMemBuffer = pcDeSeriaMemBuffer;};
                virtual ~DeSerializerMemBufInputStream(){};
                AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferid);
                AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piRetSize);
        };



private:
    xsd__base64Binary decodeFromBase64Binary(const AxisChar* pValue);
    xsd__hexBinary decodeFromHexBinary(const AxisChar* pValue);
    void deserializeLiteralArray (Axis_Array* pArray, IAnySimpleType* pSimpleType, const AxisChar* pName, const AxisChar* pNamespace);
    void deserializeEncodedArray (Axis_Array* pArray, IAnySimpleType* pSimpleType, const AxisChar* pName, const AxisChar* pNamespace, int size);
	void deserializeLiteralComplexArray(Axis_Array * pArray, void *pDZFunct, void *pCreFunct, void *pDelFunct,  const AxisChar * pName, const AxisChar * pNamespace);
	void deserializeEncodedComplexArray(Axis_Array * pArray, void *pDZFunct, void *pCreFunct, void *pDelFunct, const AxisChar * pName, const AxisChar * pNamespace, int size);
};

AXIS_CPP_NAMESPACE_END

#endif 

