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

#include <axis/IWrapperSoapDeSerializer.hpp>
#include <axis/AxisException.hpp>

#include "AxisObjectContainer.hpp"

AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/TypeMapping.h>
#include <axis/IWrapperSoapDeSerializer.h>

AXISC_STORAGE_CLASS_INFO 
void axiscDestroyIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        delete dz;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, 
                          const AxiscChar * pName, 
                          const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->checkMessageBody(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
void * axiscCheckForFault(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
Axisc_Array* axiscGetCmplxArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                        Axisc_Array * pArray, 
                                                        void * pDZFunct, 
                                                        void * pCreFunct, 
                                                        void * pDelFunct, 
                                                        void * pSizeFunct, 
                                                        const AxiscChar * pName, 
                                                        const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO: not implemented
        Axisc_Array* aa = new Axisc_Array();
        memset(aa,0,sizeof(aa));
        return aa;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (Axisc_Array*)NULL;
}

AXISC_STORAGE_CLASS_INFO 
Axisc_Array* axiscGetBasicArrayIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                        AXISC_XSDTYPE nType, 
                                                        const AxiscChar * pName, 
                                                        const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO: not implemented
        Axisc_Array* aa = new Axisc_Array();
        memset(aa,0,sizeof(aa));
        return aa;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (Axisc_Array*)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void * axiscGetCmplxObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                   void * pDZFunct, 
                                                   void * pCreFunct, 
                                                   void * pDelFunct, 
                                                   const AxiscChar * pName, 
                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscGetElementAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                         const AxiscChar * pName, 
                                                         const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscGetElementAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (xsdc__boolean *)(dz->getElementAsBoolean(pName,pNamespace));
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscGetElementAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                         const AxiscChar * pName, 
                                                                         const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsUnsignedInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscGetElementAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscGetElementAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName,
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsUnsignedShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscGetElementAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscGetElementAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsUnsignedByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscGetElementAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscGetElementAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscGetElementAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsUnsignedLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscGetElementAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsFloat(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscGetElementAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName,
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsDouble(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscGetElementAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsDecimal(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscGetElementAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscGetElementAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsAnyURI(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscGetElementAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsQName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscGetElementAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO: not implemented yet
        xsdc__hexBinary * hb = new xsdc__hexBinary();
        memset(hb,0,sizeof(hb));
        return hb;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscGetElementAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO: not implemented yet
        xsdc__base64Binary * bb = new xsdc__base64Binary();
        memset(bb,0,sizeof(bb));
        return bb;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscGetElementAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsDateTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscGetElementAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsDate(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscGetElementAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscGetElementAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getElementAsDuration(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__duration *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscGetAttributeAsIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                           const AxiscChar * pName, 
                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscGetAttributeAsBooleanIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (xsdc__boolean *)(dz->getAttributeAsBoolean(pName,pNamespace));
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscGetAttributeAsUnsignedIntIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsUnsignedInt(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscGetAttributeAsShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscGetAttributeAsUnsignedShortIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                               const AxiscChar * pName, 
                                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsUnsignedShort(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscGetAttributeAsByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscGetAttributeAsUnsignedByteIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsUnsignedByte(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscGetAttributeAsLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscGetAttributeAsIntegerIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsInteger(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscGetAttributeAsUnsignedLongIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsUnsignedLong(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscGetAttributeAsFloatIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsFloat(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscGetAttributeAsDoubleIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                 const AxiscChar * pName, 
                                                                 const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsDouble(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscGetAttributeAsDecimalIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                   const AxiscChar * pName, 
                                                                   const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
           return dz->getAttributeAsDecimal(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscGetAttributeAsStringIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsString(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscGetAttributeAsAnyURIIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                               const AxiscChar * pName, 
                                                               const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsAnyURI(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscGetAttributeAsQNameIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsQName(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscGetAttributeAsHexBinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                       const AxiscChar * pName, 
                                                                       const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO not implemented yet
        xsdc__hexBinary * hb = new xsdc__hexBinary();
        memset(hb,0,sizeof(hb));
        return hb;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscGetAttributeAsBase64BinaryIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        // TODO not implemented yet
        xsdc__base64Binary * bb = new xsdc__base64Binary();
        memset(bb,0,sizeof(bb));
        return bb;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscGetAttributeAsDateTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsDateTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscGetAttributeAsDateIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsDate(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscGetAttributeAsTimeIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                             const AxiscChar * pName, 
                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsTime(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscGetAttributeAsDurationIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getAttributeAsDuration(pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__duration *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
int axiscGetStatusIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getStatus();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AXISC_BINDING_STYLE axiscGetStyle(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AXISC_BINDING_STYLE)(dz->getStyle());
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    // Need to return something - probably best to define UNKNOWN.
    return AXISC_DOC_LITERAL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscSetStyle(AXISCHANDLE wrapperSoapDeSerializer, 
                   AXISC_BINDING_STYLE nStyle) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        dz->setStyle((AXIS_BINDING_STYLE)nStyle);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscGetVersion(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getVersion();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return -1;
}

AXISC_STORAGE_CLASS_INFO 
int axiscGetHeaderIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getHeader();
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AxiscAnyType * axiscGetAnyObjectIWrapperSoapDeSerializer(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AxiscAnyType*)(dz->getAnyObject());
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AxiscAnyType *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, 
                        void * pValue, 
                        AXISC_XSDTYPE type) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        dz->getChardataAs(pValue,(XSDTYPE)type);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, 
                                             const char * pcAttachmentid) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AXISCHANDLE)(dz->getAttachment(pcAttachmentid));
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;
}

}
