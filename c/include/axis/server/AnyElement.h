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

/**
    @class AnyElement
    @brief Struct that represents any XML element.
    @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
*/

#if !defined(__ANYELEMENT_H__OF_AXIS_INCLUDED_)
#define __ANYELEMENT_H__OF_AXIS_INCLUDED_

#define MAX_NO_OF_ATTRIBUTES 100

typedef enum { START_ELEMENT=0, CHARACTER_ELEMENT, END_ELEMENT, START_PREFIX, END_PREFIX} XML_NODE_TYPE;

typedef struct {
	XML_NODE_TYPE m_type;
	const char* m_pchNameOrValue;
	const char* m_pchNamespace;
	/* each attribute has 3 entities: localname, namespace, value in order */
	const char* m_pchAttributes[MAX_NO_OF_ATTRIBUTES*3]; 
} AnyElement;

#endif
