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
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter;


/**
 * <p>This class can be used to write the appropriate SessionBean
 * class for the given port type. 
 * A Stateless Session Bean, as defined by the Enterprise JavaBeans specification, 
 * can be used to implement a Web service to be deployed in the EJB container. 
 * A Stateless Session Bean does not have to worry about multi-threaded access. 
 * The EJB container is required to serialize request flow through any particular 
 * instance of a Service Implementation Bean. The requirements for creating a Service
 * Implementation Bean as a Stateless Session EJB are repeated in part here.</p>
 * <ol>
 * 	   <li>The Service Implementation Bean must have a default public constructor.</li>
 *     <li>The Service Implementation Bean may implement the Service Endpoint Interface, 
 *      but it is not required to do so. The bean must implement all the method
 *      signatures of the SEI.<li>
 *     <li>The Service Implementation Bean methods are not required to throw 
 *     javax.rmi.RemoteException. The business methods of the bean must be public 
 *     and must not be final or static. It may implement other methods in addition
 *      to those defined by the SEI.</li>
 *     <li>A Service Implementation Bean must be a stateless object.
 *      A Service Implementation Bean must not save client specific state 
 *     across method calls either within the bean instance’s data members or 
 *     external to the instance.</li>
 *     <li>The class must be public, must not be final and must not be abstract.</li>
 *     <li>The class must not define the finalize() method.</li>
 *     <li>Currently, it must implement the ejbCreate() and ejbRemove() methods which
 *      take no arguments. This is a requirement of the EJB container, but generally
 *      can be stubbed out with an empty implementation.</li>
 *     <li>Currently, a Stateless Session Bean must implement the javax.ejb.SessionBean 
 *     interface either directly or indirectly. This interface allows the container to notify the Service Implementation Bean of impending changes in its state. The full requirements of this interface are defined in the Enterprise JavaBeans specification section 7.5.1.</li>
 *     <li>The Enterprise JavaBeans specification section 7.8.2 defines the allowed
 *     container service access requirements.</li>
 * </ol>
 * <h5>Exposing an existing EJB</h5>
 * <p>An existing Enterprise JavaBean may be used as a Service Implementation Bean if it meets the following requirements:</p>
 *	<ol>
 *	<li>The business methods of the EJB bean class that are exposed on the SEI must meet the Service</li>
 *   <li>Implementation Bean requirements defined in section 5.3.1.</li>
 *   <li>The SEI must meet the requirements described in the JAX-RPC specification for Service Endpoint Interfaces.</li>
 *   <li>The transaction attributes of the SEI methods must not include Mandatory.</li>
 *   <li>The developer must package the Web service as described in section 5.4 and must specify an ejb-link from the port in the Web services deployment descriptor to the existing EJB.</li>
 *   <ol>
 * @author Rajith Priyanga
 * @author Srinath Perera
 * @date Nov 26, 2003
 */
public class SessionBeanWriter extends JavaClassWriter {
	private String name;

	/**
	 * Constructs a SessionBeanWriter.
	 * 
	 * @param portType The port type which contains the details.
	 * @throws GenerationFault 
	 */
	public SessionBeanWriter(J2EEWebServiceContext context) throws GenerationFault {
		super(context, context.getMiscInfo().getEndpointImplbean());
	}

	/**
	 * Returns the complete file name of the source code file which is
	 * generated by the writer.
	 */
	public String getFileName() {
		name = j2eewscontext.getMiscInfo().getEndpointImplbean();
		String outdir = j2eewscontext.getMiscInfo().getOutPutPath();
		if (!outdir.endsWith("/"))
			outdir = outdir + "/";

		return outdir +  name.replace('.', '/') + ".java";
	}

	protected void writeAttributes() throws GenerationFault {
	}

	protected void writeConstructors() throws GenerationFault {
	}

	protected void writeMethods() throws GenerationFault {
		String parmlistStr = "";
		ArrayList operations = j2eewscontext.getMiscInfo().getSEIOperations();
		for (int i = 0; i < operations.size(); i++) {
			SEIOperation op = (SEIOperation) operations.get(i);
            
			String returnType = op.getReturnType();
			returnType = (returnType==null)?"void":returnType;
            
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
			out.write(")");
//			out.write(") throws java.rmi.RemoteException");
//			ejb giving problems deploying check this            
//			  ArrayList faults = op.getFaults();
//			  for (int j = 0; j < faults.size(); j++) {
//				  out.write("," + (String) faults.get(i));
//			  }
			out.write("{\n");
			if("int".equals(returnType)){
				out.write("\t\t\treturn 12;\n");
			}else if("float".equals(returnType)){
				out.write("\t\t\treturn 0.0f;\n");
			}else if("double".equals(returnType)){
				out.write("\t\t\treturn 0.0d;\n");
			}else if("short".equals(returnType)){
				out.write("\t\t\treturn (short)0.0;\n");
			}else if("boolean".equals(returnType)){
				out.write("\t\t\treturn false;\n");
			}else if("byte".equals(returnType)){
				out.write("\t\t\treturn (byte)24;\n");
			}else if("long".equals(returnType)){
				out.write("\t\t\treturn 0.0l;\n");
			}else if("char".equals(returnType)){
				out.write("\t\t\treturn 'w';\n");
			}else if("void".equals(returnType)){
				
			}else{
				out.write("\t\t\treturn null;\n");
			}
			out.write("\t}\n");
		}

		out.write("\tpublic javax.naming.Context getInitialContext()throws javax.naming.NamingException{\n");
		out.write("\t	java.util.Properties env = new java.util.Properties();\n");
		out.write("\t	env.put(javax.naming.Context.INITIAL_CONTEXT_FACTORY,\"org.jnp.interfaces.NamingContextFactory\");\n");
		out.write("\t	env.put(javax.naming.Context.PROVIDER_URL, \"127.0.0.1:1099\");\n");
		out.write("\t	return new javax.naming.InitialContext(env);\n");
		out.write("\t}\n");

		out.write("\tpublic void ejbCreate() {}\n");
		out.write("\tpublic void ejbActivate() throws javax.ejb.EJBException, java.rmi.RemoteException {}\n");
		out.write("\tpublic void ejbPassivate() throws javax.ejb.EJBException, java.rmi.RemoteException {}\n");
		out.write("\tpublic void ejbRemove() throws javax.ejb.EJBException, java.rmi.RemoteException {}\n");
		out.write("\tpublic void setSessionContext(javax.ejb.SessionContext arg0)throws javax.ejb.EJBException, java.rmi.RemoteException {}\n");

	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter#getimplementsPart()
	 */
	protected String getimplementsPart() {
		return " implements javax.ejb.SessionBean";
	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter#isOverWrite()
	 */
	protected boolean isOverWrite() {
		return false;
	}

}
