#include "XSDElement.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    char dateTime[50];

    xsd__time timeResult;           // typedef of struct tm
    time_t timeToTest;
    timeToTest = 1100246323;
    xsd__date *temp = gmtime(&timeToTest);
    xsd__date testDate;
    memcpy(&testDate, temp, sizeof(xsd__date));

    if(argc>1)
        url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
    try
    {
        sprintf(endpoint, "%s", url);
        XSDElement* ws = new XSDElement(endpoint);

        timeResult = ws->setGetTimeType(testDate);
        strftime(dateTime, 50, "%H:%M:%S", &timeResult);
        cout << "time=" << dateTime << endl;
		bSuccess = true;

        delete ws;
    }
    catch(AxisException& e)
    {
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
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
				cout << "Exception : " << e.what() << endl;
			}
    }
    catch(exception& e)
    {
        cout << "Unknown exception has occured" << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
   
    return 0;
}

