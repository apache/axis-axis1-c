#include <string>
#include <iostream>
#include <exception>
#include "../soap/SoapFaults.h"
using namespace std;

#define TEST_EXCEPTION FAULT_LAST+1


class AxisException :public exception
{

  public:
  AxisException(int exceptionCode);
  AxisException(exception* e);
  AxisException(exception* e, int exceptionCode);
  virtual ~AxisException() throw();
  const char* what() const throw();

  private:
    void processException(exception* e);
    void processException(exception* e, int exceptionCode);
    void processException(int e);
    string getMessage(exception* e);
    string getMessage(int e);    
    string m_sMessage;
};