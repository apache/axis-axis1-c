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
 * @author Sanjaya Singharage (sanjayas@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#include <string>
#include <iostream>

#include <axis/AxisGenException.hpp>
#include "InteropTestPortType.h"

using namespace std;

#define ARRAYSIZE 2

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL
	<<
	"\n    Could use http://localhost:8080/axis/services/echo to test with Axis Java."
	<< endl;
}


int
main (int argc, char *argv[])
{
    int x;
    char buffer1[100];
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
	    sprintf (endpoint, argv[1]);
	}


	cout << endl << " Using service at " << endpoint << endl << endl;


    InteropTestPortType ws (endpoint, APTHTTP1_0);

	//testing echoString 
	printf ("invoking echoString...\n");
        char* echoStringResult = ws.echoString ("hello world");
	if (0 == strcmp (echoStringResult, "hello world"))
	    printf ("successful\n");
	else
	    printf ("failed\n");

        // Clean memory 
        if (echoStringResult)
            free(echoStringResult);

	// testing echoStringArray 
	xsd__string_Array arrstr;
	arrstr.m_Array = new char *[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	sprintf (buffer1, "%dth element of string array", 0);
	for (int i = 0; i < ARRAYSIZE; i++)
	{
	    arrstr.m_Array[i] = buffer1;
	}
	printf ("invoking echoStringArray...\n");
	xsd__string_Array arrstrResult = ws.echoStringArray (arrstr);
	if (arrstrResult.m_Array != NULL)
        {
	    printf ("successful\n");
            // Do stuff and clean memory
            for( int i = 0; i < arrstrResult.m_Size; i++ )
                free (arrstrResult.m_Array[i]);
            free(arrstrResult.m_Array);
        }
	else
	    printf ("failed\n");

        // Clean memory
        delete [] arrstr.m_Array;

        ws.setTransportProtocol(APTHTTP1_1);
	// testing echoInteger 
	printf ("invoking echoInteger...\n");
	if (ws.echoInteger (56) == 56)
	    printf ("successful\n");
	else
	    printf ("failed\n");

	// testing echoIntegerArray 
	xsd__int_Array arrint;
	arrint.m_Array = new int[ARRAYSIZE];
	arrint.m_Size = ARRAYSIZE;
	for (x = 0; x < ARRAYSIZE; x++)
	{
	    arrint.m_Array[x] = x;
	}
	printf ("invoking echoIntegerArray...\n");
	xsd__int_Array arrintResult = ws.echoIntegerArray (arrint);
	if (arrintResult.m_Array != NULL)
        {
	    printf ("successful\n");
            // Do stuff and clean memory
            free(arrintResult.m_Array);
	}
        else
	    printf ("failed\n");

        // Clean memory
        delete [] arrint.m_Array;

	// testing echoFloat 
	printf ("invoking echoFloat...\n");
	float fvalue = 1.4214;
	if (ws.echoFloat (fvalue) > 1.42)
	    printf ("successful\n");
	else
	    printf ("failed\n");

	// testing echoFloat 
	xsd__float_Array arrfloat;
	arrfloat.m_Array = new float[ARRAYSIZE];
	arrfloat.m_Size = ARRAYSIZE;
	for (x = 0; x < ARRAYSIZE; x++)
	{
	    arrfloat.m_Array[x] = 1.1111 * x;
	}
	printf ("invoking echoFloatArray...\n");
        xsd__float_Array arrfloatResult = ws.echoFloatArray (arrfloat);
	if (arrfloatResult.m_Array != NULL)
        {
	    printf ("successful\n");
            // Do stuff & clean memory
            // It is our responsibility to deallocate deserializer allocated memory
            free(arrfloatResult.m_Array);
        }
	else
	    printf ("failed\n");
        
        // Clean memory
        delete [] arrfloat.m_Array;

	// testing echo Struct
	SOAPStruct stct;
	stct.varFloat = 12345.7346345;
	stct.varInt = 5000;
	stct.varString = strdup ("This is string in SOAPStruct");
	printf ("invoking echoStruct...\n");
	SOAPStruct* stctResult = ws.echoStruct (&stct);
	if (stctResult != NULL)
        {
	    printf ("successful\n");
            // Do stuff and clean memory
            free(stctResult->varString);
            delete stctResult;
        }
	else
	    printf ("failed\n");

        // Clean memory 
        free(stct.varString);

	//testing echo Array of Struct
	SOAPStruct_Array arrstct;
	arrstct.m_Array = new SOAPStruct[ARRAYSIZE];
	arrstct.m_Size = ARRAYSIZE;
	for (x = 0; x < ARRAYSIZE; x++)
	{
	    arrstct.m_Array[x].varFloat = 1.1111 * x;
	    arrstct.m_Array[x].varInt = x;
	    sprintf (buffer1,
		     "varString of %dth element of SOAPStruct array", x);
	    arrstct.m_Array[x].varString = buffer1;
	}

	printf ("invoking echoStructArray...\n");
        SOAPStruct_Array arrstctResult = ws.echoStructArray (arrstct);
	if (arrstctResult.m_Array != NULL)
        {
	    printf ("successful\n");
            // Do stuff and clean memory
            for( int i = 0; i < arrstctResult.m_Size; i++ )
               free (arrstctResult.m_Array[i].varString);
            delete [] arrstctResult.m_Array;
        }
	else
	    printf ("failed\n");

        // Clean memory
        delete [] arrstct.m_Array;

	//testing echo void
	printf ("invoking echoVoid...\n");
	ws.echoVoid ();
	printf ("successful\n");

	//testing echo base 64 binary

	const char *bstr =
	    "some string that is sent encoded to either base64Binary or hexBinary";

	printf ("invoking echoBase64...\n");
	xsd__base64Binary bb;
	bb.__ptr = (unsigned char *) strdup (bstr);
	bb.__size = strlen (bstr);
	xsd__base64Binary bbResult = ws.echoBase64 (bb);
	if (bb.__size == bbResult.__size)
	{
	    printf ("successful\n");
            // Do stuff
	    printf ("Returned String :\n%s\n", bbResult.__ptr);
            // Clean memory
            free(bbResult.__ptr);
	}
	else
	    printf ("failed\n");

        // Clean memory
        free(bb.__ptr);

	time_t tim;
	time (&tim);
	tm *lt = gmtime (&tim);
	printf ("invoking echoDate...\n");
	if (memcmp (&ws.echoDate (*lt), lt, sizeof (tm)) == 0)
	    printf ("successful\n");
	else
	    printf ("failed\n");

	//testing echo hex binary

	printf ("invoking echoHexBinary...\n");
	xsd__hexBinary hb;
	hb.__ptr = (unsigned char *) strdup (bstr);
	hb.__size = strlen (bstr);
	xsd__hexBinary hbResult = ws.echoHexBinary (hb);
	if (hb.__size == hbResult.__size)
	{
	    printf ("successful\n");
            // Do stuff
	    printf ("Returned String :\n%s\n", hbResult.__ptr);
            // Clean memory
            free(hbResult.__ptr);
	}
	else
	    printf ("failed\n");

        // Clean memory
        free(hb.__ptr);

	//testing echo decimal
	printf ("invoking echoDecimal...\n");
	if (ws.echoDecimal (1234.567890) > 1234.56)
	    printf ("successful\n");
	else
	    printf ("failed\n");

	//testing echo boolean
	/*printf ("invoking echoBoolean...\n");
	if (ws.echoBoolean (true_) == true_)
	    printf ("successful\n");
	else
	    printf ("failed\n");
*/
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
