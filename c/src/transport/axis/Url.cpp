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


#include "Platform.hpp"
#include "Url.hpp"
#include <ctype.h>
#include <iostream>
using namespace std;


Url::Url()
    : m_Protocol(unknown), m_Port(0)
{
   /* cout << "inside Url constructor" << endl;  */
}

Url::Url(std::string url)
{
    m_URL = url;
    if(isascii((int)url.at(0)))
    {
        /* check this a valid URL */
        if((url.at(1) == (int)':') &&
            ((url.at(2) == (int)'/') || (url.at(2) == (int)'\\')))
            return;
        else /* assume valid URL hence, proceed with finding entries */
            ParseURL(url);
    }
}

Url::~Url()
{

}

void Url::SetProtocol(std::string prot)
{
    m_Port = 0;
    if(prot == "http")
    {
        m_Protocol = http;
        m_Port = HTTP_PORT;
    }
    else if( prot == "file")
    {
        m_Protocol = file;
    }
    else if( prot == "ftp")
    {
        m_Protocol = ftp;
        m_Port = FTP_PORT;
    }
    else if( prot == "https")
    {

        m_Protocol = https;
        m_Port = HTTPS_PORT;
    }
    else
        m_Protocol = unknown;

}

void Url::ParseURL(std::string& url)
{
    std::string::size_type begpos, pos;

    /* try to find out the protocol */
    if((pos = url.find("://")) != std::string::npos)
    {
        SetProtocol(url.substr(0, pos));
        /* find m_Host name */
        if(m_Protocol != unknown)
        {
            url = url.substr(pos + 3); /* rest of the URL string */
            begpos = pos = 0;
            std::string key(":/?");
            
            while((pos = url.find_first_of(key, begpos)))
            {
                if(pos == std::string::npos) /* only host name found */
                {
                    if(m_Host.empty())
                        m_Host = url;
                    if (key == "?") /* found path */
                        m_Path = url.substr(begpos - 1);
                    break;
                }
                else
                    if(pos == 0) break;

                switch(url.at(pos))
                {
                    case ':': 
                        if(m_Host.empty())
                            m_Host = url.substr(begpos, pos - begpos);
                        pos++;
                        begpos = pos;
                        key = "/?"; 
                        /* scan for the rest to get the path & query */
                        continue;

                    case '/':
                        if (key == "/?") /* found port number */
                        {
                            m_Port = atoi(url.substr(begpos, 
                                pos - begpos + 1).c_str());
                            if(m_Host.empty())
                                m_Host = url.substr(0, begpos - 1);
                        }
                        else
                            m_Host = url.substr(0, pos);
                        pos++;
                        begpos = pos;
                        key = "?";
                        continue;

                    case '?':
                        /* not correctly supported */
                        m_Query = url.substr(pos);
                        break;
                }    
                break;
            }                            
        }
    }
}



 
                    

                    


