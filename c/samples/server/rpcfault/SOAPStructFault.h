/*
 *This file is automatically generated by the Axis C++ Wrapper Class Generator
 *Web service wrapper class's implementation generated by Axis WCG
 *Parameters and wrapper methos to manipulate SOAPStruct
 */

#if !defined(__SOAPSTRUCTFAULT_PARAM_H__OF_AXIS_INCLUDED_)
#define __SOAPSTRUCTFAULT_PARAM_H__OF_AXIS_INCLUDED_

#include <axis/server/AxisUserAPI.h>

/*Local name and the URI for the type*/
static const char* Axis_URI_SOAPStructFault = "http://localhost/axis/MathOps";
static const char* Axis_TypeName_SOAPStructFault = "DivByZeroFault";

class SOAPStructFault
{
public:
	xsd__string varString;
	int varInt;
	float varFloat;
	SOAPStructFault();
	virtual ~SOAPStructFault();
};

#endif /* !defined(__SOAPSTRUCTFAULT_PARAM_H__OF_AXIS_INCLUDED_)*/
