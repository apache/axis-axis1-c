/* IBM Confidential OCO Source Material
 * 5639-D57, 5630-A36, 5630-A37, 5724-D18 (C) COPYRIGHT International Business Machines Corp. 1997, 2002
 * The source code for this program is not published or otherwise divested
 * of its trade secrets, irrespective of what has been deposited with the
 * U.S. Copyright Office.
 *
 * Change History:
 * Date     UserId      Defect          Description
 * ----------------------------------------------------------------------------
 *
 */
#include <stdio.h>
#include "operations.h"

int main(int argc, char* argv[]){
	
	void * proxy;
	xsd__string userid;
	long ticket;
	int i=0;
	Quote_Array arrayOfQuote;
	Order_Array arrayOfOrder;
	Quote quote;
	Quote *myQuote;
	Order *order;
	Order anOrder;
	xsd__decimal total;

  userid = strdup("Durand");

	/* we are changing the EndpointURI here to redirect requests toward the TCP/IP Monitor
	 * change port if using any TCP/IP traffic monitoring tool.
   */
	proxy = get_operations_stub("http://127.0.0.1:9080/TradeApplication/services/Service");

	printf("Requesting new ticket for user %s\n",userid);
	ticket = getTicket(proxy,userid);
	printf("-> received ticket: %ld\n",ticket);

	printf("Requesting the Quote list\n");
	arrayOfQuote = getAllQuotes(proxy,userid,ticket);
	printf("-> received %d Quotes\n",arrayOfQuote.m_Size);

	for(i=0;i<arrayOfQuote.m_Size;i++){
		quote = arrayOfQuote.m_Array[i];
		printf("    - %s %s $%f\n",quote.symbol,quote.label,quote.price);
	}

	printf("Requesting orders to buy some Stocks...\n");
	printf("Order 1: 10 * q:3\n");
	order = buyQuote(proxy,userid,ticket,10,arrayOfQuote.m_Array+3);
	printf("-> transaction ok. id:%d\n",order->reference);
  Axis_Delete_Order (order,0,0);

	printf("Order 2: 7 * q:6\n");
	order = buyQuote(proxy,userid,ticket,7,arrayOfQuote.m_Array+6);
	printf("-> transaction ok. id:%d\n",order->reference);
  Axis_Delete_Order (order,0,0);

	/* Another way to do the same call: with a user-created quote structure */
	printf("Order 3: 3 * q:9\n");
	myQuote = Axis_Create_Quote(NULL,0,0);
	order = buyQuote(proxy,userid,ticket,3,arrayOfQuote.m_Array+9);
	printf("-> transaction ok. id:%d\n",order->reference);
	Axis_Delete_Quote(myQuote,0,0);
  Axis_Delete_Order (order,0,0);

	printf("Requesting my Orders list\n");
	arrayOfOrder = getAllOrders(proxy,userid,ticket);
	printf("-> received %d Orders\n",arrayOfOrder.m_Size);

	for(i=0;i<arrayOfOrder.m_Size;i++){
		anOrder = arrayOfOrder.m_Array[i];
		printf("    - %d %s $%f %d\n",anOrder.reference,anOrder.symbol,anOrder.price,anOrder.quantity);
	}

	printf("Requesting my portfolio value\n");
	total = computePortfolio(proxy,userid,ticket);
	printf("-> value = $%f\n",total);

  /* Free */
	Axis_Delete_Quote(arrayOfQuote.m_Array,1,arrayOfQuote.m_Size);
  Axis_Delete_Order (arrayOfOrder.m_Array,1,arrayOfOrder.m_Size);
  free (userid);
  
    printf ("Compilation success\n"); 

	return 0;
}
