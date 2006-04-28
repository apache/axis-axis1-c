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

#include "ExtensibilityQueryPortType.hpp"

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/testXSDANY";
    AnyType* pAny = new AnyType();
    pAny->_size = 2;
    pAny->_array = new char*[2];

    url = argv[1];

    pAny->_array[0] = strdup("<queryExpression><queryByServiceDataNames xsi:type=\"ns1:QNamesType\" xmlns:ns1=\"http://www.gridforum.org/namespaces/2003/03/OGSI\"><name>serviceDataName</name></queryByServiceDataNames></queryExpression>");
    pAny->_array[1] = strdup("<getQuoteResponse xmlns=\"http://www.getquote.org/test\"><result><name>Widgets Inc.</name><symbol>WID</symbol><public>true</public></result></getQuoteResponse>");

    string str;
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
    try{
        sprintf(endpoint, "%s", url);
        ExtensibilityQueryPortType* pStub = new ExtensibilityQueryPortType(endpoint);
        AnyType* pAnyReturn = pStub->query(pAny);
                if (!pAnyReturn)
                {
                        printf("Returned AnyType is null\ntest failed\n");
                        exit(1);
                }       
        for (int i=0; i<pAnyReturn->_size; i++)
        {
                        printf("\nSent xml string: \n%s\n", pAny->_array[i]);
                        printf("\nReturned xml string: \n%s\n", pAnyReturn->_array[i]);
        }
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
        printf("%s\n", e.getExceptionCode());
                        }
    }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    return 0;
}
