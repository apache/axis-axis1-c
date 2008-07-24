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
 * NestedComplex
 * 
 * Send a complex data type, ComplexType2, which has a data element of an
 * array of a complex data type, ComplexType1. The ComplexType1 data type
 * has a xsd:string element, a xsd:int element and a complex data type element
 * SimpleArrays. The SimpleArrays complex data type has a xsd:string array and
 * a xsd_int array.
 *
 * ComplexType2
 *   + ComplexType1[]
 *       + string
 *       + int
 *       + SimpleArrays
 *           + string[]
 *           + int[]
 *
 * This is an echo type service so the response should be the same as the request.
 *
 * Author: Andrew Perry
 *
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* CHANGES TO THIS FILE MAY ALSO REQUIRE CHANGES TO THE               */
/* C-EQUIVALENT FILE. PLEASE ENSURE THAT IT IS DONE.                  */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */


#include "NestedComplex.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2
#define NEWCOPY(ptr,str) {ptr=new char[strlen(str)+1]; strcpy(ptr,str);}

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/NestedComplex";

    if(argc>1)
        url = argv[1];

    try
    {
        sprintf(endpoint, "%s", url);
        NestedComplex ws(endpoint);

        ComplexType2 complexType2;
        ComplexType2* response;
        SimpleArrays *simpleArrays1 = new SimpleArrays;
        SimpleArrays *simpleArrays2 = new SimpleArrays;
        SimpleArrays *simpleArrays[2] = {simpleArrays1, simpleArrays2};
        ComplexType1 *complexType1_1 = new ComplexType1;
        ComplexType1 *complexType1_2 = new ComplexType1;

        for (int i=0; i<2; i++)
        {
            xsd__string_Array strArray;
            xsd__int_Array intArray;
            xsd__string strType[ARRAYSIZE];
            xsd__int * intType[ARRAYSIZE];
            NEWCOPY(strType[0], "Apache");
            NEWCOPY(strType[1], "Axis C++");
            strArray.set(strType,ARRAYSIZE);
            simpleArrays[i]->setstringArray(&strArray);
            intType[0] = new int(6);
            intType[1] = new int(7);
            intArray.set(intType,ARRAYSIZE);
            simpleArrays[i]->setintArray(&intArray);
            delete intType[0];
            delete intType[1];
            delete strType[0];
            delete strType[1];
            

        }

        complexType1_1->simpleArrays = simpleArrays1;
        NEWCOPY(complexType1_1->ct1_string, "Hello");
        complexType1_1->ct1_int = 13;
        complexType1_2->simpleArrays = simpleArrays2;
        NEWCOPY(complexType1_2->ct1_string, "World");
        complexType1_2->ct1_int = 27;


        ComplexType1_Array cType1Array;
        ComplexType1 * array[ARRAYSIZE];
        array[0]= complexType1_1;
        array[1] = complexType1_2;
        cType1Array.set(array,ARRAYSIZE);
        complexType2.setcomplexType1Array(&cType1Array);
        delete array[0];
        delete array[1];
        
        response = ws.echoNestedComplex(&complexType2);
        int outputSize =0;
        
        ComplexType1 ** output = response->getcomplexType1Array()->get(outputSize);
        
        cout << output[0]->ct1_string << endl;
        cout << output[0]->ct1_int << endl;
        cout << output[0]->simpleArrays->stringArray->get(outputSize)[0] << " ";
        cout << output[0]->simpleArrays->stringArray->get(outputSize)[1] << endl;
        cout << *(output[0]->simpleArrays->intArray->get(outputSize)[0]) << " ";
        cout << *(output[0]->simpleArrays->intArray->get(outputSize)[1]) << endl;
        cout << output[1]->ct1_string << endl;
        cout << output[1]->ct1_int << endl;
        cout << output[1]->simpleArrays->stringArray->get(outputSize)[0] << " ";
        cout << output[1]->simpleArrays->stringArray->get(outputSize)[1] << endl;
        cout << *(output[1]->simpleArrays->intArray->get(outputSize)[0]) << " ";
        cout << *(output[1]->simpleArrays->intArray->get(outputSize)[1]) << endl;

    }
    catch(AxisException& e)
    {
        cout << "Exception : " << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << "Unknown exception has occured : " << e.what() << endl;
    }
    catch(...)
    {
        cout << "Unknown exception has occured" << endl;
    }
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;

    return 0;
}

