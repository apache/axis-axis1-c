/*
 * Created on Feb 26, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.geronimo.ews.ws4j2ee;

import junit.framework.TestCase;

import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2EEwithoutWSDL;

/**
 * @author srinath
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class GenerateWithoutWSDLTest extends TestCase {
	private String outDir = "target/generated/samples/";
	
	public void testMathSample() throws Exception{
		String[] args2 = new String[]{"-o"+outDir+"withoutWSDL/math/server/META-INF/math.wsdl" ,"-l" ,"http://127.0.0.1/aixs/math","testData.math.MathFace"};
		Ws4J2EEwithoutWSDL.main(args2);
	}
}
