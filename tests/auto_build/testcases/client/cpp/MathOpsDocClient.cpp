#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/MathOps";
	const char* server="localhost";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
	int iResult;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		MathOps ws(endpoint);

		op = "div";/*Operation name*/
		i1 = 10;/*First parameter*/
		i2 = 5;/*Second parameter*/

		if (strcmp(op, "div") == 0)
		{
			iResult = ws.div(i1, i2);		
			cout << "Result is:" << iResult << endl;
		}
		else 
		{
			cout << "Invalid operation "<< op<< endl<<endl;
			PrintUsage();
		}
	}
	catch(AxisException& e)
	{
	    cout << e.what()<<endl;
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << e.what() << endl;
	}
	catch(...)
	{
	    cout << "Unspecified exception has occured" << endl;
	}
	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}

void PrintUsage()
{
	cout << "Usage :\n MathOps <url>"<<endl<<endl;
	exit(1);
}

bool IsNumber(const char* p)
{
	for (int x=0; x < strlen(p); x++)
	{
		if (!isdigit(p[x])) return false;
	}
	return true;
}
