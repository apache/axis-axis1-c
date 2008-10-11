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

#include "Pattern.hpp"

AXIS_CPP_NAMESPACE_START

    Pattern::Pattern():m_Pattern(NULL)
    {
        m_isSet = false;
    }

    Pattern::Pattern(AxisChar* pattern)
    {
        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
        m_Pattern = pattern;
        m_isSet = true;
    }
    
    Pattern::~Pattern()
    {
        if(m_Pattern)
        {
            delete [] m_Pattern;
            m_Pattern = NULL;
        }
    }

    void Pattern::validatePattern(const AxisChar* value) throw (AxisSoapException)
    {
     /*
      * Currently has no effect.
      * Needs to validate the given string matches the regular expression
      * provided to the constructor.
      */
    }

AXIS_CPP_NAMESPACE_END
