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
        try
        {
                iResult = ws.div(15,5);
                cout << iResult << endl;

        }
        catch (AxisException& e)
        {
                cout << e.what() << endl;
        }
        catch(...)
        {
                cout << "Unknown exception" << endl;
        }

    //test removing SOAP header block using pointer
    IHeaderBlock *header = NULL;
    header = ws.getFirstSOAPHeaderBlock();
    ws.deleteSOAPHeaderBlock(header);

    try
    {
                iResult = ws.div(15,5);
                cout << iResult << endl;
    }
    catch (AxisException& e)
    {
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception\n" << endl;
    }


    return 0;
}
                                                          