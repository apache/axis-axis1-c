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
                        // Storing Binding Key to Buffer 
                        sprintf(buffer, "uuid:2524c425-656e-4eb2-8b13-080cfb081382");   
             
                         /* Case1 :
                            In this we pass one tModel key and get back one tModel and then displays the details*/
                        tModelKey_Array arrTModelKeys;
                        tModelKey * arrayTModel = new tModelKey[ARRAYSIZE];  
                        int i;
                        for (i = 0; i < ARRAYSIZE; i++)
                         {
                                 arrayTModel[i] = new char[100];
                                 strcpy(arrayTModel[i],buffer);
                         }
                        arrTModelKeys.set(arrayTModel,ARRAYSIZE);
                        cout << "invoking get_tModelDetail ...\n";                      
                        tModel_Array* tModels = ws->get_tModelDetail(&arrTModelKeys, cpname);
                        outputSize = 0;
                        tModel ** arrayOutTModel = tModels->get(outputSize);                    
                        cout << "tModel_Array size = " <<  outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "tModel " <<  i + 1 << endl;
                                cout << "\t tModel Key Ref = " << arrayOutTModel[i]->tModelKey_Ref<<endl;
                                cout << "\t Authorized Name = " << arrayOutTModel[i]->authorizedName << endl;
                                //Display name of tModel                                
                                cout << "\t Name = " << arrayOutTModel[i]->name_Ref->name_value <<endl;                 

                                //Display Description
                                int outputSizeDesc=0;
                                description ** arrayDesc = arrayOutTModel[i]->description_Ref->get(outputSizeDesc);
                                cout << "\t Description ... " << endl;
                                for( int j = 0; j < outputSizeDesc; j++)
                                {
                                        cout << "\t\t Description " << j+1 << " = " << arrayDesc[j]->description_value<< endl;
                                }
                                
                                if(arrayOutTModel[i]->overviewDoc_Ref){
                                        cout << "\tOverviewDoc ... " << endl;
                                        int OVDescSize=0;
                                        description ** overviewDesc = arrayOutTModel[i]->overviewDoc_Ref->description_Ref->get(OVDescSize);
                                        for(int k=0;k<OVDescSize;k++){
                                                cout << "\t\t Description "<< k+1 << overviewDesc[k]->description_value << endl;
                                        }
                                        cout << "\t\toverviewURL = " << arrayOutTModel[i]->overviewDoc_Ref->overviewURL << endl;
                                }

                                if(arrayOutTModel[i]->categoryBag_Ref){
                                                int KRArraySize = 0;
                                                keyedReference ** KRArray = arrayOutTModel[i]->categoryBag_Ref->keyedReference_Ref->get(KRArraySize);
                                                cout << "\t Category Bag Array Size = " << KRArraySize << endl;
                                                for(int k=0;k<KRArraySize;k++){
                                                        cout << "\t\t Category Bag "<< k+1 << endl;
                                                        cout << "\t\t\ttModelKey_Ref = " << KRArray[k]->tModelKey_Ref << endl;
                                                        cout << "\t\t\ttKeyName = " <<KRArray[k]->keyName << endl;
                                                        cout << "\t\t\ttKeyValue = " << KRArray[k]->keyValue << endl;                           
                                                }
                                }

                        }


                        /* Case2:
                           In this we pass 2 tModelKeys and get back two tModels */
                        
                        arrayTModel = new tModelKey[2];        
                        for (i = 0; i < 2; i++)
                         {
                                 arrayTModel[i] = new char[100];                                 
                         } 
                         strcpy(arrayTModel[0],buffer);
                         strcpy(arrayTModel[1],"uuid:52ed8652-e2f8-4816-bc71-f48748f471bf");
                        arrTModelKeys.set(arrayTModel,2);
                        cout << "\n\ninvoking get_tModelDetail ...\n";                  
                        //Inquire *ws1 = new Inquire(endpoint); 
                        tModels = ws->get_tModelDetail(&arrTModelKeys, cpname);
                        outputSize = 0;
                        arrayOutTModel = tModels->get(outputSize);                      
                        cout << "tModel_Array size = " <<  outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "tModel " <<  i + 1 << endl;
                                cout << "\t tModel Key Ref = " << arrayOutTModel[i]->tModelKey_Ref<<endl;
                                cout << "\t Authorized Name = " << arrayOutTModel[i]->authorizedName << endl;
                                //Display name of tModel                                
                                cout << "\t Name = " << arrayOutTModel[i]->name_Ref->name_value <<endl;                 

                                //Display Description
                                int outputSizeDesc=0;
                                description ** arrayDesc = arrayOutTModel[i]->description_Ref->get(outputSizeDesc);
                                cout << "\t Description ... " << endl;
                                for( int j = 0; j < outputSizeDesc; j++)
                                {
                                        cout << "\t\t Description " << j+1 << " = " << arrayDesc[j]->description_value<< endl;
                                }
                                
                                if(arrayOutTModel[i]->overviewDoc_Ref){
                                        cout << "\tOverviewDoc ... " << endl;
                                        int OVDescSize=0;
                                        description ** overviewDesc = arrayOutTModel[i]->overviewDoc_Ref->description_Ref->get(OVDescSize);
                                        for(int k=0;k<OVDescSize;k++){
                                                cout << "\t\t Description "<< k+1 << overviewDesc[k]->description_value << endl;
                                        }
                                        cout << "\t\toverviewURL = " << arrayOutTModel[i]->overviewDoc_Ref->overviewURL << endl;
                                }

                                if(arrayOutTModel[i]->categoryBag_Ref){
                                                int KRArraySize = 0;
                                                keyedReference ** KRArray = arrayOutTModel[i]->categoryBag_Ref->keyedReference_Ref->get(KRArraySize);
                                                cout << "\t Category Bag Array Size .. " << KRArraySize << endl;
                                                for(int k=0;k<KRArraySize;k++){
                                                        cout << "\t Category Bag "<< k+1 << endl;
                                                        cout << "\t\ttModelKey_Ref = " << KRArray[k]->tModelKey_Ref << endl;
                                                        cout << "\t\ttKeyName = " <<KRArray[k]->keyName << endl;
                                                        cout << "\t\ttKeyValue = " << KRArray[k]->keyValue << endl;                             
                                                }
                                }
                        }
                        /* Case 3:
                           In this we pass a non existing tModel Key */

                        
                        arrayTModel = new tModelKey[1];        
                        for (i = 0; i < 1; i++)
                         {
                                 arrayTModel[i] = new char[100];        
                                 strcpy(arrayTModel[0],"05e39405-6216-46bd-8f4c-dad67cda4c15");
                         } 
                         
                        
                        arrTModelKeys.set(arrayTModel,1);                       
                        //Inquire *ws2 = new Inquire(endpoint); 
                        cout << "\n\ninvoking get_tModelDetail ...\n";
                        tModels = ws->get_tModelDetail(&arrTModelKeys, cpname);
                        outputSize = 0;
                        arrayOutTModel = tModels->get(outputSize);                      
                        cout << "tModel_Array size = " << outputSize << endl;
                        for( i = 0; i < outputSize; i++ ) 
                        {
                                cout << "tModel " <<  i + 1 << endl;
                                cout << "\t tModel Key Ref = " << arrayOutTModel[i]->tModelKey_Ref<<endl;
                                cout << "\t Authorized Name = " << arrayOutTModel[i]->authorizedName << endl;
                                //Display name of tModel                                
                                cout << "\t Name = " << arrayOutTModel[i]->name_Ref->name_value <<endl;                 

                                //Display Description
                                int outputSizeDesc=0;
                                description ** arrayDesc = arrayOutTModel[i]->description_Ref->get(outputSizeDesc);
                                cout << "\t Description ... " << endl;
                                for( int j = 0; j < outputSizeDesc; j++)
                                {
                                        cout << "\t\t Description " << j+1 << " = " << arrayDesc[j]->description_value<< endl;
                                }
                                
                                if(arrayOutTModel[i]->overviewDoc_Ref){
                                        cout << "\tOverviewDoc ... " << endl;
                                        int OVDescSize=0;
                                        description ** overviewDesc = arrayOutTModel[i]->overviewDoc_Ref->description_Ref->get(OVDescSize);
                                        for(int k=0;k<OVDescSize;k++){
                                                cout << "\t\t Description "<< k+1 << overviewDesc[k]->description_value << endl;
                                        }
                                        cout << "\t\toverviewURL = " << arrayOutTModel[i]->overviewDoc_Ref->overviewURL << endl;
                                }

                                if(arrayOutTModel[i]->categoryBag_Ref){
                                                int KRArraySize = 0;
                                                keyedReference ** KRArray = arrayOutTModel[i]->categoryBag_Ref->keyedReference_Ref->get(KRArraySize);
                                                cout << "\t Category Bag Array Size .. " << KRArraySize << endl;
                                                for(int k=0;k<KRArraySize;k++){
                                                        cout << "\t Category Bag "<< k+1 << endl;
                                                        cout << "\t\ttModelKey_Ref = " << KRArray[k]->tModelKey_Ref << endl;
                                                        cout << "\t\ttKeyName = " <<KRArray[k]->keyName << endl;
                                                        cout << "\t\ttKeyValue = " << KRArray[k]->keyValue << endl;                             
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
