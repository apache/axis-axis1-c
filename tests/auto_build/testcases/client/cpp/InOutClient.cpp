#include "InOut.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

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

		xsd__int_Array intArray;
		intArray.m_Array = new xsd__int[3];
		intArray.m_Size = 3;
		intArray.m_Array[0]=37;
		intArray.m_Array[1]=0;
		intArray.m_Array[2]=43;

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
		cnt.ctLong = (xsd__long)87654321;
		cnt.ctString = NULL;
		cnt.ctIntArray = intArray;

		cout << "multiComplexParametersNilIntReturn" << endl;
		mcpir = ws.multiComplexParametersNilIntReturn(NULL, &cnt, NULL, NULL, stringArray);
		cout << "multiComplexParametersNilIntReturn returned " << mcpir << endl;

		/* Commented out as there is a bug in WSDL2Ws.
		 * AXISCPP-565 is the Jira against this problem.
         *
		cout << "noParametersMultiReturn" << endl;
		ws.noParametersMultiReturn(&moDouble, &moInt, &moString);
		cout << "noParametersMultiReturn returned " << *moDouble << " " << *moInt << " " << moString << endl;
		 *
		 * Removed from WSDL for time being.
		 */

        int_in.m_Array = new xsd__int[ARRAYSIZE];
        int_in.m_Size = ARRAYSIZE;
        for (int x=0; x<ARRAYSIZE; x++)
        {
            int_in.m_Array[x] = x+1;
        }

        double_in.m_Array = new xsd__double[ARRAYSIZE];
        double_in.m_Size = ARRAYSIZE;
        for (int x=0; x<ARRAYSIZE; x++)
        {
            double_in.m_Array[x] = (xsd__double)x+71.15656;
        }

        string_in.m_Array = new xsd__string[ARRAYSIZE];
        string_in.m_Size = ARRAYSIZE;
        string_in.m_Array[0] = str1;
        string_in.m_Array[1] = str2;

		cout << "multiArrayParametersIntReturn" << endl;
		int mapir = ws.multiArrayParametersIntReturn(int_in, double_in, string_in);
		cout << "multiArrayParametersIntReturn returned " << mapir << endl;

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

