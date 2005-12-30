#include "ADEC_MAST_Port.hpp"
#include "SummaryResult.hpp"
#include <iostream>
#include <axis/AxisException.hpp>
#include <ctype.h>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/RPCAll"

void PrintUsage();

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
    char endpoint[256];
    sprintf (endpoint, "%s", WSDL_DEFAULT_ENDPOINT);

    int returnValue = 1;	// Assume Failure

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
			ADEC_MAST_Port ws (endpoint, APTHTTP1_1);

			SummaryResult* outParam = new SummaryResult();
			
			xsd__string Value0 = "RED";
			xsd__int Value1 = 3;
			xsd__int Value3 = 5;
			xsd__double Value2 = 2.5;

			printf("\nSending................\n");
			printf("\nLength = %d",Value1);
			printf("\nWidth = %d",Value3);
			printf("\nDepth = %f",Value2);
			printf("\nColor = %s",Value0);

				
		
			ws.setTransportProperty("SOAPAction" , "RPCAll#doGetSummary");
			outParam = ws.doGetSummary(Value0, Value1, Value2, Value3);

			if (outParam != NULL)
			{
				printf("\n\nReceived................\n");
				printf("\nNon All Int Value = %d",outParam->NonAllIntValue);
				printf("\nNon All Double Value = %f",outParam->NonAllDoubleValue);
				printf("\n\nAll Values are...");
				printf("\n\tLength = %d",*(outParam->length));
				printf("\n\tDepth = %f",*(outParam->depth));
				printf("\n\tColor = %s",outParam->color);
				printf("\n\nNon All String Value = %s\n\n",outParam->NonAllStringValue);
			}
			else
				printf("\n\nFault\n");

			bSuccess = true;
			delete outParam;
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
			cout << "Unknown Exception occured." << endl;
		}

		iRetryIterationCount--;

	}while (iRetryIterationCount > 0 && !bSuccess);

    cout <<
	"---------------------- TEST COMPLETE -----------------------------"
	<< endl;

    return returnValue;

}
