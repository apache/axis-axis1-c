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

#include "AnyElement.h"
#include "Packet.h"
#include <axis/SOAPTransport.h>

#if !defined(__XMLPARSER_H_OF_AXIS_INCLUDED__)
#define __XMLPARSER_H_OF_AXIS_INCLUDED__

/**
 * @class XMLParser
 * @brief Interface that any parser wrapper should implement in order to be use 
 *        in Axis as a XML PULL parser. Its the responsibility of the implementation
 *        class to free any memory allocated inside the class. The class should not 
 *		  deallocate either the given input stream or any memory buffers that it gets
 *		  from the stream.
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
class XMLParser
{
public:
    virtual ~XMLParser(){};
	/**
	 * Sets the input stream. Here the parser object should also be initialized
	 * to its initial state. Axis will call this function first for each input 
	 * stream to be parsed.
	 *
	 * @param pInputStream Input stream from which the data to be parsed taken
	 *		  by calling its getBytes function. Function should not deallocate
	 *        either pInputStream or any memory buffers that it gets.
	 */
    virtual int setInputStream(AxisIOStream* pInputStream)=0;
	/**
	 * Used to get the corresponding namespace string for a given prefix.
	 *
	 * @param pcPrefix Prefix for which the namespace string is requested 
	 */
    virtual const XML_Ch* getNS4Prefix(const XML_Ch* pcPrefix)=0;
	/**
	 * Used to get the parser status. Should return AXIS_SUCCESS if nothing
	 * has gone wrong.
	 */
    virtual int getStatus()=0;
	/**
	 * Used to get the next XML event. The valid events are start element, end
	 * element and character data. If we think of SAX events the processing 
	 * instruction events, namespace prefix mapping events are not considered
	 * valid. If the implementation of this interface is wrapping up a SAX 
	 * parser it should follow the above rules.
	 *
	 * @param bIsCharData Indicates whether Axis is expecting a character data 
	 *		  event or not. If Axis is not expecting a character data event 
	 *		  (bIsCharData is false) the parser should not return a character 
	 *		  data event. Instead it should skip all character data events 
	 *	      until it finds a non-character data event and return it.
	 */
    virtual const AnyElement* next(bool bIsCharData=false)=0;
protected:
	AxisIOStream* m_pInputStream;

};

#endif

