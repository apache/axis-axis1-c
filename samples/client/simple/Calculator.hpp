/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Client Stub Class for remote web service 
 */

#if !defined(__CALCULATOR_CLIENTSTUB_H__INCLUDED_)
#define __CALCULATOR_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Stub.hpp>
#include "Calculator_AxisClientException.hpp"
#include <axis/ISoapFault.hpp>

class Calculator :public Stub
{
public:
	STORAGE_CLASS_INFO Calculator(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP1_1);
	STORAGE_CLASS_INFO Calculator();
public:
	STORAGE_CLASS_INFO virtual ~Calculator();
public: 
	STORAGE_CLASS_INFO xsd__int add(xsd__int Value0,xsd__int Value1);
	STORAGE_CLASS_INFO xsd__int sub(xsd__int Value0,xsd__int Value1);
	STORAGE_CLASS_INFO xsd__int mul(xsd__int Value0,xsd__int Value1);
	STORAGE_CLASS_INFO xsd__int div(xsd__int Value0,xsd__int Value1);
	int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__CALCULATOR_CLIENTSTUB_H__INCLUDED_)*/