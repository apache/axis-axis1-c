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

package org.apache.axismora.encoding;

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.Vector;

import javax.xml.namespace.QName;
import javax.xml.parsers.FactoryConfigurationError;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.soap.SOAPException;

import org.apache.axismora.MessageContext;
import org.apache.axismora.soap.XMLTextData;
import org.apache.axismora.util.AxisUtils;
import org.apache.axismora.util.Parser2Element;
import org.apache.axismora.wsdl2ws.java.ParmWriter;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.enum.Style;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPHeaderElement;
import org.apache.axis.soap.SOAPConstants;
import org.apache.axis.utils.NSStack;
import org.apache.commons.logging.Log;
import org.w3c.dom.Attr;
import org.w3c.dom.DOMException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.AttributesImpl;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

/**
 * All the desirialization work is done in this class. The XmlPullParser is 
 * hidden behind this class.
 * 
 * @author Dimuthu Leelarathe (muthulee@opensource.lk)
 * @author Srianth Perera (hemapani@opensource.lk)
 * 
 */

public class DesirializationContext {

    private static Log log = LogFactory.getLog(DesirializationContext.class.getName());
    private SOAPConstants soapConstants = SOAPConstants.SOAP11_CONSTANTS;
    private MessageContext messageData;
    private int state;
    private XmlPullParser xpp;
    private QName method;
    //private QName provider;
    private Style style;
    private SOAPEnvelope env;
    /* use to create the xml elements */
    private Document doc;
	private Vector headers;
    private int blindLevel = 0; //reads until the same level you started

