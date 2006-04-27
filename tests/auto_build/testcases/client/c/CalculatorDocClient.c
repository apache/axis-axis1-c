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

#include "CommonClientTestCode.h"

#include "Calculator.h"

#include <stdio.h>

int main(int argc, char ** argv)
{
    AXISCHANDLE stub;
    int ret = 0;
    char *uri = "http://localhost:80/axis/Calculator";

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>1)
        uri = argv[1];

    stub = get_Calculator_stub(uri);
    ret = add(stub,3,2);
    if (exceptionOccurred == C_TRUE ||
        get_Calculator_Status(stub) == AXISC_FAIL)
        printf("FAILED\n");
    else
        printf("%i\n",ret);

    destroy_Calculator_stub(stub);

    printf("---------------------- TEST COMPLETE -----------------------------\n");
}

