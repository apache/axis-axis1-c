/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 *
 */

/*
 * Currently supports Windows only.
 */

#ifdef WIN32
#include <winsock.h>    /* for socket(),... */
#else //Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#endif

//#include <stdio.h>
#include <axis/server/Packet.h>
#include <axis/server/AxisConfig.h>
#include "../../common/AxisSocketUtils.h"
//#include <axis/server/AxisTrace.h>
#include "ServerHelper.h"
#include <axis/server/GDefine.h>

//extern AxisTrace* g_pAT;

#define MAXPENDING 5    /* Maximum outstanding connection requests */
#define RCVBUFSIZE 1000   /* Size of receive buffer */
#ifdef WIN32
#define AXIS_SOCKET_ERROR SOCKET_ERROR
#else //Linux
#define AXIS_SOCKET_ERROR 1
#endif

char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
const char *pcHttpBody;
int iClntSocket;
map<HTTP_MAP_KEYWORDS, HTTP_MAP_TYPE*> map_HTTP_Headers;
const int HEADER_ARRAY_SIZE = 10;
HttpHeaders g_pHttpHeaders[HEADER_ARRAY_SIZE];
int iHeaderCount = 0;
bool g_blnBodySizeAvailable = false;
int g_iBodySize =0;

#define AXIS_URI_EXTENSION "/axis"

/* Following is the character that should be used to separate the method name in the 
 * SOAPAction header value. Ex: "http://localhost:80/axis/Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

AXIS_TRANSPORT_STATUS AXISCALL send_response_bytes(const char* buffer, const void* bufferid, const void* pStream)
{
	/*
	 *TODO: 
	 * //--------------Change this, sending of transport related info has to be done in "set_transport_information" method.
	 */
	//AXISTRACE3("sending trasport info");	
	
	int iMsgSize = strlen(buffer);
	char pchContentLength[4];
	sprintf(pchContentLength, "%d", iMsgSize);

	char *res = (char*) malloc(iMsgSize + 200);
	res[0] = 0;
	strcpy(res, "HTTP/1.1 200 OK\nDate: Wed, 03 Sep 2003 09:23:06 GMT\nContent-Length: ");
	strcat(res, pchContentLength);
	strcat(res, "\nContent-Type: text/xml\r\n\r\n");
	//--------------END OF Change this, sending of transport related info has to be done in "set_transport_information" method.

	strcat(res, buffer);
	
	//AXISTRACE3(res);
	
	if (send(iClntSocket, res, strlen(res), 0) == AXIS_SOCKET_ERROR) {
		free(res);
		printf("%s\n","send() failed");	
		return TRANSPORT_FAILED;
	} else {
		free(res);
		return TRANSPORT_FINISHED;
	}

}

AXIS_TRANSPORT_STATUS AXISCALL get_request_bytes(const char** req, int* retsize, const void* stream)
{
	req[0]= '\0';

	*req = pcHttpBody;
	*retsize= strlen(pcHttpBody);

	return TRANSPORT_FINISHED;
}

void AXISCALL set_transport_information(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, const void* stream)
{
	//AXISTRACE3("sending trasport info.......");	
	
	char *res ="HTTP/1.1 200 OK\nContent-Type: text/xml; charset=utf-8\nDate: Wed, 03 Sep 2003 09:23:06 GMT\nConnection: close\n\n";
	//AXISTRACE3(res);

	int iMsgSize = strlen(res);

	if (send(iClntSocket, res, iMsgSize, 0) == AXIS_SOCKET_ERROR)
		printf("%s\n","send() failed");
}

