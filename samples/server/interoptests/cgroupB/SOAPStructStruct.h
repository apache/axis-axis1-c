/*
 *This file is automatically generated by the Axis C++ Wrapper Class Generator
 *Web service wrapper class's implementation generated by Axis WCG
 *Parameters and wrapper methos to manipulate SOAPStructStruct
 */

#if !defined(__SOAPSTRUCTSTRUCT_H__OF_AXIS_INCLUDED_)
#define __SOAPSTRUCTSTRUCT_H__OF_AXIS_INCLUDED_

#include <axis/server/AxisUserAPI.h>

#include "SOAPStruct.h"
/*Local name and the URI for the type*/
static const char* Axis_URI_SOAPStructStruct = "http://soapinterop.org/xsd";
static const char* Axis_TypeName_SOAPStructStruct = "SOAPStructStruct";

typedef struct {
	xsd__string varString;
	int varInt;
	float varFloat;
	SOAPStruct * varStruct;
} SOAPStructStruct;

#endif /* !defined(__SOAPSTRUCTSTRUCT_H__OF_AXIS_INCLUDED_)*/