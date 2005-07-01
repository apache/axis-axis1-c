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
        xsd__unsignedByte* testUB = (xsd__unsignedByte*)"<test><xml>some dod&y string</xml></test>";
        input.__ptr=testUB;
        input.__size=41;

        // Test non-nillable element
        xsd__hexBinary result = ws->asNonNillableElement(input);
        cout << "non-nillable element" << endl;
        cout << " size=" << result.__size << endl;
        cout << " data=" << result.__ptr << endl;

        // Test nillable element, with a value
        xsd__hexBinary* nillableInput = new xsd__hexBinary();
        *(nillableInput) = input;
        xsd__hexBinary* nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
        {
            cout << "nillable element" << endl;
            cout << " size=" << nillableResult->__size << endl;
            cout << " data=" << nillableResult->__ptr << endl;
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
            cout << " data=" << nillableResult->__ptr << endl;
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
        cout << " data=" << requiredAttributeResult->getrequiredAttribute().__ptr << endl;
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
            cout << " data=" << optionalAttributeResult->getoptionalAttribute()->__ptr << endl;
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
        arrayInput.m_Array = new xsd__hexBinary*[2];
        xsd__hexBinary * array = new xsd__hexBinary[2];
        arrayInput.m_Size = 2;
        for (int inputIndex=0 ; inputIndex < 2 ; inputIndex++)
        {
            array[inputIndex] = input;
            arrayInput.m_Array[inputIndex] = &array[inputIndex];
        }
        xsd__hexBinary_Array arrayResult = ws->asArray(arrayInput);
        cout << "array of " << arrayResult.m_Size << " elements" << endl;
        for (int index = 0; index < arrayResult.m_Size ; index++)
        {
            cout << " element[" << index << "]" << endl;
            cout << "  size=" << arrayResult.m_Array[index]->__size << endl;
            cout << "  data=" << arrayResult.m_Array[index]->__ptr << endl;
            delete arrayResult.m_Array[index];
        }
        delete [] array;
        delete [] arrayInput.m_Array;
        delete [] arrayResult.m_Array;

        // Test complex type
        SimpleComplexType complexTypeInput;
        complexTypeInput.setcomplexTypeElement(input);
        SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        cout << "within complex type" << endl;
        cout << " size=" << complexTypeResult->getcomplexTypeElement().__size << endl;
        cout << " data=" << complexTypeResult->getcomplexTypeElement().__ptr << endl;
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
