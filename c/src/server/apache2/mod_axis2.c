/* -*- C++ -*- */
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
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */

#ifdef WIN32
#else
#define PATH_MAX 4096
#endif

#include <apache2_0/httpd.h>
#include <apache2_0/http_config.h>
#include <apache2_0/http_core.h>
#include <apache2_0/http_protocol.h>
#include <apache2_0/http_log.h>
#include <apache2_0/ap_compat.h>
#include <apache2_0/apr_tables.h>
#include <axis/server/Packet.h>
#include <malloc.h>

#define AXIS_URI_EXTENSION "/axis"

/*
 * The apache 2.0 module for Axis. THIS IS NOT COMPLETED
 */

/* Following is the character that should be used to separate the method name 
 * in the SOAPAction header value. Ex: "http://localhost:80/axis/Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

extern int process_request (Ax_soapstream* str);
/* extern int process(soapstream *); */
extern unsigned char chEBuf[1024];

#define SIZEOFMODULEBUFFER 4096



/*
 * This method adds the http header to the Ax_soapstream. These headers will be
 * dispatched later before sending the http body
 */
static void AXISCALL set_transport_information 
    (AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, 
    Ax_soapstream* stream)
{
    const char* key = NULL;
    switch (type)
    {
        case SOAPACTION_HEADER:  /* needed only in the client side ? */
            break;
        case SERVICE_URI:        /* need to set ? */
            break;
        case OPERATION_NAME:     /* need to set ? */
            break;
        case SOAP_MESSAGE_LENGTH:
            key = "Content-Length"; /* This is apache module and transport is 
                                     * http so the key 
                                     */
            break;
        default:;
    }
    if (key)
    {
        ap_table_set (((request_rec*) stream->str.op_stream)->headers_out, key,
            value);
    }
#ifdef CHUNCKED_DATA_SUPPORTED
    ap_send_http_header ((request_rec*) hdr->str.op_stream);
    /* should we remove the sent headers ? Sanjaya ? */
#endif
}

/* Call initialize_module() [of Packet.h] from within this method */
void module_init (server_rec* svr_rec, apr_pool_t* p)
{
    initialize_module (1);
}

/*
 * If this module is not handling chunked data transfer, it accumulates all 
 * buffers before sending them so that the http header "Content-Length" can be 
 * sent before sending the http body
 */
static AXIS_TRANSPORT_STATUS AXISCALL send_response_bytes (const char* buffer, 
    const void* bufferid, const void* pStream)
{
    const Ax_soapstream* stream = (Ax_soapstream*) pStream;
#ifndef CHUNCKED_DATA_SUPPORTED
    int index;
    sendbuffers* pbuffers;
#endif

    if (!bufferid) /* temporary buffers should always sent immediately */
    {
        ap_rputs (buffer, (request_rec*) (stream->str.op_stream));
        return TRANSPORT_FINISHED;
    }

#ifdef CHUNCKED_DATA_SUPPORTED
    /* Do we need to send any headers and length of this chunk ? Sanjaya ? */
    ap_rputs (buffer, (request_rec*) (stream->str.op_stream));
    /* Do we need to send any indication to mark the end of this 
     * chunk ? Sanjaya ?
     */
    return TRANSPORT_FINISHED;
#else
    pbuffers = (sendbuffers*) stream->reserved1;
    for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if (!pbuffers[index].buffer)
        {
            pbuffers[index].buffer = buffer;
            pbuffers[index].bufferid = bufferid;
            break;
        }
    }
    return TRANSPORT_IN_PROGRESS;
#endif
}

/* Call initialize_process() [of Packet.h] from within this method */
void axis_Init (server_rec* svr_rec, apr_pool_t* p)
{
}

/* Call finalize_process() [of Packet.h] from within this method */
void axis_Fini (server_rec* svr_rec, apr_pool_t* p)
{
}

/*
 * This function is called by the Axis Engine whenever it needs to get bytes 
 * from the transport layer.
 */
