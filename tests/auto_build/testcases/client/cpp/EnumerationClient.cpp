
#include "EnumerationWS.h" 
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);

int main(int argc, char* argv[])
{
  EnumerationWS *ws;

  char *endpoint = "http://localhost:9080/Enumeration/services/sampleWS";
  bool endpoint_set = false;

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

  try {
    if(endpoint_set)
      ws = new EnumerationWS(endpoint, APTHTTP);
    else
      ws = new EnumerationWS();
  } catch(AxisException &e) {
    fprintf(stderr, "Exception %s\n", e.what());
    fflush(stderr);
    if(endpoint_set)
      free(endpoint);
    return 1;
  }
  if(endpoint_set) free(endpoint);

  Type1* input = new Type1();
  Type1* result = NULL;

  input->enum_string="one";
  input->att_enum_string="one";
  input->enum_int=ENUMTYPEINT_0;
  input->att_enum_int=ENUMTYPEINT_1;
  input->att_enum_kind="CHEQUE";

  try {
    result = ws->getInput(input);
  } catch(AxisException &e) {
    fprintf(stderr, "Exception %s\n", e.what());
    fflush(stderr);
  }

  printf ("Result\n");
  if ( result == NULL ) {
    printf ("  result = NULL\n");
  } else {
    printf ("att_enum_int %d\n", result->att_enum_int);
    printf ("att_enum_string %s\n", result->att_enum_string);
    printf ("enum_int %d\n", result->enum_int);
    printf ("enum_string %s\n", result->enum_string);
    printf ("enum_kind %s\n", result->att_enum_kind);
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
