// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "RefTestPortType.hpp" 
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* url="http://localhost:80/axis/RefTest";
	const char* server="localhost";
	const char* port="80";
	url = argv[1];
	try
	{
		sprintf(endpoint, "%s", url);
		RefTestPortType ws(endpoint);

		cout << "invoking echoInt.."<<endl;
		IntType refint;
		refint.intItem =56;

		if ((ws.echoInt(&refint))->intItem == 56)
		{
			cout << "successful"<<endl;
		}
		else
		{
			cout << "failed "<<endl;
		}

	}
	catch(AxisException& e)
	{
	    cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
	    cout << "Unexpected exception has occured" << e.what() << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}
