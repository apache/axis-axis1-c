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
 */

#if !defined(AXIS_APPSCOPEHANDLERPOOL_H__INCLUDED_)
#define AXIS_APPSCOPEHANDLERPOOL_H__INCLUDED_

#include "SharedObject.h"
#include <axis/server/BasicHandler.h>

#include <map>
#include <list>
#include <string>

using namespace std;

/*
 *   @class AppScopeHandlerPool
 *   @brief interface for the AppScopeHandlerPool class.
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */

class AppScopeHandlerPool:protected SharedObject
{
    public:
        AppScopeHandlerPool ();
        virtual ~ AppScopeHandlerPool ();
    private:
        map < int, list <BasicHandler*> > m_Handlers;
    public:
        int GetInstance (BasicHandler** pHandler, int nLibId);
        int PutInstance (BasicHandler* pHandler, int nLibId);
};

#endif 
