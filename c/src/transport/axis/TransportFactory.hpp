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
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */


#if !defined(_AXIS_TRANSPORTFACTORY_HPP)
#define _AXIS_TRANSPORTFACTORY_HPP


/*
 * Create undeline transport for SOAP-Envelops carrier for a given URL
 * URL determine which transport to be instantiated for carring SOAP Envelop.
 *
 * @todo    Hope this require of creating Transport by specifing a property
 *          such as name; not just the URL.
 * @brief   The Transport Factory to instantiate a Tranport for SOAP envelop 
 *          carring
 *
 */

#include "Transport.hpp"

class TransportFactory  
{
private:
    TransportFactory(){};
    virtual ~TransportFactory(){};
public:
    static Transport* GetTransport(Url& url, bool secure);
    /* return transport object according to URL info */
};

#endif


