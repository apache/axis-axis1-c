#include "SimpleTypeArrayWS.hpp"
#include <iostream>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/array"

static void usage( char * programName, char * defaultURL)
{
    cout << endl << "Usage:" << endl
		 << programName << " [-? | service_url] " << endl
		 << "    -?              Show this help." << endl
		 << "    service_url     URL of the service." << endl
		 << "    Default service URL is assumed to be " << defaultURL << endl;
}

int main( int argc, char *argv[])
{
    SimpleTypeArrayWS *	ws;
    char				endpoint[256];
    int					returnValue = 1;	// Assume Failure
    bool				bSuccess = false;
    int					iRetryIterationCount = 3;

    sprintf( endpoint, "%s", WSDL_DEFAULT_ENDPOINT);

    if( argc > 1)
    {
// Watch for special case help request
// Check for - only so that it works for
//-?, -h or --help; -anything
		if( !strncmp( argv[1], "-", 1))
		{
		    usage( argv[0], endpoint);
			return 2;
		}

		sprintf( endpoint, argv[1]);
    }

    do
    {
		ws = new SimpleTypeArrayWS( endpoint, APTHTTP1_1);

        try
		{
			Type *			input;
			Type *			output;
			xsd__int_Array	array_input;
			int				iIntArraySize = 100;
			xsd__int **		ppIntArray = new xsd__int *[iIntArraySize];

			for( int i = 0; i < 100; i++)
			{
				(*ppIntArray)[i] = i;
			}

			array_input.set( ppIntArray, iIntArraySize);


			input = new Type ();
			input->item = &array_input;

			ws->setTransportProperty( "SOAPAction", "array#getInput");
			output = ws->getInput( input);

			xsd__int_Array *	array_output = output->getitem();
			int					iSize;
			const xsd__int **	ppArray = array_output->get( iSize);

			for( int i = 0; i < iSize; i++)
			{
				cout << "item [" << i << "] = " << *ppArray[i] << endl;
			}

			returnValue = 0;	// Success

			bSuccess = true;
		}
		catch( AxisException & e)
		{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 1)
				{
					bSilent = true;
				}
			}
			else
			{
				iRetryIterationCount = 0;
			}

			if( !bSilent)
			{
				cerr << e.what() << endl;
			}

			free( endpoint);
		}
		catch( ...)
		{
			cerr << "Unknown Exception occured." << endl;
		}

		// clean up
		try
		{
			delete ws;
		}
		catch( exception & exception)
		{
			cerr << "Exception on clean up of ws : " << exception.what() << endl;
		}
		catch( ...)
		{
			cerr << "Unknown exception on clean up of ws : " << endl;
		}

		iRetryIterationCount--;
    } while( iRetryIterationCount > 0 && !bSuccess);

	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

	return returnValue;
}
