#include "../common/MessageData.h"
#include "../wsdd/WSDDHandler.h"
#include "../wsdd/WSDDService.h"
#include "../common/BasicHandler.h"
#include <list>

class LogHandler : public BasicHandler, WSDDHandler
{
public:
	LogHandler();
	virtual ~LogHandler();

	int Invoke(MessageData* pMsg);
	void OnFault(MessageData* pMsg);
  
};
