package testData;

import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;

/**
 * @author srinath
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class DummyHandler extends BasicHandler{
    public void invoke(MessageContext arg0) throws AxisFault {
       System.out.println("Hi Am a dummy Handler .. ");
    }
}
