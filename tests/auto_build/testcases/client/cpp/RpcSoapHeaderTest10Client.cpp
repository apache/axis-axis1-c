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

#include "InteropTestPortType.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/AxisException.hpp>

#define ARRAYSIZE 2

int
main(int argc, char *argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    //sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    //endpoint for Axis CPP sample
    sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    InteropTestPortType ws(endpoint, APTHTTP1_1);

    /*
    <SOAP-ENV:Header>
    	<ns2:TestHeader xmlns:ns2="http://ws.apache.org/axisCppTest/" xmlns:namesp1="http://mynamespace.com">
	    <Credentials ns2:type="normal">
		<username ns2:usertype="normal_user">Test User</username>
		<password>Test Password</password>
	    </Credentials>
	</ns2:TestHeader>
    </SOAP-ENV:Header>
    */

    //set SOAP headers
    IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader", 
		"http://ws.apache.org/axisCppTest/");
    phb->createNamespaceDecl("namesp1", "http://mynamespace.com");

    //create parent node
    BasicNode *parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials");
    parentNode->createAttribute("type", "", "http://ws.apache.org/axisCppTest/", "normal");
    parentNode->createAttribute("scale", "", "http://ws.apache.org/axisCppTest/", "normal_scale");
    parentNode->createAttribute("lang1", "", "http://ws.apache.org/axisCppTest/", "normal_lang1");
    parentNode->createAttribute("lang2", "", "http://ws.apache.org/axisCppTest/", "normal_lang2");
    parentNode->createAttribute("lang3", "", "http://ws.apache.org/axisCppTest/", "normal_lang3");

    //create child node     
    BasicNode *childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username");
    childNode->createAttribute("usertype", "", "http://ws.apache.org/axisCppTest/", "normal_user");
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

    /* start testing the getters for SOAP Header Attributes*/
    IAttribute* pIAttribute1 = parentNode->getFirstAttribute();
    if (pIAttribute1)
    	printf("pIAttribute1 details = %s %s \n", pIAttribute1->getLocalName(), pIAttribute1->getURI());

    pIAttribute1 = NULL;
    int iTmpX = 0;
    while ((pIAttribute1 = parentNode->getNextAttribute()) != NULL) {
	printf("pIAttribute1 details = %s %s \n", pIAttribute1->getLocalName(), pIAttribute1->getURI());
	
	iTmpX++;
   	if (iTmpX==2) break; /*Just for a simple logic*/
    }

    pIAttribute1 = NULL;
    pIAttribute1 = parentNode->getCurrentAttribute();
    if (pIAttribute1)
        printf("pIAttribute1 details = %s %s \n", pIAttribute1->getLocalName(), pIAttribute1->getURI());

    pIAttribute1 = NULL;
    pIAttribute1 = parentNode->getLastAttribute();
    if (pIAttribute1)
    	printf("pIAttribute1 details = %s %s \n", pIAttribute1->getLocalName(), pIAttribute1->getURI());

    pIAttribute1 = NULL;
    pIAttribute1 = parentNode->getAttribute("", "http://ws.apache.org/axisCppTest/", "scale");
    if (pIAttribute1)
        printf("pIAttribute1 details = %s %s \n", pIAttribute1->getLocalName(), pIAttribute1->getURI());
    /*----end testing the getters for SOAP Header Attributes----- */

    printf("invoking echoString...\n");
    //testing echoString 
    try 
    {
    if (0 == strcmp(ws.echoString("hello world"), "hello world"))
	printf("successful\n");
    else
	printf("failed\n");
    }
    catch (AxisException& e)
    {
        printf("%s\n", e.what());
    }
    catch(...)
    {
        printf("Unknown exception\n");
    }

    printf("Soap Header test end\n");
    return 0;
}
