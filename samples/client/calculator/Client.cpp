// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Calculator.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

bool IsNumber (const char *p);

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | div number1 number2 [service_url]] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL << endl;
}

int
main (int argc, char *argv[])
{
    char endpoint[256];
    char original[256];
    const char *server = "localhost";
    const char *port = "80";
    const char *op = 0;
    const char *p1 = 0;
    const char *p2 = 0;
    int i1 = 0, i2 = 0;
    int iResult;

    // Set default service URL
    sprintf (endpoint, "http://localhost/axis/Calculator");
    sprintf (original, endpoint);

    try
    {
	if (argc == 1)
	{
	    usage (argv[0], endpoint);
	    return 2;
	}

	if (argc > 1)
	{
	    if (!strncmp (argv[1], "-", 1))
	    {
		// Check for - only so that it works for 
		//-?, -h or --help; -anything 

		usage (argv[0], endpoint);
		return 2;
	    }
	    //less than minimum number of args OR greater than maximum number of args
	    else if (argc < 4 || argc > 5)
	    {
		usage (argv[0], endpoint);
		return 2;
	    }
	    else if (argc == 5)
	    {
		sprintf (endpoint, argv[4]);
	    }
	}

	Calculator ws (endpoint);

	op = argv[1];
	p1 = argv[2];
	p2 = argv[3];

	if (!IsNumber (p1))
	{
	    printf ("Invalid value for first <parameter> %s\n\n", p1);
	    usage (argv[0], original);
	    return 2;
	}
	if (!IsNumber (p2))
	{
	    printf ("Invalid value for second <parameter> %s\n\n", p2);
	    usage (argv[0], original);
	    return 2;
	}

	i1 = atoi (p1);
	i2 = atoi (p2);

	if (strcmp (op, "add") == 0)
	{
	    iResult = ws.add (i1, i2);
	    printf ("%d\n", iResult);
	}
	else if (strcmp (op, "sub") == 0)
	{
	    iResult = ws.sub (i1, i2);
	    printf ("%d\n", iResult);
	}
	else if (strcmp (op, "mul") == 0)
	{
	    iResult = ws.mul (i1, i2);
	    printf ("%d\n", iResult);
	}
	else if (strcmp (op, "div") == 0)
	{
	    iResult = ws.div (i1, i2);
	    printf ("%d\n", iResult);
	}
	else
	{
	    printf ("Invalid operation %s\n\n", op);
	    usage (argv[0], original);
	    return 2;
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
    return 0;
}

bool
IsNumber (const char *p)
{
    for (int x = 0; x < strlen (p); x++)
    {
	if (!isdigit (p[x]))
	    return false;
    }
    return true;
}
