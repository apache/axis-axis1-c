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
