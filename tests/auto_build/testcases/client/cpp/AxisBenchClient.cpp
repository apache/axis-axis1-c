#include "AxisBench.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

#ifndef WIN32
  #include "sys/time.h"
#else
  #include "sys/timeb.h"

  // Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
  // Cannot print an __int64 number with cout without this overloading
  std::ostream& operator<<(std::ostream& os, __int64 i )
  {
    char buf[20];
    sprintf(buf,"%I64d", i );
    os << buf;
    return os;
  }

#endif

static bool verbose = false;
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);
void setLogOptions(const char *output_filename);

// If we re-direct cout it will be to this ofstream
ofstream output_file;

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/AxisBench/services/AxisBenchSoapImpl"

int main(int argc, char* argv[])
{ 
  AxisBench *ws;

  BenchDataType *input = NULL;
  BenchDataType *output = NULL;
  xsd__unsignedByte* buffer = NULL;

  char *endpoint = WSDL_DEFAULT_ENDPOINT;
  bool endpoint_set = false;
  int returnValue = 1; // Assume Failure

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

  try {
    if(endpoint_set) {
      ws = new AxisBench(endpoint, APTHTTP1_1);
      free(endpoint);
      endpoint_set = false;
    } else
      ws = new AxisBench();

    
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
    tm* lt = gmtime(&tim);
      
    buffer = (xsd__unsignedByte*)calloc (1, input->count + 2);
    strcpy ( (char *)buffer, "A");

    for ( int i = 0; i < input->count ; i++ ) {
        BenchBasicDataType *type = new BenchBasicDataType();
        type->StringType = "StringType";
        type->IntegerType = 10*(i+1);
        type->DoubleType = 11.111 * (i+1);
        type->BooleanType = true_;
        type->DateTimeType = *lt ;
        type->TimeType = *lt ;
        type->DateType = *lt ;
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
      if ( argc > 1 )
          i = output->count -1;

      cout << "Input Count : " << input->count << endl;
      cout << "Count : " << output->count << endl;
      for ( ; i < output->count ; i++ ) 
      {
		  if( output->infos.m_Array[i] != (BenchBasicDataType *) 0xcdcdcdcd)
		  {
			  cout << " ----------------------------------------------" << endl;
			  cout << " StringType " << output->infos.m_Array[i]->StringType << endl;
			  cout << " IntType " << output->infos.m_Array[i]->IntType << endl;
			  cout << " IntegerType " << output->infos.m_Array[i]->IntegerType << endl;
			  cout << " DoubleType " << output->infos.m_Array[i]->DoubleType << endl;
			  cout << " BooleanType " << output->infos.m_Array[i]->BooleanType << endl;
  			  strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &output->infos.m_Array[i]->DateTimeType);
			  cout << " DateTimeType " << dateTime << endl;
  			  strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &output->infos.m_Array[i]->DateType);
			  cout << " DateType " << dateTime << endl;
  			  strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &output->infos.m_Array[i]->TimeType);
			  cout << " TimeType " << dateTime << endl;
			  cout << " ByteType " << output->infos.m_Array[i]->ByteType << endl;
			  cout << " DecimalType " << output->infos.m_Array[i]->DecimalType << endl;
			  cout << " FloatType " << output->infos.m_Array[i]->FloatType << endl;
			  cout << " LongType " << output->infos.m_Array[i]->LongType << endl;
			  cout << " QNameType " << output->infos.m_Array[i]->QNameType << endl;
			  cout << " ShortType " << output->infos.m_Array[i]->ShortType << endl;

			  cout << " Base64BinaryType " << output->infos.m_Array[i]->Base64BinaryType.__size << endl;
			  if( output->infos.m_Array[i]->Base64BinaryType.__size > 0)
			  {
				  cout << " Base64BinaryType " << output->infos.m_Array[i]->Base64BinaryType.__ptr << endl;
			  }

			  cout << " HexBinaryType " << output->infos.m_Array[i]->HexBinary.__size << endl;
			  if( output->infos.m_Array[i]->HexBinary.__size > 0)
			  {
				cout << " HexBinaryType " << output->infos.m_Array[i]->HexBinary.__ptr << endl;
			  }
		  }
		  returnValue=0;
      }
    }

    if(verbose) {
        cout << " ----------------------------------------------" << endl;
        cout << input->count << " input paramters, and " << request << " requests" << endl;
        cout << "Total time = " << total << " ms" << endl;
        cout << "Average time = " << total/request << " ms" << endl;
    }
  } catch(AxisException &e) {
    cerr << e.what() << endl;
    if(endpoint_set)
      free(endpoint);
  } catch(...) {
    cerr << "Unknown Exception occured." << endl;
    if(endpoint_set)
      free(endpoint);
  }

  // Samisa: make sure we clean up memory allocated
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
  cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
  return returnValue;

}

/* Spin through args list and check for -e -p and -s options.
   Option values are expected to follow the option letter as the next
   argument.
 
   These options and values are removed from the arg list.
   If both -e and -s and or -p, then -e takes priority
*/
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint) {

    // We need at least 2 extra arg after program name
    if(*argc < 3)
        return false;

    char *server = "localhost";
    int  port = 80;
    bool ep_set = false;
    bool server_set = false;
    bool port_set = false;

    for(int i=1; i<*argc; i++) {
        if(*argv[i] == '-') {
            switch(*(argv[i]+1)) {
            case 'e':
                *endpoint = strdup(argv[i+1]);
                ep_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            case 's':
                server = strdup(argv[i+1]);
                server_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            case 'p':
                port = atoi(argv[i+1]);
                if(port >80) port_set = true;
                shift_args(i, argc, argv);
                i--;
                break;
            case 'o':
                setLogOptions(argv[i+1]);
                shift_args(i, argc, argv);
                i--;
                break;
            case 'v':
				verbose=true;
                break;
            default:
                break;
            }
        }
    }

    // use the supplied server and/or port to build the endpoint
    if(ep_set == false && (server_set || port_set)) {
        // Set p to the location of the first '/' after the http:// (7 chars)
        // e.g. from http://localhost:80/axis/base gets /axis/base
        char *ep_context = strpbrk(&(*endpoint)[7], "/");

        // http://:/ is 9 characters + terminating NULL character so add 10.
        // Allow space for port number upto 999999 6 chars
        *endpoint = (char *)calloc(1, 10 + strlen(ep_context) + strlen(server) + 6);
        sprintf(*endpoint, "http://%s:%d/%s", server, port, ep_context+1);
        if(server_set) free(server);
        ep_set = true;
    }

    return ep_set;
}

void shift_args(int i, int *argc, char *argv[]) {
    for(int j=i, k=i+2; j<*(argc)-2; j++, k++)
        argv[j]=argv[k];
    *argc-=2;
}

void setLogOptions(const char *output_filename) {
    output_file.open(output_filename, ios::out);
    if(output_file.is_open()) {
        cout.rdbuf( output_file.rdbuf() );
    }
}

