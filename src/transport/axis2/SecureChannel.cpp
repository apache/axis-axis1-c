#include "SecureChannel.h"

#define RXBUFFERLENGTH	16 * 4096

//////////////////////////////
// Public Overriden methods //
//////////////////////////////

SecureChannel::SecureChannel()
{
}

SecureChannel::~SecureChannel()
{
}

bool SecureChannel::open() throw (AxisTransportException)
{
	bool	bOpen = false;

	if( m_Sock == INVALID_SOCKET)
	{
		setServerName( this->getURLObject().getHostName());

		bOpen = openConnection();
	}
	else
	{
		bOpen = true;
	}

	return bOpen;
}

void SecureChannel::close()
{
	if( m_Sock != INVALID_SOCKET)
	{
		closeConnection();

		m_Sock = INVALID_SOCKET;
	}
	else
	{
	}
}

const Channel & SecureChannel::operator << (const char * msg) throw (AxisTransportException)
{
	writeSecureSocket( (char *) msg);

    return *this;
}

const Channel &SecureChannel::operator >> (std::string & msg) throw (AxisTransportException)
{
	char *	pszMsg = new char[RXBUFFERLENGTH];

	readSecureSocket( pszMsg, RXBUFFERLENGTH);

	msg = pszMsg;

	delete pszMsg;

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

///////////////////////////////
// Private interface methods //
///////////////////////////////

bool SecureChannel::openConnection()
{
	bool	bSuccess = false;

	return bSuccess;
}

bool SecureChannel::closeConnection()
{
	bool	bSuccess = false;

	if( CloseSecuritySocket() == 0)
	{
		bSuccess = true;
	}

	return bSuccess;
}

int SecureChannel::OpenSecureSocket()
{
	int	iRetCode = 0;

	if( Channel::open())
	{
		iRetCode = 1;
	}

	return iRetCode;
}

bool SecureChannel::writeSecureSocket( char * pszTxDataBuffer)
{
	bool	bSucess = false;

	return bSucess;
}

bool SecureChannel::readSecureSocket( char * pszRxDataBuffer, int iRxDataBufferSize)
{
	bool	bSucess = false;

	return bSucess;
}

int SecureChannel::CloseSecuritySocket()
{
	int	iRetCode = 0;

	Channel::closeChannel();

	return iRetCode;
}

string SecureChannel::getServerName()
{
	return sServerName;
}

bool SecureChannel::setServerName( string newServerName)
{
	bool	bSuccess = false;

	if( newServerName.length() > 0)
	{
		sServerName = newServerName;

		bSuccess = true;
	}
	
	return bSuccess;
}
