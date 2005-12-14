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

/* This program tests nillable attachments. */ 

#include "AttachmentService.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <signal.h>

void sig_handler(int);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/AttachmentService";	
	char *Result;
	url = argv[1];
	bool bSuccess = false;
	int	iRetryIterationCount = 3;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//signal(SIGQUIT, sig_handler);
	//signal(SIGBUS, sig_handler);
	signal(SIGFPE, sig_handler);

	do
		{
			try
			{
				sprintf(endpoint, "%s", url);
				AttachmentService ws(endpoint);
				ISoapAttachment *att=ws.createSoapAttachment();
				//declare an ifstream object to read from a file.
			    ifstream is;
				//Opening a file which contans an actual SOAP Message.
				is.open ("SOAPMessage.xml",ios::binary);
				if(is==NULL){
					cout<<"Filepath specified for attachment is wrong";
					exit(0);
				}
				//Finding out the number of bytes in the file
				is.seekg (0, ios::end);
				int length = is.tellg();
				is.seekg (0, ios::beg);
				char *buffer;
				
				// allocate memory:

				buffer = new char [length];
				// read data as a block:
				is.read (buffer,length); 				
                is.close(); 

				//Adding the content type as text/xml
				att->addHeader(AXIS_CONTENT_TYPE,"text/xml");
				xsd__base64Binary b64b1;
                b64b1.set((xsd__unsignedByte *) buffer, length);
				att->addBody(&b64b1);
				//Calling the service. Here passing NULL as argument
				//Service will return the content of 'att' ie content of first argument
				xsd__string str=ws.nillableAttachment(att,NULL,NULL,"hello");
				if(str!=NULL)
				   cout<<str<<endl;
				else
					cout<<"<null>"<<endl;				
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

void sig_handler(int sig) {
	signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

