#include "HTTPSSLChannel.hpp"


HTTPSSLChannel::HTTPSSLChannel()
{
	memset( &m_URL, 0, sizeof( URL));

	m_LastError = "No Errors";
}

HTTPSSLChannel::~HTTPSSLChannel()
{
}

const char * HTTPSSLChannel::getURL()
{
// Return the URL currently assicated with the channel object.
    return m_URL.getURL();
}

void HTTPSSLChannel::setURL( const char * cpURL)
{
// Set the Channel URL to the new value.
    m_URL.setURL( cpURL);
}

URL & HTTPSSLChannel::getURLObject()
{
    return m_URL;
}

bool HTTPSSLChannel::open() throw (HTTPTransportException&)
{
	bool	bSuccess = false;

	return bSuccess;
}

const std::string & HTTPSSLChannel::GetLastErrorMsg()
{
	return m_LastError;
}

const IChannel & HTTPSSLChannel::operator >> (std::string& msg)
{
	return *this;
}

const IChannel & HTTPSSLChannel::operator << (const char* msg)
{
	return *this;
}

void HTTPSSLChannel::setTimeout( const long lSeconds)
{
}

void HTTPSSLChannel::setSocket( unsigned int uiNewSocket)
{
}

bool HTTPSSLChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
	bool	bSuccess = false;

	return bSuccess;
}

const char * HTTPSSLChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
{
	return NULL;
}

