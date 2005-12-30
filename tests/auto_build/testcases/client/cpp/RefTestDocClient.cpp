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


#include "ChoiceServiceSoap.hpp" 
#include <iostream>

using namespace std;

#define WSDL_DEFAULT_ENDPOINT "http://bora.hursley.ibm.com:9080/LargeReturningString/services/LargeReturningString"


// Prototype
bool parse_args_for_endpoint( int * argc, char * argv[], char ** endpoint);
void shift_args( int i, int * argc, char * argv[]);


int main( int argc, char * argv[])
{
	ChoiceServiceSoap*	ws;
    FaultPropertyType* input;
	char *					endpoint = WSDL_DEFAULT_ENDPOINT;
	bool					endpoint_set = false;
	int						returnValue = 1; // Assume Failure

	endpoint_set = parse_args_for_endpoint( &argc, argv, &endpoint);

	bool	bSuccess = false;

		try
		{
			if( endpoint_set)
			{
				ws = new ChoiceServiceSoap( endpoint, APTHTTP1_1);
				free( endpoint);
				endpoint_set = false;
			}
			else
			{
				ws = new ChoiceServiceSoap();
			}

            cout <<"About to create FaultPropertyType"<<endl;
            input = new FaultPropertyType();
            // create a resource properties (which is the referenced type)
            SetResourceProperties* setResourceProperties = new SetResourceProperties();
            cout << "About to create setresprops"<<endl;
            xsd__int c=3;
            cout << "created c"<<endl;
            setResourceProperties->setb(&c);
            cout << "about to set the props"<<endl;
            input->setSetResourceProperties_Ref(setResourceProperties);
            
            // remember to clean up the resourceproperirtes !

			FaultPropertyType* result;
            cout << "About to call get"<<endl;
			result = ws->get(input);

            if(result)
            {
                cout << "Got a result FaultPropertyType"<<endl;
                SetResourceProperties* resultResProps = result->getSetResourceProperties_Ref();
                if(resultResProps)
                {
                 cout <<"Got a result Properties"<<endl;
                 
                    cout << "b="<<*resultResProps->getb()<<endl;
                }
                else
                {
                    cout << "resourceprops came back as NULL"<<endl;
                }
            }
            else
            {
                cout << "result came back as null" << endl;
            }

			bSuccess = true;
		}
		catch( AxisException &e)
		{
		    cout << e.what() << endl;
		}
		catch( ...)
		{
			cout << "Unknown Exception occured." << endl;
		}

		try
		{
			delete ws;
            delete input;
		}
		catch( exception& exception)
		{
			cout << "Exception on clean up of ws: " << exception.what() << endl;
		}
		catch( ...)
		{
			cout << "Unknown exception on clean up of ws: " << endl;
		}


	cout << "---------------------- TEST COMPLETE -----------------------------" << endl;
  
	return returnValue;
}

/* Spin through args list and check for -e -p and -s options.
   Option values are expected to follow the option letter as the next
   argument.
 
   These options and values are removed from the arg list.
   If both -e and -s and or -p, then -e takes priority
*/
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint) {
    // We need at least 2 extra arg after program name
    if(*argc <2)
        return false;

    char *server = "localhost";
    int  port = 80;
    bool ep_set = false;
    bool server_set = false;
    bool port_set = false;

    for(int i=1; i<*argc; i++) {
        if(*argv[i] == '-') {
            switch(*(argv[i]+1)) {
            case 'e':
                *endpoint = strdup(argv[i+1]);
                ep_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            case 's':
                server = strdup(argv[i+1]);
                server_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            case 'p':
                port = atoi(argv[i+1]);
                if(port >80) port_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            default:
                break;
            }
        }
    }

    // use the supplied server and/or port to build the endpoint
    if(ep_set == false && (server_set || port_set)) {
        // Set p to the location of the first '/' after the http:// (7 chars)
        // e.g. from http://localhost:80/axis/base gets /axis/base
        char *ep_context = strpbrk(&(*endpoint)[7], "/");

        // http://:/ is 9 characters + terminating NULL character so add 10.
        // Allow space for port number upto 999999 6 chars
        *endpoint = (char *)calloc(1, 10 + strlen(ep_context) + strlen(server) + 6);
        sprintf(*endpoint, "http://%s:%d/%s", server, port, ep_context+1);
        if(server_set) free(server);
        ep_set = true;
    }

    return ep_set;
}

void shift_args(int i, int *argc, char *argv[]) {
    for(int j=i, k=i+2; j<*(argc)-2; j++, k++)
        argv[j]=argv[k];
    *argc-=2;
}


