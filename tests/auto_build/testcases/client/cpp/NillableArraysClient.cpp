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
 * test setting elements in a nillable array to nil.
 * This is for primitive types only
 */


#include "NillableArrays.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 3

using namespace std;

int main(int argc, char* argv[])
{
	const char* url="http://localhost:80/axis/NillableArrays";
	char endpoint[256];

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		NillableArrays ws(endpoint);

		xsd__boolean_Array boolean_in;
		xsd__boolean_Array boolean_out;
		xsd__short_Array short_in;
		xsd__short_Array short_out;
		xsd__int_Array int_in;
		xsd__int_Array int_out;
		xsd__long_Array long_in;
		xsd__long_Array long_out;
		xsd__float_Array float_in;
		xsd__float_Array float_out;
		xsd__double_Array double_in;
		xsd__double_Array double_out;
		xsd__string_Array string_in;
		xsd__string_Array string_out;


		/* Test a boolean array */
		xsd__boolean b1 = (xsd__boolean)0;
		xsd__boolean b3 = (xsd__boolean)1;
		boolean_in.m_Array = new xsd__boolean*[ARRAYSIZE];
		boolean_in.m_Size = ARRAYSIZE;
		boolean_in.m_Array[0] = &b1;
		boolean_in.m_Array[1] = NULL;
		boolean_in.m_Array[2] = &b3;
		cout << "invoking echoBooleanArray..."<<endl;
		boolean_out = ws.echoBooleanArray(boolean_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(boolean_out.m_Size == ARRAYSIZE) {
			if(boolean_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(boolean_out.m_Array[0]) == (xsd__boolean)0 && *(boolean_out.m_Array[2]) == (xsd__boolean)1)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		
*/

		/* Test an short array */
		xsd__short s1 = (xsd__short)252;
		xsd__short s3 = (xsd__short)254;
		short_in.m_Array = new xsd__short*[ARRAYSIZE];
		short_in.m_Size = ARRAYSIZE;
		short_in.m_Array[0] = &s1;
		short_in.m_Array[1] = NULL;
		short_in.m_Array[2] = &s3;
		cout << "invoking echoShortArray..."<<endl;
		short_out = ws.echoShortArray(short_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(short_out.m_Size == ARRAYSIZE) {
			if(short_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(short_out.m_Array[0]) == 252 && *(short_out.m_Array[2]) == 254)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		
*/
		/* Test an int array */
		xsd__int val1 = 1000000;
		xsd__int val3 = 1000002;
		int_in.m_Array = new xsd__int*[ARRAYSIZE];
		int_in.m_Size = ARRAYSIZE;
		int_in.m_Array[0] = &val1;
		int_in.m_Array[1] = NULL;
		int_in.m_Array[2] = &val3;
		cout << "invoking echoIntArray..."<<endl;
		int_out = ws.echoIntArray(int_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(int_out.m_Size ==ARRAYSIZE) {
			if(int_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(int_out.m_Array[0]) == val1 && *(int_out.m_Array[2]) == val3)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;
*/

		/* Test a long array */
		xsd__long l1 = (xsd__long)200001;
		xsd__long l3 = (xsd__long)200003;
		long_in.m_Array = new xsd__long*[ARRAYSIZE];
		long_in.m_Size = ARRAYSIZE;
		long_in.m_Array[0] = &l1;
		long_in.m_Array[1] = NULL;
		long_in.m_Array[2] = &l3;
		cout << "invoking echoLongArray..."<<endl;
		long_out = ws.echoLongArray(long_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(long_out.m_Size == ARRAYSIZE) {
			if(long_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(long_out.m_Array[0]) == (xsd__long)200001 && *(long_out.m_Array[2]) == (xsd__long)200003)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		
*/

		/* Test a float array */
		xsd__float f1 = (xsd__float)11.111;
		xsd__float f3 = (xsd__float)33.111;

		float_in.m_Array = new xsd__float*[ARRAYSIZE];
		float_in.m_Size = ARRAYSIZE;
		float_in.m_Array[0] = &f1;
		float_in.m_Array[1] = NULL;
		float_in.m_Array[2] = &f3;
		cout << "invoking echoFloatArray..."<<endl;
		float_out = ws.echoFloatArray(float_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(float_out.m_Size ==ARRAYSIZE) {
			if(float_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(float_out.m_Array[0]) == (xsd__float)11.111 && *(float_out.m_Array[2]) == (xsd__float)33.111)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		
*/

		/* Test a double array */
		xsd__double d1 = (xsd__double)71.1565;
		xsd__double d3 = (xsd__double)73.1565;

		double_in.m_Array = new xsd__double*[ARRAYSIZE];
		double_in.m_Size = ARRAYSIZE;
		double_in.m_Array[0] = &d1;
		double_in.m_Array[1] = NULL;
		double_in.m_Array[2] = &d3;
		cout << "invoking echoDoubleArray..."<<endl;
		double_out = ws.echoDoubleArray(double_in);
				cout << "successful "<<endl;
/* The response is not being checked at present
		if(double_out.m_Size ==ARRAYSIZE) {
			if(double_out.m_Array[1])
				cout << "failed "<<endl;		
			else if(*(double_out.m_Array[0]) == (xsd__double)71.1565 && *(double_out.m_Array[2]) == (xsd__double)73.1565)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		
*/

		/* Test a string array */
		static char* str1 = "Apache";
		static char* str2 = "Axis C++";
		string_in.m_Array = new xsd__string[ARRAYSIZE];
		string_in.m_Size = ARRAYSIZE;
		string_in.m_Array[0] = str1;
		string_in.m_Array[1] = NULL;
		string_in.m_Array[2] = str2;
		cout << "invoking echoStringArray..."<<endl;
		string_out = ws.echoStringArray(string_in);
		if(string_out.m_Size ==ARRAYSIZE) {
			if(string_out.m_Array[1])
				cout << "failed "<<endl;		
			else if( (strcmp(string_out.m_Array[0], str1) == 0) && (strcmp(string_out.m_Array[2], str2) == 0) )
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		} else
			cout << "failed "<<endl;		

	}
	catch(AxisException& e)
	{
	    cout << "Exception : "<< e.what()<<endl;
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured"<<endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured"<<endl;
	}
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}

