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

/* This program sends multiple attachments to a service.*/

#include "AttachmentService.hpp"
#include <axis/AxisException.hpp>
#include <axis/AxisUserAPI.hpp>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string.h>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/AttachmentService";	
	char *Result;
	url = argv[1];
	bool bSuccess = false;
	int	iRetryIterationCount = 3;
	do
		{
			try
			{
				sprintf(endpoint, "%s", url);
				AttachmentService ws(endpoint);
				ISoapAttachment *att1=ws.createSoapAttachment();
				ISoapAttachment *att2=ws.createSoapAttachment();				
				char *text="This is a test message for attachment";
				//Adding the content type as text/plain
				att1->addHeader(AXIS_CONTENT_TYPE,"text/plain");
				att2->addHeader(AXIS_CONTENT_ID,"5");
				att2->addHeader(AXIS_CONTENT_TYPE,"image/jpeg");
				xsd__base64Binary b64b1;
				b64b1.__ptr = (xsd__unsignedByte*)text;
				b64b1.__size = strlen(text);				
				att1->addBody(&b64b1);
				att2->addBody(&b64b1);				
				//Calling webservice with multiple attachments. Here same object is passed as argument
				xsd__string_Array ret=ws.multiAttachment(att1,att1,att2,att1);
				cout<<ret.m_Array[0]<<endl;
				cout<<ret.m_Array[1]<<endl;
				cout<<ret.m_Array[2]<<endl;
				cout<<ret.m_Array[3]<<endl;			    			
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

