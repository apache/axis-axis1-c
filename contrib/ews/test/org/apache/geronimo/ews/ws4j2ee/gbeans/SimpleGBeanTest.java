/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee.gbeans;
import java.io.File;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

import javax.enterprise.deploy.model.DDBean;
import javax.enterprise.deploy.model.DDBeanRoot;
import javax.enterprise.deploy.model.exceptions.DDBeanCreateException;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import junit.framework.Assert;
import junit.framework.Test;
import junit.framework.TestSuite;

import org.apache.geronimo.deployment.tools.loader.WebDeployable;
import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.parsers.gbeans.JARDeployable;
import org.w3c.dom.Document;

/**
 * @author srinath
 *
 */
public class SimpleGBeanTest extends AbstractTestCase{
	
    /**
     * @param testName
     */
    public SimpleGBeanTest(String testName) {
        super(testName);
        // TODO Auto-generated constructor stub
    }
    
	public static Test suite()
	{
		TestSuite sute = new TestSuite(); 
		sute.addTest(TestSuite.createTest(SimpleGBeanTest.class,"testLoadWar"));
		sute.addTest(TestSuite.createTest(SimpleGBeanTest.class,"testJarParsing"));
		sute.addTest(TestSuite.createTest(SimpleGBeanTest.class,"test1"));
		return sute;
	}


	public void testLoadWar() throws DDBeanCreateException, MalformedURLException{
		ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
		File file = new File(getTestFile("target/generated/samples/simple.war"));
		URL url = file.toURL();
		System.out.println(url);
		WebDeployable deployable = new WebDeployable(url);
		DDBeanRoot ddBeanRoot = deployable.getDDBeanRoot();
		assertNotNull(ddBeanRoot.getChildBean("web-app")[0]);
		assertEquals(ddBeanRoot.getChildBean("web-app/servlet/servlet-class")[0].getText(),"com.jwsbook.jaxrpc.BookQuoteBean");
	}
	
	public void test1()throws DDBeanCreateException, MalformedURLException{
		ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
		File file = new File("target/generated/samples/bookquote.jar");
		if(!file.exists()){
			throw new RuntimeException("the module does not exis.. the maven build will create them .. run it before run this");
		}
		URL url = file.toURL();
		JARDeployable deployable = new JARDeployable(url);
		DDBeanRoot root = deployable.getDDBeanRoot();
		Assert.assertEquals(root.getText("ejb-jar/display-name")[0],"BookQuoteService");
		DDBean[] session = root.getChildBean("ejb-jar/enterprise-beans/session");
		Assert.assertNotNull(session);
		Assert.assertTrue(session.length > 0);
		Assert.assertEquals(session[0].getText("ejb-name")[0],"bookquote");
		Assert.assertEquals(session[0].getText("home")[0],"com.jwsbook.jaxrpc.BookQuoteHome");
		Assert.assertEquals(session[0].getText("remote")[0],"com.jwsbook.jaxrpc.BookQuoteEJB");
		Assert.assertEquals(session[0].getText("ejb-class")[0],"com.jwsbook.jaxrpc.BookQuoteBean");
		Assert.assertEquals(session[0].getText("session-type")[0],"Stateless");
		Assert.assertEquals(session[0].getText("transaction-type")[0],"Bean");
	}
	
	public void testJarParsing()throws Exception{
		File file = new File("target/generated/samples/bookquote.jar");
		if(!file.exists()){
			throw new RuntimeException("the module does not exis.. the maven build will create them .. run it before run this");
		}
		URL url = file.toURL();
		ClassLoader rootCL = new URLClassLoader(new URL[] {url}, Thread.currentThread().getContextClassLoader());
		URL descriptor = rootCL.getResource("META-INF/ejb-jar.xml");
		System.out.println(descriptor);
		DocumentBuilder parser = null;
		parser = DocumentBuilderFactory.newInstance().newDocumentBuilder();
		InputStream is = null;
		is = descriptor.openStream();
		Document doc = parser.parse(is);
	}
}
