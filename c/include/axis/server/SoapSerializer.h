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

#if !defined(_SOAPSERIALIZER_H____OF_AXIS_INCLUDED_)
#define _SOAPSERIALIZER_H____OF_AXIS_INCLUDED_

#include "IHandlerSoapSerializer.h"
#include "BasicTypeSerializer.h"
#include "AxisTime.h"
#include "Packet.h"
#include "WSDDDefines.h"
#include "SoapEnvVersions.h"

class SoapEnvelope;
class SoapHeader;
class SoapMethod;
class SoapBody;
class SoapFault;
class HeaderBlock;

#include <map>
using namespace std;

/**
 *  @class SoapSerializer
 *  @brief interface for the SoapSerializer class.
 *
 *
 *
 *  @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *  @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */

class SoapSerializer : public IHandlerSoapSerializer
{
    typedef struct
    {
        volatile unsigned char inuse;
        volatile char* buffer;
    } SerializeBuffers;
private:
    int m_nCounter;
    AxisChar m_Buf[8];
    SoapEnvelope* m_pSoapEnvelope;    
    int m_iSoapVersion;
    /* Current Serialization Style */
    AXIS_BINDING_STYLE m_nStyle;
    /* Table that keeps all allocated buffers */
    volatile SerializeBuffers* m_pSZBuffers;
    /* Size of the initial buffer created.*/
    int m_nInitialBufferSize;
    /* Size of the m_SZBuffers array.*/
    int m_nMaxBuffersToCreate;
    /* Maximum size of the buffer that is being filled */
    int m_nCurrentBufferSize;
    /* How much charators has been filled to the currently selected buffer */
    int m_nFilledSize;
    /* Currently selected buffer index*/
    int m_nCurrentBufferIndex;
    /* Overall status of Serializer. If anything goes wrong this is not 
     * AXIS_SUCCESS 
     */
    int m_nStatus;
    /* Map that contains pairs of currently available namespaces and 
     * prefixes 
     */ 
    map<AxisXMLString, AxisXMLString> m_NsStack;
    /* Provider type of current service that uses this Serializer object */
    PROVIDERTYPE m_ProviderType;
public:

    int setOutputStreamForTesting(SOAPTransport* pStream);

    int AXISCALL createSoapMethod(const AxisChar* sLocalName, 
        const AxisChar* sURI);

    int AXISCALL createSoapFault(const AxisChar* sLocalName, 
        const AxisChar* sURI);

/*    IWrapperSoapSerializer& operator<<(const char* cSerialized); */
    IWrapperSoapSerializer& operator<<(const AxisChar* cSerialized);
    /**
     * Returns the corrosponding namespace prefix.
     * @param pNamespace The namespace.
     * @return The corrosponding prefix.
     */
    const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace);
    /**
     * Returns the corrosponding namespace prefix. This method is 
     * called when the caller also wants to know whether this is a new 
     * namespace or not as appose to its overloaded other member.
     * @param pNamespace The namespace.
     * @param blnIsNewPrefix The boolean which behaves as 
     * a out parameter to indicate whether this is a new namespace or not.
     * @return The corrosponding prefix.
     */
    const AxisChar* AXISCALL getNamespacePrefix(const AxisChar* pNamespace,
        bool& blnIsNewPrefix);
    void AXISCALL removeNamespacePrefix(const AxisChar* pNamespace);
    int setSoapVersion(SOAP_VERSION);
    int init();
    int setOutputStream(SOAPTransport* pStream);
    void markEndOfStream();
    int setSoapMethod(SoapMethod* pSoapMethod);
    int setSoapFault(SoapFault* pSoapFault);
    int setSoapBody(SoapBody* pSoapBody);
    int setSoapHeader(SoapHeader* pSoapHeader);
    int setSoapEnvelope(SoapEnvelope* pSoapEnvelope);
    SoapSerializer();
    virtual ~SoapSerializer();

    /* for arrays of basic types */
    int AXISCALL addOutputBasicArrayParam(const Axis_Array* pArray, 
        XSDTYPE nType, const AxisChar* pName);

    /* for arrays of complex types */
    int AXISCALL addOutputCmplxArrayParam(const Axis_Array* pArray, 
        void* pSZFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace);

    /* for complex types */
    int AXISCALL addOutputCmplxParam(void* pObject, void* pSZFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);

    int AXISCALL addFaultDetail(void* pObject, void* pSZFunct,
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace );

    int AXISCALL serializeCmplxArray(const Axis_Array* pArray, void* pSZFunct,
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);

    int AXISCALL serializeBasicArray(const Axis_Array* pArray, XSDTYPE nType, 
        const AxisChar* pName);
    /* following two functions are needed by serializer functions of complex 
     * types for RPC style web services 
     */
    void AXISCALL serializeStartElementOfType(const AxisChar* pName, 
        const AxisChar* pNamespace, const AxisChar* pPrefix);
    void AXISCALL serializeEndElementOfType(const AxisChar* pName);
    PROVIDERTYPE getCurrentProviderType() { return m_ProviderType;};
    void setCurrentProviderType(PROVIDERTYPE nType) { m_ProviderType = nType;};

private:
    int sendSerializedBuffer();
    int setNextSerilizeBuffer();
    IArrayBean* makeArrayBean(XSDTYPE nType, void* pArray);
    IArrayBean* makeArrayBean(void* pObject, void* pSZFunct, void* pDelFunct, 
        void* pSizeFunct);

public: /* Basic Type Serializing methods */
    int removeSoapHeader();
    int setHeaderBlock(HeaderBlock* pHeaderBlock);
    IHeaderBlock* createHeaderBlock();
    
private:
    BasicTypeSerializer m_BTSZ;
    SOAPTransport* m_pOutputStream;
public:
	int setSOAPMethodAttribute(Attribute* pAttribute);
	SoapMethod* getSOAPMethod();
    IHeaderBlock* createHeaderBlock(AxisChar *pachLocalName, 
        AxisChar *pachPrefix, AxisChar *pachUri);
    /* to add a header block to the Serializer. Probably by a handler */
    int AXISCALL addHeaderBlock(IHeaderBlock* pBlk);
    int AXISCALL addOutputParam(const AxisChar* pchName, 
        void* pValue, XSDTYPE type);
    int AXISCALL serializeAsElement(const AxisChar* pchName, 
        void* pValue, XSDTYPE type);
    int AXISCALL serializeAsAttribute(const AxisChar* pName, 
        const AxisChar* pNamespace, void* pValue, XSDTYPE type);
    void AXISCALL serialize(const char* pFirst, ...);
    void setStyle(AXIS_BINDING_STYLE nStyle)
    { m_nStyle = nStyle; m_BTSZ.setStyle(nStyle);};
    AXIS_BINDING_STYLE getStyle(){return m_nStyle;};
    int AXISCALL setBodyAsHexBinary(xsd__hexBinary body);
    int AXISCALL setBodyAsBase64Binary(xsd__base64Binary body);
    const AxisChar* AXISCALL getBodyAsString();
	static void AXISCALL releaseBufferCallBack(const char* buffer, const void* bufferid);
	int serializeAnyObject(AnyType* pAnyObject);
};

#endif 


