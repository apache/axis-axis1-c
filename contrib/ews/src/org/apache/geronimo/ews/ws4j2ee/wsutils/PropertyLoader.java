package org.apache.geronimo.ews.ws4j2ee.wsutils;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Properties;

import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * Load a given property file
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class PropertyLoader {
	public static Properties loadProperties(String propertyFile) throws GenerationFault{
		try {
			Properties properties = new Properties();
			InputStream proIn = PropertyLoader.class.getResourceAsStream(propertyFile);
			if(proIn == null){
				proIn = GenerationConstants.class.getResourceAsStream("META-INF/"+propertyFile);
			}
			if(proIn == null){
				proIn = new FileInputStream("src/conf/"+propertyFile);
			}
			if(proIn == null){
				proIn = new FileInputStream(propertyFile);
			}
			if(proIn != null){
				properties.load(proIn);
			}else{
				throw new GenerationFault("the "+propertyFile+ "not found");
			}
			return properties;
		} catch (Exception e) {
			throw new GenerationFault(e);
		} 
	}
}
