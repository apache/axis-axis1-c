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
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 */

#include "Apache2Transport.h"
#include <iostream>
#include <axis/AxisException.hpp> 

#define xxx ap_log_rerror(APLOG_MARK,APLOG_ERR, globr,"logged here");
#define yyy ap_log_rerror(APLOG_MARK, APLOG_ERR, globr,"logged here");

/* file: mod_axis2.cpp */
/* here's the content handler */

extern "C" int initialize_module (int bServer);
extern "C" int uninitialize_module ();
extern int process_request(SOAPTransport* str);
extern unsigned char chEBuf[1024];

int axis_handler_helper(request_rec* req_rec)
{
    int rc;
    SOAPTransport* pTransport;
	if ((!req_rec->handler) || strcmp(req_rec->handler, "axis") != 0)
    {
        return DECLINED;
    }

    pTransport = new Apache2Transport((void*)req_rec);

    /* for SOAP 1.2 this this should be "application/soap+xml" but keep this for
     * the moment. */
    req_rec->content_type = (M_POST == req_rec->method_number) ? 
		"text/xml" : "text/html";

    // Samisa : if it is a GET request with wsdl arg then content type should be text/xml
    if (req_rec->args)
    {
        if( strcmp("wsdl", req_rec->args) == 0 )
            req_rec->content_type = "text/xml";
    }

	 /* Set up the read policy from the client.*/
    if ((rc = ap_setup_client_block(req_rec, REQUEST_CHUNKED_ERROR)) != OK)
    {
		delete pTransport;
        return rc;
    }

    /* Tell the client that we are ready to receive content and check whether 
     * client will send content. control will pass to this block only if there is
     * body content in the request 
     */
    ap_should_client_block(req_rec);

    if (0 != process_request(pTransport))
    {
		delete pTransport;
        return OK;
    }
	delete pTransport;
    return OK;	
}

extern "C"
{ 

static apr_status_t module_exit(void *data)
{
    uninitialize_module();

    return APR_SUCCESS;
}

static void module_init(apr_pool_t* p, server_rec* svr_rec)
{
   try
   {
		apr_pool_cleanup_register(p, NULL, module_exit, apr_pool_cleanup_null);
		initialize_module(1);
   }
   catch(AxisException& e) 
   {
		std::cerr << "An error occurred while Axis was initializing: " << e.what() << std::endl;
   }
   catch(...) 
   {
		std::cerr << "An unkown error occurred while Axis was initializing: " << std::endl;
   }
}

static int axis_handler(request_rec* req_rec)
{
	try
	{
		return axis_handler_helper(req_rec);
	}
	catch(AxisException& e) 
	{
		std::cerr << "An error occurred while Axis was initializing: " << e.what() << std::endl;
	}
	catch(...) 
	{
		std::cerr << "An unkown error occurred while Axis was initializing: " << std::endl;
	}
}

static void mod_axis_register_hooks(apr_pool_t* p)
{
    ap_hook_child_init(module_init, NULL, NULL, APR_HOOK_REALLY_FIRST);
    ap_hook_handler(axis_handler, NULL, NULL, APR_HOOK_LAST);    
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
}
