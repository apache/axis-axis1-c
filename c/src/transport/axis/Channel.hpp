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
 */

/*
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 *
 */

#if !defined(_AXIS_CHANNEL_HPP)
#define _AXIS_CHANNEL_HPP

#include <string>
#include "Transport.hpp"

// platform specific stuff

#ifdef WIN32

#include <winsock2.h>

// what version of WinSock is required
const int	WS_VERSION_REQD	= 0x0101;

// macros to get version major & minor
inline WS_VERSION_MAJOR() {return HIBYTE(WS_VERSION_REQD);}
inline WS_VERSION_MINOR() {return LOBYTE(WS_VERSION_REQD);}


#else

#include	<unistd.h>
#include	<sys/types.h>	// basic system data types 
#include	<sys/socket.h>	// basic socket definitions
#include	<fcntl.h>		// for nonblocking if need
#include	<netdb.h>
#include 	<netinet/in.h>
#include	<arpa/inet.h>	// inet(3) functions

const unsigned int INVALID_SOCKET =  0;
const int		   SOCKET_ERROR   = -1;

// Other OS specific stuff goes here



#endif


/**
 *
 * Implements primitive socket exceptions that should be handle by the transport
 * that the SOAP message is carring
 *	
 * @brief     The primitive socket exception for tranport layer to handle.
 *
 */

class ChannelException
{
	public:
		/// Create with a possible cause of the exception
		ChannelException(std::string p_Err){m_Error = p_Err;}
		~ChannelException(){}

		/// Return the cause of exception
		const std::string& GetErr(){return m_Error;}

	private:

		std::string m_Error;  ///< cause of exception 
};

/**
 * 
 * Implements primitive socket connection for all platforms, for sending/receiving
 * SOAP Envelops with given transport; This implementation abstract the low-level
 * communications.
 *	
 * @brief     The primitive socket implementation for SOAP Envelops passing.
 *
 */

class Channel  
{
public:
	Channel();
	virtual ~Channel();

	/// Open a socket to a given remote node/server address with remote port
	virtual bool  Open(std::string& p_RemoteNode, unsigned short p_RemoteEnd) throw (ChannelException);

	/// Close all open sockets and clean up
	virtual void  Close(){CloseChannel();}

	/// Read from a open socket and store read message in msg
	virtual const Channel& operator >> (std::string& msg);
	
	/// Write a given message (msg) to the end-point using the open socket
	virtual const Channel& operator << (const char* msg);
	
	/// Return last error (if any).
	virtual const std::string& GetLastError(){return m_LastErr;}

	/// Set the SOAP transport handler.
	virtual void SetTransportHandler(Transport* transport){m_pTransportHandler = transport;}

protected:
	/// OS specific initilization
	virtual bool Init();

	/// Report error on read/write
	virtual void Error(const char * err);

	/// Close & clean-up the open socket/system resources
	virtual void CloseChannel();

	unsigned int	m_Sock;				///< Socket descriptor
	std::string		m_RemoteNode;		///< Remote address could be IP/host-name
	unsigned short	m_RemoteEnd;		///< Remote port number
	std::string		m_LastErr;			///< Last error as a string

	Transport	* m_pTransportHandler;	///< Transport handler for validation purpose
};




#endif // _AXIS_CHANNEL_HPP


