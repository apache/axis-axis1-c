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

package org.apache.axismora.deployment.wsdd;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.deployment.WebServiceNotFoundException;
import org.apache.axismora.util.SingeltonException;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.deployment.wsdd.WSDDBeanMapping;
import org.apache.axis.deployment.wsdd.WSDDChain;
import org.apache.axis.deployment.wsdd.WSDDElement;
import org.apache.axis.deployment.wsdd.WSDDException;
import org.apache.axis.deployment.wsdd.WSDDGlobalConfiguration;
import org.apache.axis.deployment.wsdd.WSDDHandler;
import org.apache.axis.deployment.wsdd.WSDDNonFatalException;
import org.apache.axis.deployment.wsdd.WSDDRequestFlow;
import org.apache.axis.deployment.wsdd.WSDDResponseFlow;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.deployment.wsdd.WSDDTransport;
import org.apache.axis.deployment.wsdd.WSDDTypeMapping;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.commons.logging.Log;
import org.apache.xerces.parsers.DOMParser;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.SAXException;

/**
 * This class is basically the org.apache.axis.deployment.wsdd.WSDDDeployment class in
 * the original axis. I borrow the logic from it and this is rewitten to complient with 
 * the existing interfaces. Most of the logic is cut and pasted.
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class WSDDDeployment extends WSDDElement implements AxisDeployment {

    private WSDDGlobalConfiguration globalConfig = null;
    //TODO replce them with hash maps
    private HashMap serviceMap = new HashMap();
    private Vector chainMap = new Vector();
    private Vector handlerMap = new Vector();
    private Vector transportMap = new Vector();
    private Vector typeMappingMap = new Vector();
    private Vector beanMap = new Vector();
    private String deploymentFile;
    protected static Log log = LogFactory.getLog(WSDDDeployment.class.getName());
    private static boolean isInstantiated = false;

    //actually this is for testing only
    private static WSDDDeployment instance;

    //siglelton pattern
    public static WSDDDeployment getInstance(String file)
        throws WSDDException {
        if (instance == null) {
            instance = new WSDDDeployment(file);
            return instance;
        }
         return instance;
    }

    public Vector getTransport() {
        return this.typeMappingMap;
    }

    public WSDDGlobalConfiguration getGlobalInfo() {
        return this.globalConfig;
    }

    /**
     * This constructor load the wsdd file to a DOM tree and parse it to extract the 
     * informations from the file.
     * The info is loaded to vectors/Hashmaps so they can be provided to the System.
     * @param file
     * @throws WSDDException
     */

    private WSDDDeployment(String file) throws WSDDException {
        log.info("initializing deployment ..............");
        try {
            deploymentFile = file;
            DOMParser parser = new DOMParser();
            parser.parse(file);
            Document doc = parser.getDocument();
            Element e = doc.getDocumentElement();

            //to check for the validity of the WSDD file
            QName name = QNAME_DEPLOY;
            if ((null == e)
                || (null == e.getNamespaceURI())
                || (null == e.getLocalName())
                || !e.getNamespaceURI().equals(name.getNamespaceURI())
                || !e.getLocalName().equals(name.getLocalPart())) {
                throw new WSDDException("The error parsing deployment element at wsdd document");
            }

            Element[] elements = getChildElements(e, ELEM_WSDD_HANDLER);
            int i;

            for (i = 0; i < elements.length; i++) {
                WSDDHandler handler = new WSDDHandler(elements[i]);
                this.handlerMap.add(handler);
            }

            elements = getChildElements(e, ELEM_WSDD_CHAIN);
            for (i = 0; i < elements.length; i++) {
                WSDDChain chain = new WSDDChain(elements[i]);
                this.chainMap.add(chain);
            }

            elements = getChildElements(e, ELEM_WSDD_TRANSPORT);
            for (i = 0; i < elements.length; i++) {
                WSDDTransport transport = new WSDDTransport(elements[i]);
                this.transportMap.add(transport);
            }

            elements = getChildElements(e, ELEM_WSDD_SERVICE);
            for (i = 0; i < elements.length; i++) {
                try {
                    WSDDService service = new WSDDService(elements[i]);
                    this.serviceMap.put(service.getQName(), service);
                    log.info("new service found " + service.getQName());
                } catch (WSDDNonFatalException ex) {
                    log.error("non fatel exception");
                    // If it's non-fatal, just keep on going
                } catch (WSDDException ex) {
                    // otherwise throw it upwards
                    throw ex;
                }
            }

            elements = getChildElements(e, ELEM_WSDD_TYPEMAPPING);
            for (i = 0; i < elements.length; i++) {
                try {
                    WSDDTypeMapping mapping = new WSDDTypeMapping(elements[i]);
                    this.typeMappingMap.add(mapping);
                } catch (WSDDNonFatalException ex) {
                    log.error("non fatel exception");
                    // If it's non-fatal, just keep on going
                } catch (WSDDException ex) {
                    // otherwise throw it upwards
                    throw ex;
                }
            }

            elements = getChildElements(e, ELEM_WSDD_BEANMAPPING);
            for (i = 0; i < elements.length; i++) {
                WSDDBeanMapping mapping = new WSDDBeanMapping(elements[i]);
                this.beanMap.add(mapping);
            }

            Element el = getChildElement(e, ELEM_WSDD_GLOBAL);
            if (el != null)
                globalConfig = new WSDDGlobalConfiguration(el);

            log.error("deployment created");
        } catch (SAXException e) {
            e.printStackTrace();
            throw new WSDDException(e);
        } catch (IOException e) {
            e.printStackTrace();
            throw new WSDDException(e);
        }
    }

    /**
     * Getters that gives information about deployed service.
     */
    public WSDDService getService(QName name) throws WebServiceNotFoundException {
        Object service = this.serviceMap.get(name);
        if (service == null)
            throw new WebServiceNotFoundException("The Service does not exit for this QName");
        return (WSDDService) service;

    }

    public Vector getGlobelResponseFlowHandlers() {
        WSDDResponseFlow rH = (this.globalConfig.getResponseFlow());
        if (rH == null)
            return new Vector();
        return rH.getHandlers();
    }

    public Vector getGlobelRequestFlowHandlers() {
        WSDDRequestFlow rH = (this.globalConfig.getRequestFlow());
        if (rH == null)
            return new Vector();
        return rH.getHandlers();
    }

    public Vector getTransportRequestFlowHandlers(String type) {
        for (int i = 0; i < this.transportMap.size(); i++) {
            WSDDTransport t = ((WSDDTransport) this.transportMap.get(i));
            if (t.getQName().getLocalPart().equals(type)) {
                WSDDRequestFlow requestFlow = t.getRequestFlow();
                if (requestFlow != null)
                    return requestFlow.getHandlers();
            }
        }
        return new Vector();
    }

    public Vector getTransportResponseFlowHandlers(String type) {

        for (int i = 0; i < this.transportMap.size(); i++) {
            WSDDTransport t = ((WSDDTransport) this.transportMap.get(i));
            if (t.getQName().getLocalPart().equals(type)) {
                WSDDResponseFlow responseFlow = t.getResponseFlow();
                if (responseFlow != null)
                    return responseFlow.getHandlers();
            }
        }
        return new Vector();
    }

    protected QName getElementName() {
        return null;
        //TODO remove these methods???????? have to have to implements the interface !!
    }

    public void writeToContext(SerializationContext context) throws IOException {
        Writer w = null;

        /* if the context is null write the deployment to
         	the  existing wsddfile. */
        if (context == null) {
            w = new FileWriter(deploymentFile);
            context = new SerializationContextImpl(w);
        }
        context.registerPrefixForURI(NS_PREFIX_WSDD, URI_WSDD);

        context.registerPrefixForURI(NS_PREFIX_WSDD_JAVA, URI_WSDD_JAVA);

        context.startElement(QNAME_DEPLOY, null);

        if (globalConfig != null) {
            globalConfig.writeToContext(context);
        }

        Iterator i = handlerMap.iterator();
        while (i.hasNext()) {
            WSDDHandler handler = (WSDDHandler) i.next();
            handler.writeToContext(context);
        }

        i = serviceMap.values().iterator();
        while (i.hasNext()) {
            WSDDService service = (WSDDService) i.next();
            service.writeToContext(context);
        }

        i = transportMap.iterator();
        while (i.hasNext()) {
            WSDDTransport transport = (WSDDTransport) i.next();
            transport.writeToContext(context);
        }

        i = typeMappingMap.iterator();
        while (i.hasNext()) {
            WSDDTypeMapping mapping = (WSDDTypeMapping) i.next();
            mapping.writeToContext(context);
        }
        context.endElement();
        if (w != null) {
            w.flush();
            w.close();
        }

    }
    public void deployService(WSDDService service) {
        this.serviceMap.put(service.getQName(), service);
    }
    public void undeployService(QName servicename) {
        this.serviceMap.remove(servicename);
    }
}
