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

#include "MultiOut.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>

int main(int argc, char* argv[])
{
	bool bSuccess = false;
	int	iRetryIterationCount = 3;
	do
	{
		try
		{
			MultiOut ws(argv[1]);

			xsd__string OutValue0 = NULL;
			xsd__integer * pOutValue1 = NULL;
			xsd__int * pOutValue2 = NULL;
			xsd__long * pOutValue3 = NULL;
			xsd__short * pOutValue4 = NULL;
			xsd__decimal * pOutValue5 = NULL;
			xsd__float * pOutValue6 = NULL;
			xsd__double * pOutValue7 = NULL;
			xsd__boolean * pOutValue8 = NULL;
			xsd__byte * pOutValue9 = NULL;

			ws.get(&OutValue0,
				&pOutValue1,
				&pOutValue2,
				&pOutValue3,
				&pOutValue4,
				&pOutValue5,
				&pOutValue6,
				&pOutValue7,
				&pOutValue8,
				&pOutValue9);

			char sInteger[128], sLong[128];
#ifdef WIN32
			sprintf(sInteger,"%I64d",*pOutValue1);
			sprintf(sLong,"%I64d",*pOutValue3);
#else
			sprintf(sInteger,"%lld",*pOutValue1);
			sprintf(sLong,"%lld",*pOutValue3);
#endif
			const char *sBool = (*pOutValue8==false_)?"false":"true";

			cout << OutValue0 << endl;
			cout << sInteger << endl;
			cout << *pOutValue2 << endl;
			cout << sLong << endl;
			cout << *pOutValue4 << endl;
			cout << *pOutValue5 << endl;
			cout << *pOutValue6 << endl;
			cout << *pOutValue7 << endl;
			cout << sBool << endl;
#ifdef __OS400__
                  if (*pOutValue9 == 0x41) // Ascii 'A'
                     *pOutValue9 = 'A';    // Set to ebcdic A
#endif
			cout << *pOutValue9 << endl;
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
		    cout << "Unknown exception has occured" << e.what() << endl;
		}
		catch(...)
		{
		    cout << "Unknown exception has occured" << endl;
		}
		iRetryIterationCount--;
	} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}
