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

// ArrayClient.cpp : Defines the entry point for the console application.i
//
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO THIS FILE MAY ALSO REQUIRE CHANGES TO THE               */
/* C-EQUIVALENT FILE. PLEASE ENSURE THAT IT IS DONE.                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include <string>
using namespace std;

#include "ArrayTestPortType.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 100

int main(int argc, char* argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char* url="http://localhost:80/axis/MathOps";
    const char* server="localhost";
    const char* port="80";
    url = argv[1];
    bool bSuccess = false;
    int     iRetryIterationCount = 3;

    do
    {
        try
        {
            sprintf(endpoint, "%s", url);
            ArrayTestPortType ws(endpoint);
            //testing echoIntArray
            intArrayType arrin;
            intArrayType* arrout;
            xsd__int_Array arrayInput;
            int * array[ARRAYSIZE];
            for (x=0;x<ARRAYSIZE;x++)
                array[x] = new int(x + 1000);
            arrayInput.set(array,ARRAYSIZE);
            arrin.setintItem(&arrayInput);
            cout << "invoking echoIntArray..."<<endl;
            int outputSize=0;
            arrout=ws.echoIntArray(&arrin);
            for(x=0;x<ARRAYSIZE;x++)
                cout << *(arrout->intItem->get(outputSize)[x])<<endl;
            
            // Clear up input array
            for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
                delete array[deleteIndex];
            bSuccess = true;
        }
        catch(AxisException& e)
        {
            bool bSilent = false;

            if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
            {
                if( iRetryIterationCount > 0)
                    bSilent = true;
            }
            else
                iRetryIterationCount = 0;

            if( !bSilent)
                cout << "Exception : " << e.what() << endl;
        }
        catch(exception& e)
        {
            cout << "Unknown exception has occured"<<endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occured"<<endl;
        }
        iRetryIterationCount--;
    }
    while( iRetryIterationCount > 0 && !bSuccess);
    
    cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
    return 0;
}
