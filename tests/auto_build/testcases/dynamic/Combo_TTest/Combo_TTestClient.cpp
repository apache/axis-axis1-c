
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
#define NUM_THREADS 10
#define ARRAYSIZE 2


/* In windows the entry point function return type is DWORD WINAPI
   In linux it is void *                                          */
RETTYPE calThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        char *p=(char *)Param;
        char endpoint[256];
        const char* url="http://localhost:9060/Calculator/services/Calculator";
        if(p!=NULL)
             url=p;
        int iResult;
        try
        {
                sprintf(endpoint, "%s", url);
                Calculator ws(endpoint);
                iResult = ws.add(3,2);
				if(iResult==5)					
                  cout << "successful ";

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
                #ifndef WIN32
                        pthread_exit(0);
                #endif
        return 0;
}



RETTYPE arrayDocThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        char *p=(char *)Param;
        char endpoint[256];
		int x;
        const char* url="http://localhost:9060/SimpleArray/services/arrayTest";
		if(p!=NULL)
             url=p;
        try
        {
				sprintf(endpoint, "%s", url);
				ArrayTestPortType ws(endpoint);
				//testing echoIntArray
				IntArrayType arrin;
				arrin.intItem.m_Array = new int*[ARRAYSIZE];
				int * intArray = new int[ARRAYSIZE];
				arrin.intItem.m_Size = ARRAYSIZE;
				for (x=0;x<ARRAYSIZE;x++)
				{
					intArray[x] = x;
					arrin.intItem.m_Array[x] = &intArray[x];
				}
				if (ws.echoIntArray(&arrin)->intItem.m_Array != NULL)
					cout << "successful ";
				else
					cout << "failed "<<endl;		
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

RETTYPE mathOpsThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        char *p=(char *)Param;
        char endpoint[256];
        const char* url="http://localhost:9060/MathOps/services/MathOps";
        if(p!=NULL)
             url=p;
		const char* op = 0;
		const char* p1 = 0;
		const char* p2 = 0;
		int i1=0, i2=0;
		int iResult;
        try
        {
                sprintf(endpoint, "%s", url);
				MathOps ws(endpoint);
				op = "div";/*Operation name*/
				i1 = 10;/*First parameter*/
				i2 = 5;/*Second parameter*/

				if (strcmp(op, "div") == 0)
				{
					iResult = ws.div(i1, i2);		
					if(iResult==2)
						cout << "successful ";
				}
				else 
				{
					cout << "Invalid operation "<< op<< endl<<endl;
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


RETTYPE simpleTypeThreadFunc(ARGTYPE Param)
{
        /*Type casting the url to char * */
        char *p=(char *)Param;
        char endpoint[256];
        const char* url="http://localhost:9060/SimpleTypeArray/services/sampleWS";
        if(p!=NULL)
             url=p;
          SimpleTypeArrayWS *ws;
        try
        {
                sprintf(endpoint, "%s", url);
                ws=new SimpleTypeArrayWS(endpoint, APTHTTP1_1);
                Type *input;
				Type *output;
				xsd__int_Array array_input;
				int entries[100];
				int i;

				array_input.m_Array = new int*[100];
				array_input.m_Size  = 100;

				 for ( i = 0; i < 100; i++ ) {
					entries[i] = i;
				 array_input.m_Array[i] = &entries[i];
				}

				 input = new Type();
				input->item = array_input;

			

				output = ws->getInput(input);
				i=0;
				if(*(output->item.m_Array[i])== 0)
					cout << "successful ";				
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
		 char *endpoint_list[4];
		 int count=0;
		 /* Extracting endpoints for 4 stubs.*/				
		
		 if(argc>=7){
			 for(i=0;i<4;i++){
				char *temp=argv[3+i];
				count=0;
				endpoint_list[i]=new char[100];
				for(int j=0;temp[j]!='\0';j++){
					if(temp[j]=='/')
						count++;
					if(count==3){
						sprintf(endpoint_list[i],"%s%s:%s%s","http://",argv[1],argv[2],&temp[j]);
						break;
					}
				}
				
			 }		
		 }else{
			 cout<<"Endpoint details not set correctly"<<endl;
			 exit(0);
		 }

		 #ifdef WIN32
			/*Windows specific code comes here */
		   
			HANDLE hThread[NUM_THREADS];
			DWORD dwThreadId;
			DWORD (_stdcall *fnptr[5])(LPVOID p)={calThreadFunc,arrayDocThreadFunc,mathOpsThreadFunc,simpleTypeThreadFunc};
			//char endpoint[50];
			for(i=0;i<NUM_THREADS;i++){				    
					hThread[i] = CreateThread(
											NULL,                        // no security attributes
											0,                           // use default stack size
											fnptr[i%4],                 // thread function
											LPVOID(endpoint_list[i%4]),             // argument to thread function
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

