#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

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
				cout << "Trying to " << op << " " << i1 << " by " << i2 << endl;
				iResult = ws.div(i1, i2);		
				cout << "Result is " << iResult << endl;
			}
			catch(MathOpsService_AxisClientException &me)
			{
				cout << "MathOpsService_AxisClientException: ";
				ISoapFault *fault = (ISoapFault *)me.getFault();
				const char* pcCmplxFaultName = fault->getCmplxFaultObjectName().c_str();
				if(0 == strcmp("DivByZeroStruct", pcCmplxFaultName))
				{
					DivByZeroStruct* p = (DivByZeroStruct *)fault->getCmplxFaultObject();
					cout << "DivByZeroStruct Fault: \"" << p->varString << "\", " << p->varInt << ", " << p->varFloat << endl;
            	}
				else if(0 == strcmp("SpecialDetailStruct", pcCmplxFaultName))
				{
					SpecialDetailStruct* p = (SpecialDetailStruct *)fault->getCmplxFaultObject();
					cout << "SpecialDetailStruct Fault: \"" << p->varString << "\"" << endl;
				}
				else if(0 == strcmp("OutOfBoundStruct", pcCmplxFaultName))
				{
					OutOfBoundStruct* p = (OutOfBoundStruct *)fault->getCmplxFaultObject();
					cout << "OutOfBoundStruct Fault: \"" << p->varString << "\", " << p->varInt << ", \"" << p->specialDetail->varString << "\"" << endl;
				}
			}
			catch(AxisException& e)
			{
				printf("AxisException: %s\n", e.what());
			}
			catch(exception& e)
			{
				printf("Unknown Exception: \n");
			}
			catch(...)
			{
				printf("Unspecified Exception: \n");
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
	printf("Usage :\n FaultMappingDoc <url>\n\n");
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
