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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Properties;

/**
 * @author hemapani@opensource.lk
 */
public class Ws4J2eeProperties {
	private Properties properties;
	/**
	 * these a properties of the files or dir
	 * they are checked are they really exists
	 */
	private ArrayList properitesToCheck; 
	
	public Ws4J2eeProperties(){
		properties = new Properties();
		properitesToCheck = new ArrayList(); 
		properitesToCheck.add(GenerationConstants.AXIS_WEBAPPS_LIB);
		properitesToCheck.add(GenerationConstants.EJB_DEPLOY_DIR);
		properitesToCheck.add(GenerationConstants.MAVEN_LOCAL_REPOSITARY);
		loadProperties();
		checkProperties();
	}
	
	public String getProperty(String key){
		return properties.getProperty(key);
	}
	
	private void checkProperties(){
		for(int i =0;i<properitesToCheck.size();i++){
			String key = (String)properitesToCheck.get(i);
			String value = properties.getProperty(key);
			if(value != null){
				File file = new File(value);
				if(!file.exists()){
					properties.remove(key);
				}
			}
		}
	}
	
	private void loadProperties(){
		InputStream proIn = null;
		proIn = GenerationConstants.class.getResourceAsStream(GenerationConstants.WS4J2EE_PROPERTY_FILE);
        try {
            if(proIn == null){
				File file = new File("conf/"+GenerationConstants.WS4J2EE_PROPERTY_FILE);
				if(file.exists()){
					proIn = new FileInputStream(file);				
				}
            }
            if(proIn == null){
            	proIn = GenerationConstants.class.getResourceAsStream("META-INF/"+GenerationConstants.WS4J2EE_PROPERTY_FILE);
            }
            if(proIn == null){
            	proIn = new FileInputStream(GenerationConstants.WS4J2EE_PROPERTY_FILE);
            }
            if(proIn != null){
            	properties.load(proIn);
            }
        } catch (Exception e) {
         	throw new UnrecoverableGenerationFault(e);
        }
	
	}
	
}
