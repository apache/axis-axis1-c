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
 */

/*
 * @author damitha Kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#include "OpenSSLChannel.hpp"

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

OpenSSLChannel::OpenSSLChannel()
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

OpenSSLChannel::~OpenSSLChannel()
{
}

bool OpenSSLChannel::SSLInit()
{
    return true;
}

bool OpenSSLChannel::openSSLConnection(unsigned int* pSock)
{
    SSL_METHOD* req_method = SSLv23_client_method();
    SSL_SESSION* ssl_sessionid = NULL;

    m_sslContext = SSL_CTX_new(req_method);

    if(!m_sslContext)
    {
        int sslerror = ERR_get_error();

        /* OpenSSL documents that this must be at least 120 bytes long. */
        char error_buffer[120];
        ERR_error_string(sslerror, error_buffer);
        closeSSLChannel();
        throw AxisSSLChannelException(CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR, error_buffer);
    }

    SSL_CTX_set_verify(m_sslContext, /*SSL_VERIFY_PEER*/SSL_VERIFY_NONE, 
        cert_verify_callback);


    /* Lets make an SSL structure */

    m_sslHandle = SSL_new(m_sslContext);
    SSL_set_connect_state(m_sslHandle);

    /* pass the raw socket into the SSL layers */
    SSL_set_fd(m_sslHandle, *pSock);

    int iError = SSL_connect(m_sslHandle);
    /*
     *   1  is fine
     *   0  is "not successful but was shut down controlled"
     *  <0  is "handshake was not successful, because a fatal error occurred"
     */
     if(iError <= 0)
         setSSLError(iError);

    return true;
}

int OpenSSLChannel::SSLRead(std::string& msg)
{
    int nByteRecv = 0;
    const int BUF_SIZE = 4096;
    char buf[BUF_SIZE];
    nByteRecv = SSL_read(m_sslHandle, buf, BUF_SIZE - 1);
    if(nByteRecv < 0)
    {
        char error_string[256];
        /* failed SSL_read */
        int iError = SSL_get_error(m_sslHandle, nByteRecv);
        setSSLError(iError);
        closeSSLChannel();
    }
    if(nByteRecv)
    {
       buf[nByteRecv] = '\0';  
       /* got a part of the message, so add it to form */
       msg = buf;
    }
    else
       printf("execution break\n");
    return true;
}

int OpenSSLChannel::SSLWrite(const std::string& msg, unsigned int* pSock)
{
    if(INVALID_SOCKET == *pSock)
    {
        throw AxisSSLChannelException(CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR,"");
    }
    int size = msg.size(), nByteSent;

    nByteSent = SSL_write(m_sslHandle, (char *)msg.c_str(), size);

    if(nByteSent < 0)
    {
        char error_string[256];
        int iError = SSL_get_error(m_sslHandle, nByteSent);
        setSSLError(iError);
        closeSSLChannel();
    }

    return true;
}

void OpenSSLChannel::setSSLError(char* pcError)
{
    strcpy(m_pcError, pcError);
}

void OpenSSLChannel::setSSLError(int iError)
{
    switch(iError)
    {
        case SSL_ERROR_NONE: /* this is not an error */
        case SSL_ERROR_ZERO_RETURN: /* no more data */
            break;
        case SSL_ERROR_WANT_READ:
        case SSL_ERROR_WANT_WRITE:
        case SSL_ERROR_SYSCALL:
        {
            #ifdef WIN32
                iError = ::GetLastError();
            #else
                iError =  errno;
            #endif

            closeSSLChannel();
            throw AxisSSLChannelException(CLIENT_SSLCHANNEL_ERROR, "SSL_ERROR_SYSCALL");

        }
        case SSL_ERROR_SSL:
        {
            /*  A failure in the SSL library occurred, usually a
                protocol error.  The OpenSSL error queue contains more
                information on the error. */
            int sslerror = ERR_get_error();

            /* OpenSSL documents that this must be at least 120 
             * bytes long.
             */
             char error_buffer[120];

             ERR_error_string(sslerror, error_buffer);
             closeSSLChannel();
             throw AxisSSLChannelException(CLIENT_SSLCHANNEL_ERROR, error_buffer);
        }
        default: 
        /* openssl/ssl.h says "look at error stack/return value/errno"*/
        {
           /*  A failure in the SSL library occurred, usually a
               protocol error.  The OpenSSL error queue contains more
               information on the error. */
            int sslerror = ERR_get_error();

           /* OpenSSL documents that this must be at least 120 bytes 
            * long. 
            */
            char error_buffer[120];

            ERR_error_string(sslerror, error_buffer);
            closeSSLChannel();
            throw AxisSSLChannelException(CLIENT_SSLCHANNEL_ERROR, error_buffer);

        }
    }
}

char* OpenSSLChannel::getSSLError()
{
    return m_pcError;    
}


/**
 *    Close, and clean-up any OS specific stuff
 *
 */

void OpenSSLChannel::closeSSLChannel()
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
}

