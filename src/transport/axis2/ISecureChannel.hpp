#if !defined(_AXIS_ISECURECHANNEL_HPP)
#define _AXIS_ISECURECHANNEL_HPP
#include <string>

using namespace std;

class ISecureChannel
{
public:
	virtual void			setSecureProperties( const char *)=0;
	virtual const char *	getSecureProperties()=0;
};

#endif

