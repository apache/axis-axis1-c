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

#if !defined(__XMLPARSER_H_OF_AXIS_INCLUDED__)
#define __XMLPARSER_H_OF_AXIS_INCLUDED__

/*
 * @class XMLParser
 * @brief Interface that any parser wrapper should implement in order to be use 
 *        in Axis as a SOAP parser.
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */
class XMLParser
{
public:
    virtual ~XMLParser(){};
    virtual int setInputStream(const Ax_soapstream* pInputStream)=0;
    virtual const Ax_soapstream* getInputStream()=0;
    virtual int init()=0;
    virtual const XML_Ch* getNS4Prefix(const XML_Ch* prefix)=0;
    virtual int getStatus()=0;
    virtual const AnyElement* next(bool isCharData=false)=0;
    virtual AXIS_TRANSPORT_STATUS getTransportStatus()=0;
    virtual void setTransportStatus(AXIS_TRANSPORT_STATUS nStatus)=0;

};

#endif

