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

#include "DeserializerPool.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

DeserializerPool::DeserializerPool ()
{

}

DeserializerPool::~DeserializerPool ()
{
    for (list < SoapDeSerializer* >::iterator it = m_DZList.begin ();
        it != m_DZList.end (); it++)
    {
        delete (*it);
    }
}

int DeserializerPool::GetInstance (SoapDeSerializer** ppDZ)
{
    lock ();
    if (!m_DZList.empty ())
    {
        *ppDZ = m_DZList.front ();
        m_DZList.pop_front ();
    }
    else
    {
        *ppDZ = new SoapDeSerializer ();
        if (AXIS_SUCCESS != (*ppDZ)->Init ())
        {
            delete* ppDZ;
            *ppDZ = NULL;
            unlock ();
            AXISTRACE1 ("Deserializer could not be initialized", CRITICAL);
            return AXIS_FAIL;
        }
    }
    unlock ();
    return AXIS_SUCCESS;
}

int DeserializerPool::PutInstance (SoapDeSerializer* pDZ)
{
    if (AXIS_SUCCESS != pDZ->Init ())
    {
        delete pDZ;
        return AXIS_FAIL;
    }
    lock ();
    m_DZList.push_back (pDZ);
    unlock ();
    return AXIS_SUCCESS;
}
