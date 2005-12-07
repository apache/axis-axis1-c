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
#include "CommonClientTestCode.hpp"
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
			xsd__int outValue2;
			xsd__long outValue3;
			xsd__short outValue4;
			xsd__decimal outValue5;
			xsd__float outValue6;
			xsd__double outValue7;
			xsd__boolean outValue8;
			xsd__byte outValue9;

			ws.get(&OutValue0,
				&pOutValue1,
				&outValue2,
				&outValue3,
				&outValue4,
				&outValue5,
				&outValue6,
				&outValue7,
				&outValue8,
				&outValue9);

			char sInteger[128], sLong[128];

			const char *sBool = (outValue8==false_)?"false":"true";

			cout << OutValue0 << endl;
			cout << *pOutValue1 << endl;
			cout << outValue2 << endl;
			cout << outValue3 << endl;
			cout << outValue4 << endl;
			cout << outValue5 << endl;
			cout << outValue6 << endl;
			cout << outValue7 << endl;
			cout << sBool << endl;
#ifdef __OS400__
                  if (outValue9 == 0x41) // Ascii 'A'
                     outValue9 = 'A';    // Set to ebcdic A
#endif
			cout << outValue9 << endl;

			delete [] OutValue0;
			delete pOutValue1;

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
