#include "MathOps.h"
#include <axis/server/AxisException.hpp>
#include <ctype.h>

void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	const char* url="http://localhost:80/axis/MathOps";
	const char* op = 0;
	char* p1 = 0;
	const char* p2 = 0;
	int p3 = 0;
	int i1=0, i2=0;
	int iResult;
	char* pcDetail;

	url = argv[1];

	op = "div";
	
	i1 = 10;
	i2 = 5;

	if (strcmp(op, "div") == 0)
	{
	    for(p3 = 0; p3 < 3; p3++)
	    {
		try
		{     
		    switch(p3)
		    {
			case 0:
			    /* Sends a normal request. the result should be the division of
			     *  two numbers the user has provided
			     */
			    //sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
			    sprintf(endpoint, "%s", url);
			    break;
	    
			case 1:
			    /* Service name is missing. The message
			     *  Exception : AxisSoapException:Soap action is empty
			     *  should be returned to the user.
			     */
			    //sprintf(endpoint, "http://%s:%s/axis", server, port);
			    sprintf(endpoint, "%s", url);
			    p1 = strrchr(endpoint, '/');
			    *p1 = (char)NULL; // Set a NULL at the last '/' char to strip the service endpoint interface
			    break;
	  
		       case 2: 
			   /* Service name is wrong. The message
			    * Exception : AxisWsddException:Requested service not found
			    * should be returned to the user.
			    */
			    //sprintf(endpoint, "http://%s:%s/axis/Math", server, port);
			    sprintf(endpoint, "%s", url);
			    p1 = endpoint + (strlen(endpoint) - 3);
			    *p1 = (char)NULL; // Set a NULL to strip the last 3 chars
			    break;

		       case 3:
			     /* Service path is empty. The message  
			      * The corresponding http fail message
			      * should be returned to the user.
			      */
			    /*sprintf(endpoint, "http://%s:%s/", server, port);*/
			    printf("This test has been temporarily terminated" \
			    " due to an unresolved bug\n");
			    exit(0); /* This is temporary code*/
			    break;

		       case 4:
			    /* Exception : AxisTransportException:Unexpected string
			     * received. Most probably server returned an empty stream
			     */
			    sprintf(endpoint, "", server, port);
			    //sprintf(endpoint, "http://%s:%s", server, port);
			    break;
		 
		       default:
			    printf("Invalid option for the last parameter\n\n");
			    return 0;
		    }
		    //sprintf(endpoint, "http://%s:%s/axis/MathOps", server, port);
		    printf("ENDPOINT = %s\n", endpoint);
		    MathOps ws(endpoint);
		    iResult = ws.div(i1, i2);		
		    printf("Result is:%d\n", iResult);
		}
		catch(AxisException& e)
		{
		    //printf("%s\n", e.what());
		    printf("AxisException has occured\n");
		}
		catch(exception& e)
		{
		    printf("Unknown exception has occured\n");
		}
		catch(...)
		{
		    printf("Unspecified exception has occured\n");
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
	printf("Usage :\n MathOps <url>\n\n");
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
