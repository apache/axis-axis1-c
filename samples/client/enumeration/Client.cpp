
#include "EnumerationWS.hpp" 
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/enumeration"

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);
void setLogOptions(const char *output_filename);

// If we re-direct cout it will be to this ofstream
ofstream output_file;

int main(int argc, char* argv[])
{
  EnumerationWS *ws;

  char *endpoint = WSDL_DEFAULT_ENDPOINT;
  bool endpoint_set = false;
  int returnValue = 1; // Assume Failure

  Type1* input = NULL;
  Type1* result = NULL;

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
  try {
    if(endpoint_set) {
      ws = new EnumerationWS("http://localhost:80/axis/enumeration", APTHTTP1_1);
      free(endpoint);
      endpoint_set = false;
    } else
      ws = new EnumerationWS("http://localhost:80/axis/enumeration");

    input = new Type1();

    input->enum_string="one";
    input->att_enum_string="one";
    input->enum_int=ENUMTYPEINT_0;
    input->att_enum_int=ENUMTYPEINT_1;
    input->att_enum_kind="CHEQUE";

	ws->setTransportProperty("SOAPAction" , "enumeration#getInput");
    result = ws->getInput(input);

    cout << "Result" << endl;
    if ( result == NULL ) {
      cout << "  result = NULL" << endl;
    } else {
      cout << "att_enum_int " << result->att_enum_int << endl;
      cout << "att_enum_string " << result->att_enum_string << endl;
      cout << "enum_int " << result->enum_int << endl;
      cout << "enum_string " << result->enum_string << endl;
      cout << "enum_kind " << result->att_enum_kind << endl;
      returnValue = 0; // Success
    }

	bSuccess = true;
  } catch(AxisException &e) {
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
    cerr << e.what() << endl;
			}
  } catch(...) {
    cerr << "Unknown Exception occured." << endl;
  }
  try
  {
	  delete ws;
	  delete input;
	  delete result;
  }
  catch(exception& exception)
  {
  	cout << "Exception when cleaning up: " << exception.what()<<endl;
  }
  catch(...)
  {
  	cout << "Unknown exception when cleaning up: "<<endl;
  }
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
    if(endpoint_set)
      free(endpoint);
  cout << "---------------------- TEST COMPLETE -----------------------------"<< endl;
  printf("successful \n");
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
    if(output_file.is_open()){
        cout.rdbuf( output_file.rdbuf() );
    }
}

