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
 * @file XMLParser.h
 *
 * This file contains the API that any XML parser library for Axis should
 * implement.
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
 
#include "AnyElement.h"
#include "Packet.h"
#include <axis/SOAPTransport.h>

#if !defined(__XMLPARSER_H_OF_AXIS_INCLUDED__)
#define __XMLPARSER_H_OF_AXIS_INCLUDED__

/**
 * @class XMLParser
 * @brief Interface that any parser wrapper should implement in order to be
 *        use in Axis as a XML PULL parser. This interface basically describes
 *        XML pull parsing behavior. Any SAX or DOM parser can be wrapped to
 *        expose XML pull behavior by implementing this interface. But the
 *        efficiency of the overall component depends on the particular
 *        implementaion.
 *        Its the responsibility of the implementation class to free any
 *        memory allocated inside the class. The class should not deallocate
 *        the given input stream.
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
class XMLParser
{
public:
    virtual ~XMLParser(){};
    /**
     * Sets the input stream. Here the parser should be prepared to start
     * parsing a new stream and hence should be initialized to its initial
     * state. Axis will call this function first for each input stream to
     * be parsed.
     *
     * @brief  Sets the input stream.
     * @pre    The stream passed MUST be an already opened stream (established
     *         connection.
     * @param  pInputStream Input stream from which the data to be parsed are
     *         read by calling its getBytes function. Function should not
     *         deallocate either pInputStream
     * @return AXIS_SUCCESS if successfull. AXIS_FAIL otherwise.
     */
    virtual int setInputStream(AxisIOStream* pInputStream)=0;
    /**
     * Gets the corresponding namespace string for a given prefix. The
     * Parser should store the prefix/namespace pairs that it finds and
     * valid at the current cursor position of the stream. This method
     * provides a way to get the corresponding namespace for any valid
     * prefix at the current cursor position of the pull parser.
     *
     * @brief  Gets the corresponding namespace string for a given prefix.
     * @param  pcPrefix Prefix for which the namespace string is requested
     * @return The namespace if a match is found. NULL otherwise. 
     */
    virtual const XML_Ch* getNS4Prefix(const XML_Ch* pcPrefix)=0;
    /**
     * @brief  Used to get the parser status.
     * @return Returns AXIS_SUCCESS if nothing has gone wrong. AXIS_FAIL
     *         otherwise.
     */
    virtual int getStatus()=0;
    /**
     * Used to get the next XML data event. The valid events are start element, 
	 * end element and character data. If we think of SAX events the processing 
     * instruction events, namespace prefix mapping events are not returned by
     * this method. If the implementation of this interface is wrapping up a 
     * SAX parser it should follow the above rules.
     *
     * As the function signature suggests the returned AnyElement is const and
     * the caller should not deallocate any member of it. Its the sole
     * responsibility of the Parser wrapper implementation to manage any memory
     * allocated by it.
     *
     * @brief  Used to get the next XML event.
     * @param  bIsCharData Indicates whether Axis is expecting a character data 
     *         event or not. If Axis is NOT expecting a character data event 
     *         (bIsCharData is false) the parser should NOT return a character 
     *         data event. Instead it should skip all character data events 
     *         until it finds a non-character data event and return it. This
     *         behaviour is needed to ignore unexpected white space of the
     *         stream.
     * @return Returns a filled AnyElement structure that contains all the data
     *         of the current XML element. See AnyElement.h for the
     *         structure of AnyElement.
     */
    virtual const AnyElement* next(bool bIsCharData=false)=0;
    /**
     * Used to get the any next XML event. The valid events are start element,
     * end element, character data and prefix mappings. If we think of SAX  
     * events only processing instruction events are not returned by this
     * method. If the implementation of this interface is wrapping up a SAX 
     * parser it should follow the above rules.
     *
     * As the function signature suggests the returned AnyElement is const and
     * the caller should not deallocate any member of it. Its the sole
     * responsibility of the Parser wrapper implementation to manage any memory
     * allocated by it.
     *
     * @brief  Used to get the next XML event.
     * @return Returns a filled AnyElement structure that contains all the data
     *         of the current XML element. See AnyElement.h for the structure
     *         of AnyElement.
     */
    virtual const AnyElement* anyNext()=0;
    /**
     * Gets the corresponding prefix string for a given namespace. The
     * Parser should store the prefix/namespace pairs that it finds and
     * valid at the current cursor position of the stream. This method
     * provides a way to get the corresponding prefix for any valid
     * namespace at the current cursor position of the pull parser.
     *
     * @brief  Gets the corresponding namespace string for a given prefix.
     * @param  pcNS Namespace for which the prefix string is requested
     * @return The prefix if a match is found. NULL otherwise. 
     */
    virtual const XML_Ch* getPrefix4NS(const XML_Ch* pcNS)=0;
protected:
    AxisIOStream* m_pInputStream;

};

#endif

