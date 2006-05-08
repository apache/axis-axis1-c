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

#include "XSD_string.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    XSD_string* ws;

    xsd__string input;
    xsd__string result;

    char emptyString[1] = "";
    char simpleString[25] = "A simple test message!";
    char reservedCharactersString[] = "<>&\"\'";
    char whitespaceString[] = "  \t\r\nsome text \t\r\nmore text \t\r\n";

    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_string";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        ws = new XSD_string(endpoint);
      
        input = new char[25];
        strcpy (input, simpleString);

        // Test non-nillable element
        result = ws->asNonNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "non-nillable element=" << result << endl;
            else
                cout << "non-nillable element=<empty>" << endl;
            delete result;
        }
        else
            cout << "non-nillable element=<nil>" << endl;
        delete [] input;

        // Test empty non-nillable element
        input = new char[1];
        strcpy (input, emptyString);

        result = ws->asNonNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "empty non-nillable element=" << result << endl;
            else
                cout << "empty non-nillable element=<empty>" << endl;
            delete result;
        }
        else
            cout << "empty non-nillable element=<nil>" << endl;
        delete []input;

        // Test non-nillable element with XML reserved characters
        input = reservedCharactersString;
        result = ws->asNonNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "non-nillable element with XML reserved characters=" << result << endl;
            else
                cout << "non-nillable element with XML reserved characters=<empty>" << endl;
            delete result;
        }
        else
            cout << "non-nillable element with XML reserved characters=<nil>" << endl;

        // Test non-nillable element with XML reserved characters
        input = whitespaceString;
        result = ws->asNonNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "non-nillable element with whitespace characters=\"" << result << "\"" << endl;
            else
                cout << "non-nillable element with whitespace characters=<empty>" << endl;
            delete result;
        }
        else
            cout << "non-nillable element with whitespace characters=<nil>" << endl;

        // Test nillable element, with a value
        input = new char[25];
        strcpy (input, simpleString);
        result = ws->asNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "nillable element=" << result << endl;
            else
                cout << "nillable element=<empty>" << endl;
            delete result;
        }
        else
            cout << "nillable element=<nil>" << endl;
        delete [] input;

        // Test empty nillable element
        input = new char[1];
        strcpy (input, emptyString);
        result = ws->asNillableElement(input);
        if (result)
        {
            if (*result)
                cout << "empty nillable element=" << result << endl;
            else
                cout << "empty nillable element=<empty>" << endl;
            delete result;
        }
        else
            cout << "empty nillable element=<nil>" << endl;
        delete []input;

        // Test nillable element, with nil
        result = ws->asNillableElement(NULL);
        if (result)
        {
            if (*result)
                cout << "nil element=" << result << endl;
            else
                cout << "nil element=<empty>" << endl;
            delete result;
        }
        else
            cout << "nil element=<nil>" << endl;

        // Test required attribute
        input = new char[25];
        strcpy (input, simpleString);
        RequiredAttributeElement requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(input);
        RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        if (requiredAttributeResult->getrequiredAttribute())
        {
            if (*(requiredAttributeResult->getrequiredAttribute()))
                cout << "required attribute=" << requiredAttributeResult->getrequiredAttribute() << endl;
            else
                cout << "required attribute=<empty>" << endl;
        }
        else
            cout << "required attribute=<nil>" << endl;
        delete requiredAttributeResult;

        // Test empty required attribute
       input = new char[1];
        strcpy (input, emptyString);
        requiredAttributeInput.setrequiredAttribute(input);
        requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        if (requiredAttributeResult->getrequiredAttribute())
        {
            if (*(requiredAttributeResult->getrequiredAttribute()))
                cout << "empty required attribute=" << requiredAttributeResult->getrequiredAttribute() << endl;
            else
                cout << "empty required attribute=<empty>" << endl;
        }
        else
            cout << "empty required attribute=<nil>" << endl;
        delete requiredAttributeResult;

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleString);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                cout << "optional attribute, with data=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                cout << "optional attribute, with data=<empty>" << endl;
        }
        else
            cout << "optional attribute, with data=<not present>" << endl;
        delete optionalAttributeResult;

        // Test empty optional attribute
        input = new char[1];
        strcpy (input, emptyString);
        optionalAttributeInput.setoptionalAttribute(input);
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                cout << "empty optional attribute=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                cout << "empty optional attribute=<empty>" << endl;
        }
        else
            cout << "empty optional attribute=<not present>" << endl;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
                cout << "optional attribute, not present=" << optionalAttributeResult->getoptionalAttribute() << endl;
            else
                cout << "optional attribute, not present=<empty>" << endl;
        }
        else
            cout << "optional attribute, not present=<not present>" << endl;
        delete optionalAttributeResult;
*/

        // Test arrays
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsd__string_Array inputArray;
        xsd__string_Array * arrayResult;
        xsd__string array[ARRAY_SIZE];
        const xsd__string* output;
         
        for (i = 0 ; i < ARRAY_SIZE ; i++)
        {
            array[i] = new char[25];
            strcpy (array[i], simpleString);
        }
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
                    cout << output[i] << endl;
                else
                    cout << "NULL" << endl;
            }
        }
        else
            cout << "NULL array" << endl;

        // Clear up input array        
        for (i = 0 ; i < ARRAY_SIZE ; i++ )
            delete [] array[i];
        delete arrayResult;



        
        // Test complex type
        input = new char[25];
        strcpy (input, simpleString);
        SimpleComplexType complexTypeInput;
        complexTypeInput.setcomplexTypeElement(input);
        SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        if (complexTypeResult->getcomplexTypeElement())
        {
            if (*(complexTypeResult->getcomplexTypeElement()))
                cout << "within complex type=" << complexTypeResult->getcomplexTypeElement() << endl;
            else
                cout << "within complex type=<empty>" << endl;
        }
        else
            cout << "within complex type=<nil>" << endl;
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
