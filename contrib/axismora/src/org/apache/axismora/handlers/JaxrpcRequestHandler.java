package org.apache.axismora.handlers;

import javax.xml.rpc.handler.Handler;

import org.apache.axis.AxisFault;
import org.apache.axismora.MessageContext;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class JaxrpcRequestHandler extends BasicHandler {
	private Handler handler;
	public JaxrpcRequestHandler(Handler handler){
		this.handler = handler;
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.Handler#invoke(org.apache.axismora.MessageContext)
	 */
	public void invoke(MessageContext msgdata) throws AxisFault {
		if(msgdata.isPassPivot()){
			handler.handleResponse(msgdata);
		}else
			handler.handleRequest(msgdata);
	}
}
