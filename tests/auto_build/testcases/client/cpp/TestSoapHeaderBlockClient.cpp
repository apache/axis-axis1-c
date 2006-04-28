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

/* This test tests the createSOAPHeaderBlock (AxisChar* pachLocalName,AxisChar* pachUri,AxisChar* pachPrefix)
 * method in Stub class  
 */

#include "MathOps.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
        char endpoint[256];
    const char* url="http://localhost:80/axis/MathOps";
    int iResult=0;
    //AxisChar * localname = "    " ;

    url = argv[1];
    sprintf(endpoint, "%s", url);
    MathOps ws;
    ws.setEndPoint(url);


        /*create a header of the form:
        <SOAP-ENV:Header>
    <th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
    <Credentials>
    <username>Test User</username>
    <password>Test Password</password>
    </Credentials>
    </th:TestHeader>
    </SOAP-ENV:Header>
        */

    //set SOAP headers
    IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader", "http://ws.apache.org/axisCppTest/","th1");
    //IHeaderBlock *phb = ws.createSOAPHeaderBlock("      ", "          ", "   ");

    //create parent node
    BasicNode *parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials");
    //create child node
    BasicNode *childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username");
    //create char node for value
    BasicNode *valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User");
    //buld node tree
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password");

    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Password");

    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

    phb->addChild(parentNode);

    cout << "invoking MathOps div..." << endl;
    //testing add function
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
        try
        {
                iResult = ws.div(15,5);
                cout << iResult << endl;

                                bSuccess = true;
        }
        catch (AxisException& e)
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
                cout << e.what() << endl;
                        }
        }
        catch(...)
        {
                cout << "Unknown exception" << endl;
        }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    //test removing SOAP header block using pointer
    IHeaderBlock *header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);

                bSuccess = false;
                iRetryIterationCount = 3;

                do
                {
    try
    {
                iResult = ws.div(15,5);
                cout << iResult << endl;
                                bSuccess = true;
    }
    catch (AxisException& e)
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
                cout << e.what() << endl;
                        }
    }
    catch(...)
    {
        cout << "Unknown exception\n" << endl;
    }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);


    return 0;
}
                                                          
