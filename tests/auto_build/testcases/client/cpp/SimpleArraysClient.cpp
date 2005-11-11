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


#include "SimpleArrays.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

using namespace std;

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	const char* url="http://localhost:80/axis/SimpleArrays";
	char endpoint[256];

	if(argc>1)
		url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		SimpleArrays ws(endpoint);

		xsd__boolean_Array boolean_in;
		xsd__boolean_Array* boolean_out;
		xsd__short_Array short_in;
		//xsd__byte_Array byte_in;
		//xsd__byte_Array byte_out;
		xsd__short_Array* short_out;
		xsd__int_Array int_in;
		xsd__int_Array* int_out;
		xsd__long_Array long_in;
		xsd__long_Array* long_out;
		xsd__float_Array float_in;
		xsd__float_Array* float_out;
		xsd__double_Array double_in;
		xsd__double_Array* double_out;
		xsd__string_Array string_in;
		xsd__string_Array* string_out;


		/* Test a boolean array */
		xsd__boolean ** booleanInArray = new xsd__boolean*[ARRAYSIZE];
		int x = 0;
		for (x=0; x<ARRAYSIZE; x++)
		{
            booleanInArray[x] = new xsd__boolean((xsd__boolean)x);			
		}
		boolean_in.set(booleanInArray,ARRAYSIZE);
		cout << "invoking echoBooleanArray..."<<endl;
		boolean_out = ws.echoBooleanArray(&boolean_in);
		int outputSize=0;
		const xsd__boolean ** booleanOutArray = boolean_out->get(outputSize);
		if(outputSize > 0)
			if(*( booleanOutArray[0]) == (xsd__boolean)0)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;

		 // Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete booleanInArray[deleteIndex];
        }
        delete [] booleanInArray;

		/* Test a byte array - that is directly rather than as base64Binary */
		/*byte_in.m_Array = new xsd__byte[ARRAYSIZE];
		byte_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			byte_in.m_Array[x] = (xsd__byte)x+31;
		}
		cout << "invoking echoByteArray..."<<endl;
		byte_out = ws.echoByteArray(byte_in);
		if(byte_out.m_Size > 0)
			if(byte_out.m_Array[0] == (xsd__byte)31)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		
		*/
		/* Test an short array */
                /*
		short_in.m_Array = new xsd__short[ARRAYSIZE];
		short_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			short_in.m_Array[x] = x+250;
		}
		cout << "invoking echoIntArray..."<<endl;
		short_out = ws.echoIntArray(short_in);
		if(short_out.m_Size > 0)
			if(short_out.m_Array[0] == 250)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		
                */
		/* Test an int array */
		xsd__int ** intInArray = new xsd__int*[ARRAYSIZE];		
		for (x=0; x<ARRAYSIZE; x++)
		{
            intInArray[x] = new xsd__int(x+1);
			
		}
		int_in.set(intInArray,ARRAYSIZE);
		cout << "invoking echoIntArray..."<<endl;
		int_out = ws.echoIntArray(&int_in);
		outputSize = 0;
		const xsd__int **intOutArray =int_out->get(outputSize);
		if(outputSize > 0)
			if(*(intOutArray[0]) == 1)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;

		for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete intInArray[deleteIndex];
        }
        delete [] intInArray;


		/* Test a long array */
		xsd__long ** longInArray = new xsd__long*[ARRAYSIZE];        
		for (x=0; x<ARRAYSIZE; x++)
		{
            longInArray[x] = new xsd__long(x+ 200001);
			
		}
		long_in.set(longInArray,ARRAYSIZE);
		cout << "invoking echoLongArray..."<<endl;
		long_out = ws.echoLongArray(&long_in);
		outputSize = 0;
		const xsd__long **longOutArray = long_out->get(outputSize);
		if(outputSize > 0)
			if(*(longOutArray[0]) == (xsd__long)200001)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		

		// Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete longInArray[deleteIndex];
        }
        delete [] longInArray;

		/* Test a float array */
		xsd__float **floatInArray = new xsd__float*[ARRAYSIZE];
        
		for (x=0; x<ARRAYSIZE; x++)
		{
            floatInArray[x] = new xsd__float(x+ 11.111);
			
		}
        float_in.set(floatInArray,ARRAYSIZE);
		cout << "invoking echoFloatArray..."<<endl;
		float_out = ws.echoFloatArray(&float_in);
		outputSize =0;
		const xsd__float **floatOutArray=float_out->get(outputSize);
		if(outputSize > 0)
			if(*(floatOutArray[0]) == (xsd__float)11.111)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;	

		// Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete floatInArray[deleteIndex];
        }
        delete [] floatInArray;

		/* Test a double array */
		xsd__double ** doubleInArray=new xsd__double*[ARRAYSIZE];
		
		for (x=0; x<ARRAYSIZE; x++)
		{
            doubleInArray[x] = new xsd__double(x+71.15656);
			
		}
		double_in.set(doubleInArray,ARRAYSIZE);
		cout << "invoking echoDoubleArray..."<<endl;
		double_out = ws.echoDoubleArray(&double_in);
		outputSize = 0;
		const xsd__double ** doubleOutArray = double_out->get(outputSize);

		if(outputSize > 0)
			if(*(doubleOutArray[0]) == (xsd__double)71.15656)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;	

		// Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete doubleInArray[deleteIndex];
        }
        delete [] doubleInArray;

		/* Test a string array */
		static char* str1 = "Apache";
		static char* str2 = "Axis C++";
		xsd__string * stringInArray = new xsd__string[ARRAYSIZE];		
		stringInArray[0] = "Apache";
		stringInArray[1] = "Axis C++";
		string_in.set(stringInArray,ARRAYSIZE);
		cout << "invoking echoStringArray..."<<endl;
		string_out = ws.echoStringArray(&string_in);
		outputSize =0;
		const xsd__string * stringOutArray = string_out->get(outputSize);
		if(outputSize > 0)
			if(strcmp(stringOutArray[0], str1) == 0)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		

				bSuccess = true;
	}
	catch(AxisException& e)
	{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
				{
					bSilent = true;
				}
			}
			else
			{
				iRetryIterationCount = 0;
			}

            if( !bSilent)
			{
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured"<<endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured"<<endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}

