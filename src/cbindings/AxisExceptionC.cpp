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
#include <axis/AxisException.hpp>
AXIS_CPP_NAMESPACE_USE

extern "C" {
#include <axis/GDefine.h>
#include <axis/AxisUserAPI.h>
#include <axis/AxisException.h>

AXISC_STORAGE_CLASS_INFO 
void axiscExceptionDestroy(AXISCHANDLE axisException) 
{
	AxisException *ae = (AxisException*)axisException;
	delete ae;
}

AXISC_STORAGE_CLASS_INFO 
const char * axiscExceptionWhat(AXISCHANDLE axisException) 
{
	AxisException *ae = (AxisException*)axisException;
	return ae->what();
}

AXISC_STORAGE_CLASS_INFO 
const int axiscExceptionGetExceptionCode(AXISCHANDLE axisException) 
{
	AxisException *ae = (AxisException*)axisException;
	return ae->getExceptionCode();
}

}


