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
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */


#include <axis/client/transport/axis/Platform.hpp>
#include <axis/client/transport/axis/HttpTransport.hpp>
#include <iostream>
#include <axis/common/AxisException.h>

using namespace std;

/**
 *	Create HTTP transport with provided URL as remote address,
 *  set HTTP category default to POST
 */
HttpTransport::HttpTransport(Url url, bool secure) : m_Typ(POST)
{
    m_Url = url;
    m_IsHttpHeader = 0;
    m_HttpBindDone = false;
    m_Secure = secure;

    if(secure) {
        m_Channel = new SecureChannel();
    } else {
        m_Channel = new Channel();
    }
}

/**
 *	Create HTTP transport with provided remote address as URL-string,
 *  set HTTP category default to POST
 */
HttpTransport::HttpTransport(std::string& strUrl, bool secure) : m_Typ(POST)
{
    m_Url = Url(strUrl);
    m_strUrl = strUrl;
    m_IsHttpHeader = 0;
    m_HttpBindDone = false;

    if(secure) {
        m_Channel = new SecureChannel();
    } else {
        m_Channel = new Channel();
    }
}

/**
 *	Shutdown any established channel
 */

HttpTransport::~HttpTransport()
{
	m_Channel->Close();
    delete m_Channel;
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
	m_HttpBindDone = false;
	try
	{
		m_bStatus = true;
		std::string host = m_Url.GetHostName();
		m_Channel->Open(host, m_Url.GetPort());
		m_Channel->SetTransportHandler(this);
#ifdef _DEBUG
        cout << "Transport:init() successfull" << endl;
#endif
	}
	catch(ChannelException& chEx)
	{
		std::cerr << chEx.GetErr() << std::endl;
		throw;
	}
	return true;
}

void HttpTransport::Fini()
{
	m_Channel->Close();
}

/**
 *	Set properties of HTTP transport such as additional Header fields like SOAPAction.
 *
 *	@param	p_Property	Property name;  such as SOAPAction
 *	@param	p_Value		Property value
 */

void  HttpTransport::SetProperty(const char* p_Property, const char* p_Value)
{
	m_AdditionalHeader.push_back(std::make_pair(p_Property, p_Value));
}


/**
 *	Read from a HTTP transport handler and store read payload.
 *
 *	@param	p_Payload	SOAP Envelop as Payload for HTTP transport
 *
 */

const Transport& HttpTransport::operator >> (const char** pPayLoad)
{
        if(!m_bStatus)
        {
                // We have the payload; this is due to Fault request made in earlier call
                // to this method
                *pPayLoad = m_PayLoad.c_str();

                return *this;
        }

        std::string tmpPacket;  // use temporary, need to workout for this
  if(m_IsHttpHeader == 1)
  {
      //printf("m_IsHttpHeader == 1\n");
      *m_Channel >> m_PayLoad;
      *pPayLoad = m_PayLoad.c_str();
      return *this;
  }
  //printf("tmpPacket:%s\n", tmpPacket.c_str());  
	//*m_Channel >> tmpPacket;

//#ifdef _DEBUG
        //std::cout << "\n\n\nGot the message:\r\n\r\n" << tmpPacket << "\n\n";
//#endif
    do //process will step into this only if http validation is not done. That is, until the stream
      //contain the httpd header.
    {
        *m_Channel >> tmpPacket;

        // Validate the HTTP packet
        if(m_IsHttpHeader == 1) //if header is validated but payload has zero length, process will steop into this.
        {
            //printf("while,m_IsHttpHeader == 1\n");
            *pPayLoad = tmpPacket.c_str();

            break;
        }
        //printf("do while\n");
        if(m_bStatus) HTTPValidate(tmpPacket); //Validate the header
        int j = strlen(tmpPacket.c_str());
        if(j == 0)
            break;
        *pPayLoad = m_PayLoad.c_str();
        int i = strlen(m_PayLoad.c_str());
        //printf("i:%d\n", i);
        //If payload has nonzero length
        if(i > 0)
        {
            //printf("if i> 0\n");
            break;
        }
  } while(true);


        return *this;
}



/**
 *	Write a given payload to the established channel by using HTTP transport as carrier.
 *
 */

const Transport& HttpTransport::operator << (const char* p_Payload)
{
	HTTPBind();	// Bind the SOAP-Envelop with HTTP headers
	// Write to the established channel
	*m_Channel << p_Payload;
    //*m_Channel << m_OutMsg.str();
	return *this;
}


/**
 *	Build a HTTP packet with a given payload & additional HTTP properties
 *  Uses HTTP 1.1; if HTTP 1.0 is required we have to manage with setting 
 *	the properties. Only POST is supported for the time being; hope to
 *	support M-POST
 *
 */

