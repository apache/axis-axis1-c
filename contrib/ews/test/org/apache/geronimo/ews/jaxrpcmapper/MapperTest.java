package org.apache.geronimo.ews.jaxrpcmapper;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.AppTest;
import org.apache.geronimo.ews.jaxrpcmapping.WsdlToJ2ee;

/**
 * Unit test for simple App.
 *
 * @author <a href="mailto:jason@zenplex.com">Jason van Zyl</a>
 */
public class MapperTest 
    extends AbstractTestCase
{
    /**
     * Create the test case
     *
     * @param testName name of the test case
     */
    public MapperTest( String testName )
    {
        super( testName );
    }

    /**
     * @return the suite of tests being tested
     */
    public static Test suite()
    {
        return new TestSuite( MapperTest.class );
    }

    /**
     * Rigourous Test :-)
     */
    public void testHeavyWeight()
    {
        String args[] = new String[]{"-m","src/samples/mapper/heavyweight/BookQuote.xml",
                                     "-o", "target/generated/samples/mapper/heavyweight",
                                     "src/samples/mapper/heavyweight/BookQuote.wsdl"};
        WsdlToJ2ee.main(args);
    }

    public void testLightWeight()
    {
        String args[] = new String[]{"-m","src/samples/mapper/lightweight/BookQuote.xml",
                                     "-o", "target/generated/samples/mapper/lightweight",
                                     "src/samples/mapper/lightweight/BookQuote.wsdl"};
        WsdlToJ2ee.main(args);
    }
}
