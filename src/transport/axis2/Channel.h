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
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#if !defined(_AXIS_CHANNEL_HPP)
#define _AXIS_CHANNEL_HPP

#include <string>

#include "AxisTransportException.h"
#include "URL.h"

/* platform specific stuff */

#ifdef WIN32

#include <winsock2.h>

/* what version of WinSock is required */
const int    WS_VERSION_REQD    = 0x0101;

/* macros to get version major & minor */
inline WS_VERSION_MAJOR() {return HIBYTE(WS_VERSION_REQD);}
inline WS_VERSION_MINOR() {return LOBYTE(WS_VERSION_REQD);}


#else

#include    <unistd.h>
#include    <sys/types.h>    /* basic system data types  */
#include    <sys/socket.h>    /* basic socket definitions */
#include <netinet/tcp.h>
#include    <fcntl.h>        /* for nonblocking if need  */
#include  <sys/time.h>
#include    <netdb.h>
#include     <netinet/in.h>
#include    <arpa/inet.h>    /* inet(3) functions */

const unsigned int INVALID_SOCKET =  0;
const int           SOCKET_ERROR   = -1;
/* ther OS specific stuff goes here */



#endif

const int BUF_SIZE = 1024 * 8;

/*
 * 
 * Implements primitive socket connection for all platforms, for 
 * sending/receiving SOAP Envelops with given transport; This implementation
 * abstract the low-level communications.
 *    
 * @brief     The primitive socket implementation for SOAP Envelops passing.
 *
 */

class Channel  
{
public:
    Channel();
    virtual ~Channel();
    
    virtual void setURL(const char* cpURL);
    virtual void setURL(URL sURL)
	{
		m_URL = sURL;
	};
    
    const char* getURL(); 
    
    URL& getURLObject() { return m_URL; };

    /* Open a socket to a given remote node/server address with remote port */
    virtual bool  open() throw (AxisTransportException&);

    /* Close all open sockets and clean up */
    virtual void  close(){closeChannel();}

    /* Read from a open socket and store read message in msg */
    virtual const Channel& operator >> (std::string& msg);
    
    /* Read from socket in non bloking more in msg */
    virtual const Channel& readNonBlocking(std::string& msg, bool bBlockingRequired);

    /* Write a given message (msg) to the end-point using the open socket */
    virtual const Channel& operator << (const char* msg);
    
    /* Return last error (if any). */
    virtual const std::string& GetLastError(){return m_LastErr;}

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout(const long lSeconds);
    
    // This is used by SimpleAxisServer
    void setSocket(unsigned int uiNewSocket);
	virtual void setMsgLength( int iMsgLength)
	{
		m_iMsgLength = iMsgLength;
	}
	virtual int getMsgLength()
	{
		return m_iMsgLength;
	}
	virtual char * getMsg()
	{
		return m_sMsg;
	}

protected:
    /* OS specific initilization */
    virtual bool Init();

    /* Report error on read/write */
    virtual void Error(const char * err);

    /* Close & clean-up the open socket/system resources */
    virtual void closeChannel();

	virtual void hexOutput( char * psData, int iDataLength);

  /**
    * @return 0 if timeout, 1 if input available, -1 if error.
    */
    int applyTimeout();

    unsigned int   m_Sock;        /* Socket descriptor */
    URL m_URL;
    std::string    m_LastErr;     /* Last error as a string */
	int				m_iMsgLength;	// Only used for Secure
	char *			m_sMsg;			// Only used for Secure

  /**
    * Timeout in seconds
    */
    long m_lTimeoutSeconds;

};

#endif

