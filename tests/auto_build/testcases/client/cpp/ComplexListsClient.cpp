
/*
 * ComplexLists tests several things all at once.
 *
 * The areas being tested are:
 * 1. AXISCPP-487 - Elements of basic XSD types do not serialize namespace declaration
 * 2. AXISCPP-488 - Array types don't serialize namespace declarations
 * 3. AXISCPP-489 - Serializer not removing namespaces as they go out of scope
 *
 */


#include "ComplexLists.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/ComplexLists";

	if(argc>1) url = argv[1];

	try
	{
		sprintf(endpoint, "%s", url);
		ComplexLists* ws = new ComplexLists(endpoint);

		m_list ml;     // xsd__string array
		m_list mlnp;   // used for 1st namepair item of array
		m_list mlnp2;  // used for 2nd namepair item of array
		attrlist al;   // attrlist has namepair array
		namepair np1;  // namepair has m_list and name
		namepair np2;
		namepair_Array npArr;

		// m_list arg to numtilist
		ml.item.m_Array = new char*[ARRAYSIZE];   // make storage for array
		ml.item.m_Size = ARRAYSIZE;               // tell it how big it is
		ml.item.m_Array[0] = "never odd or even"; // should be returned in errortext element of attrlisterr
		ml.item.m_Array[1] = "any data string";   // add data

		// To set into namepair item of namepair array of attrlist arg of multilist
		mlnp.item.m_Array = new char*[ARRAYSIZE];
		mlnp.item.m_Size = ARRAYSIZE;
		mlnp.item.m_Array[0] = "Apache";
		mlnp.item.m_Array[1] = "Axis C++";

		// To set into namepair item of namepair array of attrlist arg of multilist
		mlnp2.item.m_Array = new char*[ARRAYSIZE];
		mlnp2.item.m_Size = ARRAYSIZE;
		mlnp2.item.m_Array[0] = "Test";
		mlnp2.item.m_Array[1] = "Complex";

		// set first namepair item to put into array
		np1.m_list_Ref = &mlnp;
		np1.name = "namepair1";

		// set second namepair item to put into array
		np2.m_list_Ref = &mlnp2;
		np2.name = "namepair2";

		// create a namepair array to add into attrlist
		npArr.m_Size=ARRAYSIZE;
		npArr.m_Array = new namepair*[ARRAYSIZE];
		npArr.m_Array[0]=&np1;
		npArr.m_Array[1]=&np2;

		// set attrlist argument
		al.item = npArr;

		attrlisterr* ale = ws->multilist(&ml, &al);
		if(ale) {
			// Should have an errortext string, an errorcode int and a m_list object returned
        	cout << ale->errortext << endl; // should be 'request successful'
			cout << ale->errorcode << endl; // should be 7
			cout << ale->attrlist_Ref->item.m_Array[0]->name << endl; // 'namepair return'
			cout << ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0] << endl; // 'never odd or even'
		} else {
			cout << "Deserialized response is NULL" << endl;
		}

		ale = ws->multilist((m_list*)NULL, &al);
		if(ale) {
			// Should have an errortext string, an errorcode int and a m_list object returned
        	cout << ale->errortext << endl; // 'request successful'
			cout << ale->errorcode << endl; // 007
			cout << ale->attrlist_Ref->item.m_Array[0]->name << endl; // 'namepair return'
			cout << ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0] << endl; // 'attrlist->m_list-item[0] was NULL'
		} else {
			cout << "Deserialized response is NULL" << endl;
		}

		// Have nil elements in response
		ale = ws->multilistnil((m_list*)NULL, &al);
		if(ale) {
			// Should have an errortext string, an errorcode int and a m_list object returned
        	cout << ale->errortext << endl; // empty
			cout << ale->errorcode << endl; // 0
			cout << ale->attrlist_Ref->item.m_Array[0]->name << endl; // empty
			cout << ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0] << endl;  // empty
		} else {
			cout << "Deserialized response is NULL" << endl;
		}

		ale = ws->complexlist(&al, "hoohah!", &al);
		if(ale) {
			// Should have an errortext string, an errorcode int and a m_list object returned
        	cout << ale->errortext << endl;
			cout << ale->errorcode << endl;
			cout << ale->attrlist_Ref->item.m_Array[0]->name << endl;
			cout << ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0] << endl;
		} else {
			cout << "Deserialized response is NULL" << endl;
		}

		delete ws;
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
	    cout << "Unknown exception has occured" << endl;
	}
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}

