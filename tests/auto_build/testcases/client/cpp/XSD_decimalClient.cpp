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


#include "XSD_decimal.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    XSD_decimal* ws;
    
    xsd__decimal result;
    xsd__decimal input;
    xsd__decimal* nillableResult;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_decimal";

    if(argc>1)
        url = argv[1];

    // bool bSuccess = false;

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_decimal(endpoint);

        result = ws->asNonNillableElement((xsd__decimal)123456789);
        printf("non-nillable element=%.6f\n", result);
        fflush(stdout);
        result = ws->asNonNillableElement((xsd__decimal)123456789.123456);
        printf("non-nillable element=%.6f\n", result);
        fflush(stdout);
        result = ws->asNonNillableElement((xsd__decimal)-123456789);
        printf("non-nillable element=%.6f\n", result);
        fflush(stdout);
        result = ws->asNonNillableElement((xsd__decimal)-123456789.123456);
        printf("non-nillable element=%.6f\n", result);
        fflush(stdout);
        result = ws->asNonNillableElement((xsd__decimal)0);
        printf("non-nillable element=%.6f\n", result);
        fflush(stdout);

        // Test nillable element, with a value
        input = (xsd__decimal)123456789;
        nillableResult = ws->asNillableElement(&input);
        if (nillableResult)
        {
            printf("nillable element=%.6f\n", *(nillableResult));
            fflush(stdout);
            delete nillableResult;
        }
        else
            cout << "nillable element=<nil>" << endl;

        // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
        if (nillableResult)
        {
            printf("nil element=%.6f\n", *(nillableResult));
            fflush(stdout);
            delete nillableResult;
        }
        else
            cout << "nil element=<nil>" << endl;

        // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.setrequiredAttribute(123456789);
        requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        printf("required attribute=%.6f\n", requiredAttributeResult->getrequiredAttribute());
        fflush(stdout);
        delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
                // Test optional attribute, with a value
                OptionalAttributeElement optionalAttributeInput;
                optionalAttributeInput.setoptionalAttribute(123456789);
                OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
                if (optionalAttributeResult->getoptionalAttribute())
                {
                        printf("optional attribute, with data=%.6f\n",  optionalAttributeResult->getoptionalAttribute());
            fflush(stdout);
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
                        printf("optional attribute, not present=%.6f\n", optionalAttributeResult->getoptionalAttribute());
            fflush(stdout);
                }
                else
                {
                        cout << "optional attribute, not present=<not present>" << endl;
                }
                delete optionalAttributeResult;
*/

        // Test array
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
                
        xsd__decimal_Array arrayInput;
        xsd__decimal_Array* arrayResult;
        xsd__decimal *array[ARRAY_SIZE];
        const xsd__decimal ** output;
        
        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] = new xsd__decimal(123456789);
        arrayInput.set(array,ARRAY_SIZE);
        
        arrayResult = ws->asArray(&arrayInput);

        if (arrayResult)
            output = arrayResult->get(outputSize);

        cout << "array of " << outputSize << " elements" << endl;
        for (i = 0; i < outputSize ; i++)
        {
            printf("  element[%i]=%.6f\n", i, *((xsd__decimal*)output[i]));
            fflush(stdout);
        }
        // Clear up input array
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete array[i];
        delete arrayResult;

        // Test complex type
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.setcomplexTypeElement(123456789);
        complexTypeResult = ws->asComplexType(&complexTypeInput);
        printf("within complex type=%.6f\n", complexTypeResult->getcomplexTypeElement());
        fflush(stdout);
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
