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

#include "MaxExclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MaxExclusive::MaxExclusive(LONGLONG maxExclusive)
    {
        m_MaxExclusive.longlongMaxExclusive = maxExclusive;
        m_isSet = true;
    }

    MaxExclusive::MaxExclusive(unsigned LONGLONG maxExclusive)
    {
        m_MaxExclusive.unsignedLongLongMaxExclusive = maxExclusive;
        m_isSet = true;
    }

    MaxExclusive::MaxExclusive(double maxExclusive)
    {
        m_MaxExclusive.doubleMaxExclusive = maxExclusive;
        m_isSet = true;
    }
    
    MaxExclusive::MaxExclusive(struct tm maxExclusive)
    {
        m_MaxExclusive.structTMMaxExclusive = maxExclusive;
        m_isSet = true;
    }

    MaxExclusive::MaxExclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MaxExclusive::getMaxExclusiveAsLONGLONG()
    {
        return m_MaxExclusive.longlongMaxExclusive;
    }

    unsigned LONGLONG MaxExclusive::getMaxExclusiveAsUnsignedLONGLONG()
    {
        return m_MaxExclusive.unsignedLongLongMaxExclusive;
    }
    
    double MaxExclusive::getMaxExclusiveAsDouble()
    {
        return m_MaxExclusive.doubleMaxExclusive;
    }
    
    struct tm MaxExclusive::getMaxExclusiveAsStructTM()
    {
        return m_MaxExclusive.structTMMaxExclusive;
    }
    
AXIS_CPP_NAMESPACE_END
