#include "MathOps.h"
#include <axis/server/AxisException.h>
#include <ctype.h>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* server="localhost";
	const char* url="http://localhost:80/axis/MathOps";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
        int iResult;
        char* pcDetail;

	url = argv[1];

	sprintf(endpoint, "%s", url);
	MathOps ws(endpoint);

	op = "div";

	if (strcmp(op, "div") == 0)
	{
            for(int i = 0; i < 4; i++)
            {
                printf("%d\n", i);
                switch(i)
                {
                    case 0: i1 = 10; i2 = 5; break;
                    case 1: i1 = 10; i2 = 0; break;
                    case 2: i1 = 1000; i2 = 5; break;
                    case 3: i1 = 10; i2 = -5; break;
                }
                try
                {
		    iResult = ws.div(i1, i2);		
                    printf("Result is:%d\n", iResult);
                }
                catch(MathOpsService_AxisClientException& e)
                {
                    printf("%s\n", e.what());
                }
                catch(AxisException& e)
                {
                    printf("Exception : %s\n", e.what());
                }
                catch(exception& e)
                {
                }
                catch(...)
                {
                }
            }
	}
	else 
	{
		printf("Invalid operation %s\n\n", op);
		PrintUsage();
	}
	return 0;
}

void PrintUsage()
{
	printf("Usage :\n MathOps <server> <port> <operation> <parameter> <parameter>\n\n");
	exit(1);
}

bool IsNumber(const char* p)
{
	for (int x=1; x < strlen(p); x++)
	{
		if (!isdigit(p[x])) return false;
	}
	return true;
}
