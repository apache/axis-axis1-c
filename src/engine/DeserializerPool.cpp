/* -*- C++ -*- */
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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include "DeserializerPool.h"

#include "../common/AxisTrace.h"

AXIS_CPP_NAMESPACE_START

using namespace std;


DeserializerPool::DeserializerPool()
{
	m_DZList.clear();
}

/*
 * ~DeserializerPool sometimes fails on AIX, so this method has been
 * recoded to make it more defensive and added extra trace. It fails
 * intermittently and the last line in the trace shows the exit of
 * the last ~SoapSerializer().
 * 
 * 
 */
DeserializerPool::~DeserializerPool ()
{
    list<IWrapperSoapDeSerializer*>::iterator it = m_DZList.begin();
	while (it != m_DZList.end())
    {
		IWrapperSoapDeSerializer *dz = *it;

#ifdef ENABLE_AXISTRACE
		if (AxisTrace::isTraceOn()) 
		{
			char text[256];
			sprintf(text, "~DeserializerPool<%p> dz=%p", this, dz);
			AxisTrace::traceLine(text);
		}
#endif

		if (NULL != dz)
	        delete dz;
		it++;
    }
	m_DZList.clear();
}

int DeserializerPool::getInstance (IWrapperSoapDeSerializer** ppDZ)
{
    //lock ();
	Lock l(this);
    if (!m_DZList.empty ())
    {
        *ppDZ = m_DZList.front ();
        m_DZList.pop_front ();
    }
    else
    {
        *ppDZ = new SoapDeSerializer ();
        if (AXIS_SUCCESS != ((SoapDeSerializer*)(*ppDZ))->init ())
        {
            delete* ppDZ;
            *ppDZ = NULL;
            //unlock ();
            AXISTRACE1 ("Deserializer could not be initialized", CRITICAL);
            return AXIS_FAIL;
        }
    }
    //unlock ();
    return AXIS_SUCCESS;
}

int DeserializerPool::putInstance (IWrapperSoapDeSerializer* pDZ)
{
    if (AXIS_SUCCESS != ((SoapDeSerializer*)pDZ)->init ())
    {
        delete pDZ;
        return AXIS_FAIL;
    }
    //lock ();
	Lock l(this);
    m_DZList.push_back (pDZ);
    //unlock ();
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