void HttpTransport::HTTPBind()
{
	if (m_HttpBindDone) return;
	m_OutHttpHeaders = "";
	if(m_Typ == POST)				// only POST is supported for now, wish-list: M-POST??
		m_OutHttpHeaders = "POST ";

	// Use HTTP 1.1; if HTTP 1.0 is required we have to manage with setting the properties
	m_OutHttpHeaders += m_Url.GetResource() + " HTTP/1.1\r\n"; // no support for proxy server yet
	m_OutHttpHeaders += "Host: " + m_Url.GetHostName();

	unsigned short port = m_Url.GetPort();

	if(!m_Secure && port != HTTP_PORT)
	{
		char buff[8];
		sprintf(buff, "%u", port);
		m_OutHttpHeaders += ":";
		m_OutHttpHeaders += buff;
	}
    else if(m_Secure && port != HTTPS_PORT)
    {
		char buff[8];
		sprintf(buff, "%u", port);
		m_OutHttpHeaders += ":";
		m_OutHttpHeaders += buff;
	}

	m_OutHttpHeaders += "\r\n";
	m_OutHttpHeaders += "Content-Type: text/xml; charset=\"UTF-8\"\r\n";	// We have to support other charsets
	
	//Set header values for additional prefixes, such as SOAPAction
	for(int i=0; i < m_AdditionalHeader.size(); i++)
	{
		if (m_AdditionalHeader[i].first == "Content-Length")
		{
			m_OutHttpHeaders += m_AdditionalHeader[i].first;
			m_OutHttpHeaders += ": "; 
			m_OutHttpHeaders += m_AdditionalHeader[i].second;
			m_OutHttpHeaders += "\r\n";
		}
		else
		{
			m_OutHttpHeaders += m_AdditionalHeader[i].first;
			m_OutHttpHeaders += ": \""; 
			m_OutHttpHeaders += m_AdditionalHeader[i].second;
			m_OutHttpHeaders += "\"\r\n";
		}
	}

	m_OutHttpHeaders += "\r\n";
	*m_Channel << m_OutHttpHeaders.c_str();
	m_HttpBindDone = true;
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
  int nHttpSatus;

  m_sHeader +=  p_HttpPacket;

  //printf("m_sHeader:%s\n", m_sHeader.c_str());
  std::string::size_type pos, nxtpos;
        pos = p_HttpPacket.find("\r\n\r\n");
        if(pos == std::string::npos)
  {
    m_PayLoad = "";
    return; //unexpected string
  }

  m_IsHttpHeader = 1; //We have the stream until payload
  pos = m_sHeader.find('\n');
        std::string strLine = m_sHeader.substr(0, pos + 1);
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
            //printf("nHttpSatus is 2\n");
                        GetPayLoad(m_sHeader, offset);
                }
                else if(nHttpSatus == 3)        // Status code is 3xx; some error has occurred
                {
                        // error recovery mechanism should go here
                        Error(m_sHeader.c_str());
                        throw ChannelException("HTTP Error, cannot process response message...");                }
                else if(nHttpSatus == 4)        // Status code is 4xx; some error has occurred
                {
                        // error recovery mechanism should go here
                        Error(m_sHeader.c_str());
                        throw ChannelException("HTTP Error, cannot process response message...");                }
                else if(nHttpSatus == 5)        // Status code is 5xx; some error has occurred
                {
                        // error recovery mechanism should go here
                        GetPayLoad(m_sHeader, offset);
                        if (!m_bStatus)
                        {
                                Error(m_sHeader.c_str());
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
        //int len=0;

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
                        m_intBodyLength = atoi(strLine.substr(pos + strlen("Content-Length: ")).c_str());
      //printf("m_intBodyLength:%d\n", m_intBodyLength);
        }

        m_PayLoad = p_HttpPacket.substr(offset);
    //printf("m_PayLoad:%s\n", m_PayLoad.c_str());


        //pos = m_PayLoad.rfind('0');

        //if(std::string::npos != pos && m_PayLoad[pos+1] != '\"')
        //{
                //nxtpos = m_PayLoad.find("1df");
                //if(std::string::npos != nxtpos && '\n' == m_PayLoad[nxtpos+4])
                //{
                        //m_bStatus = false; // we have the payload
                        // Extract the SOAP message
                        //m_PayLoad = m_PayLoad.substr(m_PayLoad.find('<'));
                        //m_PayLoad = m_PayLoad.substr(0, m_PayLoad.rfind('>') + 1);
                //}
        //}

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

int HttpTransport::getBodyLength()
{
  return m_intBodyLength;
}

void HttpTransport::setBodyLength(int bodyLength)
{
  m_intBodyLength = bodyLength;

}

int HttpTransport::getIsHttpHeader()
{
  return m_IsHttpHeader;
}
