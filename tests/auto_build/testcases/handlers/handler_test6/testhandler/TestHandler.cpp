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
 *
 *
 * @author Andrew Perry (perryan@uk.ibm.com)
 *
 *****************************************************************************
 * Test Logic.
 * Set a property in the request of the first handler in a chain and get the
 * property in the second handler in a chain and make sure they are the same.
 *
 * Test success is measured by comparing the actual response with an expected
 * response. So on failure just write anything to stdout and the test will 
 * fail.
 *****************************************************************************
 *
 *
 */

//
//////////////////////////////////////////////////////////////////////

#include "THandler.h"
#include <axis/GDefine.hpp>

extern "C" {
//the two export functions////////////////////////////////////////////

//Following describes how the export function of the handler DLLs (or .so s)

STORAGE_CLASS_INFO
int GetClassInstance(BasicHandler **inst)
{
	*inst = new BasicHandler();
	
	THandler* pTHandler = new THandler();
	(*inst)->_functions = 0;
	if (pTHandler)
	{
		(*inst)->_object = pTHandler;
		return pTHandler->init();
	}
	
	return AXIS_FAIL;
}

STORAGE_CLASS_INFO
int DestroyInstance(BasicHandler *inst)
{
	if (inst)
	{
		Handler* pH = static_cast<Handler*>(inst->_object);
		pH->fini();
		delete pH;
		delete inst;
		return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
}

}
