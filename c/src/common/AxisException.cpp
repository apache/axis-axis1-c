#include "AxisException.h"

AxisException::AxisException(int exceptionCode)
{
  processException(exceptionCode);
}

AxisException::AxisException(exception* e)
{
  processException(e);
}

AxisException::AxisException(exception* e, int exceptionCode)
{
  processException(e);
}

void AxisException::processException(exception* e, int exceptionCode)
{
  m_sMessage = getMessage(e) + getMessage(exceptionCode);
}

void AxisException::processException(exception* e)
{
  m_sMessage = getMessage(e);
}

void AxisException::processException(int exceptionCode)
{
  m_sMessage = getMessage(exceptionCode);
}

string AxisException::getMessage(exception* e)
{
  string sMessage;
  exception *objType = dynamic_cast<bad_alloc*> (e);
  if(objType != NULL)
  {
    //cout << "bad_alloc" << endl;
    sMessage = "thrown by new";
  }

  objType = dynamic_cast<bad_cast*> (e);
  if(objType != NULL)
  {
    //cout << "bad_cast" << endl;
    sMessage = "thrown by dynamic_cast when fails with a referenced type";
  }

  objType = dynamic_cast<bad_exception*> (e);
  if(objType != NULL)
  {
    //cout << "bad_exception" << endl;
    sMessage = "thrown when an exception doesn't match any catch";
  }

  objType = dynamic_cast<bad_typeid*> (e);
  if(objType != NULL)
  {
    //cout << "bad_typeid" << endl;
    sMessage = "thrown by typeid";
  }

   return sMessage;
}

string AxisException::getMessage(int e)
{
  string sMessage;
  if(e == 1)
  sMessage = "AXIS_TEST_ERROR";
  //cout <<  "AXIS_TEST_ERROR" << endl;

  return sMessage;

}

AxisException::~AxisException() throw()
{

}

const char* AxisException::what() const throw()
{
  return m_sMessage.c_str();
}

