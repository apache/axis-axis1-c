/*
 * Created on Jul 7, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.geronimo.ews.ws4j2ee.utils;

import junit.framework.Assert;

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.wsutils.PropertyLoader;

/**
 * @author srinath
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class PropertyLoaderTest extends AbstractTestCase{
    /**
     * @param testName
     */
    public PropertyLoaderTest(String testName) {
        super(testName);
        // TODO Auto-generated constructor stub
    }

	public void testPropertyLoading() throws GenerationFault{
		PropertyLoader ploader = new PropertyLoader();
		Assert.assertNotNull(ploader.loadProperties("jndi.properties"));
	}
}
