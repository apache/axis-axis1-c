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
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/05/21 samisa
 * Applied patch for HTTP 1.1 chunking 
 * submitted by Adrian Dick (adrian.dick@uk.ibm.com) and John Hawkins" (HAWKINSJ@uk.ibm.com)
 */


#include "Platform.hpp"
#include "HttpTransport.hpp"
#include <iostream>
#include <stdio.h>
#include <axis/server/AxisException.h>
#include <axis/server/GDefine.h>

using namespace std;

/*
 *    Create HTTP transport with provided URL as remote address,
 *  set HTTP category default to POST
 */
HttpTransport::HttpTransport (Url url, int secure):
m_Typ (POST)
{
    m_Url = url;
    m_IsHttpHeader = 0;
    m_HttpBindDone = false;
    m_Secure = secure;

    if (SECURE == secure)
    {
#ifdef _SSL_ENABLED_
	m_Channel = new SecureChannel ();
#endif
    }
    else
    {
	m_Channel = new Channel ();
    }
}

/*
 *    Create HTTP transport with provided remote address as URL-string,
 *  set HTTP category default to POST
 */
HttpTransport::HttpTransport (std::string & strUrl, int secure):
m_Typ (POST)
{
    m_Url = Url (strUrl);
    m_strUrl = strUrl;
    m_IsHttpHeader = 0;
    m_HttpBindDone = false;

    if (secure)
    {
#ifdef _SSL_ENABLED_
	m_Channel = new SecureChannel ();
#endif
    }
    else
    {
	m_Channel = new Channel ();
    }
}

/*
 *    Shutdown any established channel
 */

HttpTransport::~HttpTransport ()
{
    m_Channel->Close ();
    delete m_Channel;
}

/*
 * Initialize HTTP transport by establishing a channel to the remote end.
 *
 * @return  Status of the channel establishment to the remote end provided 
 *          by m_Url
 * @trows   Channel Exception
 */

bool HttpTransport::Init ()
{
    /* open a channel for transport */
    m_HttpBindDone = false;
    try
    {
	m_bStatus = true;
	std::string host = m_Url.GetHostName ();
	m_Channel->Open (host, m_Url.GetPort ());
	m_Channel->SetTransportHandler (this);
#ifdef _DEBUG
	cout << "Transport:init() successfull" << endl;
#endif
    }
    catch (ChannelException & chEx)
    {
	std::cerr << chEx.GetErr () << std::endl;
	throw;
    }
    return true;
}

void
HttpTransport::Fini ()
{
    m_Channel->Close ();
}

/*
 *    Set properties of HTTP transport such as additional Header fields like 
 *    SOAPAction.
 *
 *    @param    p_Property    Property name;  such as SOAPAction
 *    @param    p_Value        Property value
 */

void
HttpTransport::SetProperty (const char *p_Property, const char *p_Value)
{
    m_AdditionalHeader.push_back (std::make_pair (p_Property, p_Value));
}


/*
 *    Read from a HTTP transport handler and store payload.
 *
 *    @param    p_Payload    SOAP Envelop as Payload for HTTP transport
 *
 */

