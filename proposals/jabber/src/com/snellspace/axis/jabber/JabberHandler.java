package com.snellspace.axis.jabber;

import org.jabber.jabberbeans.Packet;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public interface JabberHandler {

  public void receivedPacket(
    Packet packet);

}
