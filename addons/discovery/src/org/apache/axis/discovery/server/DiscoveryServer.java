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

package org.apache.axis.discovery.server;

import org.apache.axis.discovery.core.Const;
import org.apache.axis.discovery.core.LoggingTransceiver;
import org.apache.axis.discovery.core.MulticastTransceiver;
import org.apache.axis.discovery.core.Transceiver;
import org.apache.axis.discovery.core.XmlMarshaller;
import org.apache.axis.discovery.server.management.ServerMBean;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

/**
 *  This is a discovery server: a listener, a transport and a uristore to map uris to
 *  urls
 *  @author steve loughran
 */
public class DiscoveryServer implements ServerMBean {

    /**
     *  a listener
     */
    private DiscoveryListener listener;
    /**
     *  logging
     */
    private LoggingTransceiver transceiver;

    /**
     *  Description of the Field
     */
    private UriStore map;

    /**
     *  construct a server instance
     * @param transceiver existing transceiver
     * @param registerSelf flag set to true if we want to self register
     * @exception  IOException  trouble with networking
     */
    public DiscoveryServer(Transceiver transceiver, boolean registerSelf) throws IOException {
        map = new UriStore();
        setTransceiver(transceiver);
        if (registerSelf) {
            map.registerSelf(transceiver.getReceiverURL());
        }
        listener = new DiscoveryListener(map, transceiver);
    }


    /**
     *  construct a server instance using the default port and address values
     *  and the xml marshaller
     * @exception  IOException  trouble with networking
     */
    public DiscoveryServer() throws IOException {
        this(new MulticastTransceiver(Const.MBONE_ADDRESS,
                Const.MBONE_PORT,
                Const.MBONE_PORT,
                new XmlMarshaller()),
                Const.AUTO_REGISTER_SELF);
    }

    /**
     *  make sure we stop
     *
     *@exception  Throwable  Description of the Exception
     */
    protected void finalize() throws Throwable {
        stop();
    }


    /**
     *  start listening in a separate thread
     */
    public void startInNewThread() {
        listener.start(false);
    }


    /**
     *  stop listening
     */
    public void startInThisThread() {
        listener.run();
    }


    /**
     *  stop listening, if we are
     */
    public void stop() {
        if (listener != null) {
            listener.stop();
        } else {
            transceiver.destroy();
        }
    }

    /**
     * set the transceiver, wrapping it in a logger
     * @param transceiver
     */
    public void setTransceiver(Transceiver transceiver) {
        this.transceiver = new LoggingTransceiver(transceiver);
    }

    /**
     * logging transceivers are assigned without wrapping
     * @param transceiver
     */
    public void setTransceiver(LoggingTransceiver transceiver) {
        this.transceiver = transceiver;
    }

    /**
     * get access to the uri store
     * @return
     */
    public UriStore getMap() {
        return map;
    }

    /**
     * set access to the URI store
     * @param map
     */
    public void setMap(UriStore map) {
        this.map = map;
    }

    /**
     *  get the current listener
     *
     *@return    a listener
     */
    public DiscoveryListener getListener() {
        return listener;
    }


    /**
     *  get the current transport
     *
     *@return    the transport
     */
    public LoggingTransceiver getTransceiver() {
        return transceiver;
    }


    /**
     *  get our uri map
     *
     *@return    the store
     */
    public UriStore getStore() {
        return map;
    }


    /**
     *  string form of the multicast address
     *
     *@return    a dotted ip address
     */
    public String getURL() {
        return getTransceiver().getReceiverURL();
    }


    /**
     *  how many sent
     *
     *@return    number >=0
     */

    public Integer getMessagesSent() {
        return new Integer(getTransceiver().getSends());
    }


    /**
     *  how many received (inc failures)
     *
     *@return    number>=0
     */
    public Integer getMessagesReceived() {
        return new Integer(getTransceiver().getReceipts());
    }


    /**
     *  how many failures received
     *
     *@return    number>=0
     */
    public Integer getFailures() {
        return new Integer(getTransceiver().getFailures());
    }

    /**
     * set a new listener
     * @param listener listener
     */
    public void setListener(DiscoveryListener listener) {
        this.listener = listener;
    }

    /**
     *  entry point for demos
     *
     *@param  args
     *@throws  IOException
     */
    public static void main(String args[]) throws IOException {
        Log log = LogFactory.getLog(DiscoveryServer.class);
        log.info("Starting Discovery server");
        DiscoveryServer server = new DiscoveryServer();
        if (args.length > 0) {
            Properties props = new Properties();
            log.info("Loading properties file " + args[0]);
            props.load(new FileInputStream(args[0]));
            server.getStore().registerProperties(props);
        }
        server.startInThisThread();
        log.info("Stopping Discovery server");
    }


}

