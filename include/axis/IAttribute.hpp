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

 /**
 * @file IAttribute.h
 *
 *
 */
 
#if !defined(_IATTRIBUTE_H____OF_AXIS_INCLUDED_)
#define _IATTRIBUTE_H____OF_AXIS_INCLUDED_

#include <axis/server/GDefine.hpp>

AXIS_CPP_NAMESPACE_START

/**
 *   @class IAttribute
 *   @brief interface for the IAttribute class.
 *
 *   @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

class IAttribute
{
public:        

    virtual ~IAttribute() {};

    virtual void setValue(const AxisChar* value) = 0;
    virtual void setUri(const AxisChar* uri) = 0;
    virtual void setPrefix(const AxisChar* prefix) = 0;
    virtual void setLocalName(const AxisChar* localname) = 0;    
    virtual const AxisChar* getValue() = 0;
    virtual const AxisChar* getUri() = 0;
    virtual const AxisChar* getPrefix() = 0;
    virtual const AxisChar* getLocalName() = 0;
};

AXIS_CPP_NAMESPACE_END

#endif
