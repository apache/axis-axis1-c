package org.apache.geronimo.ews.ws4j2ee.toWs.ejb;

/*
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.PropertyException; */

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
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
        return j2eewscontext.getMiscInfo().getOutPutPath() + "/ejb/META-INF/ejb-jar.xml";
    }

    public void writeCode() throws GenerationFault {
        super.writeCode();
        writeSessionDD();
    }

    public void writeSessionDD() throws GenerationFault {
        out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        out.write("<!DOCTYPE ejb-jar PUBLIC '-//Sun Microsystems, Inc.//DTD Enterprise JavaBeans 2.0//EN' 'http://java.sun.com/dtd/ejb-jar_2_0.dtd'>\n");
        out.write("<ejb-jar>\n");
        out.write("<display-name>" + j2eewscontext.getMiscInfo().getWscfdWsDesxription().getDisplayName() + "</display-name>\n");
        out.write("\t<enterprise-beans>\n");
        out.write("\t\t<session>\n");
        out.write("\t\t\t<display-name>" + j2eewscontext.getMiscInfo().getWscfdWsDesxription().getDisplayName() + "</display-name>\n");
        out.write("\t\t\t<ejb-name>" + j2eewscontext.getMiscInfo().getEjbName() + "</ejb-name>\n");
        out.write("\t\t\t<home>" + j2eewscontext.getMiscInfo().getEjbhome() + "</home>\n");
        out.write("\t\t\t<remote>" + j2eewscontext.getMiscInfo().getEjbsei() + "</remote>\n");
        out.write("\t\t\t<ejb-class>" + j2eewscontext.getMiscInfo().getEjbbean() + "</ejb-class>\n");
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
