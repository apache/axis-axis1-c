package com.snellspace.axis.jabber;

import java.util.Enumeration;

import org.apache.axis.AxisEngine;
import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.server.AxisServer;
import org.jabber.jabberbeans.InfoQuery;
import org.jabber.jabberbeans.InfoQueryBuilder;
import org.jabber.jabberbeans.Packet;
import org.jabber.jabberbeans.sax.Extension.DefaultExtension;
import org.jabber.jabberbeans.util.JID;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class JabberServer
  extends JabberConnection {

  private static AxisEngine engine;

  private String resourceID;
  private String transportName = JabberTransport.DEFAULT_TRANSPORT_NAME;
  
  public static final String JABBER_FROM = "JABBER.FROM";
  public static final String JABBER_TO   = "JABBER.TO";
  public static final String JABBER_ID   = "JABBER.ID";

  public JabberServer(
    String identity,
    String password) {
      this(JID.fromString(identity), password);
  }

  public JabberServer(
    JID identity,
    String password) {
      resourceID = identity.getResource();
      login(identity, password);
  }

  public String getTransportName() {
    return this.transportName;
  }
  
  public void setTransportName(
    String transportName) {
      this.transportName = transportName;
  }

  public String getServerID() {
    return this.resourceID;
  }

  public void setServerID(
    String id) {
      this.resourceID = id;
  }

  protected void processPacket(
    Packet packet) {
      if (packet instanceof InfoQuery) {
        InfoQuery iq = (InfoQuery)packet;
        if ("set".equals(iq.getType())) {
          for (
            Enumeration e = iq.Extensions();
            e.hasMoreElements();) {
              DefaultExtension ext = (DefaultExtension)e.nextElement();
              StringBuffer buffer = new StringBuffer(ext.toString());
              if (buffer.indexOf(Constants.URI_DEFAULT_SOAP_ENV) > 0) {
                JID from = iq.getFromAddress();
                JID to = iq.getToAddress();
                String id = iq.getIdentifier();
                String envbuf =
                  buffer.substring(
                    buffer.indexOf(">") + 1,
                    buffer.indexOf("</soap>"));
                Message soapMessage = new Message(envbuf);
                try {
                  processMessage(from,to,id,soapMessage);
                } catch (AxisFault ex) {
                  System.out.println(ex);
                }
              } else {
                // ignore for now
              }
          }
        } else {
          // ignore for now
        }
      }
  }  

  public static synchronized AxisEngine getAxisEngine() {
    if (engine == null) {
      engine = new AxisServer();
    }
    return engine;
  }

  private void processMessage(
    JID from,
    JID to,
    String id,
    Message soapMessage)
      throws AxisFault {
        AxisEngine engine = JabberServer.getAxisEngine();
        MessageContext context = 
          new MessageContext(engine);
        context.setProperty(JABBER_FROM, from.toString());
        context.setProperty(JABBER_TO, to.toString());
        context.setProperty(JABBER_ID, id);
        context.setRequestMessage(soapMessage);
        context.setTransportName(getTransportName());
        context.setTargetService(resourceID);
        
        engine.invoke(context);
        
        Message response = context.getResponseMessage();
        
        InfoQueryBuilder iqb = new InfoQueryBuilder();
        iqb.setIdentifier(id);
        iqb.setToAddress(from);
        iqb.setFromAddress(to);
        iqb.setType("result");
        iqb.addExtension(
          new JabberSender.AxisExtension(
            response));
        try {
          send(iqb.build());
        } catch (InstantiationException e) {
          System.out.println(e);
        }
  }
}
