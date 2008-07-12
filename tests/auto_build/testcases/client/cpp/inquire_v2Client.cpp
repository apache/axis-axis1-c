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

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s [endpoint] ", argv[0]);
		exit(0);
	}

	sprintf(endpoint, argv[1]);
	Inquire ws(endpoint);

	bool bSuccess = false;
	int iRetryIterationCount = 3;

	do
	{
		try
		{
			char buffer[100];
			sprintf(buffer, "UUID:2524c425-656e-4eb2-8b13-080cfb081382");

			// TEST #1  OPERATION: TModelDetail* get_tModelDetail(Get_tModelDetail* Value0);
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
			
			Get_tModelDetail gtmd_input;
			gtmd_input.setgeneric(cpname);
			gtmd_input.settModelKey(&arrtModelKeys);

			printf("invoking get_tModelDetail...\n");

			TModelDetail* tmd_result = ws.get_tModelDetail(&gtmd_input);
			tModel_Array *result = tmd_result->gettModel();
			int outputSize=0;
			tModel ** arrayOut = result->get(outputSize);
			printf("tModel_Array size = %d\n", outputSize);
			for( i = 0; i < outputSize; i++ )
			{
				printf("tModel %d...\n", i + 1 );
				printf("     tModel Key Ref = %s\n", arrayOut[i]->tModelKey_Ref);
				printf("     Operator = %s\n", arrayOut[i]->_operator);
				printf("     Authorized Name = %s\n", arrayOut[i]->authorizedName);
				if(arrayOut[i]->name_Ref)
				    printf("     Name = %s\n", arrayOut[i]->name_Ref->name_value);
				int outputSizeDesc = 0;
				description ** arrayDesc= arrayOut[i]->description_Ref->get(outputSizeDesc);
				for( int j = 0; j < outputSizeDesc; j++)
				{
					printf("     Description %d = %s\n", j + 1, arrayDesc[j]->description_value);
				}

				if( arrayOut[i]->overviewDoc_Ref )
				   printf("     Overview URL = %s\n", arrayOut[i]->overviewDoc_Ref->overviewURL);
			
				if( arrayOut[i]-> categoryBag_Ref )
				{
					printf("categoryBag...\n");
					keyedReference_Array* kra = arrayOut[i]-> categoryBag_Ref->keyedReference_Ref;
					keyedReference ** krarray = kra->get(outputSize);
					for( i = 0; i < outputSize; i++ )
					{
						printf("keyedReference  %d...\n", i + 1 );
						printf("     tModelKey = %s\n", krarray[i]->tModelKey_Ref);
						printf("     keyName = %s\n", krarray[i]->keyName);
						printf("     keyValue = %s\n", krarray[i]->keyValue);
					}
				}
			}

			// TEST #2  OPERATION: BusinessDetail* get_businessDetail(Get_businessDetail* Value0);

			sprintf(buffer, "aea80cae-6cde-4eac-9feb-19ac9719ebb9");
			businessKey_Array arrBusinessKeys;
			businessKey * arrayBusiness = new businessKey[ARRAYSIZE];
			for (i = 0; i < ARRAYSIZE; i++)
			{
				arrayBusiness[i] = new char[100];
				strcpy(arrayBusiness[i],buffer);
			}
			arrBusinessKeys.set(arrayBusiness,ARRAYSIZE);
			
			Get_businessDetail gbd_input;
			gbd_input.setgeneric(cpname);
			gbd_input.setbusinessKey(&arrBusinessKeys);
			
			printf("invoking get_businessDetail ...\n");
			BusinessDetail* bd_result = ws.get_businessDetail(&gbd_input);
			
			businessEntity_Array* businessEntities = bd_result->getbusinessEntity();
			
			outputSize = 0;
			businessEntity ** arrayOutB = businessEntities->get(outputSize);
			printf("businessEntity_Array size = %d\n", outputSize);
			for( i = 0; i < outputSize; i++ )
			{
				printf( "Business Entity %d\n", i + 1 );
				printf("     Business Key Ref = %s\n", arrayOutB[i]->businessKey_Ref);
				printf("     Operator = %s\n", arrayOutB[i]->_operator);
				printf("     Authorized Name = %s\n", arrayOutB[i]->authorizedName);
				printf( "     Names... \n" );
				int outputSizeBE = 0;
				name** arrayBE = arrayOutB[i]->name_Ref->get(outputSizeBE);
				for( int j = 0; j < outputSizeBE; j++)
				{
					printf("         Name %d = %s\n", j + 1, arrayBE[j]->name_value);
				}

				if( arrayOutB[i]->businessServices_Ref )
				{
					printf( "     Business Services...\n" );
					int outputSizeBS = 0;
					businessService ** arrayOutBS = arrayOutB[i]->businessServices_Ref->businessService_Ref->get(outputSizeBS);
					for( int j = 0; j < outputSizeBS; j++ )
					{
						printf( "         Business Service %d...\n", j + 1 );
						printf( "             service key referance = %s\n", arrayOutBS[j]->serviceKey_Ref );
						printf( "             business key referance = %s\n", arrayOutBS[j]->businessKey_Ref );
						if( arrayOutBS[j]->bindingTemplates_Ref )
						{
							printf( "             Binding Templates...\n" );
							int outputSizeBT=0;
							bindingTemplate ** arrayOutBT = arrayOutBS[j]->bindingTemplates_Ref->bindingTemplate_Ref->get(outputSizeBT);
							for( int k = 0; k < outputSizeBT; k++ )
							{
								printf( "                 Access Point %d...\n", k + 1 );
								if( arrayOutBT[k]->accessPoint_Ref )
								{
									printf( "                     Point = %s\n", arrayOutBT[k]->accessPoint_Ref->accessPoint_value );
									printf( "                     URL Type = %s\n\n", arrayOutBT[k]->accessPoint_Ref->URLType_Ref );
								}
							}
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
	} while (iRetryIterationCount > 0&& !bSuccess);

	return 0;
}
