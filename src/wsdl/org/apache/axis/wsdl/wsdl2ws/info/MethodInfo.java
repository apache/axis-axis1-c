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

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.Parameters;

public class MethodInfo
{
    private String methodname;
    private Parameters operationParameters;
    private ArrayList inputParameters;
    private ArrayList outputParameters;
    private String soapAction = null;
    private QName inputMessage;
    private QName outputMessage;
    private QName faultMessage;
    private ArrayList faultType;
    private String inputNamespaceURI = null;

    private boolean eligibleForWrapped=true;
    private boolean doUnwrapped=false;
    private boolean consumeBodyOnMessageValidation=true;

    public MethodInfo(String methodname)
    {
        this.methodname = methodname;
        inputParameters = new ArrayList(101);
        outputParameters = new ArrayList(101);
        faultType = new ArrayList(102);
    }

    public String getMethodname()
    {
        return methodname;
    }

    public Collection getInputParameterTypes()
    {
        return this.inputParameters;
    }

    public Collection getFaultType()
    {
        return this.faultType;
    }

    public void addFaultType(FaultInfo faultType)
    {
        this.faultType.add(faultType);
    }

    public void addInputParameter(ParameterInfo type)
    {
        this.inputParameters.add(type);
    }

    public Collection getOutputParameterTypes()
    {
        return this.outputParameters;
    }

    public void addOutputParameter(ParameterInfo type)
    {
        this.outputParameters.add(type);
    }

    public String getSoapAction()
    {
        return soapAction;
    }

    public void setSoapAction(String string)
    {
        soapAction = string;
    }

    public void setInputNamespaceURI(String string)
    {
        inputNamespaceURI = string;
    }

    public String getInputNamespaceURI()
    {
        return inputNamespaceURI;
    }

    public QName getInputMessage()
    {
        return inputMessage;
    }

    public QName getOutputMessage()
    {
        return outputMessage;
    }

    public void setInputMessage(QName inputMessage)
    {
        this.inputMessage = inputMessage;
    }

    public void setOutputMessage(QName ouputMessage)
    {
        this.outputMessage = ouputMessage;
    }

    public QName getFaultMessage()
    {
        return faultMessage;
    }

    public void setFaultMessage(QName faultMessage)
    {
        this.faultMessage = faultMessage;
    }

    public void setOperationParameters(Parameters opParams)
    {
        operationParameters = opParams;
    }

    public Parameters getOperationParameters()
    {
        return operationParameters;
    }

    public void setEligibleForWrapped(boolean wrapped)
    {
        this.eligibleForWrapped = wrapped;
    }
    
    public boolean isEligibleForWrapped()
    {
        return eligibleForWrapped;
    }
    
    public void setIsUnwrapped(boolean unwrapped)
    {
        this.doUnwrapped = unwrapped;
    }
    
    public boolean isUnwrapped()
    {
        return doUnwrapped;
    }

    public boolean consumeBodyOnMessageValidation()
    {
        return consumeBodyOnMessageValidation;
    }

    public void setConsumeBodyOnMessageValidation(boolean b)
    {
        this.consumeBodyOnMessageValidation = b;
    }
}
