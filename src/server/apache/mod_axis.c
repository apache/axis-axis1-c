#include <apache1_3/httpd.h>
#include <apache1_3/http_config.h>
#include <apache1_3/http_core.h>
#include <apache1_3/http_log.h>
#include <apache1_3/http_protocol.h>
#include <apache1_3/http_main.h>
#include "../../common/Packet.h"
#include <string.h>
#include <malloc.h>
/*
AxisConfig.h contains definitions for the wsdd file path
*/
#include "../../common/AxisConfig.h"

#define xxx ap_log_rerror(APLOG_MARK,APLOG_ERR, globr,"logged here");
#define yyy ap_log_rerror(APLOG_MARK, APLOG_ERR, globr,"logged here");

/* file: mod_axis.c */
/* here's the content handler */

extern int process_request(Ax_soapstream* str);
/*extern int process(soapstream *);*/
extern unsigned char chEBuf[1024];

/*Should dispatch the headers from within this method*/
int send_transport_information(Ax_soapstream* hdr)
{
      ap_send_http_header((request_rec*)hdr->str.op_stream);
	  return 0;
}

/*Call initialize_module() [of Packet.h] from within this method*/
void module_init(server_rec *svr_rec, pool* p)
{
	/*
	WSDDFILEPATH Defined in common/AxisConfig.h
	*/
	initialize_module(1, WSDDFILEPATH);
}

int send_response_bytes(const char* res, const void* opstream)
{
	ap_rputs(res, (request_rec*)opstream);
	return 0;
}

/*Call initialize_process() [of Packet.h] from within this method*/
void  axis_Init(server_rec *svr_rec, pool* p)
{}
/*Call finalize_process() [of Packet.h] from within this method*/
void axis_Fini(server_rec *svr_rec, pool* p)
{}

/**
 * This function is called by the Axis Engine whenever it needs to get bytes from the 
 * transport layer.
 */
int get_request_bytes(char* req, int reqsize, int* retsize, const void* ipstream)
{
	int len_read;
	ap_hard_timeout("util_read", (request_rec*)ipstream);
	len_read = ap_get_client_block((request_rec*)ipstream, req, reqsize);
	ap_reset_timeout((request_rec*)ipstream);
	*retsize =  len_read;
	return 0;
}

static int axis_handler(request_rec *req_rec) 
{
	int rc;
	Ax_soapstream* sstr;
	array_header* arr;

	sstr = malloc(sizeof(Ax_soapstream));
	/*populate Ax_soapstream struct with relevant transport function pointers*/
	sstr->transport.pSendFunct = send_response_bytes;
	sstr->transport.pGetFunct = get_request_bytes;
	sstr->transport.pSendTrtFunct = send_transport_information;
	sstr->transport.pGetTrtFunct = send_transport_information; /*isn't there a get transport information function for apache module ?*/
	sstr->trtype = APTHTTP;
	/*req_rec is used as both input and output streams*/
	sstr->str.ip_stream = req_rec;
	sstr->str.op_stream = req_rec;
	/*just add some sessionid*/
	sstr->sessionid = "this is temporary session id";

	req_rec->content_type = "text/xml"; /*for SOAP 1.2 this this should be "application/soap+xml" but keep this for the moment*/
	/*set up the read policy from the client.*/
	if ((rc = ap_setup_client_block(req_rec, REQUEST_CHUNKED_ERROR)) != OK)
	{
		return rc;
	}

	/*the member, "path" of "parsed_uri" contains the uri of the */
	/*request (i.e "/abc/xyz" part of http://somehost/abc/xyz)*/
	sstr->so.http.uri_path = req_rec->parsed_uri.path;

	/*ap_table_elts returns an array_header struct. The nelts element of that struct contains the number of*/
	/*input header elements. Finally assigns that to the axis soap data structure. */
	sstr->so.http.ip_headercount = ap_table_elts(req_rec->headers_in)->nelts;  

	/*casting req_rec->headers_in to axis header struct and assigning that to the axis soap structure. Hope this is ok*/

	/*obtain the array_header from the headers_in table and assign it to the axis soap structure*/
	arr = ap_table_elts(req_rec->headers_in);
	sstr->so.http.ip_headers = (Ax_header*)arr->elts;

	/*Determine the http method and assign it to the axis soap structure*/
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

  	/*tell the client that we are ready to receive content and check whether client will send content*/
	/*control will pass to this block only if there is body content in the request*/
    if (ap_should_client_block(req_rec));

	if(0 != process_request(sstr))
	{
		//ap_rputs("SOAP Engine failed to response",req_rec);
		return OK;
	}


	free(sstr);
	/*free(arr);*/
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
