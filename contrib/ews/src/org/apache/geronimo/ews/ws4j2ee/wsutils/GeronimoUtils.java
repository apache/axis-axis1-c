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

package org.apache.geronimo.ews.ws4j2ee.wsutils;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.ejb.EJBHome;

import org.apache.axis.AxisFault;
import org.openejb.ContainerIndex;
import org.openejb.EJBContainer;

/**
 * @author hemapani@opensource.lk
 */
public class GeronimoUtils {
	public static Object invokeEJB(
		String ejbName,
		String methodName,
		Class[] parmClasses,
		Object[] parameters)throws AxisFault{
            try {
                ContainerIndex index = ContainerIndex.getInstance();
                String str = "Hello\n";
                int length = index.length();
                System.out.println(length);
                for(int i = 0;i<length;i++){
                	EJBContainer contianer = index.getContainer(i);
                	if(contianer!= null){
                		String name = contianer.getEJBName();
                		if(ejbName.equals(name)){
                			EJBHome statelessHome = contianer.getEJBHome();
                			Object stateless = statelessHome.getClass().getMethod("create", null).invoke(statelessHome, null);
                			if(parmClasses!= null){
								Object obj = stateless.getClass().getMethod(methodName,parmClasses).invoke(stateless, parameters);
								return obj; 
                			}else{
								Method[] methods = stateless.getClass().getMethods();
								for(int j = 0;i< methods.length;j++){
									if(methods[j].getName().equals(methodName)){
										return methods[j].invoke(stateless, parameters);
									}
								}
								throw new NoSuchMethodException(methodName+" not found");
                			}
                		}					
                	}
                }
				throw new AxisFault("Dependancy ejb "+ejbName+"not found ");
            } catch (Exception e) {
				throw AxisFault.makeFault(e);
            } 
	
	}
}
