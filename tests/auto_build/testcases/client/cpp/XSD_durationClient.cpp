// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "XSD_duration.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/XSD_duration";

	if(argc>1)
		url = argv[1];

		// bool bSuccess = false;

	try
	{
		sprintf(endpoint, "%s", url);
		XSD_duration* ws = new XSD_duration(endpoint);

		// Test non-nillable element
	    xsd__duration result = ws->asNonNillableElement((xsd__duration)123456789);
		cout << "non-nillable element=" << result << endl;

		// Test nillable element, with a value
		xsd__duration* nillableInput = new xsd__duration();
		*(nillableInput) = (xsd__duration)123456789;
		xsd__duration* nillableResult = ws->asNillableElement(nillableInput);
		if (nillableResult)
		{
			cout << "nillable element=" << *(nillableResult) << endl;
			delete nillableResult;
		}
		else
		{
			cout << "nillable element=<nil>" << endl;
		}
       delete nillableInput;

		// Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
		if (nillableResult)
		{
			cout << "nil element=" << *(nillableResult) << endl;
			delete nillableResult;
		}
		else
		{
			cout << "nil element=<nil>" << endl;
		}

		// Test required attribute
		RequiredAttributeElement requiredAttributeInput;
		requiredAttributeInput.setrequiredAttribute(123456789);
		RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
		cout << "required attribute=" << requiredAttributeResult->getrequiredAttribute() << endl;
		delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
		// Test optional attribute, with a value
		OptionalAttributeElement optionalAttributeInput;
		optionalAttributeInput.setoptionalAttribute(123456789);
		OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
		if (optionalAttributeResult->getoptionalAttribute())
		{
			cout << "optional attribute, with data=" << *(optionalAttributeResult->getoptionalAttribute()) << endl;
		}
		else
		{
			cout << "optional attribute, with data=<not present>" << endl;
		}
		delete optionalAttributeResult;

		// Test optional attribute, not present
		optionalAttributeInput.setattribute();
		optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
		if (optionalAttributeResult->getoptionalAttribute())
		{
			cout << "optional attribute, not present=" << *(optionalAttributeResult->getoptionalAttribute()) << endl;
		}
		else
		{
			cout << "optional attribute, not present=<not present>" << endl;
		}
		delete optionalAttributeResult;
*/
		// Test array
        xsd__duration_Array arrayInput;
		int arraySize=2;
		xsd__duration ** array = new xsd__duration*[arraySize];        
        for (int inputIndex=0 ; inputIndex < 2 ; inputIndex++)
        {
            array[inputIndex] = new xsd__duration(123456789);
            
        }
		arrayInput.set(array,arraySize);
		xsd__duration_Array arrayResult = ws->asArray(arrayInput);
		int outputSize=0;
		const xsd__duration **output = arrayResult.get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
		for (int index = 0; index < outputSize; index++)
		{
			cout << "  element[" << index << "]=" << *((xsd__duration*)output[index]) << endl;
			
		}
      
		 // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;


		// Test complex type
		SimpleComplexType complexTypeInput;
		complexTypeInput.setcomplexTypeElement(123456789);
		SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
		cout << "within complex type=" << complexTypeResult->getcomplexTypeElement() << endl;
		delete complexTypeResult;

		// Tests now complete

		delete ws;
	}
	catch(AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured: " << e.what() << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}

	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}
