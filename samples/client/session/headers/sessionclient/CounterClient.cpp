/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 *
 */

#include "./gen_src/Counter.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

bool IsNumber(const char* p);

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | count number1 [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL
	<<
	"\n    Could use http://localhost:8080/axis/services/CounterService to test with Axis Java."
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
    sprintf (endpoint, "http://localhost/axis/services/CounterService");
    sprintf(original, "http://localhost/axis/services/CounterService");

	try    {
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
       	else if (argc < 3 || argc > 4)
    	{
		    usage(argv[0], endpoint);
            return 2;
    	}
        else if (argc == 4)
        {
            sprintf(endpoint, argv[3]);      
        }
    }

	cout << endl << " Using service at " << endpoint << endl << endl;
	Counter ws(endpoint);

	op = argv[1];
	p1 = argv[2];

	if (!IsNumber(p1))
	{
		printf("Invalid value for first <parameter>\n\n");
		usage(original, argv[4]);
        return 2;
	}
	
	i1 = atoi(p1);

	if (strcmp(op, "count") == 0)
	{
                iResult = ws.count(i1);
                ws.getFaultDetail(&pcDetail);
                printf("%d\n", iResult);
                /*printf("pcDetail:%s\n", pcDetail);*/
                iResult = ws.count(i1);
                printf("Second Result : %d\n", iResult);
                iResult = ws.count(i1);
                printf("Third Result : %d\n", iResult);
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
