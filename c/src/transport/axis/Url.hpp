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


#if !defined(_AXIS_URL_HPP)
#define _AXIS_URL_HPP

#include <string>

/* Welknown ports */
const unsigned short HTTP_PORT  = 80;
const unsigned short HTTPS_PORT = 443;
const unsigned short FTP_PORT   = 21;


/*
 *    Implementation of URL to manupulate URLs.  
 *
 *    This implementation only supports subset of a URL
 *    note that # references, userinfo query string 
 *    processing are not supported for this version.
 *
 *    URLs are of the form:
 * 
 *    URL              = protocol "://" server "/" [path]["?" query]
 *    server        = [userinfo "@"] hostname-port
 *    hostname-port = hostname [ ":" port ]
 *    userinfo      = user[:password]
 *
 *
 *    @brief    Manupulate URLs
 */


class Url  
{
public:

    enum Protocol { http, https, ftp, file, unknown}; 
    /* for our purpose currently we need http, https only. This is provided
     * To make extensible to support other transports for RPC but file????, 
     * yes we may require pipes; with web-service????
     */

public:
    Url();
    Url(std::string url);
    ~Url();

    void SetProtocol(std::string prot);
    void SetProtocol(Protocol prot){m_Protocol = prot;}
    void SetHostName(std::string host){m_Host= host;}
    void SetResource(std::string path){m_Path = path;}
    void SetPort(unsigned short port){m_Port = port;}

    Protocol    GetProtocol(){return m_Protocol;}
    std::string GetHostName(){return m_Host;}
    std::string GetResource(){return m_Path;}

    unsigned short GetPort(){return m_Port;}

    // other functions are not supported yet

private:

    void ParseURL(std::string& url);
    
    Protocol        m_Protocol;
    std::string     m_Host;
    unsigned short  m_Port;
    std::string     m_Path;
    std::string     m_Query;

    std::string m_Password;
    std::string m_User;
    std::string m_URL;
};

#endif


