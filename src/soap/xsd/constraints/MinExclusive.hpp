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
  * @file MinExclusive.hpp
  */
  
#if !defined(_MINEXCLUSIVE_HPP____OF_AXIS_INCLUDED_)
#define _MINEXCLUSIVE_HPP____OF_AXIS_INCLUDED_

#include "IConstrainingFacet.hpp"
#include "../../../platforms/PlatformAutoSense.hpp"
#include <ctime>

AXIS_CPP_NAMESPACE_START

/**
 *   @class MinExclusive
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class MinExclusive : public IConstrainingFacet {

public:

    MinExclusive();
    
    MinExclusive(LONGLONG minExclusive);

    MinExclusive(unsigned LONGLONG minExclusive);
    
    MinExclusive(double minExclusive);
    
    MinExclusive(struct tm minExclusive);

    LONGLONG getMinExclusiveAsLONGLONG();

    unsigned LONGLONG getMinExclusiveAsUnsignedLONGLONG();
    
    double getMinExclusiveAsDouble();
    
    struct tm getMinExclusiveAsStructTM();
    
private:
    union
    {
      LONGLONG longlongMinExclusive;
      unsigned LONGLONG unsignedLongLongMinExclusive;
      double doubleMinExclusive;  
      struct tm structTMMinExclusive;
    } m_MinExclusive;

};

AXIS_CPP_NAMESPACE_END

#endif
