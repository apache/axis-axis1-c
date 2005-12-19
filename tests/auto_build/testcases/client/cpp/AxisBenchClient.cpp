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

#include "AxisBench.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include "CommonClientTestCode.hpp"

#ifndef WIN32
  #include "sys/time.h"
#else
  #include "sys/timeb.h"
#endif

static bool verbose = false;
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);
void setLogOptions(const char *output_filename);

// If we re-direct cout it will be to this ofstream
ofstream output_file;

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/AxisBench/services/AxisBenchSoapImpl"

int main(int argc, char* argv[])
{ 
    AxisBench *ws;

    BenchDataType *input = NULL;
    BenchDataType *output = NULL;
    xsd__unsignedByte* buffer = NULL;

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    bool endpoint_set = false;
    int returnValue = 1; // Assume Failure

    endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

    bool bSuccess = false;
    int	iRetryIterationCount = 3;

    do
    {
        try
        {
            if(endpoint_set)
            {
                ws = new AxisBench(endpoint, APTHTTP1_1);
                free(endpoint);
                endpoint_set = false;
            }
            else
                ws = new AxisBench();

            int request = 1;
      
            input = new BenchDataType();
            input->count = 100;
      
            BenchBasicDataType_Array arrayIn;
            BenchBasicDataType **	ppBBDT = new BenchBasicDataType *[input->count];

            xsd__long ll = 10000;

            time_t tim;
            tim = 1100246323;
            struct tm *temp = gmtime(&tim);
            struct tm lt;
            memcpy(&lt, temp, sizeof(struct tm));
            
            char *letterA_String = stringToAscii("A");
            buffer = (xsd__unsignedByte*)calloc (1, input->count + 2);
            
            strcpy ( (char *)buffer, letterA_String);  

            for ( int i = 0; i < input->count ; i++ )
            {
                BenchBasicDataType *type = new BenchBasicDataType();
                type->StringType = "StringType";
                type->IntegerType = 10*(i+1);
                type->DoubleType = 11.111 * (i+1);
                type->BooleanType = true_;
                type->DateTimeType = lt ;
                type->TimeType = lt ;
                type->DateType = lt ;
                type->IntType = (i+1);
                type->ByteType = '1';
                type->DecimalType = 10*(i+1);
                type->FloatType = (float)((float)(11*(i+1))/(float)2.0);
                type->LongType = ll;
                type->QNameType = "toto";
                type->ShortType = (i+1);
                type->Base64BinaryType.set(buffer, i);
                type->HexBinary.set(buffer, i);
            
                ppBBDT[i] = type;

                if( ll == 0)
                {
                    ll = 1;
                }
                else
                {
                    ll += 10000;
                }

                strcat ( (char *)buffer, letterA_String);
            }

            int t1,t2;
#ifndef WIN32  
            struct timeval mstart;
            struct timeval mstop;
            gettimeofday( &mstart, NULL );
#else
            struct timeb mstart;
            struct timeb mstop;
            ftime(&mstart);
#endif

            arrayIn.set(ppBBDT, input->count);
            input->setinfos(&arrayIn);    
            for ( int ii = 0; ii < request ; ii++ )
            {
                if (output)
                { // Samisa: memory management BP
                    int outputSize =0;
                    BenchBasicDataType ** outArray =output->infos->get(outputSize); 
                    for (int i = 0; i < outputSize; i++)
                        delete outArray[i];
                    delete output;
                    output = NULL;
                }
                output = ws->doBenchRequest(input);
            }

            for (int count = 0 ; count < input->count ; count++ )
            {
                delete ppBBDT[count];
            }
            delete [] ppBBDT;
            free(buffer);

#ifndef WIN32
            gettimeofday( &mstop, NULL );
            t1 = mstart.tv_sec*1000 + mstart.tv_usec/1000;
            t2 = mstop.tv_sec*1000 + mstop.tv_usec/1000;
#else
            ftime(&mstop);
            t1 = mstart.time*1000 + mstart.millitm;
            t2 = mstop.time*1000 + mstop.millitm;
#endif

            int total = t2-t1;

            if ( ws->getStatus() == AXIS_FAIL )
                cout << "Failed" << endl;
            else 
            {
                bSuccess = true;
                char dateTime[50];
                int i = 0;
                if ( argc > 1 )
                    i = output->count -1;
                
                cout << "Input Count : " << input->count << endl;
                cout << "Count : " << output->count << endl;
                int outputSize = 0;
                BenchBasicDataType ** outArray =output->infos->get(outputSize); 
                for ( ; i < output->count ; i++ ) 
                {
                    if( outArray[i] != (BenchBasicDataType *) 0xcdcdcdcd)
                    {
                        cout << " ----------------------------------------------" << endl;
                        cout << " StringType " << outArray[i]->StringType << endl;
                        cout << " IntType " << outArray[i]->IntType << endl;
                        cout << " IntegerType " << outArray[i]->IntegerType << endl;
                        cout << " DoubleType " << outArray[i]->DoubleType << endl;
                        cout << " BooleanType " << outArray[i]->BooleanType << endl;
                        strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &outArray[i]->DateTimeType);
                        cout << " DateTimeType " << dateTime << endl;
                        strftime(dateTime, 50, "%a %b %d %Y", &outArray[i]->DateType);
                        cout << " DateType " << dateTime << endl;
// This is being removed due to problem in some servers.
// See XSDTime or XSDTimeNil testcases for full validation of the xsd:time type
//                      strftime(dateTime, 50, "%H:%M:%S", &output->infos.m_Array[i]->TimeType);
//                      cout << " TimeType " << dateTime << endl;

// Following check for os/400 - the mock server will return ascii char which needs to be converted
#ifdef __OS400__
                        if (outArray[i]->ByteType == 0x31) 
                            outArray[i]->ByteType = '1';
#endif
                        cout << " ByteType " << outArray[i]->ByteType << endl;
                        cout << " DecimalType " << outArray[i]->DecimalType << endl;
                        cout << " FloatType " << outArray[i]->FloatType << endl;
                        cout << " LongType " << outArray[i]->LongType << endl;
                        cout << " QNameType " << outArray[i]->QNameType << endl;
                        cout << " ShortType " << outArray[i]->ShortType << endl;

                        int size = 0;
                        xsd__unsignedByte * base64BinaryData = outArray[i]->Base64BinaryType.get(size);
                        cout << " Base64BinaryType " << size << endl;
                        if( size > 0)
                        {
                            cout << " Base64BinaryType " << asciiToString((char *)base64BinaryData) << endl;
                        }
                        if (base64BinaryData != NULL)
                        {
                            delete [] base64BinaryData;
                            base64BinaryData = NULL;
                        }

                        size = 0;
                        xsd__unsignedByte * hexBinaryData = outArray[i]->HexBinary.get(size);
                        cout << " HexBinaryType " << size << endl;
                        if( size > 0)
                        {
                            cout << " HexBinaryType " << asciiToString((char *)hexBinaryData) << endl;
                        }
                        if (hexBinaryData != NULL)
                        {
                            delete [] hexBinaryData;
                            hexBinaryData = NULL;
                        }
                    }
                    returnValue=0;
                }
            }

            if(verbose)
            {
                cout << " ----------------------------------------------" << endl;
                cout << input->count << " input paramters, and " << request << " requests" << endl;
                cout << "Total time = " << total << " ms" << endl;
                cout << "Average time = " << total/request << " ms" << endl;
            }
        }
        catch(AxisException &e)
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
                cout << "Exception : " << e.what() << endl;
            }
        }
        catch(...)
        {
            cerr << "Unknown Exception occured." << endl;
        }

        // Samisa: make sure we clean up memory allocated
        try
        {
            delete ws; 
            delete input;
            if (output)
            {
                delete output;
            }
        }
        catch(AxisException& e)
        {
            cerr << e.what() << endl;
        }
        catch(exception& e)
        {
            cout << "Exception : " << e.what() << endl;
        }
        catch(...)
        {
            cout << "Unknown exception on clean up: " << endl;
        }
        iRetryIterationCount--;
    }
    while( iRetryIterationCount > 0 && !bSuccess);

    if(endpoint_set)
        free(endpoint);

    cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
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
            case 'v':
                verbose=true;
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
    if(output_file.is_open()) {
        cout.rdbuf( output_file.rdbuf() );
    }
}
