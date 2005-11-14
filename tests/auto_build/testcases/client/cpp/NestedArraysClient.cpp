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
		xsd__int_Array baseArray1In;
        xsd__int ** baseArray1Vales = new xsd__int*[ARRAYSIZE];		
		baseArray1Vales[0] = new xsd__int(1);
        baseArray1Vales[1] = new xsd__int(2);
		baseArray1In.set(baseArray1Vales,ARRAYSIZE);
		baseArray1.item= &baseArray1In;

		xsd__int_Array baseArray2In;
        xsd__int ** baseArray2Vales = new xsd__int*[ARRAYSIZE];		
        baseArray2Vales[0] =new xsd__int(3);		
        baseArray2Vales[1] =new xsd__int(4);
		baseArray2In.set(baseArray2Vales,ARRAYSIZE);
		baseArray2.setitem(&baseArray2In);
		
		xsd__int_Array baseArray3In;
        xsd__int ** baseArray3Vales = new xsd__int*[ARRAYSIZE];		
        baseArray3Vales[0] = new xsd__int(5);		
        baseArray3Vales[1] = new xsd__int(6);
		baseArray3In.set(baseArray3Vales,ARRAYSIZE);
		baseArray3.setitem(&baseArray3In);
		
		xsd__int_Array baseArray4In;
        xsd__int ** baseArray4Vales = new xsd__int*[ARRAYSIZE];		
        baseArray4Vales[0] = new xsd__int(7);		
        baseArray4Vales[1] = new xsd__int(8);
		baseArray4In.set(baseArray4Vales,ARRAYSIZE);
		baseArray4.setitem(&baseArray4In);
		

		/* Set ArrayOf_xsd_int_Array into ArrayOfArrayOf_xsd_int */
		ArrayOf_xsd_int_Array sarray1;
		ArrayOf_xsd_int ** array1 = new ArrayOf_xsd_int*[ARRAYSIZE];		
		array1[0] = &baseArray1;
		array1[1] = &baseArray2;
		sarray1.set(array1,ARRAYSIZE);
		subArray1.setitem(&sarray1);
		
		ArrayOf_xsd_int_Array sarray2;
		ArrayOf_xsd_int ** array2 = new ArrayOf_xsd_int*[ARRAYSIZE];		
		array2[0] = &baseArray3;
		array2[1] = &baseArray4;
		sarray2.set(array2,ARRAYSIZE);
		subArray2.setitem(&sarray2);
		
		/* Set ArrayOfArrayOf_xsd_int into an Array of them */
		
		ArrayOfArrayOf_xsd_int ** pArray= new ArrayOfArrayOf_xsd_int*[ARRAYSIZE];		
		pArray[0]=&subArray1;
		pArray[1]=&subArray2;		
		parentArray.set(pArray,ARRAYSIZE);
		xsd__int_Array* response = ws->sendNestedArrays(&parentArray);
		int outputSize = 0;
		const xsd__int ** output = response->get(outputSize);		
		cout << *(output[0]) << " " << *(output[1]) << endl;		
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

