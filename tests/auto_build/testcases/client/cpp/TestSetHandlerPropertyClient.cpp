/* 
 *****************************************************************************
 * This test tests the functionality of setHandlerProperty() of Stub class.
 * Test Logic
 * Set a value for a property and and get it's value in Handler and also
 * set the value for a property in handler and get that value in Client.
 *
 * The test is supposed to be passed when values set in client are 
 * received in handler and vice versa.
 *****************************************************************************
 */

#include "Calculator.hpp"
#include<iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		char buffer[100];
		char* pbuff=buffer; 
		
		ws.setHandlerProperty("prop1", (void*)"value1", 7);
		ws.setHandlerProperty("prop2", &pbuff, 100);
		
		iResult = ws.add(2,3);
		cout << iResult << endl;
		cout << "value of prop2 printed in client is = " << buffer << endl;
	
	}
	catch(AxisException& e)
	{
	    printf("Exception : %s\n", e.what());
	}
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n" );
	}
	catch(...)
	{
	    printf("Unknown exception has occured\n" );
	}
	cout << "---------------- TEST COMPLETE ----------------" << endl;
	return 0;
}


