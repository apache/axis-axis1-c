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

package org.apache.geronimo.ews.ws4j2ee.utils;

import java.io.IOException;
import java.util.Enumeration;
import java.util.Properties;

import org.apache.axis.utils.ClassUtils;

/**
 * @author hemapani
 */
public class AntExecuter {
	private String buildFile = "build.xml";
	
	public void execute(String buildFile){
		org.apache.tools.ant.Main.main(new String[]{"-f",buildFile});
	
	}
	public static void main(String[] args) throws IOException{
		AntExecuter ex = new AntExecuter();
//		System.setProperty("ant.home","C:/ANT/jakarta-ant-1.5");
//		String path = System.getProperty("java.class.path");
//		path = path +";"+ "H:\\j2sdk1.4.1_01\\lib\\tools.jar";
//		System.setProperty("java.class.path",path);

		Properties p = System.getProperties();
		

//		ClassUtils.setDefaultClassLoader(ClassUtils.createClassLoader(
//								"H:\\j2sdk1.4.1_01\\lib\\tools.jar",
//								ex.getClass().getClassLoader()));
		ClassLoader cl = ClassUtils.createClassLoader("H:/j2sdk1.4.1_01/lib/tools.jar",ClassLoader.getSystemClassLoader());
		
		org.apache.tools.ant.Main.start(new String[]{"-f","target/generated/samples/withWSDL/server/google/build.xml"},
		null,cl);
		//org.apache.tools.ant.Main.main(new String[]{"-f","target/generated/samples/withWSDL/server/google/build.xml"});
		
		Enumeration e = p.keys();
		while(e.hasMoreElements()){
			String key = (String)e.nextElement();
			System.out.println(key + "= " + System.getProperty(key));
		}

		//Runtime.getRuntime().exec("ant -f target/generated/samples/withWSDL/server/google/build.xml");
	}
}
