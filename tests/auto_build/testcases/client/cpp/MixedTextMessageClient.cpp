#include <iostream>
#include "MixedFalseWithMixedTextMessage.hpp"

int main( int iArgC, char * pArgV[])
{
    char *	pszURL = "http://localhost:9090/MixedFalseWithMixedTextMessage/services/MixedFalseWithMixedTextMessage";
	bool	bSuccess = false;
	int		iRetryIterationCount = 3;

	do
	{
		try
		{
			if( iArgC > 0)
			{
				pszURL = pArgV[1];
			}

			MixedFalseWithMixedTextMessage *	pWS = new MixedFalseWithMixedTextMessage( pszURL, APTHTTP1_1);

			xsd__string	sLetterId = new char[6];

			strcpy( sLetterId, "0100");

	// Demonstrating pointer to pointers.
			xsd__string	xsTo = NULL;
			xsd__date *	pxdDate = NULL;
			xsd__int *	pxiOrderNumber = NULL;

			xsd__string *	psTo = &xsTo;
			xsd__date **	ppdDate = &pxdDate;
			xsd__int **		ppiOrderNumber = &pxiOrderNumber;

			pWS->GetLetter( sLetterId, psTo, ppdDate, ppiOrderNumber);

			cout << "The letter information for: " << sLetterId << endl;
			cout << "To:      " << *psTo << endl;
			cout << "Date:    " << asctime( *ppdDate);
			cout << "OrderNo: " << **ppiOrderNumber << endl << endl;

			delete *psTo;
			delete *ppdDate;
			delete *ppiOrderNumber;

	// Demonstrating references to pointers.
			xsd__string	sTo = NULL;
			xsd__date *	pdDate = NULL;
			xsd__int *	piOrderNumber = NULL;

			pWS->GetLetter( sLetterId, &sTo, &pdDate, &piOrderNumber);

			cout << "The letter information for: " << sLetterId << endl;
			cout << "To:      " << sTo << endl;
			cout << "Date:    " << asctime( pdDate);
			cout << "OrderNo: " << *piOrderNumber << endl;

			delete sLetterId;
			delete sTo;
			delete pdDate;
			delete piOrderNumber;

			delete pWS;

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
				cout << "Exception: " << e.what() << endl;
			}
		}
		catch( exception & e)
		{
			cout << "An unknown exception has occured: " << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unknown exception has occured" << endl;
		}

	iRetryIterationCount--;
	} while( iRetryIterationCount > 0 && !bSuccess);

	cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;

	return 0;
}