#if !defined(_AXIS_SECURECHANNEL_H)
#define _AXIS_SECURECHANNEL_H
#include "ISecureChannel.hpp"
#include "SSLChannelFactory.hpp"
#include "../SSLChannel.hpp"
#include "Channel.h"
#include <iostream>
using namespace std;

class SecureChannel: public Channel, public ISecureChannel
{
public:
	SecureChannel();
	~SecureChannel();

	bool			open() throw (AxisTransportException&);
	void			close();

	const			Channel& operator >> (std::string&) throw (AxisTransportException);
	const			Channel& operator << (const char *) throw (AxisTransportException);

	bool			setServerName( std::string);
	string			getServerName();

	void			setSecureProperties( const char *);
	const char *	getSecureProperties();

private:
	bool	openConnection();
	bool	closeConnection();

	int		OpenSecureSocket();
	int		CloseSecuritySocket();

	bool	writeSecureSocket( char *);
	bool	readSecureSocket( char *, int);

protected:
	string	sServerName;
        SSLChannelFactory* m_pFactory;
        SSLChannel* m_pSSLChannel;
};

#endif

