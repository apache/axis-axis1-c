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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__AXIS_H_OF_AXIS_INCLUDED__)
#define __AXIS_H_OF_AXIS_INCLUDED__

#include <axis/server/GDefine.hpp>

AXIS_CPP_NAMESPACE_START

class STORAGE_CLASS_INFO Axis
{
  public:
    static void initialize(bool bIsServer);
    static void terminate();
};

AXIS_CPP_NAMESPACE_END

#endif // !defined(__AXIS_H_OF_AXIS_INCLUDED__)





