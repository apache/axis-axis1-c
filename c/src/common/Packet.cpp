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
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

#include <axis/common/Packet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern "C"
{

/**
 * This method is used to add a transport specific property to a stream object for Axis supported protocols
 * such as http. For an example "Content-Length" for http. For other protocols there should be a way to
 * set these properties and its upto the transport module implementation to have those required methods. 
 */ 
int set_property(Ax_soapstream* stream, char * pchkey, char * pchvalue)
{
	int count;
	Ax_header *temp;
	switch (stream->trtype)
	{
	case APTHTTP:
		count = stream->so.http->op_headercount;
		temp = stream->so.http->op_headers;
		if(stream->so.http->op_headers)
			stream->so.http->op_headers = (Ax_header*)realloc(temp, 
											(sizeof(Ax_header)*(count+1)));
		else
			stream->so.http->op_headers = (Ax_header*)malloc((sizeof(Ax_header)*(count+1)));        
		stream->so.http->op_headers[count].headername = pchkey;
		stream->so.http->op_headers[count].headervalue = pchvalue;
		stream->so.http->op_headercount = count+1;
		return 0;
	case APTSMTP:
		return -1;
	default:
		return -1;
	}
}

/**
 * This method is used to remove all transport specific properties from a stream object for Axis supported protocols
 * such as http. For an example "SOAPAction" for http. 
 */ 
void remove_all_properties(Ax_soapstream* stream)
{
	switch (stream->trtype)
	{
	case APTHTTP:
		if (stream->so.http->ip_headercount > 0)
		{
			stream->so.http->ip_headercount = 0;
			free(stream->so.http->ip_headers);
			stream->so.http->ip_headers = NULL;
		}
		if (stream->so.http->op_headercount > 0)
		{
			stream->so.http->op_headercount = 0;
			free(stream->so.http->op_headers);
			stream->so.http->op_headers = NULL;
		}
		break;
	case APTSMTP:
		break;
	default:
		break;
	}
}

const char* get_property(const Ax_soapstream* stream,const char* pchkey)
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

	if(count==0 || hdrs==NULL)
	{
		return NULL;
	}

	for (int ix=0; ix<count; ix++)
	{
		if (strcmp((hdrs+ix)->headername, pchkey) == 0)
		{
			return (hdrs+ix)->headervalue;
		}

	}
	return NULL;
}

}