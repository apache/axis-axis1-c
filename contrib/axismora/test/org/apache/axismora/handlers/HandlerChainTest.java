package org.apache.axismora.handlers;

import java.util.ArrayList;

import javax.xml.namespace.QName;

import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.soap.BasicMessageContext;

import testData.SampleHandler1;
import testData.SampleHandler2;
import testData.SampleHandler3;
import testData.SampleHandlerThrowsFault;

import junit.framework.Assert;
import junit.framework.TestCase;

/**
 * @author hemapani
 */
public class HandlerChainTest extends TestCase{
	private static HandlerChain hchain;
	public HandlerChainTest() {
		super();
	}

	public HandlerChainTest(String arg0) {
		super(arg0);
	}
	
	
	public void testGetUnderStoodGName(){
		ArrayList understoodNames = hchain.getAllUnderStandQNames();
		Assert.assertTrue(understoodNames!=null 
			&& understoodNames.contains(new QName("http//ws.apache.org","header1"))
			&& understoodNames.contains(new QName("http//ws.apache.org","header2"))
			&& understoodNames.contains(new QName("http//ws.apache.org","header3"))
			&& understoodNames.contains(new QName("http//ws.apache.org","header4"))
			&& understoodNames.contains(new QName("http//ws.apache.org","header5"))
			&& understoodNames.contains(new QName("http//ws.apache.org","header6")));
	} 
	
	public void testRoles(){
		ArrayList roles = hchain.getAllRoles();
		
		Assert.assertTrue(roles!=null 
			&& roles.contains("sample handler 1")
			&& roles.contains("sample handler 2")
			&& roles.contains("sample handler 3"));
	}
	
	public void testInvoke()throws Exception{
		System.out.println("---- start testInvoke ----");		
		hchain.invoke(new BasicMessageContext());
	}
	
	public void testOnFault()throws Exception{
		try{	
			System.out.println("---- start testOnFault ----");	
			Handler h = new SampleHandlerThrowsFault();
			hchain.add(h);
			hchain.invoke(new BasicMessageContext());
			hchain.remove(h);
		}catch(Exception e){
			
		}	
	}
	protected void setUp() throws Exception {
		if(hchain == null){
			hchain = new BasicHandlerChain();
			hchain.add(new SampleHandler1());	
			hchain.add(new SampleHandler2());
			hchain.add(new SampleHandler3());
		}		
	}
}
