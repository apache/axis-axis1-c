
#if !defined(_ADMINUTILS_H____OF_AXIS_INCLUDED_)
#define _ADMINUTILS_H____OF_AXIS_INCLUDED_

#include <axis/server/IAdminUtils.h>

class AdminUtils : public IAdminUtils  
{
public:
	AdminUtils();
	virtual ~AdminUtils();
	int updateWSDD(AxisChar* wsdd);
};

#endif // !defined(ADMINUTILS_H____OF_AXIS_INCLUDED_)
