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
  * @file WhiteSpace.hpp
  */
  
#if !defined(_WHITESPACE_HPP____OF_AXIS_INCLUDED_)
#define _WHITESPACE_HPP____OF_AXIS_INCLUDED_

#include "IConstrainingFacet.hpp"

AXIS_CPP_NAMESPACE_START

const AxisChar WHITE_SPACE_CHARS[]    = "\t\r\n";

typedef enum
{
    PRESERVE, REPLACE, COLLAPSE
} whiteSpaceValue;

/**
 *   @class WhiteSpace
 *
 *   @author Adrian Dick (adrian.dick@uk.ibm.com)
 *
 */
class WhiteSpace : IConstrainingFacet {

public:




    WhiteSpace();
    
    WhiteSpace(whiteSpaceValue whiteSpace);
    
    bool isSet();

    const AxisChar* processWhiteSpace(const AxisChar* valueToProcess);


private:
    const AxisString& replaceWhiteSpace(AxisString& value);

    const AxisString& collapseWhiteSpace(AxisString& value);

    enum
    {
        TAB_CHARACTER = '\t',
        LINE_FEED_CHARACTER = '\r',
        CARRIAGE_RETURN_CHARACTER = '\n'
    };

    whiteSpaceValue m_WhiteSpace;

    AxisChar* m_Buf;

    AxisString m_strReturnVal;
};

AXIS_CPP_NAMESPACE_END

#endif
