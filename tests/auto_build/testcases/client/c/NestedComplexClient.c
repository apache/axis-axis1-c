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


/*
 * NestedComplex
 * 
 * Send a complex data type, ComplexType2, which has a data element of an
 * array of a complex data type, ComplexType1. The ComplexType1 data type
 * has a xsd:string element, a xsd:int element and a complex data type element
 * SimpleArrays. The SimpleArrays complex data type has a xsd:string array and
 * a xsd_int array.
 *
 * ComplexType2
 *   + ComplexType1[]
 *       + string
 *       + int
 *       + SimpleArrays
 *           + string[]
 *           + int[]
 *
 * This is an echo type service so the response should be the same as the request.
 *
 * Author: Andrew Perry
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "NestedComplex.h"

#define ARRAYSIZE 2
#define NEWCOPY(ptr,str) {ptr=axiscAxisNew(XSDC_STRING, strlen(str)+1); strcpy(ptr,str);}

int main(int argc, char* argv[])
{
    AXISCHANDLE ws; 

    ComplexType2 complexType2;
    ComplexType2* response;
    SimpleArrays *simpleArrays1 = Axis_Create_SimpleArrays(0);
    SimpleArrays *simpleArrays2 = Axis_Create_SimpleArrays(0);
    SimpleArrays *simpleArrays[2];
    ComplexType1 complexType1_1;
    ComplexType1 complexType1_2;
    
    ComplexType1_Array cType1Array;
    ComplexType1 * array[ARRAYSIZE];

    xsdc__int intValues[2] = {6, 7};
    xsdc__string strType[ARRAYSIZE] = { "Apache", "Axis C++" };
    xsdc__int * intType[ARRAYSIZE];
        
    char endpoint[256];
    const char* url="http://localhost:80/axis/NestedComplex";
    
    int i;

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_NestedComplex_stub(endpoint);

    simpleArrays[0] = simpleArrays1;
    simpleArrays[1] = simpleArrays2;
    intType[0] = &intValues[0];
    intType[1] = &intValues[1];

    for (i=0; i<2; i++)
    {
        simpleArrays[i]->stringArray->m_Array=strType;
        simpleArrays[i]->stringArray->m_Size=ARRAYSIZE;   
             
        simpleArrays[i]->intArray->m_Array=intType;
        simpleArrays[i]->intArray->m_Size=ARRAYSIZE;        
    }

    complexType1_1.simpleArrays = simpleArrays1;
    complexType1_1.ct1_string = "Hello";
    complexType1_1.ct1_int = 13;
    complexType1_2.simpleArrays = simpleArrays2;
    complexType1_2.ct1_string = "World";
    complexType1_2.ct1_int = 27;

    array[0] = &complexType1_1;
    array[1] = &complexType1_2;
    
    cType1Array.m_Array = array;
    cType1Array.m_Size = ARRAYSIZE;
    cType1Array.m_Type = C_USER_TYPE;
    
    complexType2.complexType1Array = (&cType1Array);
    
    response = echoNestedComplex(ws, &complexType2);
    
    if (response)
    {
        if (response->complexType1Array && response->complexType1Array->m_Size > 1)
        {
            ComplexType1 ** output = response->complexType1Array->m_Array;
            
            printf("%s\n", output[0]->ct1_string );
            printf("%d\n", output[0]->ct1_int );
            printf("%s %s\n", output[0]->simpleArrays->stringArray->m_Array[0], 
                              output[0]->simpleArrays->stringArray->m_Array[1] );
            printf("%d %d\n", *(output[0]->simpleArrays->intArray->m_Array[0]), 
                              *(output[0]->simpleArrays->intArray->m_Array[1]) );
            printf("%s\n", output[1]->ct1_string );
            printf("%d\n", output[1]->ct1_int );
            printf("%s %s\n", output[1]->simpleArrays->stringArray->m_Array[0], 
                              output[1]->simpleArrays->stringArray->m_Array[1] );
            printf("%d %d\n", *(output[1]->simpleArrays->intArray->m_Array[0]),  
                              *(output[1]->simpleArrays->intArray->m_Array[1]) );
        }
        else
            printf("Failed, response->complexType1Array is NULL or size is not greater than 1\n");
    }
    else
        printf("Failed, response is NULL\n");

    for (i=0; i<2; i++)
    {
        simpleArrays[i]->stringArray->m_Array=NULL;
        simpleArrays[i]->intArray->m_Array=NULL;
        
        Axis_Delete_SimpleArrays(simpleArrays[i], 0);
    }

    destroy_NestedComplex_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

