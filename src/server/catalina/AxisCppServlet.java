/* -*- Java -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
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
		response.setContentType("text/xml"); //change this according to the SOAP 1.2
			
		if(0 != bodySize)
		{
			OutputStream bodyWriter = response.getOutputStream();
			InputStream bodyReader  = request.getInputStream();
			int contentLength = request.getContentLength();
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
				AxisCppContentHandler.processContent(bodyReader, headers, 
													 bodyWriter, contentLength);	
		}
		PrintWriter pw = new PrintWriter(response.getWriter());
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



