/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */


#ifdef WIN32
#include <winsock2.h>		// for socket(),... 
#else //Linux
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#endif

//#include <axis/server/GDefine.hpp>
//#include <axis/Axis.hpp>
//#include "../../common/AxisConfig.h"
//#include "../../common/AxisSocketUtils.h"
#include "SimpleAxisTransport.h"

extern int process_request (SOAPTransport * str);


#define MAXPENDING 5		// Maximum outstanding connection requests 
#ifdef WIN32
#define AXIS_SOCKET_ERROR SOCKET_ERROR
#else //Linux
#define AXIS_SOCKET_ERROR 1
#endif

#define AXIS_URI_EXTENSION "/axis"

/* Following is the character that should be used to separate the method name 
 * in the SOAPAction header value. Ex: "http://localhost:80/axis/Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

int
createTCPServerSocket (unsigned short port)
{
    int sock;			/* socket to create */
    struct sockaddr_in echoServAddr;	/* Local address */

    /* Create socket for incoming connections */
    if ((sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	printf ("%s\n", "socket() failed");

    /* Construct local address structure */
    memset (&echoServAddr, 0, sizeof (echoServAddr));	/* Zero out structure */
    echoServAddr.sin_family = AF_INET;	/* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl (INADDR_ANY);	/* Any incoming interface */
    echoServAddr.sin_port = htons (port);	/* Local port */

    /* Bind to the local address */
    if (bind (sock, (struct sockaddr *) &echoServAddr,
	      sizeof (echoServAddr)) < 0)
	printf ("%s\n", "bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen (sock, MAXPENDING) < 0)
	printf ("%s\n", "listen() failed");

    return sock;
}

int
acceptTCPConnection (int servSock)
{
    int clntSock;		/* Socket descriptor for client */
    struct sockaddr_in echoClntAddr;	/* Client address */
#if defined WIN32
    int clntLen;		/* Length of client address data structure */
#elif defined AIX
	unsigned long clntLen;	/* Length of client address data structure */
#else //Linux
    unsigned int clntLen;	/* Length of client address data structure */
#endif

    /* Set the size of the in-out parameter */
    clntLen = sizeof (echoClntAddr);

    /* Wait for a client to connect */
    if ((clntSock = accept (servSock, (struct sockaddr *) &echoClntAddr,
			    &clntLen)) < 0)
    {
	printf ("%s\n", "accept() failed");
	//AxisSocketUtils::printSocketErrorDescription ();
    }

    /* clntSock is connected to a client! */
    /*
     * AXISTRACE3(strcat("Handling client ", inet_ntoa(echoClntAddr.sin_addr)));
     */

    return clntSock;
}

void
handleTCPClient (int clntSocket)
{
    SimpleAxisTransport *pTransport = new SimpleAxisTransport (clntSocket);

    if (0 != process_request (pTransport))
    {
	printf ("process_request FAILED\n");
    }
    delete pTransport;

}

int
main (int argc, char *argv[])
{

    int *servSock;		/* Socket descriptors for server */

#ifdef WIN32
    WSADATA wsaData;		/* Structure for WinSock setup communication */
#else //Linux
#endif

    fd_set sockSet;		/* Set of socket descriptors for select() */
    int maxDescriptor;		/* Maximum socket descriptor value */
    struct timeval selTimeout;	/* Timeout for select() */
    long timeout = 1000;	/* Timeout value given on command-line */
    int running = 1;
    int iServerPort;

    int iPort;
    int noPorts = 1;		/* Number of ports is argument count minus 2 */
    servSock = new int[noPorts];
    /* Initialize maxDescriptor for use by select() */
    maxDescriptor = -1;


    if (argc < 2)
    {
	printf ("Problem occured.\nUsage: %s <Server Port>", argv[0]);
	exit (1);
    }

#ifdef WIN32
    if (WSAStartup (MAKEWORD (2, 0), &wsaData) != 0)	/* Load Winsock 2.0 DLL */
    {
	fprintf (stderr, "WSAStartup() failed");
	exit (1);
    }
#else //Linux
#endif

    /////////////
    iServerPort = atoi (argv[1]);
    if (iServerPort == 0)
    {
	printf ("Problem occured. Error in specified server port");
	exit (1);
    }
    else
    {
	servSock[0] = createTCPServerSocket (iServerPort);
	/* Determine if new descriptor is the largest */
	if (servSock[0] > maxDescriptor)
	{
	    maxDescriptor = servSock[0];
	}
    }
    ///////////////

    //initializing Axis

    initialize_module (1);

    while (running)
    {
	FD_ZERO (&sockSet);
	FD_SET (servSock[0], &sockSet);


	/* Timeout specification */
	/* This must be reset every time select() is called */
	selTimeout.tv_sec = timeout;	/* timeout (secs.) */
	selTimeout.tv_usec = 0;	/* 0 microseconds */

	if (select (maxDescriptor + 1, &sockSet, NULL, NULL, &selTimeout) ==
	    0)
	{
	    /*
	     * DEBUG line
	     * printf("No echo requests for %ld secs...Server still alive\n", 
	     * timeout);
	     */
	}
	else
	{
	    if (FD_ISSET (servSock[0], &sockSet))
	    {
		//initializeStuff ();
		/*
		 * DEBUG line
		 * printf("Request on port %d (cmd-line position):  \n", 0);
		 */
		handleTCPClient (acceptTCPConnection (servSock[0]));
	    }
	}

	// AXISTRACE3("end of main while");
    }

    //uninitializing Axis
    uninitialize_module ();

    /* Close sockets */
    for (iPort = 0; iPort < noPorts; iPort++)
    {
#ifdef WIN32
	closesocket (servSock[iPort]);
#else //Linux
	close (servSock[iPort]);
#endif
    }

    /* Free list of sockets */
    delete [] servSock;

#ifdef WIN32
    WSACleanup ();		/* Cleanup Winsock */
#else //Linux
#endif

    //AXISTRACE3("End of main");

    return 0;
}
