#include "IQueryService.hpp"
#include <iostream>

int main( int argc, char * argv[])
{
	char *	pszEndpoint = "http://localhost:9020/UnitTest_17667";

	// If there are arguments, replace the default URL with that specified on the
	// command line.
	if( argc > 1)
	{
		pszEndpoint = argv[1];
	}

	// Create the web service.
	IQueryService *	pIQueryService = new IQueryService( pszEndpoint, APTHTTP1_1);

	try
	{
		// Initialise the objects that will be returned from the web service call.
		plmType_Array *			pPlmType_Array = NULL;
		RepFormatType_Array *	pRepFormatType_Array = NULL;

		// Get the information from the response message.
		pIQueryService->query( &pPlmType_Array, &pRepFormatType_Array);

		int					iPlmType_ArraySize = 0;
		plmType **			ppPlmType = pPlmType_Array->get( iPlmType_ArraySize);
		int					iRepFormatType_ArraySize = 0;
		RepFormatType **	ppRepFormatType = pRepFormatType_Array->get( iRepFormatType_ArraySize);

		// Display the response information.
		for( int iIndex = 0; iIndex < iPlmType_ArraySize; iIndex++)
		{
			xsd__int	id = ppPlmType[iIndex]->getplmid();

			cout << "id: " << id << endl;
		}

		if( iRepFormatType_ArraySize == 0)
		{
			cout << "RepFormatType is empty" << endl;
		}

		for( int iIndex = 0; iIndex < iRepFormatType_ArraySize; iIndex++)
		{
			xsd__unsignedInt			uiOwner = ppRepFormatType[iIndex]->getowner();
			RepresentationFormatType	pszFormat = ppRepFormatType[iIndex]->getformat();
			RepresentationLinkType		pRLT = ppRepFormatType[iIndex]->getassociatedFile();

			cout << "Owner[" << iIndex << "]:         " << uiOwner << endl;
			cout << "Format[" << iIndex << "]:        " << pszFormat << endl;
			cout << "Rep Link Type[" << iIndex << "]: " << pRLT << endl;
		}

		// Tidy up.
		delete *ppPlmType;
		delete *ppRepFormatType;
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

	// Final tidy up.
	delete pIQueryService;

	// Done!
	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

	// Output should be as follows:-
	// id: 5
	// Owner[0]:         25
	// Format[0]:        format
	// Rep Link Type[0]: associatedFile
	// ---------------------- TEST COMPLETE -----------------------------
	return 0;
}