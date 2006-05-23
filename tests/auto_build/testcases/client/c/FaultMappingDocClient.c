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
#include "MathOps.h"
#include "axis/ISoapFault.h"

void myExceptionHandler(int exceptionCode, const char *exceptionString, AXISCHANDLE pSoapFault, void *faultDetail)
{
    const char *pcCmplxFaultName;
    
    exceptionOccurred = C_TRUE;    
    
    if (pSoapFault)
    {
       pcCmplxFaultName = axiscSoapFaultGetCmplxFaultObjectName(pSoapFault);
       if(0 == strcmp("DivByZeroStruct", pcCmplxFaultName))
       {
         DivByZeroStruct *dbzs = (DivByZeroStruct *)faultDetail;
         printf("DivByZeroStruct Fault: \"%s\", %d, %f\n", dbzs->varString, dbzs->varInt, dbzs->varFloat);
       }
       else if (0 == strcmp("SpecialDetailStruct", pcCmplxFaultName))
       {
        SpecialDetailStruct *sds = (SpecialDetailStruct *)faultDetail;
        printf("SpecialDetailStruct Fault: \"%s\"\n", sds->varString);
       }
       else if (0 == strcmp("OutOfBoundStruct", pcCmplxFaultName))
       {
        OutOfBoundStruct *oobs = (OutOfBoundStruct *)faultDetail;
        printf("OutOfBoundStruct Fault: \"%s\", %d, \"%s\"\n", oobs->varString, oobs->varInt, oobs->specialDetail->varString);
       }
       else
       {
          printf("SoapFaultException: %s\n", faultDetail);
       }
       
    }
    
}

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    char endpoint[256];
    const char* server="localhost";
    const char* url="http://localhost:80/axis/MathOps";
    const char* port="80";
    const char* op = 0;
    const char* p1 = 0;
    const char* p2 = 0;
    int i1=0, i2=0;
    int iResult;
    char* pcDetail;
    int i;

    if (argc > 1)
        url = argv[1];
    sprintf(endpoint, "%s", url);

    op = "div";

    for(i = 0; i < 4; i++)
    {
        printf("%d\n",  i );

        switch(i)
        {
            case 0: i1 = 10; i2 = 5; break;
            case 1: i1 = 10; i2 = 0; break;
            case 2: i1 = 1000; i2 = 5; break;
            case 3: i1 = 10; i2 = -5; break;
        }

        ws = get_MathOps_stub(endpoint);
        
        set_MathOps_ExceptionHandler(ws, myExceptionHandler);        
        
        printf( "Trying to %s %d by %d\n", op, i1, i2 );
        iResult = div(ws, i1, i2);
        if (!exceptionOccurred)
            printf( "Result is %d\n", iResult );
        else
            exceptionOccurred = 0;
        
        destroy_MathOps_stub(ws);
    }
    
    printf( "---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

