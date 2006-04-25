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
#include "SimpleTypeInnerUnboundedInOutputWS.h" 

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/SimpleTypeInnerUnboundedInOutput/services/sampleWS"


int main(int argc, char* argv[])
{ 
    AXISCHANDLE ws;
    
    int returnValue = 1; // Assume failure
    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    
    Type1* result;
    int i;
    xsdc__int size = 10;
    
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0) 
        endpoint = argv[2];      
        
    ws = get_SimpleTypeInnerUnboundedInOutputWS_stub(endpoint);

    result = getInput(ws, &size);

    if (exceptionOccurred == C_TRUE ||
        get_SimpleTypeInnerUnboundedInOutputWS_Status(ws) == AXISC_FAIL ||
        result == NULL)
       printf("FAILED\n");    
    else 
    {  
        xsdc__string_Array * output = result->ident;
        int size = output->m_Size;
        const xsdc__string* array = output->m_Array;
        if (array != NULL)
        {
            if (size > 0)
                for ( i = 0 ; i < size ; i++)
                    printf("Result [%d] : %s\n", i, array[i]);
            else
                printf("empty array\n");
        }
        else
            printf("NULL array\n");

      returnValue = 0; // Success
    }

  destroy_SimpleTypeInnerUnboundedInOutputWS_stub(ws);
  
  printf("---------------------- TEST COMPLETE -----------------------------\n");
  return returnValue;
}
