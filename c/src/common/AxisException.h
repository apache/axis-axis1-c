#include <string>
#include <iostream>
#include <exception>
using namespace std;

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