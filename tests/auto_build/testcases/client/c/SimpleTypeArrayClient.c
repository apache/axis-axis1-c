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

#include <stdio.h>

#include "CommonClientTestCode.h"
#include "SimpleTypeArrayWS.h" 

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/SimpleTypeArray/services/sampleWS"

int main(int argc, char* argv[])
{ 
    AXISCHANDLE ws = NULL;
    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    int returnValue = 1; /* Assume Failure */
    Type *input;
    Type *output;
    xsdc__int_Array array_input;
    xsdc__int_Array *array_output;
    xsdc__int * array[100];
    xsdc__int   elements[100];
    int i;

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0) 
        endpoint = argv[2];   

    for ( i = 0; i < 100; i++ )
    {     
      elements[i] = i;
      array[i]    = &elements[i];
    }
    
    array_input.m_Array = array;
    array_input.m_Size  = 100;
    array_input.m_Type  = XSDC_INT;

    input = Axis_Create_Type();
    input->item = &array_input;

    ws = get_SimpleTypeArrayWS_stub(endpoint);
    output = getInput(ws, input);
    
    if (exceptionOccurred == C_TRUE ||
        get_SimpleTypeArrayWS_Status(ws) == AXISC_FAIL ||
        output == NULL || output->item == NULL)
       printf("FAILED\n");
    else
    {
       returnValue = 0;
       for ( i = 0; i < 100; i++ )
         printf ("item [%d] = %d\n",i,*output->item->m_Array[i]);
    }
    
    input->item = NULL;
    
    Axis_Delete_Type(input,0,0);
    Axis_Delete_Type(output,0,0);
    
    destroy_SimpleTypeArrayWS_stub(ws);
   
    printf("---------------------- TEST COMPLETE -----------------------------\n");   
    return returnValue; 
}

