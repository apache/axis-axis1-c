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

#include "Calculator.hpp"
#include <axis/AxisException.hpp>
#include <axis/AxisCPPConfigDefaults.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	const char* op = 0;
	int i1=0, i2=0;
	char* libhome = NULL;
	char parserlocation[255] ;
	char httptransportlocation[255];
	char httpchannellocation[255];
	int iResult;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//signal(SIGQUIT, sig_handler);
	//signal(SIGBUS, sig_handler);
	signal(SIGFPE, sig_handler);

	url = argv[1];
	
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
			try
			{
				sprintf(endpoint, "%s", url);
                		AxisCPPConfigDefaults config;
                		char* installdir = NULL;
				installdir = getenv( "INSTALLDIR" );
                		config.setAxisHome(installdir);
                		config.setClientLog("Client.taw");
                		char wsddfile[255];
				sprintf(wsddfile,"%s/%s",installdir,"ClientFile.wsdd");
                		//char* wsddfile = "ClientFile.wsdd";
                		config.setClientWSDDFile(wsddfile);

				libhome = getenv("LIBHOME");

                		#if defined ( WIN32 )
				sprintf(parserlocation,"%s/%s",libhome,"AxisXMLParser.dll");
				sprintf(httptransportlocation,"%s/%s",libhome,"HTTPTransport.dll");
				sprintf(httpchannellocation,"%s/%s",libhome,"HTTPChannel.dll");
				config.setXMLParserLibrary(parserlocation);
                		config.setHTTPTransportLibrary(httptransportlocation);
                		config.setHTTPChannelLibrary(httpchannellocation);

				#elif defined ( AIX )
				sprintf(parserlocation,"%s/%s",libhome,"libaxis_xmlparser.a");
				sprintf(httptransportlocation,"%s/%s",libhome,"libhttp_transport.a");
				sprintf(httpchannellocation,"%s/%s",libhome,"libhttp_channel.a");
				config.setXMLParserLibrary(parserlocation);
                		config.setHTTPTransportLibrary(httptransportlocation);
                		config.setHTTPChannelLibrary(httpchannellocation);

				#else 
				sprintf(parserlocation,"%s/%s",libhome,"libaxis_xmlparser.so");
				sprintf(httptransportlocation,"%s/%s",libhome,"libhttp_transport.so");
				sprintf(httpchannellocation,"%s/%s",libhome,"libhttp_channel.so");
				config.setXMLParserLibrary(parserlocation);
                		config.setHTTPTransportLibrary(httptransportlocation);
                		config.setHTTPChannelLibrary(httpchannellocation);
				#endif

                		config.apply();
                		//axishome = config.getAxisHome();
                		//cout << "Axis Home = " << axishome << endl;
                		char* wsddfile1 = NULL;
                		wsddfile1 = config.getClientWSDDFile();
				cout<< "Client Log file name = " << config.getClientLog() << endl;
                		char* parser  = config.getXMLParserLibrary();
                		//cout << "XML Parser used = " << parser << endl;
	
				if (strcmp (parserlocation,parser) == 0)
				{
					cout << "XML Parser is  matched" << endl;
				}
				else{ 
					cout << "XML parser is not matched" << endl;
				}
		
				if ( strcmp(httptransportlocation,config.getHTTPTransportLibrary()) == 0)
				{
					cout << "HTTP Transport is matched" << endl;
				}
				else{
					cout << "HTTP Transport is not matched" << endl;
				}

				if ( strcmp(httpchannellocation,config.getHTTPChannelLibrary()) == 0)
				{
					cout << "HTTP Channel lib is matched" << endl;
				}
				else {
					cout << "HTTP Channel is not matched" << endl;
				}

                		Calculator ws(endpoint);

				op = "add";
				i1 = 2;
				i2 = 3;

				if (strcmp(op, "add") == 0)
				{
					iResult = ws.add(i1, i2);
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
	    		cout << "Unknown exception has occured" << endl;
		}
		iRetryIterationCount--;
		} 
		while( iRetryIterationCount > 0 && !bSuccess);
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

void sig_handler(int sig) {
	signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}

