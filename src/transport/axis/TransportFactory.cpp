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


#include "Platform.hpp"
#include "TransportFactory.hpp"
#include "HttpTransport.hpp"
#include <axis/server/GDefine.hpp>


Transport* TransportFactory::GetTransport(Url& url, bool secure)
{
    if(url.GetProtocol() == Url::http)
    {
        return new HttpTransport(url, UNSECURE);
    }
    else if(url.GetProtocol() == Url::https)
    {
        return new HttpTransport(url, SECURE); /* currently not supported */
    }
    else if(url.GetProtocol() == Url::ftp)
    {
        return NULL; /* currently not supported */
    }
    else
        return NULL; /* currently not supported */
}

