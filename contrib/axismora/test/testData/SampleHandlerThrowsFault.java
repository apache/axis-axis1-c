package testData;

import javax.xml.namespace.QName;

import org.apache.axis.AxisFault;
import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;

/**
 * @author hemapani
 */
public class SampleHandlerThrowsFault extends BasicHandler{

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#getName()
	 */
	public String getName() {
		return "sample fault handler";
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#getUnderstandHeaders()
	 */
	public QName[] getUnderstandHeaders() {
		return new QName[]{};
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#invoke(org.apache.axismora.MessageContext)
	 */
	public void invoke(MessageContext msgdata) throws AxisFault {
		throw new AxisFault();
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#onFalult(org.apache.axismora.MessageContext)
	 */
	public void onFalult(MessageContext msgdata) {
		System.out.println(getName()+ "runing on fault");
	}
}
