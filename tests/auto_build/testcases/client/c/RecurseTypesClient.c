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

#include "RecurseTypesWS.h" 

int main(int argc, char* argv[])
{ 

  Kind inputAtt,*outputAtt;
  Type1 *input,*output,*pTemp;
  void * pStub;
  int i;

  pStub = get_RecurseTypesWS_stub();

  input = Axis_Create_Type1 (0,0,0);

  input->att_kind = Kind_CHEQUE;
  input->kind = strdup("Check In");
  
  input->followings.m_Array = Axis_Create_Type1 (0,1,10);
  input->followings.m_Size = 10;

  pTemp = input->followings.m_Array;
  for ( i = 0; i < 10; i++ ) {
    pTemp->kind = strdup("Sample");
    pTemp++;
  }

  output = getInput(pStub,input);

  printf ("Result\n");
  if ( output == NULL )
   printf ("Invoke failed\n");
  else {
   printf ("\tAtt_kind = %s\n", output->att_kind);
   printf ("\tKind = %s\n", output->kind);
   pTemp = output->followings.m_Array;
   for ( i = 0; i < output->followings.m_Size; i++ ) {
     printf ("\tKind [%d] = %s\n",i, pTemp->kind);
     pTemp++;
   }
  }

  /*
  Axis_Delete_Type1 (input,0,0);
  Axis_Delete_Type1 (output,0,0);
  */
  destroy_RecurseTypesWS_stub(pStub);
  return 0;
}
