/*
* The Apache Software License, Version 1.1
*
* Copyright (c) 2002 The Apache Software Foundation.  All rights
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
* 3. The end-user documentation included with the redistribution, if
*    any, must include the following acknowlegement:
*       "This product includes software developed by the
*        Apache Software Foundation (http://www.apache.org/)."
*    Alternately, this acknowlegement may appear in the software itself,
*    if and wherever such third-party acknowlegements normally appear.
*
* 4. The names "The Jakarta Project", "Ant", and "Apache Software
*    Foundation" must not be used to endorse or promote products derived
*    from this software without prior written permission. For written
*    permission, please contact apache@apache.org.
*
* 5. Products derived from this software may not be called "Apache"
*    nor may "Apache" appear in their names without prior written
*    permission of the Apache Group.
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


package test;

import com.meterware.httpunit.*;

/**
 * test the services
 * @author Steve Loughran
 * @created Jul 10, 2002 12:09:06 AM
 */

public class AdminTest extends HttpUnitTestBase {

    private String servlet;

    private String invalid_service;

    private boolean isProduction=false;

    public AdminTest(String name) {
        super(name);
    }

    /**
     *  The JUnit setup method
     *
     */
    public void setUp() throws Exception {
        super.setUp();
        servlet = url + "/servlet/AdminServlet";
    }

    /**
     * verify the page is there
     * @throws Exception
     */
    public void testPage() throws Exception {
        WebRequest request = new GetMethodWebRequest(servlet);
        assertStringInBody(request, "Server");
    }

    /**
     * dev systems have commands
     * @throws Exception
     */
    public void testPageHasCommands() throws Exception {
        WebRequest request = new GetMethodWebRequest(servlet);
        assertStringInBody(request, "Server");
        WebConversation session = new WebConversation();
        WebResponse response = session.getResponse(request);
        String body = response.getText();
        assertTrue("start server", body.indexOf("start server")>0);
        assertTrue("stop server", body.indexOf("stop server") > 0);
        assertTrue("Current Load",body.indexOf("Current load") > 0);
    }

    /**
     * test stop command
     * @throws Exception
     */
    public void testStop() throws Exception {
        WebRequest request = new GetMethodWebRequest(servlet);
        request.setParameter("cmd", "stop");
        assertStringInBody(request, "Server is stopped");
    }

    /**
     * test start command
     * @throws Exception
     */
    public void testStart() throws Exception {
        WebRequest request = new GetMethodWebRequest(servlet);
        request.setParameter("cmd", "start");
        assertStringInBody(request, "Server is running");
    }

}
