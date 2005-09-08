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


#include "XSD_IDREFSPort.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_IDREFSPort";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        XSD_IDREFSPort* ws = new XSD_IDREFSPort(endpoint);
      
        char emptyIDREFS[1] = "";
        xsd__IDREFS emptyInput = new char[1];
        strcpy (emptyInput, emptyIDREFS);
        char simpleIDREFS[25] = "A simple test message!";
        xsd__IDREFS input = new char[25];
        strcpy (input, simpleIDREFS);

        

        // Test required attribute
        input = new char[25];
        strcpy (input, simpleIDREFS);
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
        strcpy (emptyInput, emptyIDREFS);
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

/* Optional Attributes currently unsupported by WSDL2Ws
 * Exact coding of this section may change depending on chosen implementation
        // Test optional attribute, with a value
        input = new char[25];
        strcpy (input, simpleIDREFS);
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
        strcpy (emptyInput, emptyIDREFS);
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
