
#include "EnumerationWS.hpp"
#include <stdlib.h>		// For malloc(), calloc(), strdup() and free()
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/enumeration"

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL << endl;
}

// If we re-direct cout it will be to this ofstream
ofstream output_file;

int
main (int argc, char *argv[])
{
    EnumerationWS *ws;

    char endpoint[256];
    sprintf (endpoint, "%s", WSDL_DEFAULT_ENDPOINT);
    int returnValue = 1;	// Assume Failure

    Type1 *input = NULL;
    Type1 *result = NULL;

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
	    ws = new EnumerationWS (endpoint, APTHTTP1_1);

	    input = new Type1 ();

	    input->enum_string = "one";
	    input->att_enum_string = "one";
	    input->enum_int = ENUMTYPEINT_0;
	    input->att_enum_int = ENUMTYPEINT_1;
	    input->att_enum_kind = "CHEQUE";

	    ws->setTransportProperty ("SOAPAction", "enumeration#getInput");
	    result = ws->getInput (input);

	    cout << "Result" << endl;
	    if (result == NULL)
	    {
		cout << "  result = NULL" << endl;
	    }
	    else
	    {
		cout << "att_enum_int " << result->att_enum_int << endl;
		cout << "att_enum_string " << result->att_enum_string << endl;
		cout << "enum_int " << result->enum_int << endl;
		cout << "enum_string " << result->enum_string << endl;
		cout << "enum_kind " << result->att_enum_kind << endl;
		returnValue = 0;	// Success
	    }

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
		cerr << e.what () << endl;
	    }
	}
	catch (...)
	{
	    cerr << "Unknown Exception occured." << endl;
	}
	try
	{
	    delete ws;
	    delete input;
	    delete result;
	}
	catch (exception & exception)
	{
	    cout << "Exception when cleaning up: " << exception.
		what () << endl;
	}
	catch (...)
	{
	    cout << "Unknown exception when cleaning up: " << endl;
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
