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


/*
 * ComplexLists tests several things all at once.
 *
 * The areas being tested are:
 * 1. AXISCPP-487 - Elements of basic XSD types do not serialize namespace declaration
 * 2. AXISCPP-488 - Array types don't serialize namespace declarations
 * 3. AXISCPP-489 - Serializer not removing namespaces as they go out of scope
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "CommonClientTestCode.h"
#include "ComplexLists.h"

#define ARRAYSIZE 2

void printResponse(attrlisterr* ale)
{
    if(ale)
    {
        if (ale->errortext)
            printf( "%s\n", ale->errortext );
        else
            printf( "ale->errortext is NULL\n" );

        if (ale->errorcode)
            printf( "%d\n", ale->errorcode );
        else
            printf( "ale->errorcode is NULL\n" );

        if (ale->attrlist_Ref != NULL)
        {
            namepair ** output =ale->attrlist_Ref->item->m_Array;
            
            if (output[0] != NULL)
            {
                if (output[0]->name != NULL)
                    printf( "%s\n", output[0]->name );
                else
                    printf( "ale->attrlist_Ref->item.m_Array[0]->name is NULL\n" );

                if (output[0]->m_list_Ref != NULL)
                {
                    xsdc__string * outString = output[0]->m_list_Ref->item->m_Array;
                    if (outString[0] && *(outString[0]))
                        printf( "%s\n", outString[0] );
                    else
                        printf( "ale->attrlist_Ref->item.m_Array[0]->m_list_Ref->item.m_Array[0]\n" );
                }
            }
        }
    }
    else
        printf( "Deserialized response is NULL\n" );
}

int main(int argc, char* argv[])
{
    AXISCHANDLE ws;
    
    xsdc__string array[ARRAYSIZE];
    xsdc__string array1[ARRAYSIZE];
    xsdc__string array2[ARRAYSIZE];
        
    attrlisterr* ale;
    
    char endpoint[256];
    const char* url="http://localhost:80/axis/ComplexLists";

    m_list *   ml    = Axis_Create_m_list(0);   // xsdc__string array
    m_list *   mlnp  = Axis_Create_m_list(0);   // used for 1st namepair item of array
    m_list *   mlnp2 = Axis_Create_m_list(0);   // used for 2nd namepair item of array
    attrlist   al;                              // attrlist has namepair array
    namepair * np1   = Axis_Create_namepair(0); // namepair has m_list and name
    namepair * np2   = Axis_Create_namepair(0); 
    namepair_Array npArr;
    namepair *nArray[ARRAYSIZE];

    axiscAxisRegisterExceptionHandler(exceptionHandler);

    if(argc>1) url = argv[1];

    sprintf(endpoint, "%s", url);
    ws = get_ComplexLists_stub(endpoint);


    // m_list arg to numtilist
    array[0] = "never odd or even"; // should be returned in errortext element of attrlisterr
    array[1] = "any data string";   // add data
    ml->item->m_Array = array;
    ml->item->m_Size  = ARRAYSIZE;

    // To set into namepair item of namepair array of attrlist arg of multilist
    array1[0] = "Apache";
    array1[1] = "Axis C++";
    mlnp->item->m_Array = array1;
    mlnp->item->m_Size  = ARRAYSIZE;
 

    // To set into namepair item of namepair array of attrlist arg of multilist
    array2[0] =  "Test";
    array2[1] =  "Complex";
    mlnp2->item->m_Array = array2;
    mlnp2->item->m_Size  = ARRAYSIZE;

    // set first namepair item to put into array
    np1->m_list_Ref = mlnp;
    np1->name = "namepair1";

    // set second namepair item to put into array
    np2->m_list_Ref = mlnp2;
    np2->name = "namepair2";

    // create a namepair array to add into attrlist
    nArray[0]=np1;
    nArray[1]=np2;
    npArr.m_Array = nArray;
    npArr.m_Size  = ARRAYSIZE;

    // set attrlist argument
    al.item = (&npArr);

    ale = multilist(ws, ml, &al);
    printResponse(ale);
    Axis_Delete_attrlisterr(ale, 0);

    ale = multilist(ws, (m_list*)NULL, &al);
    printResponse(ale);
    Axis_Delete_attrlisterr(ale, 0);

    // Have nil elements in response
    ale = multilistnil(ws, (m_list*)NULL, &al);
    printResponse(ale);
    Axis_Delete_attrlisterr(ale, 0);

    ale = complexlist(ws, &al, "hoohah!", &al);
    printResponse(ale);
    Axis_Delete_attrlisterr(ale, 0);

    // figure out what needs to be reclaimed

    destroy_ComplexLists_stub(ws);
    
    printf("---------------------- TEST COMPLETE -----------------------------\n");

    return 0;
}

