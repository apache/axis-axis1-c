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
package org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs;

import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter;

/**
 * <h4>WebEndpoint Based Serivce Implementation Bean</h4> 
 *  <p>The Service Implementation Bean must follow the Service Developer requirements outlined in the JAX-RPC specification and are listed below except as noted.</p>
 * 	<ol>
 * 	    <li>?The Service Implementation Bean must have a default public constructor.</li>
 *	    <li>?The Service Implementation Bean may implement the Service Endpoint 
 *    	    Interface as defined by the JAX-RPC Servlet model. The bean must implement
 *          all the method signatures of the SEI. In addition, a Service Implementation 
 *          Bean may be implemented that does not implement the SEI. This additional 
 *          requirement provides the same SEI implementation flexibility as provided by
 *          EJB service endpoints. The business methods of the bean must be public and
 *          must not be static.</li>
 *	    <li>If the Service Implementation Bean does not implement the SEI, the
 *           business methods must not be final. The Service Implementation Bean 
 *           may implement other methods in addition to those defined by the SEI, 
 *          but only the SEI methods are exposed to the client.  </li>
 *	    <li>?A Service Implementation must be a stateless object. A Service 
 *           Implementation Bean must not save client specific state across method 
 *           calls either within the bean instance’s data members or external to 
 *           the instance. A container may use any bean instance to service a request.</li>
 *	    <li>?The class must be public, must not be final and must not be abstract.</li>
 *	    <li>?The class must not define the finalize() method.</li>
 *   </ol>
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WebEndpointWrapperClassWriter extends JavaClassWriter {
	protected static Log log =
		LogFactory.getLog(WrapperWsGenerator.class.getName());
	protected String seiName = null;
	/**
	 * @param j2eewscontext
	 * @param qulifiedName
	 * @throws GenerationFault
	 */
	public WebEndpointWrapperClassWriter(J2EEWebServiceContext j2eewscontext)
		throws GenerationFault {
		super(j2eewscontext, getName(j2eewscontext) + "Impl");
		seiName = j2eewscontext.getMiscInfo().getJaxrpcSEI();

	}

	private static String getName(J2EEWebServiceContext j2eewscontext) {
		String name = j2eewscontext.getMiscInfo().gettargetBinding().getName();
		if (name == null) {
			name = j2eewscontext.getMiscInfo().getJaxrpcSEI();
		}
		return name;
	}

	protected String getimplementsPart() {
		return " implements "
			+ j2eewscontext.getMiscInfo().getJaxrpcSEI();
	}

	protected void writeAttributes() throws GenerationFault {
		out.write("private " + seiName + " bean = null;\n");
	}

	protected void writeConstructors() throws GenerationFault {
		out.write("\tpublic " + classname + "()throws org.apache.geronimo.ews.ws4j2ee.wsutils.J2EEFault{\n");
		out.write("\t\tbean = ("+j2eewscontext.getMiscInfo().getEndpointImplbean()+")org.apache.geronimo.ews.ws4j2ee.wsutils.ImplBeanPool.getImplBean(\""
			+j2eewscontext.getMiscInfo().getEndpointImplbean()+"\");\n");
		out.write("\t}\n");
	}

	public String getFileName() {
		String filename =
			j2eewscontext.getMiscInfo().getOutPutPath()
				+ "/"
				+ getName(j2eewscontext).replace('.', '/')
				+ "Impl.java";
		//j2eewscontext.getMiscInfo().getJaxrpcSEI().replace('.','/')+"BindingImpl.java";
		return filename;
	}
	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter#writeMethods()
	 */
	protected void writeMethods() throws GenerationFault {
		String parmlistStr = null;
 		ArrayList operations = j2eewscontext.getMiscInfo().getSEIOperations();
		 for(int i =0;i<operations.size();i++){
			parmlistStr = "";
			 SEIOperation op = (SEIOperation)operations.get(i);
			 String returnType = op.getReturnType();
			 if(returnType == null)
				returnType = "void";
			 out.write("\tpublic "+returnType+" "+op.getMethodName()+"(");
						
			 Iterator pas = op.getParameterNames().iterator();
			 boolean first = true;
			 while(pas.hasNext()){
				 String name = (String)pas.next();
				 String type = op.getParameterType(name);
				 if(first){ 
					 first = false;
					 out.write(type + " " +name);
					 parmlistStr = parmlistStr + name;
				 }else{
					 out.write(","+type + " " +name);
					 parmlistStr = parmlistStr + ","+name;
				 }
								
			 }
						
			 out.write(") throws java.rmi.RemoteException");
			 ArrayList faults = op.getFaults();
			 for(int j = 0;j<faults.size();j++){
				 out.write(","+(String)faults.get(i));
			 }
			 out.write("{\n");
		
			 if(!"void".equals(returnType))
				 out.write("\t\treturn bean."+op.getMethodName()+"("+parmlistStr+");\n");
			 else
				 out.write("\t\tbean."+op.getMethodName()+"("+parmlistStr+");\n");	
						
			 out.write("\t}\n");
		 }
	}

}
