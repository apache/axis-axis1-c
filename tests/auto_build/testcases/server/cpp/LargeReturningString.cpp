/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains definitions of the web service
 */

#include "LargeReturningString.hpp"


LargeReturningString::LargeReturningString()
{
}

LargeReturningString::~LargeReturningString()
{
}

/* This function is called by the AxisEngine when something went wrong
 with the current web service request processing. Appropriate actions should
 be taken here.*/
void LargeReturningString::onFault()
{
}

xsd__string LargeReturningString::getLargeString(xsd__int Value0)  
{
	xsd__string ret= new char[Value0 +1];
	char c = 'A';
	memset(ret, c, Value0);
	
	ret[Value0] = '\0';

	return ret;
}