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
 *
 *
 * @author Sanjaya Singharage (sanjayasing@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__PACKET_H_OF_AXIS_INCLUDED__)
#define __PACKET_H_OF_AXIS_INCLUDED__

#include "GDefine.h"

typedef enum 
{
    SOAPACTION_HEADER,
    SERVICE_URI,
    OPERATION_NAME,
    SOAP_MESSAGE_LENGTH
} AXIS_TRANSPORT_INFORMATION_TYPE;

/*
 * This structure is supposed to keep the streaming objects of the transport
 * such as iostream in c++, request_rec in apache module etc
 */
/*typedef struct 
{
    const void* ip_stream;
    const void* op_stream;
} Ax_iostream;
*/
typedef enum
{
    AXIS_HTTP_GET,
    AXIS_HTTP_POST,
    AXIS_HTTP_UNSUPPORTED
} AXIS_HTTP_METHOD;

/*
 * This structure is used to keep string key/value pairs such as 
 * http headers. set_header
 * function can be used to add headers to a Ax_soapstream
 */ 
typedef struct
{
    char* headername;
    char* headervalue;
} Ax_header;

/*
typedef struct
{
    char* uri_path;
    Ax_header* ip_headers;
    int ip_headercount;
    Ax_header* op_headers;
    int op_headercount;
    AXIS_HTTP_METHOD ip_method;
    AXIS_HTTP_METHOD op_method;
} Ax_stream_http, Ax_stream_https;

typedef struct
{
    int dummy;  
} Ax_stream_smtp;

typedef union
{
    Ax_stream_http* http;
    Ax_stream_https* https;
    Ax_stream_smtp* smtp;
    void* other; 
} Ax_soapcontent;
*/
typedef enum
{
    TRANSPORT_FINISHED=0,
    TRANSPORT_IN_PROGRESS,
    TRANSPORT_FAILED
} AXIS_TRANSPORT_STATUS;

/*
 * Function pointer definitions for axis trasport module call backs 
 */

/*
 * This function is provided by the transport modules.
 * Called by Axis engine when it needs to send SOAP
 * message. This function may be called several times.
 * @param 
 *         1st - null terminated character buffer to be sent
 *        2nd - buffer id    which identifies the buffer
 *        3rd - Ax_soapstream object which act like a thread id
 * @return
 *    TRANSPORT_FINISHED - Transport done and buffer is free to re-use.
 *  TRANSPORT_IN_PROGRESS - Transport is in progress and buffer 
 *                          cannot be re-used yet.
 *  TRANSPORT_FAILED - Transport has failed and no use of trying to 
 *                     send any more bytes. Better to abort.
 * Note: if the bufferid is NULL that indicates the buffer is a 
 *       temporary buffer and should not be retained.
 *         So in this case the buffer should be immediately sent.
 */
typedef AXIS_TRANSPORT_STATUS 
(AXISCALL * AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES)
(const char*, const void*, const void*);

/*
 * This function is provided by the transport modules. 
 * Called by Axis engine when it needs to get SOAP
 * message. This function may be called several times.
 * @param 
 *        1st - pointer to buffer pointer to which the transport's buffer is set
 *        2nd - pointer to an int to which the number of bytes read is set
 *        3rd - Ax_soapstream object which act like a thread id
 * @return
 *    TRANSPORT_FINISHED - No any more message bytes to be received. 
 *                       If a buffer is present it is the last
 *                         buffer.
 *  TRANSPORT_IN_PROGRESS - There may be more message bytes to be received. 
 *                          Axis Engine may call this 
 *                            function again to get any subsequent message 
 *                          buffers. Buffer should be present.
 *  TRANSPORT_FAILED - Transport has failed and no use of trying to get any
 *                     more bytes. Better to abort.
 */
typedef AXIS_TRANSPORT_STATUS 
(AXISCALL * AXIS_MODULE_CALLBACK_GET_MESSAGE_BYTES)
(const char**, int*, const void*);

/*
 * This function is provided by the transport modules. 
 * Called by Axis engine when it needs to say the
 * transport module that the engine is no longer using the buffer 
 * and can be re-used.
 * @param 
 *        1st - buffer that Axis got from the transport layer.
 *        2nd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_MODULE_CALLBACK_RELEASE_RECEIVE_BUFFER)
(const char*, const void*);

/**
 * This function is provided by the transport modules. 
 * Called by Axis engine when it needs to set any
 * transport information such as http headers. 
 * This function can be called multiple times. But when
 * to send the transport information is upto the transport module
 * @param
 *        1st - Transport information type to set
 *        2nd - Information value
 *        3rd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_MODULE_CALLBACK_SET_TRANSPORT_INFORMATION)
(AXIS_TRANSPORT_INFORMATION_TYPE, const char*, const void*);

/*
 * This function is provided by the transport modules. 
 * Called by Axis engine when it needs to get any
 * transport information such as http headers. 
 * This function can be called only once.
 * @param
 *        1st - Transport information type to get
 *        2nd - Ax_soapstream object which act like a thread id
 */
