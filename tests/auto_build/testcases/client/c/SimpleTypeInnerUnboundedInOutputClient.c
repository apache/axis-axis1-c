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
