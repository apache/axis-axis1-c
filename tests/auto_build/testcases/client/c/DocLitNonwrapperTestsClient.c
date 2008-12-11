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

#include <stdlib.h>
#include <stdio.h>

#include <axis/Axis.h>

#include "CommonClientTestCode.h"
#include "OperationWS.h" 



int main(int argc, char* argv[])
{
	AXISCHANDLE ws;
    char *pszURL = "http://localhost/axis/Operation";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc > 1)
    	pszURL = argv[1];

    ws = get_OperationWS_stub(pszURL);
    
    // ==============================
    // Test 1
	{
        xsdc__string input1 = (xsdc__string )"Input for operation 1";
        xsdc__string result1;

        result1 = Operation1(ws, input1);
        if (result1)
        {
            printf("Operation1 returned: %s\n", result1);
        }
        else
            printf("Operation1 returned NULL - test failed\n");
	}
	
    // ==============================
    // Test 2
	{
        Operation2Request input2;
        Operation2Response* result2;

        input2.number1 = 2000;
        result2 = Operation2(ws, &input2);
        if (result2)
        {
            printf("Operation2 returned: %d\n", result2->result);
            Axis_Delete_Operation2Response(result2, 0);
        }
        else
            printf("Operation2 returned NULL - test failed\n");
    }

    // ==============================
    // Test 3
    {
        Operation3Response* result3;

        result3 = Operation3(ws);
        if (result3)
        {
            printf("Operation3 returned: %d\n", result3->result);
            Axis_Delete_Operation3Response(result3, 0);
        }
        else
            printf("Operation3 returned NULL - test failed\n");
     }

    // ==============================
    // Test 4
    {
        Operation4Request input4;

        aRecord *arec = (aRecord  *)Axis_Create_aRecord(0);
        arec->field1 = "field4444401";
        arec->field2 = "field4444402";
        arec->field3 = "field4444403";

        input4.record = arec;

        Operation4(ws, &input4);
        printf("Operation4 completed...no response expected. \n");
    }
    
    // ==============================
    // Test 5
    {
        Operation5Request input5;

        aRecord *arec = (aRecord  *)Axis_Create_aRecord(0);
        arec->field1 = "field5555501";
        arec->field2 = "field5555502";
        arec->field3 = "field5555503";

        input5.record = arec;

        Operation5(ws, &input5);
        printf("Operation5 completed...no response expected. \n");
    }

    printf("---------------------- TEST COMPLETE -----------------------------\n");
    
    return 0;
}
