
/* This program will create 10 Threads and each thread will invoke ManyTypeRefRoot Service 
   @Author James
*/

#include "ManyTypeRefRoot.hpp"
#include <axis/AxisException.hpp>
#include <exception>
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
        const char* url="http://puppet.in.ibm.com:9060/ManyTypeRefRoot/services/sampleWS";
        if(p!=NULL)
             url=p;
		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
        try
        {
				sprintf(endpoint, "%s", url);
			    ManyTypeRefRoot *ws=new ManyTypeRefRoot(endpoint, APTHTTP1_1);
				Type1_Array input;
				Type1_Array result;
				Type1 types[10];
				Type1* current;
				int i;
				for ( i = 0; i < 10; i++ ) {
					current = new Type1 ();
					current->kind = "Test type";
					current->index = i;
					types[i] = *current;
				}

				input.m_Array = types;
				input.m_Size = 10;

				result = ws->getInput(input);
				Type1 *arrayResult = result.m_Array;
				//for ( i = 0; i < 10; i++, arrayResult++ ) {
					cout << arrayResult->index << " : " << arrayResult->kind << endl;
				//}

					bSuccess = true;

        }catch(AxisException& e)
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
            cout << "Unknown exception has occured" << endl;
        }
        catch(...)
        {
            cout << "Unknown exception has occured" << endl;
        }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
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
		 #ifdef WIN32
			/*Windows specific code comes here */
			HANDLE hThread[NUM_THREADS];
			for(i=0;i<NUM_THREADS;i++){
					DWORD dwThreadId;
					//LPVOID dwThrdParam = LPVOID(argv[1]);
					hThread[i] = CreateThread(
											NULL,                        // no security attributes
											0,                           // use default stack size
											ThreadFunc,                  // thread function
											LPVOID(argv[1]),             // argument to thread function
											0,   
										&dwThreadId);              // returns the thread identifier

			if (hThread[i] == NULL)
			{
			cout<<"Thread creation Failed";
			}
			}
			/* Waiting for threads to terminate */
			WaitForMultipleObjects(NUM_THREADS,hThread,true, INFINITE);
			for(i=0;i<NUM_THREADS;i++)
					CloseHandle( hThread[i] );

		#else	
			pthread_t thread[NUM_THREADS];
			pthread_attr_t attr;
			int rc, t, status = 0;
		//   Initialize and set thread detached attribute
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
			for (t = 0; t < NUM_THREADS; t++)
			{
			/*Creating threads */
				rc = pthread_create(&thread[t], &attr, ThreadFunc,(void *)argv[1]);
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
  }
  cout<<"----------------------------------TEST COMPLETE--------------------------------"<<endl;
}

