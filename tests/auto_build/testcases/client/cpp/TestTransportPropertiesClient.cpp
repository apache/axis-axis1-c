/*
 * This client tests setting and getting the transport properties.
 * The test framework also verify the message content on the wire.
 */

#include "Calculator.hpp"
#include <stdio.h>
#include <iostream>

void printProperties(Calculator *obj);

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	int iResult;
	int rc=1;

	url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		ws.setTransportProtocol(APTHTTP1_1);
		ws.setTransportProperty("Accept-Language", " da, en-gb;q=0.8, en;q=0.7");
		ws.setTransportProperty("Accept-Language", "l1");
		ws.setTransportProperty("Date", "Mon Dec  6 13:37:06 GMT 2004");
		ws.setTransportProperty("Accept-Language", "l22");
		
		cout << "Full properties list " << endl;
		printProperties(&ws);

		//deleting the transport with specific key value
		ws.deleteTransportProperty("Accept-Language",2);

		cout << "After deleteTransportProperty(key,int) method  " << endl;
		printProperties(&ws);

		//Go to the last property and delete
		ws.getFirstTransportPropertyKey();
		ws.getNextTransportPropertyKey();
		ws.getNextTransportPropertyKey();
		ws.deleteCurrentTransportProperty();
		cout << "After deleteCurrentProperty method " << endl;
		printProperties(&ws);
		
		iResult = ws.add(2,3);
		printf("%d\n", iResult);
		rc=0;
	}
	catch(AxisException& e)
	{
		cout << "in AxisException block" << e.what() << endl;
	}
	catch(exception& e)
	{
		cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unspecified exception has occured" << endl;
	}
	return rc;
}
void printProperties(Calculator *obj)
{
	const char* transprop1;
	transprop1 = obj->getFirstTransportPropertyKey();
	do
	{
		transprop1 = obj->getCurrentTransportPropertyKey();
		cout << "current transport property key = " << transprop1 ;
		transprop1 = obj->getCurrentTransportPropertyValue();
		cout << " value = " << transprop1 << endl;
	}
	while ( (transprop1 = obj->getNextTransportPropertyKey()) != NULL);
	cout << "****************************************************** " << endl;
	return ;	
}