const Transport &
HttpTransport::operator >> (const char **pPayLoad)
{
    std::string tmpPacket;	/* use temporary, need to workout for this */
    if (!m_bStatus)
    {
	/* We have the payload; this is due to Fault request made in */
	/* earlier call to this method */
	*pPayLoad = m_PayLoad.c_str ();

	return *this;
    }

    /* Http header is processed and validated. We now receive the payload */
    /* from the channel */
    if (m_IsHttpHeader == 1)
    {
	*m_Channel >> m_PayLoad;
	*pPayLoad = m_PayLoad.c_str ();
	return *this;
    }



    do
    {				/* process will step into this only if http validation is not done. 
				 * That is, until the stream contain the httpd header.
				 */
	*m_Channel >> tmpPacket;

	// When HTTP has chunked the data into packets, continue to read data
	// from the channel until it is empty to ensure that all of the chunks
	// associated with the message have been read.

	// Create a local string that will receive the latest http chunk.

	std::string tmpCompletePacket;

	// Loop, reading the latest http data and then adding that data chunk to
	// the tmpPacket string until the length of the latest http data chunk is
	// zero, indicating that there is no more data to be read that is associated
	// with this message.
	/* TODO */

	// There are other places m_channel is used and needs to have same loop.
	do
	{
	    //*m_Channel >> tmpCompletePacket;
	    //have read from channel once
	    //hence read the rest in non bloking mode
	    m_Channel->readNonBlocking (tmpCompletePacket);

	    tmpPacket.append (tmpCompletePacket);

	}
	while (tmpCompletePacket.length ());

#ifdef _DEBUG
	std::cout << "\n\n\nGot the message:\r\n\r\n" << tmpPacket << "\n\n";
#endif


	/* Validate the HTTP packet */
	if (m_IsHttpHeader == 1)
	    /* if header is validated but payload has zero length, process will 
	     * step into this. 
	     */
	{
	    /* printf("while,m_IsHttpHeader == 1\n"); */
	    *pPayLoad = tmpPacket.c_str ();

	    break;
	}
	if (m_bStatus)
	    HTTPValidate (tmpPacket);	/* Validate the header */
	int j = strlen (tmpPacket.c_str ());
	if (j == 0)
	    break;
	*pPayLoad = m_PayLoad.c_str ();
	int i = strlen (m_PayLoad.c_str ());
	/* If payload has nonzero length */
	if (i > 0)
	{
	    break;
	}
    }
    while (true);

    return *this;
}



/*
 * Write a given payload to the established channel by using HTTP transport
 * as carrier.
 */

const Transport &
HttpTransport::operator << (const char *p_Payload)
{
    HTTPBind ();		/* Bind the SOAP-Envelop with HTTP headers */
    /* Write to the established channel */
    *m_Channel << p_Payload;
    /* *m_Channel << m_OutMsg.str(); */
    return *this;
}


/*
 *  Build a HTTP packet with a given payload & additional HTTP properties
 *  Uses HTTP 1.1; if HTTP 1.0 is required we have to manage with setting 
 *  the properties. Only POST is supported for the time being; hope to
 *  support M-POST
 *
 */

void
HttpTransport::HTTPBind ()
{
    if (m_HttpBindDone)
	return;
    m_OutHttpHeaders = "";
    if (m_Typ == POST)		/* only POST is supported for now, wish-list: M-POST?? */
	m_OutHttpHeaders = "POST ";
#ifdef HTTP_1_0
    /* As some servers require HTTP 1.0 we temporary define the
     * directive. 
     * TODO: can be a WSDL2Ws argument
     */
    m_OutHttpHeaders += m_Url.GetResource () + " HTTP/1.0\r\n";
    /* no support for proxy server yet */
#else
    /* Use HTTP 1.1; if HTTP 1.0 is required we have to manage with setting 
     * the properties 
     */
    m_OutHttpHeaders += m_Url.GetResource () + " HTTP/1.1\r\n";
    /* no support for proxy server yet */
#endif
    m_OutHttpHeaders += "Host: " + m_Url.GetHostName ();

    unsigned short port = m_Url.GetPort ();

    if (!m_Secure && port != HTTP_PORT)
    {
	char buff[8];
	sprintf (buff, "%u", port);
	m_OutHttpHeaders += ":";
	m_OutHttpHeaders += buff;
    }
    else if (m_Secure && port != HTTPS_PORT)
    {
	char buff[8];
	sprintf (buff, "%u", port);
	m_OutHttpHeaders += ":";
	m_OutHttpHeaders += buff;
    }

    m_OutHttpHeaders += "\r\n";
    /*
     * Special notice: as express in the RFC1700, it seems that charset token
     *  shouldn't be enclosed by quotes. It is confirmed by RFC 2616 :
     *   See http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.4.
     * As some server can't deal with quotes "UTF-8" we explicitly remove then
     */
    m_OutHttpHeaders += "Content-Type: text/xml; charset=UTF-8\r\n";
    /* We have to support other charsets */

    /* Set header values for additional prefixes, such as SOAPAction */
    for (int i = 0; i < m_AdditionalHeader.size (); i++)
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
    *m_Channel << m_OutHttpHeaders.c_str ();
    m_HttpBindDone = true;
}


