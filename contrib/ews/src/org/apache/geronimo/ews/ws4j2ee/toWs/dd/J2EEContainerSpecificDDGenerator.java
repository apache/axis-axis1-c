package org.apache.geronimo.ews.ws4j2ee.toWs.dd;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Writer;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.jboss.JBossDDWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.jonas.JOnASDDWriter;

/**
 * @author Srinath perera(hemapani@opesnource.lk)
 */
public class J2EEContainerSpecificDDGenerator implements Generator {
    private J2EEWebServiceContext j2eewscontext;
    private Writer writer;
    protected static Log log =
            LogFactory.getLog(JaxrpcMapperGenarator.class.getName());

    public J2EEContainerSpecificDDGenerator(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
        this.j2eewscontext = j2eewscontext;
        String ddName = j2eewscontext.getMiscInfo().getJ2eeContainerDDName();
        if (GenerationConstants.JBOSS_DD.equals(ddName))
            writer = new JBossDDWriter(j2eewscontext);
        else if (GenerationConstants.JONAS_DD.equals(ddName)) 
            writer = new JOnASDDWriter(j2eewscontext);
        else
            new GenerationFault("unsupported j2ee container DD " + ddName);
    }

    public void genarate() throws GenerationFault {
    	if(writer != null)
			writer.writeCode();
    }
}
