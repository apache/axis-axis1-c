#include "Calculator.h"
#include <axis/AxisGenException.h>

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
        pcDetail = 0;

	if (argc < 6)
	{
		PrintUsage();
	}
	else
	{
		server = argv[1];
		port = argv[2];
	}
	try
        {
	printf("Sending Requests to Server http://%s:%s ........\n\n", server, port);
	sprintf(endpoint, "http://%s:%s/axis/Calculator", server, port);
	Calculator ws(endpoint);

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

	if (strcmp(op, "add") == 0)
	{
                iResult = ws.add(i1, i2);
                ws.getFaultDetail(&pcDetail);
                printf("%d\n", iResult);
                /*printf("pcDetail:%s\n", pcDetail);*/
	}
	else 	if (strcmp(op, "sub") == 0)
	{
		iResult = ws.sub(i1, i2);
        printf("%d\n", iResult);
		ws.getFaultDetail(&pcDetail);
        /*printf("pcDetail:%s\n", pcDetail);*/
	}
	else 	if (strcmp(op, "mul") == 0)
	{
	        iResult = ws.mul(i1, i2);
            printf("%d\n", iResult);
			ws.getFaultDetail(&pcDetail);
            /*printf("pcDetail:%s\n", pcDetail);*/
	}
	else 	if (strcmp(op, "div") == 0)
	{
		iResult = ws.div(i1, i2);
        printf("%d\n", iResult);
		ws.getFaultDetail(&pcDetail);
        /*printf("pcDetail:%s\n", pcDetail);*/
	}
	else 
	{
		printf("Invalid operation %s\n\n", op);
		PrintUsage();
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
	printf("Usage :\n Calculator <server> <port> <operation> <parameter> <parameter>\n\n");
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
