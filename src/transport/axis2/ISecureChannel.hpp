#if !defined(_AXIS_ISECURECHANNEL_HPP)
#define _AXIS_ISECURECHANNEL_HPP
#include <string>
#include <axis/GDefine.hpp>

using namespace std;
AXIS_CPP_NAMESPACE_USE

class ISecureChannel
{
public:
	virtual void			setSecureProperties( const char *)=0;
	virtual const char *	getSecureProperties()=0;
	virtual int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)=0;
};

#endif

