package com.snellspace.axis.jabber;

import java.util.Enumeration;

import javax.xml.soap.SOAPException;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.components.uuid.UUIDGenFactory;
import org.apache.axis.handlers.BasicHandler;
import org.jabber.jabberbeans.InfoQuery;
import org.jabber.jabberbeans.InfoQueryBuilder;
import org.jabber.jabberbeans.Packet;
import org.jabber.jabberbeans.XMLData;
import org.jabber.jabberbeans.Extension.MessageExtension;
import org.jabber.jabberbeans.Extension.QueryExtension;
import org.jabber.jabberbeans.sax.Extension.DefaultExtension;
import org.jabber.jabberbeans.util.JID;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class JabberSender 
  extends BasicHandler {

  public void invoke(
    MessageContext context) 
      throws AxisFault {
        JabberConnection connection = 
          initializeConnection(context);
        Holder holder = new Holder();
        Packet request = 
          createRequestPacketFromMessage(
            context.getRequestMessage(), 
            context);
        connection.send(request, holder);
        try {
          holder.waitForPacket();
        } catch (InterruptedException e) {}
        Packet response = holder.getPacket();
        context.setResponseMessage(
          createResponseMessageFromPacket(
            response, 
            context));
        connection.disconnect();
        connection = null;
  }

  private JabberConnection initializeConnection(
    MessageContext context) {
      JID clientID = JID.fromString(context.getUsername());
      String password = context.getPassword();
      JabberConnection connection = new JabberConnection();
      connection.login(clientID, password);
      return connection;
  }

  private Packet createRequestPacketFromMessage(
    Message message,
    MessageContext context) {
      Packet packet = null;
      try {
        InfoQueryBuilder iqb = new InfoQueryBuilder();
        iqb.setIdentifier(getID());
        iqb.setType("set");
        iqb.setToAddress(
          JID.fromString(
            context.getStrProp(
              MessageContext.TRANS_URL)));
        iqb.addExtension(new AxisExtension(message));
        packet = iqb.build();
      } catch (InstantiationException ie) {}
      return packet;
  }

  private String getID() {
    return UUIDGenFactory.
      getUUIDGen("org.apache.axis.components.uuid.SimpleUUIDGen").nextUUID();
  }

  private Message createResponseMessageFromPacket(
    Packet packet,
    MessageContext context) {
      Message message = null;
      if (packet instanceof InfoQuery) {
        InfoQuery iq = (InfoQuery)packet;
        for (
          Enumeration e = iq.Extensions();
          e.hasMoreElements();) {
            DefaultExtension ext = (DefaultExtension)e.nextElement();
            StringBuffer buf = new StringBuffer(ext.toString());
            if (buf.indexOf(Constants.URI_DEFAULT_SOAP_ENV) > 0) {
                message = new Message(ext.toString());
            } else {
              // ignore non soap stuff for now
            }
        }
      }
      return message;
  }

  private class Holder 
    implements JabberHandler {
      private Packet packet;
      public Packet getPacket() {
        return this.packet;
      }
      public synchronized void waitForPacket()
        throws InterruptedException {
          if (packet != null) return;
          wait();
      }
      public synchronized void receivedPacket(
        Packet packet) {
          this.packet = packet;
          notifyAll();
      }
  }
  
  public static class AxisExtension
    extends XMLData 
    implements MessageExtension, QueryExtension {
      
      private Message message;
      
      public AxisExtension(
        Message message) {
          this.message = message;
      }
      
      public void appendItem(
        StringBuffer buffer) {
          try {
            String env = 
              message.getSOAPPart().
                getEnvelope().toString();
            buffer.append(env);
          } catch (SOAPException e) {}
      }      
  }
}
