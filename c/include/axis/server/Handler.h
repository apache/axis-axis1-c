#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__HANDLER_INCLUDED__)
#define __HANDLER_INCLUDED__

#include "BasicHandler.h"
#include <map>
#include "AxisTrace.h"
using namespace std;

class Handler : public BasicHandler
{
public:
  Handler(){};
  virtual ~Handler(){};

  virtual const string& GetOption(const string& sArg)=0;
  virtual void SetOptionList(const map<string, string>* OptionList)=0;
  int GetType(){return NORMAL_HANDLER;};


protected:
  const map<string, string>* m_pOption;
};

#endif //__HANDLER_INCLUDED__
