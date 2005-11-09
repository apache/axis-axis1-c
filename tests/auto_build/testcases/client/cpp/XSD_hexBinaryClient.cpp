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

        input.__ptr=testUB;
        input.__size=41;

        // Test non-nillable element
        xsd__hexBinary result = ws->asNonNillableElement(input);
        cout << "non-nillable element" << endl;
        cout << " size=" << result.__size << endl;
        cout << " data=" << asciiToStringOfLength((char *)result.__ptr, result.__size) << endl;

        // Test nillable element, with a value
        xsd__hexBinary* nillableInput = new xsd__hexBinary();
        *(nillableInput) = input;
        xsd__hexBinary* nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
        {
            cout << "nillable element" << endl;
            cout << " size=" << nillableResult->__size << endl;
            cout << " data=" << asciiToStringOfLength((char *)nillableResult->__ptr, nillableResult->__size) << endl;
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
            cout << " size=" << nillableResult->__size << endl;
            cout << " data=" << asciiToStringOfLength((char *)nillableResult->__ptr, nillableResult->__size) << endl;
            delete nillableResult;
        }
        else
        {
            cout << "nil element=<nil>" << endl;
        }

        // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(input);
        RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        cout << "required attribute" << endl;
        cout << " size=" << requiredAttributeResult->getrequiredAttribute().__size << endl;
        cout << " data=" << asciiToStringOfLength((char *)requiredAttributeResult->getrequiredAttribute().__ptr, requiredAttributeResult->getrequiredAttribute().__size) << endl;
        delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            cout << "optional attribute, with data" << endl;
            cout << " size=" << optionalAttributeResult->getoptionalAttribute()->__size << endl;
            cout << " data=" << asciiToStringOfLength((char *)optionalAttributeResult->getoptionalAttribute()->__ptr, optionalAttributeResult->getoptionalAttribute()->__size) << endl;
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
            cout << "optional attribute, not present" << endl;
            cout << " size=" << optionalAttributeResult->getoptionalAttribute()->__size << endl;
            cout << " data=" << optionalAttributeResult->getoptionalAttribute()->__ptr << endl;
        }
        else
        {
            cout << "optional attribute, not present=<not present>" << endl;
        }
        delete optionalAttributeResult;
*/

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
            cout << "  size=" << output[index]->__size << endl;
            cout << "  data=" << asciiToStringOfLength((char *)output[index]->__ptr, output[index]->__size) << endl;
            
        }
        // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;


        // Test complex type
        SimpleComplexType complexTypeInput;
        complexTypeInput.setcomplexTypeElement(input);
        SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        cout << "within complex type" << endl;
        cout << " size=" << complexTypeResult->getcomplexTypeElement().__size << endl;
        cout << " data=" << asciiToStringOfLength((char *)complexTypeResult->getcomplexTypeElement().__ptr, complexTypeResult->getcomplexTypeElement().__size) << endl;
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
