#if !defined(_AXIS_SECURECHANNEL_H)
#define _AXIS_SECURECHANNEL_H
#include "ISecureChannel.hpp"
//#include "ChannelFactory.hpp"
//#include "../SSLChannel.hpp"
#include "Channel.h"
#include <iostream>
using namespace std;

class SecureChannel: public Channel, public ISecureChannel
{
public:
	SecureChannel();
	virtual ~SecureChannel();

	virtual bool open() throw (AxisTransportException&);
	virtual void close();

	virtual const Channel& operator >> (std::string&) throw (AxisTransportException);
	virtual const Channel& operator << (const char *) throw (AxisTransportException);

	bool setServerName( std::string);
	string getServerName();

	virtual void setSecureProperties( const char *);
	virtual const char * getSecureProperties();
        virtual int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE
            type, const char* value);

private:
    bool openConnection();
    bool closeConnection();

    virtual int openSecureSocket(){ return 0;};
    virtual int closeSecureSocket(){ return 0;};

    virtual bool writeSecureSocket(const char *){return true;};
    virtual bool readSecureSocket( char *, int){return true;};

    virtual void setSecureError(int iError){};
    virtual char* getSecureError(){ return NULL;};

protected:
	string sServerName;
        //SecureChannel* m_pSecureChannel;
};

#endif

