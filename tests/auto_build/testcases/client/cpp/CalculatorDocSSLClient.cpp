/*****************************************************************************
* This test is written to test the functionality of SetSecure() API 
******************************************************************************
*/

#include "Calculator.hpp"
#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
        char endpoint[256];
	const char* sslkeyhome = 0;
    	char keylocation[255];
 
        const char* url="https://localhost:80/axis/Calculator";
        int iResult;

        url = argv[1];

        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                //ws.SetSecure("/home/axistest/ssl/myKeyRing.kdb", "axis4all", "AXIS", "NONE", "05", "NONE", false);
		 sslkeyhome=getenv("SSL_KEYS_HOME");

		if (!sslkeyhome)
		{ 	cout << "SSL_KEY_HOME not set" << endl;	
			return 1;
		}

		sprintf(keylocation,"%s/%s",sslkeyhome,"myKeyRing.kdb");
                ws.SetSecure(keylocation, "axis4all", "AXIS", "NONE", "05", "NONE", false);

                iResult = ws.add(2,3);
                printf("%d\n", iResult);
        }
        catch(AxisException& e)
        {
            printf("Exception : %s\n", e.what());
        }
        catch(exception& e)
        {
            printf("Unknown exception has occured\n" );
        }
        catch(...)
        {
            printf("Unknown exception has occured\n" );
        }
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        return 0;
}