static AXIS_TRANSPORT_STATUS AXISCALL get_request_bytes (const char** req, 
    int* retsize, const Ax_soapstream* stream)
{
#ifdef USE_XERCES_PARSER
    int nBufSize = *retsize;
    int len_read;
    char* pBuffer = *req;
    if (!(*req))
        return TRANSPORT_FAILED;
    /* ap_hard_timeout("util_read", (request_rec*)stream->str.ip_stream); */
    len_read = ap_get_client_block ((request_rec*) stream->str.ip_stream, *req,
        nBufSize);
    /* ap_reset_timeout((request_rec*)stream->str.ip_stream); */
    *retsize = len_read;
    if (len_read < nBufSize)
    {
        pBuffer[len_read] = '\0';
        return TRANSPORT_FINISHED;
    }
    else
        return TRANSPORT_IN_PROGRESS;
#else
    /* How can I detect an error when reading stream ? Sanjaya ?
     * In case of an error set buffer to null, size 0 and 
     * return TRANSPORT_FAILED 
     */
    int len_read;
    char* pBuffer = stream->reserved2;
    if (!pBuffer)
        return TRANSPORT_FAILED;
    /* ap_hard_timeout("util_read", (request_rec*)stream->str.ip_stream); */
    len_read = ap_get_client_block ((request_rec *) stream->str.ip_stream, 
        pBuffer, SIZEOFMODULEBUFFER);
    /* ap_reset_timeout((request_rec*)stream->str.ip_stream); */
    *req = pBuffer;
    *retsize = len_read;
    if (len_read < SIZEOFMODULEBUFFER)
    {
        pBuffer[len_read] = '\0';
        return TRANSPORT_FINISHED;
    }
    else
        return TRANSPORT_IN_PROGRESS;
#endif
}

static void AXISCALL release_receive_buffer (const char* buffer, 
    const Ax_soapstream* stream)
{

}

static const char* AXISCALL get_transport_information 
    (AXIS_TRANSPORT_INFORMATION_TYPE type, Ax_soapstream* stream)
{
    const char* ptemp;
    switch (type)
    {
        case SOAPACTION_HEADER:
            return get_property (stream, "SOAPAction");
        case SERVICE_URI:
            if (strstr (stream->so.http->uri_path, AXIS_URI_EXTENSION))
            {
                return strstr (stream->so.http->uri_path, AXIS_URI_EXTENSION) +
                    strlen (AXIS_URI_EXTENSION) + 1;
            }
            else
            {
                return stream->so.http->uri_path;
            }
        case OPERATION_NAME:
            ptemp = get_property (stream, "SOAPAction");
            if (ptemp)
            {
                if (strstr (ptemp, SOAPACTION_METHODNAME_SEPARATOR))
                {
                    return strstr (ptemp, SOAPACTION_METHODNAME_SEPARATOR) +
                        strlen (SOAPACTION_METHODNAME_SEPARATOR);
                }
                else
                {
                    return ptemp;
                }
            }
        case SOAP_MESSAGE_LENGTH:
            return get_property (stream, "Content-Length"); 
	    /* This is apache module and transport is http so the key */
        default:;
    }
    return NULL;
}

