// Copyright 2003-2004 The Apache Software Foundation.
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

#include <axis/AxisException.hpp>
#include <axis/client/Call.hpp>
#include <axis/AxisWrapperAPI.hpp>
#include <axis/ISoapAttachment.hpp>
#include <iostream>
#include <string>
#include <exception>
#include "CommonClientTestCode.hpp"
using namespace std;
AXIS_CPP_NAMESPACE_USE 

int main(int argc, char* argv[])
{
	try
	{
		Call call;
		call.setEndpointURI(argv[1]);

		////////////////////////////////////////////////////////////////////////

		for (int i=0; i<5; i++) 
		{
			cout << "i=" << i << endl;
			ISoapAttachment *att = call.createSoapAttachment();

			try {
				if (!(i%3)) att->addHeader(AXIS_CONTENT_ID,"HERES_MY_CONTENT_ID");
			} catch (AxisException &ae) {
				cout << ae.what() << endl;
			}

			att->addHeader(AXIS_CONTENT_TYPE,"text/plain");
			att->addHeader(AXIS_CONTENT_TRANSFER_ENCODING,"base64");
			
			xsd__base64Binary b64b;

			char *text = stringToAscii("This is the attachment body for the DynUnrefAttachmentTest");

            b64b.set((xsd__unsignedByte *) text, strlen(text) + 1);
			att->addBody(&b64b);	

			call.addAttachment(att);
		}

		////////////////////////////////////////////////////////////////////////

		call.initialize(CPP_DOC_PROVIDER);
		call.setSOAPVersion(SOAP_VER_1_1);
		call.setTransportProperty(SOAPACTION_HEADER , "Trash");
		call.setOperation("put", "http://localhost/axis/DynUnrefAttachment");

		cout << "Invoking..." << endl;
		if (AXIS_SUCCESS != call.invoke())
		{
			cout << "Invoke failed" << endl;
			return 0;
		}

		if(AXIS_SUCCESS != call.checkMessage("putResponse", "http://localhost/axis/DynUnrefAttachment"))
		{
			cout << "Check message failed" << endl;
			return 0;
		}
		call.unInitialize();
	}
	catch(AxisException& e)
	{
	     cout << "Exception : " <<  e.what()<< endl;		
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		 cout << "Unspecified exception has occured" << endl;
	}
	cout << "----------------------------TEST COMPLETE--------------------------------" << endl;
	return 0;
}

