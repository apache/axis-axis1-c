
/* This program will create 10 Threads and each thread will invoke FaultMapping Service 
   @Author James
*/

#include "MathOps.hpp"
#include <axis/AxisException.hpp>
//#include <exception>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <axis/Axis.hpp>
#include <signal.h>

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


void sig_handler(int);


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE ThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
    char endpoint[256];
	const char* server="localhost";
	const char* url="http://localhost:80/axis/MathOps";
	const char* port="80";
	const char* op = 0;
	const char* p1 = 0;
	const char* p2 = 0;
	int i1=0, i2=0;
	int iResult;
	char* pcDetail;

	signal(SIGILL, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGSEGV, sig_handler);
	//signal(SIGQUIT, sig_handler);
	//signal(SIGBUS, sig_handler);
	signal(SIGFPE, sig_handler);

	url = (char *)Param;

	sprintf(endpoint, "%s", url);

	op = "div";

	if (strcmp(op, "div") == 0)
	{
	    for(int i = 0; i < 4; i++)
	    {
           // cout << i << endl;

			switch(i)
			{
				case 0: i1 = 10; i2 = 5; break;
				case 1: i1 = 10; i2 = 0; break;
				case 2: i1 = 1000; i2 = 5; break;
				case 3: i1 = 10; i2 = -5; break;
			}
			try
			{
				MathOps ws(endpoint);
				//cout << "Trying to " << op << " " << i1 << " by " << i2 << endl;
				iResult = ws.div(i1, i2);		
				//cout << "Result is " << iResult << endl;
			}
			catch(DivByZeroStruct& dbzs)
			{
				/*cout << "DivByZeroStruct Fault: \"" 
					<< dbzs.varString 
					<< "\", " 
					<< dbzs.varInt 
					<< ", " 
					<< dbzs.varFloat 
					<< endl; */
			}
			catch(SpecialDetailStruct& sds)
			{
				/*cout << "SpecialDetailStruct Fault: \"" 
					<< sds.varString 
					<< "\"" 
					<< endl;*/
			}
			catch(OutOfBoundStruct& oobs)
			{
				/*cout << "OutOfBoundStruct Fault: \"" 
					<< oobs.varString 
					<< "\", " 
					<< oobs.varInt 
					<< ", \"" 
					<< oobs.specialDetail->varString 
					<< "\"" 
					<< endl;*/
				  if(i==3)
					  cout<<"Success"<<endl;
			}
			catch(SoapFaultException& sfe)
			{
				cout << "SoapFaultException: " << sfe.what() << endl;
			}
			catch(AxisException& e)
			{
                cout << "AxisException: " << e.what() << endl;
			}
			catch(exception& e)
			{
                cout << "Unknown Exception: " << endl;
			}
			catch(...)
			{
                cout << "Unspecified Exception: " << endl;
			}
	    }
	}
	else 
	{
		cout << "Invalid operation " << op << endl;
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

void sig_handler(int sig) {
	signal(sig, sig_handler);
	cout << "SIGNAL RECEIVED " << sig << endl;
	exit(1);
}


