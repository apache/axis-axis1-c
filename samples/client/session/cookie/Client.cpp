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

#include <iostream>
#include <axis/AxisException.hpp>
#include "./gen_src/Total.hpp"

using namespace std;

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | inc_size [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    inc_size       Step size for increment operation. Default is 10.\n"
	<< "    service_url    URL of the service.\n"
	<< "                   Default service URL is assumed to be " << defaultURL
	<< endl;
}


int
main (int argc, char *argv[])
{
    double increment = 10.0;
    char endpoint[256];

    // Set default service URL
    sprintf (endpoint, "http://localhost:9090/axis/services/Total");

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
	    increment = atoi(argv[1]);
	}
        
        if (argc > 2)
            sprintf (endpoint, argv[2]);

	cout << endl << " Using service at " << endpoint << endl << endl;

	Total ws (endpoint, APTHTTP1_0);

        ws.setTransportTimeout(2);

        double incResult = 0.0;
       
        ws.setMaintainSession(true); 
        cout << "setMaintainSession = true\n";
        cout << "Result = " << ws.inc(increment) << endl;
        cout << "Result = " << ws.inc(increment) << endl;
        ws.setMaintainSession(false); 
        cout << "setMaintainSession = false\n";
        cout << "Result = " << ws.inc(increment) << endl;
        cout << "Result = " << ws.inc(increment) << endl;
        ws.setMaintainSession(true); 
        cout << "setMaintainSession = true\n";
        cout << "Result = " << ws.inc(increment) << endl;
        cout << "Result = " << ws.inc(increment) << endl;

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

    return 0;
}