const char* AXISCALL get_transport_information(AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pStream) 
{
	const Ax_soapstream* stream = (Ax_soapstream*) pStream;
	const char* ptemp;
	switch(type)
	{
	case SOAPACTION_HEADER:
		return get_property(stream, "SOAPAction");
		/* TODO */
		//return "abc";
		/*-------------------*/
	case SERVICE_URI:
		if (strstr(stream->so.http->uri_path, AXIS_URI_EXTENSION))
		{
			return strstr(stream->so.http->uri_path, AXIS_URI_EXTENSION) +
				strlen(AXIS_URI_EXTENSION) + 1;
		}
		else
		{
			return stream->so.http->uri_path;
		}
	case OPERATION_NAME:
		ptemp = get_property(stream, "SOAPAction");
		/* TODO */
		/*-------------------*/
		if (ptemp) 
		{
			if (strstr(ptemp, SOAPACTION_METHODNAME_SEPARATOR))
			{
				return strstr(ptemp, SOAPACTION_METHODNAME_SEPARATOR) +
					strlen(SOAPACTION_METHODNAME_SEPARATOR);
			}
			else
			{
				return ptemp;
			}
		}
	case SOAP_MESSAGE_LENGTH: 
		return get_property(stream, "Content-Length"); /*this is apache module and transport is http so the key*/
		/* TODO */
		return 0;
		/*-------------------*/
	default:;
	}
	return NULL;
}

void AXISCALL release_receive_buffer(const char* buffer, const void* stream)
{

}

int executeWork(Ax_soapstream* pStr) {

	Ax_soapstream* str = pStr;

	process_request(str);	

	//free(str->so.http->ip_headers);
	//free(str);

	return 0;
}

int initializeStuff() {

	for (int i=0; i<RCVBUFSIZE; i++) {
		echoBuffer[i] = '\0';
	}

	memset(&g_pHttpHeaders, 0, sizeof(HttpHeaders)*HEADER_ARRAY_SIZE);

	iHeaderCount=0;
	g_blnBodySizeAvailable = false;
	g_iBodySize =0;

	return AXIS_SUCCESS;
}

int releaseStuff() {
	
	/*
	 release the map_HTTP_Headers
	 */
	map<HTTP_MAP_KEYWORDS, HTTP_MAP_TYPE*>::iterator ite_map_HTTP_Headers = map_HTTP_Headers.begin();

	while (ite_map_HTTP_Headers!= map_HTTP_Headers.end()) {
		free (((*ite_map_HTTP_Headers).second)->objuHttpMapContent);
		free (((*ite_map_HTTP_Headers).second));

		ite_map_HTTP_Headers++;
	}

	map_HTTP_Headers.clear();

	/*
	 *release the g_pHttpHeaders
	 */
	for (int i=0; i<iHeaderCount; i++) {
		free(g_pHttpHeaders[i].header_name);
		free(g_pHttpHeaders[i].header_value);
	}

	return AXIS_SUCCESS;
}

int createTCPServerSocket(unsigned short port)
{
    int sock;                        /* socket to create */
    struct sockaddr_in echoServAddr; /* Local address */

    /* Create socket for incoming connections */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        printf("%s\n","socket() failed");
      
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(port);              /* Local port */

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        printf("%s\n","bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(sock, MAXPENDING) < 0)
        printf("%s\n","listen() failed");

    return sock;
}

int acceptTCPConnection(int servSock)
{
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoClntAddr; /* Client address */
	#ifdef WIN32    
		int clntLen;            /* Length of client address data structure */
	#else //Linux
		unsigned int clntLen;            /* Length of client address data structure */
	#endif

    /* Set the size of the in-out parameter */
    clntLen = sizeof(echoClntAddr);
    
    /* Wait for a client to connect */
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0) {
        printf("%s\n","accept() failed");		
		AxisSocketUtils::printSocketErrorDescription();
	}
    
    /* clntSock is connected to a client! */
	/*
	AXISTRACE3(strcat("Handling client ", inet_ntoa(echoClntAddr.sin_addr)));
	*/

    return clntSock;
}

