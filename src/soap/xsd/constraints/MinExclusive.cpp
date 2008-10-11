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

#include "MinExclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MinExclusive::MinExclusive(LONGLONG minExclusive)
    {
        m_MinExclusive.longlongMinExclusive = minExclusive;
        m_isSet = true;
    }

    MinExclusive::MinExclusive(unsigned LONGLONG minExclusive)
    {
        m_MinExclusive.unsignedLongLongMinExclusive = minExclusive;
        m_isSet = true;
    }

    MinExclusive::MinExclusive(double minExclusive)
    {
        m_MinExclusive.doubleMinExclusive = minExclusive;
        m_isSet = true;
    }
    
    MinExclusive::MinExclusive(struct tm minExclusive)
    {
        m_MinExclusive.structTMMinExclusive = minExclusive;
        m_isSet = true;
    }

    MinExclusive::MinExclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MinExclusive::getMinExclusiveAsLONGLONG()
    {
        return m_MinExclusive.longlongMinExclusive;
    }

    unsigned LONGLONG MinExclusive::getMinExclusiveAsUnsignedLONGLONG()
    {
        return m_MinExclusive.unsignedLongLongMinExclusive;
    }
    
    double MinExclusive::getMinExclusiveAsDouble()
    {
        return m_MinExclusive.doubleMinExclusive;
    }
    
    struct tm MinExclusive::getMinExclusiveAsStructTM()
    {
        return m_MinExclusive.structTMMinExclusive;
    }
    
AXIS_CPP_NAMESPACE_END
