#pragma warning (disable : 4786)

#if !defined(__PACKET_H_INCLUDED__)
#define __PACKET_H_INCLUDED__

#include "GDefine.h"

typedef struct 
{
	unsigned char* ip_soap;
	unsigned char* op_soap;
	char* service;
	int byte_count;
} stream;
/*
typedef enum
{
	HTTP,
	SMTP
} transport_type;
*/
typedef enum
{
	GET,
	POST,
	UNSUPPORTED
} http_method;

typedef struct
{
	char * headername;
	char * headervalue;
} header;

typedef struct
{
	header * ip_headers;
	int ip_headercount;
	header * op_headers;
	int op_headercount;
	http_method ip_method;
	http_method op_method;
} stream_http;

typedef struct
{
	int dummy;  
} stream_smtp;

typedef union
{
	stream_http http;
	stream_smtp smtp;
} soapcontent;

typedef struct
{
	soapcontent so;
	AXIS_PROTOCOL_TYPE trtype;
} soapstream;

char* getheader(soapstream* soap, char* pchkey);

//This function is implemented in axis
//int initialize_module();

//This function is implemented in axis
//int initialize_process();


//This function is implemented in axis
//int finalize_process();

#ifdef __cplusplus
extern "C"
{
  //This function should be implemented by module authors
  //Allows to send pieces of soap response the transport handler
  int send_response_bytes(char * res);

  //This function should be implemented by module authors
  //Allows axis to get pieces of the request as they come to the transport listener
  int get_request_bytes(char * req, int reqsize, int* retsize);

  //This fucntion should be implemented by module authors
  int send_transport_information(soapstream *);
}

#else
  int send_response_bytes(char * res);

  int get_request_bytes(char * req, int reqsize, int* retsize);

  int send_transport_information(soapstream *);
#endif

#endif


