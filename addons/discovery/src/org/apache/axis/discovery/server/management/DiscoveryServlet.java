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
package org.apache.axis.discovery.server.management;

import org.apache.axis.AxisEngine;
import org.apache.axis.AxisFault;
import org.apache.axis.discovery.server.AxisBinder;
import org.apache.axis.discovery.server.DiscoveryServer;
import org.apache.axis.discovery.server.ServiceEntry;
import org.apache.axis.transport.http.AxisServletBase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Iterator;

/**
 *  This servlet does two things.
 * One, it starts and stops the server, with a binding to axis
 * Two, it provides a listing of endpoints, if the appropriate
 * config flag is set
 *@author                 Steve Loughran
 *@web.servlet            name="discovery"
 *@web.servlet-mapping    url-pattern="/discovery"
 */
public class DiscoveryServlet extends AxisServletBase {

    /**
     *  who our discovery server
     */
    private DiscoveryServer _server;
    /**
     *  bridging code
     */
    private AxisBinder axisBridge;
    /**
     *  logging entry
     */
    private static Log log = LogFactory.getLog(DiscoveryServlet.class);


    /**
     *  birth
     */
    public void init() {
        log.info("DiscoveryServlet::init");
        super.init();
    }


    /**
     *  handle destruction
     */
    public void destroy() {
        log.info("DiscoveryServlet::destroy");
        if (_server != null) {
            _server.stop();
        }
        super.destroy();
    }


    /**
     *  incoming get request triggers initialization.
     *
     *@param  request
     *@param  response
     *@exception  ServletException             Description of the Exception
     *@exception  IOException                  Description of the Exception
     *@throws  javax.servlet.ServletException
     *@throws  java.io.IOException
     */
    protected void doGet(HttpServletRequest request,
                         HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><head><title>Discovery Status</title></head>");
        out.println("<body bgcolor=#ffffff>");
        if (getServer(request) == null) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            out.println("Cannot start Discovery, check error logs");
            out.println("</body></html>");
            return;
        }
        listEntries(out);
        out.println("</body></html>");
    }

    /**
     * list the entries into a table
     * @param out
     */
    private void listEntries(PrintWriter out) {
        int count = 0;
        Iterator it = _server.getStore().getEntries();
        out.println("<table border=1>");
        out.print("<tr><td>URI</td><td>URL</td>hits</td>");
        for (; it.hasNext(); count++) {
            ServiceEntry entry = (ServiceEntry) it.next();
            out.print("<tr><td>");
            out.print(entry.getUri());
            out.print("</td><td>");
            out.print(entry.getUrl());
            out.print("</td><td>");
            out.print(entry.getHitCountInt());
            out.print("</td></tr>");
        }
        out.println("</table>");
        out.println(" There are " + count + " entries");
        out.println("<hr>");
        out.println("<table border=0>");

        out.print("<tr><td>Messages in:</td><td>");
        out.print(_server.getTransceiver().getReceipts());
        out.print("</td></tr>");

        out.print("<tr><td>Failures in:</td><td>");
        out.print(_server.getTransceiver().getFailures());
        out.print("</td></tr>");

        out.print("<tr><td>Messages out:</td><td>");
        out.print(_server.getTransceiver().getSends());
        out.print("</td></tr>");

        out.println("</table>");

        out.print("</td><td>");
    }


    /**
     *  Get the discovery server, creating it if need be
     *
     *@param  request
     *@return          null if we couldnt start
     */
    private DiscoveryServer getServer(HttpServletRequest request) {
        if (_server == null) {
            try {
                _server = new DiscoveryServer();
            } catch (IOException e) {
                log.fatal("creating a new DiscoveryServer", e);
                return null;
            }
            AxisEngine engine;
            engine = getEngineWithFaultHandling();
            if (engine == null) {
                return null;
            }
            axisBridge = new AxisBinder();
            String baseURL = getWebappBase(request);
            axisBridge.bind(baseURL, engine, _server.getStore(), 1000);
            _server.startInNewThread();
        }
        return _server;
    }

    private AxisEngine getEngineWithFaultHandling() {
        AxisEngine engine;
        try {
            engine = getEngine();
        } catch (AxisFault axisFault) {
            log.fatal("retrieving the Axis engine", axisFault);
            engine = null;
        }
        return engine;
    }

}

