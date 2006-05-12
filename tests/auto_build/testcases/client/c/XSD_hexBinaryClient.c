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
#include "XSD_hexBinary.h"



int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__hexBinary input;
    xsdc__hexBinary result;
    xsdc__hexBinary* nillableResult;
    
    xsdc__unsignedByte* testUB;  
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/XSD_hexBinary";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_XSD_hexBinary_stub(endpoint);       

    testUB = (xsdc__unsignedByte*)stringToAscii("<test><xml>some dod&y string</xml></test>\n");
    input.__ptr = testUB;
    input.__size= 41;


    // Test non-nillable element
    result = asNonNillableElement(ws, input);
    printf( "non-nillable element\n" );
    printf( " size=%d\n" , result.__size );
    printf( " data=%s\n" , asciiToStringOfLength((char *)result.__ptr, result.__size) );

    // Test nillable element, with a value
    nillableResult = asNillableElement(ws, &input);
    if (nillableResult)
    {
        printf( "nillable element\n" );
        printf( " size=%d\n" , nillableResult->__size );
        printf( " data=%s\n" , asciiToStringOfLength((char *)nillableResult->__ptr, nillableResult->__size) );

        axiscAxisDelete(nillableResult, XSDC_HEXBINARY);
    }
    else
        printf( "nillable element=<nil>\n" );

    // Test nillable element, with nil
    nillableResult = asNillableElement(ws, NULL);
    if (nillableResult)
    {
        printf( "nillable element\n" );
        printf( " size=%d\n" , nillableResult->__size );
        printf( " data=%s\n" , asciiToStringOfLength((char *)nillableResult->__ptr, nillableResult->__size) );

        axiscAxisDelete(nillableResult, XSDC_HEXBINARY);
    }
    else
        printf( "nil element=<nil>\n" );

    // Test array
    {
#define ARRAY_SIZE 2                    
        int i, outputSize=0;
        
        xsdc__hexBinary_Array arrayInput;
        xsdc__hexBinary_Array* arrayResult;
        xsdc__hexBinary * array[ARRAY_SIZE];
        xsdc__hexBinary ** output;
        
        for (i=0 ; i < ARRAY_SIZE ; i++)
            array[i] = &input;            
               
        arrayInput.m_Array = array;
        arrayInput.m_Size  = ARRAY_SIZE;
        arrayInput.m_Type  = XSDC_HEXBINARY;
        
        arrayResult = asArray(ws, &arrayInput);

        if (arrayResult)
        {
           output     = arrayResult->m_Array;
           outputSize = arrayResult->m_Size;
        }
    
        printf("array of %d elements\n" , outputSize );   

        for (i = 0; i < outputSize; i++)
        {
            printf( " element[%d]\n" , i);
            printf( "  size=%d\n" , output[i]->__size );
            printf( "  data=%s\n" , asciiToStringOfLength((char *) output[i]->__ptr, output[i]->__size) );           
        }

        axiscAxisDelete(arrayResult, XSDC_ARRAY);
    }


    // Test complex type
    {
        SimpleComplexType complexTypeInput;
        SimpleComplexType* complexTypeResult;
        
        complexTypeInput.complexTypeElement = input;
        complexTypeResult = asComplexType(ws, &complexTypeInput);
        printf( "within complex type\n" );
        printf( " size=%d\n" , complexTypeResult->complexTypeElement.__size );
        printf( " data=%s\n" , 
                asciiToStringOfLength((char *)complexTypeResult->complexTypeElement.__ptr, 
                                      complexTypeResult->complexTypeElement.__size) );

        Axis_Delete_SimpleComplexType(complexTypeResult, 0);
    }

    // Tests now complete
    destroy_XSD_hexBinary_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");
   
    return 0;
}