int getHttpBodySize(string &sStream) {

	//AXISTRACE3("In the NEW CODE getHttpBodySize():-------------------\n");

	int iBodySize =0;
	bool blnContinue = true;
	string strTmpLine = "";
	int iTmpPos=0;
	bool blnFullHeaderAvailable = false;
	int iFindStartLocation =0;
	string sTmpStream = sStream;

	iTmpPos = sTmpStream.find("\r\n\r\n");
	if (iTmpPos != string::npos) {
		sTmpStream = sTmpStream.substr(iFindStartLocation, iTmpPos+2);
		blnFullHeaderAvailable = true;
	}

	iTmpPos = 0;

	while (blnContinue) {
		iTmpPos = sTmpStream.find("\n", iFindStartLocation);
		if ((iTmpPos==string::npos) && (blnFullHeaderAvailable)) {
			iBodySize = -1; //To indicate an error
			blnContinue = false;			
		} else if ((iTmpPos==string::npos) && (blnFullHeaderAvailable==false)) {
			blnContinue = false; //Not a error, but can't procede			
		} else {
			strTmpLine = sTmpStream.substr(iFindStartLocation, (iTmpPos-iFindStartLocation));			
			
			int iTmpLoc = strTmpLine.find("Content-Length");
			if (iTmpLoc != string::npos) {
				iTmpLoc = strTmpLine.find(":");
				string sTmpLen = strTmpLine.substr(iTmpLoc+1);
				iBodySize = atoi(sTmpLen.c_str());
				g_blnBodySizeAvailable = true;
				blnContinue = false;
				break;
			}

			iFindStartLocation = iTmpPos+1;
		}		
	}

	return iBodySize;
}

bool checkStreamIsFullyRead(string &sStream) {

	//AXISTRACE3("In the NEW CODE checkStreamIsFullyRead():-------------------\n");

	int iTmpPos=0;
	string strTmpBody = "";

	iTmpPos = sStream.find("\r\n\r\n");

	if (iTmpPos != string::npos) {
		iTmpPos+=4;
	}

	strTmpBody = sStream.substr(iTmpPos);

	if (strTmpBody.length() < g_iBodySize) {
		return false;
	} else {
		return true;
	}
}

void handleTCPClient(int clntSocket)
{
	Ax_soapstream* str = (Ax_soapstream*)malloc(sizeof(Ax_soapstream));

	/*populate Ax_soapstream struct with relevant transport function pointers*/
	str->transport.pSendFunct = send_response_bytes;
	str->transport.pGetFunct = get_request_bytes;
	str->transport.pSetTrtFunct = set_transport_information;
	str->transport.pGetTrtFunct = get_transport_information;
	str->transport.pRelBufFunct = release_receive_buffer;

	str->trtype = APTHTTP;
	str->so.http = (Ax_stream_http*)malloc(sizeof(Ax_stream_http));
	str->sessionid = "this is temporary session id";
	str->str.ip_stream = "";
	str->str.op_stream = "";

    int recvMsgSize;                    /* Size of received message */

    /* Receive message from client */
	
	string sClientReqStream;
	bool blnContinue = true;

	while (blnContinue) {
		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0) {
			printf("%s\n","recv() failed");
		} else {
			sClientReqStream+= echoBuffer;
			//AXISTRACE3("recd sClientReqStream:-------------------\n%s\n");
			//AXISTRACE3(sClientReqStream.c_str());
			
			if (g_blnBodySizeAvailable == false) {
				g_iBodySize = getHttpBodySize(sClientReqStream);
			}

			if (g_iBodySize > 0) {
				if (checkStreamIsFullyRead(sClientReqStream)) {
					blnContinue = false;
				}
			}
		}
	}

	string sHTTPHeaders = "";
	string sHTTPBody = "";

	getSeperatedHTTPParts(sClientReqStream, sHTTPHeaders, sHTTPBody, &map_HTTP_Headers, str, g_pHttpHeaders, HEADER_ARRAY_SIZE, &iHeaderCount);
	
	//AXISTRACE3("----------START extracted HTTP Headers------------");
	//AXISTRACE3(sHTTPHeaders.c_str());
	//AXISTRACE3("----------END extracted HTTP Headers--------------");

	//AXISTRACE3("----------START extracted HTTP Body---------------");
	//AXISTRACE3(sHTTPBody.c_str());
	//AXISTRACE3("----------END extracted HTTP Body-----------------");

	str->so.http->uri_path = strdup(map_HTTP_Headers[HMK_URI]->objuHttpMapContent->msValue);

	str->so.http->ip_headercount = iHeaderCount;  

	str->so.http->ip_headers = (Ax_header*)malloc(sizeof(Ax_header));
	str->so.http->ip_headers = (Ax_header*)(g_pHttpHeaders);

	switch (map_HTTP_Headers[HMK_METHOD]->objuHttpMapContent->eHTTP_KEYWORD)
	{
	case HK_GET:
      str->so.http->ip_method = AXIS_HTTP_GET;
      break;
	case HK_POST:
      str->so.http->ip_method = AXIS_HTTP_POST;
      break;
	default:
      str->so.http->ip_method = AXIS_HTTP_UNSUPPORTED;   
	}

	pcHttpBody = sHTTPBody.c_str();
	iClntSocket = clntSocket;

	executeWork(str);
	/* De-allocate the memory */
	free(str->so.http->ip_headers);
	free(str->so.http->uri_path);	
	free(str->so.http);
	free(str);

	releaseStuff();

	#ifdef WIN32
	closesocket(clntSocket);    /* Close client socket */
	#else //Linux
	close(clntSocket);
	#endif
}

