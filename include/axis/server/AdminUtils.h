
#if !defined(_ADMINUTILS_H____INCLUDED_)
#define _ADMINUTILS_H____INCLUDED_

#include <axis/server/IAdminUtils.h>

class AdminUtils : public IAdminUtils  
{
public:
	AdminUtils();
	virtual ~AdminUtils();
	int UpdateWSDD(AxisChar* wsdd);
};

#endif // !defined(ADMINUTILS_H____INCLUDED_)
