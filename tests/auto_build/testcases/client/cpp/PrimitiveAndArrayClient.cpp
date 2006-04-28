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

#include "PrimitiveAndArray.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
        char endpoint[256];
        const char* url="http://localhost:80/axis/Calculator";

        if(argc>1)
                url = argv[1];

        try
        {
                sprintf(endpoint, "%s", url);
                PrimitiveAndArray* ws = new PrimitiveAndArray(endpoint);

                xsd__int single;
                xsd__int_Array intArray;
                ComplexReturn* response;

                single=37;

        xsd__int ** arrayOfInt = new xsd__int*[ARRAYSIZE];
                arrayOfInt[0] = new xsd__int(6);        
        arrayOfInt[1] = new xsd__int(7);                
                intArray.set(arrayOfInt,ARRAYSIZE);

                response = ws->sendPrimitiveAndArray(single, &intArray);
                int outputSize = 0;
                const xsd__int **output = response->getreturnArray()->get(outputSize);
                cout << response->returnInt << " " << *(output[0]) << " " << *(output[1]) << endl;
                single=43;
        *arrayOfInt[0] = 13;
        *arrayOfInt[1] = 17;
                intArray.set(arrayOfInt,ARRAYSIZE);
                response = ws->sendArrayAndPrimitive(&intArray, single);
                outputSize = 0;
                output = response->getreturnArray()->get(outputSize);
                cout << response->returnInt << " " << *(output[0]) << " " << *(output[1]) << endl;
                delete arrayOfInt[0];
                delete arrayOfInt[1];
                delete [] arrayOfInt;
                delete ws;
        }
        catch(AxisException& e)
        {
            cout << "Exception : " << e.what() << endl;
        }
        catch(exception& e)
        {
            cout << "Unknown exception has occured" << endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occured" << endl;
        }
        cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
        
        return 0;
}

