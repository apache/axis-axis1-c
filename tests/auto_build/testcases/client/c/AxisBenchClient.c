#include "AxisBench.h"
#include <time.h>
int main(int argc, char* argv[])
{ 

  BenchDataType *input;
  BenchDataType *output;
  BenchBasicDataType *pTemp;
  time_t tim;
  int i;
  void * pStub;
  
  xsd__unsignedByte* buffer;

  
  pStub = get_AxisBench_stub ("http://localhost:9080/AxisBench/services/AxisBenchSoapImpl");

  input = Axis_Create_BenchDataType(0,0,0);

	input->count = 100;
	input->infos.m_Array = Axis_Create_BenchBasicDataType(NULL,1,input->count);
	input->infos.m_Size = input->count;

  tim = 1079010407;

  gmtime(&tim);

  pTemp = input->infos.m_Array;

  buffer = (xsd__unsignedByte*)malloc ( input->count + 2 );
  memset (buffer,0,input->count + 2);


  for ( i = 0; i < input->count ; i++ ) {
    BenchBasicDataType *type = Axis_Create_BenchBasicDataType(0,0,0);
    type->StringType = strdup("StringType");
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
	  type->QNameType = strdup("toto");
  	type->ShortType = 1;

    type->Base64BinaryType.__size=i;
    type->Base64BinaryType.__ptr=buffer;
    type->HexBinary.__size=i;
    type->HexBinary.__ptr=buffer;
    strcat ( (char *)buffer, "A");
 
    pTemp[i] = *type;

  }

  output = doBenchRequest(pStub,input);

  if ( get_AxisBench_Status(pStub) == AXIS_FAIL ) 
    printf ("Failed\n");
  else {  
  BenchBasicDataType *pTemp;
  pTemp = output->infos.m_Array;
  printf ("Count : %d \n", output->count);
  for ( i = 0; i < output->count ; i++ ) {
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
