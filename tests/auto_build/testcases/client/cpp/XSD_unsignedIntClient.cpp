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


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO THIS FILE MAY ALSO REQUIRE CHANGES TO THE               */
/* C-EQUIVALENT FILE. PLEASE ENSURE THAT IT IS DONE.                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include "XSD_unsignedInt.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

int main(int argc, char* argv[])
{
    XSD_unsignedInt* ws;
    
    xsd__unsignedInt result;
    xsd__unsignedInt* nillableInput;
    xsd__unsignedInt* nillableResult;    
        
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_unsignedInt";

    if(argc>1)
        url = argv[1];

      // bool bSuccess = false;

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_unsignedInt(endpoint);

        result = ws->asNonNillableElement((xsd__unsignedInt)4294967295);
        cout << "non-nillable element=" << result << endl;
        result = ws->asNonNillableElement((xsd__unsignedInt)1);
        cout << "non-nillable element=" << result << endl;
        result = ws->asNonNillableElement((xsd__unsignedInt)0);
        cout << "non-nillable element=" << result << endl;


        // Test nillable element, with a value
        nillableInput = new xsd__unsignedInt();
        *(nillableInput) = (xsd__unsignedInt)123456789;
        nillableResult = ws->asNillableElement(nillableInput);
        if (nillableResult)
        {
            cout << "nillable element=" << *(nillableResult) << endl;
            delete nillableResult;
        }
        else
            cout << "nillable element=<nil>" << endl;
        delete nillableInput;

        // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
        if (nillableResult)
        {
            cout << "nil element=" << *(nillableResult) << endl;
            delete nillableResult;
        }
        else
            cout << "nil element=<nil>" << endl;

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
            cout << "optional attribute, with data=" << optionalAttributeResult->getoptionalAttribute() << endl;
        else
            cout << "optional attribute, with data=<not present>" << endl;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
            cout << "optional attribute, not present=" << optionalAttributeResult->getoptionalAttribute() << endl;
        else
            cout << "optional attribute, not present=<not present>" << endl;
        delete optionalAttributeResult;
*/

        // Test array
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsd__unsignedInt_Array arrayInput;
        xsd__unsignedInt_Array* arrayResult;
        xsd__unsignedInt * array[ARRAY_SIZE];
        const xsd__unsignedInt ** output;
        
        for (i=0 ; i < ARRAY_SIZE; i++)
            array[i] = new xsd__unsignedInt(123456789);
        arrayInput.set(array,ARRAY_SIZE);
        
        arrayResult = ws->asArray(&arrayInput);

        if (arrayResult)
            output =arrayResult->get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (i = 0; i < outputSize ; i++)
            cout << "  element[" << i << "]=" << *((xsd__unsignedInt*)(output[i])) << endl;

        // Clear up input array        
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete array[i];
        delete arrayResult;


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
