#include "gen_src/ExtensibilityQueryPortType.h"

void main()
{
    AnyType* pAny = new AnyType();
    pAny->_size = 2;
    pAny->_array = new char*[2];

    pAny->_array[0] = strdup("<queryExpression><queryByServiceDataNames xsi:type=\"ns1:QNamesType\" xmlns:ns1=\"http://www.gridforum.org/namespaces/2003/03/OGSI\"><name>serviceDataName</name></queryByServiceDataNames></queryExpression>");
    pAny->_array[1] = strdup("<getQuoteResponse xmlns=\"http://www.getquote.org/test\"><result><name>Widgets Inc.</name><symbol>WID</symbol><public>true</public></result></getQuoteResponse>");

    string str;
    try{

        ExtensibilityQueryPortType* pStub = new ExtensibilityQueryPortType("http://localhost:8080/axis/testXSDANY",APTHTTP);
        AnyType* pAnyReturn = pStub->query(pAny);

        for (int i=0; i<pAnyReturn->_size; i++)
        {
            printf("%s\n",string(pAnyReturn->_array[i]));
        }
    }
    catch(AxisException& e)
    {
        e.getExceptionCode();
    }
}