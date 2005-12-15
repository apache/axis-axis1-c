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
 * @file AnyElement.h
 * This file contains the declaration of AnyElement structure which is
 * returned by any parser's (implementation of XMLParser interface) next(..)
 * funtion.
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

/*
 * Revision 1.1  2004/12/01 roshan
 * Added the new class "AnyElemntUtils". Here we have a method to convers a 
 *  AnyElement to a string.
 */

 
#if !defined(__ANYELEMENT_H__OF_AXIS_INCLUDED_)
#define __ANYELEMENT_H__OF_AXIS_INCLUDED_

#include <string>

using namespace std;

/**
 * @def MAX_NO_OF_ATTRIBUTES
 * Defines the maximum number of attributes that AnyElement can contain.
 * @note If any starting tag of a SOAP message contains more than 100
 * attributes a runtime error can occur.
 */
#define MAX_NO_OF_ATTRIBUTES 100

/**
 * @enum XML_NODE_TYPE
 * Enumeration that defines the SAX events that the AnyElement may contain
 */
typedef enum { START_ELEMENT=0, CHARACTER_ELEMENT, END_ELEMENT, 
    START_PREFIX, END_PREFIX, START_END_ELEMENT, UNKNOWN} XML_NODE_TYPE;

/**
 * @struct AnyElement
 *
 * This structure can represent any xml element that a SOAP message contains.
 * Any parser implementation's next(..) or anyNext() methods will return a 
 * constant instance of this struct that will contain a xml element. In SAX 
 * parser perspective this structure can contain information of StartElement, 
 * EndElement, Character data element or a prefix mapping event.
 *
 * @brief Struct that represents any XML element.
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
typedef struct 
{
    /**
     * Type of SAX event whose data that an AnyElement can contain.
     */
    XML_NODE_TYPE m_type;

    // This is to handle empty elements, e.g. <tag/>, where start and end events are fired at once
    XML_NODE_TYPE m_type2;

    /**
     * Local name in case of StartElement or EndElement event. Character data
     * in case of character data event. Namespace prefix in case of prefix 
	 * prefix mapping event.
     */
    const char* m_pchNameOrValue;
    /**
     * Namespace of StartElemnt or EndElement tag. In case there is no 
	 * namespace this should be NULL (not pointing to empty string "" even)
     */
    const char* m_pchNamespace;
    /**
     * Each attribute has 3 entities: localname, namespace and value in order
     * This char* array can contain upto MAX_NO_OF_ATTRIBUTES attributes. When
     * a parser fills in this array the order should be localname, namespace
     * and then value. If there is no prefix in an attribute the namespace
     * should be NULL (note: The localname can never be null for an attribute.
     * Then anyone consuming these attributes will increment the index by 3
     * starting from 0 (0, 3, 6 ... etc) and if that position in the array is
     * NULL it is understood as the end of attributes.
     */
    const char* m_pchAttributes[MAX_NO_OF_ATTRIBUTES*3]; 
} AnyElement;

/*
 * The AnyElement utility class.
 */
class AnyElemntUtils
{
    public:
        static string toString(const AnyElement* pNode)
        {
            string sTmpVal;              			                                                                                                                                                  
            switch(pNode->m_type)
            {
                case CHARACTER_ELEMENT:
                    sTmpVal = string(pNode->m_pchNameOrValue);
                    break;
                case END_ELEMENT:
                    //sTmpVal = "<" + pNode->m_pchNameOrValue + ;
                    break;
                case START_ELEMENT:
                    //TODO.
                    break;
                case START_PREFIX:
                    break;
                case END_PREFIX:
                    break;
                case START_END_ELEMENT:
                    break;
                case UNKNOWN:
                    break;
            }
            return sTmpVal;
        }
};

#endif

