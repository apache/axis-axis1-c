
/* Tests addChild() API in IHeaderBlock
  Author @James Jose  
*/

#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/IAttribute.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int i1=2, i2=3;
	int iResult;

	if(argc > 1)
		url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		AxisChar *uri="http://ws.apache.org/";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");		
		BasicNode * Bnode1=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"APACHE ");
		phb->addChild(Bnode1);
		BasicNode * Bnode2=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"is cool");
		phb->addChild(Bnode2);
		iResult=ws.add(i1, i2);			
		cout << endl << iResult << endl;
		bSuccess = true;
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
		cout << "Unspecified exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return 0;
}
