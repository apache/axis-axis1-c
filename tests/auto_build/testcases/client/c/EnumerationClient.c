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
#include "EnumerationWS.h" 

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/Enumeration/services/sampleWS"

#define NEWCOPY(ptr,str) {ptr=axiscAxisNew(XSDC_STRING, strlen(str)+1); strcpy(ptr,str);}

int main(int argc, char* argv[])
{ 

    AXISCHANDLE ws;

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    int returnValue = 1; /* Assume Failure */

    Type1* input = NULL;
    Type1* result = NULL;

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0) 
        endpoint = argv[2];   

    ws = get_EnumerationWS_stub(endpoint);

    input = (Type1*)Axis_Create_Type1();

    NEWCOPY(input->enum_string,"one");
    NEWCOPY(input->att_enum_string,"one");
    input->enum_int=axiscAxisNew(XSDC_INT, 0);
    *input->enum_int=ENUMTYPEINT_0;
    input->att_enum_int=ENUMTYPEINT_1;
    NEWCOPY(input->att_enum_kind,"CHEQUE");

    result = getInput(ws, input);

    printf("Result\n");
    if (exceptionOccurred == C_TRUE ||
        get_EnumerationWS_Status(ws) == AXISC_FAIL ||
        result == NULL)
       printf("FAILED\n");
    else 
    {
      printf("att_enum_int %d\n", result->att_enum_int);
      printf("att_enum_string %s\n", result->att_enum_string);
      printf("enum_int %d\n", *result->enum_int);
      printf("enum_string %s\n", result->enum_string);
      printf("enum_kind %s\n", result->att_enum_kind);
      returnValue = 0; /* Success */
    }
    
    Axis_Delete_Type1(input,0,0);
    Axis_Delete_Type1(result,0,0);
    
    destroy_EnumerationWS_stub(ws);
    
  printf( "---------------------- TEST COMPLETE -----------------------------\n");

  return returnValue;    
}
