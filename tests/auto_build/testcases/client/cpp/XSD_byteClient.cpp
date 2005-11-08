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


#include "XSD_byte.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_byte";

    if(argc>1)
        url = argv[1];

      // bool bSuccess = false;

    try
    {
        sprintf(endpoint, "%s", url);
        XSD_byte* ws = new XSD_byte(endpoint);

        xsd__byte result = ws->asNonNillableElement((xsd__byte)127);
        cout << "non-nillable element=" << (int) result << endl;
        result = ws->asNonNillableElement((xsd__byte)1);
        cout << "non-nillable element=" << (int) result << endl;
        result = ws->asNonNillableElement((xsd__byte)-128);
        cout << "non-nillable element=" << (int) result << endl;
        result = ws->asNonNillableElement((xsd__byte)-1);
        cout << "non-nillable element=" << (int) result << endl;
        result = ws->asNonNillableElement((xsd__byte)0);
        cout << "non-nillable element=" << (int) result << endl;


        // Test nillable element, with a value
        xsd__byte* nillableInput = new xsd__byte();
        *(nillableInput) = (xsd__byte)123;
        xsd__byte* nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
        {
            cout << "nillable element=" << (int) *(nillableResult) << endl;
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
            cout << "nil element=" << (int) *(nillableResult) << endl;
            delete nillableResult;
        }
        else
        {
            cout << "nil element=<nil>" << endl;
        }

        // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(123);
        RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        cout << "required attribute=" << (int) requiredAttributeResult->getrequiredAttribute() << endl;
        delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(123);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            cout << "optional attribute, with data=" << (int) optionalAttributeResult->getoptionalAttribute() << endl;
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
            cout << "optional attribute, not present=" << (int) optionalAttributeResult->getoptionalAttribute() << endl;
        }
        else
        {
            cout << "optional attribute, not present=<not present>" << endl;
        }
        delete optionalAttributeResult;
*/

        // Test array
        xsd__byte_Array arrayInput;
		int arraySize=2;
		xsd__byte **array = new xsd__byte*[arraySize]();
        
        for (int inputIndex=0 ; inputIndex < 2 ; inputIndex++)
        {
            array[inputIndex] = new xsd__byte(123);
        }
		arrayInput.set(array,arraySize);
        xsd__byte_Array arrayResult = ws->asArray(arrayInput);
		int outputSize=0;
		const xsd__byte ** output=arrayResult.get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (int index = 0; index < outputSize ; index++)
        {
            cout << "  element[" << index << "]=" << (int)*output[index] << endl;
        }
        // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;


        // Test complex type
        SimpleComplexType complexTypeInput;
        complexTypeInput.setcomplexTypeElement(123);
        SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        cout << "within complex type=" << (int) complexTypeResult->getcomplexTypeElement() << endl;
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
