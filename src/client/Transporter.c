#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include "../common/Packet.h"

char * resp = "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><SOAP-ENV:Body><ns1:AddResponse xmlns:ns1=\"http://www.opensource.lk/CPPService\"><AddReturn xsi:type=\"xsd:int\">7</AddReturn></ns1:AddResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>";
int len = 354;

//char * resp = "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><SOAP-ENV:Body><ns1:AddPointResponse xmlns:ns1=\"http://www.opensource.lk/CPPService\"><Point xsi:type=\"ns3:Point xmlns:ns3=\"http://www.opensource.lk/Point\"><x xsi:type=\"xsd:int\">33</x><y xsi:type=\"xsd:int\">44</y></Point></ns1:AddResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>";
//int len = 450;


int send_response_bytes(const char* res, const void* opstream)
{
	printf("%s", res);
	return 0;
}

int get_request_bytes(char* req, int reqsize, int* retsize, const void* ipstream)
{
	printf("%s","inside get request bytes");
	strcpy(req, resp);
	*retsize = 354;
	return 0;
}

int send_transport_information(Ax_soapstream *str)
{
	printf("%s", "Sending transport info");
	return 0;
}

int receive_transport_information(Ax_soapstream *str)
{
	return 0;
}

