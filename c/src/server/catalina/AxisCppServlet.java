/* -*- Java -*- */

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
 * 4. The names "SOAP" and "Apache Software Foundation" must
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

/*
 * The AxisCpp that handles and delegate controles to JNI Axis C++ server
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
 *
 */

import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;


public class AxisCppServlet extends HttpServlet {


    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
        throws IOException, ServletException
    {
		int bodySize = request.getContentLength();
		PrintWriter pw = new PrintWriter(response.getWriter());
		response.setContentType("text/xml"); //change this according to the SOAP 1.2
			
		if(0 != bodySize)
		{
			byte [] bodyContent = new byte[bodySize+1];
			ServletInputStream bodyReader = request.getInputStream();
			try{
				bodyReader.read(bodyContent, 0, bodySize); 
			}
			catch(IOException ex)
			{
				pw.write("<error>");
				pw.write("bdy size: "+bodySize+" \nContent : "+ex.getMessage());
				pw.write("</error>");
				return;
			}
						
			//String contentType = request.getContentType();
			int headerCount = 0;
			Vector headers = new Vector();
			Enumeration names = request.getHeaderNames();
			while(names.hasMoreElements())
			{
				headerCount++;
				String headerName = (String) names.nextElement();
				headers.addElement(headerName);//Add the name
				headers.addElement(request.getHeader(headerName)); //add the value
			}

			if(bodySize > 0)
				AxisCppContentHandler.processContent(bodyContent, bodyContent.length, 
												 headers, headerCount);
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			out.write(bodyContent);
			pw.write(out.toString());
		}
		
		//setup the response
		pw.write("<error>");
		pw.write("Error - body content empty");
		pw.write("</error>");
    }
	public void doPost(HttpServletRequest request,
                      HttpServletResponse response)
        throws IOException, ServletException
    {
        doGet(request, response);
    }
}



