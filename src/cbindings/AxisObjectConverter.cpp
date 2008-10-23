/* -*- C++ -*- */
/*
 *   Copyright 2006-2006 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2006, 2006 All Rights Reserved
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
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/Axis.h>
#include "AxisObjectConverter.hpp"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

AxiscAnyType *
AxisObjectConverter::cppAnyTypeToC(AnyType *objAnyType, 
                                   AxiscAnyType *cAnyType, 
                                   bool deleteObj)
{
    // If nothing to transform, return
    if (objAnyType == NULL)
        return cAnyType;
            
    // Allocate cAnyType and initialize
    if (cAnyType == NULL)
        cAnyType = (AxiscAnyType *)axiscAxisNew(XSDC_ANY, 0);

    cAnyType->_size = objAnyType->_size;
    
    // If we are going to delete the object, simply copy the array pointer
    // to c structure. 
    if (deleteObj)
    {
    	cAnyType->_array = objAnyType->_array;
    	objAnyType->_array = NULL;
    	objAnyType->_size = 0;
    }
    else
    {
	    int len;
	    if (cAnyType->_size > 0)
	    {
	        cAnyType->_array = new AXISC_XML_String [cAnyType->_size];
	        
	        for (int i=0; i<cAnyType->_size; ++i)
	        {
	            if ( objAnyType->_array[i] == NULL)
	            {
	                cAnyType->_array[i] = NULL;
	                continue;
	            }      
	            
	            len = strlen(objAnyType->_array[i]) + 1;
	            cAnyType->_array[i] = new char[len];     
	            strcpy(cAnyType->_array[i], objAnyType->_array[i]);
	        }
	    }
    }

    // Delete c++ object before returning c object
    if (deleteObj)
        delete objAnyType;
                
    return cAnyType;
}

Axisc_Array *
AxisObjectConverter::cppArrayToC(Axis_Array *objArray, 
                                 Axisc_Array *cArray, 
                                 bool deleteObj)
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
	            case XSD_STRING:
	            {
	                ((xsd__string*) cArray->m_Array)[count] = new char[strlen(((xsd__string*) m_Array)[count])+1];
	                strcpy(((xsd__string*) cArray->m_Array)[count], ((xsd__string*) m_Array)[count]);
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
                    cArray->m_Array[count] = cppBase64BinaryToC((xsd__base64Binary *)m_Array[count], NULL, false); 
                    break;
                }
                case XSD_HEXBINARY:
                {
                    cArray->m_Array[count] = cppHexBinaryToC((xsd__hexBinary *)m_Array[count], NULL, false);
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
                case XSD_ANYTYPE:
                {
                    ((xsd__anyType*) cArray->m_Array)[count] = new char[strlen(((xsd__anyType*) m_Array)[count])+1];
                    strcpy(((xsd__anyType*) cArray->m_Array)[count], ((xsd__anyType*) m_Array)[count]);
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
    if (deleteObj)
        delete objArray;
    
    return cArray;
}                      

xsdc__base64Binary *
AxisObjectConverter::cppBase64BinaryToC(xsd__base64Binary *objBase64Bin, 
                                        xsdc__base64Binary *cBase64Bin, 
                                        bool deleteObj)
{
    // Nothing to transform, return.       
    if (!objBase64Bin)
        return (xsdc__base64Binary *)NULL;
    
    // Get info from c++ Object
    int base64BinaryDataSize;
    xsd__unsignedByte *base64BinaryData = objBase64Bin->get(base64BinaryDataSize);
                   
    // Create c-style equivalent object
    xsdc__base64Binary * pObjC = (xsdc__base64Binary *)axiscAxisNew(XSDC_BASE64BINARY, base64BinaryDataSize);
    
    // populate c-style object with data from c++ object
    if (base64BinaryDataSize > 0)
    {
        memcpy(pObjC->__ptr, base64BinaryData, base64BinaryDataSize);
        pObjC->__ptr[base64BinaryDataSize] = '\0';
    }
    
    // Delete c++ object before returning c object
    if (deleteObj)
        delete objBase64Bin;       
    
    return pObjC;
}

xsdc__hexBinary *
AxisObjectConverter::cppHexBinaryToC(xsd__hexBinary *objHexBin, 
                                     xsdc__hexBinary *cHexBin, 
                                     bool deleteObj)
{
    // If nothing to transform, return.
    if (!objHexBin)
        return (xsdc__hexBinary *)NULL;
    
    // Get info from c++ Object
    int hexDataSize;
    xsd__unsignedByte *hexData = objHexBin->get(hexDataSize);
                   
    // Create c-style equivalent object
    xsdc__hexBinary * pObjC = (xsdc__hexBinary *)axiscAxisNew(XSDC_HEXBINARY, hexDataSize);
    
    // populate c-style object with data from c++ object
    if (hexDataSize > 0)
    {
        memcpy(pObjC->__ptr, hexData, hexDataSize);
        pObjC->__ptr[hexDataSize] = '\0';
    }
    
    // Delete c++ object before returning c object
    if (deleteObj)
        delete objHexBin;    
           
    return pObjC;
}

AXIS_CPP_NAMESPACE_END