/*
 *    Obtain the status of the HTTP packet validity.
 *
 *    @param    p_HttpPacket    HTTP packet
 *
 *    @return                    Status of the HTTP packet validity.
 */

bool HttpTransport::GetStatus (const std::string & p_HttpPacket)
{
    HTTPValidate (p_HttpPacket);
    return m_bStatus;
}

 /*
  * This converts an ascii hex string to int converter.
  */
int
axtoi (char *hexStg)
{
    int
	n = 0;			// position in string
    int
	m = 0;			// position in digit[] to shift
    int
	count;			// loop index
    int
	intValue = 0;		// integer value of hex string
    int
	digit[32];		// hold values to convert
    while (n < 32)
    {
	if (hexStg[n] == '\0')
	    break;
	if (hexStg[n] > 0x29 && hexStg[n] < 0x40)	//if 0 to 9
	    digit[n] = hexStg[n] & 0x0f;	//convert to int
	else if (hexStg[n] >= 'a' && hexStg[n] <= 'f')	//if a to f
	    digit[n] = (hexStg[n] & 0x0f) + 9;	//convert to int
	else if (hexStg[n] >= 'A' && hexStg[n] <= 'F')	//if A to F
	    digit[n] = (hexStg[n] & 0x0f) + 9;	//convert to int
	else
	    break;
	n++;
    }
    count = n;
    m = n - 1;
    n = 0;
    while (n < count)
    {
	// digit[n] is value of hex digit at position n
	// (m << 2) is the number of positions to shift
	// OR the bits into return value
	intValue = intValue | (digit[n] << (m << 2));
	m--;			// adjust the position to set
	n++;			// next digit to process
    }
    return (intValue);
}


 /*
  * When we have a chunked payload we need to handle it differently.
  * This method takes in the payload that has no http header.
  * It returns the complete unchunked payload. It throws away any chunk extension information and chunk footer.  537:         * It also throws away any http body that comes after the SOAP - Any of these three things may be an issue.
  *
  * Chunked data looks like ->
  *      Chunked-Body   = *chunk
  *                       "0" CRLF
  *                       footer
  *                       CRLF
  *
  *      chunk          = chunk-size [ chunk-ext ] CRLF
  *                         chunk-data CRLF
  *
  *      hex-no-zero    = <HEX excluding "0">
  *
  *      chunk-size     = hex-no-zero *HEX
  *      chunk-ext      = *( ";" chunk-ext-name [ "=" chunk-ext-value ] )
  *      chunk-ext-name = token
  *      chunk-ext-val  = token | quoted-string
  *      chunk-data     = chunk-size(OCTET)
  *
  *      footer         = *entity-header
  *
  *
  * The algorithm used comes from the HTTP 1.1 RFC - 2068
  *        length := 0
  *        read chunk-size, chunk-ext (if any) and CRLF
  *         while (chunk-size > 0) {
  *            read chunk-data and CRLF
  *            append chunk-data to entity-body
  *            length := length + chunk-size
  *            read chunk-size and CRLF
  *         }
  *         read entity-header
  *         while (entity-header not empty) {
  *            append entity-header to existing header fields
  *            read entity-header
  *         }
  *         Content-Length := length
  *         Remove "chunked" from Transfer-Encoding
  *
  */
