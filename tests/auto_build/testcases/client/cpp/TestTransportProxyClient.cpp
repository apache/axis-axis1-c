/*
 * This client tests setProxy() method in Stub class.
 * 
 */

#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        int iResult;
        int rc=1;

        url = argv[1];

        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                ws.setProxy("proxy3.in.ibm.com",80);
                iResult = ws.add(2,3);
                cout<<  iResult << endl;
                rc=0;
        }
        catch(AxisException& e)
        {
                cout << "Inside AxisException block: " << e.what() << endl;
        }
        catch(exception& e)
        {
                cout << "Unknown exception has occured" << endl;
        }
        catch(...)
        {
                cout << "Unspecified exception has occured" << endl;
        }
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        return rc;
}

