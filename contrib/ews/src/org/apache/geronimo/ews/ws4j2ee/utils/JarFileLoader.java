
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
import java.io.InputStream;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public class JarFileLoader {
	private InputStream  wscfFile;
	private InputStream  webddfile;
	private InputStream  ejbJarfile;
	private InputStream  wsdlfile;
	private InputStream  jaxrpcfile;
	private JarFile jar; 
	
	public JarFileLoader(String jarFile) throws GenerationFault{
		try{	
			System.out.println("found jar file "+jarFile);
			jar = new JarFile(jarFile);
			if(jarFile.endsWith(".jar")){
				wscfFile = getInputStreamForJarEntry(jarFile,"META-INF/webservice.xml");
				webddfile = getInputStreamForJarEntry(jarFile,"META-INF/web.xml");
				ejbJarfile = getInputStreamForJarEntry(jarFile,"META-INF/ejb-jar.xml");
			}else if(jarFile.endsWith(".war")){
				wscfFile = getInputStreamForJarEntry(jarFile,"WEB-INF/webservice.xml");
				webddfile = getInputStreamForJarEntry(jarFile,"WEB-INF/web.xml");
			}else if(jarFile.endsWith(".ear")){
				wscfFile = getInputStreamForJarEntry(jarFile,"META-INF/webservice.xml");
				webddfile = getInputStreamForJarEntry(jarFile,"META-INF/web.xml");
				ejbJarfile = getInputStreamForJarEntry(jarFile,"META-INF/ejb-jar.xml");
			}
			if(wscfFile == null)
				throw new GenerationFault("wscf file must not be null");
		} catch (IOException e) {
			e.printStackTrace();
			throw GenerationFault.createGenerationFault(e);
		}
	}
	public InputStream getInputStreamForJarEntry(String path) throws GenerationFault{
			try {
				ZipEntry zentry = jar.getEntry(path);
				if(zentry!= null){
					return jar.getInputStream(zentry);			
				}else{
					return null;
				}
			} catch (IOException e) {
				e.printStackTrace();
				throw GenerationFault.createGenerationFault(e);
			}
		}
	
	public InputStream getInputStreamForJarEntry(String jarFile,String path) throws GenerationFault{
		try {
			ZipEntry zentry = jar.getEntry(path);
			if(zentry!= null){
				return jar.getInputStream(zentry);			
			}else{
				return null;
			}
		} catch (IOException e) {
			e.printStackTrace();
			throw GenerationFault.createGenerationFault(e);
		}
	}
	
	public void loadtheClassesInJarFile()throws GenerationFault{
	}
	
	/**
	 * @return
	 */
	public InputStream getEjbJarfile() {
		return ejbJarfile;
	}

	/**
	 * @return
	 */
	public InputStream getWebddfile() {
		return webddfile;
	}

	/**
	 * @return
	 */
	public InputStream getWscfFile() {
		return wscfFile;
	}

	/**
	 * @param stream
	 */
	public void setEjbJarfile(InputStream stream) {
		ejbJarfile = stream;
	}

	/**
	 * @param stream
	 */
	public void setWebddfile(InputStream stream) {
		webddfile = stream;
	}

	/**
	 * @param stream
	 */
	public void setWscfFile(InputStream stream) {
		wscfFile = stream;
	}

}
