/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <axis/server/AxisException.hpp>
using namespace std;

#include "Inquire.h"
#include "InquireService_AxisClientException.h"

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


    try 
    {
        char buffer[100];
        sprintf(buffer, "UUID:39B8F710-F088-11D6-8F10-000629DC0A7B");

        tModelKey_Array arrtModelKeys;
        arrtModelKeys.m_Array = new char *[ARRAYSIZE];
        arrtModelKeys.m_Size = ARRAYSIZE;
        for (int i = 0; i < ARRAYSIZE; i++)
        {
            arrtModelKeys.m_Array[i] = buffer;
        }
        char* cpname = "2.0";
        
        printf("invoking get_tModelDetail...\n");
        tModel_Array result = ws->get_tModelDetail(arrtModelKeys, cpname);
        printf("tModel_Array size = %d\n", result.m_Size);
        for( int i = 0; i < result.m_Size; i++ ) 
        {
            printf("tModel %d...\n", i + 1 );
            printf("\t tModel Key Ref = %s\n", result.m_Array[i].tModelKey_Ref);
            printf("\t Operator = %s\n", result.m_Array[i]._operator);
            printf("\t Authorized Name = %s\n", result.m_Array[i].authorizedName);
            if(result.m_Array[i].name_Ref)
                printf("\t Name = %s\n", result.m_Array[i].name_Ref->name_value);
            for( int j = 0; j < result.m_Array[i].description_Ref.m_Size; j++)
            {
                printf("\t Description %d = %s\n", j + 1,  result.m_Array[i].description_Ref.m_Array[j].description_value);
            }

            if( result.m_Array[i].overviewDoc_Ref )
                printf("\t Overview URL = %s\n", result.m_Array[i].overviewDoc_Ref->overviewURL);
        }

        sprintf(buffer, "D368F080-8423-11D6-9FFC-000C0E00ACDD" );
        businessKey_Array arrBusinessKeys;
        arrBusinessKeys.m_Array = new char *[ARRAYSIZE];
        arrBusinessKeys.m_Size = ARRAYSIZE;
        for (int i = 0; i < ARRAYSIZE; i++)
        {
            arrBusinessKeys.m_Array[i] = buffer;
        }

        printf("invoking get_businessDetail ...\n");
        //printf("businessEntity_Array size = %d\n", ws->get_businessDetail(arrBusinessKeys, cpname).m_Size);
        businessEntity_Array businessEntities = ws->get_businessDetail(arrBusinessKeys, cpname);
        //businessEntity_Array get_businessDetail(businessKey_Array Value0,xsd__string Value1);
        printf("businessEntity_Array size = %d\n", businessEntities.m_Size);
        for( int i = 0; i < businessEntities.m_Size; i++ ) 
        {
            printf( "Business Entity %d\n", i + 1 );
            printf("\t Business Key Ref = %s\n", businessEntities.m_Array[i].businessKey_Ref);
            printf("\t Operator = %s\n", businessEntities.m_Array[i]._operator);
            printf("\t Authorized Name = %s\n", businessEntities.m_Array[i].authorizedName);
            printf( "\t Names... \n" );
            for( int j = 0; j < businessEntities.m_Array[i].name_Ref.m_Size; j++)
            {
                printf("\t\t Description %d = %s\n", j + 1,  businessEntities.m_Array[i].name_Ref.m_Array[j].name_value);
            }
            
            if( businessEntities.m_Array[i].businessServices_Ref )
            {
                printf( "\t Business Services...\n" );
                for( int j = 0; j < businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Size; j++ )
                {
                    printf( "\t\t Business Service %d...\n", j + 1 );
                    printf( "\t\t\t service key referance = %s\n", businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].serviceKey_Ref );
                    printf( "\t\t\t business key referance = %s\n", businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].serviceKey_Ref );
                    if( businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].bindingTemplates_Ref )
                    {
                         printf( "\t\t\t Binding Templates...\n" );
                         for( int k = 0; k < businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].bindingTemplates_Ref->bindingTemplate_Ref.m_Size; k++ )
                         {
                            printf( "\t\t\t\t Access Point %d...\n", k + 1 );
                            if( businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].bindingTemplates_Ref->bindingTemplate_Ref.m_Array[k].accessPoint_Ref )
                            {
                                printf( "\t\t\t\t\t Point = %s\n", businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].bindingTemplates_Ref->bindingTemplate_Ref.m_Array[k].accessPoint_Ref->accessPoint_value );
                                printf( "\t\t\t\t\t URL Type = %s\n\n", businessEntities.m_Array[i].businessServices_Ref->businessService_Ref.m_Array[j].bindingTemplates_Ref->bindingTemplate_Ref.m_Array[k].accessPoint_Ref->URLType_Ref );
                            }
                         }
                    }
                }
            }
            //printf("overviewURL = %s\n", result.m_Array[i].overviewDoc_Ref->overviewURL);
        }

        
        /*name* val1 = new name();
        val1->name_value = "TEST";
        tModelInfos* tModels =  ws->find_tModel(NULL, val1, NULL, NULL, "2.0",5);

        printf("tModel info size = %d\n", tModels->tModelInfo_Ref.m_Size);
        */
    } 
    catch(InquireService_AxisClientException& e)
    {
        printf("Exception caught : %s\n", e.what());
        printf("Exception caught : %d\n", e.getExceptionCode());
    }
    catch(AxisException& e)
    {
        printf("Exception caught : %s\n", e.what());
    }
}
