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


int set_header(Ax_soapstream* soap, char * pchkey, char * pchvalue)
{
	int count = soap->so.http.ip_headercount;
	Ax_header * temp = soap->so.http.ip_headers;
	soap->so.http.ip_headers = (Ax_header*)realloc(temp, 
										(sizeof(Ax_header)*(count+1)));
	soap->so.http.ip_headers[count].headername = pchkey;
	soap->so.http.ip_headers[count].headervalue = pchvalue;
	soap->so.http.ip_headercount = count+1;

	return 0;
}

void remove_headers(Ax_soapstream* soap)
{
	if (soap->so.http.ip_headercount > 0)
	{
		soap->so.http.ip_headercount = 0;
		free(soap->so.http.ip_headers);
		soap->so.http.ip_headers = NULL;
	}
	if (soap->so.http.op_headercount > 0)
	{
		soap->so.http.op_headercount = 0;
		free(soap->so.http.op_headers);
		soap->so.http.op_headers = NULL;
	}
}

const char* get_header(const Ax_soapstream* soap,const char* pchkey)
{
	const Ax_header* hdrs = NULL;
	int count = 0;
	switch (soap->trtype)
	{
	case APTHTTP:
		hdrs = soap->so.http.ip_headers;
		count = soap->so.http.ip_headercount;
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
		//header* hdr = hdrs + ix;
		if (strcmp((hdrs+ix)->headername, pchkey) == 0)
		{
			return (hdrs+ix)->headervalue;
		}

	}
	return NULL;
}

const char* get_service_from_uri(const Ax_soapstream* soap)
{
	const char* uri = NULL;
	switch (soap->trtype)
	{
	case APTHTTP:
		uri = soap->so.http.uri_path;
		break;
	case APTFTP:
		//TODO
		break;
	case APTSMTP:
		//TODO
		break;
	default:; //some error condition
	}
	
	const char* service;
	if (uri)
	{
		service = strstr(uri, AXIS_URI_EXTENSION) + strlen(AXIS_URI_EXTENSION);
		return service;
	}
	return NULL;
}
