#if !defined(_AXIS_AXIS_CHANNEL_HPP)
#define _AXIS_AXIS_CHANNEL_HPP

#include "..\IChannel.hpp"
#include "..\URL.hpp"

AXIS_CPP_NAMESPACE_USE using namespace std;

class HTTPChannel:public IChannel
{
public:
	HTTPChannel();
	virtual ~HTTPChannel();

	const char *		getURL();
	virtual void		setURL( const char * cpURL);
    virtual URL &		getURLObject();
    bool				open() throw (HTTPTransportException&);
    const std::string &	GetLastErrorMsg();
    const IChannel &	operator >> (std::string& msg);
    const IChannel &	operator << (const char* msg);
    void				setTimeout( const long lSeconds);
    void				setSocket( unsigned int uiNewSocket);
	bool				setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
	const char *		getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type);

private:
    URL		m_URL;
	string	m_LastError;

};

#endif