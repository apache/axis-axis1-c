#include "../common/MessageData.h"
#include "../wsdd/WSDDHandler.h"
#include "../wsdd/WSDDService.h"
#include "../common/BasicHandler.h"
#include <list>

class SimpleAuthorizationHandler : public BasicHandler, WSDDHandler
{
public:
	SimpleAuthorizationHandler();
	virtual ~SimpleAuthorizationHandler();

	virtual int Invoke(MessageData* pMsg) = 0;
	virtual void OnFault(MessageData* pMsg) = 0;

protected:
  string m_sAuthUser;
  list<string> m_AllowedRoles;
  list<string>::iterator m_itCurrentRole;
};
