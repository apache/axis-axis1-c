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

/*
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.PropertyException; */

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * We are plan to use the JAXB to genarate and parse the
 * ejb-jar.xml file. this code is just for the get very simple
 * DD created
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class EJBDDWriter extends AbstractWriter {
	/**
	 * @param j2eewscontext 
	 * @throws GenerationFault 
	 */
	public EJBDDWriter(J2EEWebServiceContext j2eewscontext)
			throws GenerationFault {
		super(j2eewscontext);
	}

	public String getFileName() {
		return j2eewscontext.getMiscInfo().getOutPutPath() + "/META-INF/ejb-jar.xml";
	}

	public void writeCode() throws GenerationFault {
		super.writeCode();
		if(out != null)
			writeSessionDD();
	}

	public void writeSessionDD() throws GenerationFault {
    	
		String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
		int index = ejbname.lastIndexOf(".");
		if(index>0){
		  ejbname = ejbname.substring(index+1);
		} 

		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<!DOCTYPE ejb-jar PUBLIC '-//Sun Microsystems, Inc.//DTD Enterprise JavaBeans 2.0//EN' 'http://java.sun.com/dtd/ejb-jar_2_0.dtd'>\n");
		out.write("<ejb-jar>\n");
		out.write("<display-name>" + j2eewscontext.getMiscInfo().getWscfdWsDesxription().getDisplayName() + "</display-name>\n");
		out.write("\t<enterprise-beans>\n");
		out.write("\t\t<session>\n");
		out.write("\t\t\t<display-name>" + j2eewscontext.getMiscInfo().getWscfdWsDesxription().getDisplayName() + "</display-name>\n");
		out.write("\t\t\t<ejb-name>" + ejbname + "</ejb-name>\n");
		
		
		String implStyle = j2eewscontext.getMiscInfo().getImplStyle();
		if(GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle) 
			|| GenerationConstants.USE_REMOTE.equals(implStyle)){
			out.write("\t\t\t<home>" + j2eewscontext.getMiscInfo().getEjbhome() + "</home>\n");
			out.write("\t\t\t<remote>" + j2eewscontext.getMiscInfo().getEjbsei() + "</remote>\n");
	
		}
		if(GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle) 
			|| GenerationConstants.USE_LOCAL.equals(implStyle)){
			out.write("\t\t\t<local-home>"+j2eewscontext.getMiscInfo().getEjblocalhome()+"</local-home>");
			out.write("\t\t\t<local>"+j2eewscontext.getMiscInfo().getEjblocalsei()+"</local>");
		}
		out.write("\t\t\t<ejb-class>" + j2eewscontext.getMiscInfo().getEndpointImplbean() + "</ejb-class>\n");
		out.write("\t\t\t<session-type>Stateless</session-type>\n");
		out.write("\t\t\t<transaction-type>Bean</transaction-type>\n");
		out.write("\t\t\t<security-identity>\n");
		out.write("\t\t\t\t<description></description>\n");
		out.write("\t\t\t\t<use-caller-identity></use-caller-identity>\n");
		out.write("\t\t\t</security-identity>\n");
		out.write("\t\t</session\n>");
		out.write("\t</enterprise-beans>\n");
		out.write("</ejb-jar>\n");
		out.close();
//	   try {
//				 JAXBContext jc =
//					  JAXBContext.newInstance("org.apache.geronimo.ews.ws4j2ee.parsers.ejbdd");
//            
//				  // create an ObjectFactory instance.
//				  // if the JAXBContext had been created with mutiple pacakge names,
//				  // we would have to explicitly use the correct package name when
//				  // creating the ObjectFactory.            
//				  ObjectFactory objFactory = new ObjectFactory();
//            
//				  // create an empty PurchaseOrder
//				  EjbJar dd = objFactory.createEjbJar();
//               
//				  EjbJarType.AssemblyDescriptorType type =
//					  objFactory.createEjbJarTypeAssemblyDescriptorType();
//               
//				  dd.setAssemblyDescriptor(type);
//                
//				  DescriptionType dtype = objFactory.createDescriptionType();
//				  dtype.setValue(j2eewscontext.getMiscInfo().getWscfdWsDesxription().getDisplayName());
//				  dd.setDescription(dtype);
//                
//				  EjbJarType.EnterpriseBeansType eb =
//					  objFactory.createEjbJarTypeEnterpriseBeansType();
//				  EjbJarType.EnterpriseBeansType.Session s =
//					  objFactory.createEjbJarTypeEnterpriseBeansTypeSession();
//            
//				  EjbClassType bean = objFactory.createEjbClassType();
//				  bean.setValue(j2eewscontext.getMiscInfo().getEjbbean());
//				  Remote remote = objFactory.createRemote();
//				  remote.setValue(j2eewscontext.getMiscInfo().getEjbsei());
//				  Home home = objFactory.createHome();
//				  home.setValue(j2eewscontext.getMiscInfo().getEjbhome());
//				  EjbNameType name = objFactory.createEjbNameType();
//				  name.setValue(j2eewscontext.getMiscInfo().getWscfport().getServiceImplBean().getEjblink());
//				  s.setEjbClass(bean);
//				  s.setRemote(remote);
//				  s.setHome(home);
//				  s.setEjbName(name);
//                
//				  EjbJarType.EnterpriseBeansType.SessionType.SessionTypeType session =
//					  objFactory
//						  .createEjbJarTypeEnterpriseBeansTypeSessionTypeSessionTypeType();
//				  EjbJarType
//					  .EnterpriseBeansType
//					  .SessionType
//					  .TransactionTypeType teansaction =
//					  objFactory
//						  .createEjbJarTypeEnterpriseBeansTypeSessionTypeTransactionTypeType();
//               
//				  //the Bean is stateless fine 
//				  session.setValue("Stateless");
//               
//				  //transaction context is set to bean.
//				  //as the jsr109 says that the EJB is stateless
//				  //the transaction context does not apply. Is this acceptable??
//				  teansaction.setValue("Bean");
//                
//				  s.setSessionType(session);
//				  s.setTransactionType(teansaction);
//            
//				  eb.getSessionOrEntity().add(s);
//				  dd.setEnterpriseBeans(eb);
//            
//				  Marshaller m = jc.createMarshaller();
//				  m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);
//				  m.marshal(dd, out);
//            
//				  out.flush();
//				  out.close();
//		  } catch (PropertyException e) {
//			  e.printStackTrace();
//			  throw new GenerationFault(e);
//		  } catch (JAXBException e) {
//			  e.printStackTrace();
//			throw new GenerationFault(e);
//		  }
	}

}
