#include "Packet.h"
#include <string.h>

#include <stdio.h>

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

	if(count==0 || hdrs==NULL)
	{
		return NULL;
	}

	for (int ix=0; ix<count; ix++)
	{
		//header* hdr = hdrs + ix;
		if (strcmp((hdrs+ix)->headername, SOAPACTIONHEADER) == 0)
		{
			return (hdrs+ix)->headervalue;
		}

	}
	return NULL;
}