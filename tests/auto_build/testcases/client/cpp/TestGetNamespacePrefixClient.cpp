/* 
 * This test is written to test the functionality of getNamespacePrefix() API
 * of Stub class.
 */ 

#include "MathOps.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	int rc=1;
	const AxisChar *ch=NULL;

	url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		MathOps ws(endpoint);
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader1", "http://ws.apache.org/axisCppTest/","th1");
		phb->createNamespaceDecl("th1", "http://ws.apache.org/axisCppTest1/");
		
		
		iResult = ws.div(15,3);
		cout << "Result is = " << iResult << endl;
		//This method is no more defined in Stub API
		//cout << ws.getNamespacePrefix("http://ws.apache.org/axisCppTest1/") << endl;
		rc=0;

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
	    cout << "Unknown exception2 has occured" <<endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
		
	return rc;
}
