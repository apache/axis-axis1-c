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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
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
#include <axis/common/Packet.h>
#include <axis/common/AxisConfig.h>
#include <axis/common/AxisSocketUtils.h>
#include <axis/common/AxisTrace.h>
#include <axis/server/simple_axis_server/ServerHelper.h>

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

int send_response_bytes(const char * res, const void* opstream) 
{	
	AXISTRACE3("calling send_response_bytes");
	AXISTRACE3(res);

	int iMsgSize = strlen(res);
	
	if (send(iClntSocket, res, iMsgSize, 0) == AXIS_SOCKET_ERROR)
		printf("%s\n","send() failed");	

	return 0;
}

int get_request_bytes(char * req, int reqsize, int* retsize, const void* ipstream) 
{
	req[0]= '\0';
	strcat(req, pcHttpBody);
	*retsize= strlen(pcHttpBody);
//	*retsize = wcslen(ip)*2;
//	memcpy(req, ip, *retsize);
	return 0;
}

int send_transport_information(Ax_soapstream* sSoapstream) 
{
	AXISTRACE3("sending trasport info");	
	
	char *res ="HTTP/1.1 200 OK\nContent-Type: text/xml; charset=utf-8\nDate: Wed, 03 Sep 2003 09:23:06 GMT\nConnection: close\n\n";
	AXISTRACE3(res);

	int iMsgSize = strlen(res);

	if (send(iClntSocket, res, iMsgSize, 0) == AXIS_SOCKET_ERROR)
		printf("%s\n","send() failed");

	return 0;
}

int receive_transport_information(Ax_soapstream *str) {

	return 0;
}

int executeWork() {

	Ax_soapstream* str = (Ax_soapstream*)malloc(sizeof(Ax_soapstream));
	str->trtype = APTHTTP;
	str->sessionid = "somesessionid";
	str->so.http.ip_method = AXIS_HTTP_POST;
	str->str.ip_stream = "is";
	str->str.op_stream = "os";
	str->so.http.ip_headers = (Ax_header*)malloc(sizeof(Ax_header));
	//str->so.http.ip_headers->headername = SOAPACTIONHEADER;
	//str->so.http.ip_headers->headervalue = "\"Calculator\"";	
	str->so.http.ip_headercount = 0;

	char pchURIValue[100] = {0};
	strcat(pchURIValue, "http://someurl");
		
	if (map_HTTP_Headers.find(HMK_URI) != map_HTTP_Headers.end()) {
		const char* pChTemp = map_HTTP_Headers[HMK_URI]->objuHttpMapContent->msValue;
		strcat(pchURIValue, pChTemp);
	}

	str->so.http.uri_path = pchURIValue;

	//set transport
	str->transport.pSendFunct = send_response_bytes;
	str->transport.pGetFunct = get_request_bytes;
	str->transport.pSendTrtFunct = (AXIS_SEND_TRANSPORT_INFORMATION)send_transport_information;
	str->transport.pGetTrtFunct = (AXIS_GET_TRANSPORT_INFORMATION)receive_transport_information;

	process_request(str);	

	free(str->so.http.ip_headers);
	free(str);

	return 0;
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

void handleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
	echoBuffer[0] = '\0';

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        printf("%s\n","recv() failed");

	AXISTRACE3("----------START request stream of client------------");
	AXISTRACE3(strcat(echoBuffer,"\n"));	
	AXISTRACE3("----------END request stream of client--------------");

	/*
	while (recvMsgSize>0) {
		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 64)) < 0)
			printf("%s\n","recv() failed");

		AXISTRACE3(strcat(echoBuffer,"\n"));	
		AXISTRACE3(recvMsgSize);
	}	
	*/

	string sClientReqStream = echoBuffer;

	string sHTTPHeaders = "";
	string sHTTPBody = "";

	getSeperatedHTTPParts(sClientReqStream, sHTTPHeaders, sHTTPBody, &map_HTTP_Headers);
	
	AXISTRACE3("----------START extracted HTTP Headers------------");
	AXISTRACE3(sHTTPHeaders.c_str());
	AXISTRACE3("----------END extracted HTTP Headers--------------");

	AXISTRACE3("----------START extracted HTTP Body---------------");
	AXISTRACE3(sHTTPBody.c_str());
	AXISTRACE3("----------END extracted HTTP Body-----------------");

	pcHttpBody = sHTTPBody.c_str();
	iClntSocket = clntSocket;

	executeWork();		

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
				/*
				DEBUG line
				printf("Request on port %d (cmd-line position):  \n", 0);
				*/
				handleTCPClient(acceptTCPConnection(servSock[0]));
			}
		}

		AXISTRACE3("end of main while");
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

	AXISTRACE3("End of main");

	return 0;
}
