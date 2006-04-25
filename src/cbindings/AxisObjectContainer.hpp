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
 */

#if !defined(_AXISOBJECTCONTAINER_HPP_OF_AXIS_INCLUDED_)
#define _AXISOBJECTCONTAINER_HPP_OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#include <axis/AxisException.hpp>

 /**
  * @file AxisObjectContainer.hpp
  * This file contains a container class that will store various C++ AXIS objects
  * such as Call and Stub.  Instead of returning a opaque pointer to a Call object
  * or a Stub object, we will return an opaque pointer to the container class. 
  * The main purpose of the container class is to enable a C client to determine 
  * the status of a call against an object and to retrieve error information regarding
  * any failures.  This will be done via new C binding APIs.  Without this support
  * there would be no way for a C client to determine success or failure of an operation
  * since a C client cannot catch C++ exceptions.  The C binding APIs will catch all 
  * C++ exceptions and store error status in the AxisObjectContainer class.  
  * 
  * In the generated C stubs, the C stub code will check to see if any errors happened,
  * and if one did occur, will simply return to caller. It is up to the caller to then
  * determine status of operation by invoke xxxxxxxx against the handle passed into
  * the operation.  
  * 
  */
AXIS_CPP_NAMESPACE_START
class AxisObjectContainer
{
public :
    /** Constructor */
    AxisObjectContainer(void *objHandle): _objHandle(objHandle) { }
    
    /** Destructor */
    ~AxisObjectContainer() { }
        
    /** object handle */
    void *          _objHandle;
    
    /** object exception data */
    AxisException   _exception;
};

AXIS_CPP_NAMESPACE_END



#endif
