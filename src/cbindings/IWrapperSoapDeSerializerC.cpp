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

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/AxisUserAPIArrays.h>
#include <axis/BasicNode.h>
#include <axis/SoapEnvVersions.h>
#include <axis/IWrapperSoapDeSerializer.h>

AXIS_CPP_NAMESPACE_USE

extern "C" {


// Following helper function will create a C-binding type of array from a 
// C++ array
static Axisc_Array *generateCBindingArray(Axisc_Array *cArray, Axis_Array*objArray, bool deleteObjArray=false)
{ 
    // If nothing to transform, return
    if (objArray == NULL)
        return cArray;
             
    // Allocate cbinding array and initialize
    if (cArray == NULL)
        cArray = (Axisc_Array *)axiscAxisNew(XSDC_ARRAY, 0);
    
    // Get object array stuff
    XSDTYPE m_Type;
    int     m_Size;
    void ** m_Array = objArray->get(m_Size, m_Type);
    
    cArray->m_Size = m_Size;
    cArray->m_Type = (AXISC_XSDTYPE)m_Type;
    
    // Now generate the array
    if (m_Array != NULL && m_Size > 0)
    {
        cArray->m_Array = new void*[m_Size];
        
        for (int count = 0 ; count < m_Size ; count++)
        {
            if ( m_Array[count] == NULL)
            {
                cArray->m_Array[count] = NULL;
                continue;
            }
    
            switch (m_Type)
            {
                case XSD_DURATION:
                {
                    ((xsd__duration**) cArray->m_Array)[count] = new xsd__duration();
                    *((xsd__duration**)cArray->m_Array)[count] = *((xsd__duration**) m_Array)[count];
                    break;
                }
                case XSD_DATETIME:
                {
                    ((xsd__dateTime**) cArray->m_Array)[count] = new xsd__dateTime();
                    *((xsd__dateTime**)cArray->m_Array)[count] = *((xsd__dateTime**) m_Array)[count];
                    break;
                }
                case XSD_TIME:
                {
                    ((xsd__time**) cArray->m_Array)[count] = new xsd__time();
                    *((xsd__time**)cArray->m_Array)[count] = *((xsd__time**) m_Array)[count];
                    break;
                }
                case XSD_DATE:
                {
                    ((xsd__date**) cArray->m_Array)[count] = new xsd__date();
                    *((xsd__date**)cArray->m_Array)[count] = *((xsd__date**) m_Array)[count];
                    break;
                }
                case XSD_GYEARMONTH:
                {
                    ((xsd__gYearMonth**) cArray->m_Array)[count] = new xsd__gYearMonth();
                    *((xsd__gYearMonth**)cArray->m_Array)[count] = *((xsd__gYearMonth**) m_Array)[count];
                    break;
                }           
                case XSD_GYEAR:
                {
                    ((xsd__gYear**) cArray->m_Array)[count] = new xsd__gYear();
                    *((xsd__gYear**)cArray->m_Array)[count] = *((xsd__gYear**) m_Array)[count];
                    break;
                }
                case XSD_GMONTHDAY:
                {
                    ((xsd__gMonthDay**) cArray->m_Array)[count] = new xsd__gMonthDay();
                    *((xsd__gMonthDay**)cArray->m_Array)[count] = *((xsd__gMonthDay**) m_Array)[count];
                    break;
                }
                case XSD_GDAY:
                {
                    ((xsd__gDay**) cArray->m_Array)[count] = new xsd__gDay();
                    *((xsd__gDay**)cArray->m_Array)[count] = *((xsd__gDay**) m_Array)[count];
                    break;
                }
                case XSD_GMONTH:
                {
                    ((xsd__gMonth**) cArray->m_Array)[count] = new xsd__gMonth();
                    *((xsd__gMonth**)cArray->m_Array)[count] = *((xsd__gMonth**) m_Array)[count];
                    break;
                }
                case XSD_STRING:
                {
                    ((xsd__string*) cArray->m_Array)[count] = new char[strlen(((xsd__string*) m_Array)[count])+1];
                    strcpy(((xsd__string*) cArray->m_Array)[count], ((xsd__string*) m_Array)[count]);
                    break;
                }
                case XSD_NORMALIZEDSTRING:
                {
                    ((xsd__normalizedString*) cArray->m_Array)[count] = new char[strlen(((xsd__normalizedString*) m_Array)[count])+1];
                    strcpy(((xsd__normalizedString*) cArray->m_Array)[count], ((xsd__normalizedString*) m_Array)[count]);
                    break;
                }
                case XSD_TOKEN:
                {
                    ((xsd__token*) cArray->m_Array)[count] = new char[strlen(((xsd__token*) m_Array)[count])+1];
                    strcpy(((xsd__token*) cArray->m_Array)[count], ((xsd__token*) m_Array)[count]);
                    break;
                }
                case XSD_LANGUAGE:
                {
                    ((xsd__language*) cArray->m_Array)[count] = new char[strlen(((xsd__language*) m_Array)[count])+1];
                    strcpy(((xsd__language*) cArray->m_Array)[count], ((xsd__language*) m_Array)[count]);
                    break;
                }
                case XSD_NAME:
                {
                    ((xsd__Name*) cArray->m_Array)[count] = new char[strlen(((xsd__Name*) m_Array)[count])+1];
                    strcpy(((xsd__Name*) cArray->m_Array)[count], ((xsd__Name*) m_Array)[count]);
                    break;
                }
                case XSD_NCNAME:
                {
                    ((xsd__NCName*) cArray->m_Array)[count] = new char[strlen(((xsd__NCName*) m_Array)[count])+1];
                    strcpy(((xsd__NCName*) cArray->m_Array)[count], ((xsd__NCName*) m_Array)[count]);
                    break;
                }
                case XSD_ID:
                {
                    ((xsd__ID*) cArray->m_Array)[count] = new char[strlen(((xsd__ID*) m_Array)[count])+1];
                    strcpy(((xsd__ID*) cArray->m_Array)[count], ((xsd__ID*) m_Array)[count]);
                    break;
                }
                case XSD_IDREF:
                {
                    ((xsd__IDREF*) cArray->m_Array)[count] = new char[strlen(((xsd__IDREF*) m_Array)[count])+1];
                    strcpy(((xsd__IDREF*) cArray->m_Array)[count], ((xsd__IDREF*) m_Array)[count]);
                    break;
                }
                case XSD_IDREFS:
                {
                    ((xsd__IDREFS*) cArray->m_Array)[count] = new char[strlen(((xsd__IDREFS*) m_Array)[count])+1];
                    strcpy(((xsd__IDREFS*) cArray->m_Array)[count], ((xsd__IDREFS*) m_Array)[count]);
                    break;
                }
                case XSD_ENTITY:
                {
                    ((xsd__ENTITY*) cArray->m_Array)[count] = new char[strlen(((xsd__ENTITY*) m_Array)[count])+1];
                    strcpy(((xsd__ENTITY*) cArray->m_Array)[count], ((xsd__ENTITY*) m_Array)[count]);
                    break;
                }
                case XSD_ENTITIES:
                {
                    ((xsd__ENTITIES*) cArray->m_Array)[count] = new char[strlen(((xsd__ENTITIES*) m_Array)[count])+1];
                    strcpy(((xsd__ENTITIES*) cArray->m_Array)[count], ((xsd__ENTITIES*) m_Array)[count]);
                    break;
                }
                case XSD_NMTOKEN:
                {
                    ((xsd__NMTOKEN*) cArray->m_Array)[count] = new char[strlen(((xsd__NMTOKEN*) m_Array)[count])+1];
                    strcpy(((xsd__NMTOKEN*) cArray->m_Array)[count], ((xsd__NMTOKEN*) m_Array)[count]);
                    break;
                }
                case XSD_NMTOKENS:
                {
                    ((xsd__NMTOKENS*) cArray->m_Array)[count] = new char[strlen(((xsd__NMTOKENS*) m_Array)[count])+1];
                    strcpy(((xsd__NMTOKENS*) cArray->m_Array)[count], ((xsd__NMTOKENS*) m_Array)[count]);
                    break;
                }
                case XSD_BOOLEAN:
                {
                    ((xsd__boolean**) cArray->m_Array)[count] = new xsd__boolean();
                    *((xsd__boolean**)cArray->m_Array)[count] = *((xsd__boolean**) m_Array)[count];
                    break;
                }
                case XSD_BASE64BINARY:
                {
                    // TODO
                    ((xsdc__base64Binary**) cArray->m_Array)[count] = new xsdc__base64Binary();
                    *((xsdc__base64Binary**)cArray->m_Array)[count] = *((xsdc__base64Binary**) m_Array)[count];
                    break;
                }
                case XSD_HEXBINARY:
                {
                    // TODO
                    ((xsdc__hexBinary**) cArray->m_Array)[count] = new xsdc__hexBinary();
                    *((xsdc__hexBinary**)cArray->m_Array)[count] = *((xsdc__hexBinary**) m_Array)[count];
                    break;
                }
                case XSD_FLOAT:
                {
                    ((xsd__float**) cArray->m_Array)[count] = new xsd__float();
                    *((xsd__float**)cArray->m_Array)[count] = *((xsd__float**) m_Array)[count];
                    break;
                }
                case XSD_DECIMAL:
                {
                    ((xsd__decimal**) cArray->m_Array)[count] = new xsd__decimal();
                    *((xsd__decimal**)cArray->m_Array)[count] = *((xsd__decimal**) m_Array)[count];
                    break;
                }
                case XSD_INTEGER:
                {
                    ((xsd__integer**) cArray->m_Array)[count] = new xsd__integer();
                    *((xsd__integer**)cArray->m_Array)[count] = *((xsd__integer**) m_Array)[count];
                    break;
                }
                case XSD_NONPOSITIVEINTEGER:
                {
                    ((xsd__nonPositiveInteger**) cArray->m_Array)[count] = new xsd__nonPositiveInteger();
                    *((xsd__nonPositiveInteger**)cArray->m_Array)[count] = *((xsd__nonPositiveInteger**) m_Array)[count];
                    break;
                }
                case XSD_NEGATIVEINTEGER:
                {
                    ((xsd__negativeInteger**) cArray->m_Array)[count] = new xsd__negativeInteger();
                    *((xsd__negativeInteger**)cArray->m_Array)[count] = *((xsd__negativeInteger**) m_Array)[count];
                    break;
                }
                case XSD_LONG:
                {
                    ((xsd__long**) cArray->m_Array)[count] = new xsd__long();
                    *((xsd__long**)cArray->m_Array)[count] = *((xsd__long**) m_Array)[count];
                    break;
                }
                case XSD_INT:
                {
                    ((xsd__int**) cArray->m_Array)[count] = new xsd__int();
                    *((xsd__int**)cArray->m_Array)[count] = *((xsd__int**) m_Array)[count];
                    break;
                }
                case XSD_SHORT:
                {
                    ((xsd__short**) cArray->m_Array)[count] = new xsd__short();
                    *((xsd__short**)cArray->m_Array)[count] = *((xsd__short**) m_Array)[count];
                    break;
                }
                case XSD_BYTE:
                {
                    ((xsd__byte**) cArray->m_Array)[count] = new xsd__byte();
                    *((xsd__byte**)cArray->m_Array)[count] = *((xsd__byte**) m_Array)[count];
                    break;
                }
                case XSD_NONNEGATIVEINTEGER:
                {
                    ((xsd__nonNegativeInteger**) cArray->m_Array)[count] = new xsd__nonNegativeInteger();
                    *((xsd__nonNegativeInteger**)cArray->m_Array)[count] = *((xsd__nonNegativeInteger**) m_Array)[count];
                    break;
                }
                case XSD_UNSIGNEDLONG:
                {
                    ((xsd__unsignedLong**) cArray->m_Array)[count] = new xsd__unsignedLong();
                    *((xsd__unsignedLong**)cArray->m_Array)[count] = *((xsd__unsignedLong**) m_Array)[count];
                    break;
                }
                case XSD_UNSIGNEDINT:
                {
                    ((xsd__unsignedInt**) cArray->m_Array)[count] = new xsd__unsignedInt();
                    *((xsd__unsignedInt**)cArray->m_Array)[count] = *((xsd__unsignedInt**) m_Array)[count];
                    break;
                }
                case XSD_UNSIGNEDSHORT:
                {
                    ((xsd__unsignedShort**) cArray->m_Array)[count] = new xsd__unsignedShort();
                    *((xsd__unsignedShort**)cArray->m_Array)[count] = *((xsd__unsignedShort**) m_Array)[count];
                    break;
                }
                case XSD_UNSIGNEDBYTE:
                {
                    ((xsd__unsignedByte**) cArray->m_Array)[count] = new xsd__unsignedByte();
                    *((xsd__unsignedByte**)cArray->m_Array)[count] = *((xsd__unsignedByte**) m_Array)[count];
                    break;
                }
                case XSD_POSITIVEINTEGER:
                {
                    ((xsd__positiveInteger**) cArray->m_Array)[count] = new xsd__positiveInteger();
                    *((xsd__positiveInteger**)cArray->m_Array)[count] = *((xsd__positiveInteger**) m_Array)[count];
                    break;
                }
                case XSD_DOUBLE:
                {
                    ((xsd__double**) cArray->m_Array)[count] = new xsd__double();
                    *((xsd__double**)cArray->m_Array)[count] = *((xsd__double**) m_Array)[count];
                    break;
                }
                case XSD_ANYURI:
                {
                    ((xsd__anyURI*) cArray->m_Array)[count] = new char[strlen(((xsd__anyURI*) m_Array)[count])+1];
                    strcpy(((xsd__anyURI*) cArray->m_Array)[count], ((xsd__anyURI*) m_Array)[count]);
                    break;
                }
                case XSD_QNAME:
                {
                    ((xsd__QName*) cArray->m_Array)[count] = new char[strlen(((xsd__QName*) m_Array)[count])+1];
                    strcpy(((xsd__QName*) cArray->m_Array)[count], ((xsd__QName*) m_Array)[count]);
                    break;
                }
                case XSD_NOTATION:
                {
                    ((xsd__NOTATION*) cArray->m_Array)[count] = new char[strlen(((xsd__NOTATION*) m_Array)[count])+1];
                    strcpy(((xsd__NOTATION*) cArray->m_Array)[count], ((xsd__NOTATION*) m_Array)[count]);
                    break;
                }
                case XSD_ARRAY:
                {
                    // TODO
                    cArray->m_Array[count] = m_Array[count];
                    break;
                }
                case USER_TYPE:
                {
                    // TODO
                    cArray->m_Array[count] = m_Array[count];
                    break;
                }
                case XSD_UNKNOWN:
                case XSD_ANY:
                case ATTACHMENT:
                default:
                    break;
            } // end switch
        } // end for loop
    }
    
    // delete c++ object array if requested to do so before returning
    if (deleteObjArray)
        delete objArray;
    
    return cArray;
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerCheckMessageBody(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
Axisc_Array* axiscSoapDeSerializerGetCmplxArray(AXISCHANDLE wrapperSoapDeSerializer, 
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
        Axis_Array  tmpObjArray;
        
        tmpObjArray.set((void **)pArray->m_Array, pArray->m_Size, (XSDTYPE)pArray->m_Type);
        
        Axis_Array* pObjArray = dz->getCmplxArray(&tmpObjArray, 
                                                  pDZFunct, pCreFunct, pDelFunct, pSizeFunct, 
                                                  pName, pNamespace);
        
        return generateCBindingArray(pArray, pObjArray, false);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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

    try
    {
        Axis_Array* pObjArray = dz->getBasicArray((XSDTYPE)nType, pName, pNamespace);
        return generateCBindingArray(NULL, pObjArray, true);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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

    try
    {
        return dz->getCmplxObject(pDZFunct,pCreFunct,pDelFunct,pName,pNamespace);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (void *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscSoapDeSerializerGetElementAsInt(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscSoapDeSerializerGetElementAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscSoapDeSerializerGetElementAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscSoapDeSerializerGetElementAsShort(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscSoapDeSerializerGetElementAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscSoapDeSerializerGetElementAsByte(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscSoapDeSerializerGetElementAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscSoapDeSerializerGetElementAsLong(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscSoapDeSerializerGetElementAsInteger(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscSoapDeSerializerGetElementAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscSoapDeSerializerGetElementAsFloat(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscSoapDeSerializerGetElementAsDouble(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscSoapDeSerializerGetElementAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscSoapDeSerializerGetElementAsString(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscSoapDeSerializerGetElementAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscSoapDeSerializerGetElementAsQName(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscSoapDeSerializerGetElementAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                     const AxiscChar * pName, 
                                                                     const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        xsd__hexBinary * pObjCpp = dz->getElementAsHexBinary(pName, pNamespace);
        
        if (!pObjCpp)
            return (xsdc__hexBinary *)NULL;
        
        // Get info from c++ Object
        int hexDataSize;
        xsd__unsignedByte *hexData = pObjCpp->get(hexDataSize);
                       
        // Create c-style equivalent object
        xsdc__hexBinary * pObjC = (xsdc__hexBinary *)axiscAxisNew(XSDC_HEXBINARY, hexDataSize);
        
        // populate c-style object with data from c++ object
        if (hexDataSize > 0)
        {
            memcpy(pObjC->__ptr, hexData, hexDataSize);
            pObjC->__ptr[hexDataSize] = '\0';
        }
        
        // Delete c++ object before returning c object
        delete pObjCpp;       
        return pObjC;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscSoapDeSerializerGetElementAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                           const AxiscChar * pName, 
                                                                           const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        xsd__base64Binary * pObjCpp = dz->getElementAsBase64Binary(pName, pNamespace);
        
        if (!pObjCpp)
            return (xsdc__base64Binary *)NULL;
        
        // Get info from c++ Object
        int base64BinaryDataSize;
        xsd__unsignedByte *base64BinaryData = pObjCpp->get(base64BinaryDataSize);
                       
        // Create c-style equivalent object
        xsdc__base64Binary * pObjC = (xsdc__base64Binary *)axiscAxisNew(XSDC_BASE64BINARY, base64BinaryDataSize);
        
        // populate c-style object with data from c++ object
        if (base64BinaryDataSize > 0)
        {
            memcpy(pObjC->__ptr, base64BinaryData, base64BinaryDataSize);
            pObjC->__ptr[base64BinaryDataSize] = '\0';
        }
        
        // Delete c++ object before returning c object
        delete pObjCpp;       
        return pObjC;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscSoapDeSerializerGetElementAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscSoapDeSerializerGetElementAsDate(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscSoapDeSerializerGetElementAsTime(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscSoapDeSerializerGetElementAsDuration(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__duration *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__int * axiscSoapDeSerializerGetAttributeAsInt(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__int *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__boolean * axiscSoapDeSerializerGetAttributeAsBoolean(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__boolean *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedInt * axiscSoapDeSerializerGetAttributeAsUnsignedInt(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedInt *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__short * axiscSoapDeSerializerGetAttributeAsShort(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__short *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedShort * axiscSoapDeSerializerGetAttributeAsUnsignedShort(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedShort *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__byte * axiscSoapDeSerializerGetAttributeAsByte(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__byte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedByte * axiscSoapDeSerializerGetAttributeAsUnsignedByte(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedByte *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__long * axiscSoapDeSerializerGetAttributeAsLong(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__long *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__integer * axiscSoapDeSerializerGetAttributeAsInteger(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__integer *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__unsignedLong * axiscSoapDeSerializerGetAttributeAsUnsignedLong(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__unsignedLong *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__float * axiscSoapDeSerializerGetAttributeAsFloat(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__float *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__double * axiscSoapDeSerializerGetAttributeAsDouble(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__double *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__decimal * axiscSoapDeSerializerGetAttributeAsDecimal(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__decimal *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__string axiscSoapDeSerializerGetAttributeAsString(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__string)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__anyURI axiscSoapDeSerializerGetAttributeAsAnyURI(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__anyURI)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__QName axiscSoapDeSerializerGetAttributeAsQName(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__QName)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__hexBinary * axiscSoapDeSerializerGetAttributeAsHexBinary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                       const AxiscChar * pName, 
                                                                       const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        xsd__hexBinary * pObjCpp = dz->getAttributeAsHexBinary(pName, pNamespace);
        
        if (!pObjCpp)
            return (xsdc__hexBinary *)NULL;
        
        // Get info from c++ Object
        int hexDataSize;
        xsd__unsignedByte *hexData = pObjCpp->get(hexDataSize);
                       
        // Create c-style equivalent object
        xsdc__hexBinary * pObjC = (xsdc__hexBinary *)axiscAxisNew(XSDC_HEXBINARY, hexDataSize);
        
        // populate c-style object with data from c++ object
        if (hexDataSize > 0)
        {
            memcpy(pObjC->__ptr, hexData, hexDataSize);
            pObjC->__ptr[hexDataSize] = '\0';
        }
        
        // Delete c++ object before returning c object
        delete pObjCpp;       
        return pObjC;        
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__hexBinary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__base64Binary * axiscSoapDeSerializerGetAttributeAsBase64Binary(AXISCHANDLE wrapperSoapDeSerializer, 
                                                                             const AxiscChar * pName, 
                                                                             const AxiscChar * pNamespace) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        xsd__base64Binary * pObjCpp = dz->getAttributeAsBase64Binary(pName, pNamespace);
        
        if (!pObjCpp)
            return (xsdc__base64Binary *)NULL;
        
        // Get info from c++ Object
        int base64BinaryDataSize;
        xsd__unsignedByte *base64BinaryData = pObjCpp->get(base64BinaryDataSize);
                       
        // Create c-style equivalent object
        xsdc__base64Binary * pObjC = (xsdc__base64Binary *)axiscAxisNew(XSDC_BASE64BINARY, base64BinaryDataSize);
        
        // populate c-style object with data from c++ object
        if (base64BinaryDataSize > 0)
        {
            memcpy(pObjC->__ptr, base64BinaryData, base64BinaryDataSize);
            pObjC->__ptr[base64BinaryDataSize] = '\0';
        }
        
        // Delete c++ object before returning c object
        delete pObjCpp;       
        return pObjC;
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__base64Binary *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__dateTime * axiscSoapDeSerializerGetAttributeAsDateTime(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__dateTime *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__date * axiscSoapDeSerializerGetAttributeAsDate(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__date *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__time * axiscSoapDeSerializerGetAttributeAsTime(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__time *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
xsdc__duration * axiscSoapDeSerializerGetAttributeAsDuration(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (xsdc__duration *)NULL;
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
    
    return -1;
}

AXISC_STORAGE_CLASS_INFO 
int axiscSoapDeSerializerGetHeader(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->getHeader();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return AXISC_FAIL;
}

AXISC_STORAGE_CLASS_INFO 
AxiscAnyType * axiscSoapDeSerializerGetAnyObject(AXISCHANDLE wrapperSoapDeSerializer) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AxiscAnyType*)(dz->getAnyObject());
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AxiscAnyType *)NULL;
}

AXISC_STORAGE_CLASS_INFO 
void axiscSoapDeSerializerGetChardataAs(AXISCHANDLE wrapperSoapDeSerializer, 
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
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }
}

AXISC_STORAGE_CLASS_INFO 
AXISCHANDLE axiscSoapDeSerializerGetAttachmentSoapAttachment(AXISCHANDLE wrapperSoapDeSerializer, 
                                             const char * pcAttachmentid) 
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return (AXISCHANDLE)(dz->getAttachment(pcAttachmentid));
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (AXISCHANDLE)NULL;
}

AXISC_STORAGE_CLASS_INFO
const char * axiscSoapDeSerializerPeekNextElementName(AXISCHANDLE wrapperSoapDeSerializer)
{
    IWrapperSoapDeSerializer *dz = (IWrapperSoapDeSerializer*)wrapperSoapDeSerializer;

    try
    {
        return dz->peekNextElementName();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what());
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.");
    }

    return (const char *)NULL;
}

}
