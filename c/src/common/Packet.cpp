#include "Packet.h"
#include <string.h>

char* getheader(soapstream* soap, char* pchkey)
{
	header* hdrs = NULL;
	int count = 0;
	switch (soap->trtype)
	{
	case APTHTTP:
		hdrs = soap->so.http.ip_headers;
		count = soap->so.http.ip_headercount;
		break;
	case APTFTP:
		//TODO
		break;
	case APTSMTP:
		//TODO
		break;
	default:; //some error condition
	}

	for (int ix=0; ix<count; ix++)
	{
		header* hdr = hdrs + ix;
		if (strcmp(hdr->headername, SOAPACTIONHEADER) == 0)
		{
			return hdr->headervalue;
		}
	}
	return NULL;
}