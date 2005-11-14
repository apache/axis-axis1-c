// Copyright 2003-2004 The Apache Software Foundation.
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


/* This program will create 10 Threads and each thread will invoke different Service 
   @Author James
*/

#include "SimpleTypeArrayWS.hpp"
#include "MathOps.hpp"
#include "Calculator.hpp"
#include "ArrayTestPortType.hpp"
#include <axis/AxisException.hpp>
//#include <exception>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <axis/Axis.hpp>
#include <string.h>
/* Defining platform specific constants  */
#ifdef WIN32
#include <windows.h>
#define RETTYPE DWORD WINAPI
#define ARGTYPE LPVOID
#else
#include <pthread.h>
#include <unistd.h>
#define RETTYPE void*
#define ARGTYPE void*
#endif


//#define MACRO_NUM_THREADS 10
//int NUM_THREADS = MACRO_NUM_THREADS;
#define NUM_TESTS		4
#define NUM_THREADS		10
#define ARRAYSIZE		2
#define ARRAYSIZE_STT	100


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE calThreadFunc( ARGTYPE Param)
{
// Debug v Must be removed
// printf( "> calThreadFunc( %s)\n", (char *) Param);
// Debug ^ Must be removed

	/*Type casting the url to char * */
	char *	p = (char *) Param;
	char	endpoint[256];
	char *	url = "http://localhost:9060/Calculator/services/Calculator";

	if( p != NULL)
	{
		url = p;
	}

	int	iResult;

	try
	{
		sprintf( endpoint, "%s", url);

		Calculator	ws( endpoint);

// Debug v Must be removed
// printf( "- Created Calculator web service\n");
// Debug ^ Must be removed

		iResult = ws.add( 3,2);
	
		if( iResult == 5)
		{
			cout << "successful ";
		}
	}
	catch( AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch( exception& e)
	{
		e = e;

		cout << "Unknown exception has occured" << endl;
	}
	catch( ...)
	{
		cout << "Unknown exception has occured" << endl;
	}

	#ifndef WIN32
	pthread_exit( 0);
	#endif

// Debug v Must be removed
// printf( "< calThreadFunc\n");
// Debug ^ Must be removed
	return 0;
}

RETTYPE arrayDocThreadFunc( ARGTYPE Param)
{
// Debug v Must be removed
// printf( "> arrayDocThreadFunc( %s)\n", (char *) Param);
// Debug ^ Must be removed

	/*Type casting the url to char * */
	char *	p = (char *) Param;
	char	endpoint[256];
	int		x;
	char *	url = "http://localhost:9060/SimpleArray/services/arrayTest";

	if( p != NULL)
	{
		url = p;
	}

	try
	{
		sprintf( endpoint, "%s", url);

		ArrayTestPortType	ws( endpoint);

// Debug v Must be removed
// printf( "- Created ArrayTestPortType web service\n");
// Debug ^ Must be removed

		//testing echoIntArray
		intArrayType arrin;
		xsd__int_Array arrayIn;
		xsd__int ** array = new xsd__int*[ARRAYSIZE];

		//arrin.intItem.m_Size = ARRAYSIZE;			 // Set the array size.
		//arrin.intItem.m_Array = new int*[ARRAYSIZE]; // Create an array of integer pointers.
/*
		int * intArray = new int[ARRAYSIZE];		 // Create a pointer to an integer array.

		// Fill the array with values from 0 to ARRAYSIZE and set the integer pointer to the
		// pointer of the integer array.
		for( x = 0; x < ARRAYSIZE; x++)
		{
			intArray[x] = x;
			arrin.intItem.m_Array[x] = &intArray[x];
		}
*/

		// Fill the array with values from 0 to ARRAYSIZE and set the integer pointer to the
		// pointer of the integer array.
		for( int y = 0; y < ARRAYSIZE; y++)
		{
			//int * intArray = new int[ARRAYSIZE];		 // Create a pointer to an integer array.

			for( x = 0; x < ARRAYSIZE; x++)
			{
				array[x] =new xsd__int(x);
			}

			//arrin.intItem.m_Array[y] = intArray;
		}
		arrayIn.set(array,ARRAYSIZE);
		arrin.setintItem(&arrayIn);
/**/    int outputSize =0;
		if( ws.echoIntArray( &arrin)->intItem->get(outputSize) != NULL)
		{
			cout << "successful ";
		}
		else
		{
			cout << "failed " << endl;
		}
		// Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;

	}
	catch( AxisException& e)
	{
		e = e;

		cout << "Exception : " << e.what() << endl;
	}
	catch( exception& e)
	{
		e = e;

		cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unknown exception has occured" << endl;
	}

	#ifndef WIN32
	pthread_exit( 0);
	#endif

// Debug v Must be removed
// printf( "< arrayDocThreadFunc\n");
// Debug ^ Must be removed
	return 0;
}

RETTYPE mathOpsThreadFunc( ARGTYPE Param)
{
// Debug v Must be removed
// printf( "> mathOpsThreadFunc( %s)\n", (char *) Param);
// Debug ^ Must be removed

	/*Type casting the url to char * */
	char *	p = (char *) Param;
	char	endpoint[256];
	char *	url = "http://localhost:9060/MathOps/services/MathOps";

	if( p != NULL)
	{
		url = p;
	}

	const char *	op = 0;
	const char *	p1 = 0;
	const char *	p2 = 0;
	int				i1 = 0;
	int				i2 = 0;
	int				iResult;

	try
	{
		sprintf( endpoint, "%s", url);

		MathOps	ws( endpoint);

// Debug v Must be removed
// printf( "- Created MathOps web service\n");
// Debug ^ Must be removed

		op = "div";	// Operation name
		i1 = 10;	// First parameter
		i2 = 5;		// Second parameter

		if( strcmp( op, "div") == 0)
		{
			iResult = ws.div( i1, i2);

			if( iResult == 2)
			{
				cout << "successful ";
			}
		}
		else 
		{
			cout << "Invalid operation "<< op << endl << endl;
		}
	}
	catch( AxisException& e)
	{
		e = e;

		cout << "Exception : " << e.what() << endl;
	}
	catch( exception& e)
	{
		e = e;

		cout << "Unknown exception has occured" << endl;
	}
	catch( ...)
	{
		cout << "Unknown exception has occured" << endl;
	}

	#ifndef WIN32
	pthread_exit(0);
	#endif

// Debug v Must be removed
// printf( "< mathOpsThreadFunc\n");
// Debug ^ Must be removed
	return 0;
}


RETTYPE simpleTypeThreadFunc( ARGTYPE Param)
{
// Debug v Must be removed
// printf( "> simpleTypeThreadFunc( %s)\n", (char *) Param);
// Debug ^ Must be removed

	/*Type casting the url to char * */
	char *	p = (char *) Param;
	char	endpoint[256];
	char *	url = "http://localhost:9060/SimpleTypeArray/services/sampleWS";

	if( p != NULL)
	{
		url = p;
	}

	try
	{
		SimpleTypeArrayWS *	ws;

// Debug v Must be removed
// printf( "- Created SimpleTypeArrayWS web service\n");
// Debug ^ Must be removed

		sprintf( endpoint, "%s", url);

		ws = new SimpleTypeArrayWS( endpoint, APTHTTP1_1);

		Type *			input;
		Type *			output;
		xsd__int_Array	array_input;
		int				i;
        xsd__int ** array = new xsd__int*[ARRAYSIZE_STT];
		//array_input.m_Array = new int*[ARRAYSIZE_STT];
		//array_input.m_Size  = ARRAYSIZE_STT;

		for( int j = 0; j < ARRAYSIZE_STT; j++)
		{
			//int * piEntries = new int[ARRAYSIZE_STT];

			for( i = 0; i < ARRAYSIZE_STT; i++)
			{
				array[i] = new xsd__int(i);
			}

			//array_input.m_Array[j] = piEntries;
		}
		array_input.set(array,ARRAYSIZE_STT);
		input = new Type();
		input->setitem(&array_input);

		output = ws->getInput( input);

		i = 0;
        int outputSize = 0;
		if( *(output->item->get(outputSize)[0]) == 0)
		{
			cout << "successful ";				
		}
		// Clear up input array        
        for (int deleteIndex = 0 ; deleteIndex < ARRAYSIZE_STT ; deleteIndex++ )
        {
            delete array[deleteIndex];
        }
        delete [] array;

		delete ws;
	}
	catch( AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch(exception& e)
	{
		e = e;

		cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
		cout << "Unknown exception has occured" << endl;
	}

	#ifndef WIN32
	pthread_exit(0);
	#endif

// Debug v Must be removed
// printf( "< simpleTypeThreadFunc()\n");
// Debug ^ Must be removed
	return 0;
}

//--------------------------------------------------------------------------------------

int main( int argc, char * argv[])
{
	Axis::initialize( false);

	try
	{
		int		i;	
		char *	endpoint_list[NUM_TESTS];
		int		count = 0;

		/* Extracting endpoints for 4 stubs.*/				
		if( argc >= 7)
		{
			for( i = 0; i < NUM_TESTS; i++)
			{
				char *	temp = argv[3 + i];

				count = 0;
				endpoint_list[i] = new char[100];

				for( int j = 0; temp[j] != '\0'; j++)
				{
					if( temp[j] == '/')
					{
						count++;
					}

					if( count == (NUM_TESTS - 1))
					{
						sprintf( endpoint_list[i], "%s%s:%s%s", "http://", argv[1], argv[2], &temp[j]);
						break;
					}
				}
			}
		}
		else
		{
			cout << "Endpoint details not set correctly" << endl;

			exit(0);
		}

		 #ifdef WIN32
		/*Windows specific code comes here */
		   
		HANDLE	hThread[NUM_THREADS] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
		DWORD	dwThreadId;
		DWORD	(_stdcall *fnptr[NUM_TESTS]) (LPVOID p) = {calThreadFunc,
														   arrayDocThreadFunc,
														   mathOpsThreadFunc,
														   simpleTypeThreadFunc};
		char *	pszThreadName[] = {"Calc", "ArrayDoc", "MathOps", "SimpleType"};

		for( i = 0; i < NUM_THREADS; i++)
		{
			int	index = i % NUM_TESTS;

			hThread[i] = CreateThread( NULL,							// no security attributes
									   0,								// use default stack size
									   fnptr[index],					// thread function
									   LPVOID( endpoint_list[index]),	// argument to thread function
									   0,   
									   &dwThreadId);					// returns the thread identifier
// Debug v Must be removed
// printf( "Starting thread %d. %s with param %s. Thread handle %d\n", i, pszThreadName[index], endpoint_list[index], hThread[i]);
// Debug ^ Must be removed

			if( hThread[i] == NULL)
			{
				cout<<"Thread creation Failed";
			}
		}

		/* Waiting for threads to terminate */
		WaitForMultipleObjects( NUM_THREADS, hThread, true, INFINITE);

		for( i = 0; i < NUM_THREADS; i++)
		{
			DWORD	dwExitCode;

			GetExitCodeThread( hThread[i], &dwExitCode);

			if( STILL_ACTIVE == dwExitCode)
			{
				cout<<"error - threads still active"<<endl;
			}
			else
			{
				if( hThread[i])
				{
					CloseHandle( hThread[i]);
				}
			}
		}

		#else
		    void *(*fnptr[5])(void * p)={calThreadFunc,arrayDocThreadFunc,mathOpsThreadFunc,simpleTypeThreadFunc};
			pthread_t thread[NUM_THREADS];
			pthread_attr_t attr;
			int rc, t, status = 0;
		//   Initialize and set thread detached attribute
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
			for (t = 0; t < NUM_THREADS; t++)
			{
			/*Creating threads */
				rc = pthread_create(&thread[t], &attr, fnptr[t%4],(void *)endpoint_list[t%4]);
				if (rc)
				{
					cout<<"Thread Creation Failed";
				}
			}
		//Free attribute and wait for the other threads
		pthread_attr_destroy(&attr);
		/* Wait for the threads to terminate  */
		for(t=0;t<NUM_THREADS;t++){
			rc = pthread_join(thread[t], (void **)&status);
				if (rc)
				{
					cout<<"ERROR from pthread_join()"<<endl;
				}
		}
	#endif
  }catch(exception &e){
           cout<< e.what();
  }catch(...){
	  cout<<" Endpoints are not set correctly. There should be 4 endpoint elements in test.xml file" << endl;
  }	
  cout<<endl <<"----------------------------------TEST COMPLETE--------------------------------"<<endl;
}

