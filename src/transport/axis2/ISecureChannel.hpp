#include <string>

using namespace std;

class ISecureChannel
{
public:
	virtual void			setSecureProperties( const char *)=0;
	virtual const char *	getSecureProperties()=0;
};
