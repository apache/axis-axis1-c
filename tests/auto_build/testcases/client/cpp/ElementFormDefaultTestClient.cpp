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

#include "ElementFormDefaultTest.hpp"
#include "CommonClientTestCode.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/ElementFormDefaultTest";

    signal(SIGILL, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGSEGV, sig_handler);
    //signal(SIGQUIT, sig_handler);
    //signal(SIGBUS, sig_handler);
    signal(SIGFPE, sig_handler);

    url = argv[1];

    bool bSuccess = false;
    int iRetryIterationCount = 3;
    do
    {
        try
        {
            sprintf(endpoint, "%s", url);
            ElementFormDefaultTest ws(endpoint);

                        int arraySize = 2;
                        int count = 0;
                        int outputSize = 0;
                        
                        // form="unqualified"
                        cout << "Use of form=\"unqualified\"" << endl;
                        {
                                // Prepare input parameters                     
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer integerElement = 123;
                                xsd__integer_Array * integerArrayElement = new xsd__integer_Array();
                                xsd__integer** arrayOfInteger = new xsd__integer*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        arrayOfInteger[count] = new xsd__integer(count);
                                }
                                integerArrayElement->set(arrayOfInteger, arraySize);
                                xsd__integer * optionalInteger = new xsd__integer(234); // While optional, we can only test correct namespace handling if we have a value!
                                xsd__integer * nillableInteger = NULL;

                                UnqualifiedSimpleComplexType * complexType = new UnqualifiedSimpleComplexType();
                                complexType->setsomeData(345);

                                UnqualifiedSimpleComplexType_Array * arrayOfComplexType = new UnqualifiedSimpleComplexType_Array();
                                UnqualifiedSimpleComplexType** complexTypeArray = new UnqualifiedSimpleComplexType*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        complexTypeArray[count] = new UnqualifiedSimpleComplexType();
                                        complexTypeArray[count]->setsomeData(count);
                                }
                                arrayOfComplexType->set(complexTypeArray, arraySize);

                                // Prepare output parameters
                                xsd__string outStringElement = NULL;
                                xsd__integer outIntegerElement;
                                xsd__integer_Array * outIntegerArrayElement = NULL;
                                xsd__integer * outOptionalIntegerElement = NULL;
                                xsd__integer * outNillableIntegerElement = NULL;
                                UnqualifiedSimpleComplexType * outComplexType = NULL;
                                UnqualifiedSimpleComplexType_Array * outArrayOfComplexType = NULL;

                                // Call method on web service
                                ws.elementFormDefaultIsUnqualified(stringElement,
                                        integerElement,
                                        integerArrayElement,
                                        optionalInteger,
                                        nillableInteger,
                                        complexType,
                                        arrayOfComplexType,
                                        &outStringElement,
                                        &outIntegerElement,
                                        &outIntegerArrayElement, 
                                        &outOptionalIntegerElement, 
                                        &outNillableIntegerElement, 
                                        &outComplexType, 
                                        &outArrayOfComplexType);

                                // Clean up inputs
                                delete [] stringElement;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete arrayOfInteger[count];
                                }
                                delete [] arrayOfInteger;
                                delete integerArrayElement;
                                delete optionalInteger;
                                delete complexType;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete complexTypeArray[count];
                                }
                                delete [] complexTypeArray;
                                delete arrayOfComplexType;
                                

                                // Print output values
                                cout << "String element = " << outStringElement << endl;
                                delete [] outStringElement;
                                cout << "Integer element = " << outIntegerElement << endl;
                                cout << "Array of integer elements" << endl;
                                outputSize = 0;
                                const xsd__integer** outArrayOfIntegers = outIntegerArrayElement->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outArrayOfIntegers[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << *outArrayOfIntegers[count] << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete outIntegerArrayElement;
                                if (outOptionalIntegerElement != NULL)
                                {
                                        cout << "Optional integer element = " << *outOptionalIntegerElement << endl;
                                        delete outOptionalIntegerElement;
                                }
                                else
                                {
                                        cout << "Optional integer element = NULL" << endl;
                                }
                                if (outNillableIntegerElement != NULL)
                                {
                                        cout << "Nillable integer element = " << *outNillableIntegerElement << endl;
                                        delete outNillableIntegerElement;
                                }
                                else
                                {
                                        cout << "Nillable integer element = NULL" << endl;
                                }
                                cout << "SimpleComplexType->someData = " << outComplexType->someData << endl;
                                delete outComplexType;
                                cout << "Array of complex elements" << endl;
                                outputSize = 0;
                                UnqualifiedSimpleComplexType** outComplexArray = outArrayOfComplexType->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outComplexArray[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << outComplexArray[count]->someData << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete outArrayOfComplexType;
                        }


                        // form="qualified"
                        cout << "Use of form=\"qualified\"" << endl;
                        {
                                // Prepare input parameters                     
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer integerElement = 123;
                                xsd__integer_Array * integerArrayElement = new xsd__integer_Array();
                                xsd__integer** arrayOfInteger = new xsd__integer*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        arrayOfInteger[count] = new xsd__integer(count);
                                }
                                integerArrayElement->set(arrayOfInteger, arraySize);
                                xsd__integer * optionalInteger = new xsd__integer(234); // While optional, we can only test correct namespace handling if we have a value!
                                xsd__integer * nillableInteger = NULL;

                                QualifiedSimpleComplexType * complexType = new QualifiedSimpleComplexType();
                                complexType->setsomeData(345);

                                QualifiedSimpleComplexType_Array * arrayOfComplexType = new QualifiedSimpleComplexType_Array();
                                QualifiedSimpleComplexType** complexTypeArray = new QualifiedSimpleComplexType*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        complexTypeArray[count] = new QualifiedSimpleComplexType();
                                        complexTypeArray[count]->setsomeData(count);
                                }
                                arrayOfComplexType->set(complexTypeArray, arraySize);

                                // Prepare output parameters
                                xsd__string outStringElement = NULL;
                                xsd__integer outIntegerElement;
                                xsd__integer_Array * outIntegerArrayElement = NULL;
                                xsd__integer * outOptionalIntegerElement = NULL;
                                xsd__integer * outNillableIntegerElement = NULL;
                                QualifiedSimpleComplexType * outComplexType = NULL;
                                QualifiedSimpleComplexType_Array * outArrayOfComplexType = NULL;

                                // Call method on web service
                                ws.elementFormDefaultIsQualified(stringElement,
                                        integerElement,
                                        integerArrayElement,
                                        optionalInteger,
                                        nillableInteger,
                                        complexType,
                                        arrayOfComplexType,
                                        &outStringElement,
                                        &outIntegerElement,
                                        &outIntegerArrayElement, 
                                        &outOptionalIntegerElement, 
                                        &outNillableIntegerElement, 
                                        &outComplexType, 
                                        &outArrayOfComplexType);

                                // Clean up inputs
                                delete [] stringElement;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete arrayOfInteger[count];
                                }
                                delete [] arrayOfInteger;
                                delete integerArrayElement;
                                delete optionalInteger;
                                delete complexType;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete complexTypeArray[count];
                                }
                                delete [] complexTypeArray;
                                delete arrayOfComplexType;

                                // Print output values
                                cout << "String element = " << outStringElement << endl;
                                delete [] outStringElement;
                                cout << "Integer element = " << outIntegerElement << endl;
                                cout << "Array of integer elements" << endl;
                                outputSize = 0;
                                const xsd__integer** outArrayOfIntegers = outIntegerArrayElement->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outArrayOfIntegers[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << *outArrayOfIntegers[count] << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete outIntegerArrayElement;
                                if (outOptionalIntegerElement != NULL)
                                {
                                        cout << "Optional integer element = " << *outOptionalIntegerElement << endl;
                                        delete outOptionalIntegerElement;
                                }
                                else
                                {
                                        cout << "Optional integer element = NULL" << endl;
                                }
                                if (outNillableIntegerElement != NULL)
                                {
                                        cout << "Nillable integer element = " << *outNillableIntegerElement << endl;
                                        delete outNillableIntegerElement;
                                }
                                else
                                {
                                        cout << "Nillable integer element = NULL" << endl;
                                }
                                cout << "SimpleComplexType->someData = " << outComplexType->someData << endl;
                                delete outComplexType;
                                cout << "Array of complex elements" << endl;
                                outputSize = 0;
                                QualifiedSimpleComplexType** outComplexArray = outArrayOfComplexType->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outComplexArray[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << outComplexArray[count]->someData << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete outArrayOfComplexType;
                        }

                        // Nested within a Complex Type
                        // form="unqualified"
                        cout << "Use of form=\"unqualified\" nested within a complex type" << endl;
                        {
                                // Prepare input parameters                     
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer integerElement = 123;
                                xsd__integer_Array * integerArrayElement = new xsd__integer_Array();
                                xsd__integer** arrayOfInteger = new xsd__integer*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        arrayOfInteger[count] = new xsd__integer(count);
                                }
                                integerArrayElement->set(arrayOfInteger, arraySize);
                                xsd__integer * optionalInteger = new xsd__integer(234); // While optional, we can only test correct namespace handling if we have a value!
                                xsd__integer * nillableInteger = NULL;

                                UnqualifiedSimpleComplexType * complexType = new UnqualifiedSimpleComplexType();
                                complexType->setsomeData(345);

                                UnqualifiedSimpleComplexType_Array * arrayOfComplexType = new UnqualifiedSimpleComplexType_Array();
                                UnqualifiedSimpleComplexType** complexTypeArray = new UnqualifiedSimpleComplexType*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        complexTypeArray[count] = new UnqualifiedSimpleComplexType();
                                        complexTypeArray[count]->setsomeData(count);
                                }
                                arrayOfComplexType->set(complexTypeArray, arraySize);

                                ElementFormDefaultIsUnqualified input;
                                input.setaStringType(stringElement);
                                input.setanIntegerType(integerElement);
                                input.setanIntegerArray(integerArrayElement);
                                input.setanOptionalIntegerType(optionalInteger);
                                input.setaNillableIntegerType(nillableInteger);
                                input.setSimpleComplexType(complexType);
                                input.setarrayOfSimpleComplexType(arrayOfComplexType);

                                // Call method on web service
                                ElementFormDefaultIsUnqualified * output = ws.nestedElementFormDefaultIsUnqualified(&input);

                                // Clean up inputs
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete arrayOfInteger[count];
                                }
                                delete [] arrayOfInteger;
                                delete integerArrayElement;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete complexTypeArray[count];
                                }
                                delete [] complexTypeArray;
                                delete arrayOfComplexType;

                                // Print output values
                                cout << "String element = " << output->aStringType << endl;
                                cout << "Integer element = " << output->anIntegerType << endl;
                                cout << "Array of integer elements" << endl;
                                outputSize = 0;
                                const xsd__integer** outArrayOfIntegers = output->anIntegerArray->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outArrayOfIntegers[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << *outArrayOfIntegers[count] << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                if (output->anOptionalIntegerType != NULL)
                                {
                                        cout << "Optional integer element = " << *output->anOptionalIntegerType << endl;
                                }
                                else
                                {
                                        cout << "Optional integer element = NULL" << endl;
                                }
                                if (output->aNillableIntegerType != NULL)
                                {
                                        cout << "Nillable integer element = " << *output->aNillableIntegerType << endl;
                                }
                                else
                                {
                                        cout << "Nillable integer element = NULL" << endl;
                                }
                                cout << "SimpleComplexType->someData = " << output->SimpleComplexType->someData << endl;
                                cout << "Array of complex elements" << endl;
                                outputSize = 0;
                                UnqualifiedSimpleComplexType** outComplexArray = output->arrayOfSimpleComplexType->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outComplexArray[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << outComplexArray[count]->someData << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete output;
                        }

                        // form="qualified"
                        cout << "Use of form=\"qualified\" nested within a complex type" << endl;
                        {
                                // Prepare input parameters                     
                                xsd__string stringElement = new char[7];
                                strcpy(stringElement, "Hello!");
                                xsd__integer integerElement = 123;
                                xsd__integer_Array * integerArrayElement = new xsd__integer_Array();
                                xsd__integer** arrayOfInteger = new xsd__integer*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        arrayOfInteger[count] = new xsd__integer(count);
                                }
                                integerArrayElement->set(arrayOfInteger, arraySize);
                                xsd__integer * optionalInteger = new xsd__integer(234); // While optional, we can only test correct namespace handling if we have a value!
                                xsd__integer * nillableInteger = NULL;

                                QualifiedSimpleComplexType * complexType = new QualifiedSimpleComplexType();
                                complexType->setsomeData(345);

                                QualifiedSimpleComplexType_Array * arrayOfComplexType = new QualifiedSimpleComplexType_Array();
                                QualifiedSimpleComplexType** complexTypeArray = new QualifiedSimpleComplexType*[arraySize];
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        complexTypeArray[count] = new QualifiedSimpleComplexType();
                                        complexTypeArray[count]->setsomeData(count);
                                }
                                arrayOfComplexType->set(complexTypeArray, arraySize);

                                ElementFormDefaultIsQualified input;
                                input.setaStringType(stringElement);
                                input.setanIntegerType(integerElement);
                                input.setanIntegerArray(integerArrayElement);
                                input.setanOptionalIntegerType(optionalInteger);
                                input.setaNillableIntegerType(nillableInteger);
                                input.setSimpleComplexType(complexType);
                                input.setarrayOfSimpleComplexType(arrayOfComplexType);

                                // Call method on web service
                                ElementFormDefaultIsQualified * output = ws.nestedElementFormDefaultIsQualified(&input);

                                // Clean up inputs
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete arrayOfInteger[count];
                                }
                                delete [] arrayOfInteger;
                                delete integerArrayElement;
                                for (count = 0 ; count < arraySize ; count++ )
                                {
                                        delete complexTypeArray[count];
                                }
                                delete [] complexTypeArray;
                                delete arrayOfComplexType;

                                // Print output values
                                cout << "String element = " << output->aStringType << endl;
                                cout << "Integer element = " << output->anIntegerType << endl;
                                cout << "Array of integer elements" << endl;
                                outputSize = 0;
                                const xsd__integer** outArrayOfIntegers = output->anIntegerArray->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outArrayOfIntegers[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << *outArrayOfIntegers[count] << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                if (output->anOptionalIntegerType != NULL)
                                {
                                        cout << "Optional integer element = " << *output->anOptionalIntegerType << endl;
                                }
                                else
                                {
                                        cout << "Optional integer element = NULL" << endl;
                                }
                                if (output->aNillableIntegerType != NULL)
                                {
                                        cout << "Nillable integer element = " << *output->aNillableIntegerType << endl;
                                }
                                else
                                {
                                        cout << "Nillable integer element = NULL" << endl;
                                }
                                cout << "SimpleComplexType->someData = " << output->SimpleComplexType->someData << endl;
                                cout << "Array of complex elements" << endl;
                                outputSize = 0;
                                QualifiedSimpleComplexType** outComplexArray = output->arrayOfSimpleComplexType->get(outputSize);
                                for (count = 0 ; count < outputSize ; count++ )
                                {
                                        if (outComplexArray[count] != NULL)
                                        {
                                                cout << " element[" << count << "] = " << outComplexArray[count]->someData << endl;
                                        }
                                        else
                                        {
                                                cout << " element[" << count << "] = NULL" << endl;
                                        }
                                }
                                delete output;
                        }


                        // All tests were successful
            bSuccess = 1;
        }
        catch(AxisException& e)
        {
            bool bSilent = false;

           if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
          {
             if( iRetryIterationCount > 0)
             {
                 bSilent = true;
               }
         }
         else
          {
             iRetryIterationCount = 0;
         }

            if( !bSilent)
            {
             cout << "Exception : " << e.what() << endl;
           }
     }
     catch(exception& e)
       {
         cout << "Unexpected exception has occured: " << e.what() << endl;
     }
     catch(...)
        {
         cout << "Unknown exception has occured" << endl;
      }
     iRetryIterationCount--;
   } while( iRetryIterationCount > 0 && !bSuccess);
    cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
 
  return 0;
}

void PrintUsage()
{
  printf("Usage :\n Calculator <url>\n\n");
 exit(1);
}

bool IsNumber(const char* p)
{
    for (unsigned int x=0; x < strlen(p); x++)
 {
     if (!isdigit(p[x])) return false;
 }
 return true;
}

void sig_handler(int sig) {
    signal(sig, sig_handler);
    cout << "SIGNAL RECEIVED " << sig << endl;
 exit(1);
}
