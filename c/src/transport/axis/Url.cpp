/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */


#include <axis/client/transport/axis/Platform.hpp>
#include <axis/client/transport/axis/Url.hpp>
#include <ctype.h>
#include <iostream>
using namespace std;


Url::Url()
	: m_Protocol(unknown), m_Port(0)
{
   //cout << "inside Url constructor" << endl; 
}

Url::Url(std::string url)
{
	m_URL = url;
	if(isascii((int)url.at(0)))
	{
		// check this a valid URL
		if((url.at(1) == (int)':') &&
			((url.at(2) == (int)'/') || (url.at(2) == (int)'\\')))
			return;
		else // assume valid URL hence, proceed with finding entries
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

	// try to find out the protocol
	if((pos = url.find("://")) != std::string::npos)
	{
		SetProtocol(url.substr(0, pos));
		// find m_Host name
		if(m_Protocol != unknown)
		{
			url = url.substr(pos + 3); // rest of the URL string
			begpos = pos = 0;
			std::string key(":/?");
			
			while((pos = url.find_first_of(key, begpos)))
			{
				if(pos == std::string::npos) // only host name found
				{
					if(m_Host.empty())
						m_Host = url;
					if (key == "?") // found path
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
						key = "/?"; // scan for the rest to get the path & query
						continue;

					case '/':
						if (key == "/?") // found port number
						{
							m_Port = atoi(url.substr(begpos, pos - begpos + 1).c_str());
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
						// not correctly supported
						m_Query = url.substr(pos);
						break;
				}	
				break;
			}							
		}
	}
}



 
					

					