typedef const char* (AXISCALL * AXIS_MODULE_CALLBACK_GET_TRANSPORT_INFORMATION)
(AXIS_TRANSPORT_INFORMATION_TYPE, const void*);

/*
 * Function pointer definitions for axis call backs 
 */

/*
 * This function is provided by the Axis Engine. 
 * Called by transport module when it needs to say that
 * a message buffer passed to it is no longer being used by the transport 
 * and can be re-used by the 
 * Axis engine.This function should be called for each buffer 
 * if AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES
 * returned TRANSPORT_IN_PROGRESS.
 * @param 
 *        1st - buffer that Axis gave to the transport layer
 *        2nd - buffer id    which uniquely identifies the buffer
 *        3rd - Ax_soapstream object which act like a thread id
 */
typedef void (AXISCALL * AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER)
(const char*, const void*);

/*
 * Each transport module on the server side should populate following struct with 
 * their transport function pointers in order for the Axis Engine to work properly.
 */
/*typedef struct
{
	AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES pSendFunct;
	AXIS_MODULE_CALLBACK_GET_MESSAGE_BYTES pGetFunct;
	AXIS_MODULE_CALLBACK_RELEASE_RECEIVE_BUFFER pRelBufFunct;
	AXIS_MODULE_CALLBACK_SET_TRANSPORT_INFORMATION pSetTrtFunct;
	AXIS_MODULE_CALLBACK_GET_TRANSPORT_INFORMATION pGetTrtFunct;
	AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pRelSendBufFunct;
} Ax_transport;

typedef struct
{
    Ax_soapcontent so;
    Ax_iostream str;
    char* sessionid;
    AXIS_PROTOCOL_TYPE trtype;
    Ax_transport transport;
    void* reserved1; 
    void* reserved2; 
} Ax_soapstream;
*/
typedef struct
{
    const void* pBufferId;
    const char* pcBuffer;
} BufferInfo;

/* NO_OF_SERIALIZE_BUFFERS should be equal to the corresponding 
 * value in the axis configuration file 
 */
#define NO_OF_SERIALIZE_BUFFERS 20

#if defined(WIN32) 
#define STORAGE_CLASS_INFO __declspec(dllexport)
#else
#define STORAGE_CLASS_INFO 
#endif

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Functions to manipulate Ax_soapstream object. Implemented in Packet.cpp
 *
 */
/*
STORAGE_CLASS_INFO int set_property(Ax_soapstream* stream, char * pchkey, 
                                    char * pchvalue);
STORAGE_CLASS_INFO const char* get_property(const Ax_soapstream* stream,
                                            const char* pchkey);
STORAGE_CLASS_INFO void remove_all_properties(Ax_soapstream* stream);
*/
/*
 * This function is implemented in axis and should be called ONCE to 
 * uninitialize Axis Engine when the 
 * Axis SOAP processor shuts down.
 */
STORAGE_CLASS_INFO int uninitialize_module();

/*
 * This function is implemented in axis and should be called ONCE to 
 * initialize Axis Engine.
 */
STORAGE_CLASS_INFO int initialize_module(int bServer);

/*
 * This callback function is implemented in axis and should be called by the 
 * transport module in order to
 * start processing a SOAP message. 
 * @param 
 * stream - Ax_soapstream object contains information about the SOAP stream 
 *          and the message. This also should be populated with the 
 *          transport module.
 */
STORAGE_CLASS_INFO int process_request(void* stream);

/*
 * This callback function is implemented in axis and should be called by 
 * the transport module. 
 * @param 
 *        buffer - Buffer passed to transport by calling transport's 
 *      AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES 
 *                 callback
 *        bufferid - Id of the buffer passed to transport by calling transport's 
 *               AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES callback
 *        stream - Ax_soapstream object passed to transport by calling 
 *               transport's AXIS_MODULE_CALLBACK_SEND_MESSAGE_BYTES callback
 */
STORAGE_CLASS_INFO void axis_buffer_release(const char* buffer, 
                                            const void* bufferid, 
                                            const void* stream);

#ifdef __cplusplus
}
#endif

#endif




