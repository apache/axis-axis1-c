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




/**
 * <p>To call this Class and execute a ant task the $JAVA_HOME/lib/tool.jar need
 * to be in the class path. And so far I use the commnad line to call the Ant.
 * It should be replaced by call to the Project class.</p>  
 * @author hemapani
 */
public class AntExecuter{
    public void execute(String buildFile) throws Exception {
        //wait till the ant jar added
        try{
//			Class.forName("com.sun.tools.javac.Main");
//			org.apache.tools.ant.Main.start(
//				new String[] { "-f", buildFile },
//				null,
//				cl);
        }catch(ClassCastException e){
			System.out.println("Ant file will not be run programatcally as the " +
				"$JAVA_HOME/lib/tool.jar is not in the class path. To run the ant " +
				"prgramatically add that jar to classpath");
        }
    }
}