std::string GetChunkedPayLoad (Channel * channel, const std::string & payload)
{
#ifdef _DEBUG
    printf
	("> std::string GetChunkedPayLoad(Channel* channel, const std::string& payload)\r\n");
#endif
    string completePayload;

    string unParsedChunks = payload;	// the data that is still to be parsed.

    bool gotChunksToParse = true;
    string tmpChunk;

    // while we still have data to do
    while (gotChunksToParse)
    {
	// firstly read in the chunk size line. There might be chunk extensions in there too but get it all for now.
	// we need this later anyway;
	int endOfChunkData = unParsedChunks.find ("\r\n");
	int endOfChunkSize = endOfChunkData;

	// now get just the size of the chunk from the data
	// look to see if there are any extensions - these are put in brackets so look for those
	if (unParsedChunks.substr (0, endOfChunkData).find ("(") != string::npos)
	{
	    // there are extensions so just get the chunk dataSize
	    endOfChunkSize = unParsedChunks.find ("(");
	}

	// convert the hex String into the length of the chunk
	int chunkSize =
	    axtoi ((char *) unParsedChunks.substr (0, endOfChunkSize).
		   c_str ());
	// if the chunk size is zero then we have reached the footer
	// If we have reached the footer then we can throw it away because we don't need it
	if (chunkSize > 0)
	{
	    // now get the chunk without the CRLF
	    completePayload =
		completePayload + unParsedChunks.substr (endOfChunkData +
							 2, chunkSize);
	    // OK, now we have the chunk, we need to read in more chunks from the channel.
	    // we must have more chunks because we haven't reached the ")" which signifies the end of the
	    // now move the unparsed chunk along avoiding the 2 bytes of CRLF.
	    unParsedChunks =
		unParsedChunks.substr (endOfChunkData + 2 + chunkSize + 2);
	}
	else
	{
	    gotChunksToParse = false;
	}
    }

    return completePayload;
}

/*
 *    Validate HTTP packets received from the channel.
 *
 *    @param    p_HttpPacket    HTTP packet
 *    
 *    @return    Status code is set
 */

void
HttpTransport::HTTPValidate (const std::string & p_HttpPacket)
{
    /* for the time being just get the payload. Here we need much work */

    m_bStatus = true;
    int nHttpSatus;

    m_sHeader += p_HttpPacket;

    std::string::size_type pos, nxtpos;
    pos = p_HttpPacket.find ("\r\n\r\n");	/*Search for end of http header */
    if (pos == std::string::npos)
    {
	m_PayLoad = "";
	return;			/* unexpected string */
    }

    m_IsHttpHeader = 1;		/* We have the stream until payload */
    pos = m_sHeader.find ('\n');	/*Search for the end of line of the first string */
    std::string strLine = m_sHeader.substr (0, pos + 1);	/*extract the line into a string */
    std::string::size_type offset = pos + 1;
    /* Check for HTTP header validity; HTTP 1.0 / HTTP 1.1 is supported. */
    if ((pos = strLine.find ("HTTP/1.0")) != std::string::npos
	|| (pos = strLine.find ("HTTP/1.1")) != std::string::npos)
    {
	if (((pos =
	      strLine.find_first_of ("\" ",
				     pos + strlen ("HTTP/1.x"))) !=
	     std::string::npos)
	    && (nxtpos =
		strLine.find_first_of ("\" ", pos)) != std::string::npos)
	{
	    pos++;
	    /* Get the HTTP status code of the packet obtained */
	    nHttpSatus =
		atoi (strLine.substr (pos, nxtpos - pos).c_str ()) / 100;
	}
	else
	    return;


	/* Status code is 2xx; so valid packet. hence go ahead and extract
	 * the payload. 
	 */
	if (nHttpSatus == 2)
	{
	    GetPayLoad (m_sHeader, offset);
	}
	else if (nHttpSatus == 3)
	    /* Status code is 3xx; some error has occurred */
	{
	    /* error recovery mechanism should go here */
	    Error (m_sHeader.c_str ());
	    throw ChannelException ("HTTP Error, cannot process response \
                    message...");
	}
	else if (nHttpSatus == 4)
	    /* Status code is 4xx; some error has occurred */
	{
	    /* error recovery mechanism should go here */
	    Error (m_sHeader.c_str ());
	    throw ChannelException ("HTTP Error, cannot process response \
                    message...");
	}
	else if (nHttpSatus == 5)
	    /* Status code is 5xx; some error has occurred */
	{
	    /* error recovery mechanism should go here */
	    GetPayLoad (m_sHeader, offset);
	    if (!m_bStatus)
	    {
		Error (m_sHeader.c_str ());
		throw AxisException (SERVER_TRANSPORT_HTTP_EXCEPTION);
	    }
	}
    }
    else
	throw ChannelException ("Unknow HTTP response, cannot process \
            response message...");

}



