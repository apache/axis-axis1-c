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

#include <axis/client/Stub.h>


#include "CommonClientTestCode.h"
#include "LargeReturningString.h" 

#define WSDL_DEFAULT_ENDPOINT "http://bora.hursley.ibm.com:9080/LargeReturningString/services/LargeReturningString"


int main(int argc, char* argv[])
{ 
    AXISCHANDLE ws;

    char *                  endpoint = WSDL_DEFAULT_ENDPOINT;
    int                     returnValue = 1; /* Assume Failure */
    
    int         input = 2 * 1024 * 1024;
    xsdc__string result = "";
 
    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0) 
        endpoint = argv[2];       
        
    ws = get_LargeReturningString_stub(endpoint);        

    // Extend transport timeout to 60 seconds (default is 10).
    axiscStubSetTransportTimeout(ws, 60);

    result = getLargeString(ws, input);

    printf("Result\n");
    if (exceptionOccurred == C_TRUE ||
        get_LargeReturningString_Status(ws) == AXISC_FAIL ||
        result == NULL)
       printf("FAILED\n");
    else if( strlen( result) == input)
        printf("%d\n", strlen( result));
    else
    {
        int iError = 0, x;

        for( x = 0; x < input; x++)
        {
            if( result[x] != 'a' + (x + iError) % 26)
            {
                printf("Error. result[%d] should have been %c but was %c\n" ,x,(char) ('a' + x % 26), result[x]);
                iError++;
            }
        }

        printf("There where %d errors.\n", iError);
        printf("Requested %d bytes. Received %d bytes.\n", input, strlen(result));

        returnValue = 0; /* Success */
    }
   
    axiscAxisDelete(result, XSDC_STRING);
    destroy_LargeReturningString_stub(ws);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
  
    return returnValue;
}
