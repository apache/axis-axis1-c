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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "CommonClientTestCode.h"
#include "NestedArrays.h"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;     

    /* These contain xsdc__int_Array */
    ArrayOf_xsd_int baseArray1;
    ArrayOf_xsd_int baseArray2;
    ArrayOf_xsd_int baseArray3;
    ArrayOf_xsd_int baseArray4;

    /* These contain ArrayOf_xsd_int_Array */
    ArrayOfArrayOf_xsd_int subArray1;
    ArrayOfArrayOf_xsd_int subArray2;

    /* This is an array of ArrayOfArrayOf_xsd_int */
    ArrayOfArrayOf_xsd_int_Array parentArray;

    xsdc__int_Array baseArray1In;
    xsdc__int * baseArray1Vales[ARRAYSIZE];
    
    xsdc__int_Array baseArray2In;
    xsdc__int * baseArray2Vales[ARRAYSIZE];

    xsdc__int_Array baseArray3In;
    xsdc__int * baseArray3Vales[ARRAYSIZE];

    xsdc__int_Array baseArray4In;
    xsdc__int * baseArray4Vales[ARRAYSIZE];

    ArrayOf_xsd_int_Array sarray1;
    ArrayOf_xsd_int * array1[ARRAYSIZE];

    ArrayOf_xsd_int_Array sarray2;
    ArrayOf_xsd_int * array2[ARRAYSIZE];

    ArrayOfArrayOf_xsd_int * pArray[ARRAYSIZE];

    xsdc__int_Array* response;
    xsdc__int ** output; 
    
    xsdc__int intValues[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/NestedArrays";

    if(argc>1)
        url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_NestedArrays_stub(endpoint);

    /* Set xsdc__int_Array into ArrayOf_xsd_int */
    baseArray1Vales[0] = &intValues[0];
    baseArray1Vales[1] = &intValues[1];
    baseArray1In.m_Array = baseArray1Vales;
    baseArray1In.m_Size = ARRAYSIZE;
    baseArray1In.m_Type = XSDC_INT;
    baseArray1.item= &baseArray1In;

    baseArray2Vales[0] =&intValues[2];
    baseArray2Vales[1] =&intValues[3];
    baseArray2In.m_Array = baseArray2Vales;
    baseArray2In.m_Size = ARRAYSIZE;
    baseArray2In.m_Type = XSDC_INT;
    baseArray2.item = (&baseArray2In);

    baseArray3Vales[0] = &intValues[4];
    baseArray3Vales[1] = &intValues[5];
    baseArray3In.m_Array = baseArray3Vales;
    baseArray3In.m_Size = ARRAYSIZE;
    baseArray3In.m_Type = XSDC_INT;
    baseArray3.item = (&baseArray3In);

    baseArray4Vales[0] = &intValues[6];
    baseArray4Vales[1] = &intValues[7];
    baseArray4In.m_Array = baseArray4Vales;
    baseArray4In.m_Size = ARRAYSIZE;
    baseArray4In.m_Type = XSDC_INT;
    baseArray4.item = (&baseArray4In);

    /* Set ArrayOf_xsd_int_Array into ArrayOfArrayOf_xsd_int */
    array1[0] = &baseArray1;
    array1[1] = &baseArray2;
    sarray1.m_Array = array1;
    sarray1.m_Size = ARRAYSIZE;
    sarray1.m_Type = C_USER_TYPE;
    subArray1.item = &sarray1;

    array2[0] = &baseArray3;
    array2[1] = &baseArray4;
    sarray2.m_Array = array2;
    sarray2.m_Size = ARRAYSIZE;
    sarray2.m_Type = C_USER_TYPE;
    subArray2.item = &sarray2;

    /* Set ArrayOfArrayOf_xsd_int into an Array of them */

    pArray[0]=&subArray1;
    pArray[1]=&subArray2;
    parentArray.m_Array = pArray;
    parentArray.m_Size = ARRAYSIZE;
    parentArray.m_Type = C_USER_TYPE;

    response = sendNestedArrays(ws, &parentArray);
    
    if (response)
    {
      if (response->m_Size > 1)
        printf("%d %d\n", *(response->m_Array[0]), *(response->m_Array[1]));
      else
        printf("Failed, array size not correct\n");
    }
    else
        printf("Failed, response is NULL\n");
        
    axiscAxisDelete(response, XSDC_ARRAY);
    
    destroy_NestedArrays_stub(ws);

    printf( "---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

