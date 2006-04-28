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
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber( const char * p);

typedef enum
{
        eAdd,
        eSub,
        eMul,
        eDiv
} EOPERATION;

int main( int argc, char * argv[])
{
    char *          pURL = "http://localhost:80/axis/Calculator";
    char *          pOpList[] = {"add", "sub", "mul", "div", "*"};
    int                     iValue1List[] = {2,  5,  23, 5879, 123,  76, 94, 3987, 432, 65, 0};
    int                     iValue2List[] = {3, 99, 243,    8, 987, 987, 45,  908, -45,  0};
    int                     iResult;
    int                     iIndex_Value1List = 0;
    int                     iIndex_Value2List = 0;
    EOPERATION      eOperation = eAdd;
    bool            bSuccess = false;
    int                     iRetryIterationCount = 3;
    char            cSign;
    int                     iIterationCount = 20000;
    int                     iIteration;

    signal( SIGILL, sig_handler);
    signal( SIGABRT, sig_handler);
    signal( SIGSEGV, sig_handler);
    signal( SIGFPE, sig_handler);

    if( argc > 0)
        pURL = argv[1];

    do
    {
        try
        {
            Calculator      ws( pURL);

            cout << "Invoke the same web service method " << iIterationCount << " times without closing the connection."
              << endl;

            for( iIteration = 0; iIteration < iIterationCount; iIteration++)
            {
                switch( eOperation)
                {
                    case eAdd:
                        {
                            iResult = ws.add( iValue1List[iIndex_Value1List],
                                              iValue2List[iIndex_Value2List]);
                            cSign = '+';
                            eOperation = eSub;
                            break;
                        }

                    case eSub:
                        {
                            iResult = ws.sub( iValue1List[iIndex_Value1List],
                                              iValue2List[iIndex_Value2List]);
                            cSign = '-';
                            eOperation = eMul;
                            break;
                        }

                    case eMul:
                        {
                            iResult = ws.mul( iValue1List[iIndex_Value1List],
                                              iValue2List[iIndex_Value2List]);
                            cSign = '*';
                            eOperation = eDiv;
                            break;
                        }

                    case eDiv:
                        {
                            iResult = ws.div( iValue1List[iIndex_Value1List],
                                              iValue2List[iIndex_Value2List]);
                            cSign = '/';
                            eOperation = eAdd;
                            break;
                        }
                }

                if( iIteration == iIterationCount / 4)
                    cout << "Quarter of the way there!" << endl;
                else if( iIteration == iIterationCount / 2)
                    cout << "Half of the way there!" << endl;
                else if( iIteration == (3 * iIterationCount) / 4)
                    cout << "Three quarters of the way there!" << endl;
                else if( iIteration == iIterationCount - 1)
                {
                    cout << "All the way there!" << endl;
                    bSuccess = true;
                }

                if( iValue1List[++iIndex_Value1List] == 0)
                    iIndex_Value1List = 0;

                if( iValue2List[++iIndex_Value2List] == 0)
                    iIndex_Value2List = 0;
            }
        }
        catch( AxisException& e)
        {
            bool bSilent = false;

            if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
            {
                if( iRetryIterationCount > 1)
                    bSilent = true;
            }
            else
                iRetryIterationCount = 0;

            if( !bSilent)
                cout << "Exception : " << e.what() << endl;
        }
        catch( exception& e)
        {
            cout << "Exception has occured:" << e.what() << endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occured" << endl;
        }

        if( !bSuccess)
        {
            iRetryIterationCount--;

            cout << "Iteration: " << iIteration << " " << iValue1List[iIndex_Value1List] << cSign <<
              iValue2List[iIndex_Value2List] << "=" << iResult << endl;
        }

    } while( iRetryIterationCount > 0 && !bSuccess);

    cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}

void sig_handler( int sig)
{
    signal( sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
    exit( 1);
}

