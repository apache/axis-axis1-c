/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

#include "../../gen_src/rpc/InteropTestPortType.h"
#include <axis/server/IHeaderBlock.hpp>
#include <axis/server/AxisException.hpp>

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    if (argc == 3)
    {
	server = argv[1];
	port = argv[2];
    }
    printf("Usage :\n %s <server> <port>\n\n", argv[0]);
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    InteropTestPortType ws(endpoint, APTHTTP);

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
    //create a element node
    BasicNode *pElementNode = phb->createChild(ELEMENT_NODE);
    pElementNode->setLocalName("ConfidentialStuff");
    //create child node     
    BasicNode *childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username");
    //create char node for value
    BasicNode *valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User");
    //buld node tree
    childNode->addChild(valueNode);
    pElementNode->addChild(childNode);

    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password");

    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Password");

    childNode->addChild(valueNode);
    pElementNode->addChild(childNode);
    
    parentNode->addChild(pElementNode);

    phb->addChild(parentNode);

    //set second SOAP headers
    phb = ws.createSOAPHeaderBlock("TestHeader2",
                                   "http://ws.apache.org/axisCppTest/");
                                                                                                                                                                            
    //create parent node
    parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials2");
     //create a element node
    pElementNode = phb->createChild(ELEMENT_NODE);
    pElementNode->setLocalName("ConfidentialStuff");

    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User");
    childNode->addChild(valueNode);
    pElementNode->addChild(childNode);
    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Password");
    childNode->addChild(valueNode);
    pElementNode->addChild(childNode);
    parentNode->addChild(pElementNode);
    phb->addChild(parentNode);


    printf("Sending Requests to end point %s \n\n", endpoint);
    printf("invoking echoString...\n");
    //testing echoString 
    try
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
	printf("successful\n");
    else
	printf("failed\n");
    }
    catch(AxisException& e)
    {
        printf("%s\n", e.what());
    }
    catch(...)
    {
        printf("unknown exception\n");
    }


    //test removing SOAP header block using pointer
    IHeaderBlock *header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);
    header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);
    //now the request should have no SOAP headers
    try
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
        printf("successful\n");
    else
        printf("failed\n");
    }
    catch(AxisException& e)
    {
        printf("%s\n", e.what());
    }
    catch(...)
    {
        printf("unknown exception\n");
    }

    printf("Soap Header test end\n");
    return 0;
}
