#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "../../common/Packet.h"
#include <string.h>
#include <malloc.h>

/* file: mod_axis.c */
/* here's the content handler */

extern int process(soapstream *);
extern unsigned char chEBuf[1024];

static int axis_handler(request_rec *r) 
{
	char argsbuffer[HUGE_STRING_LEN];
	memset(argsbuffer,0,HUGE_STRING_LEN);
	int rc;

	soapstream * sstr = malloc(sizeof(soapstream));
	sstr->trtype=APTHTTP;

	r->content_type = "text/html";
	ap_send_http_header(r);
 

	//TODO
	//if the request is a GET request handle it
   
	//set up the read policy from the client.
	if ((rc = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)) != OK)
	{
		return rc;
	}


	//tell the client that we are ready to receive content and check whether client will send content
	//control will pass to this block only if there is body content in the request
	if (ap_should_client_block(r))
	{
		int rsize, len_read, rpos=0;
		long length = r->remaining;
		//set the byte count of the body content, in the axis soap data structure
		sstr->so.http.ip_soapcount=r->remaining;
		ap_hard_timeout("util_read", r);
		while ((len_read = ap_get_client_block(r, argsbuffer, sizeof(argsbuffer))) > 0)
		{    
			ap_reset_timeout(r);
			if ((rpos + len_read) > length)
			{
				rsize = length - rpos;
			}
			else 
			{
				rsize = len_read;
			}
		} 
		ap_kill_timeout(r);
	}

	//assign the body content, to the axis soap data structure
	sstr->so.http.ip_soap= argsbuffer;  

	//ap_table_elts returns an array_header struct. The nelts element of that struct contains the number of
	//input header elements. Finally assigns that to the axis soap data structure. 
	sstr->so.http.ip_headercount = ap_table_elts(r->headers_in)->nelts;  

	//casting r->headers_in to axis header struct and assigning that to the axis soap structure. Hope this is ok

	//obtain the array_header from the headers_in table and assign it to the axis soap structure
	array_header * arr = ap_table_elts(r->headers_in);
	sstr->so.http.ip_headers = (header *)arr->elts;

	//Determine the http method and assign it to the axis soap structure
	switch (r->method_number)
	{
	case M_GET:
      sstr->so.http.ip_method = GET;
      break;
	case M_POST:
      sstr->so.http.ip_method = POST;
      break;
	default:
      sstr->so.http.ip_method = UNSUPPORTED;   
	}
  
	if(0 == process(sstr))
	{
		 ap_rputs(sstr->so.http.op_soap, r);
		  //free(sstr->so.http.op_soap);      
	}
	else
	{
		ap_rputs("SOAP Engined failed to response",r);
	}
	free(sstr);
	return OK;
}
/* Make the name of the content handler known to Apache */
static handler_rec axis_handlers[] =
{
   {"axis", axis_handler},
   {NULL}
};
/* Tell Apache what phases of the transaction we handle */
module MODULE_VAR_EXPORT axis_module =
{
   STANDARD_MODULE_STUFF,
  NULL,               /* module initializer                 */
  NULL,               /* per-directory config creator       */
  NULL,               /* dir config merger                  */
  NULL,               /* server config creator              */
  NULL,               /* server config merger               */
  NULL,               /* command table                      */
  axis_handlers,     /* [9]  content handlers              */
  NULL,               /* [2]  URI-to-filename translation   */
  NULL,               /* [5]  check/validate user_id        */
  NULL,               /* [6]  check user_id is valid *here* */
  NULL,               /* [4]  check access by host address  */
  NULL,               /* [7]  MIME type checker/setter      */
  NULL,               /* [8]  fixups                        */
  NULL,               /* [10] logger                        */
  NULL,               /* [3]  header parser                 */
  NULL,               /* process initialization             */
  NULL,               /* process exit/cleanup               */
  NULL                /* [1]  post read_request handling    */
};
