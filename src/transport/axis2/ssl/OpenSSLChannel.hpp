#if !defined(_AXIS_OPENSSLCHANNEL_H)
#define _AXIS_OPENSSLCHANNEL_H
#include "../SecureChannel.hpp"
#include "AxisSSLChannelException.hpp"
#include <iostream>
using namespace std;

class OpenSSLChannel: public SecureChannel
{
public:
	OpenSSLChannel();
	~OpenSSLChannel();

	bool open() throw (AxisTransportException&);
	void close();

	const Channel& operator >> (std::string&) throw (AxisTransportException);
	const Channel& operator << (const char *) throw (AxisTransportException);

	bool setServerName( std::string) { return true;};
	string getServerName(){ return NULL;};

	void setSecureProperties( const char *){};
	const char * getSecureProperties(){ return NULL;};
        int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE
            type, const char* value){ return 0;};

private:
    bool openConnection(){ return true;};
    bool closeConnection(){ return true;};

    int openSecureSocket();
    int closeSecureSocket();

    bool writeSecureSocket(const char *);
    bool readSecureSocket( char *, int);

    void setSecureError(int iError);
    char* getSecureError();

protected:
	string sServerName;
};

#endif

