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

#ifdef WIN32
#include <ws2tcpip.h>
#include <tpipv6.h>  // For IPv6 Tech Preview.
#endif

class IPV6Channel: public Channel
{
public:
    IPV6Channel();
    virtual ~IPV6Channel();
    
    /* Open a socket to a given remote node/server address with remote port */
    virtual bool  open() throw (AxisTransportException&);

protected:
    /* OS specific initilization */
    virtual bool init();


   
};

#endif

