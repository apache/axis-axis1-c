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

#if !defined(__HANDLERLOADER_H_OF_AXIS_INCLUDED__)
#define __HANDLERLOADER_H_OF_AXIS_INCLUDED__

#include "../platforms/PlatformAutoSense.hpp"

#include "../common/MessageData.h"
#include <axis/server/GDefine.hpp>
#include <axis/server/WrapperClassHandler.hpp>
#include "SharedObject.h"
#include "AxisEngineException.h"
#include "../common/AxisConfigException.h"

#include <map>
#include <string>

using namespace std;

#define CREATE_FUNCTION "GetClassInstance"
#define DELETE_FUNCTION "DestroyInstance"

AXIS_CPP_NAMESPACE_START

typedef int (* CREATE_OBJECT) (BasicHandler** inst);
typedef int (* DELETE_OBJECT) (BasicHandler* inst);

AXIS_CPP_NAMESPACE_END


//status codes
/*#define HANDLER_INIT_FAIL	1
#define CREATION_FAILED		2
#define LOADLIBRARY_FAILED	3
#define LIBRARY_PATH_EMPTY	4
#define HANDLER_NOT_LOADED	5
#define HANDLER_BEING_USED	6
#define GET_HANDLER_FAILED	7
#define WRONG_HANDLER_TYPE	8
#define NO_HANDLERS_CONFIGURED	9
*/
/*
 *   @class HandlerLoader
 *   @brief
 *
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
 */
AXIS_CPP_NAMESPACE_START
class HandlerLoader:protected SharedObject
{
    private:
        class HandlerInformation
        {
            public:
                string m_sLib;
                int m_nLoadOptions;
                DLHandler m_Handler;
                CREATE_OBJECT m_Create;
                DELETE_OBJECT m_Delete;
                int m_nObjCount;
            public:
                HandlerInformation ()
                {
                    m_sLib = "";
                    m_nObjCount = 0;
                }
            };

            map <int, HandlerInformation*>m_HandlerInfoList;

    public:
        int createHandler (BasicHandler** pHandler, int nLibId);
        int deleteHandler (BasicHandler* pHandler, int nLibId);
        HandlerLoader ();
        ~HandlerLoader ();
    private:
        int loadLib (HandlerInformation* pHandlerInfo);
        int unloadLib (HandlerInformation* pHandlerInfo);
};
AXIS_CPP_NAMESPACE_END

#endif 
