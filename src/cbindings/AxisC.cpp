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

#include <stdarg.h>
#include <string>

#include <iostream>

#include <axis/ElementMissingException.hpp>
#include <axis/RedundantElementException.hpp>
#include <axis/UnknownElementException.hpp>

#include <axis/Axis.hpp>
#include <axis/AxisException.hpp>
#include <axis/AxisUserAPI.hpp>

#include <axis/Axis.h>
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/TypeMapping.h>

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_USE

extern "C" {

static AXIS_EXCEPTION_HANDLER_FUNCT global_exceptionHandler = NULL;

STORAGE_CLASS_INFO 
int axiscAxisInitialize(AxiscBool bIsServer) 
{
    int rc = AXISC_SUCCESS;
    
    try 
    {
        Axis::initialize(0==bIsServer);
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
        rc = AXISC_FAIL;    
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
        rc = AXISC_FAIL;
    }
    
    return rc;
} 

STORAGE_CLASS_INFO 
int axiscAxisTerminate() 
{
    int rc = AXISC_SUCCESS;
    
    try 
    {
        Axis::terminate();
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
        rc = AXISC_FAIL;    
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
        rc = AXISC_FAIL;
    }
    
    return rc;
}

AXISC_STORAGE_CLASS_INFO 
int axiscAxisDelete(void * pValue,  
                    AXISC_XSDTYPE type)
{
    int rc = AXISC_SUCCESS;
    
    try 
    {
        if (pValue == NULL)
            return rc;
            
        // There are some types we cannot pass to C++ engine
        switch (type)
        {
            case XSDC_DURATION:
            case XSDC_DATETIME:
            case XSDC_TIME:
            case XSDC_DATE:
            case XSDC_GYEARMONTH:
            case XSDC_GYEAR:
            case XSDC_GMONTHDAY:
            case XSDC_GDAY:
            case XSDC_GMONTH:
            case XSDC_STRING:
            case XSDC_NORMALIZEDSTRING:
            case XSDC_TOKEN:
            case XSDC_LANGUAGE:
            case XSDC_NAME:
            case XSDC_NCNAME:
            case XSDC_ID:
            case XSDC_IDREF:
            case XSDC_IDREFS:
            case XSDC_ENTITY:
            case XSDC_ENTITIES:
            case XSDC_NMTOKEN:
            case XSDC_NMTOKENS:
            case XSDC_BOOLEAN:
            case XSDC_FLOAT:
            case XSDC_DECIMAL:
            case XSDC_NONPOSITIVEINTEGER:
            case XSDC_NEGATIVEINTEGER:
            case XSDC_INTEGER:
            case XSDC_LONG:
            case XSDC_INT:
            case XSDC_SHORT:
            case XSDC_BYTE:
            case XSDC_NONNEGATIVEINTEGER:
            case XSDC_UNSIGNEDLONG:
            case XSDC_UNSIGNEDINT:
            case XSDC_UNSIGNEDSHORT:
            case XSDC_UNSIGNEDBYTE:
            case XSDC_POSITIVEINTEGER:
            case XSDC_DOUBLE:
            case XSDC_ANYURI:
            case XSDC_QNAME:
            case XSDC_NOTATION:
            case C_USER_TYPE:
            case C_ATTACHMENT:
            case XSDC_UNKNOWN:
            case XSDC_ANYTYPE:
            {
                Axis::AxisDelete(pValue, (XSDTYPE) type);
                break;
            }
            case XSDC_ARRAY:
            {
                Axisc_Array *array = (Axisc_Array*)pValue;
                
                // Delete array elements via recursion
                if (array->m_Array)
                {
                	for (int i=0; i<array->m_Size; ++i)
                    	if (array->m_Array[i])
                        	axiscAxisDelete(array->m_Array[i], array->m_Type);
                    delete [] array->m_Array;
                }

                // Delete array
                delete array;
                break;
            }
            case XSDC_BASE64BINARY:
            {
                xsdc__base64Binary* b64 = (xsdc__base64Binary*) pValue;
                if (b64->__ptr)
                    delete [] b64->__ptr;
                delete b64;
                break;
            }
            case XSDC_HEXBINARY:
            {
                xsdc__hexBinary* hb = (xsdc__hexBinary*) pValue;
                if (hb->__ptr)
                    delete [] hb->__ptr;
                delete hb;
                break;
            }
            case XSDC_ANY:
            {
                AxiscAnyType *anytype = (AxiscAnyType *)pValue;
				if (anytype->_size > 0 && anytype->_array) 
				{
					for (int i=0; i<anytype->_size; i++)
						if (anytype->_array[i]) 
							delete [] anytype->_array[i];
                    
                    delete [] anytype->_array;
				}
				delete anytype;
                break;
            }
            
            default:
                ;
        }
    }
    catch ( AxisException& e  )
    {
        axiscAxisInvokeExceptionHandler(e.getExceptionCode(), e.what(), NULL, NULL);
        rc = AXISC_FAIL;    
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
        rc = AXISC_FAIL;
    }    
    
    return rc;
}


AXISC_STORAGE_CLASS_INFO 
void *axiscAxisNew(AXISC_XSDTYPE type, int size)
{
    void *retVal=NULL;
    
    try 
    {            
        switch (type)
        {
            case XSDC_DURATION:
            {
                retVal = new xsd__duration();
                break;
            }
            case XSDC_DATETIME:
            {
                retVal = new xsd__dateTime();
                break;
            }
            case XSDC_TIME:
            {
                retVal = new xsd__time();
                break;
            }
            case XSDC_DATE:
            {
                retVal = new xsd__date();
                break;
            }
            case XSDC_GYEARMONTH:
            {
                retVal = new xsd__gYearMonth();
                break;
            }           
            case XSDC_GYEAR:
            {
                retVal = new xsd__gYear();
                break;
            }
            case XSDC_GMONTHDAY:
            {
                retVal = new xsd__gMonthDay();
                break;
            }
            case XSDC_GDAY:
            {
                retVal = new xsd__gDay();
                break;
            }
            case XSDC_GMONTH:
            {
                retVal = new xsd__gMonth();
                break;
            }
            case XSDC_STRING:
            case XSDC_NORMALIZEDSTRING:
            case XSDC_TOKEN:
            case XSDC_LANGUAGE:
            case XSDC_NAME:
            case XSDC_NCNAME:
            case XSDC_ID:
            case XSDC_IDREF:
            case XSDC_IDREFS:
            case XSDC_ENTITY:
            case XSDC_ENTITIES:
            case XSDC_NMTOKEN:
            case XSDC_NMTOKENS:
            case XSDC_ANYURI:
            case XSDC_QNAME:
            case XSDC_NOTATION:
            case XSDC_ANYTYPE:
            {
                retVal = new char[size+1];
                break;
            }
            case XSDC_BOOLEAN:
            {
                retVal = new xsd__boolean();
                break;
            }
            case XSDC_BASE64BINARY:
            {
                xsdc__base64Binary *b64bin = new xsdc__base64Binary();
                b64bin->__size=size;
                if (size > 0)
             		b64bin->__ptr = new xsdc__unsignedByte[size+1];
                else 
                	b64bin->__ptr=NULL;
                retVal = b64bin;
                break;
            }
            case XSDC_HEXBINARY:
            {
                xsdc__hexBinary *hexbin = new xsdc__hexBinary();
                hexbin->__size=size;
                if (size > 0)
             		hexbin->__ptr = new xsdc__unsignedByte[size+1];
                else
                	hexbin->__ptr=NULL;
                retVal = hexbin;
                break;
            }
            case XSDC_FLOAT:
            {
                retVal = new xsd__float();
                break;
            }
            case XSDC_DECIMAL:
            {
                retVal = new xsd__decimal();
                break;
            }
            case XSDC_INTEGER:
            {
                retVal = new xsd__integer();
                break;
            }
            case XSDC_NONPOSITIVEINTEGER:
            {
                retVal = new xsd__nonPositiveInteger();
                break;
            }
            case XSDC_NEGATIVEINTEGER:
            {
                retVal = new xsd__negativeInteger();
                break;
            }
            case XSDC_LONG:
            {
                retVal = new xsd__long();
                break;
            }
            case XSDC_INT:
            {
                retVal = new xsd__int();
                break;
            }
            case XSDC_SHORT:
            {
                retVal = new xsd__short();
                break;
            }
            case XSDC_BYTE:
            {
                retVal = new xsd__byte();
                break;
            }
            case XSDC_NONNEGATIVEINTEGER:
            {
                retVal = new xsd__nonNegativeInteger();
                break;
            }
            case XSDC_UNSIGNEDLONG:
            {
                retVal = new xsd__unsignedLong();
                break;
            }
            case XSDC_UNSIGNEDINT:
            {
                retVal = new xsd__unsignedInt();
                break;
            }
            case XSDC_UNSIGNEDSHORT:
            {
                retVal = new xsd__unsignedShort();
                break;
            }
            case XSDC_UNSIGNEDBYTE:
            {
                retVal = new xsd__unsignedByte();
                break;
            }
            case XSDC_POSITIVEINTEGER:
            {
                retVal = new xsd__positiveInteger();
                break;
            }
            case XSDC_DOUBLE:
            {
                retVal = new xsd__double();
                break;
            }
            case XSDC_ARRAY:
            {
                Axisc_Array * array = new Axisc_Array();
                array->m_Array = NULL;
                array->m_Size  = 0;
                array->m_Type  = XSDC_UNKNOWN;
                retVal = array;
                break;
            }
            case XSDC_ANY:
            {
                AxiscAnyType * anytype= new AxiscAnyType();
                anytype->_array = NULL;
                anytype->_size  = 0;
                retVal = anytype;
                break;
            }
            case C_USER_TYPE:
            case XSDC_UNKNOWN:
            case C_ATTACHMENT:
            default:
                break;
        }
    }
    catch ( ... )
    {
        axiscAxisInvokeExceptionHandler(-1, "Unrecognized exception thrown.", NULL, NULL);
    }    
    
    return retVal;
}


AXISC_STORAGE_CLASS_INFO 
int axiscAxisDeleteCArray(void ** pValue)
{
    delete [] pValue;
}


AXISC_STORAGE_CLASS_INFO 
void ** axiscAxisNewCArray(int size)
{
    if (size > 0)
        return new void *[size];
    else
        return (void **)NULL;
}



AXISC_STORAGE_CLASS_INFO 
void axiscAxisRegisterExceptionHandler( AXIS_EXCEPTION_HANDLER_FUNCT fp )
{
    global_exceptionHandler = fp;
}


AXISC_STORAGE_CLASS_INFO 
void axiscAxisInvokeExceptionHandler(int errorCode, 
                                     const char *errorString, 
                                     AXISCHANDLE pSoapFault, 
                                     void *faultDetail)
{
    if (global_exceptionHandler)
        global_exceptionHandler(errorCode, errorString, pSoapFault, faultDetail);
    else
        std::cerr <<  "AXIS EXCEPTION: (" << errorCode << ") " << errorString << std::endl;
}

AXISC_STORAGE_CLASS_INFO 
void axiscAxisGenerateElementMissingException(const char *s)
{
	throw ElementMissingException(s);
}

AXISC_STORAGE_CLASS_INFO 
void axiscAxisGenerateRedundantElementException(const char *s)
{
	throw RedundantElementException(s);
}

AXISC_STORAGE_CLASS_INFO 
void axiscAxisGenerateUnknownElementException(const char *s)
{
	throw UnknownElementException(s);
}

AXISC_STORAGE_CLASS_INFO
int axiscAxisStartTrace(const char* logFilePath, const char *logFilter)
{
	return Axis::startTrace(logFilePath, logFilter);
}

AXISC_STORAGE_CLASS_INFO
void axiscAxisStopTrace()
{
	Axis::stopTrace();
}

AXISC_STORAGE_CLASS_INFO
void axiscAxisWriteTrace(AXISC_TRACE_TYPE type, const char* functionName, const char * fmt, ...)
{
	// If logging is not enabled, just return.
	if (!AxisTrace::isLoggingEnabled() || !AxisTrace::isStubLoggingEnabled())
		return;
	
    // Construct final formatter
    std::string myfmt;
    std::string blank = " ";
    
    char *traceType = TRACE_TYPE_DEBUG;
    if (type == AXISC_TRACE_TYPE_ENTRY)
    	traceType = TRACE_TYPE_ENTRY;
    else if (type == AXISC_TRACE_TYPE_EXIT)
    	traceType = TRACE_TYPE_EXIT;
    else if (type == AXISC_TRACE_TYPE_EXCEPTION)
    	traceType = TRACE_TYPE_EXCEPT;
    
    if (NULL == fmt)
        fmt = "";
    myfmt += TRACE_COMPONENT_STUB + blank;
    myfmt += traceType + blank;
    myfmt += functionName;
    myfmt += "(): ";
    myfmt += fmt;
        
    va_list vargs;
    va_start(vargs,fmt);
    AxisTrace::writeTrace(myfmt.c_str(), vargs);        
    va_end(vargs);
}

}