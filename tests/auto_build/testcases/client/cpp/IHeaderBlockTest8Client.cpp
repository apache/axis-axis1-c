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

/* Tests createStdAttribute APIs for SOAPVER_1_1 in IHeaderBlock 
   Author @ James Jose
*/

#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";
        int i1=0, i2=0;
        int iResult;

        if(argc>1)
                url = argv[1];

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                i1 = 2;
                i2 = 3; 
                IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
                IAttribute *attr = phb->createStdAttribute(ACTOR,SOAP_VER_1_1);
                cout << attr->getLocalName() << " = " << attr->getValue()<<endl;
                iResult=ws.add(i1, i2); 
                cout << iResult << endl;
                Calculator ws1(endpoint);
                IHeaderBlock *phb1 = ws1.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
                IAttribute *attr1 = phb1->createStdAttribute(MUST_UNDERSTAND_TRUE,SOAP_VER_1_1);                
                cout << attr1->getLocalName() << " = " << attr1->getValue()<<endl;
                iResult=ws1.add(i1, i2);        
                cout << iResult << endl;
                Calculator ws2(endpoint);
                IHeaderBlock *phb2 = ws2.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
                IAttribute *attr2 = phb2->createStdAttribute(MUST_UNDERSTAND_FALSE,SOAP_VER_1_1);
                cout << attr2->getLocalName() << " = " << attr2->getValue()<<endl;
                iResult=ws2.add(i1, i2);        
                cout << iResult << endl;
                Calculator ws3(endpoint);
                IHeaderBlock *phb3 = ws3.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
                IAttribute *attr3 = phb3->createStdAttribute(ROLE_NEXT,SOAP_VER_1_1);
                if(attr3==NULL)
                  cout << "Null returned for non supporting standard attribute " << endl;
                iResult=ws3.add(i1, i2);        
                cout << iResult << endl;
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
                cout << "Unspecified exception has occured" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;     
        return 0;
}

