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

/*
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "../../common/AxisTrace.h"

#include "XMLParserXerces.h"
#include <xercesc/util/PlatformUtils.hpp>

#ifdef AXIS_XML4C
#include <unicode/uclean.h>
#endif

extern "C" {
STORAGE_CLASS_INFO
int CreateInstance(XMLParser **inst)
{
    /* TODO : Following initialization should be done within a function
              called by the library loader at loading time */
    XMLPlatformUtils::Initialize();
    *inst = new XMLParserXerces();
    if (*inst)
    {
        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;
}
STORAGE_CLASS_INFO 
int DestroyInstance(XMLParser *inst)
{
    if (inst)
    {
        delete inst;
    /* TODO : Following uninitialization should be done within a function
              called by the library loader at unloading time */
        XMLPlatformUtils::Terminate ();
#ifdef AXIS_XML4C
        u_cleanup();
#endif
        return AXIS_SUCCESS;
    }
    return AXIS_FAIL;
}

STORAGE_CLASS_INFO void initializeLibrary (void)
{
      // Do init actions
}

//  uninitializeLibrary() Is a C interface.
STORAGE_CLASS_INFO void uninitializeLibrary (void)
{
      // Do uninit actions
}

}
