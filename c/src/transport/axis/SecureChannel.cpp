#include <iostream>
#include <errno.h>

#include <axis/client/transport/axis/Platform.hpp>
#include <axis/client/transport/axis/SecureChannel.hpp>
#include <axis/client/transport/axis/Transport.hpp>


using namespace std;

/* "global" init done? */
static bool g_InitSSL = false;

/* We have the "SSL is seeded" boolean global for the application to
   prevent multiple time-consuming seedings in vain */
static bool g_sslSeeded = false;

static
int cert_verify_callback(int ok, X509_STORE_CTX *ctx)
{
  X509 *err_cert;
  char buf[256];

  err_cert=X509_STORE_CTX_get_current_cert(ctx);
  X509_NAME_oneline(X509_get_subject_name(err_cert),buf,256);

  return ok;
}


/**
 * Create a SecureChannel & initialize
 *
 */

SecureChannel::SecureChannel() //: m_Sock(INVALID_SOCKET)
{
    if(!g_InitSSL)
    {
        /* Lets get nice error messages */
        SSL_load_error_strings();

        /* Setup all the global SSL stuff */
        SSLeay_add_ssl_algorithms();

        g_InitSSL = true;

    }

}

SecureChannel::~SecureChannel()
{
	CloseChannel();
}


/**
 * This channel open INET channel for the time being using primitive sockets
 * Do we need any other type of channel; like shared memory, pipes etc. ????
 *
 * @param	p_RemoteNode	End point address as hostname/IP
 * @param	p_RemoteEnd		Port #
 *
 * @return  true if successfuly open a soket to the endpoint. o/w exception is thrown
 */

