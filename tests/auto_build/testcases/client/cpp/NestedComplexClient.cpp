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
 * NestedComplex
 * 
 * Send a complex data type, ComplexType2, which has a data element of an
 * array of a complex data type, ComplexType1. The ComplexType1 data type
 * has a xsd:string element, a xsd:int element and a complex data type element
 * SimpleArrays. The SimpleArrays complex data type has a xsd:string array and
 * a xsd_int array.
 *
 * ComplexType2
 *   + ComplexType1[]
 *       + string
 *       + int
 *       + SimpleArrays
 *           + string[]
 *           + int[]
 *
 * This is an echo type service so the response should be the same as the request.
 *
 * Author: Andrew Perry
 *
 */

#include "NestedComplex.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2
#define NEWCOPY(ptr,str) {ptr=new char[strlen(str)+1]; strcpy(ptr,str);}

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/NestedComplex";

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		NestedComplex ws(endpoint);

		ComplexType2 complexType2;
		ComplexType2* response;
		SimpleArrays *simpleArrays1 = new SimpleArrays;
		SimpleArrays *simpleArrays2 = new SimpleArrays;
		SimpleArrays *simpleArrays[2] = {simpleArrays1, simpleArrays2};
		ComplexType1 *complexType1_1 = new ComplexType1;
		ComplexType1 *complexType1_2 = new ComplexType1;

		for (int i=0; i<2; i++)
		{
			xsd__string_Array *strArray = &(simpleArrays[i]->stringArray);
			xsd__int_Array *intArray = &(simpleArrays[i]->intArray);

			strArray->m_Size = ARRAYSIZE;
			strArray->m_Array = new xsd__string[ARRAYSIZE];
			NEWCOPY(strArray->m_Array[0], "Apache");
			NEWCOPY(strArray->m_Array[1], "Axis C++");

			intArray->m_Size = ARRAYSIZE;
			intArray->m_Array = new xsd__int*[ARRAYSIZE];
			intArray->m_Array[0] = new int;
			*(intArray->m_Array[0]) = 6;
			intArray->m_Array[1] = new int;
			*(intArray->m_Array[1]) = 7;
		}

		complexType1_1->simpleArrays = simpleArrays1;
		NEWCOPY(complexType1_1->ct1_string, "Hello");
		complexType1_1->ct1_int = 13;
		complexType1_2->simpleArrays = simpleArrays2;
		NEWCOPY(complexType1_2->ct1_string, "World");
		complexType1_2->ct1_int = 27;

		complexType2.complexType1Array.m_Size = ARRAYSIZE;
		complexType2.complexType1Array.m_Array = new ComplexType1*[ARRAYSIZE];
		complexType2.complexType1Array.m_Array[0] = complexType1_1;
		complexType2.complexType1Array.m_Array[1] = complexType1_2;

		response = ws.echoNestedComplex(&complexType2);
		cout << response->complexType1Array.m_Array[0]->ct1_string << endl;
		cout << response->complexType1Array.m_Array[0]->ct1_int << endl;
		cout << response->complexType1Array.m_Array[0]->simpleArrays->stringArray.m_Array[0] << " ";
		cout << response->complexType1Array.m_Array[0]->simpleArrays->stringArray.m_Array[1] << endl;
		cout << *(response->complexType1Array.m_Array[0]->simpleArrays->intArray.m_Array[0]) << " ";
		cout << *(response->complexType1Array.m_Array[0]->simpleArrays->intArray.m_Array[1]) << endl;
		cout << response->complexType1Array.m_Array[1]->ct1_string << endl;
		cout << response->complexType1Array.m_Array[1]->ct1_int << endl;
		cout << response->complexType1Array.m_Array[1]->simpleArrays->stringArray.m_Array[0] << " ";
		cout << response->complexType1Array.m_Array[1]->simpleArrays->stringArray.m_Array[1] << endl;
		cout << *(response->complexType1Array.m_Array[1]->simpleArrays->intArray.m_Array[0]) << " ";
		cout << *(response->complexType1Array.m_Array[1]->simpleArrays->intArray.m_Array[1]) << endl;

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

