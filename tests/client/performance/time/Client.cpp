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
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>

#ifdef WIN32
#else
#include <sys/times.h>
#include <unistd.h>
#endif


#include <axis/AxisException.hpp>
#include "./gen_src/InteropTestPortType.hpp"

using namespace std;

#define STRING_TO_SEND "HelloWorld"

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | message_size [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    message_size   Size of the message sent in chars / 10\n"
        << "                   (i.e. If you say 5, then 50 chars would be sent).\n"
        << "                   Default is 10*10.\n"
	<< "    service_url    URL of the service.\n"
	<< "                   Default service URL is assumed to be " << defaultURL
	<< "\n                   Could use http://localhost:8080/axis/services/echo to test with Axis Java."
	<< endl;
}


int
main (int argc, char *argv[])
{
    int length = 10;
    char endpoint[256];

    // Set default service URL
    sprintf (endpoint, "http://localhost/axis/base");
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
	    length = atoi(argv[1]);
	}
        
        if (argc > 2)
            sprintf (endpoint, argv[2]);

	cout << endl << " Using service at " << endpoint << endl << endl;

	InteropTestPortType ws (endpoint);

        //ws.setTransportTimeout(2);

        // Prepare the string to be sent 
        char* buffer = new char[ length + 1];
        char c = 'A';
        memset(buffer, c, length);
        buffer[length] = '\0';
        
        //printf("%s\n", buffer);

        //char* buffer = new char[ length * strlen(STRING_TO_SEND) + 1];
        //buffer[0] = '\0';
        //for (int i = 0; i < length; i++ )
        //    strcat(buffer, STRING_TO_SEND);
	
	// Time mesurement stuff
	time_t startTime;
        time_t endTime;

	time( &startTime );

        char* echoStringResult = ws.echoString(buffer);

        //printf("%s\n", echoStringResult);

	time( &endTime );
        printf( "Time spent to invoke method ws.echoString(buffer); = %lf s\n", difftime( endTime, startTime ) );

	if (0 == strcmp(echoStringResult, buffer))
	    printf ("successful\n");
	else
	    printf ("failed\n");

        // Clean memory 
        if (echoStringResult)
            free(echoStringResult);

        delete [] buffer;

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
    tms timesSpent;
    times(&timesSpent);

    printf( "User time               = %ld clock ticks\n", timesSpent.tms_utime );
    printf( "System time             = %ld clock ticks\n", timesSpent.tms_stime);
    printf( "User time of children   = %ld clock ticks\n", timesSpent.tms_cutime);
    printf( "System time of children = %ld clock ticks\n", timesSpent.tms_cstime);
    printf( "Processor time used     = %ld clock ticks\n", clock());
    printf( "Number of clock ticks per second = %ld clock ticks/s\n", sysconf(_SC_CLK_TCK) );
#endif

    return 0;
}
