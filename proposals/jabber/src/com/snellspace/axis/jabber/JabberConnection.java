package com.snellspace.axis.jabber;

import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;

import org.jabber.jabberbeans.ConnectionBean;
import org.jabber.jabberbeans.ConnectionEvent;
import org.jabber.jabberbeans.ConnectionListener;
import org.jabber.jabberbeans.ContentPacket;
import org.jabber.jabberbeans.InfoQuery;
import org.jabber.jabberbeans.InfoQueryBuilder;
import org.jabber.jabberbeans.Packet;
import org.jabber.jabberbeans.PacketEvent;
import org.jabber.jabberbeans.PacketListener;
import org.jabber.jabberbeans.PresenceBuilder;
import org.jabber.jabberbeans.Extension.IQAuthBuilder;
import org.jabber.jabberbeans.util.JID;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class JabberConnection
  implements ConnectionListener, PacketListener {

  public static boolean DEBUG = false;

  protected ConnectionBean cb;
  protected String loginid;
  protected boolean connected;
  protected HashMap requests = new HashMap();
 
  public void disconnect() {
    cb.disconnect();
    loginid = null;
    connected = false;
  }

  public void send(
    Packet packet) {
      send(packet, null);
  }
  
  public void send(
    Packet packet,
    JabberHandler handler) {
      if (packet instanceof InfoQuery) {
        InfoQuery iq = (InfoQuery)packet;
        requests.put(
          iq.getIdentifier(),
          handler);
      }
      cb.send(packet);
  }

  public void login(
    String clientID,
    String password) {
      login(JID.fromString(clientID), password);
  }

  public void login(
    JID clientID,
    String password) {
      cb = new ConnectionBean();
      try {
        cb.connect(InetAddress.getByName(clientID.getServer()));
      } catch (UnknownHostException e) {
        throw new IllegalArgumentException(); // fix it
      } catch (IOException e) {
        throw new IllegalArgumentException(); // fix it
      }
      cb.addConnectionListener(this);
      cb.addPacketListener(this);
      InfoQueryBuilder iqb = new InfoQueryBuilder();
      IQAuthBuilder iqAuthb = new IQAuthBuilder();
      iqb.setType("set");
      iqAuthb.setUsername(clientID.getUsername());
      iqAuthb.setPassword(password);
      iqAuthb.setResource(clientID.getResource());
      InfoQuery iq = null;
      try {
        iqb.addExtension(iqAuthb.build());
        iq = (InfoQuery)iqb.build();
      } catch (InstantiationException ie) {
        throw new IllegalArgumentException(); // fix it
      }
      loginid = iq.getIdentifier();
      cb.send(iq);
  }
  
  public void receivedPacket(
    PacketEvent event) {
    Packet packet = event.getPacket();
    if (DEBUG) {
      System.out.println("receivedPacket >>"  + packet);
    }
    if (!connected) {
      if (processLogin(packet)) {
        connected = true;
      } else {
        connected = false;
      }
      return;
    }
    processPacket(packet);
  }

  protected void processPacket(
    Packet packet) {      
      try {
        ContentPacket cp = (ContentPacket)packet;
        JabberHandler handler = 
          (JabberHandler)requests.get(
            cp.getIdentifier());
        if (handler != null) {
          handler.receivedPacket(packet);
        }
      } catch (Exception e) {
        // ignore everything else 
      }
  }

  public void connectionChanged(
    ConnectionEvent event) {
      // ignore for now
  }

  public void sentPacket(
    PacketEvent event) {
      // ignore for now   
  }

  public void sendFailed(
    PacketEvent event) {
      // ignore for now
  }

  private boolean processLogin(
    Packet packet) {
      if( !(packet instanceof InfoQuery))
        return false;
      InfoQuery iq=(InfoQuery)packet;       
      if (!iq.getIdentifier().equals(loginid)) 
        return false;
      if(iq.getType().equals("result")) {     
        try {
          PresenceBuilder pb = new PresenceBuilder();
          cb.send(pb.build());
        } catch (InstantiationException e) {
          return false;
        }
      } else {
      if(iq.getType().equals("error")) {
        return false;
      } else {
        return false;
      }
    }       
    return true;
  }
      
}
