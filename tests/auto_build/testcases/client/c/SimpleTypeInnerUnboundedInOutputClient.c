#include "SimpleTypeInnerUnboundedInOutputWS.h" 

int main(int argc, char* argv[])
{ 
  int i;
  int size;
  void * pStub = get_SimpleTypeInnerUnboundedInOutputWS_stub ();

  Type1* result;

  size = 10;

  result = getInput(pStub,size);

  if ( result == NULL )
   printf ("NULL\n");
  else {
    Type1_ident* pTemp = result->ident.m_Array;
    for ( i = 0; i < result->ident.m_Size; i++ ) {
      printf ("Result [%d] : %s\n",i,pTemp[i]);
    }
  }

  Axis_Delete_Type1(result,0,0);

  destroy_SimpleTypeInnerUnboundedInOutputWS_stub(pStub);
  
  return 0;
}
