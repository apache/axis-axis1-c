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


#include "XSD_hexBinary.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"


int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_hexBinary";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        XSD_hexBinary* ws = new XSD_hexBinary(endpoint);

        xsd__hexBinary input;

        xsd__unsignedByte* testUB = (xsd__unsignedByte*)stringToAscii("<test><xml>some dod&y string</xml></test>");

        input.set(testUB, 41);

        // Test non-nillable element
        xsd__hexBinary result = ws->asNonNillableElement(input);
        cout << "non-nillable element" << endl;
        int size = 0;
        const xsd__unsignedByte * data = result.get(size);
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;

        // Test nillable element, with a value
        xsd__hexBinary* nillableInput = new xsd__hexBinary();
        *(nillableInput) = input;
        xsd__hexBinary* nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
        {
            cout << "nillable element" << endl;
            size = 0;
            data = nillableResult->get(size);
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
            size = 0 ;
            data = nillableResult->get(size);
            cout << " size=" << size << endl;
            cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;
            delete nillableResult;
        }
        else
        {
            cout << "nil element=<nil>" << endl;
        }

        // Test array
        xsd__hexBinary_Array arrayInput;
		int arraySize = 2;
        xsd__hexBinary ** array = new xsd__hexBinary*[arraySize];
        for (int inputIndex=0 ; inputIndex < arraySize ; inputIndex++)
        {
            array[inputIndex] = new xsd__hexBinary(input);            
        }
		arrayInput.set(array,arraySize);
        xsd__hexBinary_Array* arrayResult = ws->asArray(&arrayInput);
		int outputSize=0;
		const xsd__hexBinary ** output =arrayResult->get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (int index = 0; index < outputSize; index++)
        {
            cout << " element[" << index << "]" << endl;
            size = 0;
            data = output[index]->get(size);
            cout << "  size=" << size << endl;
            cout << "  data=" << asciiToStringOfLength((char *)data, size) << endl;
            
        }
        // Clear up input array        
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
        cout << "within complex type" << endl;
        size = 0;
        data = complexTypeResult->getcomplexTypeElement().get(size);
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
