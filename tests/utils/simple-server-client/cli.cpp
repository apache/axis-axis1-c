#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string>

#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1){ perror(s); exit(1); }
const unsigned int INVALID_SOCKET = 0;
const int SOCKET_ERROR = -1;

int main ()
{
    int err;
    int sd;
    struct sockaddr_in sa;
    char* str;
    char buf [4096];
    char msg [8096];

    int message_size = 8192;

    // Message that comes on the wire. This could be a soap message or
    // mime or chunked data
    char msgLine[message_size];
    FILE* pFile;
    char filename[32];
    strcpy(filename, "cli_message.txt");
    // Open the file to read the message
    if ((pFile = fopen (filename, "r")) == NULL)
        return 1;
    char sLine[message_size];
    std::string message = msgLine;
    // Read the properly formatted soap message
    while(fgets (sLine, message_size, pFile) != NULL )
    {
        message += sLine;
        message.replace(message.length() -1 , 1, "\r\n");
    } 
    printf("message:%s\n", message.c_str());
    // -----------------------------------------------
    // Create a socket and connect to server using normal socket calls.
  
    sd = socket (AF_INET, SOCK_STREAM, 0);
    CHK_ERR(sd, "socket");
 
    memset (&sa, '\0', sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr ("127.0.0.1"); // Server IP
    sa.sin_port = htons (1111); // Server Port number
  
    err = connect(sd, (struct sockaddr*) &sa,
	sizeof(sa));
    CHK_ERR(err, "connect");
    
    // ---------------------------------------------------
    // DATA EXCHANGE - Send a message and receive a reply.

    if( (err = send( sd, message.c_str(), strlen(message.c_str()), MSG_DONTROUTE)) == SOCKET_ERROR)
    {
        printf( "<write  exception, error no:%d\n", err);
    }

    int nByteRecv = 0;
    int msg_size = 0;
    do
    {
        if( (nByteRecv = recv(sd, buf, sizeof(buf)-1, 0)) == SOCKET_ERROR)
        {
             printf( "Channel error while getting data\n");
        }
        if( nByteRecv)
        {
            // printf("nByteRecv:%d\n", nByteRecv);
            buf[nByteRecv] = '\0';
            strcpy(msg, buf); 
            msg_size += nByteRecv;
        }
        else
        {
            printf ("execution break\n");
        }
    }
    while(nByteRecv < 0);
    msg[msg_size] = '\0';
    printf ("Got %d chars:\n%s\n", msg_size, buf);

    // Clean up.

    //close (sd);

    return 0;
}
// EOF - cli.cpp
