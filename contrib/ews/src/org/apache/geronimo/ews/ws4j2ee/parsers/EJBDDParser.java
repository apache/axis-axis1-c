package org.apache.geronimo.ews.ws4j2ee.parsers;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.parsers.ejbdd.EjbJar;
import org.apache.geronimo.ews.ws4j2ee.parsers.ejbdd.EjbJarType.EnterpriseBeansType.Session;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.Unmarshaller;
import java.io.InputStream;
import java.util.List;

/**
 * @author hemapani
 */
public class EJBDDParser {
    private J2EEWebServiceContext j2eewscontext;

    public EJBDDParser(J2EEWebServiceContext j2eewscontext) {
        this.j2eewscontext = j2eewscontext;
    }

    public void parse(InputStream inputStream) throws GenerationFault {
        try {
            JAXBContext jc = JAXBContext.newInstance("org.apache.geronimo.ews.ws4j2ee.parsers.ejbdd");
                
            // create an Unmarshaller
            Unmarshaller u = jc.createUnmarshaller();
            EjbJar ejbJar =
                    (EjbJar) u.unmarshal(inputStream);
            List sessions = ejbJar.getEnterpriseBeans().getSessionOrEntity();
            if (!(sessions.size() > 0 && sessions.get(0) instanceof Session))
                return;
            Session session = (Session) sessions.get(0);
            j2eewscontext.getMiscInfo().setEjbName(session.getEjbName().getValue());
        } catch (Exception e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }
}
