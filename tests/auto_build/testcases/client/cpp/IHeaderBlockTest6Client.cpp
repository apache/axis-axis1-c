
/*This program tests clone() API in the IHeaderBlock class
@ Author : James Jose
*/


#include "Calculator.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
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
		IHeaderBlock *phb=ws.createSOAPHeaderBlock("TestHeader","http://apache.com","np");
		phb->createImmediateChild(CHARACTER_NODE,"","","","Test Message");
		IHeaderBlock *cl=phb->clone();
		cl->createImmediateChild(ELEMENT_NODE,"Name","","","");
		cout << "No of Child in clone=" << cl->getNoOfChildren();
		cout << endl << "No of Child in original=" << phb->getNoOfChildren();
		BasicNode * bn=phb->getFirstChild();		
		bn->setValue("Axis");
		cout << endl << "First Child Value=" << bn->getValue();
		BasicNode *bn1=cl->getFirstChild();
		BasicNode *bn2=cl->getLastChild();		
		cout << endl << "First Child Value in clone=" << bn1->getValue();
		cout << endl << "Last Child Name in clone=" << bn2->getLocalName();
		op = "add";
		i1 = 2;
		i2 = 3;
		if (strcmp(op, "add") == 0)
		{
			iResult = ws.add(i1, i2);
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
