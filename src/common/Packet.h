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
 * @author Sanjaya Singharage (sanjayasing@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

#pragma warning (disable : 4786)

#if !defined(__PACKET_H_INCLUDED__)
#define __PACKET_H_INCLUDED__

#include "GDefine.h"

#define AXIS_URI_EXTENSION "/axis/"

typedef struct 
{
	const void* ip_stream;
	const void* op_stream;
} Ax_iostream;

typedef enum
{
	AXIS_HTTP_GET,
	AXIS_HTTP_POST,
	AXIS_HTTP_UNSUPPORTED
} AXIS_HTTP_METHOD;

typedef struct
{
	char* headername;
	char* headervalue;
} Ax_header;

typedef struct
{
	const char* uri_path;
	Ax_header* ip_headers;
	int ip_headercount;
	Ax_header* op_headers;
	int op_headercount;
	AXIS_HTTP_METHOD ip_method;
	AXIS_HTTP_METHOD op_method;
} Ax_stream_http;

typedef struct
{
	int dummy;  
} Ax_stream_smtp;

typedef union
{
	Ax_stream_http http;
	Ax_stream_smtp smtp;
} Ax_soapcontent;

/**
 *Function pointer definitions for trasport layer
 */
typedef int (*AXIS_SEND_SEND_BYTES)(const char*, const void*);
typedef int (*AXIS_GET_BYTES)(char*, int, int*, const void*);
typedef int (*AXIS_SEND_TRANSPORT_INFORMATION)(void*); /*Ax_soapstream*/
typedef int (*AXIS_GET_TRANSPORT_INFORMATION)(void*);/*Ax_soapstream*/

/**
 *Each transport module on the server side should populate following struct with 
 *their transport function pointers in order for the Axis Engine to work properly.
 */
typedef struct
{
	AXIS_SEND_SEND_BYTES pSendFunct;
	AXIS_GET_BYTES pGetFunct;
	AXIS_SEND_TRANSPORT_INFORMATION pSendTrtFunct;
	AXIS_GET_TRANSPORT_INFORMATION pGetTrtFunct;
} Ax_transport;

typedef struct
{
	Ax_soapcontent so;
	Ax_iostream str;
	char* sessionid;
	AXIS_PROTOCOL_TYPE trtype;
	Ax_transport transport;
} Ax_soapstream;

int set_header(Ax_soapstream* soap, char * pchkey, char * pchvalue);
const char* get_header(const Ax_soapstream* soap, const char* pchkey);
const char* get_service_from_uri(const Ax_soapstream* soap);

/*This function is implemented in axis*/
/*int initialize_process();*/


/*This function is implemented in axis*/
/*int finalize_process();*/

#ifdef __cplusplus
extern "C"
{
#endif
	/*This function is implemented in axis*/
	int uninitialize_module();

	/*This function is implemented in axis*/
	int initialize_module(int bServer, const char * wsddPath);

	/*This function is implemented in axis*/
	int process_request(Ax_soapstream* str);

	/*This function should be implemented by module authors*/
	/*Allows to send pieces of soap response the transport handler*/
	/*int send_response_bytes(const char* res, const void* opstream);*/

	/*This function should be implemented by module authors*/
	/*Allows axis to get pieces of the request as they come to the transport listener*/
	/*int get_request_bytes(char* req, int reqsize, int* retsize, const void* ipstream);*/

	/*This fucntion should be implemented by module authors*/
	/*int send_transport_information(Ax_soapstream *str);*/

	/*int receive_transport_information(Ax_soapstream *str);*/
#ifdef __cplusplus
}
#endif

#endif


