
/* Tests createNamespaceDecl(),createAttribute() and getAttributeValue() APIs in IHeaderBlock 
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
		const AxisChar *prefix="np";
		const AxisChar *uri="http://ws.apache.org/";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/");
		INamespace *Insp1=phb->createNamespaceDecl(prefix,uri);
		/*Adding same namespace declaration*/
		INamespace *Insp1a=phb->createNamespaceDecl(prefix,uri);
		/*Passing NULL as argument */
		INamespace *Insp1b=phb->createNamespaceDecl(NULL,NULL);
        if(Insp1b==NULL)
			cout << "Null returned for NULL arguments in createNamespaceDecl"<<endl;
		INamespace *Insp2=phb->createNamespaceDecl("np1","http://axis.apache.org/");
		const AxisChar *temp="apache";
		const AxisChar *localname="name";
		/*Testing the behaviour with NULL values */
		IAttribute *attr1=phb->createAttribute(NULL,NULL,NULL,NULL);
        IAttribute *attr2=phb->createAttribute(NULL,NULL,NULL);
		if(attr1==NULL && attr2==NULL)
			cout << "Null returned for NULL arguments in createAttribute"<<endl;
		IAttribute *Iattr1=phb->createAttribute(localname,prefix,temp);
		/*Attributes cannot have the same name  */
		IAttribute *Iattr1a=phb->createAttribute(localname,prefix,temp);
		IAttribute *Iattr2=phb->createAttribute(localname,"np1","","Axis");
		/*Attributes cannot have the same name*/
		IAttribute *Iattr2a=phb->createAttribute(localname,"np1","","Axis");
		/*Attributes cannot have the same name
		  Here prefix 'ns2' and 'np' are having same URI value.
		  So ns2:Name and np:Name can't appear in the same tag
		*/
		IAttribute *Iattr2b=phb->createAttribute(localname,"ns2","","Axis");
		IAttribute *Iattr3=phb->createAttribute(localname,"","","");	
		cout <<"name=" << phb->getAttributeValue("name","")<<endl;
		cout << "np:name=" << phb->getAttributeValue(localname,prefix)<<endl;
		cout << "np1:name=" << phb->getAttributeValue("name","np1")<<endl;
		if(phb->getAttributeValue(NULL,NULL)==NULL)
			cout<<"NULL returned for NULL argumets in getAttributeValue"<<endl;
		if(phb->getAttributeValue("name","nm")==NULL)
			cout<<"NULL returned for Non existing attribute"<<endl;
		if(phb->getAttributeValue("NAME","np1")==NULL)
			cout<<"NULL returned for Non existing Attribute"<<endl;
		if (strcmp(op, "add") == 0)
		{
			iResult=ws.add(i1, i2);			
			cout << iResult << endl;
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
