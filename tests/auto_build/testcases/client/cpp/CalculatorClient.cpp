#include "Calculator.h"
#include <axis/AxisGenException.h>
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http://localhost:9080/Calculator/services/Calculator"

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);
void setLogOptions(const char *output_filename);

// If we re-direct cout it will be to this ofstream
ofstream output_file;

int main(int argc, char* argv[])
{
    Calculator *ws;

    char *endpoint = WSDL_DEFAULT_ENDPOINT;
    bool endpoint_set = false;
    int returnValue = 1; // Assume Failure

    endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

    try {
        if(endpoint_set) {
            ws = new Calculator(endpoint, APTHTTP);
            free(endpoint);
            endpoint_set = false;
        } else
            ws = new Calculator();

        const char* op = "add";
        int i1=2, i2=2;
        int iResult;
        char* pcDetail = 0;
    
        if (strcmp(op, "add") == 0)
        {
            iResult = ws->add(i1, i2);
            cout << iResult << endl;
        }
        else     if (strcmp(op, "sub") == 0)
        {
            iResult = ws->sub(i1, i2);
            cout << iResult << endl;
        }
        else     if (strcmp(op, "mul") == 0)
        {
            iResult = ws->mul(i1, i2);
            cout << iResult << endl;
        }
        else     if (strcmp(op, "div") == 0)
        {
            iResult = ws->div(i1, i2);
            cout << iResult << endl;
        }
        else 
        {
            cout << "Invalid operation " << op << endl;
        }
        returnValue = 0; // Success
    } catch(AxisException &e) {
        cerr << e.what() << endl;
        if(endpoint_set)
          free(endpoint);
    } catch(...) {
        cerr << "Unknown Exception occurred." << endl;
        if(endpoint_set)
          free(endpoint);
    }
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
