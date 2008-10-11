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

#include "MinInclusive.hpp"

AXIS_CPP_NAMESPACE_START

    MinInclusive::MinInclusive(LONGLONG minInclusive)
    {
        m_MinInclusive.longlongMinInclusive = minInclusive;
        m_isSet = true;
    }

    MinInclusive::MinInclusive(unsigned LONGLONG minInclusive)
    {
        m_MinInclusive.unsignedLongLongMinInclusive = minInclusive;
        m_isSet = true;
    }

    MinInclusive::MinInclusive(double minInclusive)
    {
        m_MinInclusive.doubleMinInclusive = minInclusive;
        m_isSet = true;
    }
    
    MinInclusive::MinInclusive(struct tm minInclusive)
    {
        m_MinInclusive.structTMMinInclusive = minInclusive;
        m_isSet = true;
    }

    MinInclusive::MinInclusive()
    {
        m_isSet = false;
    }
    
    LONGLONG MinInclusive::getMinInclusiveAsLONGLONG()
    {
        return m_MinInclusive.longlongMinInclusive;
    }

    unsigned LONGLONG MinInclusive::getMinInclusiveAsUnsignedLONGLONG()
    {
        return m_MinInclusive.unsignedLongLongMinInclusive;
    }
    
    double MinInclusive::getMinInclusiveAsDouble()
    {
        return m_MinInclusive.doubleMinInclusive;
    }
    
    struct tm MinInclusive::getMinInclusiveAsStructTM()
    {
        return m_MinInclusive.structTMMinInclusive;
    }
    
AXIS_CPP_NAMESPACE_END
