/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains an Exception class of the web service.
 */

#if !defined(__AXISDIVBYZEROEXCEPTION_EXCEPTION_H__INCLUDED_)
#define __AXISDIVBYZEROEXCEPTION_EXCEPTION_H__INCLUDED_

#include <string>
#include <exception>
#include <axis/server/AxisException.h>
#include "DivByZeroStruct.h"

using namespace std;
class AxisDivByZeroException: public AxisException
{
public:
	AxisDivByZeroException();
	AxisDivByZeroException(DivByZeroStruct* pFault);
	AxisDivByZeroException(int iExceptionCode);
	AxisDivByZeroException(exception* e);
	AxisDivByZeroException(exception* e, int iExceptionCode);
	virtual ~AxisDivByZeroException() throw();
	 const char* what() throw();
	 const int getExceptionCode();
	 const string getMessage(exception* e);
	 const string getMessage(int iExceptionCode);
private:
	 void processException(exception* e);
	 void processException(DivByZeroStruct* pFault);
	 void processException(exception* e, int iExceptionCode);
	 void processException(int iExceptionCode);
	 string m_sMessage;
	 int m_iExceptionCode;

};

#endif /* !defined(__AXISDIVBYZEROEXCEPTION_EXCEPTION_H__INCLUDED_)*/