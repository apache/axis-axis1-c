package org.apache.geronimo.ews.ws4j2ee.toWs.dd.jonas;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author sauthieg
 */
public class JOnASDDWriter extends AbstractWriter {
	public JOnASDDWriter(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
		super(j2eewscontext);
	}

	public String getFileName() {
		return j2eewscontext.getMiscInfo().getOutPutPath() +
				"/ejb/META-INF/JonAs.xml";
	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.Writer#writeCode()
	 */
	public void writeCode() throws GenerationFault {
		super.writeCode();
		String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
		int index = ejbname.lastIndexOf(".");
		if(index>0){
		  ejbname = ejbname.substring(index+1);
		} 
		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<jonas-ejb-jar xmlns=\"http://www.objectweb.org/jonas/ns\"\n");
		out.write("               xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
		out.write("               xsi:schemaLocation=\"http://www.objectweb.org/jonas/ns\"\n");
		out.write("                                    http://www.objectweb.org/jonas/ns/jonas-ejb-jar_4_0.xsd\">\n");
		out.write("	<jonas-session>\n");
		out.write("	  <ejb-name>" + j2eewscontext.getMiscInfo().getEjbName() + "</ejb-name>\n");
		if(j2eewscontext.getMiscInfo().isSupportLocalAndRemote() 
							|| GenerationConstants.USE_REMOTE.equals(j2eewscontext.getMiscInfo().getImplStyle())){
			out.write("	  <jndi-name>" + j2eewscontext.getMiscInfo().getEjbName() + "</jndi-name>\n");
		}
		if(j2eewscontext.getMiscInfo().isSupportLocalAndRemote() 
			|| GenerationConstants.USE_LOCAL.equals(j2eewscontext.getMiscInfo().getImplStyle())){
			//TODO fill this what is the correct tag for JonAs	
			//out.write("	  <local-jndi-name>" + "ejb/" +ejbname+ "Local"+"</local-jndi-name>\n");
		}
		out.write("	</jonas-session>\n");
		out.write("</jonas-ejb-jar>\n");
		out.close();
	}
}
