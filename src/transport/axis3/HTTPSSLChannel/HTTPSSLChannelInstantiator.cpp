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
*/

/*
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#define AXISTRACE_LIBRARY_MAINENTRYPOINT
#include "../../../common/AxisTrace.h"

#ifdef WIN32
#pragma warning( disable : 4786)
#pragma warning( disable : 4101)
#endif

#include "HTTPSSLChannel.hpp"

// Instanciate functions for HTTPSSLChannel instances.

extern "C"
{
    // CreateInstance() Is a C interface.
    STORAGE_CLASS_INFO int CreateInstance( HTTPSSLChannel ** inst)
    {
		int iSuccess = AXIS_FAIL;

        *inst = new HTTPSSLChannel();

        if (*inst)
        {
            iSuccess = AXIS_SUCCESS;
        }

        return iSuccess;
    }

    // DestroyInstance() Is a C interface.
    STORAGE_CLASS_INFO int DestroyInstance( HTTPSSLChannel * inst)
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
    STORAGE_CLASS_INFO void initializeLibrary (AxisTraceEntrypoints& ep)
    {
        // Do init actions
        AxisTrace::setTraceEntrypoints(ep);
    }

    /*  uninitializeLibrary() Is a C interface.
     */
    STORAGE_CLASS_INFO void uninitializeLibrary (void)
    {
        // Do uninit actions
    }
}

