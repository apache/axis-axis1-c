
/* Tests createImmdediateChild() APIs and getChild() API
@ Author : James Jose
*/


#include "Calculator.hpp"
#include <axis/IHeaderBlock.hpp>
#include <axis/IAttribute.hpp>
#include <axis/AxisException.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	const char* op = 0;
	int i1=0, i2=0;
	int iResult;
	url = argv[1];
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		op = "add";
		i1 = 2;
		i2 = 3; 
		AxisChar *localname="Name";
		AxisChar *prefix="np";
		AxisChar *uri="http://ws.apache.org/";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");		
		BasicNode * Bnode1=phb->createImmediateChild(ELEMENT_NODE,localname,prefix,uri, NULL);	
        BasicNode * Bnode2=phb->createChild(CHARACTER_NODE,NULL,NULL,NULL,"AXIS");
		BasicNode * Bnode3=phb->createChild(ELEMENT_NODE,"FirstPart","np1","http://ws.apache.org/", NULL);
		BasicNode * Bnode4=phb->createImmediateChild(ELEMENT_NODE,"Location","","http://ws.apache.org/", NULL);
		BasicNode * Bnode5=phb->createChild(CHARACTER_NODE,"","","","Sri Lanka");		
		BasicNode * Bnode6=phb->createImmediateChild(ELEMENT_NODE);
		Bnode6->setLocalName("Project");
		IAttribute *a=Bnode6->createAttribute("Type","Open Source");		    	
			cout << endl << "Project Type=" << a->getValue();
		BasicNode * Bnode7=phb->createChild(CHARACTER_NODE);
		Bnode7->setValue("AXISCPP");
		Bnode6->addChild(Bnode7);
		Bnode3->addChild(Bnode2);
		Bnode4->addChild(Bnode5);
		Bnode1->addChild(Bnode3);		
		BasicNode * Bnode8=phb->createImmediateChild(CHARACTER_NODE,"","","","This is a test ");
		BasicNode *Bnode9=phb->createImmediateChild(CHARACTER_NODE);
		Bnode9->setValue("message");
		cout << endl << "No Of Children=" << phb->getNoOfChildren();
	    BasicNode * firstnode=phb->getFirstChild();
		cout << endl << "First Node Name = " << firstnode->getLocalName();
		BasicNode * secondnode=phb->getChild(2);
		BasicNode * childnode=secondnode->getFirstChild();		
		cout << endl << "Second Node Name = " << secondnode->getLocalName();
		cout <<  " Value =" << childnode->getValue();
		BasicNode * lastnode=phb->getLastChild();
		cout << endl << "Last Child Value=" << lastnode->getValue();
		BasicNode *nullNode=phb->getChild(phb->getNoOfChildren()+1);
		if(nullNode==NULL)
			cout << endl << "NULL is returned for non existing node";
		if (strcmp(op, "add") == 0)
		{
			iResult=ws.add(i1, i2);	
			cout << endl << iResult << endl;
		}
	    
	}
	catch(AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
		cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unspecified exception has occured" << endl;
	}
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return 0;
}
