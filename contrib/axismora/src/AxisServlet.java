/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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
 *    Apache Software Foundation (http://www.apache.org/)."
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

import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.axismora.Constants;
import org.apache.axismora.engine.AxisEngine;
import org.apache.axismora.servlet.ServletSession;

/**
 * This class is the Transport Listener. It take care of the removing the 
 * HTTP headers from the request. Rest will be processed by the back end.
 * So the Axis is a Servlet now with all these codes at the back end.  
 * @author vtpavan
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class AxisServlet extends HttpServlet {
    private static AxisEngine axisEngine;
    private String serviceName;
    private InputStream in;
    //private OutputStream out;

    public AxisServlet() {
    }
    private AxisEngine getAxisEngine(ServletContext context) throws Exception {
        if (axisEngine == null){
			axisEngine = new AxisEngine(Constants.SERVER_CONFIG_FILE,context);
        }
        return axisEngine;
    }
    
	public void init(ServletConfig arg0) throws ServletException {
		try{
			axisEngine = getAxisEngine(arg0.getServletContext());
		}catch(Exception e){
			throw new ServletException(e);
		}				
	}

    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        PrintWriter print = new PrintWriter(response.getOutputStream());
        try {
            //see wheather this is a wsdl file request ....
            String queryString = request.getQueryString();
            if (queryString != null) {
                if (queryString.equalsIgnoreCase("wsdl")) {
                    //k ... process the wsdl request 
                    //TODO... support wsdl requests
                }
            }

            axisEngine = getAxisEngine(null);
            in = request.getInputStream();
            //out = request.getOutputStream();

            String soapAction = this.getServiceName(request);

            response.setContentType("text/html");
            /**
             * Calling the SOAP engine to process the SOAP message
             */
            axisEngine
                .process(
                    soapAction,
                    in,
                    response.getOutputStream(),
                    new ServletSession(request.getSession()),
                    null //TODO set username form request
            , null //TODO set pawssword from request
            , null //TODO set encoding from request
            );
        } catch (Exception e) {
            e.printStackTrace(print);
            print.flush();
        }
    }

    /* 
     * get the Service Name from the SOAP action. Another option is to take it from the
     * request URI. We should evenually support the both
     */
    private String getServiceName(HttpServletRequest request) {
        String soapAction = request.getHeader("SOAPAction");

        int len = soapAction.length();
        if (len > 0)
            soapAction = soapAction.substring(1, len - 1);
        return soapAction.intern();
    }

    public void doPost(HttpServletRequest req, HttpServletResponse res)
        throws ServletException, IOException {
        doGet(req, res);
    }

}
