package org.apache.geronimo.ews.ws4j2ee.toWs.dd.jboss;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public class JBossDDWriter extends AbstractWriter {
	public JBossDDWriter(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
		super(j2eewscontext);
	}

	public String getFileName() {
		return j2eewscontext.getMiscInfo().getOutPutPath() +
				"/META-INF/" + j2eewscontext.getMiscInfo().getJ2eeContainerDDName();
	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.Writer#writeCode()
	 */
	public void writeCode() throws GenerationFault {
		super.writeCode();
		if(out == null)
			return;
		String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
			int index = ejbname.lastIndexOf(".");
			if(index>0){
			  ejbname = ejbname.substring(index+1);
		} 
		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<jboss>\n");
		out.write("  <enterprise-beans>\n");
		out.write("	<session>\n");
		out.write("	  <ejb-name>" + ejbname+ "</ejb-name>\n");
		out.write("	  <jndi-name>" + "ejb/" +ejbname+ "</jndi-name>\n");
		out.write("	</session>\n");
		out.write("  </enterprise-beans>\n");
		out.write("</jboss>\n");
		out.close();
	}
}
