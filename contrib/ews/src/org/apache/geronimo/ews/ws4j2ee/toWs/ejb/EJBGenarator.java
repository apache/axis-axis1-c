package org.apache.geronimo.ews.ws4j2ee.toWs.ejb;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Writer;
import org.apache.geronimo.ews.ws4j2ee.toWs.WriterFactory;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class EJBGenarator implements Generator {
    private Writer homewriter;
    private Writer remotewriter;
    private Writer beanwriter;
    private Writer ddwriter;

    public EJBGenarator(J2EEWebServiceContext context) throws GenerationFault {
        homewriter = WriterFactory.createWriter(context, GenerationConstants.EJB_HOME_INTERFACE_WRITER);
        remotewriter = WriterFactory.createWriter(context, GenerationConstants.EJB_REMOTE_INTERFACE_WRITER);
        beanwriter = WriterFactory.createWriter(context, GenerationConstants.EJB_IMPLEMENTATION_BEAN_WRITER);
        ddwriter = WriterFactory.createWriter(context, GenerationConstants.EJB_DD_WRITER);
    }

    public void genarate() throws GenerationFault {
        homewriter.writeCode();
        remotewriter.writeCode();
        beanwriter.writeCode();
        ddwriter.writeCode();
    }

}
