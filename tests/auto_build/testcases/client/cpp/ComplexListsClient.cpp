// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


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

using namespace std;

void printResponse(attrlisterr* ale)
{
    if(ale)
    {
        if (ale->errortext)
        {
            cout << ale->errortext << endl;
        }
        else
        {
            cout << "ale->errortext is NULL" << endl;
        }
        
        if (ale->errorcode)
        {
            cout << ale->errorcode << endl;
        }
        else
        {
            cout << "ale->errorcode is NULL" << endl;
        }
        
		if (ale->attrlist_Ref != NULL)
		{
			if (ale->attrlist_Ref->item.m_Array[0] != NULL)
			{
				if (ale->attrlist_Ref->item.m_Array[0]->name != NULL)
				{
					cout << ale->attrlist_Ref->item.m_Array[0]->name << endl;
				}
				else
				{
					cout << "ale->attrlist_Ref->item.m_Array[0]->name is NULL" << endl;
				}

				if (ale->attrlist_Ref->item.m_Array[0]->m_list_Ref != NULL)
				{
					if (ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0]
						&& *(ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0]))
					{
						cout << ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0] << endl;
					}
					else
					{
						cout << "ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0]" << endl;
					}
				}
			}
		}
    }
    else
    {
        cout << "Deserialized response is NULL" << endl;
    }
}

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/ComplexLists";

	if(argc>1) url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
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
        printResponse(ale);

		ale = ws->multilist((m_list*)NULL, &al);
        printResponse(ale);

		// Have nil elements in response
		ale = ws->multilistnil((m_list*)NULL, &al);
        printResponse(ale);

		ale = ws->complexlist(&al, "hoohah!", &al);
        printResponse(ale);
		bSuccess = true;

		delete ws;
	}
	catch(AxisException& e)
	{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
				{
					bSilent = true;
				}
			}
			else
			{
				iRetryIterationCount = 0;
			}

            if( !bSilent)
			{
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}

