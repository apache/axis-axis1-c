package testData;

import javax.xml.namespace.QName;

import org.apache.axis.AxisFault;
import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;

/**
 * @author hemapani
 */
public class SampleHandler1 extends BasicHandler{

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#getName()
	 */
	public String getName() {
		return "sample handler 1";
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#getUnderstandHeaders()
	 */
	public QName[] getUnderstandHeaders() {
		return new QName[]{new QName("http//ws.apache.org","header1"),new QName("http//ws.apache.org","header2")};
	}

	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#invoke(org.apache.axismora.MessageContext)
	 */
	public void invoke(MessageContext msgdata) throws AxisFault {
		System.out.println(getName()+ "runing");
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#onFalult(org.apache.axismora.MessageContext)
	 */
	public void onFalult(MessageContext msgdata) {
		System.out.println(getName()+ "runing on fault");
	}
}
