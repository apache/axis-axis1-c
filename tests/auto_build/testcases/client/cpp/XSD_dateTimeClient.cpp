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


#include "XSD_dateTime.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    XSD_dateTime* ws;
    
    char returnString[50];
    
    xsd__dateTime result;
    xsd__dateTime input;
    xsd__dateTime* nillableResult;

    time_t timeToTest;
    struct tm *temp;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_dateTime";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_dateTime(endpoint);

        timeToTest = 1100246323;
        temp = gmtime(&timeToTest);
        memcpy(&input, temp, sizeof(struct tm));

        // Test non-nillable element
        result = ws->asNonNillableElement(input);
        strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", &result);
        cout << "non-nillable element=" << returnString << endl;

        // Test nillable element, with a value
        nillableResult = ws->asNillableElement(&input);
        if (nillableResult)
        {
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", nillableResult);
            cout << "nillable element=" << returnString << endl;
            delete nillableResult;
        }
        else
            cout << "nillable element=<nil>" << endl;

        // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
        if (nillableResult)
        {
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", nillableResult);
            cout << "nil element=" << returnString << endl;
            delete nillableResult;
        }
        else
            cout << "nil element=<nil>" << endl;

        // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
        RequiredAttributeElement* requiredAttributeResult;
        
        requiredAttributeInput.setrequiredAttribute(input);
        requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
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
                        cout << "optional attribute, with data=<not present>" << endl;
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
                        cout << "optional attribute, not present=<not present>" << endl;
                delete optionalAttributeResult;
*/
        // Test array
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsd__dateTime_Array arrayInput;
        xsd__dateTime_Array* arrayResult;
        xsd__dateTime *array[ARRAY_SIZE];
        const xsd__dateTime **output;

        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] =new xsd__dateTime(input);
        arrayInput.set(array,ARRAY_SIZE);
        
        arrayResult = ws->asArray(&arrayInput);
 
        if (arrayResult)
            output = arrayResult->get(outputSize);
        
        cout << "array of " << outputSize << " elements" << endl;
        for (i = 0; i < outputSize ; i++)
        {
            strftime(returnString, 50, "%a %b %d %H:%M:%S %Y", output[i]);
            cout << "  element[" << i << "]=" << returnString << endl;
        }
        // Clear up input array
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete array[i];
        delete arrayResult;


        // Test complex type
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.setcomplexTypeElement(input);
        complexTypeResult = ws->asComplexType(&complexTypeInput);
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
