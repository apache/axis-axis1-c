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


#include "Platform.hpp"
#include "HttpTransport.hpp"
#include <iostream>
#include "../../../common/AxisException.h"

using namespace std;

/**
 *	Shutdown any established channel
 */

HttpTransport::~HttpTransport()
{
	m_Channel.Close();
}

/**
 *	Initialize HTTP transport by establishing a channel to the remote end.
 *
 *	@return		Status of the channel establishment to the remote end provided by m_Url
 *  @trows		Channel Exception
 */

bool HttpTransport::Init()
{
	// open a channel for transport
	try
	{
		m_bStatus = true;
		std::string host = m_Url.GetHostName();
		m_Channel.Open(host, m_Url.GetPort());
		m_Channel.SetTransportHandler(this);
        cout << "Transport:init() successfull" << endl;
	}
	catch(ChannelException& chEx)
	{
		std::cerr << chEx.GetErr() << std::endl;
		throw;
	}
	return true;
}


/**
 *	Set properties of HTTP transport such as additional Header fields like SOAPAction.
 *
 *	@param	p_Property	Property name;  such as SOAPAction
 *	@param	p_Value		Property value
 */

void  HttpTransport::SetProperty(const std::string& p_Property, const std::string& p_Value)
{
	m_AdditionalHeader.push_back(std::make_pair(p_Property, p_Value));
}


/**
 *	Read from a HTTP transport handler and store read payload.
 *
 *	@param	p_Payload	SOAP Envelop as Payload for HTTP transport
 *
 */

const Transport& HttpTransport::operator >> (std::string& p_Payload)
{
	if(!m_bStatus) 
	{
		// We have the payload; this is due to Fault request made in earlier call 
		// to this method
		p_Payload = m_PayLoad;
		return *this;
	}

	std::string tmpPacket;	// use temporary, need to workout for this
	m_Channel >> tmpPacket;
    
#ifdef _DEBUG
	std::cout << "\n\n\nGot the message:\r\n\r\n" << tmpPacket << "\n\n";
#endif
	
	// Validate the HTTP packet
	if(!m_bStatus) HTTPValidate(tmpPacket);

	// At this point we have the payload at hand so give it out
	p_Payload = m_PayLoad;
	return *this;
}


/**
 *	Write a given payload to the established channel by using HTTP transport as carrier.
 *
 */

const Transport& HttpTransport::operator << (const std::string& p_Payload)
{
	HTTPBind(p_Payload);	// Bind the SOAP-Envelop with HTTP headers

#ifdef _DEBUG
	std::cout << "\n\n\n";
	std::cout << m_OutMsg.str() << std::endl;
#endif

	// Write to the established channel
	m_Channel << m_OutMsg.str();
	return *this;
}


/**
 *	Build a HTTP packet with a given payload & additional HTTP properties
 *  Uses HTTP 1.1; if HTTP 1.0 is required we have to manage with setting 
 *	the properties. Only POST is supported for the time being; hope to
 *	support M-POST
 *
 */

void HttpTransport::HTTPBind(const std::string& p_Payload)
{
    m_OutMsg.flush();
	if(m_Typ == POST)				// only POST is supported for now, wish-list: M-POST??
		m_OutMsg << "POST ";

	// Use HTTP 1.1; if HTTP 1.0 is required we have to manage with setting the properties
	m_OutMsg << m_Url.GetResource() << " HTTP/1.1\r\n"; // no support for proxy server yet
	m_OutMsg << "Host: " << m_Url.GetHostName();

	unsigned short port = m_Url.GetPort();

	if(port != HTTP_PORT)
		m_OutMsg << ":" << port;

	m_OutMsg << "\r\n";
	m_OutMsg << "Content-Type: text/xml; charset=\"UTF-8\"\r\n";	// We have to support other charsets
	m_OutMsg << "Content-Length: " << p_Payload.size() << "\r\n";
	
	//Set header values for additional prefixes, such as SOAPAction
	for(int i=0; i < m_AdditionalHeader.size(); i++)
		m_OutMsg << m_AdditionalHeader[i].first << ": \"" 
		         << m_AdditionalHeader[i].second << "\"\r\n";

	m_OutMsg << "\r\n";
	m_OutMsg << p_Payload;
}


/**
 *	Obtain the status of the HTTP packet validity.
 *
 *	@param	p_HttpPacket	HTTP packet
 *
 *	@return					Status of the HTTP packet validity.
 */

