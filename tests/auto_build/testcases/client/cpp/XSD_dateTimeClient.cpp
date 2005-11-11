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


#include "XSD_dateTime.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/XSD_dateTime";

	if(argc>1)
		url = argv[1];

		// bool bSuccess = false;

	try
	{
		sprintf(endpoint, "%s", url);
		XSD_dateTime* ws = new XSD_dateTime(endpoint);

        char returnString[50];
        
        time_t timeToTest = 1100246323;
        struct tm *temp = gmtime(&timeToTest);
        struct tm time;
        memcpy(&time, temp, sizeof(struct tm));

		// Test non-nillable element
	    xsd__dateTime result = ws->asNonNillableElement(time);
        strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", &result);
		cout << "non-nillable element=" << returnString << endl;

		// Test nillable element, with a value
		xsd__dateTime* nillableInput = new xsd__dateTime();
		*(nillableInput) = time;
		xsd__dateTime* nillableResult = ws->asNillableElement(nillableInput);
		if (nillableResult)
		{
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", nillableResult);
			cout << "nillable element=" << returnString << endl;
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
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", nillableResult);
			cout << "nil element=" << returnString << endl;
			delete nillableResult;
		}
		else
		{
			cout << "nil element=<nil>" << endl;
		}

		// Test required attribute
		RequiredAttributeElement requiredAttributeInput;
		requiredAttributeInput.setrequiredAttribute(time);
		RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        result = requiredAttributeResult->getrequiredAttribute();
		strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", &result);
        cout << "required attribute=" << returnString << endl;
		delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
		// Test optional attribute, with a value
		OptionalAttributeElement optionalAttributeInput;
		optionalAttributeInput.setoptionalAttribute(time);
		OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
		if (optionalAttributeResult->getoptionalAttribute())
		{
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", optionalAttributeResult->getoptionalAttribute());
			cout << "optional attribute, with data=" << returnString << endl;
		}
		else
		{
			cout << "optional attribute, with data=<not present>" << endl;
		}
		delete optionalAttributeResult;

		// Test optional attribute, not present
		//optionalAttributeInput.setattribute();
		optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
		if (optionalAttributeResult->getoptionalAttribute())
		{
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", optionalAttributeResult->getoptionalAttribute());
			cout << "optional attribute, not present=" << returnString << endl;
		}
		else
		{
			cout << "optional attribute, not present=<not present>" << endl;
		}
		delete optionalAttributeResult;
*/
		// Test array

        xsd__dateTime_Array arrayInput;
		int arraySize = 2;
		xsd__dateTime ** array = new xsd__dateTime*[arraySize];
        
        for (int inputIndex=0 ; inputIndex < arraySize ; inputIndex++)
        {
            array[inputIndex] =new xsd__dateTime(time);
            
        }
		arrayInput.set(array,arraySize);
        xsd__dateTime_Array* arrayResult = ws->asArray(&arrayInput);
		int outputSize = 0;
		const xsd__dateTime **output = arrayResult->get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (int index = 0; index < outputSize ; index++)
        {
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", output[index]);
            cout << "  element[" << index << "]=" << returnString << endl;
            
        }
         // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;


		// Test complex type
		SimpleComplexType complexTypeInput;
		complexTypeInput.setcomplexTypeElement(time);
		SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        result = complexTypeResult->getcomplexTypeElement();
        strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", &result);
		cout << "within complex type=" << returnString << endl;
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
