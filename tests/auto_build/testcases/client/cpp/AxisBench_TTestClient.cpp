
/* This program will create 10 Threads and each thread will invoke AxisBench Service 
   @Author James
*/

#include "AxisBench.hpp"
#include <axis/AxisException.hpp>
//#include <exception>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <axis/Axis.hpp>
/* Defining platform specific constants  */
#include <time.h>

#ifdef WIN32
        #include <windows.h>
		#include "sys/timeb.h"
        #define RETTYPE DWORD WINAPI
        #define ARGTYPE LPVOID
  // Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
  // Cannot print an __int64 number with cout without this overloading
 std::ostream& operator<<(std::ostream& os, __int64 i )
  {
    char buf[20];
    sprintf(buf,"%I64d", i );
    os << buf;
    return os;
  }

#else
        #include <pthread.h>
        #include <unistd.h>
        #include "sys/time.h"
        #define RETTYPE void*
        #define ARGTYPE void*
#endif


//#define MACRO_NUM_THREADS 10
//int NUM_THREADS = MACRO_NUM_THREADS;
#define NUM_THREADS 5


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE ThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        char *p=(char *)Param;
        char endpoint[256];
        const char* url="http://puppet.in.ibm.com:9060/Calculator/services/Calculator";
        AxisBench *ws;
		BenchDataType *input = NULL;
		BenchDataType *output = NULL;
		xsd__unsignedByte* buffer = NULL;
        if(p!=NULL)
             url=p;
        int iResult;
        try
        {
                sprintf(endpoint, "%s", url);
                ws = new AxisBench(endpoint, APTHTTP1_1);
                int request = 1;
      
				input = new BenchDataType();
				input->count = 100;
			      
			//    input->infos.m_Array = new BenchBasicDataType[input->count];
				BenchBasicDataType **	ppBBDT = (BenchBasicDataType **) new BenchBasicDataType *[input->count];

			#ifdef WIN32
				__int64					ll = 10000;
			#else
				long long				ll = 10000;
			#endif

				input->infos.m_Array = ppBBDT;

				input->infos.m_Size = input->count;
			      
				time_t tim;
				tim = 1100246323;
				struct tm *temp = gmtime(&tim);
				struct tm lt;
				memcpy(&lt, temp, sizeof(struct tm));

			      
				buffer = (xsd__unsignedByte*)calloc (1, input->count + 2);
				strcpy ( (char *)buffer, "A");

				for ( int i = 0; i < input->count ; i++ ) {
					BenchBasicDataType *type = new BenchBasicDataType();
					type->StringType = "StringType";
					type->IntegerType = 10*(i+1);
					type->DoubleType = 11.111 * (i+1);
					type->BooleanType = true_;
					type->DateTimeType = lt ;
					type->TimeType = lt ;
					type->DateType = lt ;
					type->IntType = (i+1);
					type->ByteType = '1';
					type->DecimalType = 10*(i+1);
					type->FloatType = (float)((float)(11*(i+1))/(float)2.0);
					type->LongType = ll;
					type->QNameType = "toto";
					type->ShortType = (i+1);
					type->Base64BinaryType.__size=i;
					type->Base64BinaryType.__ptr=buffer;
					type->HexBinary.__size=i;
					type->HexBinary.__ptr=buffer;

					if( i == 90)
					{
						*ppBBDT = type;
			//			*ppBBDT = NULL;
					}
					else
					{
						*ppBBDT = type;
					}

					ppBBDT++;

					if( ll == 0)
					{
						ll = 1;
					}
					else
					{
						ll += 10000;
					}

					strcat ( (char *)buffer, "A");
				}

				int t1,t2;
			#ifndef WIN32  
				struct timeval mstart;
				struct timeval mstop;
				gettimeofday( &mstart, NULL );
			#else
				struct timeb mstart;
				struct timeb mstop;
				ftime(&mstart);
			#endif

				for ( int ii = 0; ii < request ; ii++ ) {
					if (output) { // Samisa: memory management BP
						for (int i = 0; i < output->infos.m_Size; i++)
							delete (BenchBasicDataType*)(output->infos.m_Array[i]);
						delete output;
						output = NULL;
					}
				output = ws->doBenchRequest(input);
				}

				free(buffer);

			#ifndef WIN32
				gettimeofday( &mstop, NULL );
				t1 = mstart.tv_sec*1000 + mstart.tv_usec/1000;
				t2 = mstop.tv_sec*1000 + mstop.tv_usec/1000;
			#else
				ftime(&mstop);
				t1 = mstart.time*1000 + mstart.millitm;
				t2 = mstop.time*1000 + mstop.millitm;
			#endif

				int total = t2-t1;
			      
				if ( ws->getStatus() == AXIS_FAIL )
					cout << "Failed" << endl;
				else 
				{
   				char dateTime[50];
				int i = 0;
			    
					if( output->infos.m_Array[i] != (BenchBasicDataType *) 0xcdcdcdcd)
					{
						cout << " StringType " << output->infos.m_Array[i]->StringType << endl;
					}	
				 
					// returnValue=0;
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
  try
  {
	  delete ws; 
	  for (int i = 0; i < input->infos.m_Size; i++)
	      delete (BenchBasicDataType*)(input->infos.m_Array[i]);
	  delete input;
	  if (output)
	  {
	    for (int i = 0; i < output->infos.m_Size; i++)
	      delete (BenchBasicDataType*)(output->infos.m_Array[i]);
	    delete output;
	  }
  }
  catch(exception& exception)
  {
  	cout << "Exception on clean up: " << exception.what()<<endl;
  }
  catch(...)
  {
  	cout << "Unknown exception on clean up: " << endl;
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
  cout<<endl <<"----------------------------------TEST COMPLETE--------------------------------"<<endl;
}

