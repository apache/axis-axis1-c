#pragma warning (disable : 4786)

#if !defined(__PACKET_H_INCLUDED__)
#define __PACKET_H_INCLUDED__

#include "GDefine.h"

typedef struct 
{
	void* ip_stream;
	void* op_stream;
} Ax_iostream;
/*
typedef enum
{
	HTTP,
	SMTP
} transport_type;
*/
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
	char* uri_path;
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

typedef struct
{
	Ax_soapcontent so;
	Ax_iostream str;
	char* sessionid;
	AXIS_PROTOCOL_TYPE trtype;
} Ax_soapstream;

char* getheader(Ax_soapstream* soap, char* pchkey);


//This function is implemented in axis
//int initialize_process();


//This function is implemented in axis
//int finalize_process();

#ifdef __cplusplus
extern "C"
{
#endif
	//This function is implemented in axis
	int initialize_module();

	//This function is implemented in axis
	int process_request(Ax_soapstream* str);

	//This function should be implemented by module authors
	//Allows to send pieces of soap response the transport handler
	int send_response_bytes(const char* res, void* opstream);

	//This function should be implemented by module authors
	//Allows axis to get pieces of the request as they come to the transport listener
	int get_request_bytes(char* req, int reqsize, int* retsize, void* ipstream);

	//This fucntion should be implemented by module authors
	int send_transport_information(Ax_soapstream *str);
#ifdef __cplusplus
}
#endif

#endif


