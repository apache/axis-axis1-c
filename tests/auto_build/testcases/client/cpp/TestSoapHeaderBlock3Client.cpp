/* This test tests the getNextSOAPHeaderBlock()
 * method in Stub class  
 */

#include "MathOps.hpp"
#include <iostream>
int main(int argc, char *argv[])
{
	char endpoint[256];
    const char* url="http://localhost:80/axis/MathOps";
    int iResult=0;
    
    url = argv[1];
    sprintf(endpoint, "%s", url);
    MathOps ws;
    ws.setEndPoint(url);


	/*create a header of the form:
	<SOAP-ENV:Header>
    <th:TestHeader xmlns:th="http://ws.apache.org/axisCppTest/">
    <Credentials1>
    <username>Test User</username>
    <password>Test Password</password>
    </Credentials1>
    </th:TestHeader>
    </SOAP-ENV:Header>
	*/
	
	

    //creating  first SOAP header block 
    IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader1", "http://ws.apache.org/axisCppTest/");
	
    //create parent node
    BasicNode *parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials1");
    BasicNode *childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username1");
    BasicNode *valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User1");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password1");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test Password1");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);

	phb->addChild(parentNode);
	
	//Creating second SOAP header block
	phb = ws.createSOAPHeaderBlock("TestHeader2",
                                   "http://ws.apache.org/axisCppTest/");
                                                                                                                                                                            
    //create parent node
    parentNode = phb->createChild(ELEMENT_NODE);
    parentNode->setLocalName("Credentials2");
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("username2");
    valueNode = phb->createChild(CHARACTER_NODE);
    valueNode->setValue("Test User2");
    childNode->addChild(valueNode);
    parentNode->addChild(childNode);
    //add another node set
    childNode = phb->createChild(ELEMENT_NODE);
    childNode->setLocalName("password2");
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

	cout << "invoking MathOps div..." << endl;
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
	
   
   IHeaderBlock *header = NULL;
   header = ws.getFirstSOAPHeaderBlock();
   header = ws.getNextSOAPHeaderBlock();
   ws.deleteSOAPHeaderBlock(ws.getCurrentSOAPHeaderBlock());
   header = ws.getFirstSOAPHeaderBlock();
   ws.deleteCurrentSOAPHeaderBlock();  
   
   //to test weather getNextSOAPHeaderBlock returns NULL when there are no header blocks exist.
   header = ws.getNextSOAPHeaderBlock();
   if ( header == NULL)
	   cout << "header is null" << endl ;
   else
	   cout << header << endl ;

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
                                 