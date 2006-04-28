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
                bool bSuccess = false;
                int     iRetryIterationCount = 3;

                do
                {
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
                INamespace *Insp2=phb->createNamespaceDecl("np1","http://axis.apache.org/");

                IAttribute *attr1=phb->createAttribute(NULL,NULL,NULL,NULL);
        IAttribute *attr2=phb->createAttribute(NULL,NULL,NULL);
                if(attr1 || attr2)
                        cout << "Attribute returned for NULL arguments in createAttribute"<<endl;

                const AxisChar *temp="apache";
                const AxisChar *localname="name";       
                IAttribute *Iattr1=phb->createAttribute(localname,prefix,temp);         
                IAttribute *Iattr2=phb->createAttribute(localname,"np1","","Axis");             
                IAttribute *Iattr3=phb->createAttribute(localname,"","","");            

                cout << "np:name=" << phb->getAttributeValue(localname,prefix)<<endl;
                cout << "np1:name=" << phb->getAttributeValue("name","np1")<<endl;
                cout <<"name=" << phb->getAttributeValue("name","")<<endl;
                if(phb->getAttributeValue(NULL,NULL)!=NULL)
                        cout<<"NULL is not returned for NULL argumets in getAttributeValue"<<endl;
                if(phb->getAttributeValue("name","nm")!=NULL)
                        cout<<"NULL is not returned for Non existing attribute"<<endl;
                if(phb->getAttributeValue("NAME","np1")!=NULL)
                        cout<<"NULL is not returned for Non existing Attribute"<<endl;
                if (strcmp(op, "add") == 0)
                {
                        iResult=ws.add(i1, i2);                 
                        cout << iResult << endl;
                }
            bSuccess = true;

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
