/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains implementations of an Exception class of the web service.
 */

#include "AxisOutOfBoundException.h"

#include <axis/server/AxisWrapperAPI.h>

AxisOutOfBoundException::AxisOutOfBoundException()
{
/* This only serves the pupose of indicating that the 
 * service has thrown an excpetion 
 */ 
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION; 
	processException(m_iExceptionCode); 
}

AxisOutOfBoundException::AxisOutOfBoundException(OutOfBoundStruct*pFault)
{
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION;
	processException(pFault);}

AxisOutOfBoundException::AxisOutOfBoundException(int iExceptionCode)
{

	m_iExceptionCode = iExceptionCode;
	processException (iExceptionCode);
}

AxisOutOfBoundException::AxisOutOfBoundException(exception* e)
{
	processException (e);
}

AxisOutOfBoundException::AxisOutOfBoundException(exception* e,int iExceptionCode)
{

	processException (e, iExceptionCode);
}

AxisOutOfBoundException::~AxisOutOfBoundException() throw () 
{
	m_sMessage ="";
}

void AxisOutOfBoundException:: processException(exception* e, int iExceptionCode)
{
	m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisOutOfBoundException::processException (OutOfBoundStruct* pFault)
{
	/*User can do something like deserializing the struct into a string*/}

void AxisOutOfBoundException::processException(exception* e)
{
	m_sMessage = getMessage (e);
}

void AxisOutOfBoundException::processException(int iExceptionCode)
{
	m_sMessage = getMessage (iExceptionCode);
}

const string AxisOutOfBoundException::getMessage (exception* objException)
{
	string sMessage = objException->what();
	return sMessage;
}

const string AxisOutOfBoundException::getMessage (int iExceptionCode)
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

const char* AxisOutOfBoundException::what() throw ()
{
	return m_sMessage.c_str ();
}

const int AxisOutOfBoundException::getExceptionCode(){
	return m_iExceptionCode;
}
