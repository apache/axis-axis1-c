#if !defined(_AXIS_AXIS_SSL_CHANNEL_HPP)
#define _AXIS_AXIS_SSL_CHANNEL_HPP

#include <stdio.h>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Platform specific stuff
#ifdef WIN32
#include "..\IChannel.hpp"
#include "..\URL.hpp"
#include "..\HTTPTransportException.hpp"
#include <winsock2.h>

#ifdef IPV6
#include <ws2tcpip.h>
#include <tpipv6.h>  // For IPv6 Tech Preview.
#endif

// What version of WinSock is required
const int    WS_VERSION_REQD    = 0x0101;

// Macros to get version major & minor
inline int WS_VERSION_MAJOR() {return HIBYTE(WS_VERSION_REQD);}
inline int WS_VERSION_MINOR() {return LOBYTE(WS_VERSION_REQD);}

#else
#include "../IChannel.hpp"
#include "../URL.hpp"
#include "../HTTPTransportException.hpp"

#include <unistd.h>
#include <sys/types.h>		// basic system data types
#include <sys/socket.h>		// basic socket definitions
#include <netinet/tcp.h>
#include <fcntl.h>			// for nonblocking if need
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// inet(3) functions

const unsigned int INVALID_SOCKET =  0;
const int          SOCKET_ERROR   = -1;

// Other OS specific stuff goes here
#endif

AXIS_CPP_NAMESPACE_USE using namespace std;

class HTTPSSLChannel:public IChannel
{
public:
	HTTPSSLChannel();
	virtual ~HTTPSSLChannel();

	const char *		getURL();
	virtual void		setURL( const char * cpURL);
    virtual URL &		getURLObject();
    bool				open() throw (HTTPTransportException&);
    const std::string &	GetLastErrorMsg();
    const IChannel &	operator >> (const char * msg);
    const IChannel &	operator << (const char * msg);
    void				setTimeout( const long lSeconds);
    void				setSocket( unsigned int uiNewSocket);
	bool				setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
	const char *		getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type);
    void				setProxy( const char * pcProxyHost, unsigned int uiProxyPort);

protected:
	bool				OpenChannel();
	void				CloseChannel();
	bool				StartSockets();
	void				StopSockets();
	int					applyTimeout();
	int					ReadFromSocket( const char * pszRxBuffer);
	int					WriteToSocket( const char * psTxBuffer, int iSize);
	void				OpenSSL_Initialise();
	bool				OpenSSL_Open();
	int					OpenSSL_Close();
	void				OpenSSL_SetSecureError( int iError);

private:
    URL				m_URL;				// URL
	string			m_LastError;		// Last error
    unsigned int	m_Sock;				// Socket descriptor
    bool			m_bUseProxy;		// Use a Proxy?
    string			m_strProxyHost;		// Proxy server name.
    unsigned int	m_uiProxyPort;		// Proxy server port.
    long			m_lTimeoutSeconds;	// Timeout in seconds
	SSL_CTX *		m_sslContext;
	SSL *			m_sslHandle;
};

#endif