/*
 *    Process rest of the packet to get the content length of the payload.
 *    Once the http header processing is over, extract payload from the 
 *    HTTP packet starting from a given offset
 *
 */

void
HttpTransport::GetPayLoad (const std::string & p_HttpPacket,
			   std::string::size_type & offset)
{
    bool chunked = false;	// Flag used to indicate whether the http data is chunked or not.
    std::string::size_type pos, nxtpos;
    std::string strLine;
    /* int len=0; */

    /* process rest of the HTTP packet to get the Content-Length of the payload */
    while (true)
    {
	if ((nxtpos = p_HttpPacket.find ('\n', offset)) == std::string::npos)
	    return;
	nxtpos++;
	strLine = p_HttpPacket.substr (offset, nxtpos - offset);
	offset = nxtpos;

	if ((strLine == "\r\n") || (strLine == "\n") || strLine.size () <= 1)
	    break;

	/* Get the payload size from the header. */
	if ((pos = strLine.find ("Content-Length:")) != std::string::npos)
	    m_intBodyLength = atoi (strLine.substr
				    (pos +
				     strlen ("Content-Length: ")).c_str ());
	// Check that the current HTTP header line has the words "Transfer-Encoding:
	// chunked" as this will indicate if the incoming data is chunked or not.
	if ((pos = strLine.find ("Transfer-Encoding: chunked")) !=
	    std::string::npos)
	{
	    chunked = true;
	}
    }
    m_PayLoad = p_HttpPacket.substr (offset);	/* rest from the offset is payload */

    if (chunked)
    {
	m_PayLoad = GetChunkedPayLoad (m_Channel, m_PayLoad);
    }


    // m_PayLoad = p_HttpPacket.substr(offset);


    /* pos = m_PayLoad.rfind('0');

       if(std::string::npos != pos && m_PayLoad[pos+1] != '\"')
       {
       nxtpos = m_PayLoad.find("1df");
       if(std::string::npos != nxtpos && '\n' == m_PayLoad[nxtpos+4])
       {
       m_bStatus = false; // we have the payload
       Extract the SOAP message
       m_PayLoad = m_PayLoad.substr(m_PayLoad.find('<'));
       m_PayLoad = m_PayLoad.substr(0, m_PayLoad.rfind('>') + 1);
       }
       } */

#ifdef _DEBUG
    std::cout << "Payload:\n" << m_PayLoad << std::endl;
#endif
}


/*
 *    Report error on read/write
 *
 */

void
HttpTransport::Error (const char *err)
{
#ifdef _DEBUG
    std::cerr << err << std::endl;
#endif
}

void
HttpTransport::ClearAdditionalHeaders ()
{
    m_AdditionalHeader.clear ();
}

int
HttpTransport::getBodyLength ()
{
    return m_intBodyLength;
}

void
HttpTransport::setBodyLength (int bodyLength)
{
    m_intBodyLength = bodyLength;

}

int
HttpTransport::getIsHttpHeader ()
{
    return m_IsHttpHeader;
}
