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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */
#include <string>
#include <stdio.h>
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
    Inquire *ws = new Inquire(endpoint); 
    //ws->setProxy("localhost", 9090);

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
    try 
    {
        char buffer[100];
        sprintf(buffer, "UUID:39B8F710-F088-11D6-8F10-000629DC0A7B");

        tModelKey_Array arrtModelKeys;
		tModelKey * array = new tModelKey [ARRAYSIZE];        
        int i = 0;
        for (i = 0; i < ARRAYSIZE; i++)
        {
            array[i] = new char[100];
			strcpy(array[i],buffer);

        }
		arrtModelKeys.set(array,ARRAYSIZE);
        char* cpname = "2.0";
        
        printf("invoking get_tModelDetail...\n");
        tModel_Array *result = ws->get_tModelDetail(&arrtModelKeys, cpname);
		int outputSize=0;
		tModel ** arrayOut = result->get(outputSize);
        printf("tModel_Array size = %d\n", outputSize);
        for( i = 0; i < outputSize; i++ ) 
        {
            printf("tModel %d...\n", i + 1 );
            printf("\t tModel Key Ref = %s\n", arrayOut[i]->tModelKey_Ref);
            printf("\t Operator = %s\n", arrayOut[i]->_operator);
            printf("\t Authorized Name = %s\n", arrayOut[i]->authorizedName);
            if(arrayOut[i]->name_Ref)
                printf("\t Name = %s\n", arrayOut[i]->name_Ref->name_value);
				int outputSizeDesc = 0;
			    description ** arrayDesc= arrayOut[i]->description_Ref->get(outputSizeDesc);  
            for( int j = 0; j < outputSizeDesc; j++)
            {
                printf("\t Description %d = %s\n", j + 1,  arrayDesc[j]->description_value);
            }

            if( arrayOut[i]->overviewDoc_Ref )
                printf("\t Overview URL = %s\n", arrayOut[i]->overviewDoc_Ref->overviewURL);
        }

        sprintf(buffer, "D368F080-8423-11D6-9FFC-000C0E00ACDD" );
        businessKey_Array arrBusinessKeys;
		businessKey * arrayBusiness = new businessKey[ARRAYSIZE];        
        for (i = 0; i < ARRAYSIZE; i++)
        {
            arrayBusiness[i] = new char[100];
			strcpy(arrayBusiness[i],buffer);
        }
		arrBusinessKeys.set(arrayBusiness,ARRAYSIZE);

        printf("invoking get_businessDetail ...\n");
        //printf("businessEntity_Array size = %d\n", ws->get_businessDetail(arrBusinessKeys, cpname).m_Size);
        businessEntity_Array* businessEntities = ws->get_businessDetail(&arrBusinessKeys, cpname);
		outputSize = 0;
		businessEntity ** arrayOutB = businessEntities->get(outputSize);
        //businessEntity_Array get_businessDetail(businessKey_Array Value0,xsd__string Value1);
        printf("businessEntity_Array size = %d\n", outputSize);
        for( i = 0; i < outputSize; i++ ) 
        {
            printf( "Business Entity %d\n", i + 1 );
            printf("\t Business Key Ref = %s\n", arrayOutB[i]->businessKey_Ref);
            printf("\t Operator = %s\n", arrayOutB[i]->_operator);
            printf("\t Authorized Name = %s\n", arrayOutB[i]->authorizedName);
            printf( "\t Names... \n" );
			int outputSizeBE = 0;
			 name** arrayBE = arrayOutB[i]->name_Ref->get(outputSizeBE);
            for( int j = 0; j < outputSizeBE; j++)
            {
                printf("\t\t Description %d = %s\n", j + 1,  arrayBE[j]->name_value);
            }
           
            if( arrayOutB[i]->businessServices_Ref )
            {
                printf( "\t Business Services...\n" );
				int outputSizeBS = 0;
				businessService ** arrayOutBS = arrayOutB[i]->businessServices_Ref->businessService_Ref->get(outputSizeBS);
                for( int j = 0; j < outputSizeBS; j++ )
                {
                    printf( "\t\t Business Service %d...\n", j + 1 );
                    printf( "\t\t\t service key referance = %s\n", arrayOutBS[j]->serviceKey_Ref );
                    printf( "\t\t\t business key referance = %s\n", arrayOutBS[j]->serviceKey_Ref );
                    if( arrayOutBS[j]->bindingTemplates_Ref )
                    {
                         printf( "\t\t\t Binding Templates...\n" );
						 int outputSizeBT=0;
						 bindingTemplate ** arrayOutBT = arrayOutBS[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
                         for( int k = 0; k < outputSizeBT; k++ )
                         {
                            printf( "\t\t\t\t Access Point %d...\n", k + 1 );
                            if( arrayOutBT[k]->accessPoint_Ref )
                            {
                                printf( "\t\t\t\t\t Point = %s\n", arrayOutBT[k]->accessPoint_Ref->accessPoint_value );
                                printf( "\t\t\t\t\t URL Type = %s\n\n", arrayOutBT[k]->accessPoint_Ref->URLType_Ref );
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
