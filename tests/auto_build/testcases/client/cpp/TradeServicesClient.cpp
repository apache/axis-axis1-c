// IBM Confidential OCO Source Material
// 5639-D57, 5630-A36, 5630-A37, 5724-D18 (C) COPYRIGHT International Business Machines Corp. 1997, 2002
// The source code for this program is not published or otherwise divested
// of its trade secrets, irrespective of what has been deposited with the
// U.S. Copyright Office.
//
// Change History:
// Date     UserId      Defect          Description
// ----------------------------------------------------------------------------
//
//
#include <stdio.h>
#include "operations.h"
#include <stdlib.h> // For malloc(), calloc(), strdup() and free()
#include <iostream>
#include <fstream>

#define WSDL_DEFAULT_ENDPOINT "http:///"

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);
void setLogOptions(const char *output_filename);

// If we re-direct cout it will be to this ofstream
ofstream output_file;

int main(int argc, char* argv[]) {
  operations *ws;

  char *endpoint = WSDL_DEFAULT_ENDPOINT;
  bool endpoint_set = false;
  int returnValue = 1; // Assume Failure

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

  try {
    if(endpoint_set) {
      ws = new operations(endpoint, APTHTTP);
      free(endpoint);
      endpoint_set = false;
    } else
      ws = new operations();

    int i;
    xsd__string userid = "Durand";

    cout << "Requesting new ticket for user " << userid << endl;
    long ticket = ws->getTicket(userid);
    cout << "-> received ticket: " << ticket << endl;

    cout << "Requesting the Quote list" << endl;
    Quote_Array arrayOfQuote = ws->getAllQuotes(userid,ticket);
    cout << "-> received " << arrayOfQuote.m_Size << " Quotes" << endl;

    for(i=0;i<arrayOfQuote.m_Size;i++){
      Quote quote = arrayOfQuote.m_Array[i];
      cout << "    - " << quote.symbol << " " << quote.label << " $" << quote.price << endl;
    }

    cout << "Requesting orders to buy some Stocks..." << endl;
    cout << "Order 1: 10 * q:3" << endl;
    Order *order = ws->buyQuote(userid,ticket,10,arrayOfQuote.m_Array+3);
    cout << "-> transaction ok. id:" << order->reference << endl;

    cout << "Order 2: 7 * q:6" << endl;
    order = ws->buyQuote(userid,ticket,7,arrayOfQuote.m_Array+6);
    cout << "-> transaction ok. id:" << order->reference << endl;

    cout << "Order 3: 3 * q:9" << endl;
    order = ws->buyQuote(userid,ticket,3,arrayOfQuote.m_Array+9);
    cout << "-> transaction ok. id:" << order->reference << endl;

    cout << "Requesting my Orders list" << endl;
    Order_Array arrayOfOrder = ws->getAllOrders(userid,ticket);
    cout << "-> received " << arrayOfOrder.m_Size << " Orders" << endl;

    for(i=0;i<arrayOfOrder.m_Size;i++){
      Order anOrder = arrayOfOrder.m_Array[i];
      cout << "    - " << anOrder.reference << " " << anOrder.symbol << " $" << anOrder.price << " " << anOrder.quantity << endl;
    }

    cout << "Requesting my portfolio value" << endl;
    xsd__decimal total = ws->computePortfolio(userid,ticket);
    cout << "-> value = $" << total << endl;
    
    cout << "SUCCESS" << endl;   

    returnValue = 0; // Success

  } catch(AxisException &e) {
    cerr << e.what() << endl;
    if(endpoint_set)
      free(endpoint);
  } catch(...) {
    cerr << "Unknown Exception occured." << endl;
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