static int mod_axis_method_handler (request_rec* req_rec)
{
    int rc;
    int ix;
    Ax_soapstream* sstr;
    apr_array_header_t* arr;
    apr_table_entry_t* pHeaderTable;
    Ax_header* pAx_Headers;

#ifndef CHUNCKED_DATA_SUPPORTED
    int contentLength = 0;
    int index;
    sendbuffers* pbuffers;
    char strtonum[8];
#endif

    if ((!req_rec->handler) || strcmp (req_rec->handler, "axis") != 0)
    {
        return DECLINED;
    }

    sstr = malloc (sizeof (Ax_soapstream));

    sstr->transport.pSendFunct = send_response_bytes;
    sstr->transport.pGetFunct = get_request_bytes;
    sstr->transport.pSetTrtFunct = set_transport_information;
    sstr->transport.pGetTrtFunct = get_transport_information;
    sstr->transport.pRelBufFunct = release_receive_buffer;

    sstr->trtype = APTHTTP;
    sstr->so.http = malloc (sizeof (Ax_stream_http));
    /* req_rec is used as both input and output streams */
    sstr->str.ip_stream = req_rec;
    sstr->str.op_stream = req_rec;
    /* just add some sessionid */
    sstr->sessionid = "this is temporary session id";

#ifdef CHUNCKED_DATA_SUPPORTED
    sstr->reserved1 = NULL;
    sstr->reserved2 = NULL;
#else
    sstr->reserved1 = calloc (NO_OF_SERIALIZE_BUFFERS, sizeof (sendbuffers));
#ifdef USE_XERCES_PARSER
#else
    sstr->reserved2 = malloc (SIZEOFMODULEBUFFER);
#endif
#endif

    /* set up the read policy from the client. */
    if ((rc = ap_setup_client_block (req_rec, REQUEST_CHUNKED_ERROR)) != OK)
    {
        if (sstr->reserved1)
            free (sstr->reserved1);
#ifdef USE_XERCES_PARSER
#else
        if (sstr->reserved2)
            free (sstr->reserved2);
#endif
        free (sstr->so.http);
        free (sstr);

        return rc;
    }

    /* The member, "path" of "parsed_uri" contains the uri of the 
     * request (i.e "/abc/xyz" part of http://somehost/abc/xyz) 
     */
    sstr->so.http->uri_path = req_rec->parsed_uri.path;

    /* ap_table_elts returns an array_header struct. The nelts element of that 
     * struct contains the number of input header elements. Finally assigns that
     * to the axis soap data structure. 
     */
    sstr->so.http->ip_headercount = ap_table_elts (req_rec->headers_in)->nelts;

    if (sstr->so.http->ip_headercount > 0)
    {
        /* obtain the array_header from the headers_in table and assign it to 
	 * the axis soap structure 
	 */
        arr = ap_table_elts (req_rec->headers_in);
        pHeaderTable = arr->elts;
        sstr->so.http->ip_headers = malloc (sizeof (Ax_header) * sstr->so.http->
            ip_headercount);
        pAx_Headers = sstr->so.http->ip_headers;
        for (ix = 0; ix < sstr->so.http->ip_headercount; ix++)
        {
            (pAx_Headers + ix)->headername = (pHeaderTable + ix)->key;
            (pAx_Headers + ix)->headervalue = (pHeaderTable + ix)->val;
        }
    }
    /* Determine the http method and assign it to the axis soap structure */
    switch (req_rec->method_number)
    {
        case M_GET:
            sstr->so.http->ip_method = AXIS_HTTP_GET;
            req_rec->content_type = "text/html";
            break;
        case M_POST:
            sstr->so.http->ip_method = AXIS_HTTP_POST;
            req_rec->content_type = "text/xml";
            /* for SOAP 1.2 this this should be "application/soap+xml"
               but keep this for the moment */
            break;
        default:
            sstr->so.http->ip_method = AXIS_HTTP_UNSUPPORTED;
    }

    /* Tell the client that we are ready to receive content and check whether 
     * client will send content control will pass to this block only if there is
     * body content in the request */
    if (ap_should_client_block (req_rec));

    if (0 != process_request (sstr))
    {
        if (sstr->reserved1)
            free (sstr->reserved1);
#ifdef USE_XERCES_PARSER
#else
        if (sstr->reserved2)
            free (sstr->reserved2);
#endif
        free (sstr->so.http);
        free (sstr);

        ap_rputs ("SOAP Engine failed to response", req_rec);
        return OK;
    }

#ifdef CHUNCKED_DATA_SUPPORTED
    /* headers have already been sent. see set_transport_information
     * http body too have been sent
     * Do we need to send any indication to mark end of chuncked 
     * data ? Sanjaya ? 
     */
    
#else
    /* Calculate Content-Length and set header */
    pbuffers = (sendbuffers*) sstr->reserved1;
    for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
        if (!pbuffers[index].buffer)
            break;
        contentLength += strlen (pbuffers[index].buffer);
    }
    if (contentLength != 0)     /* do only if the http body is not empty. */
    {
        sprintf (strtonum, "%d", contentLength);
        set_transport_information (SOAP_MESSAGE_LENGTH, strtonum, sstr);
        ap_send_http_header (req_rec);
        /* Send all buffers */
        pbuffers = (sendbuffers*) sstr->reserved1;
        for (index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
        {
            if (!pbuffers[index].buffer)
                break;
            ap_rputs (pbuffers[index].buffer, req_rec);
            /* Let Axis know that the buffer is no longer in use */
            axis_buffer_release (pbuffers[index].buffer,
                pbuffers[index].bufferid, sstr);
        }
    }
    /* Free the array */
    if (sstr->reserved1)
        free (sstr->reserved1);

#ifdef USE_XERCES_PARSER
#else
    if (sstr->reserved2)
        free (sstr->reserved2);
#endif

#endif

    free (sstr);
    /* free(arr); */
    return OK;
}

static void mod_axis_register_hooks (apr_pool_t* p)
{
    ap_hook_child_init (module_init, NULL, NULL, APR_HOOK_REALLY_FIRST);
    /* ap_hook_pre_connection(axis_Init, NULL, NULL, APR_HOOK_FIRST); */
    ap_hook_handler (mod_axis_method_handler, NULL, NULL, APR_HOOK_LAST);
    /* ap_hook_process_connection(axis_Fini, NULL, NULL, APR_HOOK_REALLY_LAST);
     */
}


module AP_MODULE_DECLARE_DATA axis_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    mod_axis_register_hooks,
};
