/* -*- C++ -*- */
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
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include "SerializerPool.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START


SerializerPool::
SerializerPool ()
{
	logEntryEngine("SerializerPool::SerializerPool")

    logExit()
}

SerializerPool::
~SerializerPool ()
{
	logEntryEngine("SerializerPool::~SerializerPool")

    for (list <IWrapperSoapSerializer*>::iterator it = m_SZList.begin ();
         it != m_SZList.end (); it++)
    {
        delete (*it);
    }
	
    logExit()
}

// Pooling should be implemented
int SerializerPool::
getInstance (IWrapperSoapSerializer** ppSZ)
{
	logEntryEngine("SerializerPool::getInstance")

	Lock l(this);
	
	int Status = AXIS_SUCCESS;

    if (!m_SZList.empty ())
    {
        *ppSZ = m_SZList.front ();
        m_SZList.pop_front ();
    }
    else
    {
#ifdef USER_SERIALIZER
        *ppSZ = (IWrapperSoapSerializer*)GetUserSerializer();
#else
        *ppSZ = new SoapSerializer ();
#endif
        
    }
	
    if (AXIS_SUCCESS != ((SoapSerializer*)(*ppSZ))->init ())
    {
        delete *ppSZ;
        *ppSZ = NULL;
        Status = AXIS_FAIL;
    }
    
	logExitWithReturnCode(Status)
	
    return Status;
}

int SerializerPool::
putInstance (IWrapperSoapSerializer* pSZ)
{
	logEntryEngine("SerializerPool::putInstance")

	Lock l(this);

    m_SZList.push_back (pSZ);
    
	logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
