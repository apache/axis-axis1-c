#include "../../common/MessageData.h"
#include "../../wsdd/WSDDHandler.h"
#include "../../wsdd/WSDDService.h"
#include "../../common/Handler.h"

#include <list>

class LogHandler : public Handler
{
public:
	LogHandler();
	virtual ~LogHandler();
  int Invoke(MessageData* pMsg);
  void OnFault(MessageData* pMsg);

  string GetOption(string sArg);
  void SetOption(string sOption, string Value);
  void SetOptionList(map<string, string>* OptionList);

protected:
  int m_iNumAccess;

};
