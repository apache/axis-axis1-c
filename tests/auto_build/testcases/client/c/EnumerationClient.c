#include "EnumerationWS.h" 

int main(int argc, char* argv[])
{ 
  void * pStub = get_EnumerationWS_stub  ();

  Type1 *input = Axis_Create_Type1(0,0,0);
  
  Type1* result;

  input->enum_int = ENUMTYPEINT_0;
  input->enum_string = strdup("one");
  input->att_enum_kind = strdup("CHEQUE");
  input->att_enum_string = strdup("one");
  input->att_enum_int = ENUMTYPEINT_1;

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

  Axis_Delete_Type1(input,0,0);
  Axis_Delete_Type1(result,0,0);
  
  return 0;
}
