// ArrayClient.cpp : Defines the entry point for the console application.i
//
#include <string>
using namespace std;

#include "ArrayTestPortType.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* url="http://localhost:80/axis/MathOps";
	const char* server="localhost";
	const char* port="80";
	url = argv[1];
	try
	{
		sprintf(endpoint, "%s", url);
		ArrayTestPortType ws(endpoint);
		//testing echoIntArray
		IntArrayType arrin;
		arrin.intItem.m_Array = new int[ARRAYSIZE];
		arrin.intItem.m_Size = ARRAYSIZE;
		for (x=0;x<ARRAYSIZE;x++)
		{
			arrin.intItem.m_Array[x] = x;
		}
		cout << "invoking echoIntArray..."<<endl;
		if (ws.echoIntArray(&arrin)->intItem.m_Array != NULL)
			cout << "successful "<<endl;
		else
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
