package org.apache.geronimo.ews.ws4j2ee.wsutils;

/**
 * <p>This class is the pool that pool the servlet based JSR109 implementations
 * These is a issue of the same thing happen differently when the code gerneration
 * Done using interfaces and DD + WSDL.</p>   
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ImplBeanPool {
	private static ImplBeanPool instance;
	static{
		instance = new ImplBeanPool();
	}
	
	public static Object getImplBean(String classname) throws J2EEFault{
		return instance.getBean(classname);
	} 
	private Object getBean(String classname)throws J2EEFault{
		try {
            Class implClass = Class.forName(classname);
            return implClass.newInstance();
        } catch (Exception e) {
            e.printStackTrace();
            throw new J2EEFault(e);
        }
	}
}
