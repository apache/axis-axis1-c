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

#if !defined(_SOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _SOAPDESERIALIZER_H____OF_AXIS_INCLUDED_

#include "IHandlerSoapDeSerializer.h"
#include "SoapEnvVersions.h"
#include "HeaderBlock.h"
#include "WSDDDefines.h"
#include "XMLParser.h"
#include "AnyElement.h"
#include <axis/SOAPTransport.h>
#include <axis/server/AxisException.h>

class SoapFault;
class SoapMethod;
class SoapBody;
class SoapEnvelope;
class SoapHeader;
class IHeaderBlock;

/*
 *  @class SoapDeSerializer
 *  @brief interface for the SoapDeSerializer class.
 *  @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
class SoapDeSerializer : public IHandlerSoapDeSerializer
{
private:
    SoapEnvelope* m_pEnv;
    SoapHeader* m_pHeader;
    XMLParser* m_pParser;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;
    /* Last procesed node needed when the attributes are processed */
    const AnyElement* m_pCurrNode;
    const AnyElement* m_pNode;
    SOAP_VERSION m_nSoapVersion;
    AxisChar* m_pEndptr; 
    /* used as a parameter to strtoXX conversion functionss */
    int m_nStatus;
    /* Provider type of current service that uses this DeSerializer object */
    PROVIDERTYPE m_ProviderType;
    char* m_pcFaultDetail;

private:
    int AXISCALL getArraySize(const AnyElement* pElement);
    int getBody();
public:
    int init();
    int getVersion();
    SoapEnvelope* getEnvelope();
    int getHeader();
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
    int AXISCALL setNewSoapBody(AxisChar* pNewSoapBody);
    bool isAnyMustUnderstandHeadersLeft();
    int getFault();
    int AXISCALL checkMessageBody(const AxisChar* pName, 
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
    /* Method used by wrappers to get a deserialized Array of complex types */
    Axis_Array AXISCALL getCmplxArray(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized Array of basic types */
    Axis_Array AXISCALL getBasicArray(XSDTYPE nType, const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized single 
     * object of complex type 
     */
    void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
    
    /* Methods used by wrappers to get a deserialized value of basic types */
    int AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    int AXISCALL getFaultDetail(char** ppcDetail);
    xsd__boolean AXISCALL getElementAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned int AXISCALL getElementAsUnsignedInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    short AXISCALL getElementAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned short AXISCALL getElementAsUnsignedShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    char AXISCALL getElementAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned char AXISCALL getElementAsUnsignedByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getElementAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getElementAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned long AXISCALL getElementAsUnsignedLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    float AXISCALL getElementAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace);
    double AXISCALL getElementAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace);
    double AXISCALL getElementAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getElementAsString(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getElementAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getElementAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__hexBinary AXISCALL getElementAsHexBinary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__base64Binary AXISCALL getElementAsBase64Binary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace);

    int AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__boolean AXISCALL getAttributeAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned int AXISCALL getAttributeAsUnsignedInt(const AxisChar* pName, 
        const AxisChar* pNamespace);
    short AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned short AXISCALL getAttributeAsUnsignedShort(const AxisChar* pName, 
        const AxisChar* pNamespace);
    char AXISCALL getAttributeAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned char AXISCALL getAttributeAsUnsignedByte(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getAttributeAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getAttributeAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned long AXISCALL getAttributeAsUnsignedLong(const AxisChar* pName, 
        const AxisChar* pNamespace);
    float AXISCALL getAttributeAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace);
    double AXISCALL getAttributeAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace);
    double AXISCALL getAttributeAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getAttributeAsString(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getAttributeAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* AXISCALL getAttributeAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__hexBinary AXISCALL getAttributeAsHexBinary(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__base64Binary AXISCALL getAttributeAsBase64Binary
        (const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace);
    
/*    void* CreateArray(XSDTYPE nType, int nSize); */
/*    void DeleteArray(Axis_Array* pArray , XSDTYPE nType); */
    void setStyle(AXIS_BINDING_STYLE nStyle){ m_nStyle = nStyle;};
    AXIS_BINDING_STYLE getStyle(){return m_nStyle;};    
    XSDTYPE getXSDType(const AnyElement* pElement);
    int AXISCALL getStatus(){return m_nStatus;};

private:
    int getElementForAttributes(const AxisChar* pName, 
        const AxisChar* pNamespace);
    xsd__base64Binary decodeFromBase64Binary(const AxisChar* pValue);
    xsd__hexBinary decodeFromHexBinary(const AxisChar* pValue);
};

#endif 

