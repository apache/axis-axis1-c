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

import java.io.File;

import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.Project;
import org.apache.tools.ant.taskdefs.Ant;

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
			Class.forName("com.sun.tools.javac.Main");
			Project project = new Project();
			project.init();
			project.setCoreLoader(null);
			Ant ant = new Ant();
			ant.setProject(project);
			ant.init();
			ant.setInheritAll(true);
			ant.setInheritRefs(true);
			File file = new File(buildFile);
			ant.setAntfile(file.getAbsolutePath());
			ant.setDir(file.getParentFile());
			ant.execute();        
		}catch(ClassCastException e){
			System.out.println("Ant file will not be run programatcally as the " +
				"$JAVA_HOME/lib/tool.jar is not in the class path. To run the ant " +
				"prgramatically add that jar to classpath");
        }catch(BuildException e){
			System.out.println(e.getMessage() +
			"if it is a compile error you may not have set the mavem reposiroty " +
			"directory in the conf/ws4j2ee.propertites Build fill ignore the faliure");
        }
    }
}
