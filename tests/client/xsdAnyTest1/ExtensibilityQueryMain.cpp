#include "gen_src/ExtensibilityQueryPortType.h"

int main(int argc, char* argv[])
{
    char endpoint[256];
    const char* server="localhost";
    const char* port="80";
    AnyType* pAny = new AnyType();
    pAny->_size = 2;
    pAny->_array = new char*[2];

    server = argv[1];
    port = argv[2];

    pAny->_array[0] = strdup("<queryExpression><queryByServiceDataNames xsi:type=\"ns1:QNamesType\" xmlns:ns1=\"http://www.gridforum.org/namespaces/2003/03/OGSI\"><name>serviceDataName</name></queryByServiceDataNames></queryExpression>");
    pAny->_array[1] = strdup("<getQuoteResponse xmlns=\"http://www.getquote.org/test\"><result><name>Widgets Inc.</name><symbol>WID</symbol><public>true</public></result></getQuoteResponse>");

    string str;
    try{
	sprintf(endpoint, "http://%s:%s/axis/testXSDANY", server, port);
        printf("endpoint:%s\n", endpoint);
        //ExtensibilityQueryPortType* pStub = new ExtensibilityQueryPortType("http://localhost:5555/axis/testXSDANY",APTHTTP);
        ExtensibilityQueryPortType* pStub = new ExtensibilityQueryPortType(endpoint);
        AnyType* pAnyReturn = pStub->query(pAny);
		if (!pAnyReturn)
		{
			printf("Returned AnyType is null\ntest failed\n");
			exit(1);
		}	
        for (int i=0; i<pAnyReturn->_size; i++)
        {
			printf("\nSent xml string: \n%s\n", pAny->_array[i]);
			printf("\nReturned xml string: \n%s\n", pAnyReturn->_array[i]);
        }
    }
    catch(AxisException& e)
    {
        printf("%s\n", e.getExceptionCode());
    }

    return 0;
}
