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

package org.apache.axismora.handlers;

import java.util.Enumeration;
import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axismora.Handler;
import org.apache.axismora.MessageContext;

import org.apache.axis.AxisFault;

/**
 * This is a kind of conviniance class for somebody wants to make simple Handler.
 * The user just have to implements invoke() only.
 * @author Srianth Perera(hemapani@opensource.lk)
 */

public abstract class BasicHandler implements Handler {
    protected static final int DEFAULT_PROPERTY_TABLE_SIZE = 101;

    protected Hashtable table;

    public BasicHandler() {
        table = new Hashtable(DEFAULT_PROPERTY_TABLE_SIZE);
    }

    /**
     * This method must be overide by class extends this class
     * @param msgdata
     */
    public abstract void invoke(MessageContext msgdata)throws AxisFault;

    public void onFalult(MessageContext msgdata) {
    }

    public void init(HandlerInfo conf) {
    	//passing the null means like to keep the exsting configaration
    	if(conf != null)
			this.table = conf.getConfig();
    }

    public void cleanup() {
    }

    public void setOption(String name, Object value) {
        table.put(name, value);
    }

    public Object getOption(String name) {
        return table.get(name);
    }
	
	public Enumeration getOptionKeys(){
		return this.table.keys();
	}
    
	/**
	 * @see lk.opensource.service.Handler#getName()
	 */
	public String getName() {
		return null;
	}

	/**
	 * @see lk.opensource.service.Handler#getUnderstandMethod()
	 */
	public QName[] getUnderstandHeaders() {
		return new QName[0];
	}

}
