#include "HTTPChannel.hpp"


HTTPChannel::HTTPChannel()
{
	memset( &m_URL, 0, sizeof( URL));

	m_LastError = "No Errors";
}

HTTPChannel::~HTTPChannel()
{
}

const char * HTTPChannel::getURL()
{
// Return the URL currently assicated with the channel object.
    return m_URL.getURL();
}

void HTTPChannel::setURL( const char * cpURL)
{
// Set the Channel URL to the new value.
    m_URL.setURL( cpURL);
}

URL & HTTPChannel::getURLObject()
{
    return m_URL;
}

bool HTTPChannel::open() throw (HTTPTransportException&)
{
	bool	bSuccess = false;

	return bSuccess;
}

const std::string & HTTPChannel::GetLastErrorMsg()
{
	return m_LastError;
}

const IChannel & HTTPChannel::operator >> (std::string& msg)
{
	return *this;
}

const IChannel & HTTPChannel::operator << (const char* msg)
{
	return *this;
}

void HTTPChannel::setTimeout( const long lSeconds)
{
}

void HTTPChannel::setSocket( unsigned int uiNewSocket)
{
}

bool HTTPChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
	bool	bSuccess = false;

	return bSuccess;
}

const char * HTTPChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
{
	return NULL;
}

