/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

import java.math.BigDecimal;
import java.net.URL;


import junit.framework.Assert;
import junit.framework.TestCase;

import org.apache.axis.encoding.Base64;
import org.soapinterop.InteropTestPortType;
import org.soapinterop.InteropTestServiceLocator;


/**
 * @author hemapani
 */
public class InteroperabilityTest extends TestCase{
	public void testInteroperability()throws Exception{
		InteropTestServiceLocator locator = new InteropTestServiceLocator();
		InteropTestPortType port =locator.getecho(new URL(AllUsageTest.END_POINT_URI));
		
		boolean val1  = true;
		Assert.assertTrue(val1 == port.echoBoolean(val1));
		System.out.println("echoBoolean test passed");
		
		int val2  = 1000;
		Assert.assertTrue(val2 == port.echoInteger(val2));
		System.out.println("echoInteger test passed");

		float val3  = 34;
		Assert.assertTrue(val3 == port.echoFloat(val3));
		System.out.println("echoFloat test passed");
		
		BigDecimal val4  = new BigDecimal(12345646.586580685065096865026020605656);
		System.out.println(val4 +"=="+ port.echoDecimal(val4));
		System.out.println("echoDecimal test passed");
		
		String val5 = "we are testing soap message interoperability";
		Assert.assertTrue(val5.equals(port.echoString(val5)));
		System.out.println("echoString test passed");
		
		byte[] val6 = Base64.encode("sending Base64".getBytes()).getBytes();
		System.out.println(val6 +"=="+ port.echoBase64(val6));
		System.out.println("echoBase64 test passed");
		
		float[] val7 = new float[]{12,23,24,27};
		float[] res7 = port.echoFloatArray(val7);
		for(int i=0;i<val7.length;i++){
			Assert.assertTrue(val7[i] == res7[i]);
		}
		System.out.println("echoFloatArray test passed");
		
		int[] val8 = new int[]{12,23,24,27};
		int[] res8 = port.echoIntegerArray(val8);
		for(int i=0;i<val8.length;i++){
			Assert.assertTrue(val8[i] == res8[i]);
		}
		System.out.println("echoIntegerArray test passed");
		
		String[] val9 = new String[]{"queen","king","pawn","knight","rook","bishop"};
		String[] res9 = port.echoStringArray(val9);
		for(int i=0;i<val9.length;i++){
			Assert.assertTrue(val9[i].equals(res9[i]));
		}
		System.out.println("echoStringArray test passed");
		
		
		port.echoVoid();
		System.out.println("echoVoid test passed");
	}
	public static void main(String[] args)throws Exception{
		InteroperabilityTest it = new InteroperabilityTest();
		it.testInteroperability(); 
	}
	
}
