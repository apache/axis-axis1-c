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
#include "XSD_byte.h" 


#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/ComplexTypeAll/services/Service"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;   
     
    SimpleComplexType1* input = Axis_Create_SimpleComplexType1(0);
    SimpleComplexType1* result = NULL;
    AxiscAnyType pAny = { NULL, 0 };
    
    char *stringArray[1];

    char *endpoint = WSDL_DEFAULT_ENDPOINT;

    int returnValue = 1; // Assume Failure

    if (argc>2 && strcmp(argv[1], "-e") == 0)
        endpoint = argv[2];

    ws = get_XSD_byte_stub(endpoint);

    pAny._size = 1;
    pAny._array = stringArray;
    pAny._array[0]="<mybook>WSCC</mybook>";

    input->any1    = &pAny;
    input->field2 = "WebServices";
    input->field3 = 123;

    result = asComplexType(ws, input);

    if( result == NULL )
        printf( "result object is NULL" );
    else
    {
        AxiscAnyType* pAnyReturn = result->any1;
        xsdc__string f2 = result->field2;
        xsdc__int f3 = result->field3;   
        char * p = strstr( pAnyReturn->_array[0], "<mybook");
    
        if( p && strstr( p, ">WSCC</mybook>"))
            printf( "Result field1 is = <mybook>WSCC</mybook>\n" );
        else
            printf( "Result field1 is = %s\n" , pAnyReturn->_array[0] );
    
        printf( "Result field2 is = %s\n" , f2 );
        printf( "Result field3 is = %d\n" , f3 );
        
        Axis_Delete_SimpleComplexType1(result, 0);
    }
    
    destroy_XSD_byte_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");

    return returnValue;
}

