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
#include "ManyTypeRefRoot.h" 

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/ManyTypeRefRoot/services/sampleWS"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;    

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    int returnValue = 1; // Assume Failure

    Type1_Array input;
    Type1_Array* result;
    Type1 *types[10];

    int i, outputSize=0;
    Type1 **arrayResult;
 
    axiscAxisRegisterExceptionHandler(exceptionHandler);
 
    if (argc>2 && strcmp(argv[1], "-e") == 0)
        endpoint = argv[2]; 
 
    ws = get_ManyTypeRefRoot_stub(endpoint);
        
    for ( i = 0; i < 10; i++ )
    {
        types[i] = Axis_Create_Type1(0);
        
        types[i]->kind  = axiscAxisNew(XSDC_STRING, 10);
        strcpy(types[i]->kind, "Test type");
        
        types[i]->index = axiscAxisNew(XSDC_INT, 0);
        *(types[i]->index) = i;
    }

    input.m_Array = types;
    input.m_Size  = 10;
    input.m_Type  = C_USER_TYPE;

    result = getInput(ws, &input);
    
    printf("Success \n");

    if (result)
    {        
        arrayResult = result->m_Array;
        outputSize  = result->m_Size;
    }
    
    for ( i = 0; i < outputSize; i++) 
        printf(" Result %d : %s\n", *arrayResult[i]->index, arrayResult[i]->kind);

    returnValue = 0; // Success

    // Clear up
    for (i = 0 ; i < 10 ; i++ )
        Axis_Delete_Type1(types[i],0);
    Axis_Delete_Type1_Array(result, 0);

    destroy_ManyTypeRefRoot_stub(ws);
        
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    
    return returnValue;
}
