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
#include "MultiOut.h"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;

    xsdc__string OutValue0 = NULL;
    xsdc__integer * pOutValue1 = NULL;
    xsdc__int outValue2;
    xsdc__long outValue3;
    xsdc__short outValue4;
    xsdc__decimal outValue5;
    xsdc__float outValue6;
    xsdc__double outValue7;
    xsdc__boolean outValue8;
    xsdc__byte outValue9;

    axiscAxisRegisterExceptionHandler(exceptionHandler);
    
    ws = get_MultiOut_stub(argv[1]);

    get(ws,&OutValue0,
           &pOutValue1,
           &outValue2,
           &outValue3,
           &outValue4,
           &outValue5,
           &outValue6,
           &outValue7,
           &outValue8,
           &outValue9);

    printf("%s\n",   OutValue0 );
    printf("%lld\n",   *pOutValue1 );
    printf("%d\n",   outValue2 );
    printf("%lld\n",   outValue3 );
    printf("%hd\n",   outValue4 );
    printf("%.0f\n",   outValue5 );
    printf("%.6g\n",   outValue6 );
    printf("%g\n",   outValue7 );
    printf("%s\n",   (outValue8==false_)?"false":"true");
#ifdef __OS400__
    if (outValue9 == 0x41) // Ascii 'A'
        outValue9 = 'A';    // Set to ebcdic A
#endif
    printf("%c\n",  outValue9 );

    axiscAxisDelete(OutValue0, XSDC_STRING);
    axiscAxisDelete(pOutValue1, XSDC_INTEGER);
    
    destroy_MultiOut_stub(ws);
    
    printf("---------------------- TEST COMPLETE -----------------------------\n");
    return 0;
}
