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


#if !defined(_AXIS_AXIS_IPV6_TRANSPORT_HPP)
#define _AXIS_AXIS_IPV6_TRANSPORT_HPP

#include "../Axis2Transport.h"
#include "IPV6Channel.hpp"

#include <string>
#include <vector>

AXIS_CPP_NAMESPACE_USE 

using namespace std;

class IPV6Transport:public Axis2Transport
{
  public:
    IPV6Transport ();
    virtual ~ IPV6Transport ();

  /**
    * Sets the endpoint URI. 
    * Keeps track of the changes made to the URI. (Because if the URI changes, 
    * we cannot reuse the opned socket)
    * @param pcEndPointURI End point URI of the service to connect to.
    *                       e.g. http://localhost:8080/axis/services/echo
    */
    void setEndpointUri (const char *) throw (AxisTransportException);      
};

#endif
