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
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

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
    protected:
        int unlock ();
        int lock ();
    private:
        bool m_bLocked;
#ifdef WIN32
    HANDLE          mut;
#else                           //Linux
    pthread_mutex_t *mut;
#endif
};

AXIS_CPP_NAMESPACE_END

#endif 
