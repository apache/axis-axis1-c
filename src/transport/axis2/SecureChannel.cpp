#include "SecureChannel.h"

SecureChannel::SecureChannel()
{
}

SecureChannel::~SecureChannel()
{
}

bool SecureChannel::open() throw (AxisTransportException&)
{
	return false;
}

void SecureChannel::close()
{
}

const Channel & SecureChannel::operator << (const char * msg) throw (AxisTransportException)
{
    return *this;
}

const Channel &SecureChannel::operator >> (std::string & msg) throw (AxisTransportException)
{
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
