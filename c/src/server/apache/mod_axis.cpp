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
 */

#include "ApacheTransport.h"

#define xxx ap_log_rerror(APLOG_MARK,APLOG_ERR, globr,"logged here");
#define yyy ap_log_rerror(APLOG_MARK, APLOG_ERR, globr,"logged here");

/* file: mod_axis.cpp */
/* here's the content handler */

extern int process_request (SOAPTransport* str);
extern unsigned char chEBuf[1024];

/* Call initialize_module() [of Packet.h] from within this method */
extern "C" static void module_init(server_rec* svr_rec, pool* p)
{
    initialize_module (1);
}

/* Call initialize_process() [of Packet.h] from within this method */
extern "C" static void axis_Init (server_rec* svr_rec, pool* p)
{
}

/*Call finalize_process() [of Packet.h] from within this method*/
extern "C" static void axis_Fini (server_rec* svr_rec, pool* p)
{
}

int axis_handler_helper(request_rec* req_rec)
{
    int rc;
    SOAPTransport* pTransport;
    pTransport = new ApacheTransport((void*)req_rec);

    /* for SOAP 1.2 this this should be "application/soap+xml" but keep this for
     * the moment. */
    req_rec->content_type = "text/xml"; 
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
    if (ap_should_client_block (req_rec));

    if (0 != process_request(pTransport))
    {
		delete pTransport;
        return OK;
    }
	delete pTransport;
    return OK;	
}

extern "C" static int axis_handler(request_rec* req_rec)
{
	return axis_handler_helper(req_rec);
}

/* Make the name of the content handler known to Apache */
extern "C" static handler_rec axis_handlers[] = { {"axis", axis_handler}, {NULL} };

/* Tell Apache what phases of the transaction we handle */
extern "C" module MODULE_VAR_EXPORT axis_module = {
    STANDARD_MODULE_STUFF,
    module_init,                /* module initializer                 */
    NULL,                       /* per-directory config creator       */
    NULL,                       /* dir config merger                  */
    NULL,                       /* server config creator              */
    NULL,                       /* server config merger               */
    NULL,                       /* command table                      */
    axis_handlers,              /* [9]  content handlers              */
    NULL,                       /* [2]  URI-to-filename translation   */
    NULL,                       /* [5]  check/validate user_id        */
    NULL,                       /* [6]  check user_id is valid *here* */
    NULL,                       /* [4]  check access by host address  */
    NULL,                       /* [7]  MIME type checker/setter      */
    NULL,                       /* [8]  fixups                        */
    NULL,                       /* [10] logger                        */
    NULL,                       /* [3]  header parser                 */
    axis_Init,                  /* process initialization             */
    axis_Fini,                  /* process exit/cleanup               */
    NULL                        /* [1]  post read_request handling    */
};
