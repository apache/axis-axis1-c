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

#if !defined(AXIS_IARRAYBEAN_H__OF_AXIS_INCLUDED_)
#define AXIS_IARRAYBEAN_H__OF_AXIS_INCLUDED_

#include <axis/server/GDefine.hpp>
#include <axis/server/AxisUserAPI.hpp>
/*
 *   @class IArrayBean
 *   @brief interface for the IArrayBean class.
 *
 *
 *   @author Susantha Kumara (skumara@virtusa.com)
*/

AXIS_CPP_NAMESPACE_START

class IArrayBean
{
    public:
        IArrayBean ()
        {
        };
    virtual ~ IArrayBean ()
    {
    };
    // API needed for the Wrapper class to manipulate ArrayBeans
    virtual void SetDimension (int nDim) = 0;
    virtual void SetItemName (const AxisChar* sName) = 0;
    virtual void SetTypeName (const AxisChar* sName) = 0;
    virtual void SetUri (const AxisChar* sURI) = 0;
};

AXIS_CPP_NAMESPACE_END

#endif 
