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
 *
 *
 *
 *
 * @author Sanjaya Singharage (sanjayas@jkcsworld.com)
 *
 */

#include <apache2_0/httpd.h>
#include <apache2_0/http_config.h>
#include <apache2_0/http_core.h>
#include <apache2_0/http_protocol.h>
#include <apache2_0/http_log.h>
#include <apache2_0/ap_compat.h>
#include <axis/common/Packet.h>
#include <malloc.h>

/*
The apache 2.0 module for Axis. THIS IS NOT COMPLETED
*/

extern int process_request(Ax_soapstream* str);
//extern int process(soapstream *);
extern unsigned char chEBuf[1024];

//Call initialize_module() [of Packet.h] from within this method
void module_init(server_rec *svr_rec, apr_pool_t* p)
{
	initialize_module(1);
}


//Call initialize_process() [of Packet.h] from within this method
void  axis_Init(server_rec *svr_rec, apr_pool_t* p)
{}
//Call finalize_process() [of Packet.h] from within this method
void axis_Fini(server_rec *svr_rec, apr_pool_t* p)
{}



int send_response_bytes(char* res, void* opstream)
{
	ap_rputs(res, (request_rec*)opstream);
	return 0;
}



//Should dispatch the headers from within this method
int send_transport_information(Ax_soapstream* hdr)
{
      ap_send_http_header((request_rec*)hdr->str.op_stream);
	  return 0;
}

int get_request_bytes(char* req, int reqsize, int* retsize, void* ipstream)
{
	int len_read;
	//ap_hard_timeout("util_read", (request_rec*)ipstream);
	len_read = ap_get_client_block((request_rec*)ipstream, req, reqsize);
	//ap_reset_timeout((request_rec*)ipstream);
	*retsize =  len_read;
	return 0;
}


static int mod_axis_method_handler (request_rec *req_rec)
{
	int rc;
	Ax_soapstream* sstr;
	apr_array_header_t* arr;

	sstr = malloc(sizeof(Ax_soapstream));
	sstr->trtype = APTHTTP;
	//req_rec is used as both input and output streams
	sstr->str.ip_stream = req_rec;
	sstr->str.op_stream = req_rec;
	//just add some sessionid
	sstr->sessionid = "this is temporary session id";

	req_rec->content_type = "text/xml"; //for SOAP 1.2 this this should be "application/soap+xml" but keep this for the moment
	//set up the read policy from the client.
	if ((rc = ap_setup_client_block(req_rec, REQUEST_CHUNKED_ERROR)) != OK)
	{
		return rc;
	}

	//the member, "path" of "parsed_uri" contains the uri of the 
	//request (i.e "/abc/xyz" part of http://somehost/abc/xyz)
	sstr->so.http.uri_path = req_rec->parsed_uri.path;

	//ap_table_elts returns an array_header struct. The nelts element of that struct contains the number of
	//input header elements. Finally assigns that to the axis soap data structure. 
	sstr->so.http.ip_headercount = ap_table_elts(req_rec->headers_in)->nelts;  

	//casting req_rec->headers_in to axis header struct and assigning that to the axis soap structure. Hope this is ok

	//obtain the array_header from the headers_in table and assign it to the axis soap structure
	arr = ap_table_elts(req_rec->headers_in);
	sstr->so.http.ip_headers = (Ax_header*)arr->elts;

	//Determine the http method and assign it to the axis soap structure
	switch (req_rec->method_number)
	{
	case M_GET:
      sstr->so.http.ip_method = AXIS_HTTP_GET;
      break;
	case M_POST:
      sstr->so.http.ip_method = AXIS_HTTP_POST;
      break;
	default:
      sstr->so.http.ip_method = AXIS_HTTP_UNSUPPORTED;   
	}

  	//tell the client that we are ready to receive content and check whether client will send content
	//control will pass to this block only if there is body content in the request
    if (ap_should_client_block(req_rec));

	if(0 != process_request(sstr))
	{
		ap_rputs("SOAP Engine failed to response",req_rec);
		return OK;
	}


	free(sstr);
	//free(arr);
	return OK;
}

/*
 * This function is a callback and it declares what other functions
 * should be called for request processing and configuration requests.
 * This callback function declares the Handlers for other events.
 */
static void mod_axis_register_hooks (apr_pool_t *p)
{
	// I think this is the call to make to register a handler for method calls (GET PUT et. al.).
	// We will ask to be last so that the comment has a higher tendency to
	// go at the end.
	ap_hook_handler(mod_axis_method_handler, NULL, NULL, APR_HOOK_LAST);
}

/*
 * Declare and populate the module's data structure.  The
 * name of this structure ('tut1_module') is important - it
 * must match the name of the module.  This structure is the
 * only "glue" between the httpd core and the module.
 */
module AP_MODULE_DECLARE_DATA mod_axis =
{
	// Only one callback function is provided.  Real
	// modules will need to declare callback functions for
	// server/directory configuration, configuration merging
	// and other tasks.
	STANDARD20_MODULE_STUFF,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	mod_axis_register_hooks,			/* callback for registering hooks */
	//	mod_tut1_register_hooks
};

