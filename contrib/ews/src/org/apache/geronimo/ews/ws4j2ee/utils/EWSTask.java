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
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2ee;
import org.apache.tools.ant.AntClassLoader;
import org.apache.tools.ant.BuildException;
import org.apache.tools.ant.Location;
import org.apache.tools.ant.Task;
import org.apache.tools.ant.types.Path;

/**
 * @author hemapani@opensource.lk
 */
public class EWSTask extends Task{
	private String outDir = ".";
	private String module = null;
	private Path classpath;
    private File root;
    private boolean compile = false;
    
    public void execute() throws BuildException {
        try{
            if(module == null){
                throw new BuildException("the module name not specifed");
            }
            root = project.getBaseDir();
            File moduleFile = new File(root,module);
            File outDirFile = new File(root,outDir);
            
            AntClassLoader cl = new AntClassLoader(
                                getClass().getClassLoader(),
                                project,
                                classpath,
                                true);
            Thread.currentThread().setContextClassLoader(cl);

            if(null == cl.getResourceAsStream("org/apache/geronimo/ews/ws4j2ee/context/webservices/server/jaxb/jaxb.properties"))
                throw new Exception("error loding properties");
            AntDeployContext deployContext 
                = new AntDeployContext(moduleFile.getAbsolutePath(),
                                outDirFile.getAbsolutePath(),cl);
                 
           Ws4J2ee ws4j2ee = new Ws4J2ee(deployContext,null);
           ws4j2ee.generate();
        }catch(Throwable e){
            try {
                File errorDump = new File(root,"ews.log");
                PrintWriter pw = new PrintWriter(new FileWriter(errorDump));
                e.printStackTrace(pw);
                pw.close();
                System.out.println(classpath);
                System.out.println("ERROR .. dump to "+errorDump.getAbsolutePath());
            } catch (IOException e1) {
            }
            throw new BuildException(e);
        }
    }

    public Location getLocation() {
        return super.getLocation();
    }

    public String getTaskName() {
        return super.getTaskName();
    }

    public void init() throws BuildException {
        super.init();
    }

    public void setLocation(Location arg0) {
        super.setLocation(arg0);
    }

    public void setTaskName(String arg0) {
        super.setTaskName(arg0);
    }

    /**
     * @return
     */
    public Path getClasspath() {
        return classpath;
    }

    /**
     * @return
     */
    public String getModule() {
        return module;
    }

    /**
     * @return
     */
    public String getOutDir() {
        return outDir;
    }

    /**
     * @param path
     */
    public void setClasspath(Path path) {
        classpath = path;
    }

    /**
     * @param string
     */
    public void setModule(String string) {
        module = string;
    }

    /**
     * @param string
     */
    public void setOutDir(String string) {
        outDir = string;
    }
    public Path createClasspath() {
      if (classpath == null) {
        classpath = new Path(project);
      }
      return classpath.createPath();
    }
    /**
     * @return
     */
    public boolean isCompile() {
        return compile;
    }

    /**
     * @param b
     */
    public void setCompile(boolean b) {
        compile = b;
    }

}
