#include "Calculator.h"
#include <axis/AxisGenException.hpp>
#include <ctype.h>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	const char* op = 0;
	int i1=0, i2=0;
	int iResult;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);

		op = "add";
		i1 = 2;
		i2 = 3;

		if (strcmp(op, "add") == 0)
		{
			iResult = ws.add(i1, i2);
			printf("%d\n", iResult);
		}
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
	return 0;
}

void PrintUsage()
{
	printf("Usage :\n Calculator <url>\n\n");
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
