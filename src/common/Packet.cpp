/* -*- C++ -*- */
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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include <axis/server/Packet.hpp>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <axis/server/AxisTrace.h>

extern "C"
{

/*
 * This method is used to add a transport specific property to a stream object 
 * for Axis supported protocols such as http. For an example "Content-Length" 
 * for http. For other protocols there should be a way to set these properties 
 * and its upto the transport module implementation to have those required 
 * methods. 
 */
    int set_property (Ax_soapstream* stream, char* pchkey, char* pchvalue)
    {
        int count;
        Ax_header* temp;
        switch (stream->trtype)
        {
            case APTHTTP:
                count = stream->so.http->op_headercount;
                temp = stream->so.http->op_headers;
                if (stream->so.http->op_headers) 
                {
                    stream->so.http->op_headers = new Ax_header[count + 1];
                    memcpy(stream->so.http->op_headers,temp,sizeof(Ax_header)*(count+1));
                    delete [] temp;
                }
                else
                    stream->so.http->op_headers = new Ax_header[count + 1];
                stream->so.http->op_headers[count].headername = pchkey;
                stream->so.http->op_headers[count].headervalue = pchvalue;
                stream->so.http->op_headercount = count + 1;
                return 0;
            case APTSMTP:return -1;
            default:return -1;
        }
    }

/*
 * This method is used to remove all transport specific properties from a stream
 * object for Axis supported protocols such as http. For an example "SOAPAction"
 * for http. 
 */
    void remove_all_properties (Ax_soapstream* stream)
    {
        switch (stream->trtype)
        {
            case APTHTTP:
                if (stream->so.http->ip_headercount > 0)
                {
                    stream->so.http->ip_headercount = 0;
                    delete [] stream->so.http->ip_headers;
                    stream->so.http->ip_headers = NULL;
                }
                if (stream->so.http->op_headercount > 0)
                {
                    stream->so.http->op_headercount = 0;
                    delete [] stream->so.http->op_headers;
                    stream->so.http->op_headers = NULL;
                }
                break;
            case APTSMTP:
                break;
            default:
                break;
        }
    }

    const char* get_property (const Ax_soapstream* stream, const char* pchkey)
    {
        const Ax_header* hdrs = NULL;
        int count = 0;
        switch (stream->trtype)
        {
            case APTHTTP:
                hdrs = stream->so.http->ip_headers;
                count = stream->so.http->ip_headercount;
                break;
            case APTFTP:
                //TODO
                break;
            case APTSMTP:
                //TODO
                break;
            default:; //some error condition
        }

        if (count == 0 || hdrs == NULL)
        {
            return NULL;
        }

        for (int ix = 0; ix < count; ix++)
        {
            if (strcmp ((hdrs + ix)->headername, pchkey) == 0)
            {
                return (hdrs + ix)->headervalue;
            }
        }
        return NULL;
    }
}
