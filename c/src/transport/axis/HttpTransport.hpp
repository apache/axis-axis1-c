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
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */


#if !defined(_AXIS_HTTPTRANSPORT_HPP)
#define _AXIS_HTTPTRANSPORT_HPP

#include <sstream>
#include <string>
#include <vector>
#include "Transport.hpp"
#include "Channel.hpp"
#ifdef _SSL_ENABLED_
    #include "SecureChannel.hpp"
#endif

/**
 * 
 * Implements HTTP transport as SOAP-Envelop carrier, for sending/receiving
 * SOAP messages with HTTP 1.1/1.0; This implementation abstract the Transport layer for the
 * SOAP payloads
 *	
 * @brief     The HTTP transport implementation for SOAP 
 *
 */



class HttpTransport  : public Transport
{
public:
	/// HTTP category, Only POST is used currently, MPOST is not supported yet
	enum Type{POST, MPOST};

	/// Create HTTP transport with provided URL as remote address, set HTTP category default to POST
	//HttpTransport(Url url) : m_Typ(POST) {m_Url = url; m_IsHttpHeader = 0; m_HttpBindDone = false;}

	/// Create HTTP transport with provided remote address as URL-string, set HTTP category default to POST
	//HttpTransport(std::string& strUrl) : m_Typ(POST) {m_Url = Url(strUrl); m_IsHttpHeader = 0;m_strUrl = strUrl; m_HttpBindDone = false;}
	~HttpTransport();

    HttpTransport(std::string& strUrl, bool secure);
    
    HttpTransport(Url url, bool secure);

	/// Initialize HTTP transport by establishing a channel to the remote end.
	bool  Init();

	/* Finish using this transport and close channel */
	void Fini();

	/// Obtain the status of the HTTP packet validity
	bool  GetStatus(const std::string& p_HttpPacket);

	/// Set properties of HTTP transport such as additional Header fields like SOAPAction.
	void  SetProperty(const char* p_Property, const char* p_Value);

	/// Read from a HTTP transport handler and store read payload
	const Transport& operator >> (const char** pPayload);

	/// Write a given payload by using HTTP transport as carrier
	const Transport& operator << (const char* p_Payload);
    int getBodyLength();
    void setBodyLength(int bodyLength);
    int getIsHttpHeader();

private:
	/// Build a HTTP packet with a given payload & additional HTTP properties
	void HTTPBind();

	/// Validate HTTP packets received from the channel.
	void HTTPValidate(const std::string& p_HttpPacket);

	/// Extract payload from the HTTP packet starting from a given offset
	void GetPayLoad(const std::string& p_HttpPacket, std::string::size_type& offset);

	/// Report error on read/write
	void Error(const char * err);

    void ClearAdditionalHeaders();

private:

	typedef std::vector< std::pair<std::string, std::string> > Header_t;

	Type m_Typ;						///< Type of the HTTP; POST or MPOST

	std::string m_OutHttpHeaders;	///< Holds	outgoing HTTP packet
	std::istringstream m_InMsg;		///< Holds	incoming HTTP packet

	std::string m_PayLoad;			///< Holds the payload
	Header_t	m_AdditionalHeader; ///< Additional Header fields as name value pairs
private:
	Channel* m_Channel;
	bool m_HttpBindDone;
    int m_IsHttpHeader;
    std::string m_sHeader;
    int m_intBodyLength;
    bool m_Secure;
};

#endif //_AXIS_HTTPTRANSPORT_HPP

