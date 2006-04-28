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


/* This program will create 10 Threads and each thread will invoke XSDTime Service 
   @Author James
*/

#include "XSDElement.hpp"
#include <axis/AxisException.hpp>
//#include <exception>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <axis/Axis.hpp>
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
#define NUM_THREADS 10


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE ThreadFunc(ARGTYPE Param)
{
    /*Type casting the url to char * */
    char *p=(char *)Param;
    char endpoint[256];
    const char* url="http://puppet.in.ibm.com:9060/XSDElement/services/XSDElementPort";
    if(p!=NULL)
         url=p;
    char dateTime[50];
    xsd__time timeResult;           // typedef of struct tm
    time_t timeToTest;
    timeToTest = 1100246323;
    xsd__date *temp = gmtime(&timeToTest);
    xsd__date testDate;
    memcpy(&testDate, temp, sizeof(xsd__date));

    bool bSuccess = false;
    int iRetryIterationCount = 3;

    do
    {
        try
        {
            sprintf(endpoint, "%s", url);
            XSDElement* ws = new XSDElement(endpoint);
            timeResult = ws->setGetTimeType(testDate);
            strftime(dateTime, 50, "%H:%M:%S", &timeResult);
            cout << "time=" << dateTime << endl;
            bSuccess = true;
            delete ws;
        }
        catch(AxisException& e)
        {
            bool bSilent = false;

            if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
            {
                if( iRetryIterationCount > 0)
                        bSilent = true;
            }
            else
                iRetryIterationCount = 0;

            if( !bSilent)
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
        
    iRetryIterationCount--;
    } 
    while( iRetryIterationCount > 0 && !bSuccess);
    
#ifndef WIN32
            pthread_exit(0);
#endif
    
    return 0;
}




int main(int argc, char *argv[])
{
    Axis::initialize(false);
    try
    {
        int i;
#ifdef WIN32
        /*Windows specific code comes here */
        HANDLE hThread[NUM_THREADS];
        for(i=0;i<NUM_THREADS;i++)
        {
            DWORD dwThreadId;
            //LPVOID dwThrdParam = LPVOID(argv[1]);
            hThread[i] = CreateThread(NULL,            // no security attributes
                                      0,               // use default stack size
                                      ThreadFunc,      // thread function
                                      LPVOID(argv[1]), // argument to thread function
                                      0,   
                                      &dwThreadId);    // returns the thread identifier

            if (hThread[i] == NULL)
               cout<<"Thread creation Failed";
        }
        
        /* Waiting for threads to terminate */
        WaitForMultipleObjects(NUM_THREADS,hThread,true, INFINITE);
        for (i=0;i<NUM_THREADS;i++)
           CloseHandle( hThread[i] );
#else   
            pthread_t thread[NUM_THREADS];
            pthread_attr_t attr;
            int rc, t;
            void *status;
            //   Initialize and set thread detached attribute
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
            for (t = 0; t < NUM_THREADS; t++)
            {
                rc = pthread_create(&thread[t], &attr, ThreadFunc,(void *)argv[1]);
                if (rc)
                        cout<<"Thread Creation Failed";
            }
                    
            //Free attribute and wait for the other threads
            pthread_attr_destroy(&attr);
            
            /* Wait for the threads to terminate  */
            for(t=0;t<NUM_THREADS;t++)
            {
                rc = pthread_join(thread[t], &status);
                if (rc)
                    cout<<"ERROR from pthread_join()"<<endl;
            }
#endif
  }
  catch(exception &e)
  {
           cout<< e.what();
  }
  
  cout<<endl <<"----------------------------------TEST COMPLETE--------------------------------"<<endl;
}

