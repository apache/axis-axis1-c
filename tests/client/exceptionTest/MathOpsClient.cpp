#include "gen_src/MathOps.h"
#include <axis/server/AxisException.h>
#include <ctype.h>

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
        int p3 = 0;
	int i1=0, i2=0;
        int iResult;
        char* pcDetail;

	if (argc < 7)
	{
		PrintUsage();
	}
	else
	{
		server = argv[1];
		port = argv[2];
	}

	op = argv[3];
	p1 = argv[4];
	p2 = argv[5];
        p3 = atoi(argv[6]);

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
	        printf("Sending Requests to Server http://%s:%s ........\n\n", server, port);
                switch(p3)
                {
                    case 0:
                        /* Sends a normal request. the result should be the division of
                         *  two numbers the user has provided
                         */
	                 sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
                         break;
            
                    case 1:
                        /* Service name is missing. The message
                         *  Exception : AxisSoapException:Soap action is empty
                         *  should be returned to the user.
                         */
	                 sprintf(endpoint, "http://%s:%s/axis", server, port);
                         break;
          
                   case 2: 
                       /* Service name is wrong. The message
                        * Exception : AxisWsddException:Requested service not found
                        * should be returned to the user.
                        */
	                sprintf(endpoint, "http://%s:%s/axis/Math", server, port);
                        break;

                   case 3:
                         /* Service path is empty. The message  
                          * The corresponding http fail message
                          * should be returned to the user.
                          */
	                sprintf(endpoint, "http://%s:%s/", server, port);
                        break;

                   case 4:
                        /* Exception : AxisTransportException:Unexpected string
                         * received. Most probably server returned an empty stream
                         */
	                sprintf(endpoint, "", server, port);
	                //sprintf(endpoint, "http://%s:%s", server, port);
                        break;
                 
                   default:
                        printf("Invalide option for the last parameter\n\n");
                        return 0;
                }
	        //sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
	        MathOps ws(endpoint);
		iResult = ws.div(i1, i2);		
                printf("Result is:%d\n", iResult);
            }
            catch(AxisException& e)
            {
                printf("Exception : %s\n", e.what());
            }
            catch(exception& e)
            {
		printf("Unknown exception has occured\n");
            }
            catch(...)
            {
		printf("Unknown exception has occured\n");
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
	printf("Usage :\n MathOps <server> <port> <operation> <parameter> <parameter> <parameter>\n\n");
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
