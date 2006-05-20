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
 * test setting elements in a nillable array to nil.
 * This is for primitive types only
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "NillableArrays.h"

#define ARRAYSIZE 3

int main(int argc, char* argv[])
{
    AXISCHANDLE ws; 
        
    const char* url="http://localhost:80/axis/NillableArrays";
    char endpoint[256];
    
    int outputSize = 0;    

    xsdc__boolean_Array boolean_in;
    xsdc__boolean_Array* boolean_out;
    xsdc__short_Array short_in;
    xsdc__short_Array* short_out;
    xsdc__int_Array int_in;
    xsdc__int_Array* int_out;
    xsdc__long_Array long_in;
    xsdc__long_Array* long_out;
    xsdc__float_Array float_in;
    xsdc__float_Array* float_out;
    xsdc__double_Array double_in;
    xsdc__double_Array* double_out;
    xsdc__string_Array string_in;
    xsdc__string_Array* string_out;


    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_NillableArrays_stub(endpoint);


    /* Test a boolean array */
    {
        xsdc__boolean b1 = (xsdc__boolean)0;
        xsdc__boolean b3 = (xsdc__boolean)1;
        xsdc__boolean *booleanInArray[ARRAYSIZE];
        xsdc__boolean ** booleanArray;
        
        booleanInArray[0] = &b1;
        booleanInArray[1] = NULL;
        booleanInArray[2] = &b3;

        boolean_in.m_Array = booleanInArray;
        boolean_in.m_Size = ARRAYSIZE;
        boolean_in.m_Type = XSDC_BOOLEAN;
        
        
        printf( "invoking echoBooleanArray...\n");
        
        boolean_out = echoBooleanArray(ws, &boolean_in);
    
        outputSize = 0;
        if (boolean_out)
        {
           booleanArray = boolean_out->m_Array;
           outputSize = boolean_out->m_Size;
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(booleanArray[1])
                printf( "failed \n");
            else if( (*booleanArray[0] == b1) && (*booleanArray[2] == b3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
            
        axiscAxisDelete(boolean_out, XSDC_ARRAY);
    }

    /* Test an short array */
    {
        xsdc__short s1 = (xsdc__short)252;
        xsdc__short s3 = (xsdc__short)254;
        xsdc__short * shortInArray[ARRAYSIZE];
        xsdc__short ** shortArray ;
        
        shortInArray[0] = &s1;
        shortInArray[1] = NULL;
        shortInArray[2] = &s3;

        short_in.m_Array = shortInArray;
        short_in.m_Size = ARRAYSIZE;
        short_in.m_Type = XSDC_SHORT;
                
        printf( "invoking echoShortArray...\n");
        short_out = echoShortArray(ws, &short_in);
    
        outputSize = 0;
        if (short_out)
        {
           shortArray = short_out->m_Array;
           outputSize = short_out->m_Size;
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(shortArray[1])
                printf( "failed \n");
            else if( (*shortArray[0] == s1) && (*shortArray[2] == s3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");
        
        axiscAxisDelete(short_out, XSDC_ARRAY);
    }

    /* Test an int array */
    {
        xsdc__int val1 = 1000000;
        xsdc__int val3 = 1000002;
        xsdc__int *intInArray[ARRAYSIZE];
        xsdc__int ** intArray;
        
        intInArray[0] = &val1;
        intInArray[1] = NULL;
        intInArray[2] = &val3;
        
        int_in.m_Array = intInArray;
        int_in.m_Size = ARRAYSIZE;
        int_in.m_Type = XSDC_INT;
                
        printf( "invoking echoIntArray...\n");
        int_out = echoIntArray(ws, &int_in);
    
        outputSize = 0;
        if (int_out)
        {
            intArray = int_out->m_Array;
            outputSize = int_out->m_Size;            
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(intArray[1])
                printf( "failed \n");
            else if( (*intArray[0] == val1) && (*intArray[2] == val3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");

        axiscAxisDelete(int_out, XSDC_ARRAY);
    }


    /* Test a long array */
    {
        xsdc__long l1 = (xsdc__long)200001;
        xsdc__long l3 = (xsdc__long)200003;
        xsdc__long *longInArray[ARRAYSIZE];
        xsdc__long ** longArray;
        
        longInArray[0] = &l1;
        longInArray[1] = NULL;
        longInArray[2] = &l3;

        long_in.m_Array = longInArray;
        long_in.m_Size = ARRAYSIZE;
        long_in.m_Type = XSDC_LONG;
                
        printf( "invoking echoLongArray...\n");
        long_out = echoLongArray(ws, &long_in);
    
        outputSize = 0;
        if (long_out)
        {        
            longArray = long_out->m_Array;
            outputSize = long_out->m_Size;
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(longArray[1])
                printf( "failed \n");
            else if( (*longArray[0] == l1) && (*longArray[2] == l3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");

        axiscAxisDelete(long_out, XSDC_ARRAY);
    }

    /* Test a float array */
    {
        xsdc__float f1 = (xsdc__float)11.111;
        xsdc__float f3 = (xsdc__float)33.111;
        xsdc__float *floatInArray[ARRAYSIZE];
        xsdc__float ** floatArray;
        
        floatInArray[0] = &f1;
        floatInArray[1] = NULL;
        floatInArray[2] = &f3;

        float_in.m_Array = floatInArray;
        float_in.m_Size = ARRAYSIZE;
        float_in.m_Type = XSDC_FLOAT;
                
        printf( "invoking echoFloatArray...\n");
        float_out = echoFloatArray(ws, &float_in);
    
        outputSize = 0;
        if (float_out)
        {
            floatArray = float_out->m_Array;
            outputSize = float_out->m_Size;
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(floatArray[1])
                printf( "failed \n");
            else if( (*floatArray[0] == f1) && (*floatArray[2] == f3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");

        axiscAxisDelete(float_out, XSDC_ARRAY);
    }

    /* Test a double array */
    {
        xsdc__double d1 = (xsdc__double)71.1565;
        xsdc__double d3 = (xsdc__double)73.1565;
    
        xsdc__double *doubleInArray[ARRAYSIZE];
        xsdc__double ** doubleArray;
        
        doubleInArray[0] = &d1;
        doubleInArray[1] = NULL;
        doubleInArray[2] = &d3;

        double_in.m_Array = doubleInArray;
        double_in.m_Size = ARRAYSIZE;
        double_in.m_Type = XSDC_DOUBLE;
                
        printf( "invoking echoDoubleArray...\n");
        double_out = echoDoubleArray(ws, &double_in);
    
        outputSize = 0;
        if (double_out)
        {
            doubleArray = double_out->m_Array;
            outputSize = double_out->m_Size;
        }
        if(outputSize ==ARRAYSIZE)
        {
            if(doubleArray[1])
                printf( "failed \n");
            else if( (*doubleArray[0] == d1) && (*doubleArray[2] == d3) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");

        axiscAxisDelete(double_out, XSDC_ARRAY);
    }

    /* Test a string array */
    {
        static char* str1 = "Apache";
        static char* str2 = "Axis C++";
        xsdc__string stringInArray[ARRAYSIZE];
        xsdc__string *output;
        
        stringInArray[0] = str1;
        stringInArray[1] = NULL;
        stringInArray[2] = str2;


        string_in.m_Array = stringInArray;
        string_in.m_Size = ARRAYSIZE;
        string_in.m_Type = XSDC_STRING;        
        printf( "invoking echoStringArray...\n");
        string_out = echoStringArray(ws, &string_in);
        outputSize =0;
        if (string_out)
        {
            output = string_out->m_Array;
            outputSize = string_out->m_Size;
        }
        
        if(outputSize ==ARRAYSIZE)
        {
            if(output[1])
                printf( "failed \n");
            else if( (strcmp(output[0], str1) == 0) && (strcmp(output[2], str2) == 0) )
                printf( "successful \n");
            else
                printf( "failed \n");
        }
        else
            printf( "failed \n");

        axiscAxisDelete(string_out, XSDC_ARRAY);
    }

    destroy_NillableArrays_stub(ws);
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");
    
    return 0;
}

