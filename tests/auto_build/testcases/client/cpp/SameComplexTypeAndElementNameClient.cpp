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
#include "TestServicePortType.hpp"

int main( int argc, char * argv[])
{
        bool    bSuccess = false;
        int             iRetryIterationCount = 3;

        do
        {
                try
                {
                        const char *    pszURL = "http://localhost:9090/SameComplexTypeAndElementName/services/SameComplexTypeAndElementNameSoapImpl";

                        pszURL = argv[1];

                        TestServicePortType *   pWS = new TestServicePortType( pszURL, APTHTTP1_1);
                        SampleBeanBoolean *             pSBB = new SampleBeanBoolean();
                        SampleBeanComplex *             pSBC = new SampleBeanComplex();

                        SampleBeanComplex_Array BBArrayIn;
                        SampleBeanComplex ** BBArray = NULL;                    
                        BBArrayIn.set(BBArray,0);
                        pSBB->setSampleBean(&BBArrayIn);
                        pSBB->setSampleBeanBoolean(false_);
        
                        pWS->aBeanPortTypeBase( pSBB);  
                        cout << "Called aBeanPortTypeBase()" << endl;

                        SampleBeanComplex_Array BCArrayIn;
                        SampleBeanComplex ** BCArray = NULL;                    
                        BCArrayIn.set(BCArray,0);
                        
                        pSBC->setSampleBeanComplex(&BCArrayIn);
                        pSBC->setBoolean(false_);
                        pWS->aBeanPortTypeComplex( pSBC);

                        cout << "Called aBeanPortTypeComplex()" << endl;

                        delete pSBC;
                        delete pSBB;
                        delete pWS;

                        bSuccess = true;
                }
                catch( AxisException& e)
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

        if( bSuccess)
        {
                cout << "---------------------- TEST PASSED -----------------------------" << endl;
        }
        else
        {
                cout << "---------------------- TEST FAILED -----------------------------" << endl;
        }
        return 0;
}