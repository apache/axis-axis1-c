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

import java.net.URL;

import junit.framework.Assert;
import junit.framework.TestCase;

import usageTests.types.BasicStruct;
import usageTests.types.SOAPStruct;
import usageTests.types.SupportedTypesTest;
import usageTests.types.SupportedTypesTestServiceLocator;


/**
 * @author hemapani
 */
public class SupportTypesTest extends TestCase{
	public void testSupportedTypes()throws Exception{
		SupportedTypesTestServiceLocator locator = new SupportedTypesTestServiceLocator();
		SupportedTypesTest port = locator.getHeavy(new URL(AllUsageTest.END_POINT_URI));
		
		SOAPStruct arg = new SOAPStruct();
		arg.setVal1("hello");
		arg.setVal10(new String[]{"to be or not be","that is the question"});
		arg.setVal11(new int[]{0,1,5});
		arg.setVal12(new short[]{1,37,3});
		arg.setVal13(new double[]{23.67,4678.43,4565.65787487});
		arg.setVal14(new float[]{1,23,3,4567,32,56});
		arg.setVal15(new long[]{13123435,46767676,565476,6768686});
		arg.setVal17("sorry is a hard thing to say, forgiving is harder".getBytes());
		arg.setVal18(new boolean[]{true,false,false});
		BasicStruct val = new BasicStruct();
		val.setValA1("oaks are uprooted by the strom, not the bambos");
		val.setValA2(647587698);
		val.setValA3(657860879);
		val.setValA4("heart say you have been clever, yet results say you have been lucky");
		val.setValA5("everybody starts, only greats will finish");
		arg.setVal19(val);
		arg.setVal2(5654768);
		arg.setVal20(new BasicStruct[]{val,val,val,val});
		short j = 0;
		arg.setVal3(j);
		arg.setVal4(4546.789709);
		arg.setVal6(465436768);
		arg.setVal8("A".getBytes()[0]);
		arg.setVal9(true);
		arg.setVal21(val);
		SOAPStruct result = port.echoSOAPStruct(arg);
		
		Assert.assertEquals(arg.getVal1(),result.getVal1());
		Assert.assertEquals(arg.getVal2(),result.getVal2());
		Assert.assertEquals(arg.getVal3(),result.getVal3());
		Assert.assertTrue(arg.getVal4() == result.getVal4());
		Assert.assertTrue(arg.getVal5() == result.getVal5());
		Assert.assertTrue(arg.getVal6() == result.getVal6());
		System.out.println(arg.getVal8() +" == "+result.getVal8());
		Assert.assertTrue(arg.isVal9() == result.isVal9());
		
		String[] val9 = arg.getVal10();
		String[] res9 = result.getVal10();
		
		for(int i=0;i<res9.length;i++){
			Assert.assertEquals(val9[i],res9[i]);
		}

		
		int[] val8 = arg.getVal11(); 
		int[] res8 = result.getVal11();
		for(int i=0;i<res8.length;i++){
			Assert.assertTrue(val8[i] == res8[i]);
		}
		
		short[] val12 = arg.getVal12(); 
		short[] res12 = result.getVal12();
		for(int i=0;i<res12.length;i++){
			Assert.assertTrue(val12[i] == res12[i]);
		}
		double[] val13 = arg.getVal13(); 
		double[] res13 = result.getVal13();
		for(int i=0;i<res13.length;i++){
			Assert.assertTrue(val13[i] == res13[i]);
		}
		float[] val14 = arg.getVal14(); 
		float[] res14 = result.getVal14();
		for(int i=0;i<res14.length;i++){
			Assert.assertTrue(val14[i] == res14[i]);
		}
		
		long[] val15 = arg.getVal15(); 
		long[] res15 = result.getVal15();
		for(int i=0;i<res15.length;i++){
			Assert.assertTrue(val15[i] == res15[i]);
		}
		System.out.println(new String(arg.getVal17()) +" == "+new String(result.getVal17()));
		
		boolean[] val18 = arg.getVal18(); 
		boolean[] res18 = result.getVal18();
		for(int i=0;i<res18.length;i++){
			Assert.assertTrue(val18[i] == res18[i]);
		}
		
		Object obj1 = arg.getVal19();
		Object other1 = result.getVal19();
		Assert.assertTrue((obj1 == null && other1 == null) || 
				((obj1 != null && other1 != null)
				&& obj1.equals(other1)));

		Object[] objarg = arg.getVal20();
		Object[] objother = result.getVal20();
		
		for(int i =0; i<objarg.length;i++){
			 obj1 = objarg[i];
			 other1 = objother[i];
		     Assert.assertTrue((obj1 == null && other1 == null) || 
				((obj1 != null && other1 != null)&& obj1.equals(other1)));
		}
		System.out.println("test completed");
	}
	
	public static void main(String[] args)throws Exception{
		SupportTypesTest stt =  new SupportTypesTest(); 
		stt.testSupportedTypes();
	}
}
