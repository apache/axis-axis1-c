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
 
 /*
  * @file Pattern.hpp
  */
  
#if !defined(_PATTERN_HPP____OF_AXIS_INCLUDED_)
#define _PATTERN_HPP____OF_AXIS_INCLUDED_

#include "IConstrainingFacet.hpp"
#include "../../AxisSoapException.h"

AXIS_CPP_NAMESPACE_START

/**
 *   @class Pattern
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class Pattern : private IConstrainingFacet {

public:

    Pattern();
    
    Pattern(AxisChar* pattern);
    
    ~Pattern();

    void validatePattern(const AxisChar* value) throw (AxisSoapException);
    
    bool isSet();

private:
    AxisChar* m_Pattern;

};

AXIS_CPP_NAMESPACE_END

#endif
