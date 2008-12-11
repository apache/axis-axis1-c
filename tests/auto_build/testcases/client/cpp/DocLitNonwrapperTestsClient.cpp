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


#include <axis/AxisException.hpp>
#include <axis/Axis.hpp>
#include "OperationWS.hpp" 

#include <stdlib.h> // For malloc(), calloc(), strdup() and free()
#include <iostream>


int main(int argc, char* argv[])
{
    char *pszURL = "http://localhost/axis/Operation";

    // Axis::startTrace("/tmp/axis.log", "noEntryExit;transport");

    if (argc > 1)
    	pszURL = argv[1];

    OperationWS ws(pszURL);

    try
    {

        // ==============================
        // Test 1
        xsd__string input1 = (xsd__string )"Input for operation 1";
        xsd__string result1;

        result1 = ws.Operation1(input1);
        if (result1)
        {
            cout << "Operation1 returned: " << result1<< endl;
        }
        else
            cout << "Operation1 returned NULL - test failed" << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }
      
    try
    {  
        // ==============================
        // Test 2
        Operation2Request input2;
        Operation2Response* result2;

        input2.setnumber1(2000);
        result2 = ws.Operation2(&input2);
        if (result2)
        {
            cout << "Operation2 returned: " << result2->getresult() << endl;
            Axis_Delete_Operation2Response(result2);
        }
        else
            cout << "Operation2 returned NULL - test failed" << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }

    try
    {  
        // ==============================
        // Test 3
        Operation3Response* result3;

        result3 = ws.Operation3();
        if (result3)
        {
            cout << "Operation3 returned: " << result3->getresult() << endl;
            Axis_Delete_Operation3Response(result3);
        }
        else
            cout << "Operation3 returned NULL - test failed" << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }

    try
    {  
        // ==============================
        // Test 4
        Operation4Request input4;

        aRecord *arec = (aRecord  *)Axis_Create_aRecord();
        arec->setfield1("field4444401");
        arec->setfield2("field4444402");
        arec->setfield3("field4444403");

        input4.setrecord(arec);

        ws.Operation4(&input4);
        cout << "Operation4 completed...no response expected. " << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }

    try
    {  
        // ==============================
        // Test 5
        Operation5Request input5;

        aRecord *arec = (aRecord  *)Axis_Create_aRecord();
        arec->setfield1("field5555501");
        arec->setfield2("field5555502");
        arec->setfield3("field5555503");

        input5.setrecord(arec);

        ws.Operation5(&input5);
        cout << "Operation5 completed...no response expected. " << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }

    cout << "---------------------- TEST COMPLETE -----------------------------" << endl;
    
    return 0;
}
