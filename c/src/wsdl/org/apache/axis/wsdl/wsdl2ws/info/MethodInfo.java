/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * This Class represents a method (operation is wsdl) in a web service 
 * class.
 * @author Srinath Perera(hemapani@opensource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.xml.namespace.QName;

public class MethodInfo {
    private String methodname;
    private ArrayList inputParameters;
    private ArrayList outputParameters;
    private String soapAction;
    private List inputEncoding;
    private List outputEncoding;
    private String inputUse;
    private String outputUse;
    private QName inputMessage;
    private QName outputMessage;

    public MethodInfo() {
        this.methodname = null;
        inputParameters = new ArrayList(101);
		outputParameters = new ArrayList(101);
    }

    public MethodInfo(String methodname) {
        this.methodname = methodname;
        inputParameters = new ArrayList(101);
		outputParameters = new ArrayList(101);
    }

    public String getMethodname() {
        return methodname;
    }

    public void setMethodname(String methodname) {
        this.methodname = methodname;
    }
/*
    public Enumeration getParameters() {
        return this.parameters.keys();
    }
*/
    public Collection getInputParameterTypes() {
        return this.inputParameters;
    }

    public void addInputParameter(ParameterInfo type) {
        this.inputParameters.add(type);
    }

	public Collection getOutputParameterTypes() {
		return this.outputParameters;
	}

	public void addOutputParameter(ParameterInfo type) {
		this.outputParameters.add(type);
	}
    
/*
    public ParameterInfo getParameter(String paramName) {
        Object obj = this.parameters.get(paramName);
        if (obj != null)
            return (ParameterInfo) obj;
        return null;
    }
*/
    /**
     * @return
     */
    public List getInputEncoding() {
        return inputEncoding;
    }

    /**
     * @return
     */
    public List getOutputEncoding() {
        return outputEncoding;
    }

    /**
     * @return
     */
    public String getSoapAction() {
        return soapAction;
    }

    /**
     * @param string
     */
    public void setInputEncoding(List string) {
        inputEncoding = string;
    }

    /**
     * @param string
     */
    public void setOutputEncoding(List string) {
        outputEncoding = string;
    }

    /**
     * @param string
     */
    public void setSoapAction(String string) {
        soapAction = string;
    }

    /**
     * @return
     */
    public String getInputUse() {
        return inputUse;
	}
    /**
     * @return
     */
    public String getOutputUse() {
        return outputUse;
    }

    /**
     * @param string
     */
    public void setInputUse(String string) {
        inputUse = string;
    }

    /**
     * @param string
     */
    public void setOutputUse(String string) {
        outputUse = string;
    }
	/**
	 * @return QName
	 */
	public QName getInputMessage() {
		return inputMessage;
	}

	/**
	 * @return QName
	 */
	public QName getOutputMessage() {
		return outputMessage;
	}

	/**
	 * Sets the inputMessage.
	 * @param inputMessage The inputMessage to set
	 */
	public void setInputMessage(QName inputMessage) {
		this.inputMessage = inputMessage;
	}

	/**
	 * Sets the ouputMessage.
	 * @param ouputMessage The ouputMessage to set
	 */
	public void setOutputMessage(QName ouputMessage) {
		this.outputMessage = ouputMessage;
	}

}
