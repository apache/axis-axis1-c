#include "MathOps.hpp"
#include <axis/server/AxisException.hpp>
#include <ctype.h>

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
	char* pcDetail;

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
			printf("Result is:%d\n", iResult);
		}
		else 
		{
			printf("Invalid operation %s\n\n", op);
			PrintUsage();
		}
	}
	catch(AxisException& e)
	{
	    printf("%s\n", e.what());
	}
	catch(exception& e)
	{
	    printf("Unknown exception has occured\n");
	}
	catch(...)
	{
	    printf("Unspecified exception has occured\n");
	}
	
	return 0;
}

void PrintUsage()
{
	printf("Usage :\n MathOps <url>\n\n");
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
