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


/* Tests setPrefix() and getPrefix()in IAttribute class
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
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		Calculator ws(endpoint);
		const char *prefix="nsp";
		IHeaderBlock *phb = ws.createSOAPHeaderBlock("TestHeader","http://ws.apache.org/","nsp");
		IAttribute *attr1=phb->createAttribute("Name","ns","AXIS");
		/* Tests for NULL Value */
		cout<<attr1->setPrefix(NULL)<<endl;
		cout<<attr1->setPrefix(prefix)<<endl;
		BasicNode *bn=phb->createImmediateChild(ELEMENT_NODE,"Project","","","");
		IAttribute *attr2=bn->createAttribute("TYPE","Open Source");
		/* Tests for non declared namespace prefix */
		cout<<attr2->setPrefix("nd")<<endl;
		cout << "Header Attribute Prefix = " << attr1->getPrefix()<<endl;
		cout << "Child Node Attribute Prefix = " << attr2->getPrefix()<<endl;
		op = "add";
		i1 = 2;
		i2 = 3;
		if (strcmp(op, "add") == 0)
		{
			iResult = ws.add(i1, i2);
			cout  << iResult << endl;
			bSuccess = true;
		}
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
		cout << "Unspecified exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;	
	return 0;
}

