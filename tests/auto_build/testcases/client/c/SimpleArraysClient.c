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

#include "CommonClientTestCode.h"
#include "SimpleArrays.h"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    const char* url="http://localhost:80/axis/SimpleArrays";
    char endpoint[256];

    int i = 0;

    if(argc>1)
        url = argv[1];
        
    sprintf(endpoint, "%s", url);
    ws = get_SimpleArrays_stub(endpoint);
        
    /* Test a boolean array */
    {
        xsdc__boolean *inArray[ARRAYSIZE];
        xsdc__boolean arrayElements[ARRAYSIZE];
        xsdc__boolean_Array input;
        xsdc__boolean_Array* output;

        for (i=0; i<ARRAYSIZE; i++)
        {
            inArray[i]     = &arrayElements[i];
            arrayElements[i] = (xsdc__boolean)i;
        }
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_BOOLEAN;
        
        printf( "invoking echoBooleanArray...\n");
        output = echoBooleanArray(ws, &input);

        if(output->m_Size > 0)
        {
            if(*( output->m_Array[0]) == (xsdc__boolean)0)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }

    /* Test an int array */
    {
        xsdc__int *inArray[ARRAYSIZE];
        xsdc__int  arrayElements[ARRAYSIZE];        
        xsdc__int_Array input;
        xsdc__int_Array* output;
        
        for (i=0; i<ARRAYSIZE; i++)
        {
            inArray[i]     = &arrayElements[i];
            arrayElements[i] = (xsdc__int)(i+1);
        }
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_INT;
        
        printf( "invoking echoIntArray...\n");
        output = echoIntArray(ws, &input);

        if(output->m_Size > 0)
        {
            if(*(output->m_Array[0]) == 1)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }


    /* Test a long array */
    {
        xsdc__long *inArray[ARRAYSIZE];  
        xsdc__long  arrayElements[ARRAYSIZE];      
        xsdc__long_Array input;
        xsdc__long_Array* output;

        
        for (i=0; i<ARRAYSIZE; i++)
        {
            inArray[i]     = &arrayElements[i];
            arrayElements[i] = (xsdc__long)(i+ 200001);
        }
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_LONG;
        
        printf( "invoking echoLongArray...\n");
        output = echoLongArray(ws, &input);

        if(output->m_Size > 0)
        {
            if(*(output->m_Array[0]) == (xsdc__long)200001)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }

    /* Test a float array */
    {
        xsdc__float *inArray[ARRAYSIZE];
        xsdc__float  arrayElements[ARRAYSIZE];
        xsdc__float_Array input;
        xsdc__float_Array* output;

            
        for (i=0; i<ARRAYSIZE; i++)
        {
            inArray[i]     = &arrayElements[i];
            arrayElements[i] = (xsdc__float)(i+ 11.111);
        }
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_FLOAT;
        
        printf( "invoking echoFloatArray...\n");
        output = echoFloatArray(ws, &input);

        if(output->m_Size > 0)
        {
            if(*(output->m_Array[0]) == (xsdc__float)11.111)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }

    /* Test a double array */
    {
        xsdc__double * inArray[ARRAYSIZE];
        xsdc__double   arrayElements[ARRAYSIZE];        
        xsdc__double_Array input;
        xsdc__double_Array* output;     
    
        for (i=0; i<ARRAYSIZE; i++)
        {
            inArray[i]     = &arrayElements[i];
            arrayElements[i] = (xsdc__double)(i+ 71.15656);
        }
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_DOUBLE;
        
        printf( "invoking echoDoubleArray...\n");
        output = echoDoubleArray(ws, &input);
    
        if(output->m_Size > 0)
        {
            if(*(output->m_Array[0]) == (xsdc__double)71.15656)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }

    /* Test a string array */
    {
        xsdc__string inArray[ARRAYSIZE] = { "Apache", "Axis C++" };
        xsdc__string_Array input;
        xsdc__string_Array* output;   
                
        input.m_Array = inArray;
        input.m_Size  = ARRAYSIZE;
        input.m_Type  = XSDC_STRING;

        printf( "invoking echoStringArray...\n");
        output = echoStringArray(ws, &input);

        if(output->m_Size > 0)
        {
            if(strcmp(output->m_Array[0], "Apache") == 0)
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(output, XSDC_ARRAY);    
    }
        
    destroy_SimpleArrays_stub(ws);    

    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}

