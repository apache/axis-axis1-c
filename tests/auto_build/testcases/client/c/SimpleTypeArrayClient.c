#include "SimpleTypeArrayWS.h" 
int main(int argc, char* argv[])
{ 

  void *pStub;
  Type *input;
  Type *output;
  xsd__int_Array array_input;
  xsd__int_Array array_output;
  int * entries;
  int i;

  entries = malloc ( sizeof (int) );

  array_input.m_Array = entries;
  array_input.m_Size  = 100;

  for ( i = 0; i < 100; i++ ) {
    entries[i] = i;
  }

  input = Axis_Create_Type(0,0,0);
  input->item = array_input;

  pStub = 
    get_SimpleTypeArrayWS_stub();
  
  output = getInput(pStub, input);

  for ( i = 0; i < 100; i++ ) {
    printf ("item [%d] = %d\n",i,output->item.m_Array[i]);
  }
  
  Axis_Delete_Type(input,0,0);
  Axis_Delete_Type(output,0,0);

  destroy_SimpleTypeArrayWS_stub(pStub);


}

