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

#include "SharedObject.h"

AXIS_CPP_NAMESPACE_START

SharedObject::SharedObject ()
{
    m_bLocked = false;
#ifdef WIN32
#else //Linux
    mut = new pthread_mutex_t;
    pthread_mutex_init (mut, NULL);
#endif
}

SharedObject::~SharedObject ()
{
#ifdef WIN32
#else //Linux
    pthread_mutex_destroy (mut);
    delete mut;
#endif
}

/* Following functions should be improved to avoid chances of failure using 
 * platform specific mechanisms
 */ 
int SharedObject::lock ()
{
#ifdef WIN32
    while (m_bLocked)
    {
        Ax_Sleep (0);
    }

#else //Linux
    pthread_mutex_lock (mut);
#endif
    m_bLocked = true;
    return 0;
}

int SharedObject::unlock ()
{
#ifdef WIN32
#else //Linux
    pthread_mutex_unlock (mut);
#endif
    m_bLocked = false;
    return 0;
}

AXIS_CPP_NAMESPACE_END
