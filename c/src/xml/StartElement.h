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
 *   @class 
 *   @brief 
 *   @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */

#if !defined(AXIS_STARTELEMENT_H__OF_AXIS_INCLUDED_)
#define AXIS_STARTELEMENT_H__OF_AXIS_INCLUDED_

#include <list>
using namespace std;

#include "Element.h"
#include "SimpleAttribute.h"

class StartElement : public Element  
{
public:
    StartElement();
    virtual ~StartElement();
    list<SimpleAttribute*> m_Attributes;
public:
    virtual XML_NODE_TYPE getType() { return START_ELEMENT;};
};


#endif 

