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

#if !defined(AXIS_Event_H__OF_AXIS_INCLUDED_)
#define AXIS_Event_H__OF_AXIS_INCLUDED_

#include <axis/server/AnyElement.h>

#include <string>
using namespace std;

class Event  
{
public:
    Event();
    virtual ~Event();
	/* character data, element name or prefix(in case of prefix mapping event) */
    string m_NameOrValue; 
public:
    virtual XML_NODE_TYPE getType(){ return CHARACTER_ELEMENT;};
};

typedef Event CharElement;

#endif 


