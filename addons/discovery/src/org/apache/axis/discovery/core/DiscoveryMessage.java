/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */


package org.apache.axis.discovery.core;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.Serializable;
import java.net.DatagramPacket;
import java.net.InetAddress;

/**
 *  messages that get sent over the wire all fit into this format different
 *  messages use different elements all: messageID, messageType, uri request:
 *  scope response: url, description
 *
 */
public class DiscoveryMessage implements Serializable {
    /**
     *  message identifier
     */
    private int messageID;

    /**
     *  message type
     */

    private String messageType;

    /**
     *  what were you looking for
     */
    private String uri;

    /**
     *  scope string; valid on requests only
     */
    private String scope;

    /**
     *  response URL; "" or null for no match responses only
     */
    private String url;

    /**
     *  end user readable UTF-8 text. responses only
     */

    private String description = "";

    /**
     *  addresss of sender
     */
    private transient InetAddress sender;

    /**
     *  port of sender
     */
    private transient int senderPort;

    /**
     *  counter of messages
     */
    private static int idCounter = 1;

    /**
     *  our log
     */
    private static Log log = LogFactory.getLog(DiscoveryMessage.class);

    /**
     *  Construct; give the message a new ID (can be changed) you have to know
     *  what type of message you want when you create it.
     *
     *@param  messageType
     */
    public DiscoveryMessage(String messageType) {
        this.setMessageType(messageType);
        createID();
    }


    /**
     * empty ctor inits nothing
     */
    public DiscoveryMessage() {
    }


    /**
     *  give a message an id
     */
    public void createID() {
        setMessageID(getID());
    }


    /**
     *  stringify
     *
     *@return
     */
    public String toString() {
        String response = getMessageType() + " #" + getMessageID() + " from "
                + (sender != null ? sender.getHostAddress() : "unknown")
                + ":" + getSenderPort() + " scope [" + scope + "]"
                + " for [" + getUri() + "]";
        if (isType(MESSAGE_RESPONSE)) {
            response += " = [" + getUrl() + "]"
                    + "; " + getDescription();

        }
        return response;
    }


    /**
     *  test if a message matches a type
     *
     *@param  type
     *@return
     */
    public boolean isType(String type) {
        return getMessageType() != null && getMessageType().equals(type);
    }


    /**
     *  a request message
     */
    public static final String MESSAGE_REQUEST = "Find";

    /**
     *  a response message
     */
    public static final String MESSAGE_RESPONSE = "Found";

    /**
     *  a response message
     */
    public static final String MESSAGE_ADVERTISMENT = "Advertisment";


    /**
     *  synchronized access to a static ID counter.
     *
     *@return
     */
    protected static synchronized int getID() {
        return idCounter++;
    }


    /**
     *  create a new response message. copy over sender info
     *
     *@return    Description of the Return Value
     */
    public DiscoveryMessage createResponse() {
        DiscoveryMessage response = new DiscoveryMessage(MESSAGE_RESPONSE);
        response.setMessageID(getMessageID());
        response.setUri(getUri());
        response.setSender(getSender());
        response.setSenderPort(getSenderPort());
        return response;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getMessageID() {
        return messageID;
    }

    public void setMessageID(int messageID) {
        this.messageID = messageID;
    }

    public String getMessageType() {
        return messageType;
    }

    public void setMessageType(String messageType) {
        this.messageType = messageType;
    }

    public String getScope() {
        return scope;
    }

    public void setScope(String scope) {
        this.scope = scope;
    }

    public InetAddress getSender() {
        return sender;
    }

    public void setSender(InetAddress sender) {
        this.sender = sender;
    }

    public int getSenderPort() {
        return senderPort;
    }

    public void setSenderPort(int senderPort) {
        this.senderPort = senderPort;
    }

    public String getUri() {
        return uri;
    }

    public void setUri(String uri) {
        this.uri = uri;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }


    /**
     * test for an object being valid. Rules about optional parts for different
     * message types are implemented here.
     * @return true iff we are happy
     */
    public boolean isValid() {
        boolean valid;
        valid = messageID != 0;
        // non empty uri
        valid &= uri != null && uri.length() != 0;
        valid &= scope != null;
        if (isType(MESSAGE_RESPONSE)) {
            valid &= url != null && url.length() != 0;
        } else if (isType(MESSAGE_REQUEST)) {
            //any checks here?
        } else {
            //an unknown type means it aint valid
            valid = false;
        }
        return valid;
    }

    /**
     *  get the return address from a packet and save it to a message
     *
     * @param  packet received packet
     */
    public void extractReturnAddress(DatagramPacket packet) {
        setSender(packet.getAddress());
        setSenderPort(packet.getPort());
    }

    /**
     * address the packet to the sender for return packets
     * @param packet
     */
    public void addressToSender(DatagramPacket packet) {
        packet.setAddress(sender);
        packet.setPort(senderPort);
    }

    /**
     * equality test validates core fields but not transient tat like sender
     * @param o
     * @return true if the message is deemed equal
     */
    public boolean equals(Object o) {
        if (!(o instanceof DiscoveryMessage)) {
            return false;
        }

        DiscoveryMessage message = (DiscoveryMessage) o;

        if (messageID != message.messageID) {
            return false;
        }
        if (description == null
                ? message.description != null
                : !description.equals(message.description)) {
            return false;
        }
        if (messageType == null
                ? message.messageType != null
                : !messageType.equals(message.messageType)) {
            return false;
        }
        if (scope == null
                ? message.scope != null
                : !scope.equals(message.scope)) {
            return false;
        }
        if (uri == null
                ? message.uri != null
                : !uri.equals(message.uri)) {
            return false;
        }
        if (url == null
                ? message.url != null
                : !url.equals(message.url)) {
            return false;
        }

        return true;
    }

    /**
     * use the mesage ID as a hash chode
     * @return
     */
    public int hashCode() {
        return messageID;
    }

}

