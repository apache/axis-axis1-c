
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
		xsd__boolean_Array boolean_out;
		xsd__short_Array short_in;
		//xsd__byte_Array byte_in;
		//xsd__byte_Array byte_out;
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
		boolean_in.m_Array = new xsd__boolean[ARRAYSIZE];
		boolean_in.m_Size = ARRAYSIZE;
        int x = 0;
		for (x=0; x<ARRAYSIZE; x++)
		{
			boolean_in.m_Array[x] = (xsd__boolean)x;
		}
		cout << "invoking echoBooleanArray..."<<endl;
		boolean_out = ws.echoBooleanArray(boolean_in);
		if(boolean_out.m_Size > 0)
			if(boolean_out.m_Array[0] == (xsd__boolean)0)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		

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
		int_in.m_Array = new xsd__int[ARRAYSIZE];
		int_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			int_in.m_Array[x] = x+1;
		}
		cout << "invoking echoIntArray..."<<endl;
		int_out = ws.echoIntArray(int_in);
		if(int_out.m_Size > 0)
			if(int_out.m_Array[0] == 1)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;

		/* Test a long array */
		long_in.m_Array = new xsd__long[ARRAYSIZE];
		long_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			long_in.m_Array[x] = (xsd__long)x+200001;
		}
		cout << "invoking echoLongArray..."<<endl;
		long_out = ws.echoLongArray(long_in);
		if(long_out.m_Size > 0)
			if(long_out.m_Array[0] == (xsd__long)200001)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		


		/* Test a float array */
		float_in.m_Array = new xsd__float[ARRAYSIZE];
		float_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			float_in.m_Array[x] = (xsd__float)x+11.111;
		}
		cout << "invoking echoFloatArray..."<<endl;
		float_out = ws.echoFloatArray(float_in);
		if(float_out.m_Size > 0)
			if(float_out.m_Array[0] == (xsd__float)11.111)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		

		/* Test a double array */
		double_in.m_Array = new xsd__double[ARRAYSIZE];
		double_in.m_Size = ARRAYSIZE;
		for (x=0; x<ARRAYSIZE; x++)
		{
			double_in.m_Array[x] = (xsd__double)x+71.15656;
		}
		cout << "invoking echoDoubleArray..."<<endl;
		double_out = ws.echoDoubleArray(double_in);
		if(double_out.m_Size > 0)
			if(double_out.m_Array[0] == (xsd__double)71.15656)
				cout << "successful "<<endl;
			else
				cout << "failed "<<endl;		
		else
			cout << "failed "<<endl;		

		/* Test a string array */
		static char* str1 = "Apache";
		static char* str2 = "Axis C++";
		string_in.m_Array = new xsd__string[ARRAYSIZE];
		string_in.m_Size = ARRAYSIZE;
		string_in.m_Array[0] = str1;
		string_in.m_Array[1] = str2;
		cout << "invoking echoStringArray..."<<endl;
		string_out = ws.echoStringArray(string_in);
		if(string_out.m_Size > 0)
			if(strcmp(string_out.m_Array[0], str1) == 0)
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

