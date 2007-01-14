#include "StartEndElement.hpp"
#include <iostream>

// Test that a start/end element is handled correctly.

int main( int argc, char * argv[])
{
	char *	pszEndpoint = "http://localhost:9020/UnitTest_StartEndElement1";

	// If there are arguments, replace the default URL with that specified on the
	// command line.
	if( argc > 1)
	{
		pszEndpoint = argv[1];
	}

	// Create the web service.
	StartEndElement  ws( pszEndpoint, APTHTTP1_1);

	try
	{
        
        // Set input information
        NewOperation_Param_NewOperation in;
        in.setshortNumber(20);
        in.setaString("somestring", false);
        
        // Issue we service require
        NewOperationResponse_Param_NewOperationResponse* out = ws.NewOperation(&in);
        
        // Dump output response
        if (out == NULL)
            cout << "Test failed, NULL response" << endl;
        else
        {
            int arraySize = -1;
            if (out->ListInfoString == NULL)
                cout << "Test failed, Expecting data for field ListInfoString" << endl;
            else if (out->ListInfoString->InfoString == NULL)
                cout << "Test failed, Expecting data for field InfoString" << endl;
            else if (out->ListInfoString->InfoString->get(arraySize) != NULL || arraySize != 0)
                cout << "Test failed, Expecting zero-size array" << endl;
                
            if (out->SomeString == NULL)
                cout << "Test failed, Expecting data for field SomeString" << endl;
            else
                cout << "SomeString = " << out->SomeString << endl;
        }
        
        delete out;
	}

	// Catch those exceptions!
	catch( AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch( exception& e)
	{
	    cout << "Unknown exception has occured: " << e.what() << endl;
	}
	catch( ...)
	{
	    cout << "Unknown exception has occured" << endl;
	}

	// Done!
	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

	return 0;
}