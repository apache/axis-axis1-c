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
#include "../../common/Packet.h"
#include "../../common/AxisConfig.h"
#include "ServerHelper.h"

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

int executeWork() {

	Ax_soapstream* str = (Ax_soapstream*)malloc(sizeof(Ax_soapstream));
	str->trtype = APTHTTP;
	str->sessionid = "somesessionid";
	str->so.http.ip_method = AXIS_HTTP_POST;
	str->str.ip_stream = "is";
	str->str.op_stream = "os";
	str->so.http.ip_headers = (Ax_header*)malloc(sizeof(Ax_header));
//	str->so.http.ip_headers->headername = SOAPACTIONHEADER;
//	str->so.http.ip_headers->headervalue = "\"Calculator\"";	
	str->so.http.ip_headercount = 0;
	str->so.http.uri_path = "http://someurl/axis/Calculator";

	//DEBUG line
	//printf("soap request :\n %s\n", echoBuffer);
//	wprintf(L"soap request :\n %s\n", ip);

	initialize_module(1, WSDDFILEPATH);
	
	process_request(str);	
	
	uninitialize_module();
	free(str->so.http.ip_headers);
	free(str);

	return 0;
}

int send_response_bytes(const char * res, const void* opstream) 
{	
	//printf("calling send_response_bytes");
	//printf("%s", res);

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
	//printf("sending trasport info");	
	
	char *res ="HTTP/1.1 200 OK\nContent-Type: text/xml; charset=utf-8\nDate: Wed, 03 Sep 2003 09:23:06 GMT\nConnection: close\n\n";

	//printf(res);

	int iMsgSize = strlen(res);

	if (send(iClntSocket, res, iMsgSize, 0) == AXIS_SOCKET_ERROR)
		printf("%s\n","send() failed");

	return 0;
}

void printError() {

	#ifdef WIN32
		int iError = WSAGetLastError();		

		if (iError == WSANOTINITIALISED) {
			printf("%s\n", "WSANOTINITIALISED");
		} else if (iError == WSAENETDOWN) {
			printf("%s\n", "WSAENETDOWN");
		} else if (iError == WSAEFAULT) {
			printf("%s\n", "WSAEFAULT");
		} else if (iError == WSAEINTR) {
			printf("%s\n", "WSAEINTR");
		} else if (iError == WSAEINPROGRESS) {
			printf("%s\n", "WSAEINPROGRESS");
		} else if (iError == WSAEINVAL) {
			printf("%s\n", "WSAEINVAL");
		} else if (iError == WSAEMFILE) {
			printf("%s\n", "WSAEMFILE");
		} else if (iError == WSAENOBUFS) {
			printf("%s\n", "WSAENOBUFS");
		} else if (iError == WSAENOTSOCK) {
			printf("%s\n", "WSAENOTSOCK");
		} else if (iError == WSAEOPNOTSUPP) {
			printf("%s\n", "WSAEOPNOTSUPP");
		} else if (iError == WSAEWOULDBLOCK) {
			printf("%s\n", "WSAEWOULDBLOCK");
		} 
	#else //Linux
	#endif
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
		printError();
	}
    
    /* clntSock is connected to a client! */
    
	//Debug line
    //printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

    return clntSock;
}

void handleTCPClient(int clntSocket)
{
    int recvMsgSize;                    /* Size of received message */
	echoBuffer[0] = '\0';

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        printf("%s\n","recv() failed");

	//DEBUG info
	//printf("----------START request stream of client------------\n");
	//printf("%s\n\n", echoBuffer);	
	//printf("----------END request stream of client------------\n");

	string sClientReqStream = string(echoBuffer);

	string sHTTPHeaders = "";
	string sHTTPBody = "";

	getSeperatedHTTPParts(sClientReqStream, sHTTPHeaders, sHTTPBody);
	
	//DEBUG info
	//printf("----------START extracted HTTP Headers------------\n");
	//cout<<sHTTPHeaders<<endl;
	//printf("----------END extracted HTTP Headers------------\n");

	//DEBUG info
	//printf("----------START extracted HTTP Body------------\n");
	//cout<<sHTTPBody<<endl;
	//printf("----------END extracted HTTP Body------------\n");

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

	while (running) {
		FD_ZERO(&sockSet);
		FD_SET(servSock[0], &sockSet);	


		/* Timeout specification */
		/* This must be reset every time select() is called */
		selTimeout.tv_sec = timeout;       /* timeout (secs.) */
		selTimeout.tv_usec = 0;            /* 0 microseconds */

		if (select(maxDescriptor+1, &sockSet, NULL, NULL, &selTimeout) == 0)
			printf("No echo requests for %ld secs...Server still alive\n", timeout);
		else 
		{        
			if (FD_ISSET(servSock[0], &sockSet))
			{
				//DEBUG line
				//printf("Request on port %d (cmd-line position):  \n", 0);
				handleTCPClient(acceptTCPConnection(servSock[0]));				
			}
		}

		//DEBUG info
		//printf("end of main while\n");
	}

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

	printf("End of main\n");

	return 0;
}
