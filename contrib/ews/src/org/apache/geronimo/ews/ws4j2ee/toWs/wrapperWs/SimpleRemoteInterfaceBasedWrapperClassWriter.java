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

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public abstract class SimpleRemoteInterfaceBasedWrapperClassWriter extends WrapperClassWriter{

	/**
	 * @param j2eewscontext
	 * @throws GenerationFault
	 */
	public SimpleRemoteInterfaceBasedWrapperClassWriter(J2EEWebServiceContext j2eewscontext)
		throws GenerationFault {
		super(j2eewscontext);
	}
    
	protected abstract String getJNDIInitialContextFactory();
	protected abstract String getJNDIHostAndPort();
	
	protected void writeMethods() throws GenerationFault {
		out.write("\tpublic void setMessageContext(org.apache.axis.MessageContext msgcontext){;\n");
		out.write("\t\tthis.msgcontext = msgcontext;\n");
		out.write("\t}\n");
		writeGetRemoteRef(classname);
		
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
			 out.write("\t\tif(ejb ==  null)\n");
			 out.write("\t\t\tejb = getRemoteRef();\n");

			 if(!"void".equals(returnType))
				 out.write("\t\treturn ejb."+op.getMethodName()+"("+parmlistStr+");\n");
			 else
				 out.write("\t\tejb."+op.getMethodName()+"("+parmlistStr+");\n");	
				
			 out.write("\t}\n");
		 }
		 //out.write("}\n");	

	}
	private void writeGetRemoteRef(String classname){
	   out.write("\tpublic "+seiName+" getRemoteRef()throws org.apache.axis.AxisFault{\n");
	   if(j2eewscontext.getMiscInfo().isUseRemoteInterface()){
		   out.write("\t\ttry {\n");
		   out.write("\t\t    javax.security.auth.callback.CallbackHandler handler\n");
		   out.write("\t\t        = org.apache.geronimo.ews.ws4j2ee.wsutils.security.jaasmodules.\n");
		   out.write("\t\t            AutenticationCallbackHandlerFactory.createCallbackHandler(msgcontext);\n");
		   out.write("\t\t    if(handler != null){\n");
		   out.write("\t\t        javax.security.auth.login.LoginContext lc\n"); 
		   out.write("\t\t            = new javax.security.auth.login.LoginContext(\"TestClient\", handler);\n");
		   out.write("\t\t        lc.login();\n");
		   out.write("\t\t    }\n");
		   out.write("\t\t}catch (javax.security.auth.login.LoginException e) {\n");
		   out.write("\t\t     e.printStackTrace();\n");
		   out.write("\t\t     throw org.apache.axis.AxisFault.makeFault(e);\n");
		   out.write("\t\t}\n");
	   	
		   out.write("\t\ttry{\n");
		   out.write("\t\t\tjava.util.Properties env = new java.util.Properties();\n");
		   out.write("\t\t\tenv.put(javax.naming.Context.INITIAL_CONTEXT_FACTORY,\""+getJNDIInitialContextFactory()+"\");\n");
		   out.write("\t\t\tenv.put(javax.naming.Context.PROVIDER_URL, \""+getJNDIHostAndPort()+"\");\n");
			
		   out.write("\t\t\tjavax.naming.Context initial = new javax.naming.InitialContext(env);\n");		
		   String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
			int index = ejbname.lastIndexOf(".");
			if(index>0){
			  ejbname = ejbname.substring(index+1);
			} 
		   out.write("\t\t\tObject objref = initial.lookup(\"ejb/"+ejbname+"\");\n");
		   String ejbhome = j2eewscontext.getMiscInfo().getEjbhome();
		   out.write("\t\t\t"+ejbhome+" home = \n\t\t\t\t("+ejbhome
			   +")javax.rmi.PortableRemoteObject.narrow(objref,"+ejbhome+".class);\n");
		   out.write("\t\t\treturn home.create();\n");
		   out.write("\t\t}catch (Exception e) {\n");
		   out.write("\t\t    throw org.apache.axis.AxisFault.makeFault(e);\n");
		   out.write("\t\t}\n");
		   
	   }else{
		   out.write("\t\t\treturn null;\n");
	   }   
	   out.write("\t}\n");
	}



}
