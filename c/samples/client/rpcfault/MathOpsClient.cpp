#include "MathOps.h"
#include <axis/server/AxisException.h>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
        int iResult;
        char* pcDetail;

	if (argc < 6)
	{
		PrintUsage();
	}
	else
	{
		server = argv[1];
		port = argv[2];
	}
	printf("Sending Requests to Server http://%s:%s ........\n\n", server, port);
	sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
	MathOps ws(endpoint);

	op = argv[3];
	p1 = argv[4];
	p2 = argv[5];

	if (!IsNumber(p1))
	{
		printf("Invalid value for first <parameter>\n\n");
		PrintUsage();
	}
	if (!IsNumber(p2))
	{
		printf("Invalid value for second <parameter>\n\n");
		PrintUsage();
	}
	
	i1 = atoi(p1);
	i2 = atoi(p2);

	if (strcmp(op, "div") == 0)
	{
            try
            {
		iResult = ws.div(i1, i2);		
                printf("Result is:%d\n", iResult);
            }
            catch(AxisDivByZeroException& e)
            {
                printf("Exception : %s\n", e.what());
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
	for (int x=0; x < strlen(p); x++)
	{
		if (!isdigit(p[x])) return false;
	}
	return true;
}
