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

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		InOut ws(endpoint);

		xsd__int_Array int_in;
		xsd__double_Array double_in; 
		xsd__string_Array string_in;
		xsd__double* moDouble;
		xsd__int* moInt;
		xsd__string moString;

        static char* str1 = "Apache";
        static char* str2 = "Axis C++";

		cout << "noParametersNoReturn" << endl;
		ws.noParametersNoReturn();
		cout << "noParametersNoReturn returned" << endl;

		cout << "noParametersIntReturn" << endl;
		int npir = ws.noParametersIntReturn();
		cout << "noParametersIntReturn returned " << npir << endl;

		cout << "multiParametersNoReturn" << endl;
		ws.multiParametersNoReturn("Hey dude", 69, (xsd__double)17.19);
		cout << "multiParametersNoReturn returned" << endl;

        xsd__int * arrayOfInt = new xsd__int[3];
		xsd__int_Array intArray;
		intArray.m_Array = new xsd__int*[3];
		intArray.m_Size = 3;
        arrayOfInt[0] = 37;
		intArray.m_Array[0] = &arrayOfInt[0];
        arrayOfInt[1] = 0;
		intArray.m_Array[1]=&arrayOfInt[1];
        arrayOfInt[2] = 43;
		intArray.m_Array[2]=&arrayOfInt[2];

		xsd__string_Array stringArray;
		stringArray.m_Array = new xsd__string[3];
		stringArray.m_Size = 3;
		stringArray.m_Array[0]="One";
		stringArray.m_Array[1]="Two";
		stringArray.m_Array[2]="Three";

		ComplexType1 ct;
		ct.ctLong = (xsd__long)87654321;
		ct.ctString = "World";
		ct.ctIntArray = intArray;

		cout << "multiComplexParametersIntReturn" << endl;
		int mcpir = ws.multiComplexParametersIntReturn("Hello", &ct, 27, 13.31, stringArray);
		cout << "multiComplexParametersIntReturn returned " << mcpir << endl;

		stringArray.m_Array[0]="Four";
		stringArray.m_Array[1]=NULL;
		stringArray.m_Array[2]="Six";

		ComplexNilType1 cnt;
        xsd__long * longValue = new xsd__long(87654321);
		cnt.ctLong = longValue;
		cnt.ctString = NULL;
		cnt.ctIntArray = intArray;

		cout << "multiComplexParametersNilIntReturn" << endl;
		mcpir = ws.multiComplexParametersNilIntReturn(NULL, &cnt, NULL, NULL, stringArray);
		cout << "multiComplexParametersNilIntReturn returned " << mcpir << endl;

        delete longValue;

		/* Commented out as there is a bug in WSDL2Ws.
		 * AXISCPP-565 is the Jira against this problem.
         *
		cout << "noParametersMultiReturn" << endl;
		ws.noParametersMultiReturn(&moDouble, &moInt, &moString);
		cout << "noParametersMultiReturn returned " << *moDouble << " " << *moInt << " " << moString << endl;
		 *
		 * Removed from WSDL for time being.
		 */

        xsd__int * arrayOfInt2 = new xsd__int[ARRAYSIZE];
        int_in.m_Array = new xsd__int*[ARRAYSIZE];
        int_in.m_Size = ARRAYSIZE;
        int x = 0;
        for (x=0; x<ARRAYSIZE; x++)
        {
            arrayOfInt2[x] = x+1;
            int_in.m_Array[x] = &arrayOfInt2[x];
        }

        xsd__double * arrayOfDouble = new xsd__double[ARRAYSIZE];
        double_in.m_Array = new xsd__double*[ARRAYSIZE];
        double_in.m_Size = ARRAYSIZE;
        for (x=0; x<ARRAYSIZE; x++)
        {
            arrayOfDouble[x] = (xsd__double)x+71.15656;
            double_in.m_Array[x] = &arrayOfDouble[x];
        }

        string_in.m_Array = new xsd__string[ARRAYSIZE];
        string_in.m_Size = ARRAYSIZE;
        string_in.m_Array[0] = str1;
        string_in.m_Array[1] = str2;

		cout << "multiArrayParametersIntReturn" << endl;
		int mapir = ws.multiArrayParametersIntReturn(int_in, double_in, string_in);
		cout << "multiArrayParametersIntReturn returned " << mapir << endl;

		ComplexType2 ct2;
		ct2.ctLong = (xsd__long)98765432;
		ct2.ctIntArray = intArray;
		ct2.ctString = "Complex2";
		ct2.ctComplex = &ct;

		cout << "complexParameterComplexReturn" << endl;
		ComplexType2* ctr = ws.complexParameterComplexReturn(&ct2);
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
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}

