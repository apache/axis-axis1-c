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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#include <string>
using namespace std;

#include "InteropTestPortType.h"

#define ARRAYSIZE 2

int
main (int argc, char *argv[])
{
    int x;
    char buffer1[100];
    char endpoint[256];
    const char *server = "localhost";
    const char *port = "80";
    if (argc == 3)
    {
	server = argv[1];
	port = argv[2];
    }
    printf ("Usage :\n %s <server> <port>\n\n", argv[0]);
    //sprintf(endpoint, "http://%s:%s/axis/base", server, port);
    //endpoint for Axis Java sample
    sprintf (endpoint, "http://%s:%s/axis/base", server, port);

    try
    {
	InteropTestPortType ws (endpoint);

	//set end point (optional) 
	//ws.setEndPoint( "http://localhost:8080/axis/services/echo" );
	//set proxy (optional) 
	//ws.setProxy( "proxy.my.ibm.com", 80 );

	//set HTTP headers
	ws.setTransportProperty ("Accept-Language",
				 " da, en-gb;q=0.8, en;q=0.7");
	ws.setTransportProperty ("Accept-Language", "lang2");
	ws.setTransportProperty ("Accept-Language", "lang3");

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
	IHeaderBlock *phb = ws.createSOAPHeaderBlock ("TestHeader",
						      "http://ws.apache.org/axisCppTest/");

	//create parent node
	BasicNode *parentNode = phb->createChild (ELEMENT_NODE);
	parentNode->setLocalName ("Credentials");
	//create child node     
	BasicNode *childNode = phb->createChild (ELEMENT_NODE);
	childNode->setLocalName ("username");
	//create char node for value
	BasicNode *valueNode = phb->createChild (CHARACTER_NODE);
	valueNode->setValue ("Test User");
	//buld node tree
	childNode->addChild (valueNode);
	parentNode->addChild (childNode);

	//add another node set
	childNode = phb->createChild (ELEMENT_NODE);
	childNode->setLocalName ("password");

	valueNode = phb->createChild (CHARACTER_NODE);
	valueNode->setValue ("Test Password");

	childNode->addChild (valueNode);
	parentNode->addChild (childNode);

	phb->addChild (parentNode);

	//set second SOAP headers
	phb = ws.createSOAPHeaderBlock ("TestHeader2",
					"http://ws.apache.org/axisCppTest/");

	//create parent node
	parentNode = phb->createChild (ELEMENT_NODE);
	parentNode->setLocalName ("Credentials2");
	childNode = phb->createChild (ELEMENT_NODE);
	childNode->setLocalName ("username");
	valueNode = phb->createChild (CHARACTER_NODE);
	valueNode->setValue ("Test User");
	childNode->addChild (valueNode);
	parentNode->addChild (childNode);
	//add another node set
	childNode = phb->createChild (ELEMENT_NODE);
	childNode->setLocalName ("password");
	valueNode = phb->createChild (CHARACTER_NODE);
	valueNode->setValue ("Test Password");
	childNode->addChild (valueNode);
	parentNode->addChild (childNode);
	phb->addChild (parentNode);

	//set timeout
	ws.setTransportTimeout (4);

	printf ("Sending Requests to end point %s \n\n", endpoint);
	printf ("invoking echoString...\n");
	//testing echoString 
	string bigstring;
	for (int ii = 0; ii < 2; ii++)
	{
	    bigstring += "hello world ";
	}
	strcpy (buffer1, bigstring.c_str ());
	char *result = ws.echoString ("hello world");
	if (0 == strcmp (result, "hello world"))
	    printf ("successful\n");
	else
	    printf ("failed\n");

	if (result)
	    delete[]result;

	printf ("Test transport property accessors\n");
	printf ("First transport key = %s\n",
		ws.getFirstTransportPropertyKey ());
	printf ("First transport value = %s\n",
		ws.getCurrentTransportPropertyValue ());
	const char *key = NULL;
	int count = 1;
	while (key = ws.getNextTransportPropertyKey ())
	{
	    printf ("Next transport key = %s\n", key);
	    printf ("Next transport value = %s\n",
		    ws.getCurrentTransportPropertyValue ());
	    count++;
	    //test removal of last transport property
	    if (count == 3)
		ws.deleteCurrentTransportProperty ();
	}

	//ws.deleteTransportProperty("Accept-Language", 2);

	printf ("First header block no of children = %d\n",
		ws.getFirstSOAPHeaderBlock ()->getNoOfChildren ());
	IHeaderBlock *header = NULL;
	count = 1;
	while (header = ws.getNextSOAPHeaderBlock ())
	{
	    printf ("Next header block no of children = %d\n",
		    header->getNoOfChildren ());
	    count++;
	    //test removal of last SOAP header block
	    if (count == 2)
		ws.deleteCurrentSOAPHeaderBlock ();
	}

	//test removing SOAP header block using pointer
	header = ws.getFirstSOAPHeaderBlock ();
	ws.deleteSOAPHeaderBlock (header);
	//now the request should have no SOAP headers

	// testing echoStringArray 
	xsd__string_Array arrstr;
	arrstr.m_Array = new char *[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	for (int i = 0; i < ARRAYSIZE; i++)
	{
	    sprintf (buffer1, "%dth element of string array", i + 1);
	    arrstr.m_Array[i] = buffer1;
	}
	printf ("invoking echoStringArray...\n");

	xsd__string_Array arrstrResult = ws.echoStringArray (arrstr);

	if (arrstrResult.m_Array != NULL)
	{
	    printf ("successful\n");
	    for (int i = 0; i < arrstrResult.m_Size; i++)
		delete[]arrstrResult.m_Array[i];
	    delete[]arrstrResult.m_Array;
	}
	else
	    printf ("failed\n");
	//clean memory
	delete[]arrstr.m_Array;

	printf ("Stub Base class test end\n");
    }
    catch (AxisException & e)
    {
	printf ("Exception : %s\n", e.what ());
    }
    catch (exception & e)
    {
	printf ("Unknown exception has occured\n");
    }
    catch (...)
    {
	printf ("Unknown exception has occured\n");
    }
    return 0;
}
