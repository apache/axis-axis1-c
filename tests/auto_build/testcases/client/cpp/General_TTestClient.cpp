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


/* This program will create 10 Threads and each thread will invoke different operations of Calculator Service
   @Author James
*/

#include "Calculator.hpp"
#include <axis/AxisException.hpp>
//#include <exception>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
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

/* Defining a structure to pass arguments to entry point function */

struct ARG_LIST{
        char url[200];
        char op[4];
};

//#define MACRO_NUM_THREADS 10
//int NUM_THREADS = MACRO_NUM_THREADS;
#define NUM_THREADS 10


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE ThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        ARG_LIST *p=(ARG_LIST *)Param;
        char endpoint[256];
        const char* url="http://puppet.in.ibm.com:9060/Calculator/services/Calculator";
                char *op;
                if(p!=NULL){
             url=p->url;
                         op=p->op;
                }
    
        try
                {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);                                
                                if(strcmp(op,"add")==0){
                  if(ws.add(3,2)==5)
                                          cout << "successful" << endl;
                                }else if(strcmp(op,"mul")==0){
                                   if(ws.mul(3,2)==6)
                                           cout << "successful" << endl;
                                }else if(strcmp(op,"sub")==0){
                                   if(ws.sub(3,2)==1)
                                           cout << "successful" << endl;                                                        
                        }else if(strcmp(op,"div")==0){
                                   if(ws.div(4,2)==2)
                                           cout << "successful" << endl;
                           }            

                }catch(AxisException& e)
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
                #ifndef WIN32
                        pthread_exit(0);
                #endif
        return 0;
}




int main(int argc, char *argv[])
{
    Axis::initialize(false);
        try{
                 int i;
                 ARG_LIST a;
                 /* Copying url to argument list */
                 strcpy(a.url,argv[1]);
                 char actions[4][4]={"add","sub","div","mul"};
                 #ifdef WIN32
                        /*Windows specific code comes here */
                        HANDLE hThread[NUM_THREADS];
                        for(i=0;i<NUM_THREADS;i++){
                                   /* Copying operation name to argument list */
                                        strcpy(a.op,actions[i%4]);
                                        DWORD dwThreadId;
                                        //LPVOID dwThrdParam = LPVOID(argv[1]);
                                        hThread[i] = CreateThread(
                                                                                        NULL,                        // no security attributes
                                                                                        0,                           // use default stack size
                                                                                        ThreadFunc,                  // thread function
                                                                                        LPVOID(&a),               //LPVOID(argv[1]),             // argument to thread function
                                                                                        0,   
                                                                                &dwThreadId);              // returns the thread identifier

                        if (hThread[i] == NULL)
                        {
                        cout<<"Thread creation Failed";
                        }
                        Sleep(500);
                        }
                        /* Waiting for threads to terminate */
                        WaitForMultipleObjects(NUM_THREADS,hThread,true, INFINITE);
                        for(i=0;i<NUM_THREADS;i++)
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
                                 /* Copying operation name to argument list */
                                strcpy(a.op,actions[t%4]);
                                /*Creating threads */
                                rc = pthread_create(&thread[t], &attr, ThreadFunc,(void *)(&a));
                                if (rc)
                                {
                                        cout<<"Thread Creation Failed";
                                }
                                sleep(1);
                        }
                //Free attribute and wait for the other threads
                pthread_attr_destroy(&attr);
                /* Wait for the threads to terminate  */
                for(t=0;t<NUM_THREADS;t++){                     
                        rc = pthread_join(thread[t], &status);
                                if (rc)
                                {
                                        cout<<"ERROR from pthread_join()"<<endl;
                                }
                }
        #endif
  }catch(exception &e){
           cout<< e.what();
  }
  cout<<endl <<"----------------------------------TEST COMPLETE--------------------------------"<<endl;
}

