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

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;


/**
 * <p>To call this Class and execute a ant task the $JAVA_HOME/lib/tool.jar need
 * to be in the class path. And so far I use the commnad line to call the Ant.
 * It should be replaced by call to the Project class.</p>  
 * @author hemapani
 */
public class AntExecuter {
	private String buildFile = "build.xml";
	
	public void execute(String buildFile)throws Exception{
////		Process p = Runtime.getRuntime().exec("echo %JAVA_HOME%");
//  		Process p = Runtime.getRuntime().exec(new String[]{"notepad"});
//		BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
//		String line = null;
//		while((line = in.readLine())!= null){
//			System.out.println(line);
//		}
//wait till the ant jar added
//		org.apache.tools.ant.Main.main(new String[]{"-f",buildFile,"-verbose","-debug"});
//TODO  following code should load the tool.jar but it does not work yet
//		ClassLoader cl = org.apache.axis.utils.ClassUtils.createClassLoader(
//					"H:/j2sdk1.4.1_01/lib/tools.jar",
//					ClassLoader.getSystemClassLoader());
		//org.apache.tools.ant.Main.start(new String[]{"-f",buildFile},null,cl);
	}
}
