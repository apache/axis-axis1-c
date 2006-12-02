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


#include "LargeReturningString.hpp" 
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http://bora.hursley.ibm.com:9080/LargeReturningString/services/LargeReturningString"

// If we re-direct cout it will be to this ofstream
ofstream output_file;

// Prototype
bool parse_args_for_endpoint( int * argc, char * argv[], char ** endpoint);
void shift_args( int i, int * argc, char * argv[]);
void setLogOptions( const char * output_filename);

int main( int argc, char * argv[])
{
        LargeReturningString *  ws;
        char *                                  endpoint = WSDL_DEFAULT_ENDPOINT;
        bool                                    endpoint_set = false;
        int                                             returnValue = 1; // Assume Failure
        const char* sslkeyhome = 0;
        char keylocation[255];


        endpoint_set = parse_args_for_endpoint( &argc, argv, &endpoint);

        bool    bSuccess = false;
        int             iRetryIterationCount = 3;

        do
        {
                try
                {
                        if( endpoint_set)
                        {
                                ws = new LargeReturningString( endpoint, APTHTTP1_1);
                        }
                        else
                        {
                                ws = new LargeReturningString();
                        }

                        int                     input = 2 * 1024 * 1024;
                        xsd__string     result = "";

// Extend transport timeout to 60 seconds (default is 10).

                        sslkeyhome=getenv("SSL_KEYS_HOME");

                        if (!sslkeyhome)
                        {
                                cout << "SSL_KEYS_HOME not set" << endl;
                                return 1;
                        }

                        sprintf(keylocation,"%s/%s",sslkeyhome,"myKeyRing.kdb");
                        ws->SetSecure(keylocation, "axis4all", "AXIS", "NONE", "05", "NONE", false);

                        ws->setTransportTimeout( 60);

                        result = ws->getLargeString(input);

                        cout << "Result" << endl;

                        if ( result == NULL)
                        {
                                cout << "NULL" << endl;
                        }

                        if( strlen( result) == input)
                        {
                                cout << (int) strlen( result) << endl;
                        }
                        else
                        {
                                int     iError = 0;

                                for( int x = 0; x < input; x++)
                                {
                                        if( result[x] != 'a' + (x + iError) % 26)
                                        {
                                                cout << "Error. result[" << x << "] should have been " << (char) ('a' + x % 26) << " but was " << result[x] << endl;

                                        iError++;
                                        }
                                }

                                cout << "There where " << iError << " errors." << endl;
                                cout << "Requested " << input << " bytes.  Received " << (int) strlen( result) << " bytes." << endl;
                
                                returnValue = 0; // Success
                        }

                        bSuccess = true;
                }
                catch( AxisException &e)
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
                            cout << e.what() << endl;
                        }
                }
                catch( ...)
                {
                        cout << "Unknown Exception occured." << endl;
                }

                try
                {
                        delete ws;
                }
                catch( exception& exception)
                {
                        cout << "Exception on clean up of ws: " << exception.what() << endl;
                }
                catch( ...)
                {
                        cout << "Unknown exception on clean up of ws: " << endl;
                }

                iRetryIterationCount--;
        } while( iRetryIterationCount > 0 && !bSuccess);

    if( endpoint_set)
        {
                free( endpoint);
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
    if(*argc < 3)
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
            case 'o':
                setLogOptions(argv[i+1]);
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
void setLogOptions(const char *output_filename) {
    output_file.open(output_filename, ios::out);
    if(output_file.is_open()){
        cout.rdbuf( output_file.rdbuf() );
    }
}

