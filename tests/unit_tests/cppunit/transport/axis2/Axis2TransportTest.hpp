#include <cppunit/Asserter.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/config-auto.h>
#include <cppunit/config-bcb5.h>
 //config-msvc6.h
#include <cppunit/Exception.h>
#include <cppunit/NotEqualException.h>
#include <cppunit/Outputter.h>
#include <cppunit/Portability.h>
#include <cppunit/SourceLine.h>
 //SynchronizedObject.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFailure.h>
 //TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestSucessListener.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/TextTestResult.h>
#include <cppunit/TextTestRunner.h>
 //XmlOutputter.h>
#include "../../../../../src/transport/axis2/Axis2Transport.h"

class Axis2TransportTest : public CppUnit::TestFixture  {
private:
  Axis2Transport* m_pTransport;
public:
    void setUp()
    {
        m_pTransport = new Axis2Transport();
    }

    void tearDown() 
    {
        delete m_pTransport;
    }

    void testGetBytes()
    {
	char sentMessage[32];
    	char endpoint[64];
    	strcpy(sentMessage, "this is a test");
    	sprintf (endpoint, "http://127.0.0.1:1111/axis");
    	m_pTransport->setEndpointUri(endpoint);
    	m_pTransport->sendBytes(sentMessage, "buffer id");
    	m_pTransport->flushOutput();
    	int status = TRANSPORT_IN_PROGRESS;
    	int tempbuffsize = 1024;
        int *buffsize = &tempbuffsize;
    	int tempsize;
    	char* buff = (char*) malloc(*buffsize);
    	memset(buff, 0, *buffsize);
    	char msg[8192];
        do
    	{
	    tempsize = *buffsize;
	    status = m_pTransport->getBytes(buff, buffsize);
	    //printf("buffsize:%d\n", *buffsize);
	    //printf("buff:\n%s\n", buff);
	    strcat(msg, buff);
	    if(*buffsize > tempsize)
	    {
	        realloc (buff, *buffsize);
	        memset(buff, 0, *buffsize);
	    }
    	}
        while((TRANSPORT_IN_PROGRESS == status) && (*buffsize) > 0);
    	//while(TRANSPORT_IN_PROGRESS == status);
    	//printf("msg:\n%s\n", msg);
    }
};


/*int main(void)
{
    //We don't need actually send a meaningful message. Just to invoke the
    //test server we need this*
   
    
    char sentMessage[32];
    char endpoint[64];
    strcpy(sentMessage, "this is a test");
    sprintf (endpoint, "http://127.0.0.1:1111/axis");
    Axis2Transport* pTransport = new Axis2Transport();
    pTransport->setEndpointUri(endpoint);
    pTransport->sendBytes(sentMessage, "buffer id");
    pTransport->flushOutput();
    int status = TRANSPORT_IN_PROGRESS;
    int *buffsize;
    *buffsize = 1024;
    int tempsize;
    char* buff = (char*) malloc(*(buffsize));
    memset(buff, 0, *buffsize);
    char msg[8192];
    do
    {
        tempsize = *buffsize;
        status = pTransport->getBytes(buff, buffsize);
        printf("buffsize:%d\n", *buffsize);
        printf("buff:\n%s\n", buff);
        strcat(msg, buff);
        if(*buffsize > tempsize)
        {
            realloc (buff, *(buffsize));
            memset(buff, 0, *buffsize);
        }
    }
    //while((TRANSPORT_IN_PROGRESS == status) && (*buffsize) > 0);
    while(TRANSPORT_IN_PROGRESS == status);
    printf("msg:\n%s\n", msg);

    return 0;
}*/