int main(int argc, char *argv[ ])
{

	int *servSock;                   /* Socket descriptors for server */

	#ifdef WIN32
	WSADATA wsaData;                 /* Structure for WinSock setup communication */
	#else //Linux
	#endif

	fd_set sockSet;                  /* Set of socket descriptors for select() */
	int maxDescriptor;               /* Maximum socket descriptor value */
	struct timeval selTimeout;       /* Timeout for select() */
	long timeout= 1000;                    /* Timeout value given on command-line */
	int running = 1;
	int iServerPort;

	int iPort;
	int noPorts = 1;             /* Number of ports is argument count minus 2 */
	servSock = (int *) malloc(noPorts * sizeof(int));
	/* Initialize maxDescriptor for use by select() */
    maxDescriptor = -1;


	if (argc < 2) {
		printf("Problem occured.\nUsage: %s <Server Port>", argv[0]);	
		exit(1);
	}

	#ifdef WIN32
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}
	#else //Linux
	#endif

	/////////////
	iServerPort = atoi(argv[1]);
	if (iServerPort == 0) {
		printf("Problem occured. Error in specified server port");
		exit(1);
	} else {
		servSock[0] = createTCPServerSocket(iServerPort);
		/* Determine if new descriptor is the largest */
        if (servSock[0] > maxDescriptor) {
            maxDescriptor = servSock[0];
		}
	}
	///////////////

	//initializing Axis

	initialize_module(1);
	
	while (running) {
		FD_ZERO(&sockSet);
		FD_SET(servSock[0], &sockSet);	


		/* Timeout specification */
		/* This must be reset every time select() is called */
		selTimeout.tv_sec = timeout;       /* timeout (secs.) */
		selTimeout.tv_usec = 0;            /* 0 microseconds */

		if (select(maxDescriptor+1, &sockSet, NULL, NULL, &selTimeout) == 0) {
			/*
			DEBUG line
			printf("No echo requests for %ld secs...Server still alive\n", timeout);
			*/
		}
		else 
		{        
			if (FD_ISSET(servSock[0], &sockSet))
			{
				initializeStuff();
				/*
				DEBUG line
				printf("Request on port %d (cmd-line position):  \n", 0);
				*/
				handleTCPClient(acceptTCPConnection(servSock[0]));
			}
		}

		//AXISTRACE3("end of main while");
	}

	//uninitializing Axis
	uninitialize_module();

	/* Close sockets */
    for (iPort = 0; iPort < noPorts; iPort++) {
		#ifdef WIN32
		closesocket(servSock[iPort]);
		#else //Linux
		close(servSock[iPort]);			
		#endif
	}

    /* Free list of sockets */
    free(servSock);

	#ifdef WIN32
	WSACleanup();  /* Cleanup Winsock */
	#else //Linux
	#endif

	//AXISTRACE3("End of main");

	return 0;
}
