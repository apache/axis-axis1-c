/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002-2003 The Apache Software Foundation.  All rights
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
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "The Jakarta Project", "Commons", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
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
 *
 */
 
 package org.apache.geronimo.ews.ws4j2ee.toWs.ejb;

import java.util.ArrayList;
import java.util.Iterator;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.JavaInterfaceWriter;

/**
 * This class can be used to write the appropriate EJB Remote interface
 * class for the given port type.
 * 
 * @author Rajith Priyanga
 * @author Srinath Perera
 * @date Nov 26, 2003
 */
public class EJBRemoteWriter extends JavaInterfaceWriter {
	private String name;
	protected EJBContext ejbcontext;
		

	/**
	 * Constructs a EJBRemoteWriter.
	 * 
	 * @param portType The port type which contains the details.
	 * @throws GenerationFault 
	 */
	public EJBRemoteWriter(J2EEWebServiceContext context,EJBContext ejbcontext) throws GenerationFault {
		super(context, ejbcontext.getEjbRemoteInterface());
		this.ejbcontext =  ejbcontext;
	}

	protected String getExtendsPart() {
		return " extends javax.ejb.EJBObject";
	}

	protected void writeAttributes() throws GenerationFault {
	}

	protected void writeMethods() throws GenerationFault {
		String parmlistStr = "";
		ArrayList operations = j2eewscontext.getMiscInfo().getSEIOperations();
		for (int i = 0; i < operations.size(); i++) {
			SEIOperation op = (SEIOperation) operations.get(i);
			String returnType = op.getReturnType();
			if(returnType == null)
				returnType = "void";
			out.write("\tpublic " + returnType + " " + op.getMethodName() + "(");

            
			Iterator pas = op.getParameterNames().iterator();
			boolean first = true;
			while (pas.hasNext()) {
				String name = (String) pas.next();
				String type = (String) op.getParameterType(name);
				if (first) {
					first = false;
					out.write(type + " " + name);
					parmlistStr = parmlistStr + name;
				} else {
					out.write("," + type + " " + name);
					parmlistStr = "," + name;
				}

			}

			out.write(") throws java.rmi.RemoteException");
//ejb giving problems deploying check this            
//			  ArrayList faults = op.getFaults();
//			  for (int j = 0; j < faults.size(); j++) {
//				  out.write("," + (String) faults.get(i));
//			  }
			out.write(";\n");
		}
	}

}
