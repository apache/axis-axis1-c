#include "AxisBench.h"
#include <time.h>

#ifndef WIN32
  #include "sys/time.h"
#else
  #include "sys/timeb.h"
#endif

static bool verbose = false;
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);

int main(int argc, char* argv[])
{ 
  AxisBench *ws;
  BenchDataType *input;
  BenchDataType *output;
  xsd__unsignedByte* buffer;
  int request = 1;

  char *endpoint = "http://localhost:9080/AxisBench/services/AxisBenchSoapImpl";
  bool endpoint_set = false;

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

  try {
    if(endpoint_set)
      ws = new AxisBench(endpoint, APTHTTP);
    else
      ws = new AxisBench();
  } catch (AxisException &e) {
    fprintf(stderr, "%s\n", e.what());
    return 1;
  }
  
  input = new BenchDataType();
  input->count = 100;
  
  /* Use hard coded values for ease of setting non-default URI
  if ( argc > 1 )
    input->count = atoi(argv[1]);
  
  if ( argc > 2 )
    request = atoi(argv[2]);
  */
  
  input->infos.m_Array = new BenchBasicDataType[input->count];
  input->infos.m_Size = input->count;
  
  time_t tim;
  tim = 1079010407;
  tm* lt = gmtime(&tim);
  
  buffer = (xsd__unsignedByte*)malloc ( input->count + 1 );
  memset (buffer,0,input->count + 1);
  
  for ( int i = 0; i < input->count ; i++ ) {
    BenchBasicDataType *type = new BenchBasicDataType();
    type->StringType = "StringType";
    type->IntegerType = i;
    type->DoubleType = 1.0;
    type->BooleanType = true_;
    type->DateTimeType = *lt ;
    type->TimeType = *lt ;
    type->DateType = *lt ;
    
    type->IntType = i;
    type->ByteType = '1';
    type->DecimalType = 10;
    type->FloatType = i/2;
    type->LongType = i*100;
    type->QNameType = "toto";
    type->ShortType = 1;
    /*
    type->Base64BinaryType.__size=i;
    type->Base64BinaryType.__ptr=buffer;
    type->HexBinary.__size=i;
    type->HexBinary.__ptr=buffer;
    strcat ( (char *)buffer, "A");
    */
    input->infos.m_Array[i] = *type;
    
  }
  
  free(buffer);

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
    output = ws->doBenchRequest(input);
  }


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
    printf ("Failed\n");
  else 
  {
    int i = 0;
    if ( argc > 1 )
      i = output->count -1;
    printf ("Count : %d \n", output->count);
    for ( ; i < output->count ; i++ ) {
      printf (" ----------------------------------------------\n");
      printf (" StringType %s \n", output->infos.m_Array[i].StringType);
      printf (" IntegerType %d \n", output->infos.m_Array[i].IntegerType);
      printf (" DoubleType %f \n", output->infos.m_Array[i].DoubleType);
      printf (" BooleanType %d \n", output->infos.m_Array[i].BooleanType);
      printf (" DateTimeType %s \n", asctime(&output->infos.m_Array[i].DateTimeType));
      printf (" DateType %s \n", asctime(&output->infos.m_Array[i].DateType));
      printf (" TimeType %s \n", asctime(&output->infos.m_Array[i].TimeType));
      printf (" ByteType %d \n", output->infos.m_Array[i].ByteType);
      printf (" DecimalType %f \n", output->infos.m_Array[i].DecimalType);
      printf (" FloatType %f \n", output->infos.m_Array[i].FloatType);
      printf (" LongType %ld \n", output->infos.m_Array[i].LongType);
      printf (" QNameType %s \n", output->infos.m_Array[i].QNameType);
      printf (" ShortType %d \n", output->infos.m_Array[i].ShortType);
      printf (" Base64BinaryType %d \n", output->infos.m_Array[i].Base64BinaryType.__size);
      printf (" Base64BinaryType %s \n", output->infos.m_Array[i].Base64BinaryType.__ptr);
      printf (" HexBinaryType %d \n", output->infos.m_Array[i].HexBinary.__size);
      printf (" HexBinaryType %s \n", output->infos.m_Array[i].HexBinary.__ptr);
    }
  }

  if(verbose) {
    printf (" ----------------------------------------------\n");
    printf ("%d input paramters, and %d requests\n", input->count, request);
    printf ("Total time = %d ms\n",  total );
    printf ("Average time = %d ms\n", total/request);
  }

  return 0;
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
