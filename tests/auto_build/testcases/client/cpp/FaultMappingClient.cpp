// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "MathOps.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <signal.h>
#include <iostream>

void sig_handler(int);
using namespace std;

typedef struct
{
	int	iValue1;
	int	iValue2;
} MathOperationData;

int main( int argc, char * argv[])
{
	char *				pszURL = "http://localhost:80/axis/MathOps";
	const char *		pszOperation = NULL;
	MathOperationData	sMathOperationData[] = {{  10,  5},
												{  10,  0},
												{1000,  5},
												{  10, -5},
												{   0,  0}};

	signal( SIGILL,  sig_handler);
	signal( SIGABRT, sig_handler);
	signal( SIGSEGV, sig_handler);
//  signal( SIGQUIT, sig_handler);
//  signal( SIGBUS,  sig_handler);
	signal( SIGFPE,  sig_handler);

	pszURL = argv[1];

	pszOperation = "div";

	if( strcmp( pszOperation, "div") == 0)
	{
	    int	iMathDataCount = 0;

		while( sMathOperationData[iMathDataCount].iValue1 != 0 &&
			   sMathOperationData[iMathDataCount].iValue1 != sMathOperationData[iMathDataCount].iValue2)
	    {
			bool bSuccess = false;
			int	iRetryIterationCount = 3;

            cout << iMathDataCount << endl;

			do
			{
				try
				{
					MathOps	ws( pszURL);

					if( iRetryIterationCount == 3)
					{
						cout << "Trying to "
							 << pszOperation
							 << " "
							 << sMathOperationData[iMathDataCount].iValue1
							 << " by "
							 << sMathOperationData[iMathDataCount].iValue2
							 << endl;
					}

// HTTP/1.1 500 Internal Server Error
// :
// <soapenv:Header/>
// <faultcode xmlns:ns2144481696="http://soapinterop.org/types"
//                         xmlns="">ns2144481696:DivByZeroStruct</faultcode>
// <faultstring xmlns="">org.soapinterop.DivByZeroStruct</faultstring>
// <detail xmlns="">
// <faultstruct1 href="#id0"/>
// </detail>
// </soapenv:Fault>
// <multiRef id="id0"
//           soapenc:root="0"
//           soapenv:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"
//           xsi:type="ns2144481696:DivByZeroStruct"
//           xmlns:ns2144481696="http://soapinterop.org/types"
//           xmlns="">
// <varString xsi:type="xsd:string">Division by zero exception</varString>

					int	iResult = ws.div( sMathOperationData[iMathDataCount].iValue1,
										  sMathOperationData[iMathDataCount].iValue2);
				
					cout << "Result is " << iResult << endl;
				
					bSuccess = true;
				}
				catch( DivByZeroStruct& dbzs)
				{
					cout << "DivByZeroStruct Fault: \""
						 << dbzs.varString
						 << "\", "
						 << dbzs.varInt
						 << ", "
						 << dbzs.varFloat
						 << endl;

					bSuccess = true;
				}
				catch( SpecialDetailStruct& sds)
				{
					cout << "SpecialDetailStruct Fault: \""
						 << sds.varString
						 << "\""
						 << endl;

					bSuccess = true;
				}
				catch( OutOfBoundStruct& oobs)
				{
					cout << "OutOfBoundStruct Fault: \""
						 << oobs.varString
						 << "\", "
						 << oobs.varInt
						 << ", \""
						 << oobs.specialDetail->varString
						 << "\""
						 << endl;

					bSuccess = true;
				}
				catch( SoapFaultException& sfe)
				{
					cout << "SoapFaultException: " << sfe.what() << endl;
				}
				catch( AxisException& e)
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
						cout << "Exception : " << e.what() << endl;
					}
				}
				catch( exception& e)
				{
		            cout << "Unknown Exception: " << e.what() << endl;
				}
				catch(...)
				{
		            cout << "Unspecified Exception: " << endl;
				}

				iRetryIterationCount--;
			} while( iRetryIterationCount > 0 && !bSuccess);

			iMathDataCount++;
	    }
	}
	else 
	{
		cout << "Invalid operation " << pszOperation << endl;
	}

	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;
	
	return 0;
}

void sig_handler( int sig)
{
	signal( sig, sig_handler);

    cout << "SIGNAL RECEIVED " << sig << endl;

	exit(1);
}