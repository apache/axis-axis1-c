/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains implementations of the ref Exception class of the web service.
 */

#include "ref_AxisClientException.h"

#include <axis/server/AxisWrapperAPI.hpp>

ref_AxisClientException::ref_AxisClientException()
{
/* This only serves the purpose of indicating that the 
 * service has thrown an excpetion 
 */ 
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION; 
	processException(m_iExceptionCode); 
}

ref_AxisClientException::ref_AxisClientException(ISoapFault* pFault)
{
	m_iExceptionCode = AXISC_SERVICE_THROWN_EXCEPTION;
	processException(pFault);}

ref_AxisClientException::ref_AxisClientException(int iExceptionCode)
{

	m_iExceptionCode = iExceptionCode;
	processException (iExceptionCode);
}

ref_AxisClientException::ref_AxisClientException(exception* e)
{
	processException (e);
}

ref_AxisClientException::ref_AxisClientException(exception* e,int iExceptionCode)
{

	processException (e, iExceptionCode);
}

ref_AxisClientException::~ref_AxisClientException() throw () 
{
	m_sMessage ="";
}

void ref_AxisClientException:: processException(exception* e, int iExceptionCode)
{
	m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void ref_AxisClientException::processException (ISoapFault* pFault)
{
	/*User can do something like deserializing the struct into a string*/
}

void ref_AxisClientException::processException(exception* e)
{
	m_sMessage = getMessage (e);
}

void ref_AxisClientException::processException(int iExceptionCode)
{
	m_sMessage = getMessage (iExceptionCode);
}

const string ref_AxisClientException::getMessage (exception* objException)
{
	string sMessage = objException->what();
	return sMessage;
}

const string ref_AxisClientException::getMessage (int iExceptionCode)
{
	string sMessage;
	switch(iExceptionCode)
	{
		case AXISC_SERVICE_THROWN_EXCEPTION:
		sMessage = "The ref service has thrown an exception. see details";
		break;
		default:
		sMessage = "Unknown Exception has occured in the ref service";
	}
return sMessage;
}

const char* ref_AxisClientException::what() throw ()
{
	return m_sMessage.c_str ();
}

const int ref_AxisClientException::getExceptionCode(){
	return m_iExceptionCode;
}

