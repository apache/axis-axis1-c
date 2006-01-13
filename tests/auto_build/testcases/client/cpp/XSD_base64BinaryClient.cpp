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


#include "XSD_base64Binary.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"


int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/XSD_base64Binary";

	if(argc>1)
		url = argv[1];

		// bool bSuccess = false;

	try
	{
		sprintf(endpoint, "%s", url);
		XSD_base64Binary* ws = new XSD_base64Binary(endpoint);

        xsd__base64Binary input;

        xsd__unsignedByte* testUB = (xsd__unsignedByte*)stringToAscii("<test><xml>some dod&y string</xml></test>");

        input.set(testUB, 41);

		// Test non-nillable element
	    xsd__base64Binary result = ws->asNonNillableElement(input);
        int size = 0;
        const xsd__unsignedByte * resultData = result.get(size);
		cout << "non-nillable element" << endl;
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)resultData, size) << endl;

		// Test nillable element, with a value
		xsd__base64Binary* nillableInput = new xsd__base64Binary();
		*(nillableInput) = input;
		xsd__base64Binary* nillableResult = ws->asNillableElement(nillableInput);
		if (nillableResult)
		{
			cout << "nillable element" << endl;
            size = 0;
            const xsd__unsignedByte * data = nillableResult->get(size);
            cout << " size=" << size << endl;
            cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;
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
            cout << "nillable element" << endl;
            size = 0;
            const xsd__unsignedByte * data = nillableResult->get(size);
            cout << " size=" << size << endl;
            cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;
            delete nillableResult;
        }
		else
		{
			cout << "nil element=<nil>" << endl;
		}

		// Test array
        xsd__base64Binary_Array arrayInput;
		int arraySize=2;
        xsd__base64Binary **array = new xsd__base64Binary*[arraySize];       
        for (int inputIndex=0 ; inputIndex < 2 ; inputIndex++)
        {
            array[inputIndex] =new xsd__base64Binary(input);            
        }
		arrayInput.set(array,arraySize);
		xsd__base64Binary_Array* arrayResult = ws->asArray(&arrayInput);
		int outputSize=0;
		const xsd__base64Binary **output=arrayResult->get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
		for (int index = 0; index < outputSize ; index++)
		{
            size = 0;
            const xsd__unsignedByte * data = output[index]->get(size);
			cout << " element[" << index << "]" << endl;
            cout << "  size=" << size << endl;
            cout << "  data=" << asciiToStringOfLength((char *) data, size) << endl;
		}

        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;
        delete arrayResult;

		// Test complex type
		SimpleComplexType complexTypeInput;
		complexTypeInput.setcomplexTypeElement(input);
		SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        xsd__base64Binary binaryObject = complexTypeResult->getcomplexTypeElement();
        size = 0;
        const xsd__unsignedByte * data = binaryObject.get(size);
		cout << "within complex type" << endl;
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;
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

