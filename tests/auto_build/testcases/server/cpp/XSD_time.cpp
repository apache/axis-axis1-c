/*
 * Copyright 2003-2004 The Apache Software Foundation.

 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains definitions of the web service
 */

#include "XSD_time.hpp"


XSD_time::XSD_time()
{
}

XSD_time::~XSD_time()
{
}

/* This function is called by the AxisEngine when something went wrong
 with the current web service request processing. Appropriate actions should
 be taken here.*/
void XSD_time::onFault()
{
}
/* This function is called by the AxisEngine when this web service
 library is first loaded. So here we can initialize any global/static
 data structures of this web service or open database connections */
void XSD_time::init()
{
}
/* This function is called by the AxisEngine when this web service
 library is unloaded. So we can deallocate any global/static data structures
 and close database connections etc here. */
void XSD_time::fini()
{
}
xsd__time XSD_time::asNonNillableElement(xsd__time Value0)  
{
	return Value0;
}
xsd__time * XSD_time::asNillableElement(xsd__time * Value0)  
{
	return Value0;
}
RequiredAttributeElement* XSD_time::asRequiredAttribute(RequiredAttributeElement* Value0)  
{
	return Value0;
}
OptionalAttributeElement* XSD_time::asOptionalAttribute(OptionalAttributeElement* Value0)  
{
	return Value0;
}
xsd__time_Array XSD_time::asArray(xsd__time_Array Value0)  
{
	return Value0;
}
SimpleComplexType* XSD_time::asComplexType(SimpleComplexType* Value0)  
{
	return Value0;
}
