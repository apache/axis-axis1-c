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
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__PACKET_H_INCLUDED__)
#define __PACKET_H_INCLUDED__

#include "GDefine.h"

typedef enum 
{
	SOAPACTION_HEADER,
	SERVICE_URI,
	OPERATION_NAME,
	SOAP_MESSAGE_LENGTH
} AXIS_TRANSPORT_INFORMATION_TYPE;
/**
 * This structure is supposed to keep the streaming objects of the transport
 * such as iostream in c++, request_rec in apache module etc
 */
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

/**
 * This structure is used to keep string key/value pairs such as http headers. set_header
 * function can be used to add headers to a Ax_soapstream
 */ 
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
	const char* uri_path;
	Ax_header* ip_headers;
	int ip_headercount;
	Ax_header* op_headers;
	int op_headercount;
	AXIS_HTTP_METHOD ip_method;
	AXIS_HTTP_METHOD op_method;
} Ax_stream_https;

typedef struct
{
	int dummy;  
} Ax_stream_smtp;

typedef union
{
	Ax_stream_http* http;
	Ax_stream_smtp* smtp;
	Ax_stream_https* https;
	void* other; /*transport specific other protocols can have its own structs here*/
} Ax_soapcontent;

typedef enum
{
	TRANSPORT_FINISHED=0,
	TRANSPORT_IN_PROGRESS,
	TRANSPORT_FAILED
} AXIS_TRANSPORT_STATUS;

/**
 * Function pointer definitions for axis trasport module call backs 
 */

/**
 * This function is provided by the transport modules. Called by Axis engine when it needs to send SOAP
 * message. This function may be called several times.
 * @param 
 *		1st - null terminated character buffer to be sent
 *		2nd - buffer id	which identifies the buffer
 *		3rd - Ax_soapstream object which act like a thread id
 * @return
 *	TRANSPORT_FINISHED - Transport done and buffer is free to re-use.
 *  TRANSPORT_IN_PROGRESS - Transport is in progress and buffer cannot be re-used yet.
 *  TRANSPORT_FAILED - Transport has failed and no use of trying to send any more bytes. Better to abort.
 * Note: if the bufferid is NULL that indicates the buffer is a temporary buffer and should not be retained.
 *		 So in this case the buffer should be immediately sent.
 */
typedef AXIS_TRANSPORT_STATUS (AXISCALL * AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES)(const char*, const void*, const void*);

/**
 * This function is provided by the transport modules. Called by Axis engine when it needs to get SOAP
 * message. This function may be called several times.
 * @param 
 *		1st - pointer to buffer pointer to which the transport's buffer is set
 *		2nd - pointer to an int to which the number of bytes read is set
 *		3rd - Ax_soapstream object which act like a thread id
 * @return
 *	TRANSPORT_FINISHED - No any more message bytes to be received. If a buffer is present it is the last
 *						 buffer.
 *  TRANSPORT_IN_PROGRESS - There may be more message bytes to be received. Axis Engine may call this 
 *							function again to get any subsequent message buffers. Buffer should be present.
 *  TRANSPORT_FAILED - Transport has failed and no use of trying to get any more bytes. Better to abort.
 */
typedef AXIS_TRANSPORT_STATUS (AXISCALL * AXIS_MODULE_CALLBACK_GET_MESSAGE_BYTES)(const char**, int*, const void*);

/**
 * This function is provided by the transport modules. Called by Axis engine when it needs to say the
 * transport module that the engine is no longer using the buffer and can be re-used.
 * @param 
 *		1st - buffer that Axis got from the transport layer.
 *		2nd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_MODULE_CALLBACK_RELEASE_RECEIVE_BUFFER)(const char*, const void*);

/**
 * This function is provided by the transport modules. Called by Axis engine when it needs to set any
 * transport information such as http headers. This function can be called multiple times. But when
 * to send the transport information is upto the transport module
 * @param
 *		1st - Transport information type to set
 *		2nd - Information value
 *		3rd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_MODULE_CALLBACK_SET_TRANSPORT_INFORMATION)(AXIS_TRANSPORT_INFORMATION_TYPE, const char*, const void*);

/**
 * This function is provided by the transport modules. Called by Axis engine when it needs to get any
 * transport information such as http headers. This function can be called only once.
 * @param
 *		1st - Transport information type to get
 *		2nd - Ax_soapstream object which act like a thread id
 */
typedef const char* (AXISCALL * AXIS_MODULE_CALLBACK_GET_TRANSPORT_INFORMATION)(AXIS_TRANSPORT_INFORMATION_TYPE, const void*);

/**
 * Function pointer definitions for axis call backs 
 */

/**
 * This function is provided by the Axis Engine. Called by transport module when it needs to say that
 * a message buffer passed to it is no longer being used by the transport and can be re-used by the 
 * Axis engine.This function should be called for each buffer if AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES
 * returned TRANSPORT_IN_PROGRESS.
 * @param 
 *		1st - buffer that Axis gave to the transport layer
 *		2nd - buffer id	which uniquely identifies the buffer
 *		3rd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER)(const char*, const void*, const void*);

/**
 * Each transport module on the server side should populate following struct with 
 * their transport function pointers in order for the Axis Engine to work properly.
 */
typedef struct
{
	AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES pSendFunct;
	AXIS_MODULE_CALLBACK_GET_MESSAGE_BYTES pGetFunct;
	AXIS_MODULE_CALLBACK_RELEASE_RECEIVE_BUFFER pRelBufFunct;
	AXIS_MODULE_CALLBACK_SET_TRANSPORT_INFORMATION pSetTrtFunct;
	AXIS_MODULE_CALLBACK_GET_TRANSPORT_INFORMATION pGetTrtFunct;
} Ax_transport;

typedef struct
{
	Ax_soapcontent so;
	Ax_iostream str;
	char* sessionid;
	AXIS_PROTOCOL_TYPE trtype;
	Ax_transport transport;
	void* reserved1; /* usage depend on the tranport module */
	void* reserved2; /* usage depend on the tranport module */
} Ax_soapstream;

typedef struct
{
	const void* bufferid ;
	const char* buffer;
} sendbuffers;

/* NO_OF_SERIALIZE_BUFFERS should be equal to the corresponding value in the axis configuration file */
#define NO_OF_SERIALIZE_BUFFERS 20

#ifdef __cplusplus
extern "C"
{
#endif
/**
 * Functions to manipulate Ax_soapstream object. Implemented in Packet.cpp
 *
 */
int set_property(Ax_soapstream* stream, char * pchkey, char * pchvalue);
const char* get_property(const Ax_soapstream* stream,const char* pchkey);
void remove_all_properties(Ax_soapstream* stream);

/**
 * This function is implemented in axis and should be called ONCE to uninitialize Axis Engine when the 
 * Axis SOAP processor shuts down.
 */
int uninitialize_module();

/**
 * This function is implemented in axis and should be called ONCE to initialize Axis Engine.
 */
int initialize_module(int bServer);

/**
 * This callback function is implemented in axis and should be called by the transport module in order to
 * start processing a SOAP message. 
 * @param 
 *		stream - Ax_soapstream object contains information about the SOAP stream and the message. This also 
 *				 should be populated with the transport module.
 */
int process_request(Ax_soapstream* stream);

/**
 * This callback function is implemented in axis and should be called by the transport module. 
 * @param 
 *		buffer - Buffer passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 *		bufferid - Id of the buffer passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 *		stream - Ax_soapstream object passed to transport by calling transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *				 callback
 */
void axis_buffer_release(const char* buffer, const void* bufferid, const void* stream);

#ifdef __cplusplus
}
#endif

#endif


