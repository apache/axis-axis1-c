#if !defined(__HANDLER_INCLUDED__)
#define __HANDLER_INCLUDED__

#include "BasicHandler.h"
#include <map>
using namespace std;

class Handler : public BasicHandler
{
public:
  Handler(){};
	virtual ~Handler(){};
  virtual string GetOption(string sArg)=0;
  virtual void SetOption(string sOption, string Value)=0;
  virtual void SetOptionList(map<string, string>* OptionList)=0;

protected:
map<string, string>* m_Option;
};

#endif //__HANDLER_INCLUDED__
