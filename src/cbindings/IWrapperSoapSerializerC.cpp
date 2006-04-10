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

#include <axis/IWrapperSoapSerializer.hpp>
#include <axis/AxisException.hpp>

#include "../soap/SoapSerializer.h"
#include "AxisObjectContainer.hpp"

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/AxisUserAPIArrays.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/TypeMapping.h>
#include <axis/WSDDDefines.h>
#include <axis/IWrapperSoapSerializer.h>

AXIS_CPP_NAMESPACE_USE

extern "C" {

AXISC_STORAGE_CLASS_INFO 
void axiscDestroyIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        delete sz;
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
int axiscCreateSoapMethod(AXISCHANDLE wrapperSoapSerializer, 
                          const AxiscChar * sLocalName, 
                          const AxiscChar * sURI) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->createSoapMethod(sLocalName,sURI);
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
int axiscCreateSoapFault(AXISCHANDLE wrapperSoapSerializer, 
                         const AxiscChar * sLocalName, 
                         const AxiscChar * sURI, 
                         const AxiscChar * sFaultCode, 
                         const AxiscChar * sFaultString) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->createSoapFault(sLocalName,sURI,sFaultCode,sFaultString);
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

/**
AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetNamespacePrefixIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer, 
                                                                const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->getNamespacePrefix(pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}
***/

AXISC_STORAGE_CLASS_INFO 
const AxiscChar * axiscGetNamespacePrefixIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer, 
                                                                const AxiscChar * pNamespace,
                                                                AxiscBool * blnIsNewPrefix) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        bool isNewPrefix = false;
        const AxiscChar * returnValue = sz->getNamespacePrefix(pNamespace, isNewPrefix);
        *(blnIsNewPrefix) = (AxiscBool) isNewPrefix;
        return returnValue;
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (const AxiscChar *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscRemoveNamespacePrefix(AXISCHANDLE wrapperSoapSerializer, 
                                const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->removeNamespacePrefix(pNamespace);
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
int axiscAddOutputParam(AXISCHANDLE wrapperSoapSerializer, 
                        const AxiscChar * pchName, 
                        void * pValue, 
                        AXISC_XSDTYPE type) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addOutputParam(pchName,pValue,(XSDTYPE)type);    
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
int axiscAddOutputCmplxArrayParam(AXISCHANDLE wrapperSoapSerializer, 
                                  const Axisc_Array * pArray, 
                                  void * pSZFunct, 
                                  void * pDelFunct, 
                                  void * pSizeFunct,
                                  const AxiscChar * pName, 
                                  const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addOutputCmplxArrayParam((const Axis_Array*)pArray,pSZFunct,pDelFunct,
                                            pSizeFunct,pName,pNamespace);
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
int axiscAddOutputBasicArrayParam(AXISCHANDLE wrapperSoapSerializer, 
                                  const Axisc_Array * pArray,
                                  AXISC_XSDTYPE nType, 
                                  const AxiscChar * pName) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addOutputBasicArrayParam((const Axis_Array*)pArray,(XSDTYPE)nType,pName);
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
int axiscAddOutputCmplxParam(AXISCHANDLE wrapperSoapSerializer, 
                             void * pObject, 
                             void * pSZFunct, 
                             void * pDelFunct, 
                             const AxiscChar * pName,
                             const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addOutputCmplxParam(pObject,pSZFunct,pDelFunct,pName,pNamespace);
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
int axiscAddFaultDetail(AXISCHANDLE wrapperSoapSerializer, 
                        void * pObject, 
                        void * pSZFunct, 
                        void * pDelFunct, 
                        const AxiscChar * pName, 
                        const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addFaultDetail(pObject,pSZFunct,pDelFunct,pName,pNamespace);
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
int axiscSerializeCmplxArray(AXISCHANDLE wrapperSoapSerializer, 
                             const Axisc_Array * pArray,
                             void * pSZFunct, 
                             void * pDelFunct, 
                             void * pSizeFunct, 
                             const AxiscChar * pName, 
                             const AxiscChar * pNamespace) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        // Need to convert C-style array to C++-style array before calling serialization method.
        Axis_Array objArray;
        if (pArray && pArray->m_Array)
            objArray.set((void **)pArray->m_Array, pArray->m_Size, (XSDTYPE)pArray->m_Type);

        return sz->serializeCmplxArray((const Axis_Array*)&objArray,pSZFunct,pDelFunct,
                                       pSizeFunct,pName,pNamespace);
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
int axiscSerializeBasicArray(AXISCHANDLE wrapperSoapSerializer, 
                             const Axisc_Array * pArray, 
                             const AxiscChar * pNamespace,
                             AXISC_XSDTYPE nType, 
                             const AxiscChar * pName)
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        // Need to convert C-style array to C++-style array before calling serialization method.
        Axis_Array objArray;
        if (pArray && pArray->m_Array)
            objArray.set((void **)pArray->m_Array, pArray->m_Size, (XSDTYPE)pArray->m_Type);
        
        // Serialize
        return sz->serializeBasicArray((const Axis_Array*)&objArray,pNamespace,(XSDTYPE)nType,pName);
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
int axiscSerializeAsElement(AXISCHANDLE wrapperSoapSerializer, 
                            const AxiscChar * sName, 
                            const AxiscChar * pNamespace, 
                            void * pValue, AXISC_XSDTYPE type) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {                
        // Some elements (e.g. xsd__hexBinary, base64Binary) differ in how C++ defines
        // the types and how C defines the types, in those cases we need to create 
        // the correct type that the engine is expecting.
        switch (type)
        {
            case axiscpp::XSD_HEXBINARY:
            {
                xsdc__hexBinary *pVal = (xsdc__hexBinary *)pValue;
                xsd__hexBinary pValObject;
                pValObject.set(pVal->__ptr, pVal->__size);
                if (pNamespace)
                   return sz->serializeAsElement(sName,pNamespace,&pValObject,(XSDTYPE)type);
                else               
                   return sz->serializeAsElement(sName,&pValObject,(XSDTYPE)type);
            }
            case axiscpp::XSD_BASE64BINARY:
            {
                xsdc__base64Binary *pVal = (xsdc__base64Binary *)pValue;
                xsd__base64Binary pValObject;
                pValObject.set(pVal->__ptr, pVal->__size);
                if (pNamespace)
                   return sz->serializeAsElement(sName,pNamespace,&pValObject,(XSDTYPE)type);
                else               
                   return sz->serializeAsElement(sName,&pValObject,(XSDTYPE)type);
            }
            default:
            {
                if (pNamespace)
                   return sz->serializeAsElement(sName,pNamespace,pValue,(XSDTYPE)type);
                else 
                   return sz->serializeAsElement(sName,pValue,(XSDTYPE)type);
            }
        }
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
int axiscSerializeAsAttribute(AXISCHANDLE wrapperSoapSerializer, 
                              const AxiscChar * sName, 
                              const AxiscChar * pNamespace, 
                              void * pValue, 
                              AXISC_XSDTYPE type) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->serializeAsAttribute(sName,pNamespace,pValue,(XSDTYPE)type);
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
void axiscSerializeStartElementOfType(AXISCHANDLE wrapperSoapSerializer, 
                                      const AxiscChar * pName, 
                                      const AxiscChar * pNamespace, 
                                      const AxiscChar * pPrefix) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->serializeStartElementOfType(pName,pNamespace,pPrefix);
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
void axiscSerializeEndElementOfType(AXISCHANDLE wrapperSoapSerializer, 
                                    const AxiscChar * pName) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->serializeEndElementOfType(pName);
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
AXISC_PROVIDERTYPE axiscGetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return (AXISC_PROVIDERTYPE)(sz->getCurrentProviderType());
    }
    catch ( AxisException& e  )
    {
        axiscInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return ::UNKNOWN_PROVIDER;
}

AXISC_STORAGE_CLASS_INFO 
void axiscSetCurrentProviderType(AXISCHANDLE wrapperSoapSerializer, 
                                 AXISC_PROVIDERTYPE nType) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->setCurrentProviderType((PROVIDERTYPE)nType);
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
int axiscAddOutputAnyObject(AXISCHANDLE wrapperSoapSerializer, 
                            AxiscAnyType * pAnyObject) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->addOutputAnyObject((AnyType*)pAnyObject);
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
int axiscSerializeAnyObject(AXISCHANDLE wrapperSoapSerializer, 
                            AxiscAnyType * pAnyObject) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->serializeAnyObject((AnyType*)pAnyObject);
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
int axiscSerializeAsChardata(AXISCHANDLE wrapperSoapSerializer, 
                             void * pValue, 
                             AXISC_XSDTYPE type) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return sz->serializeAsChardata(pValue,(XSDTYPE)type);
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
void axiscAddAttachment(AXISCHANDLE wrapperSoapSerializer, 
                        const AxiscChar * achId, 
                        AXISCHANDLE objAttach) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->addAttachment(achId,(ISoapAttachment*)objAttach);
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
void axiscAddAttachmentBody(AXISCHANDLE wrapperSoapSerializer, 
                            const AxiscChar * achId, 
                            xsdc__base64Binary * pAttchBody) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->addAttachmentBody(achId,(xsd__base64Binary*)pAttchBody);
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
void axiscAddAttachmentHeader(AXISCHANDLE wrapperSoapSerializer, 
                              const AxiscChar * achId, 
                              const AxiscChar * achHeaderName, 
                              const AxiscChar * achHeaderValue) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        sz->addAttachmentHeader(achId,achHeaderName,achHeaderValue);
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
AXISCHANDLE axiscCreateSoapAttachmentSoapAttachment(AXISCHANDLE wrapperSoapSerializer) 
{
    IWrapperSoapSerializer *sz = (IWrapperSoapSerializer*)wrapperSoapSerializer;

    try
    {
        return (AXISCHANDLE)(sz->createSoapAttachment());
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

AXISC_STORAGE_CLASS_INFO void axiscSerializeIWrapperSoapSerializer(AXISCHANDLE wrapperSoapSerializer, 
                                                                   const char *pFirst, 
                                                                   ...) 
{
    SoapSerializer *sz = (SoapSerializer*)wrapperSoapSerializer;

    try
    {
        // TODO: There were problems getting the ... to work properly, so serializeVargs was
        // introduced. Also wsdl2ws only ever calls this method with one parameter so
        // ignore the extra parameters here for the moment. This should be fixed properly
        // later. I think SoapSerializer::serialize is wrong to assume that the variable
        // list of parameters will be terminated by a null pointer. I think we should always
        // pass in an explicit parameter count here.
        sz->serializeVargs(1,&pFirst);
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

}
