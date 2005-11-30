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
			xsd__integer OutValue1 = 0;
			xsd__int OutValue2 = 0;
			xsd__long OutValue3 = 0;
			xsd__short OutValue4 = 0;
			xsd__decimal OutValue5 = 0;
			xsd__float OutValue6 = 0;
			xsd__double OutValue7 = 0;
			xsd__boolean OutValue8 = false_;
			xsd__byte OutValue9 = 0;

			ws.get(&OutValue0,
				(xsd__integer**)&OutValue1,
				(xsd__int**)&OutValue2,
				(xsd__long**)&OutValue3,
				(xsd__short**)&OutValue4,
				(xsd__decimal**)&OutValue5,
				(xsd__float**)&OutValue6,
				(xsd__double**)&OutValue7,
				(xsd__boolean**)&OutValue8,
				(xsd__byte**)&OutValue9);

			char sInteger[128], sLong[128];
#ifdef WIN32
			sprintf(sInteger,"%I64d",OutValue1);
			sprintf(sLong,"%I64d",OutValue3);
#else
			sprintf(sInteger,"%lld",OutValue1);
			sprintf(sLong,"%lld",OutValue3);
#endif
			const char *sBool = (OutValue8==false_)?"false":"true";

			cout << OutValue0 << endl;
			cout << sInteger << endl;
			cout << OutValue2 << endl;
			cout << sLong << endl;
			cout << OutValue4 << endl;
			cout << OutValue5 << endl;
			cout << OutValue6 << endl;
			cout << OutValue7 << endl;
			cout << sBool << endl;
#ifdef __OS400__
                  if (OutValue9 == 0x41) // Ascii 'A'
                     OutValue9 = 'A';    // Set to ebcdic A
#endif
			cout << OutValue9 << endl;
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
		    cout << "Unknown exception has occured" << endl;
		}
		iRetryIterationCount--;
	} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	return 0;
}
