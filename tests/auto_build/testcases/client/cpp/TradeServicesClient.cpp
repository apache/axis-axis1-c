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

// Prototype
bool parse_args_for_endpoint(int *argc, char *argv[], char **endpoint);
void shift_args(int i, int *argc, char *argv[]);


int main(int argc, char* argv[]){
  int i;
  xsd__string userid;
  operations *ws;


  char *endpoint = WSDL_DEFAULT_ENDPOINT;
  bool endpoint_set = false;

  endpoint_set = parse_args_for_endpoint(&argc, argv, &endpoint);

  try {
    if(endpoint_set)
      ws = new operations(endpoint, APTHTTP);
    else
      ws = new operations();

    userid = "Durand";

    // we are changing the EndpointURI here to redirect requests toward the TCP/IP Monitor
    // uncomment the following if using any TCP/IP traffic monitoring tool
    // ws->SetEndpointURI("http://localhost:9081/TradeApplication/services/Service");

    printf("Requesting new ticket for user %s\n",userid);
    long ticket = ws->getTicket(userid);
    printf("-> received ticket: %ld\n",ticket);

    printf("Requesting the Quote list\n");
    Quote_Array arrayOfQuote = ws->getAllQuotes(userid,ticket);
    printf("-> received %d Quotes\n",arrayOfQuote.m_Size);

    for(i=0;i<arrayOfQuote.m_Size;i++){
      Quote quote = arrayOfQuote.m_Array[i];
      printf("    - %s %s $%f\n",quote.symbol,quote.label,quote.price);
    }

    printf("Requesting orders to buy some Stocks...\n");
    printf("Order 1: 10 * q:3\n");
    Order *order = ws->buyQuote(userid,ticket,10,arrayOfQuote.m_Array+3);
    printf("-> transaction ok. id:%d\n",order->reference);

    printf("Order 2: 7 * q:6\n");
    order = ws->buyQuote(userid,ticket,7,arrayOfQuote.m_Array+6);
    printf("-> transaction ok. id:%d\n",order->reference);

    printf("Order 3: 3 * q:9\n");
    order = ws->buyQuote(userid,ticket,3,arrayOfQuote.m_Array+9);
    printf("-> transaction ok. id:%d\n",order->reference);

    printf("Requesting my Orders list\n");
    Order_Array arrayOfOrder = ws->getAllOrders(userid,ticket);
    printf("-> received %d Orders\n",arrayOfOrder.m_Size);

    for(i=0;i<arrayOfOrder.m_Size;i++){
      Order anOrder = arrayOfOrder.m_Array[i];
      printf("    - %d %s $%f %d\n",anOrder.reference,anOrder.symbol,anOrder.price,anOrder.quantity);
    }

    printf("Requesting my portfolio value\n");
    xsd__decimal total = ws->computePortfolio(userid,ticket);
    printf("-> value = $%f\n",total);
    
    printf ("Compilation success\n");   
  } catch(AxisException &e) {
    fprintf(stderr, "%s\n", e.what());
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
