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

package org.apache.axismora.soap;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.StringReader;
import java.io.StringWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axismora.MessageContext;
import org.apache.axismora.ServicePool;
import org.apache.axismora.client.ClientRequestContext;
import org.apache.axismora.client.InputParameterInfo;
import org.apache.axismora.client.RequestBodyContent;
import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.encoding.DesirializationContext;
import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.encoding.Serializable;
import org.apache.axismora.provider.result.DocLiteralResult;
import org.apache.axismora.provider.result.HandlerResetResult;
import org.apache.axismora.provider.result.MSGResult;
import org.apache.axismora.provider.result.RPCResult;
import org.apache.axismora.util.AxisUtils;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.enum.Style;
import org.apache.axis.message.SOAPBody;
import org.apache.axis.message.SOAPBodyElement;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.message.SOAPHeaderElement;
import org.apache.axis.session.Session;
import org.apache.axis.soap.SOAPConstants;
import org.apache.commons.logging.Log;
import org.w3c.dom.Element;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

/**
 * This is the Concreate implementation of MessageContext 
 * @author Dimuthu Leelarathne
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class BasicMessageContext implements MessageContext {
    /* correct set of SOAP constants */
    public static SOAPConstants SOAP_CONSTANTS;
    protected static Log log = LogFactory.getLog(BasicMessageContext.class.getName());
    /* desirealization Context  */
    private DesirializationContext deserializer;
    /* Store the SOAPFault if SoapFault has occured */
    private SOAPFault soapFault;
    /* indicate weather SOAPFault has occured */
    private boolean hasSoapFault;
    /* name of the method(operation) that should be invoked may be 
       null for the some webservice styles */
    private QName methodName;

    /* All recived SOAP Headers */
    private Vector soapHeaderElements;
    /* SOAPHeaders created in this SOAPNode */
    private Vector createdSoapHeaders;
    /* recived SOAP envelope (only the envelope the content is not stored here)*/
    private SOAPEnvelope soapEnvelope;
    /* response SOAPBody .. do we need this ???? */
    private SOAPBody soapBody;
    /* The output stream to which the response should be written */
    private OutputStream outStream;
    /* processed result of by the provider */
    private Serializable resultValue;

    /* information about this SOAP Node */
    private SOAPNodeInfo nodeinfo;
    /* Service under processing */
    private WSDDService service;
    /* SOAP version do we need this ???*/
    private int soapVersion;
    /* serializer of the result */
    private SerializationContext serializer;
    /* Service Style */
    private Style style;

    private Writer w;

    /* Authentication detail */
    private String usrname;
    private char[] password;

    /* Session given by the Server ... the current Session in progress */
    private Session currentSession;
    private boolean sessionaware = true;
    private final int ELEMENT_MAP_SIZE = 101;
    /**
     *  servicepool stores the Service objects (wrapper ect...)
     */
    private org.apache.axismora.ServicePool servicepool;

    /**
     * this is the property discribes by the jax-rpc you can get and set values
     */
    private Hashtable propertyMap;
    private final int PROPERTY_MAP_SIZE = 101;
    /* Indicate processing is done at the wrapper/Service or not */
    private boolean atPivot = false;
    /* indicate has the engine pass pivot point */
    private boolean passPivot = false;
    // the encoding style of the input Stream
    private String streamEncoding;
    //indicate at server side or the client side
    private boolean atServerSide;
    //indicate to use literal or encoded
    private boolean isLiteral=false;
	/**
	 * this Constructor is for the sake of testing only
	 */
	public BasicMessageContext(){}	

    public BasicMessageContext(
        InputStream inStream,
        OutputStream outStream,
        SOAPNodeInfo nodeinfo,
        WSDDService service,
        ServicePool servicepool,
        Session currentSession,
        String streamEncoding)
        throws AxisFault {

        this.servicepool = servicepool;
        this.currentSession = currentSession;
        this.propertyMap = new Hashtable(PROPERTY_MAP_SIZE);
        this.nodeinfo = nodeinfo;
        this.service = service;
        this.outStream = outStream;
        this.soapHeaderElements = new Vector(ELEMENT_MAP_SIZE);
        this.createdSoapHeaders = new Vector(ELEMENT_MAP_SIZE);
        this.streamEncoding = streamEncoding;
        this.methodName = service.getQName();
        this.style = service.getStyle();
        //initialize desirialization context - this drives the desiarialization
        this.deserializer =
            new DesirializationContext(
                this,
                inStream,
                (service != null ? this.service.getStyle() : null));

        w = new OutputStreamWriter(this.outStream);
        /*
          initializing the serialization context
          This is comlpletly borrowed from existing Apache Axis. this drives all the serialization.
          The implementation  uses on the Envelope,Header and the Body of the org.apache.axis.message
          serializzation of these naturally followed the existing model.
        */
        serializer = new SerializationContextImpl(w);

        log.info("MessageContext created.......");

    }

    public BasicMessageContext(
        SOAPNodeInfo nodeinfo,
        WSDDService service,
        ServicePool servicepool,
        ClientRequestContext requestContext)
        throws AxisFault {
        this.propertyMap = new Hashtable(PROPERTY_MAP_SIZE);
        this.soapHeaderElements = new Vector(ELEMENT_MAP_SIZE);
        this.createdSoapHeaders = new Vector(ELEMENT_MAP_SIZE);

        this.servicepool = servicepool;
        this.currentSession = null;

        this.nodeinfo = nodeinfo;
        this.service = service;
        this.outStream = requestContext.getSender().getOut();
        this.streamEncoding = requestContext.getEncoding();
        this.style=service.getStyle();
        //initialize desirialization context - this drives the desiarialization
        this.deserializer =
            new DesirializationContext(
                this,
                requestContext.getSender().getIn(),
                requestContext.getStyle());

        w = new OutputStreamWriter(this.outStream);
        /*
          initializing the serialization context
          This is comlpletly borrowed from existing Apache Axis. this drives all the serialization.
          The implementation  uses on the Envelope,Header and the Body of the org.apache.axis.message
          serializzation of these naturally followed the existing model.
        */
        serializer = new SerializationContextImpl(w);

        log.info("MessageContext created.......");

    }

    public void parseAndValidateKnownTags() throws AxisFault {
        //parse the envelope and headers
        this.deserializer.parseKnownTags();
        /* Check for Must Understand SOAPFault */
        checkMustUnderstandFault();
    }

    public void setService(WSDDService ser) {
        this.service = ser;
    }

    public WSDDService getService() {
        return this.service;
    }

    public boolean hasSoapFault() {
        return hasSoapFault;
    }

    /**
     * This will set hasSoapFault true,will be detected by the Axis engine and start
     * driving handlers back on <code>onFault()</code>
     * @param pSoapFault
     */

    public void setSoapFault(SOAPFault pSoapFault) {
        hasSoapFault = true;
        this.soapFault = pSoapFault;
    }

    public SOAPFault getFault() {
        return this.soapFault;
    }

    //	public String getNamespacePrefix(){}

    public void setSoapVersion(int i) {
        this.soapVersion = i;
    }

    public int getVersion() {
        return this.soapVersion;
    }

    public boolean setSoapBodyContent(Object result) throws AxisFault {
        System.out.println(""+this.style.getName());
        if (result instanceof OutParameter){
           if(this.style.getName().equals("document")){
                this.resultValue = new DocLiteralResult((OutParameter)result);
           }else this.resultValue = new RPCResult((OutParameter) result, this.methodName);	
        }else if (result instanceof Element[])
            this.resultValue = new MSGResult((Element[]) result);
        else if (result instanceof InputParameterInfo[])
            this.resultValue =
                new RequestBodyContent((InputParameterInfo[]) result, this.methodName);
        else
            throw new AxisFault("unknown result type set to message Context");
        return true;
    }

    public QName getMethodName() {
        return this.methodName;
    }

    public void setMethodName(QName mName) {
        this.methodName = mName;
    }

    /**
     *  This is blind reading.
     *  @see <code>DesirializationContext#getvalue()</code>
     */
    public String getValue() throws IOException, XmlPullParserException {
        return this.deserializer.getValue();
    }

    public String getValue(String uri, String localpart) throws AxisFault {
        return this.deserializer.getValue(uri, localpart);
    }

    public org.apache.axismora.ServicePool getServicePool() {
        return this.servicepool;
    }

    public AxisDeployment getDeployment() {
        return this.nodeinfo.getDeployment();
    }

    public Session getSession() {
        if (!sessionaware)
            return null;
        return this.currentSession;
    }

    //this is all reading
    public XMLTextData getTag() throws AxisFault {
        return deserializer.getTag();
    }

    public boolean addSoapHeader(SOAPHeaderElement pSoapHeader) {
        //return this.soapHeaderElements.add(pSoapHeader);
        return this.soapHeaderElements.add(pSoapHeader);
    }

    public boolean addHandlerCreatedSOAPHeader(SOAPHeaderElement pSoapHeader) {
        return this.createdSoapHeaders.add(pSoapHeader);
    }

    public Vector getHeadersByActor(ArrayList actors) {
        Vector headers = new Vector();

        Iterator it = this.soapHeaderElements.iterator();
        SOAPHeaderElement header;

        while (it.hasNext()) {
            header = (SOAPHeaderElement) it.next();
            if (this.getSOAPConstants().getNextRoleURI().equals(header.getActor())
                || actors.contains(header.getActor())) {
                headers.add(header);

            }
        }
        this.soapHeaderElements.removeAll(headers);
        return headers;
    }

    public ArrayList getSOAPHeaders(String actor, QName headername) {
        ArrayList selctHeaders = new ArrayList();
        SOAPHeaderElement header;

        for (int i = 0; i < this.soapHeaderElements.size(); i++) {
            header = ((SOAPHeaderElement) this.soapHeaderElements.get(i));
            /* if qname match and (role next or role matches) */
            if (header.getQName().equals(headername)
                && (this.getSOAPConstants().getNextRoleURI().equals(header.getActor())
                    || header.getActor().equals(actor))) {
                selctHeaders.add(header);
            }
        }
        this.soapHeaderElements.removeAll(selctHeaders);
        return selctHeaders;
    }

    /**
     * @param actor
     * @return  All the headers where actor maps with the actor or actor is next
     */
    public ArrayList getSOAPHeaders(String actor) {
        SOAPHeaderElement he;
        Iterator headers = this.soapHeaderElements.iterator();
        ArrayList headersToReturn = new ArrayList();
        while (headers.hasNext()) {
            he = (SOAPHeaderElement) headers.next();
            if (actor.equals(he.getActor())
                || this.getSOAPConstants().getNextRoleURI().equals(he.getActor())) {
                headersToReturn.add(he);
            }
        }
        this.soapHeaderElements.removeAll(headersToReturn);
        return headersToReturn;
    }

    public SOAPBody getBody() {
        return this.soapBody;
    }

    public SOAPEnvelope getEnvelope() {
        return this.soapEnvelope;
    }

    public void setSoapBody(SOAPBody pSoapBody) {
        this.soapBody = pSoapBody;
    }

    public void setSoapEnvelope(SOAPEnvelope pSoapEnvelope) {
        this.soapEnvelope = pSoapEnvelope;
    }

    public SerializationContext getSerializationContext() {
        return this.serializer;
    }
    public void startParseSOAPBody() throws AxisFault {
        this.deserializer.startParseSOAPBody();
    }

    public void setLitereal(boolean boo){
		isLiteral = boo;
    }
    
    
    /**
     * The serialization is done by the means adding the headers(they are kept separate up to the point)
     * and body to the envelope and calling the the <code>output(SerializationContext)</code> on the <code>SOAPEnvelope.</code>
     * We are Simply reusing the exisiting Aixs <code>SerializationContext</code>.
     * Note:- But you have to make sure the object value of the <code>SOAPHeaderElement</code> and <code>SOAPBodyElement</code>
     * should be such that the <code>SerializationContext</code> can find serializers for the values at the type mapping.
     * We achive this by adding two custom Serializers to the <code>Typemapping</code>
     * (change <code>DefaultTypeMappingImpl</code> add new registry entry as default or enable change the code dynamically)
     *
     * headers - content(objvalue) are as org.w3c.Element array inside <code>SOAPHeaderElementContent</code>
     * body - content(objvalue) as Result object
     */
    public void serialize() throws AxisFault {
        try {
            //if soap Envelope not set create a default one 
            if(this.soapEnvelope == null)
            	this.soapEnvelope = new SOAPEnvelope(); 
            
            //add the headers to the soap envelope
            Iterator headers = this.soapHeaderElements.iterator();
            SOAPHeaderElement header;
            
            if(this.isLiteral){
                 serializer.setDoMultiRefs(false);
                 serializer.setShouldSendXSIType(true);
            }
            /**
             *  recived headers are added if they are relay = true or not meant to
             *  This node.
            */
            for (; headers.hasNext();) {
                header = (SOAPHeaderElement) headers.next();
                if (header.getRelay()
                    || !nodeinfo.getAllRoles().contains(header.getActor()))
                    this.soapEnvelope.addHeader(header);
            }
            /* Add all the headers created at this node */
            Iterator newheaders = this.soapHeaderElements.iterator();
            for (; newheaders.hasNext();)
                this.soapEnvelope.addHeader((SOAPHeaderElement) newheaders.next());

            //add the soap body
            SOAPBodyElement bo = new SOAPBodyElement();

            if (!this.hasSoapFault)
                bo.setObjectValue(this.resultValue);
            else {
                //this works the testCase - Serialization Test testFault()
                this.soapEnvelope.getBody().addChildElement(this.soapFault);
            }

            this.soapEnvelope.addBodyElement(bo);

            ///specific to rpc
            if (this.methodName != null) {
                bo.setName(this.methodName.getLocalPart() + "Response");
                bo.setNamespaceURI(this.methodName.getNamespaceURI());
            }

            /*
               ** registor our Serializer **
               Add the Seralizer which can serialize a instance of result.
               The serializer added to the default type mapping
               1) used value is enable adding to default type mapping  edit the DefaultTypeMappingImpl ** used here **
               2) Add the Serializer as a default type mapping
               3) add dymnamically Still DONOT WORKING (Serialier not found exception) we might able to find a way !!!
                       TypeMappingRegistry reg = new TypeMappingRegistryImpl();
                       javax.xml.rpc.encoding.TypeMapping t = reg.getOrMakeTypeMapping("www.opensurce.lk/axis/encoding");
                       sc.getTypeMapping().register(Result.class , Constants.SOAP_RESULT,  new ResultSerializerFactory(),null);
                       t.register(Parameter.class , Constants.SOAP_RESULT,  new ResultSerializerFactory(),null);
             */

            /*	serializer.getTypeMapping().register(
            		Result.class,
            		Constants.SOAP_RESULT,
            		new ResultSerializerFactory(),
            		null);
            	serializer.getTypeMapping().register(
            		SOAPHeaderElementContent.class,
            		Constants.SOAP_BODY_ELEMENT_CONTENT,
            		new SOAPHeaderElementContentSerializerFactory(),
            		null); */

            //print the message to the output
            this.soapEnvelope.output(serializer);
            this.w.flush();

        } catch (Exception e) {
            e.printStackTrace();
            throw new AxisFault("error at serialization", e);
        }

    }

    public void resetBlindLevel() {
        this.deserializer.resetBlindLevel();
    }

    public void setStyle(Style style) {
        this.style = style;
    }

    public String getUser() {
        return usrname;
    }

    public void setUser(String usrname) {
        this.usrname = usrname;
    }

    public char[] getPassword() {
        return password;
    }

    public void setPassword(char[] password) {
        this.password = password;
    }

    public void setProperty(String name, Object value) {
        this.propertyMap.put(name, value);
    }

    public Object getProperty(String name) {
        return this.propertyMap.get(name);
    }

    public void removeProperty(String name) {
        this.propertyMap.remove(name);
    }

    public boolean containsProperty(String name) {
        return this.propertyMap.containsKey(name);
    }

    public Iterator getPropertyNames() {
        return this.propertyMap.keySet().iterator();
    }

    public XmlPullParser getBodyParser() throws AxisFault {

        try {
            /* if this is called not at the pivot, unless the user return the parser the execution will fail at once due to soap fault.
              This will make sure the parser return with in current handler */
            this.hasSoapFault = !(!atPivot && !passPivot);
            if (hasSoapFault)
                this.soapFault =
                    new SOAPFault(
                        new AxisFault("Handler has taken the parser and have not return: cant find body "));
            if (!passPivot)
                return this.deserializer.getParser();
            else {
                StringWriter w = new StringWriter();
                SerializationContext sc = new SerializationContextImpl(w);
                resultValue.serialize(sc);
                StringBuffer buf = w.getBuffer();

                //k... then go until the body tag and have the pull parser curser Where it should have
                XmlPullParser xpp = this.deserializer.getParser();
                xpp.setInput(new StringReader(buf.toString()));
                return xpp;
            }
        } catch (Exception e) {
            throw AxisUtils.getTheAixsFault(
                Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                this.nodeinfo.getDeployment(),
                null,
                e);
        }
    }
    public String getBodyString() throws AxisFault {
        try {
            /* if this is called not at the pivot, unless the user return the parser the execution will fail at once due to soap fault.
              This will make sure the parser return with in current handler */
            this.hasSoapFault = !(!atPivot && !passPivot);
            StringWriter w = new StringWriter();
            SerializationContext sc = new SerializationContextImpl(w);
            if (hasSoapFault)
                this.soapFault =
                    new SOAPFault(
                        new AxisFault("Handler has taken the parser and have not return: cant find body "));
            if (!passPivot) {
                //if pivot has not passes create DOM element and serialise it to writer
                sc.writeDOMElement(AxisUtils.make(this.deserializer.getParser()));
                return w.getBuffer().toString();
            } else {
                //if pivot has passed serialize the result to the writer
                resultValue.serialize(sc);
                //return what write to writer
                StringBuffer buf = w.getBuffer();
                return buf.toString();
            }
        } catch (Exception e) {
            throw AxisUtils.getTheAixsFault(
                Constants.FAULT_SOAP12_RECEIVER,
                "error at get body parser",
                this.nodeinfo.getDeployment(),
                null,
                e);
        }
    }

    public void resetBody(String str) {
        try {
            //if pivot is passed reset the with new result value
            if (passPivot) {
                this.resultValue = new HandlerResetResult(str);
                //we are done
                return;
            }
            //else create new XMLPullParser
            StringBuffer buf = new StringBuffer();
            //get soap envelope as a String and put it to a buffer
            buf.append(this.soapEnvelope.toString());

            String prefix = this.soapEnvelope.getPrefix();
            String startEndBodyTag =
                "<" + prefix + ":" + org.apache.axis.Constants.ELEM_BODY + "/>";
            String startBodyTag =
                "<" + prefix + ":" + org.apache.axis.Constants.ELEM_BODY + ">";
            String endBodyTag =
                "</" + prefix + ":" + org.apache.axis.Constants.ELEM_BODY + ">";

            //replace the body in the buffer with returned body
            int state = buf.indexOf(startEndBodyTag);
            //is it a <body/> tag
            if (state != -1) {
                buf.delete(state, state + startEndBodyTag.length());
                buf.insert(state, startBodyTag + str + endBodyTag);
                //or is it a <body></body>
            } else {
                state = buf.indexOf(endBodyTag);
                if (state != -1)
                    buf.insert(state - 1, str);
                else
                    //nothing ???
                    throw new AxisFault("illegal envelope");
            }

            //k... then go until the body tag and have the pull parser cursor 
            //Where it should have
            XmlPullParser xpp = this.deserializer.getParser();
            xpp.setInput(new StringReader(buf.toString()));

            state = xpp.next();
            while (state != XmlPullParser.END_DOCUMENT) {
                if (state == XmlPullParser.START_TAG
                    && xpp.getName().equals(org.apache.axis.Constants.ELEM_BODY)
                    && xpp.getNamespace().equals(this.soapEnvelope.getNamespaceURI()))
                    break;
                state = xpp.next();
            } //while

            this.deserializer.setState(state);

            this.hasSoapFault = false;
            this.soapFault = null;

        } catch (Exception e) {
            e.printStackTrace();
            this.setSoapFault(
                new SOAPFault(
                    AxisUtils.getTheAixsFault(
                        Constants.FAULT_SOAP12_RECEIVER,
                        "error reset body",
                        this.nodeinfo.getDeployment(),
                        null,
                        e)));
        }

    }

    /**
     * All the roles this SOAPNode plays
     */
    public Vector getRoles() {
        return new Vector(nodeinfo.getAllRoles());
    }

    /* (non-Javadoc)
     * @see lk.opensource.service.MessageData#getSOAPConstants(org.apache.axis.soap.SOAPConstants)
     */
    public SOAPConstants getSOAPConstants() {
        return SOAP_CONSTANTS;
    }

    /* (non-Javadoc)
     * @see lk.opensource.service.MessageData#setSOAPConstants(org.apache.axis.soap.SOAPConstants)
     */
    public void setSOAPConstants(SOAPConstants soapConstants) {
        SOAP_CONSTANTS = soapConstants;
    }

    /* (non-Javadoc)
     * @see lk.opensource.service.MessageData#isAtPivot()
     */
    public boolean isAtPivot() {
        return this.atPivot;
    }

    /* (non-Javadoc)
     * @see lk.opensource.service.MessageData#setAtPivot(java.lang.Boolean)
     */
    public void setAtPivot(boolean atPivot) {
        this.atPivot = atPivot;

    }

    public boolean isPassPivot() {
        return passPivot;
    }

    public void setPassPivot(boolean b) {
        passPivot = b;
    }
    /**
     *  This method Checks weather there is must understand fault and throw AxisFault if that is the case
     *  precondition - soapHeaderElementValues are set (it is not null)
     */
    private void checkMustUnderstandFault() throws AxisFault {
        Iterator headers = this.soapHeaderElements.iterator();
        SOAPHeaderElement header;
        ArrayList roles = nodeinfo.getAllRoles();
        ArrayList headersUnderstand = nodeinfo.getAllUnderstandHeaders();
        while (headers.hasNext()) {
            header = (SOAPHeaderElement) headers.next();
            if (header.getMustUnderstand()
                && (roles.contains(header.getActor())
                    || this.getSOAPConstants().getNextRoleURI().equals(header.getActor()))
                && !headersUnderstand.contains(header.getQName()))
                throw AxisUtils.getTheAixsFault(
                    this.getSOAPConstants().getMustunderstandFaultQName(),
                    "must understand fault occures",
                    nodeinfo.getDeployment(),
                    null,
                    null);
        }
    }
    /**
     * @return
     */
    public String getStreamEncoding() {
        return streamEncoding;
    }

    /**
     * @param string
     */
    public void setStreamEncoding(String string) {
        streamEncoding = string;
    }

    /**
     * @return
     */
    public boolean isAtServerSide() {
        return atServerSide;
    }

    /**
     * @param b
     */
    public void setAtServerSide(boolean b) {
        atServerSide = b;
    }

    public void check4SOAPFault() throws AxisFault {
        this.deserializer.check4SOAPFault();
    }

    public String nextText() throws AxisFault {
        return deserializer.nextText();
    }

	/**
	 * @return
	 */
	public DesirializationContext getDeserializer() {
		return deserializer;
	}

}
