/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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
 *        Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl;

import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import javax.wsdl.Binding;
import javax.wsdl.PortType;
import javax.wsdl.Service;
import javax.xml.namespace.QName;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.Element;
import org.apache.axis.wsdl.symbolTable.PortEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.axis.wsdl.symbolTable.SymTabEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.type.SchemaType;



/**
 * <p>This Class is a wrapper fo the Axis SymbolTable. Since SymbolTable is parsed
 * completly it is not editable so the methods will throw the
 * UnsupportedOperationException.</p>
 * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class AxisWSDLContext implements WSDLContext {
	protected static Log log =
				LogFactory.getLog(AxisWSDLContext.class.getName());
    private SymbolTable symbolTable;
    private HashMap services;
    private HashMap bindings;
    private HashMap portetypes;
    private HashMap ports;
    private boolean verbose = false;

    public AxisWSDLContext(SymbolTable axisSymbltable) {
        this.symbolTable = axisSymbltable;
        this.services = new HashMap();
        this.bindings = new HashMap();
        this.portetypes = new HashMap();
        this.ports = new HashMap();

        Iterator it = symbolTable.getHashMap().values().iterator();
        while (it.hasNext()) {
            Vector v = (Vector) it.next();
            for (int i = 0; i < v.size(); ++i) {
                SymTabEntry entry = (SymTabEntry) v.elementAt(i);

                if (entry instanceof ServiceEntry) {
                    Service service = ((ServiceEntry) entry).getService();
                    this.services.put(service.getQName(), entry);
                } else if (entry instanceof BindingEntry) {
                    Binding binding = ((BindingEntry) entry).getBinding();
                    this.bindings.put(binding.getQName(), entry);
                } else if (entry instanceof PortTypeEntry) {
                    PortType portType = ((PortTypeEntry) entry).getPortType();
                    this.portetypes.put(portType.getQName(), entry);
                } else if (entry instanceof PortEntry) {
                    PortEntry port = ((PortEntry) entry);
                    this.ports.put(port.getQName().getLocalPart(), entry);
                }

            }
        }
    }

    /**
     * Symbol table can't be edited
     */
    public void addService(Service service) {
        throw new UnsupportedOperationException("Symboltable can't be edited");
    }

    /**
     * Symbol table can't be edited
     */
    public void addType(SchemaType type) {
        throw new UnsupportedOperationException("Symboltable can't be edited");
    }

    /**
     * 
     */
    public BindingEntry getBinding(QName bindingname) {
        if (bindingname == null) {
            //if binding not specified the first one will return
            Iterator values = this.bindings.values().iterator();
            if (values.hasNext())
                return (BindingEntry) values.next();
        }

        return (BindingEntry) this.bindings.get(bindingname);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getBindings()
     */
    public Collection getBindings() {
        return this.bindings.values();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getPortType(org.apache.xml.utils.QName)
     */
    public PortTypeEntry getPortType(QName portname) {
        return (PortTypeEntry) this.portetypes.get(portname);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getPortTypes()
     */
    public Collection getPortTypes() {
        return this.portetypes.values();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getService(org.apache.xml.utils.QName)
     */
    public ServiceEntry getService(QName servicename) {
        return (ServiceEntry) this.services.get(servicename);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getServices()
     */
    public Collection getServices() {
        return this.services.values();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getType(org.apache.xml.utils.QName)
     */
    public TypeEntry getType(QName typename) {
        // TODO Auto-generated method stub
        return symbolTable.getType(typename);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getTypes()
     */
    public Map getTypes() {
        return symbolTable.getTypeIndex();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getElement(javax.xml.namespace.QName)
     */
    public Element getElement(QName name) {
        return this.symbolTable.getElement(name);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getPort()
     */
    public PortEntry getPort(QName name) {
    	if(verbose)
    		log.info("getting port type "+name);
        Object obj = this.ports.get(name);
        //when Symbol table populates the URI of the port is given as ""
        //so we have to cheat 
        if (obj == null) {
            obj = this.ports.get(name.getLocalPart());
        }
        

        return (PortEntry) obj;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#getTargetNSURI()
     */
    public String getTargetNSURI() {
        return symbolTable.getDefinition().getTargetNamespace();
    }
}
