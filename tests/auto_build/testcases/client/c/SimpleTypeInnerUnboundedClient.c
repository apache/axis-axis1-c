#include "SimpleTypeInnerUnboundedWS.h" 

int main(int argc, char* argv[])
{ 
  int i;
  void * pStub = get_SimpleTypeInnerUnboundedWS_stub ("http://localhost:9080/SimpleTypeInnerUnbounded/services/sampleWS");

  Type1 *input = Axis_Create_Type1(0,0,0);
  Type1_ident idents[10];
  
  Type1* result;

  input->enum_int = 1;
  input->enum_string = strdup("one");
  input->att_enum_kind = strdup("CHEQUE");
  input->att_enum_string = strdup("one");
  input->att_enum_int = 1;


  input->ident.m_Array = idents;
  input->ident.m_Size = 10;
  for ( i = 0; i < 10; i++ ) {
    idents[i] = strdup ("Hello world");
  }



  result = getInput(pStub,input);

  printf ("Result\n");
  if ( result == NULL )
   printf ("NULL\n");
  else {
   printf ("att_enum_int %d\n", result->att_enum_int);
   printf ("att_enum_string %s\n", result->att_enum_string);
   printf ("enum_int %d\n", result->enum_int);
   printf ("enum_string %s\n", result->enum_string);
   printf ("enum_kind %s\n", result->att_enum_kind);
  }

  //Axis_Delete_Type1(input,0,0);
  //Axis_Delete_Type1(result,0,0);

  destroy_SimpleTypeInnerUnboundedWS_stub(pStub);
  
  return 0;
}
