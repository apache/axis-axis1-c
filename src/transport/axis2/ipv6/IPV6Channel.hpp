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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#if !defined(_AXIS_IPV6_CHANNEL_HPP)
#define _AXIS_IPV6_CHANNEL_HPP

#include <string>

#include "../Channel.h"

class IPV6Channel: public Channel
{
public:
    IPV6Channel();
    virtual ~IPV6Channel();
    
    /* Open a socket to a given remote node/server address with remote port */
    virtual bool  open() throw (AxisTransportException&);

    /* Read from a open socket and store read message in msg */
    //virtual const Channel& operator >> (std::string& msg);
    
    /* Read from socket in non bloking more in msg */
    //virtual const Channel& readNonBlocking(std::string& msg, bool bBlockingRequired);

    /* Write a given message (msg) to the end-point using the open socket */
    //virtual const Channel& operator << (const char* msg);
    

protected:
    /* OS specific initilization */
    virtual bool init();


    /* Close & clean-up the open socket/system resources */
    virtual void closeChannel();

	virtual void hexOutput( char * psData, int iDataLength);

  /**
    * @return 0 if timeout, 1 if input available, -1 if error.
    */
    int applyTimeout();
};

#endif

