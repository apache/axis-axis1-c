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

package org.apache.axismora.transport;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;

import org.apache.axis.AxisFault;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.encoding.Base64;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.soap.SOAPConstants;
import org.apache.axis.transport.http.HTTPConstants;
import org.apache.commons.logging.Log;

/**
 * @author Dimuthu Leelarathne(muthulee@opensource.lk)
 */
public class HTTPSender extends BasicHandler {

    protected static Log log = LogFactory.getLog(HTTPSender.class.getName());

    private InputStream in = null;
    private OutputStream out = null;
    private URL url = null;
    private String user = null;
    private char[] passwd = null;
    private QName soapAction = null;
    private MessageContext msg = null;
    private Socket sock = null;
    private SOAPConstants constants;

    public HTTPSender(
        URL url,
        String user,
        char[] passwd,
        QName soapAction,
        SOAPConstants constants) {
        this.url = url;
        this.user = user;
        this.passwd = passwd;
        this.soapAction = soapAction;
        this.constants = constants;
        try {
            sock = new Socket(url.getHost(), url.getPort());
            this.in = sock.getInputStream();
            this.out = sock.getOutputStream();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void invoke(MessageContext msg) throws AxisFault {
        try {
            this.msg = msg;
            // send the response 
            msg.setSOAPConstants(this.constants);
            msg.setSoapEnvelope(new SOAPEnvelope(this.constants));
            writeHeaders();
            msg.serialize();
            //now we are getting the response
            readHeadersFromSocket();
            msg.parseAndValidateKnownTags();
            msg.check4SOAPFault();
        } catch (IOException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }

    private InputStream readHeadersFromSocket() throws IOException {
        //this is code cut and paste from the 
        //org.apache.axis.trasport.http.HTTPSender header parsing code 
        byte b = 0;
        int len = 0;
        int colonIndex = -1;
        String name, value;
        int returnCode = 0;
        if (null == in)
            in = this.sock.getInputStream();

        Hashtable headers = new Hashtable();

        // Should help performance. Temporary fix only till its all stream oriented.
        // Need to add logic for getting the version # and the return code
        // but that's for tomorrow!

        /* Logic to read HTTP response headers */
        boolean readTooMuch = false;

        for (ByteArrayOutputStream buf = new ByteArrayOutputStream(4097);;) {
            if (!readTooMuch) {
                b = (byte) in.read();
            }
            if (b == -1) {
                break;
            }
            readTooMuch = false;
            if ((b != '\r') && (b != '\n')) {
                if ((b == ':') && (colonIndex == -1)) {
                    colonIndex = len;
                }
                len++;
                buf.write(b);
            } else if (b == '\r') {
                continue;
            } else { // b== '\n'
                if (len == 0) {
                    break;
                }
                b = (byte) in.read();
                readTooMuch = true;

                // A space or tab at the begining of a line means the header continues.
                if ((b == ' ') || (b == '\t')) {
                    continue;
                }
                buf.close();
                byte[] hdata = buf.toByteArray();
                buf.reset();
                if (colonIndex != -1) {
                    name =
                        new String(
                            hdata,
                            0,
                            colonIndex,
                            HTTPConstants.HEADER_DEFAULT_CHAR_ENCODING);
                    value =
                        new String(
                            hdata,
                            colonIndex + 1,
                            len - 1 - colonIndex,
                            HTTPConstants.HEADER_DEFAULT_CHAR_ENCODING);
                    colonIndex = -1;
                } else {

                    name =
                        new String(
                            hdata,
                            0,
                            len,
                            HTTPConstants.HEADER_DEFAULT_CHAR_ENCODING);
                    value = "";
                }
                if (log.isDebugEnabled()) {
                    log.debug(name + value);
                }

                if (msg.getProperty(HTTPConstants.MC_HTTP_STATUS_CODE) == null) {

                    // Reader status code
                    int start = name.indexOf(' ') + 1;
                    String tmp = name.substring(start).trim();
                    int end = tmp.indexOf(' ');

                    if (end != -1) {
                        tmp = tmp.substring(0, end);
                    }
                    returnCode = Integer.parseInt(tmp);
                    msg.setProperty(
                        HTTPConstants.MC_HTTP_STATUS_CODE,
                        new Integer(returnCode));
                    msg.setProperty(
                        HTTPConstants.MC_HTTP_STATUS_MESSAGE,
                        name.substring(start + end + 1));
                } else {
                    headers.put(name.toLowerCase(), value);
                }
                len = 0;
            }
        }

        return in;
    }

    // read response from socket   

    // desclaimers
    /**
    	  * no chunking supported yet.
    	  * no HTTP version 1.1 supported yet
    	  * no continue expected supported
    	  * Header content type hard coded as "text/xml; charset=utf-8". Change it.
    	  * User-Agent hardcoded as : Axis/LSF
    	  * 
      */

    private void writeHeaders() {

        StringBuffer otherHeaders = new StringBuffer();

        if (user != null) {
            StringBuffer buff = new StringBuffer();
            buff.append(user).append(":");
            if (passwd == null) {
                buff.append("");
            } else {
                buff.append(new String(passwd));
                otherHeaders
                    .append(HTTPConstants.HEADER_AUTHORIZATION)
                    .append(": Basic ")
                    .append(Base64.encode(buff.toString().getBytes()))
                    .append("\r\n");
            }
        } //if(user)

        StringBuffer header = new StringBuffer();

        String webMethod = null;
        boolean posting = true;

        // TODO : If we're SOAP 1.2, allow the web method to be set from the
        // MessageContext.

        webMethod = HTTPConstants.HEADER_POST;

        header.append(webMethod).append(" ");

        // we do not check whether useful or not
        header.append(this.url.toExternalForm());

        String httpConnection = null;

        String httpver = HTTPConstants.HEADER_PROTOCOL_V10;
        httpver = httpver.trim();

        header.append(" ");
        header.append(HTTPConstants.HEADER_PROTOCOL_10);
        header.append("\r\n");

        if (posting) {
            header
                .append(HTTPConstants.HEADER_CONTENT_TYPE)
                .append(": ")
                .append("text/xml; charset=utf-8")
                .append("\r\n");
        }
        header.append(
            HTTPConstants.HEADER_ACCEPT) //Limit to the types that are meaningful to us.
        .append(": ")
        .append(HTTPConstants.HEADER_ACCEPT_APPL_SOAP)
        .append(", ")
        .append(HTTPConstants.HEADER_ACCEPT_APPLICATION_DIME)
        .append(", ")
        .append(HTTPConstants.HEADER_ACCEPT_MULTIPART_RELATED)
        .append(", ")
        .append(HTTPConstants.HEADER_ACCEPT_TEXT_ALL)
        .append("\r\n")
        .append(HTTPConstants.HEADER_USER_AGENT) //Tell who we are.
        .append(": ").append("Axis/LSF").append("\r\n").append(
            HTTPConstants.HEADER_HOST) //used for virtual connections
        .append(": ")
        .append(this.url.getHost())
        .append((this.url.getPort() == -1) ? ("") : (":" + this.url.getPort()))
        .append("\r\n")
        .append(
            HTTPConstants.HEADER_CACHE_CONTROL)
        //Stop caching proxies from caching SOAP reqeuest.
        .append(": ")
        .append(HTTPConstants.HEADER_CACHE_CONTROL_NOCACHE)
        .append("\r\n")
        .append(HTTPConstants.HEADER_PRAGMA)
        .append(": ")
        .append(HTTPConstants.HEADER_CACHE_CONTROL_NOCACHE)
        .append("\r\n")
        .append(HTTPConstants.HEADER_SOAP_ACTION) //The SOAP action.
        .append(": \"").append(this.soapAction.getLocalPart()).append("\"\r\n");

        /*				if (posting) {
        					    // no chunking 
        						//Content length MUST be sent on HTTP 1.0 requests.
        						header.append(HTTPConstants.HEADER_CONTENT_LENGTH)
        								.append(": ")
        								.append(reqMessage.getContentLength())
        								.append("\r\n");
        				}
        */
        if (null != httpConnection) {
            header.append(HTTPConstants.HEADER_CONNECTION);
            header.append(": ");
            header.append(httpConnection);
            header.append("\r\n");
        }

        if (null != otherHeaders) {
            //Add other headers to the end.
            //for pre java1.4 support, we have to turn the string buffer argument into
            //a string before appending.
            header.append(otherHeaders.toString());
        }

        header.append("\r\n"); //The empty line to start the BODY.

        try {

            /*	if (!posting) {
            		out.write(header.toString()
            				.getBytes(HTTPConstants.HEADER_DEFAULT_CHAR_ENCODING));
            		out.flush();
            	}
            	
            */

            out.write(
                header.toString().getBytes(HTTPConstants.HEADER_DEFAULT_CHAR_ENCODING));
            // Flush ONLY once.
            out.flush();

        } catch (UnsupportedEncodingException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        if (log.isDebugEnabled()) {
            log.debug("xmlSent00");
            log.debug("---------------------------------------------------");
        }
        return;
    }

    /**
     * @return
     */
    public InputStream getIn() {
        return this.in;
    }

    /**
     * @return
     */
    public OutputStream getOut() {
        return this.out;
    }

}
