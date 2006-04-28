/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 * @author Roshan Weerasuriya (roshan@opensource.lk, roshanw@jkcsworld.com)
 */

#include <string>
using namespace std;

#include "InteropTestPortType.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    
        // Set the endpoint from command line argument if set
        if (argc > 1)
                strcpy(endpoint, argv[1]);


        
        InteropTestPortType ws(endpoint, APTHTTP1_1);

    /*create a header of the form:
       <SOAP-ENV:Header>
       <th:newName xmlns:th="http://ws.apache.org/axisCppTest/">
       <TestAuthHeader>
       <username>Test User</username>
       <password>Test Password</password>
       </TestAuthHeader>
       </th:newName>
       </SOAP-ENV:Header>
     */

    //set SOAP headers
    IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader", 
                "http://ws.apache.org/axisCppTest/");

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

    //set second SOAP headers
    phb = ws.createSOAPHeaderBlock("TestHeader2",
                                   "http://ws.apache.org/axisCppTest/");
                                                                                                                                                                            
    //create parent node
    parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials2");
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User2");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);
    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Password2");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("Key");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Key");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

    phb->addChild(parentNode);


    printf("invoking echoString...\n");
    //testing echoString 
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
    try
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
        printf("successful\n");
    else
        printf("failed\n");

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
        printf("%s\n", e.what());
                        }
    }
    catch(...)
    {
        printf("unknown exception\n");
    }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    //test removing SOAP header block using pointer
    IHeaderBlock *header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);

    header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);

    //now the request should have no SOAP headers

                bSuccess = false;
                iRetryIterationCount = 3;

                do
                {
    try 
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
        printf("successful\n");
    else
        printf("failed\n");

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
        printf("%s\n", e.what());
                        }
    }
    catch(...)
    {
        printf("unknown exception\n");
    }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    printf("Soap Header test end\n");
    return 0;
}
