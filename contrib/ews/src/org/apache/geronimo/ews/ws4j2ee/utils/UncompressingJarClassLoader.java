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
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Enumeration;
import java.util.Vector;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class UncompressingJarClassLoader {
    private JarFile ajar;
    private byte[] data = new byte[10 * 1024];
    private Vector urls = new Vector();

    public UncompressingJarClassLoader(
        String dir,
        File jarFile,
        String classpath,
        String jarpath) {
        try {
            ajar = new JarFile(jarFile);
            uncompress(dir, jarFile.getAbsoluteFile(), classpath, jarpath);
        } catch (Exception e) {
            e.printStackTrace();
            GenerationFault.createGenerationFault(e);
        }
    }
    public ClassLoader getClassLoader() throws GenerationFault  {
	    try{	
	        URL[] aurls = new URL[urls.size()];
	        for (int i = 0; i < aurls.length; i++) {
	            aurls[i] = ((File) urls.get(i)).toURL();
	            System.out.println(aurls[i]);
	        }
	        return new URLClassLoader(aurls,ClassLoader.getSystemClassLoader());
		} catch (Exception e) {
			throw GenerationFault.createGenerationFault(e);
		}
    }

    public void uncompress(
        String dir,
        File jarFile,
        String classpath,
        String jarpath) throws GenerationFault {
        try {
            Enumeration enties = ajar.entries();
			File file = null;
            if(classpath != null){
				file = new File(dir + "/" + classpath);
				file.mkdirs();
				urls.add(file);
            }
            //file.createNewFile();
            while (enties.hasMoreElements()) {
                ZipEntry entry = (ZipEntry) enties.nextElement();
                String name = entry.getName();

                if ((classpath != null && name.startsWith(classpath)) || name.startsWith(jarpath)) {
                    file = new File(dir + "/" + name);
                    int index = name.indexOf('.');

                    if (index > 0) {
                        file.getParentFile().mkdirs();
                        //file.createNewFile();
                        JarEntry loaded_class_entry = ajar.getJarEntry(name);
                        InputStream is = ajar.getInputStream(entry);
                        OutputStream os = new FileOutputStream(file);

                        int val = 1;
                        while (true) {
                            val = is.read(data, 0, 1024);
                            if (val < 0 || val == 0)
                                break;
                            os.write(data, 0, val);
                        }
                        is.close();
                        os.close();
                        if (name.endsWith(".jar")) {
                            urls.add(file);
                        } else if (name.endsWith(".war")) {
                            index = name.indexOf(".war");
                            String warDir = name.substring(0, index);
                            uncompress(
                                warDir,
                                file.getAbsoluteFile(),
                                classpath,
                                jarpath);
                        }
                    }

                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }

    }
    public Vector getURLs(){
    	return urls;
    }
}
