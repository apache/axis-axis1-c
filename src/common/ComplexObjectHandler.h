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

#if !defined(_COMPLEXOBJECTHANDLER_H____OF_AXIS_INCLUDED_)
#define _COMPLEXOBJECTHANDLER_H____OF_AXIS_INCLUDED_

#include <axis/server/AxisUserAPI.hpp>
#include <axis/server/AxisWrapperAPI.hpp>

AXIS_CPP_NAMESPACE_START

/*
 *  @class ComplexObjectHandler
 *  @brief
 *
 *  @author Susantha Kumara (skumara@virtusa.com)
 */
class ComplexObjectHandler
{
public:
    void* pObject;
    AXIS_SERIALIZE_FUNCT pSZFunct;
    AXIS_OBJECT_CREATE_FUNCT pCreFunct;
    AXIS_OBJECT_DELETE_FUNCT pDelFunct;
    AXIS_DESERIALIZE_FUNCT pDZFunct;
    AXIS_OBJECT_SIZE_FUNCT pSizeFunct;
    AxisString m_TypeName;
    AxisString m_URI;
public:
    ComplexObjectHandler();
    ~ComplexObjectHandler();
    void init();
};

AXIS_CPP_NAMESPACE_END

#endif 

