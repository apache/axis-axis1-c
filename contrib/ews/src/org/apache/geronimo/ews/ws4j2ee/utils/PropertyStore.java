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
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;

/**
 * @author hemapani@opensource.lk
 */
public class PropertyStore {
	private Properties properties;
	private File file;
	public PropertyStore(){
		File baseDir = new File(".");
		String path = baseDir.getAbsolutePath();
		if(path.endsWith("incubator-geronimo")
			||path.endsWith("incubator-geronimo\\")
			||path.endsWith("incubator-geronimo/")){
			path = new File("./modules/axis/").getAbsolutePath();
		}
		file = new File(path,"target/"+GenerationConstants.WS4J2EE_PROPERTY_FILE);
		
		file.getParentFile().mkdirs();
		FileInputStream in = null;
		System.out.println(file.getAbsolutePath() + " created .. ");
        try {
            properties = new Properties();
            if(file.exists()){
            	in = new FileInputStream(file);
            	properties.load(in);
            }
        } catch (FileNotFoundException e) {
        } catch (IOException e) {
        }finally{
			try{
				if(in != null){
					in.close();
				}
			}catch(Exception e){}

        }
	}
	public void store(String repository){
		properties.setProperty(GenerationConstants.MAVEN_LOCAL_REPOSITARY,repository);
		FileOutputStream out = null;
		try {
				out = new FileOutputStream(file);
			properties.store(out,"repository Location");
		} catch (FileNotFoundException e) {
		} catch (IOException e) {
		}finally{
			try{
				if(out != null){
					out.close();
				}
			}catch(Exception e){}
		}
	}
	
	public static void main(String[] args){
		try{
			PropertyStore store = new PropertyStore();
			store.store(args[0]);
		}catch(Exception e){}
	}
}
