package org.apache.geronimo.ews.ws4j2ee.toWs.dd;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Writer;

/**
 * @author Srinath perera(hemapani@opesnource.lk)
 */
public class WebContainerDDGenerator implements Generator {
    private J2EEWebServiceContext j2eewscontext;
    private Writer writer;
    protected static Log log =
            LogFactory.getLog(JaxrpcMapperGenarator.class.getName());

    public WebContainerDDGenerator(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
        
    }

    public void genarate() throws GenerationFault {
    	System.out.println("code to generatre web.xml");
    }
}
