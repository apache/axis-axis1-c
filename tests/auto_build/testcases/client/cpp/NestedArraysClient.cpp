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

#include "NestedArrays.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/NestedArrays";

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		NestedArrays* ws = new NestedArrays(endpoint);

		/* These contain xsd__int_Array */
		ArrayOf_xsd_int baseArray1;
		ArrayOf_xsd_int baseArray2;
		ArrayOf_xsd_int baseArray3;
		ArrayOf_xsd_int baseArray4;

		/* These contain ArrayOf_xsd_int_Array */
		ArrayOfArrayOf_xsd_int subArray1;
		ArrayOfArrayOf_xsd_int subArray2;

		/* This is an array of ArrayOfArrayOf_xsd_int */
		ArrayOfArrayOf_xsd_int_Array parentArray;

		/* Set xsd__int_Array into ArrayOf_xsd_int */
        xsd__int * baseArray1Vales = new xsd__int[ARRAYSIZE];
		baseArray1.item.m_Array = new xsd__int*[ARRAYSIZE];
		baseArray1.item.m_Size = ARRAYSIZE;
        baseArray1Vales[0] = 1;
		baseArray1.item.m_Array[0] = &baseArray1Vales[0];
        baseArray1Vales[1] = 2;
		baseArray1.item.m_Array[1] = &baseArray1Vales[1];

        xsd__int * baseArray2Vales = new xsd__int[ARRAYSIZE];
		baseArray2.item.m_Array = new xsd__int*[ARRAYSIZE];
		baseArray2.item.m_Size = ARRAYSIZE;
        baseArray2Vales[0] = 3;
		baseArray2.item.m_Array[0] = &baseArray2Vales[0];
        baseArray2Vales[1] = 4;
		baseArray2.item.m_Array[1] = &baseArray2Vales[1];

        xsd__int * baseArray3Vales = new xsd__int[ARRAYSIZE];
		baseArray3.item.m_Array = new xsd__int*[ARRAYSIZE];
		baseArray3.item.m_Size = ARRAYSIZE;
        baseArray3Vales[0] = 5;
		baseArray3.item.m_Array[0] = &baseArray3Vales[0];
        baseArray3Vales[1] = 6;
		baseArray3.item.m_Array[1] = &baseArray3Vales[1];

        xsd__int * baseArray4Vales = new xsd__int[ARRAYSIZE];
		baseArray4.item.m_Array = new xsd__int*[ARRAYSIZE];
		baseArray4.item.m_Size = ARRAYSIZE;
        baseArray4Vales[0] = 7;
		baseArray4.item.m_Array[0] = &baseArray4Vales[0];
        baseArray4Vales[1] = 8;
		baseArray4.item.m_Array[1] = &baseArray4Vales[1];

		/* Set ArrayOf_xsd_int_Array into ArrayOfArrayOf_xsd_int */
		subArray1.item.m_Array = new ArrayOf_xsd_int[ARRAYSIZE];
		subArray1.item.m_Size = ARRAYSIZE;
		subArray1.item.m_Array[0] = baseArray1;
		subArray1.item.m_Array[1] = baseArray2;

		subArray2.item.m_Array = new ArrayOf_xsd_int[ARRAYSIZE];
		subArray2.item.m_Size = ARRAYSIZE;
		subArray2.item.m_Array[0] = baseArray3;
		subArray2.item.m_Array[1] = baseArray4;

		/* Set ArrayOfArrayOf_xsd_int into an Array of them */
		parentArray.m_Array = new ArrayOfArrayOf_xsd_int[ARRAYSIZE];
		parentArray.m_Size = ARRAYSIZE;
		parentArray.m_Array[0] = subArray1;
		parentArray.m_Array[1] = subArray2;

		xsd__int_Array response = ws->sendNestedArrays(parentArray);

		cout << *(response.m_Array[0]) << " " << *(response.m_Array[1]) << endl;

		delete ws;
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

