#include "SecureChannel.h"
#include "SSLChannelFactory.hpp"

SecureChannel::SecureChannel()
{
    m_pFactory = new SSLChannelFactory();
    m_pFactory->initialize();
    m_pSSLChannel = m_pFactory->getSSLChannelObject(); 
    m_pSSLChannel->SSLInit();
}

SecureChannel::~SecureChannel()
{
}

bool SecureChannel::open() throw (AxisTransportException&)
{
    Channel::open();
    m_pSSLChannel->openSSLConnection(&m_Sock); 
    return true;
}

void SecureChannel::close()
{
}

const Channel & SecureChannel::operator << (const char * msg) throw (AxisTransportException)
{
    m_pSSLChannel->SSLWrite(msg, &m_Sock);
    return *this;
}

const Channel &SecureChannel::operator >> (std::string & msg) throw (AxisTransportException)
{
    m_pSSLChannel->SSLRead(msg);
    return *this;
}

void SecureChannel::setSecureProperties( const char * psSSLArgs)
{
	string * ps = (string *) psSSLArgs;
}

const char * SecureChannel::getSecureProperties()
{
	const char * pSSLProperty = "SecureProperty";

	return pSSLProperty;
}
