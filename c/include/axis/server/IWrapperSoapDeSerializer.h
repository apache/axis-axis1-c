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

#if !defined(_IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_)
#define _IWRAPPERSOAPDESERIALIZER_H____OF_AXIS_INCLUDED_


#include "GDefine.h"
#include "AxisUserAPI.h"
#include "TypeMapping.h"
#include "WSDDDefines.h"
#include "Packet.h"
#include <axis/SOAPTransport.h>

#ifdef __cplusplus

#include "ISoapDeSerializer.h"
#include <string>
using namespace std;
#endif

typedef struct {
    int (AXISCALL* checkMessageBody)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    int (AXISCALL* checkForFault)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized Array of complex types */
    Axis_Array (AXISCALL* getCmplxArray)(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, void* pSizeFunct, 
        const AxisChar* pName, const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized Array of basic types */
    Axis_Array (AXISCALL* getBasicArray)(void* pObj, XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace);
    /* Method used by wrappers to get a deserialized single object of 
     * complex type 
     */
    void* (AXISCALL* getCmplxObject)(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace);
    
    /* Methods used by wrappers to get a deserialized value of basic types */
    int (AXISCALL* getElementAsInt)(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace);
    int (AXISCALL* getFaultDetail)(void* pObj, char** ppcDetail);
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
    int (AXISCALL* getStatus)(void* pObj);
    AnyType* (AXISCALL* getAnyObject)(void* pObj);
} IWrapperSoapDeSerializerFunctions;

typedef struct { 
    void* _object; /* this will be C++ SoapDeSerializer Object */
    IWrapperSoapDeSerializerFunctions* _functions; 
    /* this is the static function table */
} IWrapperSoapDeSerializer_C;

#ifndef __cplusplus
typedef IWrapperSoapDeSerializer_C IWrapperSoapDeSerializer;
#else
/**
    @class IWrapperSoapDeSerializer
    @brief interface for the IWrapperSoapDeSerializer class.


    @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
    @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
*/
class IWrapperSoapDeSerializer : public ISoapDeSerializer
{
public:
    virtual ~IWrapperSoapDeSerializer(){};

    virtual int AXISCALL checkMessageBody(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual int AXISCALL checkForFault(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized Array of complex types */
    virtual Axis_Array AXISCALL getCmplxArray(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, void* pSizeFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized Array of basic types */
    virtual Axis_Array AXISCALL getBasicArray(XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)=0;
    /* Method used by wrappers to get a deserialized single object of 
     * complex type 
     */
    virtual void* AXISCALL getCmplxObject(void* pDZFunct, void* pCreFunct, 
        void* pDelFunct, const AxisChar* pName, const AxisChar* pNamespace)=0;
    
    /* Methods used by wrappers to get a deserialized value of basic types */
    virtual int AXISCALL getElementAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual int AXISCALL getFaultDetail(char** ppcDetail) = 0;
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
    virtual xsd__base64Binary AXISCALL getElementAsBase64Binary(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsDateTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsDate(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual struct tm AXISCALL getElementAsTime(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual long AXISCALL getElementAsDuration(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;

    virtual int AXISCALL getAttributeAsInt(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual xsd__boolean AXISCALL getAttributeAsBoolean(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned int AXISCALL getAttributeAsUnsignedInt(const AxisChar* 
        pName, const AxisChar* pNamespace)=0;
    virtual short AXISCALL getAttributeAsShort(const AxisChar* pName, 
        const AxisChar* pNamespace)=0;
    virtual unsigned short AXISCALL getAttributeAsUnsignedShort(const AxisChar*
        pName, const AxisChar* pNamespace)=0;
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
    virtual int AXISCALL getStatus()=0;
    
    /* Externalization of deserializer API */
    virtual int setInputStream(SOAPTransport* pInputStream)=0;
    virtual int init()=0;
    virtual PROVIDERTYPE getCurrentProviderType()=0;
    virtual void setCurrentProviderType(PROVIDERTYPE nType)=0;    
    virtual AXIS_BINDING_STYLE getStyle()=0;    
    virtual void setStyle(AXIS_BINDING_STYLE nStyle)=0;
    virtual int getVersion()=0;
    virtual int getHeader()=0;    
	virtual AnyType* AXISCALL getAnyObject()=0;            

    /* following stuff is needed to provide the interface for C web services */
public:
    static IWrapperSoapDeSerializerFunctions ms_VFtable;
    static int AXISCALL s_CheckMessageBody(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
    {return ((IWrapperSoapDeSerializer*)pObj)->checkMessageBody(pName, 
    pNamespace);};
    static int AXISCALL s_CheckForFault(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
    {return ((IWrapperSoapDeSerializer*)pObj)->checkMessageBody(pName, 
    pNamespace);};
    static Axis_Array AXISCALL s_GetCmplxArray(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, void* pSizeFunct, const AxisChar* 
        pName, const AxisChar* pNamespace)
    {return ((IWrapperSoapDeSerializer*)pObj)->getCmplxArray(pDZFunct, 
    pCreFunct, pDelFunct, pSizeFunct, pName, pNamespace);};
    static Axis_Array AXISCALL s_GetBasicArray(void* pObj, XSDTYPE nType, 
        const AxisChar* pName, const AxisChar* pNamespace)
    {return ((IWrapperSoapDeSerializer*)pObj)->getBasicArray(nType, pName, 
    pNamespace);};
    static void* AXISCALL s_GetCmplxObject(void* pObj, void* pDZFunct, 
        void* pCreFunct, void* pDelFunct, const AxisChar* pName, 
        const AxisChar* pNamespace)
    {return ((IWrapperSoapDeSerializer*)pObj)->getCmplxObject(pDZFunct, 
    pCreFunct, pDelFunct, pName, pNamespace);};
    static int AXISCALL s_GetElementAsInt(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsInt(pName, 
    pNamespace);};
    static int AXISCALL s_GetFaultDetail(void* pObj, char** ppcDetail)
    { return ((IWrapperSoapDeSerializer*)pObj)->getFaultDetail(ppcDetail);};
    static xsd__boolean AXISCALL s_GetElementAsBoolean(void* pObj, const 
        AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsBoolean(pName, 
    pNamespace);};
    static unsigned int AXISCALL s_GetElementAsUnsignedInt(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsUnsignedInt(pName, 
    pNamespace);};
    static short AXISCALL s_GetElementAsShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsShort(pName, 
    pNamespace);};
    static unsigned short AXISCALL s_GetElementAsUnsignedShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsUnsignedShort
    (pName, pNamespace);};
    static char AXISCALL s_GetElementAsByte(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsByte(pName, 
    pNamespace);};
    static unsigned char AXISCALL s_GetElementAsUnsignedByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsUnsignedByte(pName,
    pNamespace);};
    static long AXISCALL s_GetElementAsLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsLong(pName, 
    pNamespace);};
    static long AXISCALL s_GetElementAsInteger(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsInteger(pName, 
    pNamespace);};
    static unsigned long AXISCALL s_GetElementAsUnsignedLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsUnsignedLong(pName,
    pNamespace);};
    static float AXISCALL s_GetElementAsFloat(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsFloat(pName, 
    pNamespace);};
    static double AXISCALL s_GetElementAsDouble(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsDouble(pName, 
    pNamespace);};
    static double AXISCALL s_GetElementAsDecimal(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsDouble(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsString(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsString(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsAnyURI(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsAnyURI(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetElementAsQName(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsQName(pName, 
    pNamespace);};
    static xsd__hexBinary AXISCALL s_GetElementAsHexBinary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsHexBinary(pName, 
    pNamespace);};
    static xsd__base64Binary AXISCALL s_GetElementAsBase64Binary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsBase64Binary(pName,
    pNamespace);};
    static struct tm AXISCALL s_GetElementAsDateTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsDateTime(pName, 
    pNamespace);};
    static struct tm AXISCALL s_GetElementAsDate(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsDate(pName, 
    pNamespace);};
    static struct tm AXISCALL s_GetElementAsTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsTime(pName, 
    pNamespace);};
    static long AXISCALL s_GetElementAsDuration(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getElementAsDuration(pName, 
    pNamespace);};
    static int AXISCALL s_GetAttributeAsInt(void* pObj, const AxisChar* pName, 
        const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsInt(pName, 
    pNamespace);};
    static xsd__boolean AXISCALL s_GetAttributeAsBoolean(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsBoolean(pName, 
    pNamespace);};
    static unsigned int AXISCALL s_GetAttributeAsUnsignedInt(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsUnsignedInt
    (pName, pNamespace);};
    static short AXISCALL s_GetAttributeAsShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsShort(pName, 
    pNamespace);};
    static unsigned short AXISCALL s_GetAttributeAsUnsignedShort(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsUnsignedShort
    (pName, pNamespace);};
    static char AXISCALL s_GetAttributeAsByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsByte(pName, 
    pNamespace);};
    static unsigned char AXISCALL s_GetAttributeAsUnsignedByte(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsUnsignedByte
    (pName, pNamespace);};
    static long AXISCALL s_GetAttributeAsLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsLong(pName, 
    pNamespace);};
    static long AXISCALL s_GetAttributeAsInteger(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsInteger(pName, 
    pNamespace);};
    static unsigned long AXISCALL s_GetAttributeAsUnsignedLong(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsUnsignedLong
    (pName, pNamespace);};
    static float AXISCALL s_GetAttributeAsFloat(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsFloat(pName, 
    pNamespace);};
    static double AXISCALL s_GetAttributeAsDouble(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsDouble(pName, 
    pNamespace);};
    static double AXISCALL s_GetAttributeAsDecimal(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsDecimal(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsString(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsString(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsAnyURI(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsAnyURI(pName, 
    pNamespace);};
    static AxisChar* AXISCALL s_GetAttributeAsQName(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsQName(pName, 
    pNamespace);};
    static xsd__hexBinary AXISCALL s_GetAttributeAsHexBinary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsHexBinary(pName, 
    pNamespace);};
    static xsd__base64Binary AXISCALL s_GetAttributeAsBase64Binary(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsBase64Binary
    (pName, pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDateTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsDateTime(pName, 
    pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsDate(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsDate(pName, 
    pNamespace);};
    static struct tm AXISCALL s_GetAttributeAsTime(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsTime(pName, 
    pNamespace);};
    static long AXISCALL s_GetAttributeAsDuration(void* pObj, 
        const AxisChar* pName, const AxisChar* pNamespace)
    { return ((IWrapperSoapDeSerializer*)pObj)->getAttributeAsDuration(pName, 
    pNamespace);};
    static int AXISCALL s_GetStatus(void* pObj)
    { return ((IWrapperSoapDeSerializer*)pObj)->getStatus();};
	static 	AnyType* AXISCALL s_GetAnyObject(void* pObj)
	{ return ((IWrapperSoapDeSerializer*)pObj)->getAnyObject();};

    static void s_Initialize()
    {
        ms_VFtable.checkMessageBody = s_CheckMessageBody;
        ms_VFtable.checkForFault = s_CheckForFault;
        ms_VFtable.getCmplxArray = s_GetCmplxArray;
        ms_VFtable.getBasicArray = s_GetBasicArray;
        ms_VFtable.getCmplxObject = s_GetCmplxObject;
        ms_VFtable.getElementAsInt = s_GetElementAsInt;
        ms_VFtable.getFaultDetail = s_GetFaultDetail;
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
        ms_VFtable.getStatus = s_GetStatus;
		ms_VFtable.getAnyObject = s_GetAnyObject;
    }
};
#endif

#endif
