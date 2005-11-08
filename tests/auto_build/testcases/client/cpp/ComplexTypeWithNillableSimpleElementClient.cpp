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

#include <iostream>
#include "ComplexTypeWithNillableSimpleElement.hpp"

void main( int argc, char* argv[])
{
	char *	pszEndpoint = "http://localhost:9080/ComplexTypeWithNillableSimpleElement";

    if( argc > 1)
	{
        pszEndpoint = argv[1];
	}

    try
    {
		ComplexTypeWithNillableSimpleElement *	pWS = new ComplexTypeWithNillableSimpleElement( pszEndpoint, APTHTTP1_1);

		SimpleComplexType *	pSCTI = new SimpleComplexType();
		SimpleComplexType * pSCTO = NULL;
		xsd__int *			pI = new xsd__int();
		xsd__int			iInput = 1738;
		xsd__int			iOutput = 8371;

		*pI = iInput;

		pSCTI->setcomplexTypeElement( pI);

		pSCTO = pWS->echo( pSCTI);

		cout << "The output should be the reverse of the input." << endl <<
			 "Input = " << *pI << " Output = " << *pSCTO->getcomplexTypeElement() << endl <<
			 (iOutput == *pSCTO->getcomplexTypeElement() ? "Success" : "Failed") << endl;

		delete pI;
		delete pSCTI;
		delete pSCTO;
		delete pWS;
    }
    catch( AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown exception has occured: " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }

    cout << "---------------------- TEST COMPLETE -----------------------------" << endl;

	return;
}