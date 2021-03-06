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

#include "InOut.hpp"
#include <axis/AxisException.hpp>
#include <iostream>
#include "CommonClientTestCode.hpp"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/InOut";

    static char* str1 = "Apache";
    static char* str2 = "Axis C++";
    
    int x = 0;
    int npr;

    if(argc>1)
            url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        InOut ws(endpoint);

        cout << "noParametersNoReturn" << endl;
        ws.noParametersNoReturn();
        cout << "noParametersNoReturn returned" << endl;

        cout << "noParametersIntReturn" << endl;
        npr = ws.noParametersIntReturn();
        cout << "noParametersIntReturn returned " << npr << endl;

        cout << "multiParametersNoReturn" << endl;
        ws.multiParametersNoReturn("Hey dude", 69, (xsd__double)17.19);
        cout << "multiParametersNoReturn returned" << endl;


        // test multiParametersMultiReturn
        xsd__string outValue0 = "";
        xsd__int outValue1 = 0;
        xsd__double outValue2 = 0;

        cout << "multiParametersMultiReturn" << endl;
        ws.multiParametersMultiReturn("Hey dude", 69, (xsd__double)17.19, &outValue0, &outValue1, &outValue2);
        cout << "multiParametersMultiReturn returned " << outValue0 << " , " << outValue1 << " , " << outValue2
          <<endl;

        //...........................................................

        xsd__int * arrayOfInt[3];
        xsd__int_Array intArray;
        xsd__string_Array stringArray;
        xsd__string arrayOfString[3];
        
        ComplexType1 ct;
                
        arrayOfInt[0] = new xsd__int(37);
        arrayOfInt[1] = new xsd__int(0);
        arrayOfInt[2] = new xsd__int(43);
        intArray.set(arrayOfInt,3);

        arrayOfString[0]="One";
        arrayOfString[1]="Two";
        arrayOfString[2]="Three";
        stringArray.set(arrayOfString,3);


        ct.ctLong = (xsd__long)87654321;
        ct.ctString = "World";
        ct.setctIntArray(&intArray);

        cout << "multiComplexParametersIntReturn" << endl;
        npr = ws.multiComplexParametersIntReturn("Hello", &ct, 27, 13.31, &stringArray);
        cout << "multiComplexParametersIntReturn returned " << npr << endl;

        //test multiComplexParametersMultiComplexReturn

        xsd__string OutValue0 = "";
        ComplexType1* OutValue1;
        xsd__int outValue22 = 0;
        xsd__double outValue33 = 0;

        cout << "multiComplexParametersMultiComplexReturn" << endl;
        ws.multiComplexParametersMultiComplexReturn("Hello", &ct, 27, 13.31, &stringArray, 
                                                    &OutValue0, &OutValue1, &outValue22, &outValue33);
        cout << "multiComplexParametersMultiComplexReturn returned " << OutValue0 << " , " 
                 << OutValue1->ctString <<  endl;

        //..............................................................................


        arrayOfString[0]="Four";
        arrayOfString[1]=NULL;
        arrayOfString[2]="Six";
        stringArray.set(arrayOfString,3);

        ComplexNilType1 cnt;
        xsd__long longValue = 87654321;
        cnt.ctLong = &longValue;
        cnt.ctString = NULL;
        cnt.setctIntArray(&intArray);

        cout << "multiComplexParametersNilIntReturn" << endl;
        npr = ws.multiComplexParametersNilIntReturn(NULL, &cnt, NULL, NULL, &stringArray);
        cout << "multiComplexParametersNilIntReturn returned " << npr << endl;

            /* Commented out as there is a bug in WSDL2Ws.
             * AXISCPP-565 is the Jira against this problem.
            xsd__double* moDouble;
            xsd__int* moInt;
            xsd__string moString;
            cout << "noParametersMultiReturn" << endl;
            ws.noParametersMultiReturn(&moDouble, &moInt, &moString);
            cout << "noParametersMultiReturn returned " << *moDouble << " " << *moInt << " " << moString << endl;
             *
             * Removed from WSDL for time being.
             */


        xsd__int_Array int_in;
        xsd__double_Array double_in;
        xsd__string_Array string_in;
        
        xsd__double * arrayOfDouble[ARRAYSIZE];
        xsd__int * arrayOfInt2[ARRAYSIZE];
        xsd__string arrayOfString2[ARRAYSIZE];        
        
        for (x=0; x<ARRAYSIZE; x++)
            arrayOfInt2[x] = new xsd__int(x+1);
        int_in.set(arrayOfInt2,ARRAYSIZE);

        for (x=0; x<ARRAYSIZE; x++)
            arrayOfDouble[x] = new xsd__double((xsd__double)x+71.15656);
        double_in.set(arrayOfDouble,ARRAYSIZE);

        arrayOfString2[0] = str1;
        arrayOfString2[1] = str2;
        string_in.set(arrayOfString2,ARRAYSIZE);
        
        cout << "multiArrayParametersIntReturn" << endl;
        npr = ws.multiArrayParametersIntReturn(&int_in, &double_in, &string_in);
        cout << "multiArrayParametersIntReturn returned " << npr << endl;


        ComplexType2 ct2;
        ct2.ctLong = (xsd__long)98765432;
        ct2.setctIntArray(&intArray);
        ct2.ctString = "Complex2";
        ct2.ctComplex = &ct;
        ComplexType2* ctr;

        cout << "complexParameterComplexReturn" << endl;
        ctr = ws.complexParameterComplexReturn(&ct2);
        cout << "complexParameterComplexReturn returned " << ctr->ctString << endl;

        ct2.ctLong = (xsd__long)22222222;
        ct2.ctString = NULL;
        ct2.ctComplex = NULL;

        cout << "complexParameterComplexReturn with nil parameters" << endl;
        ctr = ws.complexParameterComplexReturn(&ct2);
        cout << "complexParameterComplexReturn with nil parameters returned " << ctr->ctLong << endl;

    }
    catch(AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << "Unknown exception has occured : " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}

