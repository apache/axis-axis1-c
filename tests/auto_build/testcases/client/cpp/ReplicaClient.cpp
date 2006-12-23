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

#include <iostream>
#include "IAllTypesTestService.hpp"

int main( int argc, char * argv[])
{
        bool    bSuccess = false;
        int             iRetryIterationCount = 3;

        do
        {
                try
                {
                        const char *    pszURL = "http://localhost:9090/Replica/services/ReplicaImpl";

                        pszURL = argv[1];

                        IAllTypesTestService *                  pWS = new IAllTypesTestService( pszURL, APTHTTP1_1);
                        IAllTypesTestServiceReplica *   pServceReplica = new IAllTypesTestServiceReplica();
                        MyClass_Array *                                 pMyClassArray = new MyClass_Array();
                        int                                                             iMyClassSize = 1;
                        MyClass *                                               pMyClass = new MyClass[iMyClassSize];
                        xsd__NMTOKEN                                    myId = "1612";
                        xsd__string                                             myName = "Tester";
                        xsd__base64Binary *                             pMyValues = new xsd__base64Binary();
                        int                                                             iMyValuesDataSize = 10;
                        xsd__unsignedByte *                             pMyValuesData = new xsd__unsignedByte[iMyValuesDataSize];

                        for( int iCount = 0; iCount < iMyValuesDataSize; iCount++)
                        {
                                *(pMyValuesData + iCount) = (xsd__unsignedByte) (10 * iCount);
                        }

                        pMyValues->set( pMyValuesData, iMyValuesDataSize);

                        pMyClass->setid( myId);
                        pMyClass->setName( myName);
                        pMyClass->setValues( pMyValues);

                        pMyClassArray->set( &pMyClass, iMyClassSize);
                        pServceReplica->setMyClass( pMyClassArray);

                        pWS->miReplica( pServceReplica);

                        delete [] pMyClass;
                        delete pMyValues;
                        delete [] pMyValuesData;
                        delete pMyClassArray;
                        delete pServceReplica;
                        delete pWS;

                        cout << "Test completed without fault" << endl;

                        bSuccess = true;
                }
                catch( AxisException& e)
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
                catch( exception& e)
                {
                        cout << "Unknown exception has occured : " << e.what() << endl;
                }
                catch(...)
                {
                        cout << "Unknown exception has occured" << endl;
                }

                iRetryIterationCount--;
        } while( iRetryIterationCount > 0 && !bSuccess);

        cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

        return 0;
}