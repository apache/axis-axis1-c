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


// !!! Must be first thing in file !!!
#include "../../../platforms/PlatformAutoSense.hpp"

#include "../../../common/AxisTrace.h"

#include "HTTPChannel.hpp"

// Instanciate functions for HTTPChannel instances.

extern "C"
{
    // CreateInstance() Is a C interface.
    STORAGE_CLASS_INFO int CreateInstance( HTTPChannel ** inst)
    {
        int iSuccess = AXIS_FAIL;

        *inst = new HTTPChannel();

        if (*inst)
        {
            iSuccess = AXIS_SUCCESS;
        }

        return iSuccess;
    }

    // DestroyInstance() Is a C interface.
    STORAGE_CLASS_INFO int DestroyInstance( HTTPChannel * inst)
    {
        int iSuccess = AXIS_FAIL;

        if (inst)
        {
            delete inst;

            iSuccess = AXIS_SUCCESS;
        }

        return iSuccess;
    }

    /*  initializeLibrary() Is a C interface.
     */
    STORAGE_CLASS_INFO void initializeLibrary (void)
    {
        // Do init actions
    }

    /*  uninitializeLibrary() Is a C interface.
     */
    STORAGE_CLASS_INFO void uninitializeLibrary (void)
    {
        // Do uninit actions
    }
}
