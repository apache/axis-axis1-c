#include "Calculator.h"
#include <axis/AxisGenException.hpp>
#include <iostream>

bool IsNumber(const char* p);

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | div number1 number2 [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL
	<<
	"\n    Could use http://localhost:8080/axis/services/echo to test with Axis Java."
	<< endl;
}

int main(int argc, char* argv[])
{
	char endpoint[256];
    char original[256];
	const char* server="localhost";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
    int iResult;
    char* pcDetail;
    pcDetail = 0;

    // Set default service URL
    sprintf (endpoint, "https://localhost:443/axis/Calculator");
    sprintf(original, "https://localhost:443/axis/Calculator");

	try
    {
    if( argc ==1 )
    {
        usage(argv[0], endpoint);
        return 2;
    }

    if (argc > 1)
    {
        if(!strncmp (argv[1], "-", 1))
	    {
            // Check for - only so that it works for 
            //-?, -h or --help; -anything 

            usage(argv[0], endpoint);
            return 2;
	    }
        //less than minimum number of args OR greater than maximum number of args
       	else if (argc < 4 || argc > 5)
    	{
		    usage(argv[0], endpoint);
            return 2;
    	}
        else if (argc == 5)
        {
            sprintf(endpoint, argv[4]);      
        }
    }

	cout << endl << " Using service at " << endpoint << endl << endl;
	Calculator ws(endpoint);

	op = argv[1];
	p1 = argv[2];
	p2 = argv[3];

	if (!IsNumber(p1))
	{
		printf("Invalid value for first <parameter>\n\n");
		usage(original, argv[4]);
        return 2;
	}
	if (!IsNumber(p2))
	{
		printf("Invalid value for second <parameter>\n\n");
		usage(original, argv[4]);
        return 2;
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
		usage(original, argv[4]);
        return 2;
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

bool IsNumber(const char* p)
{
	for (int x=0; x < strlen(p); x++)
	{
		if (!isdigit(p[x])) return false;
	}
	return true;
}
