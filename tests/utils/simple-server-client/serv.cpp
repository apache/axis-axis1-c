#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

const unsigned int INVALID_SOCKET = 0;
const int SOCKET_ERROR = -1;

#define CHK_NULL(x) if ((x)==NULL) exit (1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }

int main ()
{
    int err;
    int listen_sd;
    int sd;
    struct sockaddr_in sa_serv;
    struct sockaddr_in sa_cli;
    size_t client_len;
    char* str;
    char buf [4096];
    int message_size = 8192;

    // Message that comes on the wire. This could be a soap message or
    // mime or chunked data
    char msgLine[message_size];
    FILE* pFile;
    char filename[32];
    strcpy(filename, "serv_message.txt");
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

    // Prepare TCP socket for receiving connections

    listen_sd = socket (AF_INET, SOCK_STREAM, 0);
    CHK_ERR(listen_sd, "socket");
  
    memset (&sa_serv, '\0', sizeof(sa_serv));
    sa_serv.sin_family = AF_INET;
    sa_serv.sin_addr.s_addr = INADDR_ANY;
    sa_serv.sin_port = htons (1111); // Server Port number
  
    err = bind(listen_sd, (struct sockaddr*) &sa_serv,
        sizeof (sa_serv));
    CHK_ERR(err, "bind");
	     
    // Receive a TCP connection.
	     
    err = listen (listen_sd, 5);
    CHK_ERR(err, "listen");
  
    client_len = sizeof(sa_cli);
    sd = accept (listen_sd, (struct sockaddr*) &sa_cli, &client_len);
    CHK_ERR(sd, "accept");
    close (listen_sd);

    printf ("Connection from %lx, port %x\n",
	  sa_cli.sin_addr.s_addr, sa_cli.sin_port);
  
    int nByteRecv = 0;
    int recv_msg_size = 0;
    char recv_msg[8096];
    do
    {
        if( (nByteRecv = recv( sd, buf, sizeof(buf)-1, 0)) == SOCKET_ERROR)
        {
            printf( "Channel error while getting data\n");
        }

        if( nByteRecv)
        {
            // printf("nByteRecv:%d\n", nByteRecv);
            buf[nByteRecv] = '\0';
            strcpy(recv_msg, buf);
            recv_msg_size += nByteRecv; 
        }
        else
        {
            printf ("execution break\n");
        }
     }
     while(nByteRecv < 0);

    // DATA EXCHANGE - Receive message and send reply.
    recv_msg[recv_msg_size] = '\0';
    printf ("Received message:\n%s\n", buf);
  
    if( (err = send( sd, message.c_str(), strlen(message.c_str()), MSG_DONTROUTE)) == SOCKET_ERROR)
    {
        printf( "<write  exception, error no:%d\n", err);
    }


    // Clean up.

    close (sd);

    return 0;
}
// EOF - serv.cpp
