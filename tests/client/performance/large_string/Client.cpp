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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>

#ifdef WIN32
#else
#endif

#include <axis/AxisException.h>
#include "./gen_src/InteropTestPortType.h"

using namespace std;

#define STRING_TO_SEND "HelloWorld"

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | iterations [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    iterations     no of invocations of echoString. Each echoString will\n"
    << "                   use a string the size of the current iteration number \n"
	<< "    service_url    URL of the service.\n"
	<< "                   Default service URL is assumed to be \n" 
    << "                   " << defaultURL
	<< "\n                   Could use http://localhost:8080/axis/services/echo \n"
    << "                   " << "to test with Axis Java."
	<< endl;
}

int main (int argc, char *argv[])
{
    int length = 10;
    char endpoint[256];
    int charlength = 1;
    char * sendbuf = NULL;
    char* echoStringResult = NULL;

    // Set default service URL
    sprintf (endpoint, "http://localhost:8080/axis/base");
    // Could use http://localhost:8080/axis/services/echo to test with Axis Java

    try
    {

	    if (argc > 1)
	    {
	        // Watch for special case help request
	        if (!strncmp (argv[1], "-", 1)) // Check for - only so that it works for 
                                                //-?, -h or --help; -anything 
	        {
		    usage (argv[0], endpoint);
		    return 2;
	        }
	        charlength = atoi(argv[1]);
	    }
        
        if (argc > 2)
            sprintf (endpoint, argv[2]);

	    cout << endl << " Using service at " << endpoint << endl << endl;

	    InteropTestPortType ws (endpoint);

        ws.setTransportTimeout(2);



        for(int i=1;i<=charlength;i++)
        {
            sendbuf = (char*)malloc(sizeof(char)*(i+1));
            memset(sendbuf, 's', i);
            *(sendbuf+i) = '\0';

            echoStringResult = ws.echoString(sendbuf);
            if (0 == strcmp(echoStringResult, sendbuf))            
            {
                printf("%d%s", i, "length string Successful\n");
            }
            else
            {
                printf("%d%s", i, "length string FAILED\n");
            }
            printf("%s\n",echoStringResult );
            free (sendbuf);
            sendbuf = NULL;

            if(echoStringResult)
                free(echoStringResult);
         }


    }
    catch (AxisException & e)
    {
	    printf ("Exception : %s\n", e.what ());
    }
    catch (exception & e)
    {
	    printf ("Unknown exception has occured\n");
    }
    catch (...)
    {
    	printf ("Unknown exception has occured\n");
    }

    // System vs User time stuff
#ifdef WIN32
#else // Linux/Unix
#endif

    return 0;
}
