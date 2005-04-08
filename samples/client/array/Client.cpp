#include "SimpleTypeArrayWS.hpp"
#include <stdlib.h>		// For malloc(), calloc(), strdup() and free()
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/array"

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
    SimpleTypeArrayWS *ws;

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
	ws = new SimpleTypeArrayWS (endpoint, APTHTTP1_1);
	try
	{

	    Type *input;
	    Type *output;
	    xsd__int_Array array_input;
	    int entries[100];
	    int i;

	    array_input.m_Array = new int *[100];
	    array_input.m_Size = 100;

	    for (i = 0; i < 100; i++)
	    {
		entries[i] = i;
		array_input.m_Array[i] = &entries[i];
	    }

	    input = new Type ();
	    input->item = array_input;

	    ws->setTransportProperty ("SOAPAction", "array#getInput");
	    output = ws->getInput (input);

	    for (i = 0; i < 100; i++)
	    {
		cout << "item [" << i << "] = " << *(output->item.
						     m_Array[i]) << endl;
	    }
	    returnValue = 0;	// Success

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
	    //if(endpoint_set)
	    free (endpoint);
	}
	catch (...)
	{
	    cerr << "Unknown Exception occured." << endl;
	}

	// clean up
	try
	{
	    delete ws;
	}
	catch (exception & exception)
	{
	    cerr << "Exception on clean up of ws : " << exception.
		what () << endl;
	}
	catch (...)
	{
	    cerr << "Unknown exception on clean up of ws : " << endl;
	}
	iRetryIterationCount--;
    }
    while (iRetryIterationCount > 0 && !bSuccess);
    cout <<
	"---------------------- TEST COMPLETE -----------------------------"
	<< endl;
    return returnValue;

}
