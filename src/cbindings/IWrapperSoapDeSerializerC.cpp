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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/IWrapperSoapDeSerializer.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectConverter.hpp"
#include "client/StubC.h"

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/IWrapperSoapDeSerializer.h>
#include <axis/client/Call.hpp>

#include "../common/AxisTrace.h"
#include "../soap/SoapDeSerializer.h"

AXIS_CPP_NAMESPACE_USE

extern "C" {

static void processException(void *d, AxisException& e)
{
    AXIS_EXCEPTION_HANDLER_FUNCT exceptionHandler = axiscAxisInvokeExceptionHandler;
    void *stubExceptionHandler;
    Call *c = NULL;

    StubC *s = (StubC *)(((SoapDeSerializer *)d)->getCStub());
    if (s)
    {
        if ((stubExceptionHandler = s->getCExceptionHandler()) != NULL)
            exceptionHandler = (AXIS_EXCEPTION_HANDLER_FUNCT)stubExceptionHandler;

        s->doNotPerformClientRequest = true;
        c = s->getCallStubC();
    }

    if (c)
        c->processSoapFault(&e, exceptionHandler);
    else
        exceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
}


AXISC_STORAGE_CLASS_INFO 
void axiscSoapDeSerializerDestroy(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        delete dz;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, 
                          const AxiscChar * pName, 
                          const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return AXISC_FAIL;

    try
    {
        return dz->checkMessageBody(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
void * axiscSoapDeSerializerCheckForFault(AXISCHANDLE wrapperSoapDeSerializer, 
                          const AxiscChar * pName, 
                          const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->checkForFault(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
Axisc_Array* axiscSoapDeSerializerGetCmplxArray(AXISCHANDLE wrapperSoapDeSerializer, 
                                                        Axisc_Array * pArray, 
                                                        void * pDZFunct, 
                                                        void * pCreFunct, 
                                                        void * pDelFunct, 
                                                        const AxiscChar * pName, 
                                                        const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (Axisc_Array*)NULL;

    try
    {
        Axis_Array  tmpObjArray;
        
        if (pArray)
            tmpObjArray.set((void **)pArray->m_Array, pArray->m_Size, (XSDTYPE)pArray->m_Type);
        
        Axis_Array* pObjArray = dz->getCmplxArray(&tmpObjArray, 
                                                  pDZFunct, pCreFunct, pDelFunct, pName, pNamespace);
        
        return AxisObjectConverter::cppArrayToC(pObjArray, pArray, false);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (Axisc_Array*)NULL;
}

AXISC_STORAGE_CLASS_INFO 
Axisc_Array* axiscSoapDeSerializerGetBasicArray(AXISCHANDLE wrapperSoapDeSerializer, 
                                                        AXISC_XSDTYPE nType, 
                                                        const AxiscChar * pName, 
                                                        const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (Axisc_Array*)NULL;

    try
    {
        Axis_Array* pObjArray = dz->getBasicArray((XSDTYPE)nType, pName, pNamespace);
        
        return AxisObjectConverter::cppArrayToC(pObjArray, NULL, true);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (Axisc_Array*)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void * axiscSoapDeSerializerGetCmplxObject(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   void * pDZFunct, 
                                                   void * pCreFunct, 
                                                   void * pDelFunct, 
                                                   const AxiscChar * pName, 
                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (void *)NULL;

    try
    {
        return dz->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscSoapDeSerializerGetElementAsInt(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__int *)NULL;

    try
    {
        return dz->getElementAsInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscSoapDeSerializerGetElementAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__boolean *)NULL;

    try
    {
        return (xsdc__boolean *)(dz->getElementAsBoolean(pName,pNamespace));
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscSoapDeSerializerGetElementAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedInt *)NULL;

    try
    {
        return dz->getElementAsUnsignedInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscSoapDeSerializerGetElementAsShort(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__short *)NULL;

    try
    {
        return dz->getElementAsShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscSoapDeSerializerGetElementAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName,
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedShort *)NULL;

    try
    {
        return dz->getElementAsUnsignedShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscSoapDeSerializerGetElementAsByte(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__byte *)NULL;

    try
    {
        return dz->getElementAsByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscSoapDeSerializerGetElementAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedByte *)NULL;

    try
    {
        return dz->getElementAsUnsignedByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscSoapDeSerializerGetElementAsLong(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__long *)NULL;

    try
    {
        return dz->getElementAsLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscSoapDeSerializerGetElementAsInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__integer *)NULL;

    try
    {
        return dz->getElementAsInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscSoapDeSerializerGetElementAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedLong *)NULL;

    try
    {
        return dz->getElementAsUnsignedLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscSoapDeSerializerGetElementAsFloat(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__float *)NULL;

    try
    {
        return dz->getElementAsFloat(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscSoapDeSerializerGetElementAsDouble(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName,
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__double *)NULL;

    try
    {
        return dz->getElementAsDouble(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscSoapDeSerializerGetElementAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__decimal *)NULL;

    try
    {
        return dz->getElementAsDecimal(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscSoapDeSerializerGetElementAsString(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__string)NULL;

    try
    {
        return dz->getElementAsString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscSoapDeSerializerGetElementAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__anyURI)NULL;

    try
    {
        return dz->getElementAsAnyURI(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscSoapDeSerializerGetElementAsQName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__QName)NULL;

    try
    {
        return dz->getElementAsQName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscSoapDeSerializerGetElementAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__hexBinary *)NULL;

    try
    {
        xsd__hexBinary * pObjCpp = dz->getElementAsHexBinary(pName, pNamespace);
        
        return AxisObjectConverter::cppHexBinaryToC(pObjCpp, NULL, true);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscSoapDeSerializerGetElementAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__base64Binary *)NULL;

    try
    {
        xsd__base64Binary * pObjCpp = dz->getElementAsBase64Binary(pName, pNamespace);
        
        return AxisObjectConverter::cppBase64BinaryToC(pObjCpp, NULL, true);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscSoapDeSerializerGetElementAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__dateTime *)NULL;

    try
    {
        return dz->getElementAsDateTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscSoapDeSerializerGetElementAsDate(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__date *)NULL;

    try
    {
        return dz->getElementAsDate(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscSoapDeSerializerGetElementAsTime(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__time *)NULL;

    try
    {
        return dz->getElementAsTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscSoapDeSerializerGetElementAsDuration(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__duration *)NULL;

    try
    {
        return dz->getElementAsDuration(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__duration *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gYearMonth * axiscSoapDeSerializerGetElementAsGYearMonth(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gYearMonth *)NULL;

    try
    {
        return dz->getElementAsGYearMonth(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gYearMonth *)NULL;    
}

AXISC_STORAGE_CLASS_INFO
xsdc__gYear * axiscSoapDeSerializerGetElementAsGYear(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName, 
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gYear *)NULL;

    try
    {
        return dz->getElementAsGYear(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gYear *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gMonthDay * axiscSoapDeSerializerGetElementAsGMonthDay(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gMonthDay *)NULL;

    try
    {
        return dz->getElementAsGMonthDay(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gMonthDay *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gDay * axiscSoapDeSerializerGetElementAsGDay(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName, 
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gDay *)NULL;

    try
    {
        return dz->getElementAsGDay(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gDay *)NULL;    
}

AXISC_STORAGE_CLASS_INFO
xsdc__gMonth * axiscSoapDeSerializerGetElementAsGMonth(AXISCHANDLE wrapperSoapDeSerializer, 
                                                       const AxiscChar * pName, 
                                                       const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gMonth *)NULL;

    try
    {
        return dz->getElementAsGMonth(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gMonth *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__nonPositiveInteger * axiscSoapDeSerializerGetElementAsNonPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__nonPositiveInteger *)NULL;

    try
    {
        return dz->getElementAsNonPositiveInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__nonPositiveInteger *)NULL;        
}

AXISC_STORAGE_CLASS_INFO
xsdc__negativeInteger * axiscSoapDeSerializerGetElementAsNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__negativeInteger *)NULL;

    try
    {
        return dz->getElementAsNegativeInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__negativeInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__nonNegativeInteger * axiscSoapDeSerializerGetElementAsNonNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__nonNegativeInteger *)NULL;

    try
    {
        return dz->getElementAsNonNegativeInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__nonNegativeInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__positiveInteger * axiscSoapDeSerializerGetElementAsPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__positiveInteger *)NULL;

    try
    {
        return dz->getElementAsPositiveInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__positiveInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__normalizedString axiscSoapDeSerializerGetElementAsNormalizedString(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__normalizedString)NULL;

    try
    {
        return dz->getElementAsNormalizedString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__normalizedString)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__token axiscSoapDeSerializerGetElementAsToken(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName,
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__token)NULL;

    try
    {
        return dz->getElementAsToken(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__token)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__language axiscSoapDeSerializerGetElementAsLanguage(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__language)NULL;

    try
    {
        return dz->getElementAsLanguage(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__language)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__Name axiscSoapDeSerializerGetElementAsName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                 const AxiscChar * pName, 
                                                 const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__Name)NULL;

    try
    {
        return dz->getElementAsName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__Name)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NCName axiscSoapDeSerializerGetElementAsNCName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName, 
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NCName)NULL;

    try
    {
        return dz->getElementAsNCName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NCName)NULL;      
}


AXISC_STORAGE_CLASS_INFO
xsdc__ID axiscSoapDeSerializerGetElementAsID(AXISCHANDLE wrapperSoapDeSerializer, 
                                             const AxiscChar * pName,
                                             const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ID)NULL;

    try
    {
        return dz->getElementAsID(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ID)NULL;    
}

AXISC_STORAGE_CLASS_INFO
xsdc__IDREF axiscSoapDeSerializerGetElementAsIDREF(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName,
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__IDREF)NULL;

    try
    {
        return dz->getElementAsIDREF(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__IDREF)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__IDREFS axiscSoapDeSerializerGetElementAsIDREFS(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName,
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__IDREFS)NULL;

    try
    {
        return dz->getElementAsIDREFS(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__IDREFS)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__ENTITY axiscSoapDeSerializerGetElementAsENTITY(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName,
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ENTITY)NULL;

    try
    {
        return dz->getElementAsENTITY(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ENTITY)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__ENTITIES axiscSoapDeSerializerGetElementAsENTITIES(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName,
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ENTITIES)NULL;

    try
    {
        return dz->getElementAsENTITIES(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ENTITIES)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKEN axiscSoapDeSerializerGetElementAsNMTOKEN(AXISCHANDLE wrapperSoapDeSerializer, 
                                                       const AxiscChar * pName,
                                                       const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NMTOKEN)NULL;

    try
    {
        return dz->getElementAsNMTOKEN(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NMTOKEN)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKENS axiscSoapDeSerializerGetElementAsNMTOKENS(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NMTOKENS)NULL;

    try
    {
        return dz->getElementAsNMTOKENS(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NMTOKENS)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NOTATION axiscSoapDeSerializerGetElementAsNOTATION(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NOTATION)NULL;

    try
    {
        return dz->getElementAsNOTATION(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NOTATION)NULL;      
}


AXISC_STORAGE_CLASS_INFO
xsdc__anyType axiscSoapDeSerializerGetElementAsAnyType(AXISCHANDLE wrapperSoapDeSerializer, 
                                                       const AxiscChar * pName, 
                                                       const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__anyType)NULL;

    try
    {
        return dz->getElementAsAnyType(pName, pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__anyType)NULL;      
}




AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscSoapDeSerializerGetAttributeAsInt(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__int *)NULL;

    try
    {
        return dz->getAttributeAsInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscSoapDeSerializerGetAttributeAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__boolean *)NULL;

    try
    {
        return (xsdc__boolean *)(dz->getAttributeAsBoolean(pName,pNamespace));
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscSoapDeSerializerGetAttributeAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedInt *)NULL;

    try
    {
        return dz->getAttributeAsUnsignedInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscSoapDeSerializerGetAttributeAsShort(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__short *)NULL;

    try
    {
        return dz->getAttributeAsShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscSoapDeSerializerGetAttributeAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedShort *)NULL;

    try
    {
        return dz->getAttributeAsUnsignedShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscSoapDeSerializerGetAttributeAsByte(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__byte *)NULL;

    try
    {
        return dz->getAttributeAsByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscSoapDeSerializerGetAttributeAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedByte *)NULL;

    try
    {
        return dz->getAttributeAsUnsignedByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscSoapDeSerializerGetAttributeAsLong(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__long *)NULL;

    try
    {
        return dz->getAttributeAsLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscSoapDeSerializerGetAttributeAsInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__integer *)NULL;

    try
    {
        return dz->getAttributeAsInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscSoapDeSerializerGetAttributeAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__unsignedLong *)NULL;

    try
    {
        return dz->getAttributeAsUnsignedLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscSoapDeSerializerGetAttributeAsFloat(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__float *)NULL;

    try
    {
        return dz->getAttributeAsFloat(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscSoapDeSerializerGetAttributeAsDouble(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__double *)NULL;

    try
    {
        return dz->getAttributeAsDouble(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscSoapDeSerializerGetAttributeAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__decimal *)NULL;

    try
    {
           return dz->getAttributeAsDecimal(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscSoapDeSerializerGetAttributeAsString(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__string)NULL;

    try
    {
        return dz->getAttributeAsString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscSoapDeSerializerGetAttributeAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__anyURI)NULL;

    try
    {
        return dz->getAttributeAsAnyURI(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscSoapDeSerializerGetAttributeAsQName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__QName)NULL;

    try
    {
        return dz->getAttributeAsQName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscSoapDeSerializerGetAttributeAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                       const AxiscChar * pName, 
                                                                       const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__hexBinary *)NULL;

    try
    {
        xsd__hexBinary * pObjCpp = dz->getAttributeAsHexBinary(pName, pNamespace);
        
        return AxisObjectConverter::cppHexBinaryToC(pObjCpp, NULL, true);  
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscSoapDeSerializerGetAttributeAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__base64Binary *)NULL;

    try
    {
        xsd__base64Binary * pObjCpp = dz->getAttributeAsBase64Binary(pName, pNamespace);
        
        return AxisObjectConverter::cppBase64BinaryToC(pObjCpp, NULL, true);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscSoapDeSerializerGetAttributeAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__dateTime *)NULL;

    try
    {
        return dz->getAttributeAsDateTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscSoapDeSerializerGetAttributeAsDate(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__date *)NULL;

    try
    {
        return dz->getAttributeAsDate(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscSoapDeSerializerGetAttributeAsTime(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__time *)NULL;

    try
    {
        return dz->getAttributeAsTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscSoapDeSerializerGetAttributeAsDuration(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__duration *)NULL;

    try
    {
        return dz->getAttributeAsDuration(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__duration *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gYearMonth * axiscSoapDeSerializerGetAttributeAsGYearMonth(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gYearMonth *)NULL;

    try
    {
        return dz->getAttributeAsGYearMonth(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gYearMonth *)NULL;    
}

AXISC_STORAGE_CLASS_INFO
xsdc__gYear * axiscSoapDeSerializerGetAttributeAsGYear(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName, 
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gYear *)NULL;

    try
    {
        return dz->getAttributeAsGYear(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gYear *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gMonthDay * axiscSoapDeSerializerGetAttributeAsGMonthDay(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gMonthDay *)NULL;

    try
    {
        return dz->getAttributeAsGMonthDay(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gMonthDay *)NULL;
}

AXISC_STORAGE_CLASS_INFO
xsdc__gDay * axiscSoapDeSerializerGetAttributeAsGDay(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName, 
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gDay *)NULL;

    try
    {
        return dz->getAttributeAsGDay(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gDay *)NULL;    
}

AXISC_STORAGE_CLASS_INFO
xsdc__gMonth * axiscSoapDeSerializerGetAttributeAsGMonth(AXISCHANDLE wrapperSoapDeSerializer, 
                                                       const AxiscChar * pName, 
                                                       const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__gMonth *)NULL;

    try
    {
        return dz->getAttributeAsGMonth(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__gMonth *)NULL;
}


AXISC_STORAGE_CLASS_INFO
xsdc__nonPositiveInteger * axiscSoapDeSerializerGetAttributeAsNonPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__nonPositiveInteger *)NULL;

    try
    {
        return dz->getAttributeAsNonPositiveInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__nonPositiveInteger *)NULL;        
}

AXISC_STORAGE_CLASS_INFO
xsdc__negativeInteger * axiscSoapDeSerializerGetAttributeAsNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__negativeInteger *)NULL;

    try
    {
        return dz->getAttributeAsNegativeInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__negativeInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__nonNegativeInteger * axiscSoapDeSerializerGetAttributeAsNonNegativeInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__nonNegativeInteger *)NULL;

    try
    {
        return dz->getAttributeAsNonNegativeInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__nonNegativeInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__positiveInteger * axiscSoapDeSerializerGetAttributeAsPositiveInteger(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__positiveInteger *)NULL;

    try
    {
        return dz->getAttributeAsPositiveInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__positiveInteger *)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__normalizedString axiscSoapDeSerializerGetAttributeAsNormalizedString(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__normalizedString)NULL;

    try
    {
        return dz->getAttributeAsNormalizedString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__normalizedString)NULL;          
}

AXISC_STORAGE_CLASS_INFO
xsdc__token axiscSoapDeSerializerGetAttributeAsToken(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName,
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__token)NULL;

    try
    {
        return dz->getAttributeAsToken(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__token)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__language axiscSoapDeSerializerGetAttributeAsLanguage(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__language)NULL;

    try
    {
        return dz->getAttributeAsLanguage(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__language)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__Name axiscSoapDeSerializerGetAttributeAsName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                 const AxiscChar * pName, 
                                                 const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__Name)NULL;

    try
    {
        return dz->getAttributeAsName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__Name)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NCName axiscSoapDeSerializerGetAttributeAsNCName(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName, 
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NCName)NULL;

    try
    {
        return dz->getAttributeAsNCName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NCName)NULL;      
}


AXISC_STORAGE_CLASS_INFO
xsdc__ID axiscSoapDeSerializerGetAttributeAsID(AXISCHANDLE wrapperSoapDeSerializer, 
                                               const AxiscChar * pName,
                                               const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ID)NULL;

    try
    {
        return dz->getAttributeAsID(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ID)NULL;    
}


AXISC_STORAGE_CLASS_INFO
xsdc__IDREF axiscSoapDeSerializerGetAttributeAsIDREF(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   const AxiscChar * pName,
                                                   const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__IDREF)NULL;

    try
    {
        return dz->getAttributeAsIDREF(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__IDREF)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__IDREFS axiscSoapDeSerializerGetAttributeAsIDREFS(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName,
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__IDREFS)NULL;

    try
    {
        return dz->getAttributeAsIDREFS(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__IDREFS)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__ENTITY axiscSoapDeSerializerGetAttributeAsENTITY(AXISCHANDLE wrapperSoapDeSerializer, 
                                                     const AxiscChar * pName,
                                                     const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ENTITY)NULL;

    try
    {
        return dz->getAttributeAsENTITY(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ENTITY)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__ENTITIES axiscSoapDeSerializerGetAttributeAsENTITIES(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName,
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__ENTITIES)NULL;

    try
    {
        return dz->getAttributeAsENTITIES(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__ENTITIES)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKEN axiscSoapDeSerializerGetAttributeAsNMTOKEN(AXISCHANDLE wrapperSoapDeSerializer, 
                                                       const AxiscChar * pName,
                                                       const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NMTOKEN)NULL;

    try
    {
        return dz->getAttributeAsNMTOKEN(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NMTOKEN)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NMTOKENS axiscSoapDeSerializerGetAttributeAsNMTOKENS(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NMTOKENS)NULL;

    try
    {
        return dz->getAttributeAsNMTOKENS(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NMTOKENS)NULL;      
}

AXISC_STORAGE_CLASS_INFO
xsdc__NOTATION axiscSoapDeSerializerGetAttributeAsNOTATION(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (xsdc__NOTATION)NULL;

    try
    {
        return dz->getAttributeAsNOTATION(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (xsdc__NOTATION)NULL;      
}


AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerGetStatus(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getStatus();
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AXISC_BINDING_STYLE axiscSoapDeSerializerGetStyle(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AXISC_BINDING_STYLE)(dz->getStyle());
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    // Need to return something - probably best to define UNKNOWN.
    return AXISC_DOC_LITERAL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscSoapDeSerializerSetStyle(AXISCHANDLE wrapperSoapDeSerializer, 
                   AXISC_BINDING_STYLE nStyle) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        dz->setStyle((AXIS_BINDING_STYLE)nStyle);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerGetVersion(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getVersion();
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
    
    return -1;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerGetHeader(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return AXISC_FAIL;

    try
    {
        return dz->getHeader();
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AxiscAnyType * axiscSoapDeSerializerGetAnyObject(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (AxiscAnyType *)NULL;

    try
    {
        AnyType * pObjCpp = dz->getAnyObject();
        
        return AxisObjectConverter::cppAnyTypeToC(pObjCpp, NULL, true);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AxiscAnyType *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscSoapDeSerializerGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, 
                        void ** pValue, 
                        AXISC_XSDTYPE type) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
    {
        *pValue = NULL;
        return;
    }

    try
    {
        dz->getChardataAs(pValue,(XSDTYPE)type);
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscSoapDeSerializerGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, 
                                             const char * pcAttachmentid) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return (AXISCHANDLE)NULL;

    try
    {
        return (AXISCHANDLE)(dz->getAttachment(pcAttachmentid));
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO
const char * axiscSoapDeSerializerPeekNextElementName(AXISCHANDLE wrapperSoapDeSerializer)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;
    StubC *s = (StubC *)(((SoapDeSerializer *)dz)->getCStub());
    if (s && s->doNotPerformClientRequest)
        return "";

    try
    {
        return dz->peekNextElementName();
    }
    catch ( AxisException& e  )
    {
        processException(wrapperSoapDeSerializer, e);
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }

    return (const char *)NULL;
}

}
