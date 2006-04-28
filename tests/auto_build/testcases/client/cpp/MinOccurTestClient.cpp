#include "AllComplexType.hpp"
#include "AllTestSoap.hpp"
#include <iostream>
#include <axis/AxisException.hpp>
#include <ctype.h>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/MinOccur"

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

    int returnValue = 1;        // Assume Failure

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

        bool bSuccess = false;
    int iRetryIterationCount = 3;

        do
    {
                try
                {
                        AllTestSoap ws (endpoint, APTHTTP1_1);
                        AllComplexType* inParam = new AllComplexType();

                        inParam->Value0 = 8;
                        inParam->Value1 = 3;
                        inParam->Value3 = "HELLO";
                        inParam->Value6 = "TINTIN";

                        printf("\nSending.................");
                        printf("\nValue0 = %d",inParam->Value0);
                        printf("\nValue1 = %d",inParam->Value1);
                        printf("\nValue3 = %s",inParam->Value3);
                        printf("\nValue6 = %s",inParam->Value6);
                        
                        ws.setTransportProperty("SOAPAction" , "MinOccur#echoAll");
                        AllComplexType* outParam = ws.echoAll(inParam);

                        if (outParam != NULL)
                        {
                                printf("\n\nReceived................");
                                printf("\nValue0 = %d",outParam->Value0);
                                printf("\nValue1 = %d",outParam->Value1);
                                printf("\nValue3 = %s",outParam->Value3);
                                printf("\nValue6 = %s",outParam->Value6);
                                printf("\n\nSuccessfull\n");
                        }
                        else
                                printf("\nFault\n");

                        bSuccess = true;
                        delete inParam;
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