    public DesirializationContext(MessageContext md, InputStream ins, Style style)
        throws AxisFault {

        try {
            //get the common document
            this.doc = AxisUtils.getCommonDomDocument();

            this.messageData = md;
            this.style = Style.RPC;    
            this.method = null;

            InputStreamReader in = new InputStreamReader(ins);

            String streamEnc = (md != null?md.getStreamEncoding():null);
            XmlPullParserFactory factory =
                XmlPullParserFactory.newInstance(
                    System.getProperty(XmlPullParserFactory.PROPERTY_NAME),
                    null);
            factory.setNamespaceAware(true);
            factory.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, true);
            this.xpp = factory.newPullParser();
            xpp.setInput(in);
        } catch (FactoryConfigurationError e) {
            log.error(e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (ParserConfigurationException e) {
            log.error(e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (XmlPullParserException e) {
            log.error(e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        }
    }

    // this constructor is written for the sole purpose of unit testing.

    public DesirializationContext(String file) throws XmlPullParserException, IOException {
        XmlPullParserFactory factory = XmlPullParserFactory.newInstance();
        factory.setNamespaceAware(true);
        xpp = factory.newPullParser();
        xpp.setInput(new FileReader(file));
        this.state = xpp.next();
        System.out.println("Testing DesirializationContext ...." + xpp.getText());
    }

    /**
     * parse the Envelope, Headers and make nessesary conditions to deliver the message to the wrappers
     * The parsing is stop without parsing the <Body> tag. 
     * @throws AxisFault
     */
    public void parseKnownTags() throws AxisFault {
        try {
            this.state = this.xpp.next();
            //go till find a start tag do we need this ??? (presence do no harm)
            while (this.state != XmlPullParser.START_TAG)
                this.state = this.xpp.next();
            //now we are looking at the envelope
            this.env = this.createEnvelope();
            this.messageData.setSoapEnvelope(this.env);
            log.info("envelope creatd");

            // now we are looking at headers
            headers = this.createHeaders();
            log.info("headers creatd");

            SOAPHeaderElement header;
            for (int i = 0; i < headers.size(); i++) {
                header = (SOAPHeaderElement) headers.get(i);
                header.setEnvelope(env);
                this.messageData.addSoapHeader(header);
            }
            //we are done  if body is all right we will give the control to the wrappers.
        } catch (XmlPullParserException e) {
            log.error("error parsing known tags", e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (IOException e) {
            log.error("error parsing known tags", e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        }
    }

    public AxisPullParser getAxisPullParser() {
        return new AxisPullParser(this.xpp);
    }

    /**
     * Start Parse the Body. Parse the Body tag and if and only if RPC. 
     * First child element of the Body. 
     */
    public void startParseSOAPBody() throws AxisFault {
        try {
            // make sure I am at start tag
            while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                this.state = this.xpp.next();

            if (state == XmlPullParser.START_TAG && this.xpp.getName().equals(Constants.ELEM_BODY))
                this.state = this.xpp.next();
            else
                throw new AxisFault("Invalied Axis format Body tag missing");

            //If RPC I should read the method as well
            if (this.style.equals("rpc")) {
                //this two lines are to make sure we are dealing with the start tag
                while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                    this.state = this.xpp.next();
                if (this.state == XmlPullParser.END_DOCUMENT)
                    throw new AxisFault("parsing error Illegal format - method not specified ");
                this.method = new QName(this.xpp.getNamespace(), this.xpp.getName());
                this.messageData.setMethodName(this.method);
                //TODO removethis.state = this.xpp.next();
                ParmWriter.tag = getTag();
            }
            //ok sounds perfect, the control is passed to wrapper		
        } catch (AxisFault e) {
            log.error("error start parsing body ", e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                null,
                e);
        } catch (XmlPullParserException e) {
            log.error("error start parsing body ", e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                null,
                e);
        } catch (IOException e) {
            log.error("error start parsing body ", e);
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                null,
                e);
        }
    }
    public void check4SOAPFault() throws AxisFault {
        try {
            // make sure I am at start tag
            while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                this.state = this.xpp.next();

            if (state == XmlPullParser.START_TAG && this.xpp.getName().equals(Constants.ELEM_BODY))
                this.state = this.xpp.next();
            else
                throw new AxisFault("Invalied Axis format Body tag missing");

            //this two lines are to make sure we are dealing with the start tag
            while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                this.state = this.xpp.next();
            if (this.state == XmlPullParser.END_DOCUMENT)
                throw new AxisFault("parsing error Illegal format - method not specified ");
            //let is there a SOAP fault
            QName nextTag = new QName(this.xpp.getNamespace(), this.xpp.getName());
            if (new QName(soapConstants.getEnvelopeURI(), Constants.ELEM_FAULT).equals(nextTag))
                throw this.parseFault();

            //If RPC I move to the next TAG
            if (this.style.equals("rpc"))
                //while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                //	this.state = this.xpp.next();
                ParmWriter.tag = getTag();

            //ok sounds perfect, the control is passed to wrapper		
        } catch (XmlPullParserException e) {
            log.error("error start parsing body ", e);
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        } catch (IOException e) {
            log.error("error start parsing body ", e);
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }

    /**
     * Parse the Headers to the SOAPHeaderElements object in the SAAJ. The 
     * Content of the Headers will be extracted as org.w3c.Element and put them in
     * to special vector called SOAPHeaderElementContent.
     * @return vector of SOAPHeaderElement's
     * @throws AxisFault
     */
    public Vector createHeaders() throws AxisFault {
        Vector v = new Vector();
        SOAPHeaderElement he = null;
        SOAPHeaderElementContent hec = null;
        Element e = null;

        boolean isTextAllowed = false; // true between only start and end tag
        int level = 0; // on which level do we at the doc

        Stack stack = new Stack();

        // do we have a header
        try {
            while (!(state == XmlPullParser.START_TAG || state == XmlPullParser.END_DOCUMENT))
                this.state = this.xpp.next();
            if (this.state == XmlPullParser.END_DOCUMENT)
                throw new AxisFault("parsing error Illegal format");
            if ((this.xpp.getName().equals(Constants.ELEM_HEADER))) {

                this.state = this.xpp.next();

                // parse till the end of the headers
                while (!(this.state == XmlPullParser.END_DOCUMENT)
                    && !((this.state == XmlPullParser.END_TAG)
                        && (this.xpp.getName().equals(Constants.ELEM_HEADER)))) {

                    if (this.state == XmlPullParser.START_TAG) {
                        if (level == 0) {
                            he = new SOAPHeaderElement(this.xpp.getNamespace(), this.xpp.getName());
                            hec = new SOAPHeaderElementContent();

                            this.setHeaderAttributes(he);
                        } else {
                            e =
                                createElement(
                                    this.xpp.getNamespace(),
                                    this.xpp.getPrefix(),
                                    this.xpp.getName());
                            addAttributes(e);
                            stack.push(e);
                        }
                        level++;
                        isTextAllowed = true;
                    } else if (this.state == XmlPullParser.END_TAG) {
                            if (level == 0) /* nothing to do */;
                        else if (level == 1) {
                            //ok Header element is done add it to the vector
                            if (he.getObjectValue() == null)
                                he.setObjectValue(hec);
                            v.add(he);
                        } else if (level == 2) {
                            //element is done add it to the HeaderElementContent
                            hec.addElement(e);
                        } else {
                            // yap we are at among element push element to element as child
                            Element temp = (Element) stack.pop();
                            if (!stack.isEmpty()) {
                                //TODO do we need this condition (it is taken care by the above condition any way !!! )
                                e = (Element) stack.pop();
                                e.appendChild(temp);
                                stack.push(e);
                            }
                        }
                        level--;
                        isTextAllowed = true;
                    } else if (this.state == XmlPullParser.TEXT) {
                        if (level == 0) {
                            //nothing to do
                        } else if (level == 1) {
                            if (isTextAllowed) {
                                boolean iswhitespace = !this.xpp.isWhitespace();
                                String value = this.xpp.getText();
                                if (value != null && iswhitespace)
                                    he.setObjectValue(value);
                            }
                        } else if (level == 2) {
                            if (isTextAllowed)
                                e.appendChild(this.createTextNode(this.xpp.getText()));
                        }
                    } //end of text if
                    this.state = this.xpp.next();
                } //end of while for header tags
                this.state = this.xpp.next(); // we will go to the  next
            }
        } catch (DOMException e1) {
            log.error("error parsing headers", e1);
            e1.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),null,null,e1);
        } catch (XmlPullParserException e1) {
            log.error("error parsing headers ", e1);
            e1.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),null,null,e1);
        } catch (IOException e1) {
            log.error("error parsing headers", e1);
            e1.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),null,null,e1);
        } catch (SOAPException e1) {
            log.error("error parsing headers", e1);
            e1.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),null,null,e1);
        }
        return v;
    } //end of the header create

    /**
     * Create a SOAPEnvelope(according to SAAJ spec) by parsing the SOAP envelope in the message.  
     * @return SOAPEnvelope object 
     * @throws AxisFault
     */
    public SOAPEnvelope createEnvelope() throws AxisFault {
        try {

            if (!this.xpp.getName().equals(Constants.ELEM_ENVELOPE))
                throw new AxisFault("Invalid SOAP format, Envelope misplaced");

            AttributesImpl att = new AttributesImpl();
            for (int i = 0; i < this.xpp.getAttributeCount(); i++) {
                att.addAttribute(
                    this.xpp.getAttributeNamespace(i),
                    this.xpp.getAttributeName(i),
                    this.xpp.getAttributePrefix(i) + ":" + this.xpp.getAttributeName(i),
                    this.xpp.getAttributeType(i),
                    this.xpp.getAttributeValue(i));
            }

            NSStack namespaces = new NSStack();

            try {
                for (int i = 0; true; i++) {
                    namespaces.add(this.xpp.getNamespaceUri(i),
                    				 this.xpp.getNamespacePrefix(i));
                }
            } catch (XmlPullParserException e) { /*the loop finish at the exception */
            }

            SOAPEnvelope env =
                this.getEnvelope(
                    this.xpp.getNamespace(),
                    this.xpp.getName(),
                    this.xpp.getPrefix(),
                    att,
                    namespaces);
            this.state = this.xpp.next();
            return env;
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        }
    }

    /* Convienance methods to create a SOAP Envelope*/
    private SOAPEnvelope getEnvelope(
        String namespace,
        String localName,
        String prefix,
        Attributes attributes,
        NSStack namespaces)
        throws AxisFault {

        // check for the SOAP version
        if (!localName.equals(Constants.ELEM_ENVELOPE))
            throw new AxisFault("invalied element");
        if (namespace.equals(Constants.URI_SOAP11_ENV)) { // SOAP 1.1
            soapConstants = SOAPConstants.SOAP11_CONSTANTS;
        } else if (namespace.equals(Constants.URI_SOAP12_ENV)) { // SOAP 1.2
            soapConstants = SOAPConstants.SOAP12_CONSTANTS;
        } else {
            soapConstants = Constants.DEFAULT_SOAP_VERSION;
            throw new AxisFault("Unknown SOAP version");
        }
        if (messageData != null)
            this.messageData.setSOAPConstants(soapConstants);

        //set the SOAP envelope values
        SOAPEnvelope envelope = new SOAPEnvelope();
        envelope.setPrefix(prefix);
        envelope.setNamespaceURI(namespace);
        envelope.setNSMappings(namespaces.cloneFrame());
        envelope.setSoapConstants(soapConstants);

        return envelope;
    }

    /**
     * Create a dom element
     * @param uri
     * @param prefix
     * @param localname
     * @return
     */
    public Element createElement(String uri, String prefix, String localname) {
        if (uri == null || uri.equals(""))
            return doc.createElement(localname);
        return this.doc.createElementNS(uri, prefix + ":" + localname);
    }

    public Node createTextNode(String val) {
        return this.doc.createTextNode(val);
    }

    /**
     * convineance method to set the attributes of the header appropriately
     * @param he
     */
    private void setHeaderAttributes(SOAPHeaderElement he) {
        String uri;
        String name;
        String value;

        for (int i = 0; i < this.xpp.getAttributeCount(); i++) {
            uri = this.xpp.getAttributeNamespace(i);
            name = this.xpp.getAttributeName(i);
            value = this.xpp.getAttributeValue(i);

            if (uri.equals(Constants.URI_SOAP11_ENV) || uri.equals(Constants.URI_SOAP12_ENV)) {
                if (name.equals("actor"))
                    he.setActor(value);
                else if (name.equals("mustUnderstand")) {
                    if (value.equals("0"))
                        he.setMustUnderstand(false);
                    else
                        he.setMustUnderstand(true);
                }

            } else
                he.addAttribute(uri, name, value);

        }
    }

    /**
     * If the message style is not RPC null returns
     * @return Qname  of the method of RPC soap request
     */
    public QName getRPCmethod() {
        return this.method;
    }

    public void resetBlindLevel() {
        this.blindLevel = 0;
    }
    /**
     * get the information about the next xml tag in the stream. I ignore the 
     * white space and gard agienst the end of document conditions 
     * @return
     * @throws AxisFault
     */
    public XMLTextData getTag() throws AxisFault {
        String value = null;
        String uri = null;
        String localName = null;
        String attrType = null;
        XMLTextData tag = null;

        try {
            //first move to next
            this.state = xpp.next();

            while ((this.state != XmlPullParser.START_TAG)
                && (this.state != XmlPullParser.END_TAG)
                && (this.state != XmlPullParser.TEXT || xpp.isWhitespace())) {
                if (this.state == XmlPullParser.END_DOCUMENT)
                    throw (new XmlPullParserException("OOps !! End of the document"));
                this.state = xpp.next();
            }
            //when u come here the state is StratTag or TEXT tag or End Tag
            if (this.state == XmlPullParser.TEXT) {
                value = xpp.getText();
            } else { // it is start or end tag here
                uri = xpp.getNamespace();
                localName = xpp.getName();
                if (this.state == XmlPullParser.START_TAG) {
                    attrType =
                        xpp.getAttributeValue("http://www.w3.org/2001/XMLSchema-instance", "type");
                }
            }
            // bellow things should be done for all tags
            tag = new XMLTextData(this.state, value, uri, localName, attrType);
            //this.state = xpp.next();
            return tag;

        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                null,
                e);
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                null,
                e);
        }
    }

    // for dynamic structrues one after another
    // cannot support for dynamic structures withing dynamicstructures
    public String getValueOREnd() throws AxisFault {
        try {

            String value = null;

            while (this.state != XmlPullParser.END_DOCUMENT) {
                if (this.state == XmlPullParser.TEXT && xpp.isWhitespace() == false) {
                    value = xpp.getText();
                    if (value != null) {
                        this.state = xpp.next();
                        return value;
                    }
                } else if (this.state == XmlPullParser.END_TAG) {
                    if (blindLevel > 1) {
                        blindLevel--;
                    } else if (blindLevel == 1) {
                        blindLevel--;
                        this.state = xpp.next();
                        return null;
                    } else {
                        throw (new Exception("Cannot find a start of element"));
                    }
                } else if (this.state == XmlPullParser.START_TAG) {
                    blindLevel++;
                } else { // other stuff
                    // do nothing
                }
                this.state = xpp.next();
            } //end of while
            throw (new XmlPullParserException("OOps !! End of the document"));
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (Exception e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        }
    }

    //convieniece method
    private void moveCursorToSameLevelOrStart(int level)
        throws XmlPullParserException, IOException {
        while (this.state != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.START_TAG || level == 0) {
                this.state = xpp.next();
                return;
            }
            if (this.state == XmlPullParser.END_TAG)
                level--;
            this.state = xpp.next();
        } // end of while
        throw (new XmlPullParserException("Oops !! 123end of the document"));
    }
    /**
     * This is blind reading it will return the value between next start and end tag. 
     * but encountered a end tag of given uri and the local part the function return null.
     * This can be very helpful in parsing the dynamic structures in the SOAP message.
     * 	e.g.
     * 		<a:localname>
     * 			<item> ... </item>
     *			<item> ... </item>
     * 		</a:localname> 
     * 		while((value = getValue(uri,localname)) != null){
     * 			store the value;
     * 		 }
     *    
     * eg:- <b>x<b>  return x
     *      x<b>y<b> return y
     *      <b/> return ""
     */
    public String getValue(String uri, String localPart) throws AxisFault {
        try {
            String value = null;
            //first move to next
            //this.state = xpp.next();

            while ((this.state = xpp.next()) != XmlPullParser.END_DOCUMENT) {
                if (xpp.getEventType() == XmlPullParser.TEXT && xpp.isWhitespace() == false) {
                    value = xpp.getText();
                    if (value != null) {
                        this.state = xpp.next();
                        return value;
                    }
                } else if (xpp.getEventType() == XmlPullParser.END_TAG) {
                    if (uri != null) {
                        if (uri.equals(xpp.getNamespace()) && xpp.getName().equals(localPart)) {
                            this.state = xpp.next();
                            return null;
                        }
                    } else {
                        if (xpp.getName().equals(localPart)) {
                            this.state = xpp.next();
                            return null;
                        }
                    }
                } else {
                }
                //this.state = xpp.next();
            } // end of while
            throw new XmlPullParserException("Oops!!! End of Document");
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,null,e);
        }
    }
    /**
     * This is blind reading it will return the value between next start and end tag. 
     *    
     * eg:- <b>x<b>  return x
     *      x<b>y<b> return y
     *      <b/> return ""
     */

    public String getValue() throws XmlPullParserException, IOException {
        String value = null;
        //first move to next
        //this.state = xpp.next();
        while ((this.state = xpp.next()) != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.TEXT) {
                if (xpp.isWhitespace() == false) {
                    value = xpp.getText();
                    if (value != null) {
                        this.state = xpp.next();
                        return value;
                    } // null if
                } // white space
            } //text
            //this.state = xpp.next();
        } //while
        throw new XmlPullParserException("Oops get Value!!! End of Document");
    }

    public XmlPullParser getParser() {
        return this.xpp;
    }

    public void setParser(XmlPullParser parser) {
        this.xpp = parser;
    }
    public void setState(int state) {
        this.state = state;
    }

    /**
     * read the attributes from the pullParser and put them in to the element 
     */
    private void addAttributes(Element e) throws AxisFault {
        try {
            Document doc = AxisUtils.getCommonDomDocument();
            int count = this.xpp.getAttributeCount();
            for (int i = 0; i < count; i++) {
                String ns = this.xpp.getAttributeNamespace(i);
                Attr att;
                if (ns != null || ns.equals(""))
                    att = doc.createAttributeNS(ns, this.xpp.getAttributeName(i));
                else
                    att = doc.createAttribute(this.xpp.getAttributeName(i));
                att.setValue(this.xpp.getAttributeValue(i));
                e.setAttributeNode(att);
            }
        } catch (Exception e1) {
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),
                null,
                null,
                e1);
        }
    }

    /**
     *R1000 When a MESSAGE contains a soap:
     *Fault element, that element MUST NOT have element 
     *children other than faultcode, faultstring, faultactor and detail. 
     */

    public AxisFault parseFault() throws AxisFault {
        AxisFault af = new AxisFault();
        SOAPConstants soapConstants = SOAPConstants.SOAP11_CONSTANTS;

        try {
            while (this.state != XmlPullParser.END_DOCUMENT) {
                if (this.state == XmlPullParser.START_TAG) {
                    if ((xpp.getName().equals("Fault"))
                        && soapConstants.getEnvelopeURI().equals(xpp.getNamespace()))
                        this.state = xpp.next();
                    break;
                }
                this.state = xpp.next();
            }

            while (this.state != XmlPullParser.END_DOCUMENT) {
                if (this.state == XmlPullParser.START_TAG) {
                    if (xpp.getName().equals("faultcode")) {
                        String nspace = xpp.getNamespace();
                        String code = getValue();
                        af.setFaultCode(new QName(nspace, code));
                    } else if (xpp.getName().equals("faultstring")) {
                        af.setFaultString(getValue());
                    } else if (xpp.getName().equals("faultactor")) {
                        af.setFaultActor(getValue());
                    } else if (xpp.getName().equals("detail")) {
                        af.setFaultDetail(
                            Parser2Element.RootElement2ChildElements(null, "detail", xpp));
                    } else {
                        this.state = xpp.next();
                        throw (new AxisFault(
							"Unexpected child element encountered in SoapFault"));
                    }

                } else if (this.state == XmlPullParser.END_TAG) {
                    if ((xpp.getName() == "Fault")
                        && soapConstants.getEnvelopeURI().equals(xpp.getNamespace())) {
                        this.state = xpp.next();
                        return af;
                    }
                } else {

                }
                this.state = xpp.next();
            } //while

        } catch (AxisFault e) {
            e.printStackTrace();
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
            throw new AxisFault("Encountered error while deserializing SOAPFault", e);
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw new AxisFault("Encountered error while deserializing SOAPFault", e);
        }
        throw new AxisFault("Oops!!! End of Document");
    } // parsefault

    /**
       * This method return first value between two imediate start and end tags.
       * The alogorithm is as followed
       *  1) go forward till find an start tag.
       *  2) then go foward till find end tag
       *  3) return the last string found in the way, it is the right one :)
       */

    public String nextText() throws AxisFault {
        try {
            String text = null;
            //first try to find a start TAG	
            while (state != XmlPullParser.START_TAG) {
                if (state == XmlPullParser.END_DOCUMENT)
                    throw new AxisFault("end of the document reached");
                state = xpp.next();
            }

            //fine then try to find end TAG
            while (state != XmlPullParser.END_TAG) {
                if (state == XmlPullParser.END_DOCUMENT)
                    throw new AxisFault("end of the document reached");
                if (state == XmlPullParser.TEXT) {
                    text = (xpp.isWhitespace() ? null : xpp.getText());
                }
                state = xpp.next();
            }
            //we find a start and end TAG pair at least text is what we are looking 
            return text;
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }

    /**
    * Important when calling this method empty Namespaces 
    * must be given as "".
    * 
    * @param qn
    * @return
    * @throws AxisFault
    */
    public Vector getValuesUntil(QName qn) throws AxisFault {
        Vector vec = new Vector();
        String text = null;

        try {
            while (true) {

                //first try to find a start TAG	
                while (state != XmlPullParser.START_TAG) {

                    if (state == XmlPullParser.END_TAG) {
                        if (xpp.getNamespace() == qn.getNamespaceURI()
                            && xpp.getName() == qn.getLocalPart())
                            return vec;
                    } else if (state == XmlPullParser.END_DOCUMENT) {
                        throw new AxisFault("end of the document reached");
                    } else {
                    }
                    state = xpp.next();
                } // while

                state = xpp.next();

                //fine then try to find end TAG
                while (true) {
                    if (state == XmlPullParser.TEXT) {
                        if (!xpp.isWhitespace()) {
                            text = xpp.getText();
                        } else { // is a whitesapce
                            text = null;
                        }
                    } else if (state == XmlPullParser.END_TAG) {
                        vec.add(text);
                        if (xpp.getNamespace() == qn.getNamespaceURI()
                            && xpp.getName() == qn.getLocalPart())
                            return vec;
                        else
                            break;
                    } else if (state == XmlPullParser.END_DOCUMENT) {
                        throw new AxisFault("end of the document reached");
                    } else {
                    }
                    state = xpp.next();
                } //while-we find a start and end TAG pair at least text is what we are looking for
            } // end of big while	  

        } catch (IOException e) {
            e.printStackTrace();
            throw new AxisFault("IOException ....... ", e);
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }

    }

    public String getSimpleValue(QName qn) throws AxisFault {

        try {
            this.state = xpp.getEventType();

            while (this.state != XmlPullParser.END_DOCUMENT) {
                // check for null and ""
                if (state == XmlPullParser.START_TAG) {
                    log.debug(
                        "NamespaceURIs and LocalParts should be equal."
                            + xpp.getNamespace()
                            + qn.getNamespaceURI()
                            + xpp.getName()
                            + qn.getLocalPart());

                    if (xpp.getName() == qn.getLocalPart()
                        && xpp.getNamespace() == qn.getNamespaceURI()) {
                        state = xpp.next();
                        if (state == XmlPullParser.TEXT) {
                            //return the text
                            String text = xpp.getText();

                            if (xpp.next() == XmlPullParser.END_TAG)
                                return text;
                            else
                                throw new AxisFault("Unexpected start tag encountered, when called to deserialize a simple type");

                        } else if (state == XmlPullParser.END_TAG) {
                            return "";
                        } else { // i.e. not a simple tag
                            throw new AxisFault("Unexpected start tag encountered, when called to deserialize a simple type");
                        }

                    } // QName comparison
                } // end of start if
                state = xpp.next();
            } // while End tag
            throw new AxisFault("End of the document is reached");
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw new AxisFault("", e);
        } catch (IOException e) {
            e.printStackTrace();
            throw new AxisFault("", e);
        }
    }
	/**
	 * @return
	 */
	public Vector getHeaders() {
		return headers;
	}

}
