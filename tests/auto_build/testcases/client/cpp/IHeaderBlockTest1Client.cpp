/* Tests setLocalName() and getLocalName() APIs in IHeaderBlock 
  @ Author : James Jose
*/

#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	const char* op = 0;
	int i1=0, i2=0;
	int iResult;
	url = argv[1];
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		const AxisChar *localname="TestHeader";
		op = "add";
		i1 = 2;
		i2 = 3; 
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("Test","http://ws.apache.org/axisCppTest/");
		cout<<phb->setLocalName(NULL)<<endl;
		cout<<phb->getLocalName()<<endl;
		cout<<phb->setLocalName(localname)<<endl;		
		IHeaderBlock *fhb=ws.getFirstSOAPHeaderBlock();	
		localname=fhb->getLocalName();
		cout << "Local Name is " << localname << endl;
		if (strcmp(op, "add") == 0)
		{
			iResult=ws.add(i1, i2);			
			cout << iResult << endl;
			bSuccess = true;
		}
		
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

