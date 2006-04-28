/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <axis/AxisException.hpp>
using namespace std;

#include "Inquire.hpp"

#define ARRAYSIZE 1 

char endpoint[256];

int
main(int argc, char *argv[])
{
    if( argc < 2 )
    {
        printf( "Usage: %s [endpoint] ", argv[0]);
        exit(0);
    }

    sprintf(endpoint, argv[1]); 
        char* cpname = "2.0";
        int outputSize=0;
    Inquire *ws = new Inquire(endpoint);   

                bool bSuccess = false;
                int     iRetryIterationCount = 3;

        do
        {
                try 
                {
                        char buffer[100];
                        // Storing service Key to Buffer 
                        sprintf(buffer, "f0aa27f0-88e7-4750-808a-a4d038a48ae7");                        
             
                         /* Case1 :
                            In this we pass one service key and get back one business service and then displays the details*/
                        serviceKey_Array arrServiceKeys;
                        serviceKey * arrayService = new serviceKey[ARRAYSIZE];  
                        int i;
                        for (i = 0; i < ARRAYSIZE; i++)
                         {
                                 arrayService[i] = new char[100];
                                 strcpy(arrayService[i],buffer);
                         }
                        arrServiceKeys.set(arrayService,ARRAYSIZE);
                        cout << "invoking get_serviceDetail ...\n";                     
                        businessService_Array* businessServices = ws->get_serviceDetail(&arrServiceKeys, cpname);
                        outputSize = 0;
                        businessService ** arrayOutService = businessServices->get(outputSize);                 
                        cout << "businessService_Array size = " <<  outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "Business Service " <<  i + 1 << endl;
                                cout << "\t Business Key Ref = " << arrayOutService[i]->businessKey_Ref<<endl;
                                cout << "\t Service Key Ref = " << arrayOutService[i]->serviceKey_Ref<<endl;                                                    
                                cout << "\t Names... \n" ;
                                int outputSizeName = 0;

                                //Display name of the business Service

                                name** arrayName = arrayOutService[i]->name_Ref->get(outputSizeName);
                                for( int j = 0; j < outputSizeName; j++)
                                {
                                        cout << "\t\t Name " << j + 1 << " = " <<  arrayName[j]->name_value <<endl;
                                } 

                                //Display Description
                                int outputSizeDesc=0;
                                description ** arrayDesc = arrayOutService[i]->description_Ref->get(outputSizeDesc);
                                cout << "\t Description ... " << endl;
                                for( int j = 0; j < outputSizeDesc; j++)
                                {
                                        cout << "\t\t Description " << j+1 << " = " << arrayDesc[j]->description_value<< endl;
                                }       
                                if( arrayOutService[i]->bindingTemplates_Ref )
                                {
                                        cout << "\t\t\t Binding Templates...\n" ;
                                        int outputSizeBT=0;
                                        bindingTemplate ** arrayOutServiceT = arrayOutService[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
                                        for( int k = 0; k < outputSizeBT; k++ )
                                        {
                                                cout << "\t\t\t\t Access Point " <<  k + 1 << endl;
                                                if( arrayOutServiceT[k]->accessPoint_Ref )
                                                {
                                                        cout << "\t\t\t\t\t Point = " << arrayOutServiceT[k]->accessPoint_Ref->accessPoint_value << endl;
                                                        cout <<  "\t\t\t\t\t URL Type = " << arrayOutServiceT[k]->accessPoint_Ref->URLType_Ref << endl;
                                                }
                                        }
                                }
                                
                                if(arrayOutService[i]->categoryBag_Ref){
                                                int KRArraySize = 0;
                                                keyedReference ** KRArray = arrayOutService[i]->categoryBag_Ref->keyedReference_Ref->get(KRArraySize);
                                                cout << "\t\t\t Category Bag Array Size .. " << KRArraySize << endl;
                                                for(int k=0;k<KRArraySize;k++){
                                                        cout << "\t\t\t Category Bag "<< k+1 << endl;
                                                cout << "\t\t\t\ttModelKey_Ref = " << KRArray[k]->tModelKey_Ref << endl;
                                                cout << "\t\t\t\ttKeyName = " <<KRArray[k]->keyName << endl;
                                                cout << "\t\t\t\ttKeyValue = " << KRArray[k]->keyValue << endl;                         
                                                }
                                }
           
                        }


                        /* Case2:
                           In this we pass 2 serviceKeys and get back two business Services */
                        
                        arrayService = new serviceKey[2];        
                        for (i = 0; i < 2; i++)
                         {
                                 arrayService[i] = new char[100];                                
                         } 
                         strcpy(arrayService[0],buffer);
                         strcpy(arrayService[1],"90757090-956e-4e13-82c0-4e85904ec076");
                        arrServiceKeys.set(arrayService,2);
                        cout << "\n\ninvoking get_serviceDetail ...\n";                 
                        //Inquire *ws1 = new Inquire(endpoint); 
                        businessServices = ws->get_serviceDetail(&arrServiceKeys, cpname);
                        outputSize = 0;
                        arrayOutService = businessServices->get(outputSize);                    
                        cout << "businessService_Array size = " <<  outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "Business Service " << i + 1 <<endl;
                                cout << "\t Business Key Ref = " << arrayOutService[i]->businessKey_Ref << endl;
                                cout << "\t Service Key Ref = " << arrayOutService[i]->serviceKey_Ref<<endl;                            
                                cout << "\t Names... \n";
                                int outputSizeName = 0;
                                name** arrayName = arrayOutService[i]->name_Ref->get(outputSizeName);
                                for( int j = 0; j < outputSizeName; j++)
                                {
                                        cout << "\t\t Name " << j + 1 << " = " << arrayName[j]->name_value << endl;
                                }           
                                if( arrayOutService[i]->bindingTemplates_Ref )
                                {
                                        cout << "\t\t\t Binding Templates...\n" ;
                                        int outputSizeBT=0;
                                        bindingTemplate ** arrayOutServiceT = arrayOutService[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
                                        for( int k = 0; k < outputSizeBT; k++ )
                                        {
                                                cout << "\t\t\t\t Access Point " << k + 1;
                                                if( arrayOutServiceT[k]->accessPoint_Ref )
                                                {
                                                        cout << "\t\t\t\t\t Point = " << arrayOutServiceT[k]->accessPoint_Ref->accessPoint_value << endl;
                                                        cout << "\t\t\t\t\t URL Type = " << arrayOutServiceT[k]->accessPoint_Ref->URLType_Ref << endl;
                                                }
                                        }
                                }                       
           
                        }

                        /* Case 3:
                           In this we pass a non existing Service Key */

                        
                        arrayService = new serviceKey[2];        
                        for (i = 0; i < 1; i++)
                         {
                                 arrayService[i] = new char[100];       
                                 strcpy(arrayService[0],"05e39405-6216-46bd-8f4c-dad67cda4c15");
                         } 
                         
                        
                        arrServiceKeys.set(arrayService,1);                     
                        //Inquire *ws2 = new Inquire(endpoint); 
                        cout << "\n\ninvoking get_serviceDetail ...\n";
                        businessServices = ws->get_serviceDetail(&arrServiceKeys, cpname);
                        outputSize = 0;
                        arrayOutService = businessServices->get(outputSize);                    
                        cout << "businessService_Array size = " << outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "Business Entity " << i + 1 << endl;
                                cout << "\t Business Key Ref = " << arrayOutService[i]->businessKey_Ref << endl;
                                cout << "\t Service Key Ref = " << arrayOutService[i]->serviceKey_Ref << endl;
                                cout << "\t Names... \n";
                                int outputSizeName = 0;
                                name** arrayName = arrayOutService[i]->name_Ref->get(outputSizeName);
                                for( int j = 0; j < outputSizeName; j++)
                                {
                                        cout << "\t\t Name  " << j + 1 << " = " << arrayName[j]->name_value;
                                }           
                                
                                if( arrayOutService[i]->bindingTemplates_Ref )
                                {
                                        cout << "\t\t\t Binding Templates...\n" ;
                                        int outputSizeBT=0;
                                        bindingTemplate ** arrayOutServiceT = arrayOutService[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
                                        for( int k = 0; k < outputSizeBT; k++ )
                                        {
                                                cout << "\t\t\t\t Access Point " << k + 1 << endl;
                                                if( arrayOutServiceT[k]->accessPoint_Ref )
                                                {
                                                        cout << "\t\t\t\t\t Point = " << arrayOutServiceT[k]->accessPoint_Ref->accessPoint_value << endl;
                                                        cout << "\t\t\t\t\t URL Type = " << arrayOutServiceT[k]->accessPoint_Ref->URLType_Ref << endl;
                                                }
                                        }
                                }           
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
        printf("Exception caught : %s\n", e.what());
                        }
    }
                iRetryIterationCount--;
                } while( iRetryIterationCount > 0 && !bSuccess);

    return 0;
}
