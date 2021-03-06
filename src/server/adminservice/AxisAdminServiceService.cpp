/*
 * Copyright 2003-2006 The Apache Software Foundation.

 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains the two export functions of the Web service Dynamic Library 
 */

#include "AxisAdminServiceWrapper.hpp" 
extern "C" {
STORAGE_CLASS_INFO
int GetClassInstance(BasicHandler **inst)
{
    *inst = new BasicHandler();
    WrapperClassHandler* pWCH = new AxisAdminServiceWrapper();
    (*inst)->_functions = 0;
    if (pWCH)
    {
        (*inst)->_object = pWCH;
        return pWCH->init();
    }
    return AXIS_FAIL;
}
STORAGE_CLASS_INFO 
int DestroyInstance(BasicHandler *inst)
{
    if (inst)
    {
        WrapperClassHandler* pWCH = reinterpret_cast<WrapperClassHandler*>(inst->_object);
        pWCH->fini();
        delete pWCH;
        pWCH = NULL;
        delete inst;
        inst = NULL;
        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;
}
}
