// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
#include <iostream>
using namespace std;

#include "InteropTestPortType.hpp"

#define ARRAYSIZE 2

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL << endl;
}


int
main (int argc, char *argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    sprintf (endpoint, "http://%s:%s/axis/base", server, port);

    if (argc > 1)
    {
	// Watch for special case help request
	if (!strncmp (argv[1], "-", 1))	// Check for - only so that it works for
	    //-?, -h or --help; -anything
	{
	    usage (argv[0], endpoint);
	    return 2;
	}
	sprintf (endpoint, argv[1]);
    }

    bool bSuccess = false;
    int iRetryIterationCount = 3;

    do
    {
	try
	{
	    InteropTestPortType ws (endpoint, APTHTTP1_1);

	    //testing echoString 
	    printf ("invoking echoString...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoString");
	    string bigstring;
	    for (int ii = 0; ii < 2; ii++)
	    {
		bigstring += "hello world ";
	    }
	    strcpy (buffer1, bigstring.c_str ());

	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoString");

        char* cpResult = ws.echoString ("hello world");
	    if (0 == strcmp (cpResult, "hello world"))
		printf ("successful\n");
	    else
		printf ("failed\n");

        delete [] cpResult;

	    // testing echoStringArray 
	    xsd__string_Array arrstr;
	    arrstr.m_Array = new char *[ARRAYSIZE];
	    arrstr.m_Size = ARRAYSIZE;
	    sprintf (buffer1, "%dth element of string array", 0);
	    for (int i = 0; i < ARRAYSIZE; i++)
	    {
		arrstr.m_Array[i] = buffer1;
	    }

	    ws.setTransportProperty ("SOAPAction",
				     "InteropBase#echoStringArray");
	    printf ("invoking echoStringArray...\n");

        char** arrstrResult = ws.echoStringArray (arrstr).m_Array;
        
	    if (arrstrResult != NULL)
		printf ("successful\n");
	    else
		printf ("failed\n");

        delete [] arrstr.m_Array;
        delete [] arrstrResult;

	    // testing echoInteger 
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoInteger");
	    printf ("invoking echoInteger...\n");
	    if (ws.echoInteger (56) == 56)
		printf ("successful\n");
	    else
		printf ("failed\n");

	    // testing echoIntegerArray 
	    xsd__int_Array arrint;
	    arrint.m_Array = new int *[ARRAYSIZE];
	    arrint.m_Size = ARRAYSIZE;
	    int iToSend[ARRAYSIZE];

	    for (x = 0; x < ARRAYSIZE; x++)
	    {
		iToSend[x] = x;
		arrint.m_Array[x] = &iToSend[x];
	    }
	    ws.setTransportProperty ("SOAPAction",
				     "InteropBase#echoIntegerArray");
	    printf ("invoking echoIntegerArray...\n");
	    if (ws.echoIntegerArray (arrint).m_Array != NULL)
		printf ("successful\n");
	    else
		printf ("failed\n");

        delete [] arrint.m_Array;

	    // testing echoFloat 
	    printf ("invoking echoFloat...\n");
	    float fvalue = 1.4214;
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoFloat");
	    if (ws.echoFloat (fvalue) > 1.42)
		printf ("successful\n");
	    else
		printf ("failed\n");

	    // testing echoFloat 
	    xsd__float_Array arrfloat;
	    arrfloat.m_Array = new float *[ARRAYSIZE];
	    arrfloat.m_Size = ARRAYSIZE;
	    float fToSend[ARRAYSIZE];
	    for (x = 0; x < ARRAYSIZE; x++)
	    {
		fToSend[x] = 1.1111 * x;
		arrfloat.m_Array[x] = &fToSend[x];
	    }
	    ws.setTransportProperty ("SOAPAction",
				     "InteropBase#echoFloatArray");
	    printf ("invoking echoFloatArray...\n");
	    if (ws.echoFloatArray (arrfloat).m_Array != NULL)
		printf ("successful\n");
	    else
		printf ("failed\n");

        delete [] arrfloat.m_Array;

	    // testing echo Struct
	    SOAPStruct stct;
		xsd__int integer = 5000;
		xsd__float floatVal = 12345.7346345;
	    stct.varFloat = &floatVal;
	    stct.varInt = &integer;
	    stct.varString = strdup ("This is string in SOAPStruct");
	    printf ("invoking echoStruct...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoStruct");
	    if (ws.echoStruct (&stct) != NULL)
		printf ("successful\n");
	    else
		printf ("failed\n");

        free(stct.varString);

	    //testing echo Array of Struct
	    SOAPStruct_Array arrstct;
	    arrstct.m_Array = new SOAPStruct[ARRAYSIZE];
	    arrstct.m_Size = ARRAYSIZE;
	    for (x = 0; x < ARRAYSIZE; x++)
	    {
			integer = x;
			floatVal = 1.1111 * x;
		arrstct.m_Array[x].varFloat = &floatVal;
		arrstct.m_Array[x].varInt = &integer;
		sprintf (buffer1,
			 "varString of %dth element of SOAPStruct array", x);
		arrstct.m_Array[x].varString = buffer1;
	    }

	    //testing echo Struct Array
	    ws.setTransportProperty ("SOAPAction",
				     "InteropBase#echoStructArray");
	    printf ("invoking echoStructArray...\n");
	    SOAPStruct_Array arrstctResult = ws.echoStructArray (arrstct);
	    if (arrstctResult.m_Array != NULL)
		printf ("successful\n");
	    else
		printf ("failed\n");

        delete [] arrstct.m_Array;
        for( x = 0; x < arrstctResult.m_Size; x++)
            delete [] arrstctResult.m_Array[x].varString;
        delete [] arrstctResult.m_Array;

	    //testing echo void
	    printf ("invoking echoVoid...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoVoid");
	    ws.echoVoid ();
	    printf ("successful\n");

	    //testing echo base 64 binary
	    const char *bstr =
		"some string that is sent encoded to either base64Binary or hexBinary";

	    printf ("invoking echoBase64...\n");
	    xsd__base64Binary bb;
	    bb.__ptr = (unsigned char *) strdup (bstr);
	    bb.__size = strlen (bstr);
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoBase64");
	    xsd__base64Binary bbResult = ws.echoBase64 (bb);
	    if (bb.__size == bbResult.__size)
	    {
		printf ("successful\n");
		printf ("Returned String :\n%s\n", bbResult.__ptr);
	    }
	    else
		printf ("failed\n");
        
        free(bb.__ptr);
        delete [] bbResult.__ptr;

	    time_t tim;
	    time (&tim);
	    tm *lt = gmtime (&tim);
	    printf ("invoking echoDate...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoDate");
	    if (memcmp (&ws.echoDate (*lt), lt, sizeof (tm)) == 0)
		printf ("successful\n");
	    else
		printf ("failed\n");

	    //testing echo hex binary
	    printf ("invoking echoHexBinary...\n");
	    xsd__hexBinary hb;
	    hb.__ptr = (unsigned char *) strdup (bstr);
	    hb.__size = strlen (bstr);
	    ws.setTransportProperty ("SOAPAction",
				     "InteropBase#echoHexBinary");
	    xsd__hexBinary hbReturn = ws.echoHexBinary (hb);
	    if (hb.__size == hbReturn.__size)
	    {
		printf ("successful\n");
		printf ("Returned String :\n%s\n", hbReturn.__ptr);
	    }
	    else
		printf ("failed\n");

        free(hb.__ptr);
        delete [] hbReturn.__ptr;
	    //testing echo decimal
	    printf ("invoking echoDecimal...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoDecimal");
	    if (ws.echoDecimal (1234.567890) > 1234.56)
		printf ("successful\n");
	    else
		printf ("failed\n");

	    //testing echo boolean
	    printf ("invoking echoBoolean...\n");
	    ws.setTransportProperty ("SOAPAction", "InteropBase#echoBoolean");
	    if (ws.echoBoolean (true_) == true_)
		printf ("successful\n");
	    else
		printf ("failed\n");

	    bSuccess = true;
	}
	catch (AxisException & e)
	{
	    bool bSilent = false;

	    if (e.getExceptionCode () ==
		CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
	    {
		if (iRetryIterationCount > 0)
		{
		    bSilent = true;
		}
	    }
	    else
	    {
		iRetryIterationCount = 0;
	    }

	    if (!bSilent)
	    {
		printf ("%s\n", e.what ());
	    }
	}
	catch (exception & e)
	{
	    printf ("%s\n", e.what ());
	}
	catch (...)
	{
	    printf ("Unknown exception has occured\n");
	}
	iRetryIterationCount--;
    }
    while (iRetryIterationCount > 0 && !bSuccess);
    //getchar();
    return 0;
}
