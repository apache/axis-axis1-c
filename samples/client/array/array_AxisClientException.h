/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains an Exception class of the web service.
 */

#if !defined(__AXISCLIENTEXCEPTION_EXCEPTION_H__INCLUDED_)
#define __AXISCLIENTEXCEPTION_EXCEPTION_H__INCLUDED_

#include <string>
#include <exception>
#include <axis/AxisException.hpp>
#include <axis/ISoapFault.hpp>
using namespace std;
AXIS_CPP_NAMESPACE_USE 

class array_AxisClientException: public AxisException
{
public:
	array_AxisClientException();
	array_AxisClientException(ISoapFault* pFault);
	array_AxisClientException(int iExceptionCode);
	array_AxisClientException(exception* e);
	array_AxisClientException(exception* e, int iExceptionCode);
	virtual ~array_AxisClientException() throw();
	 const char* what() throw();
	 const int getExceptionCode();
	 const string getMessage(exception* e);
	 const string getMessage(int iExceptionCode);
private:
	 void processException(exception* e);
	 void processException(ISoapFault* pFault);
	 void processException(exception* e, int iExceptionCode);
	 void processException(int iExceptionCode);
	 string m_sMessage;
	 int m_iExceptionCode;

};

#endif /* !defined(__AXISCLIENTEXCEPTION_EXCEPTION_H__INCLUDED_)*/
