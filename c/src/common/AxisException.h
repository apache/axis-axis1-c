#include <string>
#include <iostream>
#include <exception>
using namespace std;

#define AXIS_TEST_ERROR 1

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
    void processException(exception* e, int e);
    void processException(int e);
    string getMessage(exception* e);
    string getMessage(int e);    
    string m_sMessage;
};