#pragma warning (disable : 4786)

#if !defined(__PACKET_H_INCLUDED__)
#define __PACKET_H_INCLUDED__

#include "../common/GDefine.h"

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
	char * ip_soap;
	long ip_soapcount;
	const char * op_soap;
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

#endif


