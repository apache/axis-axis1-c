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
import org.apache.axis.discovery.core.DiscoveryException;
import org.apache.axis.discovery.core.DiscoveryMessage;
import org.apache.axis.discovery.core.Transceiver;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.IOException;

/**
 *  this class implements the listener; has a few places to override if you feel
 *  like it. Listening can be done in a seperate thread, if that is your wont
 *
 *@author     steve loughran
 *@created    August 30, 2002
 */
public class DiscoveryListener implements Runnable {

    /**
     * cached transceiver
     */
    private Transceiver transceiver;

    /**
     *  map of uris to urls
     */
    private UriStore map;

    /**
     *  our log
     */
    private static Log log = LogFactory.getLog(DiscoveryListener.class);

    /**
     *  a do-not-cache key used to spin the listener
     */
    private volatile boolean timeToDie = false;
    /**
     *  axis binder
     */
    private AxisBinder axisBinder;

    /**
     *  creat w/ map and transport
     *
     *@param  map
     *@param  transceiver
     */
    public DiscoveryListener(UriStore map, Transceiver transceiver) {
        this.map = map;
        this.transceiver = transceiver;
    }


    /**
     *  accessor
     *
     *@return    current transport
     */
    public Transceiver getTransceiver() {
        return transceiver;
    }


    /**
     *@return
     */
    public UriStore getMap() {
        return map;
    }


    /**
     *  Wake up, time to die. Set this to stop the listener next iteration. An
     *  alternate approach would be to send a packet to the listener, restrict
     *  it to local machine for security.
     */
    public void setTimeToDie() {
        timeToDie = true;
    }


    /**
     *  Gets the axisBinder attribute of the DiscoveryListener object
     *
     *@return    The axisBinder value
     */
    public AxisBinder getAxisBinder() {
        return axisBinder;
    }


    /**
     *  Sets the axisBinder attribute of the DiscoveryListener object
     *
     *@param  axisBinder  The new axisBinder value
     */
    public void setAxisBinder(AxisBinder axisBinder) {
        this.axisBinder = axisBinder;
    }


    /**
     *  start the thread running
     *
     *@param  daemon  Description of the Parameter
     */
    public void start(boolean daemon) {
        Thread thread = new Thread(this, "DiscoveryListener");
        thread.setDaemon(daemon);
        thread.start();
    }


    /**
     *  thread callback. This stuff is running in a different thread from the
     *  rest
     */
    public void run() {
        log.info("starting listener loop");
        while (!timeToDie) {
            try {
                DiscoveryMessage request = transceiver.receiveMessage(Const.SERVER_TIMEOUT);
                //resync our bindings;
                //and not before.
                if (axisBinder != null) {
                    axisBinder.resync();
                }
                //check for a null request
                if (request == null) {
                    continue;
                }

                //check it is for a type we want
                if (!request.isType(DiscoveryMessage.MESSAGE_REQUEST)) {
                    log.info("ignoring message of type " + request);
                    continue;
                }
                //now handle the message
                DiscoveryMessage responses[] = processRequest(request);
                for (int i = 0; i < responses.length; i++) {
                    transceiver.sendMessage(responses[i]);
                }
            } catch (IOException e) {
                log.error("processing a request", e);
            } catch (DiscoveryException e) {
                log.error("processing a request", e);
            }
        }
        destroy();

    }

    private void destroy() {
        transceiver.destroy();
    }


    /**
     *  subclassable handler of request to response processing
     *
     *@param  request
     *@return
     */
    public DiscoveryMessage[] processRequest(DiscoveryMessage request) {
        logRequest(request);
        DiscoveryMessage[] responses = map.processRequest(request);
        logResponses(responses);
        return responses;
    }


    /**
     *  log a request
     *
     *@param  request  Description of the Parameter
     */
    public void logRequest(DiscoveryMessage request) {
        log.info("received " + request);
    }


    /**
     *  log a response
     *
     *@param  responses
     */
    public void logResponses(DiscoveryMessage[] responses) {
        for (int i = 0; i < responses.length; i++) {
            log.info("response =" + responses[i]);
        }
        if (responses.length == 0) {
            log.info("no match");
        }
    }


    /**
     *  stop us
     */
    public void stop() {
        setTimeToDie();
    }

}

