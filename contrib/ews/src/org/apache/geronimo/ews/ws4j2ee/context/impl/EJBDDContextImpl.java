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

package org.apache.geronimo.ews.ws4j2ee.context.impl;

import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;

/**
 * @author hemapani@opensource.lk
 */
public class EJBDDContextImpl implements EJBContext {
	private String ejbName;
	private String implBean;
	private String ejbhomeInterface;
	private String ejbRemoteInterface;
	private String ejbLocalHomeInterfce;
	private String ejbLocalInterface;
	
	public EJBDDContextImpl(String ejbName,
							String implBean,
							String ejbhomeInterface,
							String ejbRemoteInterface,
							String ejbLocalHomeInterfce,
							String ejbLocalInterface){
		this.ejbName = ejbName;
		this.implBean = implBean;
		this.ejbhomeInterface = ejbhomeInterface;
		this.ejbRemoteInterface = ejbRemoteInterface;
		this.ejbLocalHomeInterfce = ejbLocalHomeInterfce;
		this.ejbLocalInterface = ejbLocalInterface;
	}
    /**
     * @return
     */
    public String getEjbLocalHomeInterfce() {
        return ejbLocalHomeInterfce;
    }

    /**
     * @return
     */
    public String getEjbLocalInterface() {
        return ejbLocalInterface;
    }

    /**
     * @return
     */
    public String getEjbName() {
        return ejbName;
    }

    /**
     * @return
     */
    public String getEjbRemoteInterface() {
        return ejbRemoteInterface;
    }

    /**
     * @return
     */
    public String getImplBean() {
        return implBean;
    }
    /**
     * @return
     */
    public String getEjbhomeInterface() {
        return ejbhomeInterface;
    }

    /**
     * @param string
     */
    public void setEjbhomeInterface(String string) {
        ejbhomeInterface = string;
    }

    /**
     * @param string
     */
    public void setEjbLocalHomeInterfce(String string) {
        ejbLocalHomeInterfce = string;
    }

    /**
     * @param string
     */
    public void setEjbLocalInterface(String string) {
        ejbLocalInterface = string;
    }

    /**
     * @param string
     */
    public void setEjbName(String string) {
        ejbName = string;
    }

    /**
     * @param string
     */
    public void setEjbRemoteInterface(String string) {
        ejbRemoteInterface = string;
    }

    /**
     * @param string
     */
    public void setImplBean(String string) {
        implBean = string;
    }

}
