#include "XSDElementNil.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";
    char dateTime[50];

    xsd__time* timeResult;          // typedef of struct tm
    xsd__time timeInput;            // typedef of struct tm
    time_t timeToTest;
    timeToTest = 1100246323;
    xsd__date *temp = gmtime(&timeToTest);
    xsd__date testDate;
    memcpy(&testDate, temp, sizeof(xsd__date));

    if(argc>1)
        url = argv[1];

    try
    {
     sprintf(endpoint, "%s", url);
     XSDElementNil* ws = new XSDElementNil(endpoint);

     timeResult = ws->setGetTimeType(&testDate);
     strftime(dateTime, 50, "%H:%M:%S", timeResult);
     cout << "time=" << dateTime << endl;

     delete ws;
    }
    catch(AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << "Unknown exception has occured" << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
   
    return 0;
}

