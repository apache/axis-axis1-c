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
 *   @class Element
 *   @brief 
 *   @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */

#if !defined(AXIS_ELEMENT_H__INCLUDED_)
#define AXIS_ELEMENT_H__INCLUDED_

#include "Event.h"

class Element : public Event  
{
public:
    Element();
    virtual ~Element();
    string m_Namespace;
public:
    virtual XML_NODE_TYPE GetType() { return END_ELEMENT;};
};

class StartPrefix : public Element
{
    virtual XML_NODE_TYPE GetType() { return START_PREFIX;};        
};

class EndPrefix : public Element
{
    virtual XML_NODE_TYPE GetType() { return END_PREFIX;};        
};

typedef Element EndElement;


#endif 

