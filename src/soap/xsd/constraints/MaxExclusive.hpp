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
  * @file MaxExclusive.hpp
  */
  
#if !defined(_MAXEXCLUSIVE_HPP____OF_AXIS_INCLUDED_)
#define _MAXEXCLUSIVE_HPP____OF_AXIS_INCLUDED_

#include "IConstrainingFacet.hpp"
#include "../../../platforms/PlatformAutoSense.hpp"
#include <ctime>

AXIS_CPP_NAMESPACE_START

/**
 *   @class MaxExclusive
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class MaxExclusive : public IConstrainingFacet {

public:

    MaxExclusive();
    
    MaxExclusive(LONGLONG maxExclusive);
    
    MaxExclusive(double maxExclusive);
    
    MaxExclusive(struct tm maxExclusive);

    LONGLONG getMaxExclusiveAsLONGLONG();
    
    double getMaxExclusiveAsDouble();
    
    struct tm getMaxExclusiveAsStructTM();
    
private:
    union
    {
      LONGLONG longlongMaxExclusive;
      double doubleMaxExclusive;  
      struct tm structTMMaxExclusive;
    } m_MaxExclusive;

};

AXIS_CPP_NAMESPACE_END

#endif
