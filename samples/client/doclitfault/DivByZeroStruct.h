/*
 *This file is automatically generated by the Axis C++ Wrapper Class Generator
 *Web service wrapper class's implementation generated by Axis WCG
 *Parameters and wrapper methos to manipulate DivByZeroStruct
 */

#if !defined(__DIVBYZEROFAULT_PARAM_H__INCLUDED_)
#define __DIVBYZEROFAULT_PARAM_H__INCLUDED_

#include <axis/server/AxisUserAPI.h>

AXIS_CPP_NAMESPACE_USE

/*Local name and the URI for the type*/
static const char* Axis_URI_DivByZeroStruct = "http://localhost/axis/MathOps/types";
static const char* Axis_TypeName_DivByZeroStruct = "DivByZeroStruct";

class DivByZeroStruct
{
public:
	xsd__string varString;
	int varInt;
	float varFloat;
	DivByZeroStruct();
	virtual ~DivByZeroStruct();
        void setFaultcode();
        void setFaultstring();
        void setFaultDetail();
};

#endif /* !defined(__DIVBYZEROFAULT_PARAM_H__INCLUDED_)*/
