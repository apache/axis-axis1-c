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

        input.set(testUB, 41);

        // Test required attribute
        RequiredAttributeElement requiredAttributeInput;
        requiredAttributeInput.setrequiredAttribute(input);
        RequiredAttributeElement* requiredAttributeResult = ws->asRequiredAttribute(&requiredAttributeInput);
        cout << "required attribute" << endl;
        int size = 0;
        const xsd__unsignedByte * data = requireAttributeResult->getrequiredAttribute().get();
        cout << " size=" << size << endl;
        cout << " data=" << asciiToStringOfLength((char *)data, size) << endl;
        delete requiredAttributeResult;

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
