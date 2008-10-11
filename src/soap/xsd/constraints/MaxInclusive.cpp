// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// !!! This include file must be first thing in file !!!
#include "../../../platforms/PlatformAutoSense.hpp"

#include "MaxInclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MaxInclusive::MaxInclusive(LONGLONG maxInclusive)
    {
        m_MaxInclusive.longlongMaxInclusive = maxInclusive;
        m_isSet = true;
    }

    MaxInclusive::MaxInclusive(unsigned LONGLONG maxInclusive)
    {
        m_MaxInclusive.unsignedLongLongMaxInclusive = maxInclusive;
        m_isSet = true;
    }

    MaxInclusive::MaxInclusive(double maxInclusive)
    {
        m_MaxInclusive.doubleMaxInclusive = maxInclusive;
        m_isSet = true;
    }
    
    MaxInclusive::MaxInclusive(struct tm maxInclusive)
    {
        m_MaxInclusive.structTMMaxInclusive = maxInclusive;
        m_isSet = true;
    }

    MaxInclusive::MaxInclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MaxInclusive::getMaxInclusiveAsLONGLONG()
    {
        return m_MaxInclusive.longlongMaxInclusive;
    }

    unsigned LONGLONG MaxInclusive::getMaxInclusiveAsUnsignedLONGLONG()
    {
        return m_MaxInclusive.unsignedLongLongMaxInclusive;
    }
    
    double MaxInclusive::getMaxInclusiveAsDouble()
    {
        return m_MaxInclusive.doubleMaxInclusive;
    }
    
    struct tm MaxInclusive::getMaxInclusiveAsStructTM()
    {
        return m_MaxInclusive.structTMMaxInclusive;
    }
    
AXIS_CPP_NAMESPACE_END
