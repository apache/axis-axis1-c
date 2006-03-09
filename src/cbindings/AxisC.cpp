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
 
#include <iostream>
#include <axis/Axis.hpp>
#include <axis/AxisException.hpp>

AXIS_CPP_NAMESPACE_USE

extern "C" {
	#include <axis/GDefine.h>
	#include <axis/AxisUserAPI.h>
	#include <axis/TypeMapping.h>
	#include <axis/Axis.h>

// Create an object using the GlobalExceptionHandlerPrototype prototype.
	static GlobalExceptionHandlerPrototype * global_exceptionHandler = NULL;

	STORAGE_CLASS_INFO int axiscInitializeAxis( AxiscBool bIsServer) 
	{
		int rc = AXISC_SUCCESS;
	    
		try 
		{
			Axis::initialize( 0 == bIsServer);
		}
		catch( AxisException& e)
		{
			axiscInvokeExceptionHandler( e.getExceptionCode(), e.what());

			rc = AXISC_FAIL;    
		}
		catch( ...)
		{
			rc = AXISC_FAIL;
		}
	    
		return rc;
	} 

	STORAGE_CLASS_INFO int axiscTerminate() 
	{
		int rc = AXISC_SUCCESS;
	    
		try 
		{
			Axis::terminate();
		}
		catch( AxisException& e)
		{
			axiscInvokeExceptionHandler( e.getExceptionCode(), e.what());

			rc = AXISC_FAIL;    
		}
		catch( ...)
		{
			rc = AXISC_FAIL;
		}
	    
		return rc;
	}

	AXISC_STORAGE_CLASS_INFO int axiscAxisDelete( void * pValue, AXISC_XSDTYPE type)
	{
		int rc = AXISC_SUCCESS;
	    
		try 
		{
			Axis::AxisDelete(pValue, (XSDTYPE) type);
		}
		catch( AxisException& e)
		{
			axiscInvokeExceptionHandler( e.getExceptionCode(), e.what());

			rc = AXISC_FAIL;    
		}
		catch( ...)
		{
			rc = AXISC_FAIL;
		}    
	    
		return rc;
	}

	AXISC_STORAGE_CLASS_INFO void axiscRegisterExceptionHandler( void * fp)
	{
		global_exceptionHandler = (GlobalExceptionHandlerPrototype *) fp;
	}

	AXISC_STORAGE_CLASS_INFO void axiscInvokeExceptionHandler( int errorCode, const char * errorString)
	{
		if( global_exceptionHandler)
		{
			(global_exceptionHandler) (errorCode, errorString);
// Try?			(*global_exceptionHandler) (errorCode, errorString);
		}
		else
		{
			cerr <<  "AXIS EXCEPTION: (" << errorCode << ") " << errorString << endl;
		}
	}
}