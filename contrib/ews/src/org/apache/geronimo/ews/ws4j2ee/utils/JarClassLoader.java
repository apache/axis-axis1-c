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
import java.io.IOException;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author srinath
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class JarClassLoader extends ClassLoader{
    private JarFile ajar;
    private HashMap classToResourceMap = new HashMap();
    private  byte[] data = new byte[10*1024];
    /**
     * @param parent
     */
    public JarClassLoader(ClassLoader parent,File jarFile ) {
        super(parent);
		try {
            ajar = new JarFile(jarFile);
            Enumeration enties = ajar.entries();
            while(enties.hasMoreElements()){
            	ZipEntry entry = (ZipEntry)enties.nextElement();
            	String name = entry.getName();
            	if(name.endsWith(".class")){
            		System.out.println("loading ..."+name); 
					loadClass(name);            	
            	}else if(name.endsWith(".jar")){
            		//TODO load the jar ??
            	}	
            }
        } catch (Exception e) {
            e.printStackTrace();
            GenerationFault.createGenerationFault(e);
        }		
    }
	public Class findClass(String name) throws ClassNotFoundException {
		if(ajar == null){
			return super.findClass(name);
		}
		JarEntry loaded_class_entry = ajar.getJarEntry(name);
		if(loaded_class_entry == null)
			return(null); 
		try {  
			InputStream is = ajar.getInputStream(loaded_class_entry);
			
			int available = is.available();
			if(available > data.length){
				data = new byte[available];
			}
			
			int index = 0;
			int val = 1;
			System.out.println(available);
			while(true){
				val = is.read(data,index,1024);
				if(val < 0 || val == 0 )
					break;
				index = index + val;
			}
			Class classt = defineClass(null, data, 0, index);
			is.close();
			return classt;
		}
		catch(IOException ioe)  {
			System.out.println("Exception: " + ioe);
			return(null);
		}
	}
}
