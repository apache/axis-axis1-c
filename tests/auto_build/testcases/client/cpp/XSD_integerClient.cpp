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

#include "XSD_integer.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"

int main(int argc, char* argv[])
{
    XSD_integer* ws;
    
    xsd__integer result;
    xsd__integer input;
    xsd__integer* nillableResult;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_integer";

    if(argc>1)
        url = argv[1];

      // bool bSuccess = false;

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_integer(endpoint);
        
        result = ws->asNonNillableElement((xsd__integer) LONGLONGVALUE(9223372036854775807));
        cout << "non-nillable element=" << result << endl;
        
        result = ws->asNonNillableElement((xsd__integer)1);
        cout << "non-nillable element=" << result << endl;
        
        result = ws->asNonNillableElement((xsd__integer) LONGLONGVALUE(-9223372036854775808));
        cout << "non-nillable element=" << result << endl;
        
        result = ws->asNonNillableElement((xsd__integer)-1);
        cout << "non-nillable element=" << result << endl;
        
        result = ws->asNonNillableElement((xsd__integer)0);
        cout << "non-nillable element=" << result << endl;


        // Test nillable element, with a value
        input = (xsd__integer)123456789;
        nillableResult = ws->asNillableElement(&input);
        if (nillableResult)
        {
            cout << "nillable element=" << *(nillableResult) << endl;
            delete nillableResult;
        }
        else
            cout << "nillable element=<nil>" << endl;

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
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.setrequiredAttribute(123456789);
        requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
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

        // Test arrays
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsd__integer_Array inputArray;
        xsd__integer_Array * arrayResult;
        xsd__integer* array[ARRAY_SIZE];
        const xsd__integer** output;
        
        for (i = 0 ; i < ARRAY_SIZE ; i++)
            array[i] = new xsd__integer(123456789);
        inputArray.set(array, ARRAY_SIZE);
        
        arrayResult = ws->asArray(&inputArray);

        if (arrayResult)
            output = arrayResult->get(outputSize);
            
        cout << "array of " << outputSize << " elements" << endl;
        if (output != NULL)
        {
            for (i = 0 ; i < outputSize ; i++)
            {
                cout << "  element[" << i << "]=";
                if (output[i] != NULL)
                    cout << *output[i] << endl;
                else
                    cout << "NULL" << endl;
            }
        }
        else
            cout << "NULL array" << endl;

        // Clear up input array        
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete array[i];
        delete arrayResult;

        // Test complex type
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.setcomplexTypeElement(123456789);
        complexTypeResult = ws->asComplexType(&complexTypeInput);
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
