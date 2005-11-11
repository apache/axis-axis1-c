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

#include "Arrays.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include <signal.h>

void sig_handler(int);
void PrintUsage();
bool IsNumber(const char* p);

void testAxis_Array();
void testAxis_ArrayWithNillElements();
void testAxis_ArrayCopying();
void testComplexTypeWithSimpleArray();
void testArrayOfComplexType();
void testCopyingArrayOfComplexType();

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* url="http://localhost:80/axis/Arrays";

    signal(SIGILL, sig_handler);
    signal(SIGABRT, sig_handler);
    signal(SIGSEGV, sig_handler);
    //signal(SIGQUIT, sig_handler);
    //signal(SIGBUS, sig_handler);
    signal(SIGFPE, sig_handler);

    url = argv[1];

    testAxis_Array();
    testAxis_ArrayWithNillElements();
    testAxis_ArrayCopying();
	testComplexTypeWithSimpleArray();
	testArrayOfComplexType();
	testCopyingArrayOfComplexType();

    bool bSuccess = false;
    int iRetryIterationCount = 3;
    do
    {
        try
        {
			int count = 0;
            sprintf(endpoint, "%s", url);
            Arrays ws(endpoint);

            int arraySize = 3;
            xsd__int_Array inputArray;
            xsd__int** array = new xsd__int*[arraySize];
            for (count = 0 ; count < arraySize ; count++)
            {
                array[count] = new xsd__int(count);
            }
            inputArray.set(array, arraySize);

            xsd__int_Array * outputArray = ws.simpleArray(&inputArray);
            int outputSize = 0;
            const xsd__int** output = outputArray->get(outputSize);
            cout << "Array size = " << outputSize << endl;
            if (output != NULL)
            {
                for (count = 0 ; count < outputSize ; count++)
                {
                    if (output[count] != NULL)
                    {
                        cout << *output[count] << endl;
                    }
                    else
                    {
                        cout << "NULL" << endl;
                    }
                }
            }
            else
            {
                cout << "NULL array" << endl;
            }
			delete outputArray;
            

			ComplexTypeWithSimpleArray * inputComplexType = new ComplexTypeWithSimpleArray;
			inputComplexType->setsimpleType(&inputArray);
			ComplexTypeWithSimpleArray * outputComplexType = ws.complexTypeWithSimpleArray(inputComplexType);
			outputArray = outputComplexType->getsimpleType();
			if (outputComplexType != NULL)
			{
				output = outputArray->get(outputSize);
				cout << "Array size = " << outputSize << endl;
				if (output != NULL)
				{
					for (int count = 0 ; count < outputSize ; count++)
					{
						if (output[count] != NULL)
						{
							cout << *output[count] << endl;
						}
						else
						{
							cout << "NULL" << endl;
						}
					}
				}
				else
				{
					cout << "NULL array" << endl;
				}
			}
			else
			{
				cout << "NULL complex type" << endl;
			}

			// Clean up simple input array
			for (count = 0 ; count < arraySize ; count++)
			{
				delete array[count];
			}
			delete [] array;

			delete inputComplexType;
			delete outputComplexType;

			ComplexTypeWithSimpleElement_Array complexArray;
			int inputSize = 3;
			ComplexTypeWithSimpleElement** complexInputArray = new ComplexTypeWithSimpleElement*[inputSize];
			for (count = 0 ; count < inputSize ; count++)
			{
				complexInputArray[count] = new ComplexTypeWithSimpleElement();
				complexInputArray[count]->setsimpleType(count);
			}
			complexArray.set(complexInputArray, inputSize);

			ComplexTypeWithSimpleElement_Array * complexOutputAxis_Array = ws.complexTypeArray(&complexArray);

			outputSize = 0;
			const ComplexTypeWithSimpleElement** complexOutputArray = complexOutputAxis_Array->get(outputSize);
			cout << "Complex array size is " << outputSize << endl;
			if (complexOutputArray != NULL)
			{
				for (count = 0 ; count < outputSize ; count++)
				{
					if (complexOutputArray[count] != NULL)
					{
						cout << ((ComplexTypeWithSimpleElement) *complexOutputArray[count]).getsimpleType() << endl;
					}
					else
					{
						cout << "NULL" << endl;
					}
				}
			}
			else
			{
				cout << "NULL array" << endl;
			}
			delete complexOutputAxis_Array;

			// Clean up complex input array
			for (count = 0 ; count < inputSize ; count++)
			{
				delete complexInputArray[count];
			}
			delete [] complexInputArray;

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

void testAxis_Array()
{
    int count = 0;
    // Unit test the Axis_Array object for simple types (in this case xsd__int)
    // Initialize Array
    int unitTestInputSize = 3;
    xsd__int_Array unitTest_Axis_Array;
    xsd__int** unitTestActualArray = new xsd__int*[unitTestInputSize];
    for (count = 0 ; count < unitTestInputSize ; count++ )
    {
        unitTestActualArray[count] = new xsd__int(count);
    }
    unitTest_Axis_Array.set(unitTestActualArray, unitTestInputSize);

    // Verify the correct data is available
    int size;
    const xsd__int** unitTestOutputArray = unitTest_Axis_Array.get(size);
    cout << "Array size = " << size << endl;
    if (unitTestOutputArray != NULL)
    {
        for (count = 0 ; count < size ; count++)
        {
            if (unitTestOutputArray[count] != NULL)
            {
                cout << *unitTestOutputArray[count] << endl;
            }
            else
            {
                cout << "NULL" << endl;
            }
        }
    }
    else
    {
        cout << "NULL array" << endl;
    }

    // Alter the content of the original array, this should no longer affect the Axis_Array object
    for (count = 0 ; count < unitTestInputSize ; count++ )
    {
        *unitTestActualArray[count] = count * 1000;
    }

    // Verify the correct data is available, and not the altered content
    unitTestOutputArray = unitTest_Axis_Array.get(size);
    cout << "Array size = " << size << endl;
    if (unitTestOutputArray != NULL)
    {
        for (count = 0 ; count < size ; count++)
        {
            if (unitTestOutputArray[count] != NULL)
            {
                cout << *unitTestOutputArray[count] << endl;
            }
            else
            {
                cout << "NULL" << endl;
            }
        }
    }
    else
    {
        cout << "NULL array" << endl;
    }

    // Delete the original array, this should not affect the Axis_Array
    for (count = 0 ; count < unitTestInputSize ; count++)
    {
        delete unitTestActualArray[count];
    }
    delete [] unitTestActualArray;

    // Verify the correct data is still available
    unitTestOutputArray = unitTest_Axis_Array.get(size);
    cout << "Array size = " << size << endl;
    if (unitTestOutputArray != NULL)
    {
        for (count = 0 ; count < size ; count++)
        {
            if (unitTestOutputArray[count] != NULL)
            {
                cout << *unitTestOutputArray[count] << endl;
            }
            else
            {
                cout << "NULL" << endl;
            }
        }
    }
    else
    {
        cout << "NULL array" << endl;
    }
}

void testAxis_ArrayWithNillElements()
{
    // Unit test the Axis_Array object for simple types (in this case xsd__int) with a nil (NULL) element
    // Initialize Array
    int unitTestInputSize = 3;
    xsd__int_Array unitTest_Axis_Array;
    xsd__int** unitTestActualArray = new xsd__int*[unitTestInputSize];
    unitTestActualArray[0] = new xsd__int(12345);
    unitTestActualArray[1] = NULL;
    unitTestActualArray[2] = new xsd__int(54321);

    unitTest_Axis_Array.set(unitTestActualArray, unitTestInputSize);

	// Clean up the input array
	delete unitTestActualArray[0];
	delete unitTestActualArray[2];
	delete [] unitTestActualArray;

    // Verify the correct data is available
    int size;
    const xsd__int** unitTestOutputArray = unitTest_Axis_Array.get(size);
    cout << "Array size = " << size << endl;
    if (unitTestOutputArray != NULL)
    {
        for (int count = 0 ; count < size ; count++)
        {
            if (unitTestOutputArray[count] != NULL)
            {
                cout << *unitTestOutputArray[count] << endl;
            }
            else
            {
                cout << "NULL" << endl;
            }
        }
    }
    else
    {
        cout << "NULL array" << endl;
    }
}

void testAxis_ArrayCopying()
{
    int count = 0;
    int unitTestInputSize = 3;
    xsd__int_Array unitTest_Axis_Array;
    xsd__int** unitTestActualArray = new xsd__int*[unitTestInputSize];
    for (count = 0 ; count < unitTestInputSize ; count++ )
    {
        unitTestActualArray[count] = new xsd__int(count);
    }
    unitTest_Axis_Array.set(unitTestActualArray, unitTestInputSize);

    for (count = 0 ; count < unitTestInputSize ; count++ )
    {
        *unitTestActualArray[count] = count * 10;
    }
    unitTest_Axis_Array.set(unitTestActualArray, unitTestInputSize);

    for (count = 0 ; count < unitTestInputSize ; count++)
    {
        delete unitTestActualArray[count];
    }
    delete [] unitTestActualArray;

    int outputSize = 0;
    const xsd__int** outputArray = unitTest_Axis_Array.get(outputSize);
    cout << "Size is " << outputSize << endl;
    if (outputArray != NULL)
    {
        for (count = 0 ; count < outputSize ; count++)
        {
            if (outputArray[count] != NULL)
            {
                cout << *outputArray[count] << endl;
            }
            else
            {
                cout << "NULL" << endl;
            }
        }
    }
    else
    {
        cout << "NULL" << endl;
    }
}

void testComplexTypeWithSimpleArray()
{
	ComplexTypeWithSimpleArray complexType;
	int count = 0;
	int inputSize = 3;
	xsd__int_Array inputArray;
	xsd__int** array = new xsd__int*[inputSize];
	for (count = 0 ; count < inputSize ; count++ )
	{
		array[count] = new xsd__int(count);
	}
	inputArray.set(array, inputSize);
	
	// Clear up the input array
	for (count = 0 ; count < inputSize ; count++ )
	{
		delete array[count];
	}
	delete [] array;

	complexType.setsimpleType(&inputArray);

	xsd__int_Array * outputArray = complexType.getsimpleType();
	int outputSize = 0;
	const xsd__int** output = outputArray->get(outputSize);
	cout << "Size is " << outputSize << endl;
	if (output != NULL)
	{
		for (count = 0 ; count < outputSize ; count++ )
		{	
			if (output[count] != NULL)
			{
				cout << *output[count] << endl;
			}
			else
			{
				cout << "NULL" << endl;
			}

		}
	}
	else
	{
		cout << "NULL array" << endl;
	}


}

void testArrayOfComplexType()
{
	ComplexTypeWithSimpleElement_Array array;
	int count = 0;
	int inputSize = 3;
	ComplexTypeWithSimpleElement** inputArray = new ComplexTypeWithSimpleElement*[inputSize];
	for (count = 0 ; count < inputSize ; count++)
	{
		inputArray[count] = new ComplexTypeWithSimpleElement();
		inputArray[count]->setsimpleType(count);
	}
	array.set(inputArray, inputSize);

	int outputSize = 0;
	const ComplexTypeWithSimpleElement** outputArray = array.get(outputSize);
	cout << "Size is " << outputSize << endl;
	if (outputArray != NULL)
	{
		for (count = 0 ; count < outputSize ; count++)
		{
			if (outputArray[count] != NULL)
			{
				cout << ((ComplexTypeWithSimpleElement) *outputArray[count]).getsimpleType() << endl;
			}
			else
			{
				cout << "NULL" << endl;
			}
		}
	}
	else
	{
		cout << "NULL array" << endl;
	}

	// Delete contents of input array - NOTE: this will also be output array!
	for (count = 0 ; count < inputSize ; count ++ )
	{
		delete inputArray[count];
	}
	delete [] inputArray;

}

void testCopyingArrayOfComplexType()
{
	ComplexTypeWithSimpleElement_Array * array = new ComplexTypeWithSimpleElement_Array();
	int count = 0;
	int inputSize = 3;
	ComplexTypeWithSimpleElement** inputArray = new ComplexTypeWithSimpleElement*[inputSize];
	for (count = 0 ; count < inputSize ; count++)
	{
		inputArray[count] = new ComplexTypeWithSimpleElement();
		inputArray[count]->setsimpleType(count);
	}
	array->set(inputArray, inputSize);

	ComplexTypeWithSimpleElement_Array * copyArray = new ComplexTypeWithSimpleElement_Array();
	copyArray->clone(*array);
	copyArray->clear();
	delete (Axis_Array*) copyArray;
	delete array;

	// Delete contents of input array
	for (count = 0 ; count < inputSize ; count ++ )
	{
		delete inputArray[count];
	}
	delete [] inputArray;

}

