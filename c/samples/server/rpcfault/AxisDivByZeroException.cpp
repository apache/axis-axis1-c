/*
 * This is the  implementation file genarated by WSDL2Ws tool.
 * AxisDivByZeroException.cpp: implemtation for the AxisDivByZeroException.
 *
 */

#include "AxisDivByZeroException.h"

#include <axis/server/AxisWrapperAPI.h>

AxisDivByZeroException::AxisDivByZeroException()
{
/* This only serves the pupose of indicating that the 
 * service has thrown an excpetion 
 */ 
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION; 
	processException(m_iExceptionCode); 
}

AxisDivByZeroException::AxisDivByZeroException(DivByZeroStruct*pFault)
{
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION;
	processException(pFault);}

AxisDivByZeroException::AxisDivByZeroException(int iExceptionCode)
{

	m_iExceptionCode = iExceptionCode;
	processException (iExceptionCode);
}

AxisDivByZeroException::AxisDivByZeroException(exception* e)
{
	processException (e);
}

AxisDivByZeroException::AxisDivByZeroException(exception* e,int iExceptionCode)
{

	processException (e, iExceptionCode);
}

AxisDivByZeroException::~AxisDivByZeroException() throw () 
{
	m_sMessage ="";
}

void AxisDivByZeroException:: processException(exception* e, int iExceptionCode)
{
	m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisDivByZeroException::processException (DivByZeroStruct* pFault)
{
	/*User can do something like deserializing the struct into a string*/}

void AxisDivByZeroException::processException(exception* e)
{
	m_sMessage = getMessage (e);
}

void AxisDivByZeroException::processException(int iExceptionCode)
{
	m_sMessage = getMessage (iExceptionCode);
}

const string AxisDivByZeroException::getMessage (exception* objException)
{
	string sMessage = objException->what();
	return sMessage;
}

const string AxisDivByZeroException::getMessage (int iExceptionCode)
{
	string sMessage;
	switch(iExceptionCode)
	{
		case AXISC_SERVICE_THROWN_EXCEPTION:
		sMessage = "A service has thrown an exception. see detail";
		break;
		default:
		sMessage = "Unknown Exception has occured";
	}
return sMessage;
}

const char* AxisDivByZeroException::what() throw ()
{
	return m_sMessage.c_str ();
}

const int AxisDivByZeroException::getExceptionCode(){
	return m_iExceptionCode;
}

