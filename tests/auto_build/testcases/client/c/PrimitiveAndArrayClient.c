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
#include "PrimitiveAndArray.h"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;

    xsdc__int single;
    xsdc__int_Array intArray;
    xsdc__int * arrayOfInt[ARRAYSIZE];
    xsdc__int int1;
    xsdc__int int2;
    xsdc__int **output;
    
    ComplexReturn* response;

    char endpoint[256];
    const char* url="http://localhost:80/axis/Calculator";

    if(argc>1)
        url = argv[1];
        
    axiscAxisRegisterExceptionHandler(exceptionHandler);
    
    sprintf(endpoint, "%s", url);
    
    ws = get_PrimitiveAndArray_stub(endpoint);

    arrayOfInt[0] = &int1;
    arrayOfInt[1] = &int2;

    single=37;

    int1 = 6;
    int2 = 7;

    intArray.m_Array = arrayOfInt;
    intArray.m_Size = ARRAYSIZE;
    intArray.m_Type = XSDC_INT;

    response = sendPrimitiveAndArray(ws, single, &intArray);

    if (response)
    {
        output = response->returnArray->m_Array;
        printf("%d %d %d\n",  response->returnInt, *(output[0]), *(output[1]) );
    }
    
    single=43;
    *arrayOfInt[0] = 13;
    *arrayOfInt[1] = 17;
    
    response = sendArrayAndPrimitive(ws, &intArray, single);

    if (response)
    {
        output = response->returnArray->m_Array;
        printf("%d %d %d\n",  response->returnInt, *(output[0]), *(output[1]) );
    }
    
    destroy_PrimitiveAndArray_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

