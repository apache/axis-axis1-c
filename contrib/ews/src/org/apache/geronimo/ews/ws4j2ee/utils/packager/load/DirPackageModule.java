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

package org.apache.geronimo.ews.ws4j2ee.utils.packager.load;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Vector;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class DirPackageModule implements PackageModule{
	protected InputStream wscfFile;
	protected InputStream webddfile;
	protected InputStream ejbJarfile;
	private String location;

    /**
     * @param jarFile
     * @throws GenerationFault
     */
    public DirPackageModule(String location)
        throws GenerationFault {
        File file = null;
        this.location = location; 
        try {
            file = new File(location+ "/WEB-INF/webservice.xml");
            if(file.exists()){
            	wscfFile = new FileInputStream(file);
            }else{
            	file = new File(location+ "/META-INF/webservice.xml");
            	if(file.exists()){
            		wscfFile = new FileInputStream(file);        	
            	}else{
            		wscfFile = new FileInputStream(new File(location+ "/webservice.xml"));			
            	}
            }
			findDDs();
        } catch (FileNotFoundException e) {
			throw GenerationFault.createGenerationFault(e);
        }	
    }
    
	/**
	 * @param jarFile
	 * @throws GenerationFault
	 */
	public DirPackageModule(File wscfDDFile)
		throws GenerationFault {
		try{
			wscfFile = new FileInputStream(wscfDDFile);
			File parent = wscfDDFile.getParentFile();
			String parentName = parent.getAbsolutePath();
			if(parentName.endsWith("WEB-INF")
				||parentName.endsWith("WEB-INF/")
				||parentName.endsWith("WEB-INF")
				||parentName.endsWith("META-INF/")){
				this.location = parent.getParentFile().getAbsolutePath();
			}else{
				this.location = parent.getAbsolutePath();
			}
			findDDs();
		} catch (FileNotFoundException e) {
			throw GenerationFault.createGenerationFault(e);
		}	
	}            
            
	public void findDDs()throws GenerationFault {
		try{	
            File file = new File(location+ "/META-INF/ejb-jar.xml");
            if(file.exists()){
            	ejbJarfile = new FileInputStream(file);
            }else{
            	file = new File(location+ "/ejb-jar.xml");
            	if(file.exists()){
            		ejbJarfile = new FileInputStream(file);        	
            	}
            }
            
            file = new File(location+ "WEB-INF/web.xml");
            if(file.exists()){
            	webddfile = new FileInputStream(file);
            }else{
            	file = new File(location+ "/web.xml");
            	if(file.exists()){
            		webddfile = new FileInputStream(file);        	
            	}
            }
            if (wscfFile == null)
                throw new GenerationFault("wscf file must not be null");
        } catch (FileNotFoundException e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public ClassLoader getClassLoaderWithPackageLoaded() throws GenerationFault {
        try {
            File file = new File(location);
            return new URLClassLoader(new URL[]{file.toURL()});
        } catch (MalformedURLException e) {
			throw GenerationFault.createGenerationFault(e);
        }
    }
    public Vector getClassPathElements() throws GenerationFault {
    	Vector elements = new Vector();
		elements.add(new File(location));
		return elements;
    }

    public InputStream getEjbJarfile() throws GenerationFault {
        return ejbJarfile;
    }

    public InputStream getWebddfile() throws GenerationFault {
        return webddfile;
    }

    public InputStream getWscfFile() throws GenerationFault {
        return wscfFile;
    }

    public void setEjbJarfile(InputStream stream) throws GenerationFault {
		this.ejbJarfile = stream;

    }

    public void setWebddfile(InputStream stream) throws GenerationFault {
		this.webddfile = stream;
    }

    public void setWscfFile(InputStream stream) throws GenerationFault {
        this.wscfFile = stream;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule#findFileInModule(java.lang.String)
     */
    public InputStream findFileInModule(String path)throws GenerationFault  {
    	try {
            File file = new File(location + "/"+path);
            if(file.exists())
            	new FileInputStream(file);
            return null;
        } catch (FileNotFoundException e) {
			throw GenerationFault.createGenerationFault(e);
        }
    }

}
