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
  * @file TotalDigits.hpp
  */
  
#if !defined(_TOTALDIGITS_HPP____OF_AXIS_INCLUDED_)
#define _TOTALDIGITS_HPP____OF_AXIS_INCLUDED_

#include "IConstrainingFacet.hpp"

AXIS_CPP_NAMESPACE_START

/**
 *   @class TotalDigits
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class TotalDigits : public IConstrainingFacet {

public:

    TotalDigits();
    
    TotalDigits(int totalDigits);

    int getTotalDigits();
    
private:
    int m_TotalDigits;

};

AXIS_CPP_NAMESPACE_END

#endif
