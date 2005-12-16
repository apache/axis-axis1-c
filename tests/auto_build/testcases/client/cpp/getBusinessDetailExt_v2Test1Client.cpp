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
 * @author James Jose
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
    //ws->setProxy("localhost", 9090);

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

	do
	{
		try 
		{
			char buffer[100];
			// Storing business Key to Buffer 
			sprintf(buffer, "aea80cae-6cde-4eac-9feb-19ac9719ebb9");			
             
			 /* Case1 :
			    In this we pass one business key and get back one business Entity and then displays the details*/
			businessKey_Array arrBusinessKeys;
			businessKey * arrayBusiness = new businessKey[ARRAYSIZE];  
			int i;
			for (i = 0; i < ARRAYSIZE; i++)
			 {
				 arrayBusiness[i] = new char[100];
				 strcpy(arrayBusiness[i],buffer);
			 }
			arrBusinessKeys.set(arrayBusiness,ARRAYSIZE);
			cout << "invoking get_businessDetailExt ...\n";			
			businessEntityExt_Array* businessEntityExtArr = ws->get_businessDetailExt(&arrBusinessKeys, cpname);
			outputSize = 0;
			businessEntityExt ** busEntityExt = businessEntityExtArr->get(outputSize);			
			cout << "businessEntityExt_Array size = " <<  outputSize << endl;
			for( i = 0; i < outputSize; i++ ) 
			{
				cout << "Business EntityExt " <<  i + 1 << endl;
				if(busEntityExt[i]->any1){
					cout <<"\tAny Size = " << busEntityExt[i]->any1->_size << endl;
					for (int s=0;s<busEntityExt[i]->any1->_size;s++)					
						cout <<"\tAny Value = " << s+1 << busEntityExt[i]->any1->_array[s]<<endl;
				}
				businessEntity *busEntity=busEntityExt[i]->businessEntity_Ref;				
				cout << "\t Business Key Ref = " << busEntity->businessKey_Ref<<endl;
				//printf("\t Operator = %s\n", arrayOutB[i]->_operator);
				cout << "\t Authorized Name = " << busEntity->authorizedName << endl;
				cout << "\t Names... \n" ;
				int outputSizeName = 0;

				//Display name of the business Entity

				name** arrayName = busEntity->name_Ref->get(outputSizeName);
				for( int j = 0; j < outputSizeName; j++)
				{
					cout << "\t\t Name " << j + 1 << " = " <<  arrayName[j]->name_value <<endl;
				} 

				//Display Description
				int outputSizeDesc=0;
				description ** arrayDesc = busEntity->description_Ref->get(outputSizeDesc);
				cout << "\t Description ... " << endl;
				for( int j = 0; j < outputSizeDesc; j++)
				{
					cout << "\t\t Description " << j+1 << " = " << arrayDesc[j]->description_value<< endl;
				} 

				//Display Contact Details
				int outputSizeContact=0;
				contact **arrayContact=busEntity->contacts_Ref->contact_Ref->get(outputSizeContact);
				cout << "\t Contact Information ... " << endl;
				for( int j = 0; j < outputSizeContact; j++)
				{
					cout << "\t\tContact information " << j+1 << endl;
					cout << "\t\t\t Person Name " << j+1 << " = " <<  arrayContact[j]->personName << endl;
					cout << "\t\t\t Use Type " << j+1 << " = " <<arrayContact[j]->useType << endl;
					int descSize = 0;
					description ** arrayCDesc= arrayContact[j]->description_Ref->get(descSize);
					for(int k=0;k<descSize;k++){
						cout << "\t\t\t Description = " << arrayCDesc[k]->description_value << endl;
					}
					int phoneSize=0;
					phone ** phoneArray = arrayContact[j]->phone_Ref->get(phoneSize);
					for(int k=0;k<phoneSize;k++){
						 cout << "\t\t\t Phone useType = " <<phoneArray[k]->useType << endl;
						 cout << "\t\t\t Phone Value = " << phoneArray[k]->phone_value<< endl;
					}
					int emailSize =0 ;
					email ** emailArray = arrayContact[j]->email_Ref->get(emailSize);
					for(int k=0;k<emailSize;k++){
						 cout << "\t\t\t email useType = " << emailArray[k]->useType << endl;
						 cout << "\t\t\t email Value = " <<emailArray[k]->email_value << endl;
					}

					int addressSize = 0;
					address ** addressArray = arrayContact[j]->address_Ref->get(addressSize);
					for(int k=0;k<addressSize;k++){
						 cout << "\t\t\t Address useType = " << addressArray[k]->useType << endl;
						 cout << "\t\t\t Address Value = " << addressArray[k]->sortCode << endl;
						 int addressLineSize = 0;
						 addressLine ** addLineArray = addressArray[k]->addressLine_Ref->get(addressLineSize);
						 for(int l=0;l<addressLineSize;l++){
							cout << "\t\t\t AddressLine keyName = " << addLineArray[l]->keyName << endl;
						    cout << "\t\t\t AddressLine keyValue = " << addLineArray[l]->keyValue << endl;
							cout << "\t\t\t AddressLine keyValue = " << addLineArray[l]->addressLine_value << endl;
						}
					}
				} 

				if( busEntity->businessServices_Ref )
				{
					cout <<  "\t Business Services...\n" ;
					int outputSizeBS = 0;
					businessService ** arrayOutBS = busEntity->businessServices_Ref->businessService_Ref->get(outputSizeBS);
					for( int j = 0; j < outputSizeBS; j++ )
					{
						cout <<  "\t\t Business Service " << j + 1 << endl;
						cout <<  "\t\t\t service key referance = " << arrayOutBS[j]->serviceKey_Ref << endl;
						cout <<  "\t\t\t business key referance = " <<  arrayOutBS[j]->serviceKey_Ref << endl;
						if( arrayOutBS[j]->bindingTemplates_Ref )
						{
							cout << "\t\t\t Binding Templates...\n" ;
							int outputSizeBT=0;
							bindingTemplate ** arrayOutBT = arrayOutBS[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
							for( int k = 0; k < outputSizeBT; k++ )
							{
								cout << "\t\t\t\t Access Point " <<  k + 1 << endl;
								if( arrayOutBT[k]->accessPoint_Ref )
								{
									cout << "\t\t\t\t\t Point = " << arrayOutBT[k]->accessPoint_Ref->accessPoint_value << endl;
									cout <<  "\t\t\t\t\t URL Type = " << arrayOutBT[k]->accessPoint_Ref->URLType_Ref << endl;
								}
							}
						}
					}
				}
				
				if(busEntity->categoryBag_Ref){
						int KRArraySize = 0;
						keyedReference ** KRArray = busEntity->categoryBag_Ref->keyedReference_Ref->get(KRArraySize);
						cout << "\t\t\t Category Bag Array Size .. " << KRArraySize << endl;
						for(int k=0;k<KRArraySize;k++){
							cout << "\t\t\t Category Bag" << k+1 << endl;
							cout << "\t\t\t\ttModelKey_Ref = " << KRArray[k]->tModelKey_Ref << endl;
							cout << "\t\t\t\ttKeyName = " <<KRArray[k]->keyName << endl;
							cout << "\t\t\t\ttKeyValue = " << KRArray[k]->keyValue << endl;                		
						}
				}
            //printf("overviewURL = %s\n", result.m_Array[i].overviewDoc_Ref->overviewURL);
			}


			/* Case2:
			   In this we pass 2 businessKeys and get back two business Entities */

			//businessKey_Array arrBusinessKeys1;
			arrayBusiness = new businessKey[2];        
			for (i = 0; i < 2; i++)
			 {
				 arrayBusiness[i] = new char[100];				 
			 } 
			 strcpy(arrayBusiness[0],buffer);
			 strcpy(arrayBusiness[1],"05e39405-6216-46bd-8f4c-dad67cda4c72");
			arrBusinessKeys.set(arrayBusiness,2);
			cout << "\n\ninvoking get_businessDetailExt ...\n";
			//printf("businessEntity_Array size = %d\n", ws->get_businessDetail(arrBusinessKeys, cpname).m_Size);
			//Inquire *ws1 = new Inquire(endpoint); 
			businessEntityExtArr = ws->get_businessDetailExt(&arrBusinessKeys, cpname);
			outputSize = 0;
			busEntityExt = businessEntityExtArr->get(outputSize);		
			//businessEntity_Array get_businessDetail(businessKey_Array Value0,xsd__string Value1);
			cout << "businessEntityExt_Array size = " <<  outputSize << endl;
			for( i = 0; i < outputSize; i++ ) 
			{
				cout << "Business Entity Ext " << i + 1 <<endl;
				if(busEntityExt[i]->any1){
					cout <<"\tAny Size = " << busEntityExt[i]->any1->_size << endl;
					for (int s=0;s<busEntityExt[i]->any1->_size;s++)					
						cout <<"\tAny Value = " << s+1 << busEntityExt[i]->any1->_array[s]<<endl;
				}
				businessEntity *busEntity=busEntityExt[i]->businessEntity_Ref;	
				cout << "\t Business Key Ref = " << busEntity->businessKey_Ref << endl;
				//cout << "\t Operator = " << arrayOutB1[i]->_operator << endl;
				cout << "\t Authorized Name = " << busEntity->authorizedName << endl;
				cout << "\t Names... \n";
				int outputSizeBE = 0;
				name** arrayBE = busEntity->name_Ref->get(outputSizeBE);
				for( int j = 0; j < outputSizeBE; j++)
				{
					cout << "\t\t Name " << j + 1 << " = " << arrayBE[j]->name_value << endl;
				}           
				if(  busEntity->businessServices_Ref )
				{
					cout <<  "\t Business Services...\n" ;
					int outputSizeBS = 0;
					businessService ** arrayOutBS = busEntity->businessServices_Ref->businessService_Ref->get(outputSizeBS);
					for( int j = 0; j < outputSizeBS; j++ )
					{
						cout << "\t\t Business Service " << j + 1 << endl;
						cout << "\t\t\t service key referance = " <<  arrayOutBS[j]->serviceKey_Ref << endl;
						cout << "\t\t\t business key referance = " << arrayOutBS[j]->serviceKey_Ref << endl;
						if( arrayOutBS[j]->bindingTemplates_Ref )
						{
							cout << "\t\t\t Binding Templates...\n" ;
							int outputSizeBT=0;
							bindingTemplate ** arrayOutBT = arrayOutBS[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
							for( int k = 0; k < outputSizeBT; k++ )
							{
								cout << "\t\t\t\t Access Point " << k + 1;
								if( arrayOutBT[k]->accessPoint_Ref )
								{
									cout << "\t\t\t\t\t Point = " << arrayOutBT[k]->accessPoint_Ref->accessPoint_value << endl;
									cout << "\t\t\t\t\t URL Type = " << arrayOutBT[k]->accessPoint_Ref->URLType_Ref << endl;
								}
							}
						}
					}
				}
            //printf("overviewURL = %s\n", result.m_Array[i].overviewDoc_Ref->overviewURL);
			}

			/* Case 3:
			   In this we pass a non existing Business Key */
		
			
			arrayBusiness = new businessKey[1];        
			for (i = 0; i < 1; i++)
			 {
				 arrayBusiness[i] = new char[100];	
				 strcpy(arrayBusiness[0],"05e39405-6216-46bd-8f4c-dad67cda4c15");
			 } 			
			arrBusinessKeys.set(arrayBusiness,1);			
			//printf("businessEntity_Array size = %d\n", ws->get_businessDetail(arrBusinessKeys, cpname).m_Size);
			//Inquire *ws2 = new Inquire(endpoint); 
			cout << "\n\ninvoking get_businessDetailExt ...\n";
			businessEntityExtArr = ws->get_businessDetailExt(&arrBusinessKeys, cpname);
			outputSize = 0;
			busEntityExt = businessEntityExtArr->get(outputSize);			
			//businessEntity_Array get_businessDetail(businessKey_Array Value0,xsd__string Value1);
			cout << "businessEntity_Array size = " << outputSize << endl;
			for( i = 0; i < outputSize; i++ ) 
			{
				cout << "Business Entity Ext " << i + 1 <<endl;
				if(busEntityExt[i]->any1){
					cout <<"\tAny Size = " << busEntityExt[i]->any1->_size << endl;
					for (int s=0;s<busEntityExt[i]->any1->_size;s++)					
						cout <<"\tAny Value = " << s+1 << busEntityExt[i]->any1->_array[s]<<endl;
				}
				businessEntity *busEntity=busEntityExt[i]->businessEntity_Ref;	
				cout << "\t Business Key Ref = " << busEntity->businessKey_Ref << endl;
				cout << "\t Authorized Name = " << busEntity->authorizedName;
				cout << "\t Names... \n";
				int outputSizeBE = 0;
				name** arrayBE = busEntity->name_Ref->get(outputSizeBE);
				for( int j = 0; j < outputSizeBE; j++)
				{
					cout << "\t\t Description  " << j + 1 << " = " << arrayBE[j]->name_value;
				}           
				if( busEntity->businessServices_Ref )
				{
					cout << "\t Business Services...\n" ;
					int outputSizeBS = 0;
					businessService ** arrayOutBS = busEntity->businessServices_Ref->businessService_Ref->get(outputSizeBS);
					for( int j = 0; j < outputSizeBS; j++ )
					{
						cout << "\t\t Business Service " << j + 1 << endl;
						cout << "\t\t\t service key referance = "<< arrayOutBS[j]->serviceKey_Ref << endl;
						cout << "\t\t\t business key referance = " << arrayOutBS[j]->serviceKey_Ref << endl;
						if( arrayOutBS[j]->bindingTemplates_Ref )
						{
							cout << "\t\t\t Binding Templates...\n" ;
							int outputSizeBT=0;
							bindingTemplate ** arrayOutBT = arrayOutBS[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
							for( int k = 0; k < outputSizeBT; k++ )
							{
								cout << "\t\t\t\t Access Point " << k + 1 << endl;
								if( arrayOutBT[k]->accessPoint_Ref )
								{
									cout << "\t\t\t\t\t Point = " << arrayOutBT[k]->accessPoint_Ref->accessPoint_value << endl;
									cout << "\t\t\t\t\t URL Type = " << arrayOutBT[k]->accessPoint_Ref->URLType_Ref << endl;
								}
							}
						}
					}
				}
            //printf("overviewURL = %s\n", result.m_Array[i].overviewDoc_Ref->overviewURL);
			}
			bSuccess = true;
			/*name* val1 = new name();
			val1->name_value = "TEST";
			tModelInfos* tModels =  ws->find_tModel(NULL, val1, NULL, NULL, "2.0",5);

			printf("tModel info size = %d\n", tModels->tModelInfo_Ref.m_Size);
			*/
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
