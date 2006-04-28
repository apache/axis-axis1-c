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


#include "XSD_anyURI.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>


int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_anyURI";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        XSD_anyURI* ws = new XSD_anyURI(endpoint);
      
        char emptyanyURI[1] = "";
        xsd__anyURI emptyInput = new char[1];
        strcpy (emptyInput, emptyanyURI);
                char simpleanyURI[100] = "http://www.w3.org/People/Dürst/";
        xsd__anyURI input = new char[100];
        strcpy (input, simpleanyURI);

        // Test non-nillable element
        xsd__anyURI result = ws->asNonNillableElement(input);
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
