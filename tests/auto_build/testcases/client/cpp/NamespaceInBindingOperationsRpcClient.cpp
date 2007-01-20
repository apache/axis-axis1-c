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

#include "StockQuotePortType.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <signal.h>
#include <iostream>

void sig_handler(int);
using namespace std;

int main( int argc, char * argv[])
{
    char *pszURL = "http://localhost:80/axis/MathOps";
    const char *pszOperation = NULL;

    signal( SIGILL,  sig_handler);
    signal( SIGABRT, sig_handler);
    signal( SIGSEGV, sig_handler);
    signal( SIGFPE,  sig_handler);

    pszURL = argv[1];

    try
    {
        StockQuotePortType ws(pszURL);
        xsd__float result = ws.getQuote("IBM");
        printf("obtained result %f\n", result);
    }
    catch( SoapFaultException& e)
    {
        char *faultCode   = (char *)e.getFaultCode();
        char *faultString = (char *)e.getFaultString();
        char *faultActor  = (char *)e.getFaultActor();
        
        if (!faultCode)  faultCode = "NULL";
        if (!faultString) faultString = "NULL";
        if (!faultActor) faultActor = "NULL";
        
        cout << "FaultCode = " << faultCode << endl;
        cout << "FaultString = " << faultString << endl;
        cout << "FaultActor = " << faultActor << endl;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown Exception: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unspecified Exception: " << endl;
    }


    cout << "---------------------- TEST COMPLETE -----------------------------" << endl;
    
    return 0;
}

void sig_handler( int sig)
{
    signal( sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
    exit(1);
}