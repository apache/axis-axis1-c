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

package org.apache.axismora;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.soap.XMLTextData;

import org.apache.axis.AxisFault;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.message.SOAPHeaderElement;
import org.apache.axis.session.Session;
import org.apache.axis.soap.SOAPConstants;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
/**
 * @author Dimuthu Leelarathne(muthulee@openosource.lk)
 */
public interface MessageContext extends javax.xml.rpc.handler.MessageContext {
    /**
     *  set the Serivce currently under processing
     */
    public void setService(WSDDService ser);
    /**
     *  get the Serivce currently under processing
     */
    public WSDDService getService();
    /**
     * does a soapfault has occured in processing so far
     */
    public boolean hasSoapFault();
    /**
     * Add SOAPFault to the MessageData
     * @param pSoapFault
     */
    public void setSoapFault(SOAPFault pSoapFault);
    /**
     * get the SOAPFault
     * @return  SOAPFault Element
     */
    public SOAPFault getFault();
    /**
     * set the SOAPVersion of the SOAP request undergoing processing
     * @param i soapversion as integer
     */
    public void setSoapVersion(int i);
    /**
     * set the SOAPVersion of the SOAP request undergoing processing
     * @return soapversion as integer
     */
    
	/**
	 * Tells the serializer to use literal encoding. 
	 */
	public void setLitereal(boolean boo);
    
    public int getVersion();
    /**
     * Set the result of the execution at the pivot point It must be either Parameter
     * or a org.w3c.Element[].
     * @param result
     * @return
     */
    public boolean setSoapBodyContent(Object result) throws AxisFault;
    /**
     * get the name of the method (wsdl operation) invoke by this requst
     * @return method name as QName
     */
    public QName getMethodName();
    /**
     * get the name of the method (wsdl operation) invoke by this requst
     * @param mName as QName
     */
    public void setMethodName(QName mName);

    /**
     *  This method reads form XML tag pair start and end tags.
     *  @return return first non whitespace text found bitween two start and end tags.
     *  White space defined in the same context the XmlPull define it.
     */
    public String getValue() throws IOException, XmlPullParserException;
    /**
     * equalent to the getValue() but return null if it finds the end element given by
     * URI and Localpart before the test (value) is find.
     * @param uri
     * @param localpart
     * @return  the value or null
     * @throws AxisFault
     */
    public String getValue(String uri, String localpart) throws AxisFault;
    /* this method return all the information about next tag find in the documet */
    public XMLTextData getTag() throws AxisFault;
    /* add SOAP header from request to the MessageData*/
    public boolean addSoapHeader(SOAPHeaderElement pSoapHeader);
    /* add header created by this node to the MeassageData. They will not processed at this node */
    public boolean addHandlerCreatedSOAPHeader(SOAPHeaderElement pSoapHeader);
    /* get the SOAPEnvelope under processing */
    public SOAPEnvelope getEnvelope();
    /* set request SOAPEnvelope to the MessageData*/
    public void setSoapEnvelope(SOAPEnvelope pSoapEnvelope);
    /* create and write the response back to the sender*/
    public void serialize() throws AxisFault;
    /* get the serialiation context */
    public SerializationContext getSerializationContext();
    /**
     * get deployment configaration information
     * @return  AxisDeployment instance never return null
     */
    public AxisDeployment getDeployment();
    /**
     * get the current Session object passes by the Server
     * @return Session object or null if session not enabled
     */
    public Session getSession();

    /**
     * the service pool that have Services(wrappers) stored according to their scope
     */
    public org.apache.axismora.ServicePool getServicePool();
    /*set the user name*/
    public void setUser(String usr);
    /* get the user name */
    public String getUser();
    /* set the password */
    public char[] getPassword();
    /* get the pasword */
    public void setPassword(char[] passwd);
    /**
     *  This method let the user have the body. But then the MessageData donot have body
     *  The user must create a body from the info he read and set it back. Otherwise the execution
     *  will fail at once.
     *  This method is expensive at the response Flow.. This should be 
     *  used by in the request flow.
     */
    public XmlPullParser getBodyParser() throws AxisFault;
    /**
     *  This method return the SOAP message body as a String .. This method is
     *  Expensive ... specially at the request flow .. better to use this is 
     *  response flow.
     */
    public String getBodyString() throws AxisFault;
    /**
     * reset the process body to back to the masageData
     * @param str
     * @see this.getBodyParser()
     * @see this.getBodyString()
     */
    public void resetBody(String str);
    /**
     * get All the headers with the actor equal to the given actor or the
     * Actor is next
     * @param actors
     * @return  Vector() never return null, if no match return empty vector
     */
    public Vector getHeadersByActor(ArrayList actors);
    /**
     * get All the headers with the actor equal to the given actor or the
     * Actor is next and the header name is given header name
     * @param actor
     * @param headername
     * @return  Vector() never return null, if no match return empty vector
     */
    public ArrayList getSOAPHeaders(String actor, QName headername);
    /**
     * get All the headers with the actor equal to the given actor or the
     * Actor is next
     * @param actor
     * @return  Vector() never return null, if no match return empty vector
     */
    public ArrayList getSOAPHeaders(String actor);
    /**
     * start parsing the SOAP body .. if style is RPC the immediate chiled element
     * of the body is read for the method name
     * @throws AxisFault
     */
    public void startParseSOAPBody() throws AxisFault;
    /**
     * get the roles played by this SOAP node
     * @return
     */
    public Vector getRoles();
    /**
     * set the SOAPConstants mach with request SOAP version
     * @param soapConstants
     */
    public void setSOAPConstants(SOAPConstants soapConstants);
    /**
     * get the SOAPConstants mach with request SOAP version
     * @return soapConstants
     */
    public SOAPConstants getSOAPConstants();

    /**
     * indicate the current processing done at the service (pivot) not
     */
    public boolean isAtPivot();
    /**
     * Set whether message is at pivot or not
     * @param atPivot
     */
    public void setAtPivot(boolean atPivot);
    /**
     * pivot indicate the processing done at the service (pivot) not
     */
    public boolean isPassPivot();
    /**
     * pivot indicate the processing done at the service (pivot) not
     */
    public void setPassPivot(boolean b);

    /**
     * @return string giving the encoding style e.g. utf-8
     */
    public String getStreamEncoding();

    /**
     * @param string giving the encoding style e.g. utf-8
     */
    public void setStreamEncoding(String string);

    /**
     * indiacate the execution is at server side or not
     * @return
     */
    public boolean isAtServerSide();

    /**
     * sets the execution is at server side or not
     * @param b
     */
    public void setAtServerSide(boolean b);

    /**
     * parse SOAP Envelope and Headers
     * @throws AxisFault
     */
    public void parseAndValidateKnownTags() throws AxisFault;
    /**
     * Chaeck wheather the response have a SOAPFault
     * @throws AxisFault
     */
    public void check4SOAPFault() throws AxisFault;
    /**
     * remove the next value (if null if it is <xxx/> type of element)
     * between next immediadte pair of start and end tags.
     * e.g. <xx>a</xx> returns a
     * 		<xxx/> returns null
     * 		<xxx></xxx> returns null
     * 		<xax><xxx>e</xxx></xax> return e
     * @return non white space string or null
     * @throws AxisFault
     */
    public String nextText() throws AxisFault;
}