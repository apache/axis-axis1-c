#include "PrimitiveAndArray.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";

	if(argc>1)
		url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		PrimitiveAndArray* ws = new PrimitiveAndArray(endpoint);

		xsd__int single;
		xsd__int_Array intArray;
		ComplexReturn* response;

		single=37;

        xsd__int * arrayOfInt = new xsd__int[ARRAYSIZE];
		intArray.m_Size = ARRAYSIZE;
		intArray.m_Array = new xsd__int*[ARRAYSIZE];
		arrayOfInt[0] = 6;
        intArray.m_Array[0] = &arrayOfInt[0];
        arrayOfInt[1] = 7;
		intArray.m_Array[1] = &arrayOfInt[1];

		response = ws->sendPrimitiveAndArray(single, intArray);
		cout << response->returnInt << " " << *(response->returnArray.m_Array[0]) << " " << *(response->returnArray.m_Array[1]) << endl;

		single=43;
        arrayOfInt[0] = 13;
        arrayOfInt[1] = 17;
		response = ws->sendArrayAndPrimitive(intArray, single);
		cout << response->returnInt << " " << *(response->returnArray.m_Array[0]) << " " << *(response->returnArray.m_Array[1]) << endl;

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

