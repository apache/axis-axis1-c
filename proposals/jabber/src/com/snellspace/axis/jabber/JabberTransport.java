package com.snellspace.axis.jabber;

import org.apache.axis.AxisEngine;
import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.client.Call;
import org.apache.axis.client.Transport;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class JabberTransport 
  extends Transport {

  public static final String DEFAULT_TRANSPORT_NAME = "JabberSender";

  private String to;

  public JabberTransport() {
    transportName = DEFAULT_TRANSPORT_NAME;
  }
  
  public JabberTransport(
    String transportName) {
      this.transportName = transportName;
  }

  public String getTo() {
    return to;
  }
  
  public void setTo(
    String to) {
      this.to = to;
  }
  
  public void setupMessageContextImpl(
    MessageContext context,
    Call call,
    AxisEngine engine)
      throws AxisFault {
        context.setProperty(
          MessageContext.TRANS_URL,
          getTo());
  }

}
