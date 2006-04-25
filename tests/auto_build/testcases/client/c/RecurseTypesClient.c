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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "RecurseTypesWS.h" 

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/RecurseTypes/services/sampleWS"

int main(int argc, char* argv[])
{ 
    AXISCHANDLE ws;

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    int returnValue = 1; // Assume Failure

    Type1 *input,*output;
    int i;
    Type1_Array arrayIn;
    Type1 ** array;
 
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0) 
        endpoint = argv[2];       
       
    ws = get_RecurseTypesWS_stub(endpoint);
               
    input = (Type1 *)Axis_Create_Type1();
    input->att_kind = axiscAxisNew(XSDC_STRING,strlen(Kind_CHEQUE) + 1);
    strcpy(input->att_kind, Kind_CHEQUE);
    input->kind = axiscAxisNew(XSDC_STRING,strlen("Check In") + 1);
    strcpy(input->kind, "Check In");

    array = (Type1 **)malloc(sizeof(Type1 *) * 10);

    for ( i = 0; i < 10; i++ )
    {
        array[i]=Axis_Create_Type1();
        array[i]->kind = axiscAxisNew(XSDC_STRING,strlen("Sample") + 1);
        strcpy(array[i]->kind, "Sample");
        array[i]->index = 0;
    }
    arrayIn.m_Array = array;
    arrayIn.m_Size = 10;
    arrayIn.m_Type = C_USER_TYPE;
    
    output = getInput(ws, input);

    printf("Result\n");
    if (exceptionOccurred == C_TRUE ||
        get_RecurseTypesWS_Status(ws) == AXISC_FAIL ||
        output == NULL)
       printf("FAILED\n");    
    else 
    {
      int outputSize = output->followings->m_Size;
      Type1 ** outArray = output->followings->m_Array;
      
      printf("\tAtt_kind = %s\n", output->att_kind);
      printf("\tKind = %s\n", output->kind);

      for ( i = 0; i < outputSize; i++ )
        printf("\tKind [%d] = %s\n", i, outArray[i]->kind);
        
      Axis_Delete_Type1((Type1 *)array, 1, 10);

      /* TODO need to free resources */

      returnValue = 0; // Success
    }

  printf("---------------------- TEST COMPLETE -----------------------------\n");
  
  return returnValue;
}
