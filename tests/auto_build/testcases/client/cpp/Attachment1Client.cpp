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

#include "AttachmentBindingImpl.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"

int main(int argc, char* argv[])
{
	bool bSuccess = false;
	int	iRetryIterationCount = 3;

	do
	{
		try
		{
			AttachmentBindingImpl ws(argv[1]);

			char *text=stringToAscii("Some attachment text");

			#define NUM_ATTS 6
			ISoapAttachment *att[NUM_ATTS];
			xsd__base64Binary b64b[NUM_ATTS];

			for (int i=0; i<NUM_ATTS; i++)
			{
				att[i] = ws.createSoapAttachment();

				if (1==i)
					att[i]->addHeader(AXIS_CONTENT_TYPE,"image/jpeg");
				else if (2==i)
					att[i]->addHeader("Content-Disposition","checked");
				
				b64b[i].set((unsigned char *)text, strlen(text)+1);
				att[i]->addBody(&b64b[i]);	
			}

			xsd__int iResult = ws.put(att[0], att[1], att[2], att[3], att[4], att[5], NULL);
			cout << iResult << endl;
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

void PrintUsage()
{
	printf("Usage :\n Calculator <url>\n\n");
	exit(1);
}

bool IsNumber(const char* p)
{
	for (int x=0; x < strlen(p); x++)
	{
		if (!isdigit(p[x])) return false;
	}
	return true;
}

