package org.apache.geronimo.ews.ws4j2ee;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.AppTest;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2EEwithWSDL;

/**
 * Unit test for simple App.
 *
 * @author <a href="mailto:jason@zenplex.com">Jason van Zyl</a>
 */
public class GenerateTest 
    extends AbstractTestCase
{
    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public GenerateTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( GenerateTest.class );
    }

    public void testBookSample() throws Exception
    {
        String args[] = new String[]{getTestFile("src/samples/jaxrpc/book/webservice.xml"),
                                     "-o" + getTestFile("target/generated/gencode/server/book")};
        Ws4J2EEwithWSDL.main(args);
    }

    public void testTimeSample() throws Exception
    {
        String args[] = new String[]{getTestFile("src/samples/jaxrpc/time/webservices.xml"),
                                     "-o" + getTestFile("target/generated/gencode/server/time")};
        Ws4J2EEwithWSDL.main(args);
    }
}
