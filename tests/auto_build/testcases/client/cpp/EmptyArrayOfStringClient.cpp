#include "EmptyArrayOfString.hpp"
#include <iostream>

// Test that a start/end element is handled correctly.

int main( int argc, char * argv[])
{
	char *	pszEndpoint = "http://localhost:9020/UnitTest_EmptyArrayOfString";

	// If there are arguments, replace the default URL with that specified on the
	// command line.
	if( argc > 1)
	{
		pszEndpoint = argv[1];
	}

	// Create the web service.
	EmptyArrayOfString  ws( pszEndpoint, APTHTTP1_1);

	try
	{
        // Issue we service require
        NewOperationResponse_Param_NewOperationResponse* out = ws.NewOperation(20);
        
        // Dump output response
        if (out == NULL)
            cout << "Test failed, NULL response" << endl;
        else
        {
            int arraySize = -1;
            if (out->ListInfoString == NULL)
                cout << "Test failed, Expecting data for field ListInfoString" << endl;
            else if (out->ListInfoString->_string == NULL)
                cout << "Test failed, Expecting data for field _string" << endl;
            else if (out->ListInfoString->_string->get(arraySize) != NULL || arraySize != 0)
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