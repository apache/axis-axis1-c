
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
		xsd__string_Array strArray;
		xsd__int_Array intArray;
		SimpleArrays simpleArrays;
		ComplexType1 complexType1_1;
		ComplexType1 complexType1_2;
		ComplexType1_Array complexType1Array;

		strArray.m_Size = ARRAYSIZE;
		strArray.m_Array = new xsd__string[ARRAYSIZE];
		strArray.m_Array[0] = "Apache";
		strArray.m_Array[1] = "Axis C++";

        xsd__int * arrayOfInt = new xsd__int[ARRAYSIZE];
		intArray.m_Size = ARRAYSIZE;
		intArray.m_Array = new xsd__int*[ARRAYSIZE];
        arrayOfInt[0] = 6;
		intArray.m_Array[0] = &arrayOfInt[0];
        arrayOfInt[1] = 7;
		intArray.m_Array[1] = &arrayOfInt[1];

		simpleArrays.stringArray = strArray;
		simpleArrays.intArray = intArray;

		complexType1_1.simpleArrays = &simpleArrays;
		complexType1_1.ct1_string = "Hello";
		complexType1_1.ct1_int = 13;
		complexType1_2.simpleArrays = &simpleArrays;
		complexType1_2.ct1_string = "World";
		complexType1_2.ct1_int = 27;

		complexType1Array.m_Size = ARRAYSIZE;
		complexType1Array.m_Array = new ComplexType1*[ARRAYSIZE];
		complexType1Array.m_Array[0] = &complexType1_1;
		complexType1Array.m_Array[1] = &complexType1_2;

		complexType2.complexType1Array = complexType1Array;

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