bool HttpTransport::GetStatus(const std::string& p_HttpPacket)
{
	HTTPValidate(p_HttpPacket);
	return m_bStatus;
}


/**
 *	Validate HTTP packets received from the channel.
 *
 *	@param	p_HttpPacket	HTTP packet
 *	
 *	@return					Status code is set
 */

void HttpTransport::HTTPValidate(const std::string& p_HttpPacket)
{
	// for the time being just get the payload. Here we need much work

	m_bStatus = true;
	std::string::size_type pos = p_HttpPacket.find('\n'), nxtpos;

	int nHttpSatus;

	if(pos == std::string::npos) return; //unexpected string

	std::string strLine = p_HttpPacket.substr(0, pos + 1);
	std::string::size_type offset = pos + 1;

	// Check for HTTP header validity; HTTP 1.0 / HTTP 1.0 is supported.
	if((pos = strLine.find("HTTP/1.0")) != std::string::npos
		|| (pos = strLine.find("HTTP/1.1")) != std::string::npos)
	{
		if(((pos = strLine.find_first_of("\" ", pos + strlen("HTTP/1.x"))) 
			!= std::string::npos) &&
			(nxtpos = strLine.find_first_of("\" ", pos)) != std::string::npos)
		{
			pos++;
			// Get the HTTP status code of the packet obtained
			nHttpSatus = atoi(strLine.substr(pos, nxtpos - pos).c_str())/100;
		}
		else
			return;


		// Status code is 2xx; so valid packet. hence go ahead and extract the payload.
		if(nHttpSatus == 2)
		{
			GetPayLoad(p_HttpPacket, offset);
		}
		else if(nHttpSatus == 3)	// Status code is 3xx; some error has occurred
		{
			// error recovery mechanism should go here
			Error(p_HttpPacket.c_str());
			throw ChannelException("HTTP Error, cannot process response message...");
		}
		else if(nHttpSatus == 4)	// Status code is 4xx; some error has occurred
		{
			// error recovery mechanism should go here
			Error(p_HttpPacket.c_str());
			throw ChannelException("HTTP Error, cannot process response message...");
		}
		else if(nHttpSatus == 5)	// Status code is 5xx; some error has occurred
		{
			// error recovery mechanism should go here
			GetPayLoad(p_HttpPacket, offset);
			if (!m_bStatus) 
			{
				Error(p_HttpPacket.c_str());
				throw AxisException(HTTP_ERROR);
			}
		}
	}
	else
		throw ChannelException("Unknow HTTP response, cannot process response message...");

}


/**
 *	Extract payload from the HTTP packet starting from a given offset
 *
 */

void HttpTransport::GetPayLoad(const std::string& p_HttpPacket, std::string::size_type& offset)
{
	std::string::size_type pos, nxtpos;
	std::string strLine;
	int len=0;

	// process rest of the HTTP packet
	while (true)
	{
		if((nxtpos = p_HttpPacket.find('\n', offset)) == std::string::npos) return;
		nxtpos++;
		strLine = p_HttpPacket.substr(offset, nxtpos - offset);
		offset = nxtpos;

		if((strLine == "\r\n") || (strLine == "\n") || strLine.size() <= 1)
			break;

		// Get the payload size from the header.
		if((pos = strLine.find("Content-Length:")) != std::string::npos) 
			len = atoi(strLine.substr(pos + strlen("Content-Length: ")).c_str());
	}

	m_PayLoad = p_HttpPacket.substr(offset);

	pos = m_PayLoad.rfind('0');

	if(std::string::npos != pos && m_PayLoad[pos+1] != '\"')
	{
		//nxtpos = m_PayLoad.find("1df");
		//if(std::string::npos != nxtpos && '\n' == m_PayLoad[nxtpos+4])
		{
			m_bStatus = false; // we have the payload
			// Extract the SOAP message
			m_PayLoad = m_PayLoad.substr(m_PayLoad.find('<'));
			m_PayLoad = m_PayLoad.substr(0, m_PayLoad.rfind('>') + 1);
		}
	}

#ifdef _DEBUG
	std::cout << "Payload:\n" << m_PayLoad << std::endl;
#endif

}


/**
 *	Report error on read/write
 *
 */

void HttpTransport::Error(const char * err)
{
#ifdef _DEBUG
	std::cerr << err << std::endl;
#endif
}

void HttpTransport::ClearAdditionalHeaders()
{
    m_AdditionalHeader.clear();
}