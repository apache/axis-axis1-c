#include "AxisBench.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

#ifndef WIN32
#include "sys/time.h"
#else
#include "sys/timeb.h"

  // Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
  // Cannot print an __int64 number with cout without this overloading
std::ostream & operator<< (std::ostream & os, __int64 i)
{
    char buf[20];
    sprintf (buf, "%I64d", i);
    os << buf;
    return os;
}

#endif

static bool verbose = false;
#include <stdlib.h>		// For malloc(), calloc(), strdup() and free()

// If we re-direct cout it will be to this ofstream
ofstream output_file;

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/bench"

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
    AxisBench *ws;

    BenchDataType *input = NULL;
    BenchDataType *output = NULL;
    xsd__unsignedByte *buffer = NULL;

    char endpoint[256];
    sprintf (endpoint, "%s", WSDL_DEFAULT_ENDPOINT);
    int returnValue = 1;	// Assume Failure


    bool bSuccess = false;
    int iRetryIterationCount = 3;
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
    do
    {
	try
	{
	    ws = new AxisBench (endpoint, APTHTTP1_1);


	    int request = 1;

	    input = new BenchDataType ();
	    input->count = 10;

	    BenchBasicDataType **ppBBDT =
		(BenchBasicDataType **) new BenchBasicDataType*[input->count];

#ifdef WIN32
	    __int64 ll = 10000;
#else
	    long long ll = 10000;
#endif

	    input->infos.m_Array = ppBBDT;

	    input->infos.m_Size = input->count;

	    time_t tim;
	    tim = 1100246323;
	    struct tm *temp = gmtime (&tim);
	    struct tm lt;
	    memcpy (&lt, temp, sizeof (struct tm));


	    buffer = (xsd__unsignedByte *) calloc (1, input->count + 2);
	    strcpy ((char *) buffer, "A");

	    for (int i = 0; i < input->count; i++)
	    {
		BenchBasicDataType *type = new BenchBasicDataType ();
		type->StringType = "StringType";
		type->IntegerType = 10 * (i + 1);
		type->DoubleType = 11.111 * (i + 1);
		type->BooleanType = true_;
		type->DateTimeType = lt;
		type->TimeType = lt;
		type->DateType = lt;
		type->IntType = (i + 1);
		type->ByteType = '1';
		type->DecimalType = 10 * (i + 1);
		type->FloatType =
		    (float) ((float) (11 * (i + 1)) / (float) 2.0);
		type->LongType = ll;
		type->QNameType = "toto";
		type->ShortType = (i + 1);
		type->Base64BinaryType.__size = i;
		type->Base64BinaryType.__ptr = buffer;
		type->HexBinary.__size = i;
		type->HexBinary.__ptr = buffer;

		if (i == 90)
		{
		    *ppBBDT = type;
		}
		else
		{
		    *ppBBDT = type;
		}

		ppBBDT++;

		if (ll == 0)
		{
		    ll = 1;
		}
		else
		{
		    ll += 10000;
		}

		strcat ((char *) buffer, "A");
	    }

	    int t1, t2;
#ifndef WIN32
	    struct timeval mstart;
	    struct timeval mstop;
	    gettimeofday (&mstart, NULL);
#else
	    struct timeb mstart;
	    struct timeb mstop;
	    ftime (&mstart);
#endif

	    for (int ii = 0; ii < request; ii++)
	    {
		if (output)
		{		// Samisa: memory management BP
		    for (int i = 0; i < output->infos.m_Size; i++)
			delete (BenchBasicDataType *) (output->infos.
						       m_Array[i]);
		    delete output;
		    output = NULL;
		}
		ws->setTransportProperty ("SOAPAction",
					  "AxisBench#doBenchRequest");
		output = ws->doBenchRequest (input);
	    }

	    free (buffer);

#ifndef WIN32
	    gettimeofday (&mstop, NULL);
	    t1 = mstart.tv_sec * 1000 + mstart.tv_usec / 1000;
	    t2 = mstop.tv_sec * 1000 + mstop.tv_usec / 1000;
#else
	    ftime (&mstop);
	    t1 = mstart.time * 1000 + mstart.millitm;
	    t2 = mstop.time * 1000 + mstop.millitm;
#endif

	    int total = t2 - t1;

	    if (ws->getStatus () == AXIS_FAIL)
		cout << "Failed" << endl;
	    else
	    {
		bSuccess = true;
		char dateTime[50];
		int i = 0;
		if (argc > 1)
		    i = output->count - 1;

		cout << "Input Count : " << input->count << endl;
		cout << "Count : " << output->count << endl;
		for (; i < output->count; i++)
		{
		    if (output->infos.m_Array[i] !=
			(BenchBasicDataType *) 0xcdcdcdcd)
		    {
			cout <<
			    " ----------------------------------------------"
			    << endl;
			cout << " StringType " << output->infos.m_Array[i]->
			    StringType << endl;
			cout << " IntType " << output->infos.m_Array[i]->
			    IntType << endl;
			cout << " IntegerType " << output->infos.m_Array[i]->
			    IntegerType << endl;
			cout << " DoubleType " << output->infos.m_Array[i]->
			    DoubleType << endl;
			cout << " BooleanType " << output->infos.m_Array[i]->
			    BooleanType << endl;
			strftime (dateTime, 50, "%a %b %d %H:%M:%S %Y",
				  &output->infos.m_Array[i]->DateTimeType);
			cout << " DateTimeType " << dateTime << endl;
			strftime (dateTime, 50, "%a %b %d %Y",
				  &output->infos.m_Array[i]->DateType);
			cout << " DateType " << dateTime << endl;
// This is being removed due to problem in some servers.
// See XSDTime or XSDTimeNil testcases for full validation of the xsd:time type
//            strftime(dateTime, 50, "%H:%M:%S", &output->infos.m_Array[i]->TimeType);
//                        cout << " TimeType " << dateTime << endl;
			cout << " ByteType " << output->infos.m_Array[i]->
			    ByteType << endl;
			cout << " DecimalType " << output->infos.m_Array[i]->
			    DecimalType << endl;
			cout << " FloatType " << output->infos.m_Array[i]->
			    FloatType << endl;
			cout << " LongType " << output->infos.m_Array[i]->
			    LongType << endl;
			cout << " QNameType " << output->infos.m_Array[i]->
			    QNameType << endl;
			cout << " ShortType " << output->infos.m_Array[i]->
			    ShortType << endl;

			cout << " Base64BinaryType " << output->infos.
			    m_Array[i]->Base64BinaryType.__size << endl;
			if (output->infos.m_Array[i]->Base64BinaryType.
			    __size > 0)
			{
			    cout << " Base64BinaryType " << output->infos.
				m_Array[i]->Base64BinaryType.__ptr << endl;
			}

			cout << " HexBinaryType " << output->infos.
			    m_Array[i]->HexBinary.__size << endl;
			if (output->infos.m_Array[i]->HexBinary.__size > 0)
			{
			    cout << " HexBinaryType " << output->infos.
				m_Array[i]->HexBinary.__ptr << endl;
			}
		    }
		    returnValue = 0;
		}
	    }

	    if (verbose)
	    {
		cout << " ----------------------------------------------" <<
		    endl;
		cout << input->
		    count << " input paramters, and " << request <<
		    " requests" << endl;
		cout << "Total time = " << total << " ms" << endl;
		cout << "Average time = " << total / request << " ms" << endl;
	    }
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
		cout << "Exception : " << e.what () << endl;
	    }
	}
	catch (...)
	{
	    cerr << "Unknown Exception occured." << endl;
	}

	// make sure we clean up memory allocated
	try
	{
	    delete ws;
	    for (int i = 0; i < input->infos.m_Size; i++)
		delete (BenchBasicDataType *) (input->infos.m_Array[i]);
	    delete input;
	    if (output)
	    {
		for (int i = 0; i < output->infos.m_Size; i++)
		    delete (BenchBasicDataType *) (output->infos.m_Array[i]);
		delete output;
	    }
	}
	catch (AxisException & e)
	{
	    cerr << e.what () << endl;
	}
	catch (exception & e)
	{
	    cout << "Exception : " << e.what () << endl;
	}
	catch (...)
	{
	    cout << "Unknown exception on clean up: " << endl;
	}
	iRetryIterationCount--;
    }
    while (iRetryIterationCount > 0 && !bSuccess);
    cout <<
	"---------------------- TEST COMPLETE -----------------------------"
	<< endl;
    printf ("successful \n");
    return returnValue;

}

