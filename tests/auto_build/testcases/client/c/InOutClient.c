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


/*
   Perform a variety of tests.
   1) pass no parameters and get no return
   2) pass no parameters and get an int return
   3) pass a mixture of primitive parameters and get no return
   4) pass a mixture of primitives, arrays and complex types all of which are not nillable
   5) pass a mixture of primitives, arrays and complex types some of which are nillable
   6) pass multiple arrays of different primitive types and get an int return
   7) pass a complex type which has primitives, arrays and complex type and return the 
      same type
   8) pass a complex type which has primitives, arrays and complex type and return the 
      same type with element set as nil
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "InOut.h"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/InOut";

    static char* str1 = "Apache";
    static char* str2 = "Axis C++";
    
    int x = 0;
    int npr;
    
    ComplexType1 ct;
    
    xsdc__string_Array stringArray;
    xsdc__string arrayOfString[3] = {"One", "Two", "Three"};
    
    xsdc__int_Array intArray;
    xsdc__int arrayOfIntVal[3] = {37, 0, 43 };
    xsdc__int * arrayOfInt[3];
        
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
       url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_InOut_stub(endpoint);

    printf( "noParametersNoReturn\n" );
    noParametersNoReturn(ws);
    printf( "noParametersNoReturn returned\n" );

    printf( "noParametersIntReturn\n" );
    npr = noParametersIntReturn(ws);
    printf( "noParametersIntReturn returned %d\n" , npr );

    printf( "multiParametersNoReturn\n" );
    multiParametersNoReturn(ws, "Hey dude", 69, (xsdc__double)17.19);
    printf( "multiParametersNoReturn returned\n" );


    // test multiParametersMultiReturn
    {
        xsdc__string outValue0 = "";
        xsdc__int outValue1 = 0;
        xsdc__double outValue2 = 0;
    
        printf( "multiParametersMultiReturn\n" );
        multiParametersMultiReturn(ws, "Hey dude", 69, (xsdc__double)17.19, 
                                   &outValue0, &outValue1, &outValue2);
        printf( "multiParametersMultiReturn returned %s , %d , %g\n" , outValue0 , outValue1, outValue2);
    }

    //...........................................................

    {
        for (x=0; x<3; x++)
            arrayOfInt[x] = &arrayOfIntVal[x];
            
        intArray.m_Array = arrayOfInt;
        intArray.m_Size  = 3;
        intArray.m_Type  = XSDC_INT;
        
        stringArray.m_Array = arrayOfString;
        stringArray.m_Size  = 3;
        stringArray.m_Type  = XSDC_STRING;
    
        ct.ctLong = (xsdc__long)87654321;
        ct.ctString = "World";
        ct.ctIntArray = &intArray;
    
        printf( "multiComplexParametersIntReturn\n" );
        npr = multiComplexParametersIntReturn(ws, "Hello", &ct, 27, 13.31, &stringArray);
        printf( "multiComplexParametersIntReturn returned %d\n" , npr );
    }

    //test multiComplexParametersMultiComplexReturn
    {       
        xsdc__string OutValue0 = "";
        ComplexType1* OutValue1;
        xsdc__int outValue22 = 0;
        xsdc__double outValue33 = 0;
    
        printf( "multiComplexParametersMultiComplexReturn\n" );
        multiComplexParametersMultiComplexReturn(ws, "Hello", &ct, 27, 13.31, &stringArray, 
                                                    &OutValue0, &OutValue1, &outValue22, &outValue33);
        printf( "multiComplexParametersMultiComplexReturn returned %s , %s\n" , OutValue0 , OutValue1->ctString);
    }

    //..............................................................................
    {
        ComplexNilType1 cnt;
        xsdc__long longValue = 87654321;
        
        arrayOfString[0]="Four";
        arrayOfString[1]=NULL;
        arrayOfString[2]="Six";
                
        cnt.ctLong = &longValue;
        cnt.ctString = NULL;
        cnt.ctIntArray = &intArray;
    
        printf( "multiComplexParametersNilIntReturn\n" );
        npr = multiComplexParametersNilIntReturn(ws, NULL, &cnt, NULL, NULL, &stringArray);
        printf( "multiComplexParametersNilIntReturn returned %d\n" , npr );
    }

        /* Commented out as there is a bug in WSDL2Ws.
         * AXISCPP-565 is the Jira against this problem.
        xsdc__double* moDouble;
        xsdc__int* moInt;
        xsdc__string moString;
        printf( "noParametersMultiReturn\n" );
        ws.noParametersMultiReturn(&moDouble, &moInt, &moString);
        printf( "noParametersMultiReturn returned " , *moDouble , " " , *moInt , " " , moString );
         *
         * Removed from WSDL for time being.
         */

    {
        xsdc__int_Array int_in;
        xsdc__double_Array double_in;
        xsdc__string_Array string_in;
        
        xsdc__double arrayOfDoubleValue[ARRAYSIZE];
        xsdc__int arrayOfIntValue[ARRAYSIZE];
        
        xsdc__double * arrayOfDouble[ARRAYSIZE];
        xsdc__int * arrayOfInt2[ARRAYSIZE];
        xsdc__string arrayOfString2[ARRAYSIZE];   
        
        for (x=0; x<ARRAYSIZE; x++)
        {
            arrayOfIntValue[x] = x+1;
            arrayOfInt2[x] = &arrayOfIntValue[x];
        }
        
        int_in.m_Array = arrayOfInt2;
        int_in.m_Size  = ARRAYSIZE;
        int_in.m_Type  = XSDC_INT;
        
        for (x=0; x<ARRAYSIZE; x++)
        {
            arrayOfDoubleValue[x] = (xsdc__double)x+71.15656;
            arrayOfDouble[x] = &arrayOfDoubleValue[x];
        }

        double_in.m_Array = arrayOfDouble;
        double_in.m_Size  = ARRAYSIZE;
        double_in.m_Type  = XSDC_DOUBLE;
        
        arrayOfString2[0] = str1;
        arrayOfString2[1] = str2;

        string_in.m_Array = arrayOfString2;
        string_in.m_Size  = ARRAYSIZE;
        string_in.m_Type  = XSDC_STRING;
        
        printf( "multiArrayParametersIntReturn\n" );
        npr = multiArrayParametersIntReturn(ws, &int_in, &double_in, &string_in);
        printf( "multiArrayParametersIntReturn returned %d\n" , npr );
    }

    {
        ComplexType2 ct2;
        ComplexType2* ctr;
        
        ct2.ctLong = (xsdc__long)98765432;
        ct2.ctIntArray = &intArray;
        ct2.ctString = "Complex2";
        ct2.ctComplex = &ct;
    
        printf( "complexParameterComplexReturn\n" );
        ctr = complexParameterComplexReturn(ws, &ct2);
        printf( "complexParameterComplexReturn returned %s\n" , ctr->ctString );
        Axis_Delete_ComplexType2(ctr, 0);
    
        ct2.ctLong = (xsdc__long)22222222;
        ct2.ctString = NULL;
        ct2.ctComplex = NULL;
    
        printf( "complexParameterComplexReturn with nil parameters\n" );
        ctr = complexParameterComplexReturn(ws, &ct2);
        printf( "complexParameterComplexReturn with nil parameters returned %lld\n" , ctr->ctLong );
        Axis_Delete_ComplexType2(ctr, 0);
    }

    destroy_InOut_stub(ws);
    

    printf("---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

