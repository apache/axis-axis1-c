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
#include "operations.h" 


#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/ComplexTypeAll/services/Service"


int main(int argc, char* argv[])
{
    AXISCHANDLE ws;

    aRecord input;
    aRecord* result;

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    int returnValue = 1; // Assume Failure

    if(argc>2) endpoint = argv[2];
    
    ws = get_operations_stub(endpoint);

    input.field1 = "Hello World!";
    input.field2 = "I'm still here!";
    input.field3 = "Now I go!";
    
    result = myOperation(ws, &input);

    printf( "Result field1 is = %s\n" , result->field1 );
    printf( "Result field2 is = %s\n" , result->field2 );
    printf( "Result field3 is = %s\n" , result->field3 );

    returnValue = 0; // Success
        
    destroy_operations_stub(ws);
        
    printf( "---------------------- TEST COMPLETE -----------------------------\n");

    return returnValue;
}
