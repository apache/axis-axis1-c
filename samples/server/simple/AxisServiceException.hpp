/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains an Exception class of the web service.
 */

#if !defined(__AXISSERVICEEXCEPTION_EXCEPTION_H__INCLUDED_)
#define __AXISSERVICEEXCEPTION_EXCEPTION_H__INCLUDED_

#include <string>
#include <exception>
#include <axis/AxisException.hpp>
#include <axis/ISoapFault.hpp>
using namespace std;
AXIS_CPP_NAMESPACE_USE 

class AxisServiceException: public AxisException
{
public:
	STORAGE_CLASS_INFO AxisServiceException();
	STORAGE_CLASS_INFO AxisServiceException(ISoapFault* pFault);
	STORAGE_CLASS_INFO AxisServiceException(int iExceptionCode);
	STORAGE_CLASS_INFO AxisServiceException(exception* e);
	STORAGE_CLASS_INFO AxisServiceException(exception* e, int iExceptionCode);
	STORAGE_CLASS_INFO AxisServiceException(string sMessage);
	STORAGE_CLASS_INFO virtual ~AxisServiceException() throw();
	STORAGE_CLASS_INFO const char* what() throw();
	STORAGE_CLASS_INFO const int getExceptionCode();
	STORAGE_CLASS_INFO const string getMessage(exception* e);
	STORAGE_CLASS_INFO const string getMessage(int iExceptionCode);
	STORAGE_CLASS_INFO const ISoapFault* getFault();

private:
	 void processException(exception* e);
	 void processException(ISoapFault* pFault);
	 void processException(exception* e, int iExceptionCode);
	 void processException(int iExceptionCode);
	 string m_sMessage;
	 int m_iExceptionCode;
	 ISoapFault* m_pISoapFault;

};

#endif /* !defined(__AXISSERVICEEXCEPTION_EXCEPTION_H__INCLUDED_)*/
