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
#include "TestServicePortType.hpp"

int main( int argc, char * argv[])
{
    const char *    pszURL = "http://localhost:9090/OneWayOperation/services/OneWayOperationImpl";
    
    if (argc > 1)
        pszURL = argv[1];
     
    TestServicePortType pWS( pszURL, APTHTTP1_1);
    SampleBeanBoolean pSBB;
    SampleBeanComplex pSBC; 
    
	ABeanPortTypeComplexInput inputComplex;
	ABeanPortTypeBaseInput    inputBase;
        
    try
    {

    	
        SampleBeanComplex_Array BBArrayIn;
        SampleBeanComplex ** BBArray = NULL;                    
        BBArrayIn.set(BBArray,0);
        pSBB.setSampleBean(&BBArrayIn);
        pSBB.setSampleBeanBoolean(false_);
        
        inputBase.setElement(new SampleBeanBoolean(pSBB));
        pWS.aBeanPortTypeBase( &inputBase );  
        cout << "Called aBeanPortTypeBase()" << endl;

        SampleBeanComplex_Array BCArrayIn;
        SampleBeanComplex ** BCArray = NULL;                    
        BCArrayIn.set(BCArray,0);
        
        pSBC.setSampleBeanComplex(&BCArrayIn);
        pSBC.setBoolean(false_);
        
        inputComplex.setElement(new SampleBeanComplex(pSBC));
        pWS.aBeanPortTypeComplex( &inputComplex);
        cout << "Called aBeanPortTypeComplex()" << endl;

        cout << "Calling aBeanPortTypeComplex() to initiate fault processing" << endl;
        pWS.aBeanPortTypeComplex( &inputComplex);
        
        cout << "Calling aBeanPortTypeComplex() to see everything OK after fault processing" << endl;
        pWS.aBeanPortTypeComplex( &inputComplex);
    }
    catch( SoapFaultException& e)
    {
        char *faultCode   = (char *)e.getFaultCode();
        char *faultString = (char *)e.getFaultString();
        char *faultActor  = (char *)e.getFaultActor();
        
        if (!faultCode)  faultCode = "NULL";
        if (!faultString) faultString = "NULL";
        if (!faultActor) faultActor = "NULL";
        
        cout << "  FaultCode = " << faultCode << endl;
        cout << "  FaultString = " << faultString << endl;
        cout << "  FaultActor = " << faultActor << endl;
        cout << "  SoapFaultException: " << e.what() << endl;
    }    
    catch( AxisException& e)
    {
        cout <<  e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown exception has occured : " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }

    try
    {
        cout << "Calling aBeanPortTypeComplex() to see everything OK after fault processing" << endl;
        pWS.aBeanPortTypeComplex( &inputComplex);
    }
    catch( SoapFaultException& e)
    {
        char *faultCode   = (char *)e.getFaultCode();
        char *faultString = (char *)e.getFaultString();
        char *faultActor  = (char *)e.getFaultActor();
        
        if (!faultCode)  faultCode = "NULL";
        if (!faultString) faultString = "NULL";
        if (!faultActor) faultActor = "NULL";
        
        cout << "  FaultCode = " << faultCode << endl;
        cout << "  FaultString = " << faultString << endl;
        cout << "  FaultActor = " << faultActor << endl;
        cout << "  SoapFaultException: " << e.what() << endl;
    }    
    catch( AxisException& e)
    {
        cout <<  e.what() << endl;
    }
    catch( exception& e)
    {
        cout << "Unknown exception has occured : " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }

    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}