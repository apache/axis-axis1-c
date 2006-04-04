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

#include <axis/Axis.h>
#include "CommonClientTestCode.h"
#include "AxisBench.h"

int main(int argc, char* argv[])
{ 
  BenchDataType *input;
  BenchDataType *output;
  BenchBasicDataType *pTemp;
  time_t tim;
  int i;
  void * pStub;
  xsdc__unsignedByte* buffer;
  char *uri = "http://localhost:9080/AxisBench/services/AxisBenchSoapImpl";

  axiscRegisterExceptionHandler(exceptionHandler);
  
  if (argc>1) 
    uri = argv[1];

  pStub = get_AxisBench_stub (uri);

  input = Axis_Create_BenchDataType(0,0,0);

  input->count = 100;
  input->infos.m_Array = Axis_Create_BenchBasicDataType(NULL,1,input->count);
  input->infos.m_Size = input->count;

  tim = 1079010407;
  gmtime(&tim);

  pTemp = input->infos.m_Array;

  buffer = (xsdc__unsignedByte*)malloc ( input->count + 2 );
  memset (buffer,0,input->count + 2);

  for ( i = 0; i < input->count ; i++ ) 
  {
    BenchBasicDataType *type = Axis_Create_BenchBasicDataType(0,0,0);
    type->StringType = c_strdup("StringType");
    type->IntegerType = i;
    type->DoubleType = 1;/*i/10;*/
    type->BooleanType = true_;
    type->DateTimeType = *gmtime(&tim);
    type->DateType = *gmtime(&tim);
    type->TimeType = *gmtime(&tim);

    type->IntType = i;
    type->ByteType = '1';
    type->DecimalType = 10;
    type->FloatType = i/2;
    type->LongType = i*100;
    type->QNameType = c_strdup("toto");
    type->ShortType = 1;

    type->Base64BinaryType.__size=i;
    type->Base64BinaryType.__ptr=buffer;
    type->HexBinary.__size=i;
    type->HexBinary.__ptr=buffer;
    strcat ( (char *)buffer, "A");
 
    pTemp[i] = *type;
  }

  output = doBenchRequest(pStub,input);

  if (exceptionOccurred == C_TRUE ||
      get_AxisBench_Status(pStub) == AXISC_FAIL ) 
    printf ("Failed\n");
  else 
  {  
      BenchBasicDataType *pTemp;
      pTemp = output->infos.m_Array;
      printf ("Count : %d \n", output->count);
      for ( i = 0; i < output->count ; i++ ) 
      {
        printf (" ----------------------------------------------\n");
        printf (" StringType %s \n", pTemp[i].StringType);
        printf (" IntegerType %d \n", pTemp[i].IntegerType);
        printf (" DoubleType %f \n", pTemp[i].DoubleType);
        printf (" BooleanType %d \n", pTemp[i].BooleanType);
        printf (" DateTimeType %s \n", asctime(&pTemp[i].DateTimeType));
        printf (" DateType %s \n", asctime(&pTemp[i].DateType));
        printf (" TimeType %s \n", asctime(&pTemp[i].TimeType));
        printf (" ByteType %d \n", pTemp[i].ByteType);
        printf (" DecimalType %f \n", pTemp[i].DecimalType);
        printf (" FloatType %f \n", pTemp[i].FloatType);
        printf (" LongType %ld \n", pTemp[i].LongType);
        printf (" QNameType %s \n", pTemp[i].QNameType);
        printf (" ShortType %d \n", pTemp[i].ShortType);
    
        printf (" Base64BinaryType %d \n", output->infos.m_Array[i].Base64BinaryType.__size);
        printf (" Base64BinaryType %s \n", output->infos.m_Array[i].Base64BinaryType.__ptr);
    
        printf (" HexBinaryType %d \n", output->infos.m_Array[i].HexBinary.__size);
        printf (" HexBinaryType %s \n", output->infos.m_Array[i].HexBinary.__ptr);
      }
  }
  
  Axis_Delete_BenchDataType (input,0,0);
  Axis_Delete_BenchDataType (output,0,0);
  
  return 0;
}
