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
 *
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */
 
/*
 * Revision 1.1  2004/05/24 samisa
 * Added accesser to transport 
 */
 
/*
 * Revision 1.2  2004/05/25 samisa
 * Added accesser to SOAP serializer 
 */

/*
 * Revision 1.3  2004/05/31 samisa
 * Added setProxy
 */



/* Call.h: interface for the Call class.*/


#if !defined(_CALL_H____OF_AXIS_INCLUDED_)
#define _CALL_H____OF_AXIS_INCLUDED_

#include "../server/AxisWrapperAPI.h"
#include "../server/SoapEnvVersions.h"
#include "../server/WSDDDefines.h"

#ifdef __cplusplus
#include "../server/IParam.h"
#include "../server/AxisEngine.h"
#include <list>
using namespace std;
class ClientAxisEngine;
class SOAPTransport;
#else
#include "../server/Packet.h"
#endif

#if defined(WIN32) 
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO 
#endif

typedef struct {
	void (AXISCALL* setSOAPVersion)(void* pObj, SOAP_VERSION version);
	int (AXISCALL* setTransportProperty)(void* pObj, 
        AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
	int (AXISCALL* setProtocol)(void* pObj, AXIS_PROTOCOL_TYPE protocol);
	int (AXISCALL* initialize)(void* pObj, PROVIDERTYPE nStyle, int secure);
	int (AXISCALL* invoke)(void* pObj);
	int (AXISCALL* unInitialize)(void* pObj);

	/* Method that set the remote method name */
	void (AXISCALL* setOperation)(void* pObj, const char* pchOperation, 
        const char* pchNamespace);
	int (AXISCALL* setEndpointURI)(void* pObj, const char* pchEndpointURI);

	/* Method for adding complex parameters */
	void (AXISCALL* addCmplxParameter)(void* pObj, void* pObject, 
        void* pSZFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
	/* Method for adding complex type array parameters */
	void (AXISCALL* addCmplxArrayParameter)(void* pObj, Axis_Array* pArray,
        void* pSZFunct, void* pDelFunct, void* pSizeFunct,
        const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding basic type array parameters */
	void (AXISCALL* addBasicArrayParameter)(void* pObj, Axis_Array* pArray,
        XSDTYPE nType, const char* pName);
	/* Method for adding parameters of basic types */
	void (AXISCALL* addParameter)(void* pObj, void* pValue,const char* pName,
        XSDTYPE nType);

	/* Methods used by stubs to get a deserialized value of an XML element 
     * as basic types 
     */
	int (AXISCALL* getElementAsInt)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
	xsd__boolean (AXISCALL* getElementAsBoolean)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* getElementAsUnsignedInt)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* getElementAsShort)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned short (AXISCALL* getElementAsUnsignedShort)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* getElementAsByte)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned char (AXISCALL* getElementAsUnsignedByte)(void* pObj,
        const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* getElementAsLong)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    long (AXISCALL* getElementAsInteger)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned long (AXISCALL* getElementAsUnsignedLong)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* getElementAsFloat)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    double (AXISCALL* getElementAsDouble)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    double (AXISCALL* getElementAsDecimal)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
	AxisChar* (AXISCALL* getElementAsString)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* (AXISCALL* getElementAsAnyURI)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    AxisChar* (AXISCALL* getElementAsQName)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
	xsd__hexBinary (AXISCALL* getElementAsHexBinary)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* getElementAsBase64Binary)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* getElementAsDateTime)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* getElementAsDate)(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace);
    struct tm (AXISCALL* getElementAsTime)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    long (AXISCALL* getElementAsDuration)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);

	/* Methods used by stubs to get a deserialized value of an XML attribute 
     * basic types 
     */
	int (AXISCALL* getAttributeAsInt)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
	xsd__boolean (AXISCALL* getAttributeAsBoolean)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* getAttributeAsUnsignedInt)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* getAttributeAsShort)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned short (AXISCALL* getAttributeAsUnsignedShort)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* getAttributeAsByte)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned char (AXISCALL* getAttributeAsUnsignedByte)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* getAttributeAsLong)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    long (AXISCALL* getAttributeAsInteger)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    unsigned long (AXISCALL* getAttributeAsUnsignedLong)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* getAttributeAsFloat)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    double (AXISCALL* getAttributeAsDouble)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    double (AXISCALL* getAttributeAsDecimal)(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace);
	AxisChar* (AXISCALL* getAttributeAsString)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* getAttributeAsAnyURI)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* getAttributeAsQName)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary (AXISCALL* getAttributeAsHexBinary)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* getAttributeAsBase64Binary)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* getAttributeAsDateTime)(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* getAttributeAsDate)(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace);
    struct tm (AXISCALL* getAttributeAsTime)(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace);
    long (AXISCALL* getAttributeAsDuration)(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace);

	/* Method used by stubs to get a deserialized value of complex types */
	void* (AXISCALL* getCmplxObject)(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of complex types */
	Axis_Array (AXISCALL* getCmplxArray)(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of basic types */
	Axis_Array (AXISCALL* getBasicArray)(void* pObj, XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace);

	int (AXISCALL* checkMessage)(void *pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);

	int (AXISCALL* checkFault)(void *pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
	
	/* Minimal error check */
	int (AXISCALL* getStatus)(void *pObj);
	AnyType* (AXISCALL* getAnyObject)(void *pObj);
	int (AXISCALL* addAnyObject)(void *pObj, AnyType* pAnyObject);

} CallFunctions;

#ifdef __cplusplus

class STORAGE_CLASS_INFO CallBase
{	
public:
	virtual void AXISCALL setSOAPVersion(SOAP_VERSION version)=0;
	virtual int AXISCALL setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE 
        type, const char* value)=0;
	virtual int AXISCALL setProtocol(AXIS_PROTOCOL_TYPE protocol)=0;
	virtual int AXISCALL initialize(PROVIDERTYPE nStyle, int secure)=0;
	virtual int AXISCALL invoke()=0;
	virtual int AXISCALL unInitialize()=0;

	/* Method that set the remote method name */
	virtual void AXISCALL setOperation(const char* pchOperation, 
        const char* pchNamespace)=0;
	virtual int AXISCALL setEndpointURI(const char* pchEndpointURI)=0;

	/* Method for adding complex parameters */
	virtual void AXISCALL addCmplxParameter(void* pObject, void* pSZFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method for adding complex type array parameters */
	virtual void AXISCALL addCmplxArrayParameter(Axis_Array* pArray, 
        void* pSZFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method for adding basic type array parameters */
	virtual void AXISCALL addBasicArrayParameter(Axis_Array* pArray, 
        XSDTYPE nType, const char* pName)=0;
	/* Method for adding parameters of basic types */
	virtual void AXISCALL addParameter(void* pValue,const char* pName, 
        XSDTYPE nType)=0;

	/* Methods used by stubs to get a deserialized value of an XML element 
     * as basic types 
     */
	virtual int AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL getElementAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL getElementAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL getElementAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL getElementAsUnsignedShort(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL getElementAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL getElementAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL getElementAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual long AXISCALL getElementAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL getElementAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL getElementAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual double AXISCALL getElementAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual double AXISCALL getElementAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL getElementAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL getElementAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL getElementAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual xsd__hexBinary AXISCALL getElementAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL getElementAsBase64Binary(const 
        AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual long AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

	/* Methods used by stubs to get a deserialized value of XML attribute 
     * as basic types 
     */
	virtual int AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL getAttributeAsBoolean(const AxisChar* pName,
        const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL getAttributeAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL getAttributeAsUnsignedShort(const 
        AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL getAttributeAsByte(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL getAttributeAsUnsignedByte(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL getAttributeAsLong(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual long AXISCALL getAttributeAsInteger(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL getAttributeAsUnsignedLong(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL getAttributeAsFloat(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual double AXISCALL getAttributeAsDouble(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual double AXISCALL getAttributeAsDecimal(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL getAttributeAsString(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL getAttributeAsAnyURI(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL getAttributeAsQName(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	virtual xsd__hexBinary AXISCALL getAttributeAsHexBinary(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL getAttributeAsBase64Binary(const 
        AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual long AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

	/* Method used by stubs to get a deserialized value of complex types */
	virtual void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method used by stubs to get a deserialized Array of complex types */
	virtual Axis_Array AXISCALL getCmplxArray(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
	/* Method used by stubs to get a deserialized Array of basic types */
	virtual Axis_Array AXISCALL getBasicArray(XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;

	virtual int AXISCALL checkMessage(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

	virtual int AXISCALL checkFault(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

	/* Minimal error check */
	virtual int AXISCALL getStatus()=0;
		
	virtual AnyType* AXISCALL getAnyObject()=0;
	virtual int AXISCALL addAnyObject(AnyType* pAnyObject)=0;

	/* following stuff is needed to provide the interface for C web services */
public:
	static CallFunctions ms_VFtable;
	static bool bInitialized;
	/* add static functions for all interface functions here */
	static void AXISCALL s_SetSOAPVersion(void* pObj, SOAP_VERSION version)
	{((CallBase*)pObj)->setSOAPVersion(version);};
	static int AXISCALL s_SetTransportProperty(void* pObj, 
        AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
	{ return ((CallBase*)pObj)->setTransportProperty(type,value);};
	static int AXISCALL s_SetProtocol(void* pObj, AXIS_PROTOCOL_TYPE protocol)
	{ return ((CallBase*)pObj)->setProtocol(protocol);};
	static int AXISCALL s_InitializeCall(void* pObj, PROVIDERTYPE nStyle, 
        int secure)
	{ return ((CallBase*)pObj)->initialize(nStyle, secure);};
	static int AXISCALL s_Invoke(void* pObj)
	{ return ((CallBase*)pObj)->invoke();};
	static int AXISCALL s_UnInitialize(void* pObj)
	{ return ((CallBase*)pObj)->unInitialize();};

	/* Method that set the remote method name */
	static void AXISCALL s_SetOperation(void* pObj, const char* pchOperation, 
        const char* pchNamespace)
	{ ((CallBase*)pObj)->setOperation(pchOperation, pchNamespace);};
	static int AXISCALL s_SetEndpointURI(void* pObj, 
        const char* pchEndpointURI)
	{ return ((CallBase*)pObj)->setEndpointURI(pchEndpointURI);};

	static void AXISCALL s_AddParameter(void* pObj, void* pValue, 
        const AxisChar* pchName, XSDTYPE type)
	{ ((CallBase*)pObj)->addParameter(pValue, pchName, type);};
	static void AXISCALL s_AddCmplxArrayParameter(void* pObj, 
        Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct,
        const AxisChar* pName, const AxisChar* pNamespace)
	{ ((CallBase*)pObj)->addCmplxArrayParameter(pArray, pSZFunct, pDelFunct, 
    pSizeFunct, pName, pNamespace);};
	static void AXISCALL s_AddBasicArrayParameter(void* pObj, 
        Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ ((CallBase*)pObj)->addBasicArrayParameter(pArray, nType, pName);};
	static void AXISCALL s_AddCmplxParameter(void* pObj, void* pObject, 
        void* pDZFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{ ((CallBase*)pObj)->addCmplxParameter(pObject, pDZFunct, pDelFunct, pName,
    pNamespace);};

	static int AXISCALL s_GetElementAsInt(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetElementAsBoolean(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetElementAsUnsignedInt(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetElementAsShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetElementAsUnsignedShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsUnsignedShort(pName, pNamespace);};
    static char AXISCALL s_GetElementAsByte(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetElementAsUnsignedByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsUnsignedByte(pName, pNamespace);};
    static long AXISCALL s_GetElementAsLong(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsLong(pName, pNamespace);};
    static long AXISCALL s_GetElementAsInteger(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetElementAsUnsignedLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsUnsignedLong(pName, pNamespace);};
	static float AXISCALL s_GetElementAsFloat(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDouble(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDecimal(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsDouble(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetElementAsString(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsAnyURI(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsQName(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetElementAsHexBinary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetElementAsBase64Binary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsBase64Binary(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDateTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDate(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsTime(pName, pNamespace);};
    static long AXISCALL s_GetElementAsDuration(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getElementAsDuration(pName, pNamespace);};

	static int AXISCALL s_GetAttributeAsInt(void* pObj, const AxisChar* pName,
        const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetAttributeAsBoolean(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetAttributeAsUnsignedInt(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetAttributeAsShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetAttributeAsUnsignedShort(void* pObj,
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsUnsignedShort(pName, 
    pNamespace);};
    static char AXISCALL s_GetAttributeAsByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetAttributeAsUnsignedByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsUnsignedByte(pName, 
    pNamespace);};
    static long AXISCALL s_GetAttributeAsLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsLong(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsInteger(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetAttributeAsUnsignedLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsUnsignedLong(pName, 
    pNamespace);};
	static float AXISCALL s_GetAttributeAsFloat(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDouble(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDecimal(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsDecimal(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetAttributeAsString(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsAnyURI(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsQName(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetAttributeAsHexBinary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetAttributeAsBase64Binary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsBase64Binary(pName, 
    pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDateTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDate(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsTime(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsDuration(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->getAttributeAsDuration(pName, pNamespace);};

	static Axis_Array AXISCALL s_GetCmplxArray(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->getCmplxArray(pDZFunct, pCreFunct, pDelFunct,
    pSizeFunct, pName, pNamespace);};
	static Axis_Array AXISCALL s_GetBasicArray(void* pObj, XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->getBasicArray(nType, pName, pNamespace);};
	static void* AXISCALL s_GetCmplxObject(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->getCmplxObject(pDZFunct, pCreFunct, pDelFunct, 
    pName, pNamespace);};

	static int AXISCALL s_CheckMessage(void *pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->checkMessage(pName, pNamespace);};

	static int AXISCALL s_CheckFault(void *pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->checkFault(pName, pNamespace);};
	
	/* Minimal error check */
	static int AXISCALL s_GetStatus(void *pObj)
	{return ((CallBase*)pObj)->getStatus();};

	static AnyType* AXISCALL s_GetAnyObject(void *pObj)
	{return ((CallBase*)pObj)->getAnyObject();};
	static int AXISCALL s_AddAnyObject(void *pObj, AnyType* pAnyObject)
	{return ((CallBase*)pObj)->addAnyObject(pAnyObject);};

	/* and populate ms_VFtable with corresponding entry */
	static void s_Initialize()
	{	
		if (bInitialized) return;
		bInitialized = true;
		ms_VFtable.setSOAPVersion = s_SetSOAPVersion;
		ms_VFtable.setTransportProperty = s_SetTransportProperty;
		ms_VFtable.setProtocol = s_SetProtocol;
		ms_VFtable.initialize = s_InitializeCall;
		ms_VFtable.invoke = s_Invoke;
		ms_VFtable.unInitialize = s_UnInitialize;
		ms_VFtable.setOperation = s_SetOperation;
		ms_VFtable.setEndpointURI = s_SetEndpointURI;
		ms_VFtable.addParameter = s_AddParameter;
		ms_VFtable.addCmplxArrayParameter = s_AddCmplxArrayParameter;
		ms_VFtable.addBasicArrayParameter = s_AddBasicArrayParameter;
		ms_VFtable.addCmplxParameter = s_AddCmplxParameter;
		ms_VFtable.getCmplxArray = s_GetCmplxArray;
		ms_VFtable.getBasicArray = s_GetBasicArray;
		ms_VFtable.getCmplxObject = s_GetCmplxObject;
		ms_VFtable.getElementAsInt = s_GetElementAsInt;
		ms_VFtable.getElementAsBoolean = s_GetElementAsBoolean;
		ms_VFtable.getElementAsUnsignedInt = s_GetElementAsUnsignedInt;
		ms_VFtable.getElementAsShort = s_GetElementAsShort;
		ms_VFtable.getElementAsUnsignedShort = s_GetElementAsUnsignedShort;
		ms_VFtable.getElementAsByte = s_GetElementAsByte;
		ms_VFtable.getElementAsUnsignedByte = s_GetElementAsUnsignedByte;
		ms_VFtable.getElementAsLong = s_GetElementAsLong;
		ms_VFtable.getElementAsInteger = s_GetElementAsInteger;
		ms_VFtable.getElementAsUnsignedLong = s_GetElementAsUnsignedLong;
		ms_VFtable.getElementAsFloat = s_GetElementAsFloat;
		ms_VFtable.getElementAsDouble = s_GetElementAsDouble;
		ms_VFtable.getElementAsDecimal = s_GetElementAsDecimal;
		ms_VFtable.getElementAsString = s_GetElementAsString;
		ms_VFtable.getElementAsAnyURI = s_GetElementAsAnyURI;
		ms_VFtable.getElementAsQName = s_GetElementAsQName;
		ms_VFtable.getElementAsHexBinary = s_GetElementAsHexBinary;
		ms_VFtable.getElementAsBase64Binary = s_GetElementAsBase64Binary;
		ms_VFtable.getElementAsDateTime = s_GetElementAsDateTime;
		ms_VFtable.getElementAsDate = s_GetElementAsDate;
		ms_VFtable.getElementAsTime = s_GetElementAsTime;
		ms_VFtable.getElementAsDuration = s_GetElementAsDuration;
		ms_VFtable.getAttributeAsInt = s_GetAttributeAsInt;
		ms_VFtable.getAttributeAsBoolean = s_GetAttributeAsBoolean;
		ms_VFtable.getAttributeAsUnsignedInt = s_GetAttributeAsUnsignedInt;
		ms_VFtable.getAttributeAsShort = s_GetAttributeAsShort;
		ms_VFtable.getAttributeAsUnsignedShort = s_GetAttributeAsUnsignedShort;
		ms_VFtable.getAttributeAsByte = s_GetAttributeAsByte;
		ms_VFtable.getAttributeAsUnsignedByte = s_GetAttributeAsUnsignedByte;
		ms_VFtable.getAttributeAsLong = s_GetAttributeAsLong;
		ms_VFtable.getAttributeAsInteger = s_GetAttributeAsInteger;
		ms_VFtable.getAttributeAsUnsignedLong = s_GetAttributeAsUnsignedLong;
		ms_VFtable.getAttributeAsFloat = s_GetAttributeAsFloat;
		ms_VFtable.getAttributeAsDouble = s_GetAttributeAsDouble;
		ms_VFtable.getAttributeAsDecimal = s_GetAttributeAsDecimal;
		ms_VFtable.getAttributeAsString = s_GetAttributeAsString;
		ms_VFtable.getAttributeAsAnyURI = s_GetAttributeAsAnyURI;
		ms_VFtable.getAttributeAsQName = s_GetAttributeAsQName;
		ms_VFtable.getAttributeAsHexBinary = s_GetAttributeAsHexBinary;
		ms_VFtable.getAttributeAsBase64Binary = s_GetAttributeAsBase64Binary;
		ms_VFtable.getAttributeAsDateTime = s_GetAttributeAsDateTime;
		ms_VFtable.getAttributeAsDate = s_GetAttributeAsDate;
		ms_VFtable.getAttributeAsTime = s_GetAttributeAsTime;
		ms_VFtable.getAttributeAsDuration = s_GetAttributeAsDuration;
		ms_VFtable.checkMessage = s_CheckMessage;
		ms_VFtable.checkFault = s_CheckFault;
		ms_VFtable.getStatus = s_GetStatus;
		ms_VFtable.getAnyObject = s_GetAnyObject;
		ms_VFtable.addAnyObject = s_AddAnyObject;
	}
};

/* A separate call class object should be used by each thread */
class STORAGE_CLASS_INFO Call : public CallBase
{
public:
	Call();
	virtual ~Call();
	void AXISCALL setSOAPVersion(SOAP_VERSION version);
	int AXISCALL setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type,
        const char* value);
	int AXISCALL setProtocol(AXIS_PROTOCOL_TYPE protocol);
	int AXISCALL unInitialize();
	int AXISCALL initialize(PROVIDERTYPE nStyle, int secure);
	int AXISCALL invoke();

	/* Method for adding complex parameters */
	void AXISCALL addCmplxParameter(void* pObject, void* pSZFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding complex type array parameters */
	void AXISCALL addCmplxArrayParameter(Axis_Array* pArray, void* pSZFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
	/* Method for adding basic type array parameters */
	void AXISCALL addBasicArrayParameter(Axis_Array* pArray, XSDTYPE nType, 
        const AxisChar* pName);
	/* Method for adding parameters of basic types */
	void AXISCALL addParameter(void* pValue,const char* pchName, 
        XSDTYPE nType);

	/* Method that set the remote method name */
	void AXISCALL setOperation(const char* pchOperation, 
        const char* pchNamespace);
	int AXISCALL setEndpointURI(const char* pchEndpointURI);
public:
	IHeaderBlock* createHeaderBlock(AxisChar *pachLocalName, 
        AxisChar *pachPrefix, AxisChar *pachUri);
	IHeaderBlock* createHeaderBlock();
	int setSoapHeader(SoapHeader *pSoapHeader);
	/* Methods used by stubs to get a deserialized value of XML element 
     * as basic types 
     */
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

	/* Methods used by stubs to get a deserialized value of a XML attribute 
     * as basic types 
     */
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
	xsd__base64Binary AXISCALL getAttributeAsBase64Binary(const AxisChar* 
        pName, const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace);
    struct tm AXISCALL getAttributeAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace);
    long AXISCALL getAttributeAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace);

	/* Method used by stubs to get a deserialized value of complex types */
	void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of complex types */
	Axis_Array AXISCALL getCmplxArray(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of basic types */
	Axis_Array AXISCALL getBasicArray(XSDTYPE nType, const AxisChar* pName, 
        const AxisChar* pNamespace);

	int AXISCALL checkMessage(const AxisChar* pName, 
        const AxisChar* pNamespace);
  
	int AXISCALL checkFault(const AxisChar* pName, 
        const AxisChar* pNamespace);

	int AXISCALL getStatus();
	
	SOAPTransport* getTransport() { return m_pTransport; }
	SoapSerializer* getSOAPSerializer() { return (SoapSerializer*)m_pIWSSZ; }
	
  /**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy(const char* pcProxyHost, unsigned int uiProxyPort); 

	AnyType* AXISCALL getAnyObject();
	int AXISCALL addAnyObject(AnyType* pAnyObject);
		
private:
	int openConnection(int secure);
	void closeConnection();
	int makeArray();

private:
	ClientAxisEngine* m_pAxisEngine;
	/* 
	   Following are pointers to relevant objects of the ClientAxisEngine
	   instance. So they do not belong to this object and are not created 
       or deleted 
	 */
	MessageData* m_pMsgData;
	IHandlerSoapSerializer* m_pIWSSZ;
	IHandlerSoapDeSerializer* m_pIWSDZ;
	/* 
	   m_Soap contains transport related information and function pointers 
	   to manipulate transport layer.
	 */
	//Ax_soapstream m_Soap;
	const char* m_pcEndPointUri;
	AXIS_PROTOCOL_TYPE m_nTransportType;
	/*
	   Transport object
	 */
	SOAPTransport* m_pTransport;
	
	/* Minimal error check */
	int m_nStatus;
  /**
    * Proxy server name.
    */
    std::string m_strProxyHost;
  /**
    * Proxy server port.
    */
    unsigned int m_uiProxyPort;
  /**
    * Use Proxy or not?
    */
    bool m_bUseProxy;

};

#endif

typedef struct { 
	void* _object; /* this will be C++ Call Object */
	CallFunctions* _functions; /* this is the static function table */
} Call_C;

#ifdef __cplusplus
extern "C" { 
#endif
STORAGE_CLASS_INFO void* getStubObject(AXIS_PROTOCOL_TYPE nProtocol, 
                                       AxisChar* pchEndpointURI); 
STORAGE_CLASS_INFO void destroyStubObject(void* pCall); 
#ifdef __cplusplus
} 
#endif

#ifndef __cplusplus
typedef Call_C Call; 
#endif

#endif
