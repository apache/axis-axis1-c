/*
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
*/

#include <apache/httpd.h>
#include <apache/http_config.h>
#include <apache/http_core.h>
#include <apache/http_log.h>
#include <apache/http_protocol.h>
#include <apache/http_main.h>
#include "../../common/Packet.h"
#include <string.h>
#include <malloc.h>

#define xxx   ap_log_rerror(APLOG_MARK,APLOG_ERR, globr,"logged here");
#define yyy ap_log_rerror(APLOG_MARK, APLOG_ERR, globr,"logged here");


/* file: mod_axis.c */
/* here's the content handler */

extern int process_request(soapstream *);
//extern int process(soapstream *);
extern unsigned char chEBuf[1024];

//global place holder for the current request_record
request_rec * globr;
//global variable to store the nubmer of bytes read from ap_get_client_block
int  len_read = 0;
//global variable to store the remaining number of bytes to be read from the http request content
int cont_length_remaining=0;

//Should dispatch the headers from within this method
int send_transport_information(soapstream * hdr)
{
      ap_send_http_header(globr);
	  return 0;
}

//Call initialize_module() [of Packet.h] from within this method
void module_init(server_rec *r, pool* p)
{}

int send_response_bytes(char * res)
{
  ap_rputs(res, globr);
  return 0;
}

//Cal initialize_process() [of Packet.h] from within this method
void  axis_Init(server_rec *r, pool* p)
{}
//Call finalize_process() [of Packet.h] from within this method
void axis_Fini(server_rec *r, pool* p)
{}

int get_request_bytes(char * req, int reqsize, int* retsize)
{

  if(cont_length_remaining>0)
  {
  ap_hard_timeout("util_read", globr);
  len_read = ap_get_client_block(globr, req, reqsize);

  ap_reset_timeout(globr);
  cont_length_remaining -= len_read;
  *retsize =  len_read;
  }
  else
  {
    *retsize = 0;
    }
 return 0;
}

static int axis_handler(request_rec *r) 
{

	int rc;
	char argsbuffer[HUGE_STRING_LEN];
	soapstream * sstr;
	array_header * arr;
    globr = r;
	memset(argsbuffer,0,HUGE_STRING_LEN);

	sstr = malloc(sizeof(soapstream));
	sstr->trtype=APTHTTP;
	r->content_type = "text/html";
	//set up the read policy from the client.
	if ((rc = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)) != OK)
	{
		return rc;
	}

	//ap_table_elts returns an array_header struct. The nelts element of that struct contains the number of
	//input header elements. Finally assigns that to the axis soap data structure. 
	sstr->so.http.ip_headercount = ap_table_elts(r->headers_in)->nelts;  

	//casting r->headers_in to axis header struct and assigning that to the axis soap structure. Hope this is ok

	//obtain the array_header from the headers_in table and assign it to the axis soap structure
	arr = ap_table_elts(r->headers_in);
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

  	//tell the client that we are ready to receive content and check whether client will send content
	//control will pass to this block only if there is body content in the request
    if (ap_should_client_block(globr));
    cont_length_remaining = r->remaining;

	if(0 != process_request(sstr))
	{
		ap_rputs("SOAP Engine failed to response",r);
		return OK;
	}


	free(sstr);
	//free(arr);
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
  module_init,               /* module initializer                 */
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
  axis_Init,               /* process initialization             */
  axis_Fini,               /* process exit/cleanup               */
  NULL                /* [1]  post read_request handling    */
};
