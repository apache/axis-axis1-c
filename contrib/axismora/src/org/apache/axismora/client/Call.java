/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

package org.apache.axismora.client;

import java.net.MalformedURLException;
import java.net.URL;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.xml.messaging.URLEndpoint;
import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

import org.apache.axismora.MessageContext;
import org.apache.axismora.encoding.InParameter;
import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.transport.HTTPSender;
import org.apache.axismora.wrappers.simpleType.BooleanParam;
import org.apache.axismora.wrappers.simpleType.ByteParam;
import org.apache.axismora.wrappers.simpleType.CharParam;
import org.apache.axismora.wrappers.simpleType.DoubleParam;
import org.apache.axismora.wrappers.simpleType.FloatParam;
import org.apache.axismora.wrappers.simpleType.IntParam;
import org.apache.axismora.wrappers.simpleType.ShortParam;
import org.apache.axismora.wrappers.simpleType.StringParam;

import org.apache.axis.AxisFault;
import org.apache.axis.enum.Style;
import org.apache.axis.soap.SOAPConstants;

/**
 * This calss implements the JAX-RPC  call interace. There are few methods we do 
 * not need yet. We have to decide between JAX-RPC client side support and or leaving 
 * few methods alone.
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class Call implements javax.xml.rpc.Call {
    /* the end point URI of the server*/
    private URLEndpoint endpointURI;
    /* the service name the client calls */
    private QName soapAction;
    /* name of the method the client invokes */
    private QName methodName;
    /* xml name of the return type*/
    private QName returnType;
    /* java class naem of the return type. i return type is a basic type 
      the wrapper class is used e.g. int -> Integer*/
    private Class returnJavaType;
    /* list of the parameters to the method */
    private ArrayList inParams;
    /* the axis engine use to invoke the method */
    private AxisClient engine;
    /* if authentication used the username */
    private String username;
    /* if authentication used the passwd */
    private char[] passwd;

    private Style style;

    private SOAPConstants constants = SOAPConstants.SOAP12_CONSTANTS;

    private String encoding;

    public Call(AxisClient engine) {
        this.engine = engine;
        inParams = new ArrayList();
    }

    /**
     * @see javax.xml.rpc.Call#addParameter(java.lang.String, javax.xml.namespace.QName, java.lang.Class, javax.xml.rpc.ParameterMode)
     */
    public void addParameter(
        String paramName,
        QName xmlType,
        Class javaType,
        ParameterMode parameterMode) {
        inParams.add(
        	new InputParameterInfo(paramName, null, xmlType, javaType, parameterMode));
    }

    /**
     * @see javax.xml.rpc.Call#addParameter(java.lang.String, javax.xml.namespace.QName, javax.xml.rpc.ParameterMode)
     */
    public void addParameter(String paramName, 
    				QName xmlType, ParameterMode parameterMode) {
        addParameter(paramName, xmlType, null, parameterMode);

    }

    /**
     * @see javax.xml.rpc.Call#getOperationName()
     */
    public QName getOperationName() {
        return this.methodName;
    }

    /**
     * @see javax.xml.rpc.Call#getOutputParams()
     */
    public Map getOutputParams() {
        // TODO Auto-generated method stub
        return null;
    }

    /**
     * @see javax.xml.rpc.Call#getOutputValues()
     */
    public List getOutputValues() {
        // TODO Auto-generated method stub
        return null;
    }

    /**
     * @see javax.xml.rpc.Call#getParameterTypeByName(java.lang.String)
     */
    public QName getParameterTypeByName(String paramName) {
        // TODO Auto-generated method stub
        return null;
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#getPortTypeName()
     */
    public QName getPortTypeName() {
        return soapAction;
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#getProperty(java.lang.String)
     */
    public Object getProperty(String name) {
        return this.engine.getOption(name);
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#getPropertyNames()
     */
    public Iterator getPropertyNames() {
        // TODO how to implements this ???????
        return null;
    }

    /**
     * @see javax.xml.rpc.Call#getReturnType()
     */
    public QName getReturnType() {
        return this.returnType;
    }

    /**
     * @see javax.xml.rpc.Call#getTargetEndpointAddress()
     */
    public String getTargetEndpointAddress() {
        return this.endpointURI.getURL();
    }

    /**
     * @see javax.xml.rpc.Call#invoke(java.lang.Object[])
     */
    public Object invoke(Object[] inputParams) throws RemoteException {
        return this.invoke(this.methodName, inputParams);
    }

    /** 
     * This function is for the extending the functionality for the  invokeLowLevel()
     * method. It make the interface supports the JAX-RPC
     * @see javax.xml.rpc.Call#invoke(javax.xml.namespace.QName, java.lang.Object[])
     */
    public Object invoke(QName operationName, Object[] inputParams)
    	throws RemoteException {
        try {
            if (inputParams.length != this.inParams.size())
                throw new AxisFault("the parameter given dos not macth with information(QName|parameter name) given before ");
            if (inputParams.length == 0 || !(inputParams[0] instanceof OutParameter))
                throw new AxisFault("you can pass only OutParameters as parameters");

            MessageContext context = invokeLowLevel(operationName, (OutParameter[]) inputParams);
            if (this.returnJavaType == null)
                throw new AxisFault("reurn java type not specified");
            InParameter out = null;
            if (Integer.class.equals(returnJavaType))
                out = new IntParam(context);
            else if (Double.class.equals(returnJavaType))
                out = new DoubleParam(context);
            else if (Double.class.equals(returnJavaType))
                out = new DoubleParam(context);
            else if (Float.class.equals(returnJavaType))
                out = new FloatParam(context);
            else if (Short.class.equals(returnJavaType))
                out = new ShortParam(context);
            else if (Character.class.equals(returnJavaType))
                out = new CharParam(context);
            else if (Byte.class.equals(returnJavaType))
                out = new ByteParam(context);
            else if (String.class.equals(returnJavaType))
                out = new StringParam(context);
            else if (Boolean.class.equals(returnJavaType))
                out = new BooleanParam(context);
            else if (java.math.BigDecimal.class.equals(returnJavaType))
                out = null; //TODO set value 
            else if (java.math.BigInteger.class.equals(returnJavaType))
                out = null; //TODO set value	
            else if (java.util.Calendar.class.equals(returnJavaType))
                out = null; //TODO set value
            else if (java.util.Date.class.equals(returnJavaType))
                out = null; //TODO set value
            else {
                out = (InParameter) returnJavaType.newInstance();
                out.desierialize(context);
            }
            //TODO check 4 all the types

            return out;
        } catch (InstantiationException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }
    /**
     * This method is the real implementation for a engine with the XMLPullparser.
     * It return the Message data and the genarated stub with the knowladge of the 
     * return type can parse it easier.
     * @param operationName
     * @param inputParams
     * @return
     * @throws RemoteException
     */

    public MessageContext invokeLowLevel(QName operationName, OutParameter[] inputParams)
        throws RemoteException {
        if (operationName == null)
            throw new AxisFault("the methodname to invoke must be specified");
        if (endpointURI == null)
            throw new AxisFault("the endpont uri must be specified");

        try {
            InputParameterInfo[] inInfo = new InputParameterInfo[this.inParams.size()];

            for (int i = 0; i < inParams.size(); i++) {
                inInfo[i] = ((InputParameterInfo) this.inParams.get(i));
                inInfo[i].setOutparam(inputParams[i]);

            }
            HTTPSender sender =
                new HTTPSender(
                    new URL(this.endpointURI.getURL()),
                    username,
                    passwd,
                    this.soapAction,
                    constants);

            ClientRequestContext reqContext =
                new ClientRequestContext(sender, soapAction, 
                			methodName, inInfo, style, encoding);
            return this.engine.processClient(reqContext);
        } catch (MalformedURLException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#invokeOneWay(java.lang.Object[])
     */
    public void invokeOneWay(Object[] params) {
        // TODO Auto-generated method stub

    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#isParameterAndReturnSpecRequired(javax.xml.namespace.QName)
     */
    public boolean isParameterAndReturnSpecRequired(QName operationName) {
        // TODO Auto-generated method stub
        return false;
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#removeAllParameters()
     */
    public void removeAllParameters() {
        // TODO Auto-generated method stub

    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#removeProperty(java.lang.String)
     */
    public void removeProperty(String name) {
        // TODO Auto-generated method stub
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#setOperationName(javax.xml.namespace.QName)
     */
    public void setOperationName(QName operationName) {
        this.methodName = operationName;
    }

    /**
     * @see javax.xml.rpc.Call#setPortTypeName(javax.xml.namespace.QName)
     */
    public void setPortTypeName(QName portType) {
        this.soapAction = portType;
    }

    /**
     * @see javax.xml.rpc.Call#setProperty(java.lang.String, java.lang.Object)
     */
    public void setProperty(String name, Object value) {
        this.engine.setOption(name, value);
    }

    /**
     * @see javax.xml.rpc.Call#setReturnType(javax.xml.namespace.QName, java.lang.Class)
     */
    public void setReturnType(QName xmlType, Class javaType) {
        this.returnJavaType = javaType;
        this.returnType = xmlType;
    }

    /**
     * @see javax.xml.rpc.Call#setReturnType(javax.xml.namespace.QName)
     */
    public void setReturnType(QName xmlType) {
        this.returnType = xmlType;
    }

    /* (non-Javadoc)
     * @see javax.xml.rpc.Call#setTargetEndpointAddress(java.lang.String)
     */
    public void setTargetEndpointAddress(String address) {
        this.endpointURI = new URLEndpoint(address);
    }
    public void setSOAPVersion(SOAPConstants constants) {
        this.constants = constants;
    }

    /**
     * @param cs
     */
    public void setPasswd(char[] cs) {
        passwd = cs;
    }

    /**
     * @param class1
     */
    public void setReturnJavaType(Class class1) {
        returnJavaType = class1;
    }

    /**
     * @param string
     */
    public void setUsername(String string) {
        username = string;
    }

    /**
     * @param name
     */
    public void setStyle(Style st) {
        style=st;
    }}
