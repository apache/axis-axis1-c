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
#define NEWCOPY(ptr,str) {ptr=new char[strlen(str)+1]; strcpy(ptr,str);}

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
			int outputSize =0;
			const namepair ** output =ale->attrlist_Ref->getitem()->get(outputSize);
			//if (ale->attrlist_Ref->item.m_Array[0] != NULL)
			if (output[0] != NULL)
			{
				if (output[0]->name != NULL)
				{
					cout << output[0]->name << endl;
				}
				else
				{
					cout << "ale->attrlist_Ref->item.m_Array[0]->name is NULL" << endl;
				}

				if (output[0]->m_list_Ref != NULL)
				{
					outputSize = 0;
					const xsd__string * outString = output[0]->m_list_Ref->item->get(outputSize);
					if (outString[0]
						&& *(outString[0]))
					{
						cout << outString[0] << endl;
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
		m_list *mlnp = new m_list;   // used for 1st namepair item of array
		m_list *mlnp2 = new m_list;  // used for 2nd namepair item of array
		attrlist al;   // attrlist has namepair array
		namepair *np1 = new namepair;  // namepair has m_list and name
		namepair *np2 = new namepair;
		namepair_Array npArr;

		// m_list arg to numtilist
		xsd__string * array = new xsd__string[ARRAYSIZE];		
		NEWCOPY(array[0], "never odd or even"); // should be returned in errortext element of attrlisterr
		NEWCOPY(array[1], "any data string");   // add data
		ml.item->set(array,ARRAYSIZE);

		// To set into namepair item of namepair array of attrlist arg of multilist
		xsd__string * array1 = new xsd__string[ARRAYSIZE];		
		NEWCOPY(array1[0], "Apache");
		NEWCOPY(array1[1], "Axis C++");
		mlnp->item->set(array1,ARRAYSIZE);

		// To set into namepair item of namepair array of attrlist arg of multilist
		xsd__string * array2 = new xsd__string[ARRAYSIZE];		
		NEWCOPY(array2[0], "Test");
		NEWCOPY(array2[1], "Complex");
		mlnp2->item->set(array2,ARRAYSIZE);

		// set first namepair item to put into array
		np1->m_list_Ref = mlnp;
		NEWCOPY(np1->name, "namepair1");

		// set second namepair item to put into array
		np2->m_list_Ref = mlnp2;
		NEWCOPY(np2->name, "namepair2");

		// create a namepair array to add into attrlist
		namepair ** nArray = new namepair *[ARRAYSIZE];
		nArray[0]=np1;
		nArray[1]=np2;
		npArr.set(nArray,ARRAYSIZE);

		// set attrlist argument
		al.setitem(&npArr);

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

