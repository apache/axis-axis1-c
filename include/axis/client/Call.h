/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

/* Call.h: interface for the Call class.*/


#if !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)
#define AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_

#include "../server/AxisWrapperAPI.h"
#include "../server/SoapEnvVersions.h"
#include "../server/WSDDDefines.h"

#ifdef __cplusplus
#include "../server/IParam.h"
#include "../server/AxisEngine.h"
#include <list>
using namespace std;
class ClientAxisEngine;
class AxisTransport;
#else
#include "../server/Packet.h"
#endif

#if defined(WIN32) 
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO 
#endif

typedef struct {
	void (AXISCALL* SetSOAPVersion)(void* pObj, SOAP_VERSION version);
	int (AXISCALL* SetTransportProperty)(void* pObj, AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
	int (AXISCALL* SetProtocol)(void* pObj, AXIS_PROTOCOL_TYPE protocol);
	int (AXISCALL* Initialize)(void* pObj, PROVIDERTYPE nStyle, int secure);
	int (AXISCALL* Invoke)(void* pObj);
	int (AXISCALL* UnInitialize)(void* pObj);

	/* Method that set the remote method name */
	void (AXISCALL* SetOperation)(void* pObj, const char* pchOperation, const char* pchNamespace);
	int (AXISCALL* SetEndpointURI)(void* pObj, const char* pchEndpointURI);

	/* Method for adding complex parameters */
	void (AXISCALL* AddCmplxParameter)(void* pObj, void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding complex type array parameters */
	void (AXISCALL* AddCmplxArrayParameter)(void* pObj, Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding basic type array parameters */
	void (AXISCALL* AddBasicArrayParameter)(void* pObj, Axis_Array* pArray, XSDTYPE nType, const char* pName);
	/* Method for adding parameters of basic types */
	void (AXISCALL* AddParameter)(void* pObj, void* pValue,const char* pName, XSDTYPE nType);

	/* Methods used by stubs to get a deserialized value of an XML element as basic types */
	int (AXISCALL* GetElementAsInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean (AXISCALL* GetElementAsBoolean)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* GetElementAsUnsignedInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* GetElementAsShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short (AXISCALL* GetElementAsUnsignedShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* GetElementAsByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char (AXISCALL* GetElementAsUnsignedByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsInteger)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long (AXISCALL* GetElementAsUnsignedLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* GetElementAsFloat)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetElementAsDouble)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetElementAsDecimal)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetElementAsString)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetElementAsAnyURI)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetElementAsQName)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary (AXISCALL* GetElementAsHexBinary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* GetElementAsBase64Binary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDateTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsDate)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetElementAsTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetElementAsDuration)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);

	/* Methods used by stubs to get a deserialized value of an XML attribute basic types */
	int (AXISCALL* GetAttributeAsInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean (AXISCALL* GetAttributeAsBoolean)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int (AXISCALL* GetAttributeAsUnsignedInt)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    short (AXISCALL* GetAttributeAsShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short (AXISCALL* GetAttributeAsUnsignedShort)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    char (AXISCALL* GetAttributeAsByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char (AXISCALL* GetAttributeAsUnsignedByte)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsInteger)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long (AXISCALL* GetAttributeAsUnsignedLong)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	float (AXISCALL* GetAttributeAsFloat)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetAttributeAsDouble)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    double (AXISCALL* GetAttributeAsDecimal)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* (AXISCALL* GetAttributeAsString)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetAttributeAsAnyURI)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* (AXISCALL* GetAttributeAsQName)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary (AXISCALL* GetAttributeAsHexBinary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary (AXISCALL* GetAttributeAsBase64Binary)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsDateTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsDate)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    struct tm (AXISCALL* GetAttributeAsTime)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);
    long (AXISCALL* GetAttributeAsDuration)(void* pObj, const AxisChar* pName, const AxisChar* pNamespace);

	/* Method used by stubs to get a deserialized value of complex types */
	void* (AXISCALL* GetCmplxObject)(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of complex types */
	Axis_Array (AXISCALL* GetCmplxArray)(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of basic types */
	Axis_Array (AXISCALL* GetBasicArray)(void* pObj, XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace);

	int (AXISCALL* CheckMessage)(void *pObj, const AxisChar* pName, const AxisChar* pNamespace);
} CallFunctions;

#ifdef __cplusplus

class STORAGE_CLASS_INFO CallBase
{	
public:
	virtual void AXISCALL SetSOAPVersion(SOAP_VERSION version)=0;
	virtual int AXISCALL SetTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)=0;
	virtual int AXISCALL SetProtocol(AXIS_PROTOCOL_TYPE protocol)=0;
	virtual int AXISCALL Initialize(PROVIDERTYPE nStyle, int secure)=0;
	virtual int AXISCALL Invoke()=0;
	virtual int AXISCALL UnInitialize()=0;

	/* Method that set the remote method name */
	virtual void AXISCALL SetOperation(const char* pchOperation, const char* pchNamespace)=0;
	virtual int AXISCALL SetEndpointURI(const char* pchEndpointURI)=0;

	/* Method for adding complex parameters */
	virtual void AXISCALL AddCmplxParameter(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method for adding complex type array parameters */
	virtual void AXISCALL AddCmplxArrayParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method for adding basic type array parameters */
	virtual void AXISCALL AddBasicArrayParameter(Axis_Array* pArray, XSDTYPE nType, const char* pName)=0;
	/* Method for adding parameters of basic types */
	virtual void AXISCALL AddParameter(void* pValue,const char* pName, XSDTYPE nType)=0;

	/* Methods used by stubs to get a deserialized value of an XML element as basic types */
	virtual int AXISCALL GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL GetElementAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__hexBinary AXISCALL GetElementAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL GetElementAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace)=0;

	/* Methods used by stubs to get a deserialized value of XML attribute as basic types */
	virtual int AXISCALL GetAttributeAsInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__boolean AXISCALL GetAttributeAsBoolean(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL GetAttributeAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL GetAttributeAsShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL GetAttributeAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual char AXISCALL GetAttributeAsByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned char AXISCALL GetAttributeAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsInteger(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual unsigned long AXISCALL GetAttributeAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual float AXISCALL GetAttributeAsFloat(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetAttributeAsDouble(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual double AXISCALL GetAttributeAsDecimal(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual AxisChar* AXISCALL GetAttributeAsString(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetAttributeAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual AxisChar* AXISCALL GetAttributeAsQName(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__hexBinary AXISCALL GetAttributeAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace)=0;
	virtual xsd__base64Binary AXISCALL GetAttributeAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsDateTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsDate(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL GetAttributeAsTime(const AxisChar* pName, const AxisChar* pNamespace)=0;
    virtual long AXISCALL GetAttributeAsDuration(const AxisChar* pName, const AxisChar* pNamespace)=0;

	/* Method used by stubs to get a deserialized value of complex types */
	virtual void* AXISCALL GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method used by stubs to get a deserialized Array of complex types */
	virtual Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* Method used by stubs to get a deserialized Array of basic types */
	virtual Axis_Array AXISCALL GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)=0;

	virtual int AXISCALL CheckMessage(const AxisChar* pName, const AxisChar* pNamespace)=0;
	/* following stuff is needed to provide the interface for C web services */
public:
	static CallFunctions ms_VFtable;
	static bool bInitialized;
	/* add static functions for all interface functions here */
	static void AXISCALL s_SetSOAPVersion(void* pObj, SOAP_VERSION version)
	{((CallBase*)pObj)->SetSOAPVersion(version);};
	static int AXISCALL s_SetTransportProperty(void* pObj, AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
	{ return ((CallBase*)pObj)->SetTransportProperty(type,value);};
	static int AXISCALL s_SetProtocol(void* pObj, AXIS_PROTOCOL_TYPE protocol)
	{ return ((CallBase*)pObj)->SetProtocol(protocol);};
	static int AXISCALL s_Initialize(void* pObj, PROVIDERTYPE nStyle, int secure)
	{ return ((CallBase*)pObj)->Initialize(nStyle, secure);};
	static int AXISCALL s_Invoke(void* pObj)
	{ return ((CallBase*)pObj)->Invoke();};
	static int AXISCALL s_UnInitialize(void* pObj)
	{ return ((CallBase*)pObj)->UnInitialize();};

	/* Method that set the remote method name */
	static void AXISCALL s_SetOperation(void* pObj, const char* pchOperation, const char* pchNamespace)
	{ ((CallBase*)pObj)->SetOperation(pchOperation, pchNamespace);};
	static int AXISCALL s_SetEndpointURI(void* pObj, const char* pchEndpointURI)
	{ return ((CallBase*)pObj)->SetEndpointURI(pchEndpointURI);};

	static void AXISCALL s_AddParameter(void* pObj, void* pValue, const AxisChar* pchName, XSDTYPE type)
	{ ((CallBase*)pObj)->AddParameter(pValue, pchName, type);};
	static void AXISCALL s_AddCmplxArrayParameter(void* pObj, Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ ((CallBase*)pObj)->AddCmplxArrayParameter(pArray, pSZFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static void AXISCALL s_AddBasicArrayParameter(void* pObj, Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName)
	{ ((CallBase*)pObj)->AddBasicArrayParameter(pArray, nType, pName);};
	static void AXISCALL s_AddCmplxParameter(void* pObj, void* pObject, void* pDZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{ ((CallBase*)pObj)->AddCmplxParameter(pObject, pDZFunct, pDelFunct, pName, pNamespace);};

	static int AXISCALL s_GetElementAsInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetElementAsBoolean(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetElementAsUnsignedInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetElementAsShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetElementAsUnsignedShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsUnsignedShort(pName, pNamespace);};
    static char AXISCALL s_GetElementAsByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetElementAsUnsignedByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsUnsignedByte(pName, pNamespace);};
    static long AXISCALL s_GetElementAsLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsLong(pName, pNamespace);};
    static long AXISCALL s_GetElementAsInteger(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetElementAsUnsignedLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsUnsignedLong(pName, pNamespace);};
	static float AXISCALL s_GetElementAsFloat(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDouble(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetElementAsDecimal(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsDouble(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetElementAsString(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsAnyURI(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsQName(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetElementAsHexBinary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetElementAsBase64Binary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsBase64Binary(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDateTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsDate(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetElementAsTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsTime(pName, pNamespace);};
    static long AXISCALL s_GetElementAsDuration(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetElementAsDuration(pName, pNamespace);};

	static int AXISCALL s_GetAttributeAsInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsInt(pName, pNamespace);};
	static xsd__boolean AXISCALL s_GetAttributeAsBoolean(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsBoolean(pName, pNamespace);};
    static unsigned int AXISCALL s_GetAttributeAsUnsignedInt(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsUnsignedInt(pName, pNamespace);};
    static short AXISCALL s_GetAttributeAsShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsShort(pName, pNamespace);};
    static unsigned short AXISCALL s_GetAttributeAsUnsignedShort(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsUnsignedShort(pName, pNamespace);};
    static char AXISCALL s_GetAttributeAsByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsByte(pName, pNamespace);};
    static unsigned char AXISCALL s_GetAttributeAsUnsignedByte(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsUnsignedByte(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsLong(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsInteger(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsInteger(pName, pNamespace);};
    static unsigned long AXISCALL s_GetAttributeAsUnsignedLong(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsUnsignedLong(pName, pNamespace);};
	static float AXISCALL s_GetAttributeAsFloat(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsFloat(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDouble(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsDouble(pName, pNamespace);};
    static double AXISCALL s_GetAttributeAsDecimal(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsDecimal(pName, pNamespace);};
	static AxisChar* AXISCALL s_GetAttributeAsString(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsString(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsAnyURI(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsAnyURI(pName, pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsQName(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsQName(pName, pNamespace);};
	static xsd__hexBinary AXISCALL s_GetAttributeAsHexBinary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsHexBinary(pName, pNamespace);};
	static xsd__base64Binary AXISCALL s_GetAttributeAsBase64Binary(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsBase64Binary(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDateTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsDateTime(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDate(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsDate(pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsTime(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsTime(pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsDuration(void* pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{ return ((CallBase*)pObj)->GetAttributeAsDuration(pName, pNamespace);};

	static Axis_Array AXISCALL s_GetCmplxArray(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->GetCmplxArray(pDZFunct, pCreFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
	static Axis_Array AXISCALL s_GetBasicArray(void* pObj, XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->GetBasicArray(nType, pName, pNamespace);};
	static void* AXISCALL s_GetCmplxObject(void* pObj, void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->GetCmplxObject(pDZFunct, pCreFunct, pDelFunct, pName, pNamespace);};

	static int AXISCALL s_CheckMessage(void *pObj, const AxisChar* pName, const AxisChar* pNamespace)
	{return ((CallBase*)pObj)->CheckMessage(pName, pNamespace);};

	/* and populate ms_VFtable with corresponding entry */
	static void s_Initialize()
	{	
		if (bInitialized) return;
		bInitialized = true;
		ms_VFtable.SetSOAPVersion = s_SetSOAPVersion;
		ms_VFtable.SetTransportProperty = s_SetTransportProperty;
		ms_VFtable.SetProtocol = s_SetProtocol;
		ms_VFtable.Initialize = s_Initialize;
		ms_VFtable.Invoke = s_Invoke;
		ms_VFtable.UnInitialize = s_UnInitialize;
		ms_VFtable.SetOperation = s_SetOperation;
		ms_VFtable.SetEndpointURI = s_SetEndpointURI;
		ms_VFtable.AddParameter = s_AddParameter;
		ms_VFtable.AddCmplxArrayParameter = s_AddCmplxArrayParameter;
		ms_VFtable.AddBasicArrayParameter = s_AddBasicArrayParameter;
		ms_VFtable.AddCmplxParameter = s_AddCmplxParameter;
		ms_VFtable.GetCmplxArray = s_GetCmplxArray;
		ms_VFtable.GetBasicArray = s_GetBasicArray;
		ms_VFtable.GetCmplxObject = s_GetCmplxObject;
		ms_VFtable.GetElementAsInt = s_GetElementAsInt;
		ms_VFtable.GetElementAsBoolean = s_GetElementAsBoolean;
		ms_VFtable.GetElementAsUnsignedInt = s_GetElementAsUnsignedInt;
		ms_VFtable.GetElementAsShort = s_GetElementAsShort;
		ms_VFtable.GetElementAsUnsignedShort = s_GetElementAsUnsignedShort;
		ms_VFtable.GetElementAsByte = s_GetElementAsByte;
		ms_VFtable.GetElementAsUnsignedByte = s_GetElementAsUnsignedByte;
		ms_VFtable.GetElementAsLong = s_GetElementAsLong;
		ms_VFtable.GetElementAsInteger = s_GetElementAsInteger;
		ms_VFtable.GetElementAsUnsignedLong = s_GetElementAsUnsignedLong;
		ms_VFtable.GetElementAsFloat = s_GetElementAsFloat;
		ms_VFtable.GetElementAsDouble = s_GetElementAsDouble;
		ms_VFtable.GetElementAsDecimal = s_GetElementAsDecimal;
		ms_VFtable.GetElementAsString = s_GetElementAsString;
		ms_VFtable.GetElementAsAnyURI = s_GetElementAsAnyURI;
		ms_VFtable.GetElementAsQName = s_GetElementAsQName;
		ms_VFtable.GetElementAsHexBinary = s_GetElementAsHexBinary;
		ms_VFtable.GetElementAsBase64Binary = s_GetElementAsBase64Binary;
		ms_VFtable.GetElementAsDateTime = s_GetElementAsDateTime;
		ms_VFtable.GetElementAsDate = s_GetElementAsDate;
		ms_VFtable.GetElementAsTime = s_GetElementAsTime;
		ms_VFtable.GetElementAsDuration = s_GetElementAsDuration;
		ms_VFtable.GetAttributeAsInt = s_GetAttributeAsInt;
		ms_VFtable.GetAttributeAsBoolean = s_GetAttributeAsBoolean;
		ms_VFtable.GetAttributeAsUnsignedInt = s_GetAttributeAsUnsignedInt;
		ms_VFtable.GetAttributeAsShort = s_GetAttributeAsShort;
		ms_VFtable.GetAttributeAsUnsignedShort = s_GetAttributeAsUnsignedShort;
		ms_VFtable.GetAttributeAsByte = s_GetAttributeAsByte;
		ms_VFtable.GetAttributeAsUnsignedByte = s_GetAttributeAsUnsignedByte;
		ms_VFtable.GetAttributeAsLong = s_GetAttributeAsLong;
		ms_VFtable.GetAttributeAsInteger = s_GetAttributeAsInteger;
		ms_VFtable.GetAttributeAsUnsignedLong = s_GetAttributeAsUnsignedLong;
		ms_VFtable.GetAttributeAsFloat = s_GetAttributeAsFloat;
		ms_VFtable.GetAttributeAsDouble = s_GetAttributeAsDouble;
		ms_VFtable.GetAttributeAsDecimal = s_GetAttributeAsDecimal;
		ms_VFtable.GetAttributeAsString = s_GetAttributeAsString;
		ms_VFtable.GetAttributeAsAnyURI = s_GetAttributeAsAnyURI;
		ms_VFtable.GetAttributeAsQName = s_GetAttributeAsQName;
		ms_VFtable.GetAttributeAsHexBinary = s_GetAttributeAsHexBinary;
		ms_VFtable.GetAttributeAsBase64Binary = s_GetAttributeAsBase64Binary;
		ms_VFtable.GetAttributeAsDateTime = s_GetAttributeAsDateTime;
		ms_VFtable.GetAttributeAsDate = s_GetAttributeAsDate;
		ms_VFtable.GetAttributeAsTime = s_GetAttributeAsTime;
		ms_VFtable.GetAttributeAsDuration = s_GetAttributeAsDuration;
		ms_VFtable.CheckMessage = s_CheckMessage;
	}
};

/* A separate call class object should be used by each thread */
class STORAGE_CLASS_INFO Call : public CallBase
{
public:
	virtual ~Call();
	void AXISCALL SetSOAPVersion(SOAP_VERSION version);
	int AXISCALL SetTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
	int AXISCALL SetProtocol(AXIS_PROTOCOL_TYPE protocol);
	int AXISCALL UnInitialize();
	int AXISCALL Initialize(PROVIDERTYPE nStyle, int secure);
	int AXISCALL Invoke();

	/* Method for adding complex parameters */
	void AXISCALL AddCmplxParameter(void* pObject, void* pSZFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding complex type array parameters */
	void AXISCALL AddCmplxArrayParameter(Axis_Array* pArray, void* pSZFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method for adding basic type array parameters */
	void AXISCALL AddBasicArrayParameter(Axis_Array* pArray, XSDTYPE nType, const AxisChar* pName);
	/* Method for adding parameters of basic types */
	void AXISCALL AddParameter(void* pValue,const char* pchName, XSDTYPE nType);

	/* Method that set the remote method name */
	void AXISCALL SetOperation(const char* pchOperation, const char* pchNamespace);
	int AXISCALL SetEndpointURI(const char* pchEndpointURI);
	Call();
public:
	IHeaderBlock* createHeaderBlock(AxisChar *pachLocalName, AxisChar *pachPrefix, AxisChar *pachUri);
	IHeaderBlock* createHeaderBlock();
	int SetSoapHeader(SoapHeader *pSoapHeader);
	/* Methods used by stubs to get a deserialized value of XML element as basic types */
	int AXISCALL GetElementAsInt(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean AXISCALL GetElementAsBoolean(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int AXISCALL GetElementAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace);
    short AXISCALL GetElementAsShort(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short AXISCALL GetElementAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace);
    char AXISCALL GetElementAsByte(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char AXISCALL GetElementAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsLong(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsInteger(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long AXISCALL GetElementAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace);
	float AXISCALL GetElementAsFloat(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetElementAsDouble(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetElementAsDecimal(const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* AXISCALL GetElementAsString(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetElementAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetElementAsQName(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary AXISCALL GetElementAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary AXISCALL GetElementAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsDateTime(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsDate(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetElementAsTime(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetElementAsDuration(const AxisChar* pName, const AxisChar* pNamespace);

	/* Methods used by stubs to get a deserialized value of a XML attribute as basic types */
	int AXISCALL GetAttributeAsInt(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__boolean AXISCALL GetAttributeAsBoolean(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned int AXISCALL GetAttributeAsUnsignedInt(const AxisChar* pName, const AxisChar* pNamespace);
    short AXISCALL GetAttributeAsShort(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned short AXISCALL GetAttributeAsUnsignedShort(const AxisChar* pName, const AxisChar* pNamespace);
    char AXISCALL GetAttributeAsByte(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned char AXISCALL GetAttributeAsUnsignedByte(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsLong(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsInteger(const AxisChar* pName, const AxisChar* pNamespace);
    unsigned long AXISCALL GetAttributeAsUnsignedLong(const AxisChar* pName, const AxisChar* pNamespace);
	float AXISCALL GetAttributeAsFloat(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetAttributeAsDouble(const AxisChar* pName, const AxisChar* pNamespace);
    double AXISCALL GetAttributeAsDecimal(const AxisChar* pName, const AxisChar* pNamespace);
	AxisChar* AXISCALL GetAttributeAsString(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetAttributeAsAnyURI(const AxisChar* pName, const AxisChar* pNamespace);
    AxisChar* AXISCALL GetAttributeAsQName(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__hexBinary AXISCALL GetAttributeAsHexBinary(const AxisChar* pName, const AxisChar* pNamespace);
	xsd__base64Binary AXISCALL GetAttributeAsBase64Binary(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsDateTime(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsDate(const AxisChar* pName, const AxisChar* pNamespace);
    struct tm AXISCALL GetAttributeAsTime(const AxisChar* pName, const AxisChar* pNamespace);
    long AXISCALL GetAttributeAsDuration(const AxisChar* pName, const AxisChar* pNamespace);

	/* Method used by stubs to get a deserialized value of complex types */
	void* AXISCALL GetCmplxObject(void* pDZFunct, void* pCreFunct, void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of complex types */
	Axis_Array AXISCALL GetCmplxArray(void* pDZFunct, void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* pName, const AxisChar* pNamespace);
	/* Method used by stubs to get a deserialized Array of basic types */
	Axis_Array AXISCALL GetBasicArray(XSDTYPE nType, const AxisChar* pName, const AxisChar* pNamespace);

	int AXISCALL CheckMessage(const AxisChar* pName, const AxisChar* pNamespace);
private:
	int OpenConnection(int secure);
	void CloseConnection();
	int MakeArray();

private:
	ClientAxisEngine* m_pAxisEngine;
	/* 
	   Following are pointers to relevant objects of the ClientAxisEngine instance 
	   So they do not belong to this object and are not created or deleted 
	 */
	MessageData* m_pMsgData;
	SoapSerializer* m_pIWSSZ;
	SoapDeSerializer* m_pIWSDZ;
	/* 
	   m_Soap contains transport related information and function pointers to manipulate
	   transport layer.
	 */
	Ax_soapstream m_Soap;
	/*
	   Transport object
	 */
	AxisTransport* m_pTransport;
};

#endif

typedef struct { 
	void* _object; /* this will be C++ Call Object */
	CallFunctions* _functions; /* this is the static function table */
} Call_C;

#ifdef __cplusplus
extern "C" { 
#endif
STORAGE_CLASS_INFO void* GetStubObject(AXIS_PROTOCOL_TYPE nProtocol, AxisChar* pchEndpointURI); 
STORAGE_CLASS_INFO void DestroyStubObject(void* pCall); 
#ifdef __cplusplus
} 
#endif

#ifndef __cplusplus
typedef Call_C Call; 
#endif

#endif /* !defined(AFX_CALL_H__D13E5626_0A9B_43EA_B606_364B98CEDAA8__INCLUDED_)*/