bool SecureChannel::Open(std::string& p_RemoteNode, unsigned short p_RemoteEnd) throw (ChannelException)
{
	m_RemoteNode = p_RemoteNode;
	m_RemoteEnd  = p_RemoteEnd;

	if(!Init())
		throw ChannelException("Cannot initialize a channel to the remote end");

	sockaddr_in clAddr, svAddr;

	if ((m_Sock = socket(PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
	{
		clAddr.sin_family = AF_INET;     // AF_INET (address family Internet).
		clAddr.sin_port   = 0; 			 // No Specify Port required
		clAddr.sin_addr.s_addr = INADDR_ANY;

		if (bind(m_Sock, (struct sockaddr*) &clAddr, sizeof(clAddr)) == SOCKET_ERROR)
		{
			Error("Error - Binding");
			CloseChannel();
			throw ChannelException("Cannot open a channel to the remote end, shutting down the channel");
		}

		// Although the above fragment makes use of the bind() API, it would be
		// just as effective to skip over this call as there are no specific
		// local port ID requirements for this client. The only advantage that
		// bind() offers is the accessibility of the port which the system chose
		// via the .sin_port member of the cli_addr structure which will be set
		// upon success of the bind() call.

		svAddr.sin_family = AF_INET;
		svAddr.sin_port   = htons(m_RemoteEnd);

		struct hostent*  pHostEntry = NULL;

		// probably this is the host-name of the server we are connecting to
		if((pHostEntry = gethostbyname(m_RemoteNode.c_str())))
		{
			svAddr.sin_addr.s_addr = ((struct in_addr *)pHostEntry->h_addr)->s_addr;
		}
		else
		{
			// no this is the IP address
			svAddr.sin_addr.s_addr = inet_addr(m_RemoteNode.c_str());
		}

		// connect to the remote server.
		if (connect(m_Sock,(struct sockaddr*)&svAddr, sizeof(svAddr)) == SOCKET_ERROR)
		{
			Error("Sockets error: Couldn't connect socket.");
			CloseChannel();
			throw ChannelException("Cannot open a channel to the remote end, shutting down the channel");
		}
	}
	else
	{
		Error("Sockets error: Couldn't create socket.");
		CloseChannel();
		throw ChannelException("Cannot open a channel");
	}

    SSL_METHOD* req_method = SSLv23_client_method();
    SSL_SESSION* ssl_sessionid = NULL;

    m_sslContext = SSL_CTX_new(req_method);

    if(!m_sslContext) {
        int sslerror = ERR_get_error();

        /* OpenSSL documents that this must be at least 120 bytes long. */
        char error_buffer[120];

        ERR_error_string(sslerror, error_buffer);
        Error(error_buffer);

        Error("SSL: couldn't create a context!");
        CloseChannel();
		throw ChannelException("Cannot open a channel to the remote end, shutting down the channel");
    }

    SSL_CTX_set_verify(m_sslContext, /*SSL_VERIFY_PEER*/SSL_VERIFY_NONE, cert_verify_callback);


    /* Lets make an SSL structure */

    m_sslHandle = SSL_new(m_sslContext);
    SSL_set_connect_state(m_sslHandle);

    /* pass the raw socket into the SSL layers */
    SSL_set_fd(m_sslHandle, m_Sock);

    int err = SSL_connect(m_sslHandle);

    /*
     *   1  is fine
     *   0  is "not successful but was shut down controlled"
     *  <0  is "handshake was not successful, because a fatal error occurred"
     */


	return true;
}

/**
 * OS specific initialization should do here
 *
 * @return  true if successfuly initilaize OS specific stuffs. false o/w
 */

bool SecureChannel::Init()
{
#ifdef WIN32

	WSADATA wsaData;			// contains vendor-specific information, such as the
								// maximum number of sockets available and the maximum
								// datagram size.

	if(WSAStartup(WS_VERSION_REQD, &wsaData))  //Filled by Windows Sockets DLLs
	{
		m_LastErr = "WinSock DLL not responding.";
		Error((char *)m_LastErr.c_str());
		return false;
	}
	else
	{
		// Query to see whether the available version matches what we need
		if (( LOBYTE (wsaData.wVersion) < WS_VERSION_MAJOR()) ||
			 (LOBYTE (wsaData.wVersion) == WS_VERSION_MAJOR() &&
			  HIBYTE (wsaData.wVersion) < WS_VERSION_MINOR()))
		{
			char buf[100];
			sprintf(buf,"Windows Sockets version %d.%d not supported by winsock2.dll",
						LOBYTE (wsaData.wVersion), HIBYTE (wsaData.wVersion));
			Error(buf);
			CloseChannel();
			return false;
		}
	}
#else
    //cout << "no need for linux" << endl;
	// other OS specific Intitialization goes here
#endif

	return true;
}

/**
 * Write/send a message to the remote server; sending blocks the app.
 * we may need to do this asynchronizely; preferably either non-blocking
 * send or pthread.
 *
 * @param	Message to be written to the open channel
 */
const Channel& SecureChannel::operator << (const std::string& msg)
{
	if(INVALID_SOCKET == m_Sock)
	{
		Error("Writing cannot be done without having a open socket to remote end.");
		throw ChannelException("Output streaming error on undefined channel; please open the channel first");
	}

	int size = msg.size(), nByteSent;

    nByteSent = SSL_write(m_sslHandle, (char *)msg.c_str(), size);

    if(nByteSent < 0)
	{
        char error_string[256];

        int err = SSL_get_error(m_sslHandle, nByteSent);

        switch(err) {
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                /* The operation did not complete; the same TLS/SSL I/O function
                   should be called again later. This is basically an EWOULDBLOCK
                   equivalent. */
                return *this;

            case SSL_ERROR_SYSCALL:
            {
                #ifdef WIN32
                    err = ::GetLastError();
                #else
                    err =  errno;
                #endif

                sprintf(error_string, "SSL_write() returned SYSCALL, errno = %d\n", err);
                Error(error_string);
                CloseChannel();
	            throw ChannelException("Output streaming error on SecureChannel while writing data");

                return *this;
            }

            case SSL_ERROR_SSL:
            {
                /*  A failure in the SSL library occurred, usually a
                    protocol error.  The OpenSSL error queue contains more
                    information on the error. */
                int sslerror = ERR_get_error();

                /* OpenSSL documents that this must be at least 120 bytes long. */
                char error_buffer[120];

                sprintf(error_string, "SSL_write(): %s\n", ERR_error_string(sslerror, error_buffer));
                Error(error_string);
                CloseChannel();
		        throw ChannelException("Output streaming error on SecureChannel while writing data");

                return *this;
            }

            break;
        }

        /* a true error */
        sprintf(error_string, "Output streaming error: SSL_write() returned error %d\n", err);

		Error(error_string);
		CloseChannel();
		throw ChannelException("Output streaming error on SecureChannel while writing data");
	}

	return *this;
}

/**
 * Read/receive a message from the remote server; reading may be done in chunks.
 *
 * @param	string to hold the read Message
 */

const Channel& SecureChannel::operator >> (std::string& msg)
{
	if(INVALID_SOCKET == m_Sock)
	{
		Error("Reading cannot be done without having a open socket.");
		throw ChannelException("Input streaming error on undefined channel; please open the channel first");
	}

	int nByteRecv = 0;
	const int BUF_SIZE = 4096;
	char buf[BUF_SIZE];

	
        nByteRecv = SSL_read(m_sslHandle, buf, BUF_SIZE - 1);

        if(nByteRecv < 0) {
            char error_string[256];

            /* failed SSL_read */
            int err = SSL_get_error(m_sslHandle, nByteRecv);

            switch(err) {
                case SSL_ERROR_NONE: /* this is not an error */
                case SSL_ERROR_ZERO_RETURN: /* no more data */
                    break;
                case SSL_ERROR_WANT_READ:
                case SSL_ERROR_WANT_WRITE:
                    /* there's data pending, re-invoke SSL_read() */
                    return *this; /* basically EWOULDBLOCK */
                default: /* openssl/ssl.h says "look at error stack/return value/errno" */
                {
                    /*  A failure in the SSL library occurred, usually a
                    protocol error.  The OpenSSL error queue contains more
                    information on the error. */
                    int sslerror = ERR_get_error();

                    /* OpenSSL documents that this must be at least 120 bytes long. */
                    char error_buffer[120];

                    sprintf(error_string, "SSL_read(): %s\n", ERR_error_string(sslerror, error_buffer));
                    Error(error_string);
                    CloseChannel();
		            throw ChannelException("Input streaming error on SecureChannel while reading data");

                    return *this;
                }

            }

            /* a true error */
            sprintf(error_string, "Input streaming error: SSL_read() returned error %d\n", err);

		    Error(error_string);
		    CloseChannel();
		    throw ChannelException("Input streaming error on SecureChannel while reading data");
        }

		if(nByteRecv)
		{
			buf[nByteRecv] = '\0';  // got a part of the message, so add it to form
            msg = buf;
		}
		else
            printf("execution break\n");
    

    return *this;
}

/**
 *	Close, and clean-up any OS specific stuff
 *
 */

void SecureChannel::CloseChannel()
{
    if(m_sslHandle)
    {
        SSL_shutdown(m_sslHandle);
        SSL_set_connect_state(m_sslHandle);

        SSL_free(m_sslHandle);
        m_sslHandle = NULL;
    }

    if(m_sslContext)
    {
        SSL_CTX_free (m_sslContext);
        m_sslContext = NULL;
    }

#ifdef WIN32
	if(INVALID_SOCKET != m_Sock)
		closesocket(m_Sock);

	// Check for any possible error conditions from WSACleanup() and report
	// them before exiting, as this information might indicate a network
	// layer problem in the system.

	WSACleanup();
#else
	if(INVALID_SOCKET != m_Sock)
		close(m_Sock);

#endif
}

/**
 * Log any errors that cause on channel usage/initilaization
 *
 */

void SecureChannel::Error(const char * err)
{
#ifdef _DEBUG
	std::cerr << err << std::endl;
#endif
}