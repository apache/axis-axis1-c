#include "LargeReturningString.h" 

int main(int argc, char* argv[])
{ 
  void * pStub = get_LargeReturningString_stub  ();

  int input = 20000;
  xsd__string result;

  result = getLargeReturningString(pStub,input);

  printf ("Result\n");
  if ( result == NULL )
   printf ("NULL\n");
  else {
   printf ("%s\n", result);
  }
  
  return 0;
}
