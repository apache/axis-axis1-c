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
 * 4. The names "SOAP" and "Apache Software Foundation" must
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


#if !defined(_AXIS_URL_HPP)
#define _AXIS_URL_HPP

#include <string>

// Welknown ports
const unsigned short HTTP_PORT  = 80;	
const unsigned short HTTPS_PORT = 443;
const unsigned short FTP_PORT   = 21;


/**
 *	Implementation of URL to manupulate URLs.  
 *
 *	This implementation only supports subset of a URL
 *	note that # references, userinfo query string 
 *	processing are not supported for this version.
 *
 *	URLs are of the form:
 * 
 *	URL			  = protocol "://" server "/" [path]["?" query]
 *	server        = [userinfo "@"] hostname-port
 *	hostname-port = hostname [ ":" port ]
 *	userinfo	  = user[:password]
 *
 *
 *	@brief	Manupulate URLs
 */


class Url  
{
public:

	enum Protocol { http, https, ftp, file, unknown}; // for our purpose currently we need
													  // http, https only. This is provided
													  // To make extensible to
													  // support other transports for RPC
													  // but file????, yes we may require 
													  // pipes; with web-service????

public:
	Url();
	Url(std::string url);
	~Url();

	void SetProtocol(std::string prot);
	void SetProtocol(Protocol prot){m_Protocol = prot;}
	void SetHostName(std::string host){m_Host= host;}
	void SetResource(std::string path){m_Path = path;}
	void SetPort(unsigned short port){m_Port = port;}

	Protocol	GetProtocol(){return m_Protocol;}
	std::string GetHostName(){return m_Host;}
	std::string GetResource(){return m_Path;}

	unsigned short GetPort(){return m_Port;}

	// other functions are not supported yet

private:

	void ParseURL(std::string& url);
	
	Protocol		m_Protocol;
	std::string		m_Host;
	unsigned short  m_Port;
	std::string		m_Path;
	std::string		m_Query;

    std::string m_Password;
    std::string m_User;
    std::string m_URL;
};

#endif // _AXIS_URL_HPP


