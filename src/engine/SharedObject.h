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
 */

#if !defined(AXIS_SHAREDOBJECT_H__OF_AXIS_INCLUDED_)
#define AXIS_SHAREDOBJECT_H__OF_AXIS_INCLUDED_

#include <axis/GDefine.hpp>
#ifdef WIN32
#include <windows.h>
#else //Linux
#include "pthread.h"
#endif
/*
 *   @class SharedObject
 *   @brief interface for the SharedObject class.
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

AXIS_CPP_NAMESPACE_START

class SharedObject
{
    public:
        SharedObject ();
        virtual ~ SharedObject ();
        int unlock ();
        int lock ();

    protected:
		class Lock
		{
			public:
				inline Lock();
				inline Lock(SharedObject *obj);
				inline ~Lock();
				inline void unlock();

			private:
				SharedObject *m_locked;
		};

	
	private:
        bool m_bLocked;
#ifdef WIN32
    HANDLE          mut;
#else                           //Linux
    pthread_mutex_t *mut;
#endif
};

// Inline functions
SharedObject::Lock::Lock() : m_locked(NULL)
{}

SharedObject::Lock::Lock(SharedObject *obj) 
{
    obj->lock();
    m_locked = obj;
}

SharedObject::Lock::~Lock()
{ 
    if (m_locked) m_locked->unlock(); 
}

void SharedObject::Lock::unlock()
{ 
    if (m_locked) 
    { 
        m_locked->unlock(); 
        m_locked = NULL; 
    } 
}

AXIS_CPP_NAMESPACE_END

#endif 
