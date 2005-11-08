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


#include "XSD_Name.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_Name";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        XSD_Name* ws = new XSD_Name(endpoint);
      
        char emptyName[1] = "";
        xsd__Name emptyInput = new char[1];
        strcpy (emptyInput, emptyName);
        //char simpleName[25] = "A simple test message!";
        char simpleName[25] = "xml.si-mple_nam:e";
        xsd__Name input = new char[25];
        strcpy (input, simpleName);

        // Test non-nillable element
        xsd__Name result = ws->asNonNillableElement(input);
        if (result)
        {
            if (*result)
            {
                cout << "non-nillable element=" << result << endl;
            }
            else
            {
                cout << "non-nillable element=<empty>" << endl;
            }
        }
        else
        {
            cout << "non-nillable element=<nil>" << endl;
        }
        delete [] input;

        // Test empty non-nillable element
        result = ws->asNonNillableElement(emptyInput);
        if (result)
        {
            if (*result)
            {
                cout << "empty non-nillable element=" << result << endl;
            }
            else
            {
                cout << "empty non-nillable element=<empty>" << endl;
            }
        }
        else
        {
            cout << "empty non-nillable element=<nil>" << endl;
        }
        delete [] emptyInput;

        // Test nillable element, with a value
        input = new char[25];
        strcpy (input, simpleName);
        xsd__Name nillableResult = ws->asNillableElement(input);
        if (nillableResult)
        {
            if (*nillableResult)
            {
                cout << "nillable element=" << nillableResult << endl;
            }
            else
            {
                cout << "nillable element=<empty>" << endl;
            }
            delete nillableResult;
        }
        else
        {
            cout << "nillable element=<nil>" << endl;
        }
        delete [] input;

        // Test empty nillable element
        emptyInput = new char[1];
        strcpy (emptyInput, emptyName);
        nillableResult = ws->asNillableElement(emptyInput);
        if (nillableResult)
        {
            if (*nillableResult)
            {
                cout << "empty nillable element=" << nillableResult << endl;
            }
            else
            {
                cout << "empty nillable element=<empty>" << endl;
            }
            delete nillableResult;
        }
        else
        {
            cout << "empty nillable element=<nil>" << endl;
        }
        delete [] emptyInput;

        // Test nillable element, with nil
        nillableResult = ws->asNillableElement(NULL);
        if (nillableResult)
        {
            if (*nillableResult)
            {
                cout << "nil element=" << nillableResult << endl;
            }
            else
            {
                cout << "nil element=<empty>" << endl;
            }
            delete nillableResult;
        }
        else
        {
            cout << "nil element=<nil>" << endl;
        }

        // Test required attribute
        input = new char[25];
        strcpy (input, simpleName);
        RequiredAttributeElement requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(input);
        RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        if (requiredAttributeResult->getrequiredAttribute())
        {
            if (*(requiredAttributeResult->getrequiredAttribute()))
            {
                cout << "required attribute=" << requiredAttributeResult->getrequiredAttribute() << endl;
            }
            else
            {
                cout << "required attribute=<empty>" << endl;
            }
        }
        else
        {
            cout << "required attribute=<nil>" << endl;
        }
        delete requiredAttributeResult;

        // Test empty required attribute
        emptyInput = new char[1];
        strcpy (emptyInput, emptyName);
        requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(emptyInput);
        requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        if (requiredAttributeResult->getrequiredAttribute())
        {
            if (*(requiredAttributeResult->getrequiredAttribute()))
            {
                cout << "empty required attribute=" << requiredAttributeResult->getrequiredAttribute() << endl;
            }
            else
            {
                cout << "empty required attribute=<empty>" << endl;
            }
        }
        else
        {
            cout << "empty required attribute=<nil>" << endl;
        }
        delete requiredAttributeResult;

/*  Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleName);
        OptionalAttributeElement optionalAttributeInput;
        optionalAttributeInput.setoptionalAttribute(input);
        OptionalAttributeElement* optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
            {
                cout << "optional attribute, with data=" << optionalAttributeResult->getoptionalAttribute() << endl;
            }
            else
            {
                cout << "optional attribute, with data=<empty>" << endl;
            }
        }
        else
        {
            cout << "optional attribute, with data=<not present>" << endl;
        }
        delete [] input;
        delete optionalAttributeResult;

        // Test empty optional attribute
        emptyInput = new char[1];
        strcpy (emptyInput, emptyName);
        optionalAttributeInput.setoptionalAttribute(emptyInput);
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
            {
                cout << "empty optional attribute=" << optionalAttributeResult->getoptionalAttribute() << endl;
            }
            else
            {
                cout << "empty optional attribute=<empty>" << endl;
            }
        }
        else
        {
            cout << "empty optional attribute=<not present>" << endl;
        }
        delete [] emptyInput;
        delete optionalAttributeResult;

        // Test optional attribute, not present
        // optionalAttributeInput.setattribute();
        optionalAttributeResult = ws->asOptionalAttribute(&optionalAttributeInput);
        if (optionalAttributeResult->getoptionalAttribute())
        {
            if (*(optionalAttributeResult->getoptionalAttribute()))
            {
                cout << "optional attribute, not present=" << optionalAttributeResult->getoptionalAttribute() << endl;
            }
            else
            {
                cout << "optional attribute, not present=<empty>" << endl;
            }
        }
        else
        {
            cout << "optional attribute, not present=<not present>" << endl;
        }
        delete optionalAttributeResult;
*/

        // Test array
          xsd__Name_Array arrayInput;
		 int arraySize=2;
		 xsd__Name *array = new xsd__Name[arraySize]();        
        for (int inputIndex=0 ; inputIndex <arraySize ; inputIndex++)
        {
            input = new char[25];
            strcpy (input, simpleName);
            array[inputIndex] = input;
        }
		arrayInput.set(array,arraySize);
        xsd__Name_Array arrayResult = ws->asArray(arrayInput);
		int outputSize=0;
		const xsd__Name *output = arrayResult.get(outputSize);
        cout << "array of " << outputSize << " elements" << endl;
        for (int index = 0; index < outputSize ; index++)
        {
            if (output!=NULL)
            {
                if (output[index]!=NULL)
                {
                    cout << "  element[" << index << "]=" << output[index] << endl;
                }
                else
                {
                    cout << "  element[" << index << "]=<empty>" << endl;
                }
             }
            else
            {
                cout << "  element[" << index << "]=<nil>" << endl;
            }
        }
        // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < arraySize ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;

        // Test complex type
        input = new char[25];
        strcpy (input, simpleName);
        SimpleComplexType complexTypeInput;
        complexTypeInput.setcomplexTypeElement(input);
        SimpleComplexType* complexTypeResult = ws->asComplexType(&complexTypeInput);
        if (complexTypeResult->getcomplexTypeElement())
        {
            if (*(complexTypeResult->getcomplexTypeElement()))
            {
                cout << "within complex type=" << complexTypeResult->getcomplexTypeElement() << endl;
            }
            else
            {
                cout << "within complex type=<empty>" << endl;
            }
        }
        else
        {
            cout << "within complex type=<nil>" << endl;
        }
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
