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

