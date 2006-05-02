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
#include "AxisBench.h"

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/AxisBench/services/AxisBenchSoapImpl"

int main(int argc, char* argv[])
{
    AXISCHANDLE ws = NULL;

    BenchDataType *     input = NULL;
    BenchDataType *     output = NULL;
    xsdc__unsignedByte* buffer = NULL;

    char *      endpoint = WSDL_DEFAULT_ENDPOINT;
    int    returnValue = 1; /* Assume Failure */

    int i;

    BenchBasicDataType_Array arrayIn;
    BenchBasicDataType ** ppBBDT;

    xsdc__long ll;
    time_t tim;
    struct tm *  temp;
    struct tm lt;

    char * letterA_String;

    int request = 1;


    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if (argc>2 && strcmp(argv[1], "-e") == 0)
        endpoint = argv[2];

    ws = get_AxisBench_stub (endpoint);

    /* extend transport timeout value to 60 secs */
    axiscStubSetTransportTimeout(ws, 60);

    ppBBDT = (BenchBasicDataType **)malloc(sizeof(BenchBasicDataType *) * 100);

    input = Axis_Create_BenchDataType(0);
    input->count = 100;

    ll = 10000;
    tim = 1100246323;
    temp = gmtime( &tim);

    memcpy( &lt, temp, sizeof( struct tm));

    letterA_String = stringToAscii( "A");
    buffer = (xsdc__unsignedByte *) calloc( 1, input->count + 2);
    strcpy( (char *) buffer, letterA_String);

    for( i = 0; i < input->count ; i++)
    {
        BenchBasicDataType *type = Axis_Create_BenchBasicDataType(0);

        type->StringType = "StringType";
        type->IntegerType = 10 * (i + 1);
        type->DoubleType = 11.111 * (i + 1);
        type->BooleanType = true_;
        type->DateTimeType = lt;
        type->TimeType = lt;
        type->DateType = lt;
        type->IntType = (i + 1);
        type->ByteType = '1';
        type->DecimalType = 10 * (i + 1);
        type->FloatType = (float) ((float) (11 * (i + 1)) / (float) 2.0);
        type->LongType = ll;
        type->QNameType = "toto";
        type->ShortType = (i + 1);
        type->Base64BinaryType.__size=i;
        type->Base64BinaryType.__ptr=buffer;
        type->HexBinary.__size=i;
        type->HexBinary.__ptr=buffer;

        ppBBDT[i] = type;

        if( ll == 0)
            ll = 1;
        else
            ll += 10000;

        strcat ( (char *) buffer, letterA_String);
    }

    arrayIn.m_Array = ppBBDT;
    arrayIn.m_Size  = input->count;
    arrayIn.m_Type  = C_USER_TYPE;

    input->infos =  &arrayIn;

    for(i = 0; i < request; i++)
    {
        if (output)
        {
            Axis_Delete_BenchDataType(output,0);
            output = NULL;
        }

        output = doBenchRequest(ws, input);

        if (exceptionOccurred == C_TRUE
            || output == NULL
            || get_AxisBench_Status(ws) == AXISC_FAIL )
            break;
    }

    for( i = 0; i < input->count; i++)
    {
        /* since these are pointers to our own buffers, null them out before deleting  */
        ppBBDT[i]->StringType = NULL;
        ppBBDT[i]->QNameType  = NULL;
        ppBBDT[i]->Base64BinaryType.__ptr=NULL;
        ppBBDT[i]->HexBinary.__ptr=NULL;

        Axis_Delete_BenchBasicDataType(ppBBDT[i],0);
    }

    if (ppBBDT)
        free(ppBBDT);
    if (buffer)
        free( buffer);
    input->infos = NULL;

    if (exceptionOccurred == C_TRUE
        || output == NULL
        || get_AxisBench_Status(ws) == AXISC_FAIL )
        printf ("Failed\n");
    else
    {
        char    dateTime[50];
        BenchBasicDataType **   outArray = output->infos->m_Array;

        if( argc > 1)
            i = output->count - 1;

        printf("Input Count : %d\n", input->count);
        printf("Count : %d\n", output->count);

        for ( i = 0; i < output->count ; i++ )
        {
            if( outArray[i] != NULL)
            {
                printf( " ----------------------------------------------\n" );
                printf( " StringType %s\n", outArray[i]->StringType );
                printf( " IntType %d\n", outArray[i]->IntType );
                printf( " IntegerType %lld\n", outArray[i]->IntegerType );
                printf( " DoubleType %g\n", outArray[i]->DoubleType );
                printf( " BooleanType %d\n", outArray[i]->BooleanType );
                strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &outArray[i]->DateTimeType);
                printf( " DateTimeType %s\n", dateTime );
                strftime(dateTime, 50, "%a %b %d %Y", &outArray[i]->DateType);
                printf( " DateType %s\n", dateTime );

                // Following check for os/400 - the mock server will return ascii char which needs to be converted
#ifdef __OS400__
                if( outArray[i]->ByteType == 0x31)
                    outArray[i]->ByteType = '1';
#endif
                printf( " ByteType %c\n", outArray[i]->ByteType );
                printf( " DecimalType %g\n", outArray[i]->DecimalType );
                printf( " FloatType %g\n", outArray[i]->FloatType );
                printf( " LongType %lld\n", outArray[i]->LongType );
                printf( " QNameType %s\n", outArray[i]->QNameType );
                printf( " ShortType %hd\n", outArray[i]->ShortType );

                printf( " Base64BinaryType %d\n", outArray[i]->Base64BinaryType.__size );
                if( outArray[i]->Base64BinaryType.__size > 0)
                    printf( " Base64BinaryType %s\n", asciiToString((char *)outArray[i]->Base64BinaryType.__ptr) );

                printf( " HexBinaryType %d\n", outArray[i]->HexBinary.__size );
                if( outArray[i]->HexBinary.__size > 0)
                    printf( " HexBinaryType %s\n", asciiToString( (char *) outArray[i]->HexBinary.__ptr) );
            }

            returnValue = 0;
        }
    }

    Axis_Delete_BenchDataType (input,0);
    Axis_Delete_BenchDataType (output,0);

    printf( "---------------------- TEST COMPLETE -----------------------------\n" );

    return returnValue;
}
