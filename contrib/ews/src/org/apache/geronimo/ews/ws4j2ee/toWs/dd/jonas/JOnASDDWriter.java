package org.apache.geronimo.ews.ws4j2ee.toWs.dd.jonas;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
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
                "/ejb/META-INF/" + j2eewscontext.getMiscInfo().getJ2eeContainerDDName();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Writer#writeCode()
     */
    public void writeCode() throws GenerationFault {
        super.writeCode();
        out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
        out.write("<jonas-ejb-jar xmlns=\"http://www.objectweb.org/jonas/ns\"\n");
        out.write("               xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
        out.write("               xsi:schemaLocation=\"http://www.objectweb.org/jonas/ns\"\n");
        out.write("                                    http://www.objectweb.org/jonas/ns/jonas-ejb-jar_4_0.xsd\">\n");
        out.write("	<jonas-session>\n");
        out.write("	  <ejb-name>" + j2eewscontext.getMiscInfo().getEjbName() + "</ejb-name>\n");
        out.write("	  <jndi-name>" + j2eewscontext.getMiscInfo().getEjbName() + "</jndi-name>\n");
        out.write("	</jonas-session>\n");
        out.write("</jonas-ejb-jar>\n");
        out.close();
    }
}
