#include <string>

using namespace std;

class ISecureChannel
{
public:
	virtual bool			setServerName( std::string)=0;
	virtual string			getServerName()=0;
	virtual void			setSecureProperties( const char *)=0;
	virtual const char *	getSecureProperties()=0;
};
