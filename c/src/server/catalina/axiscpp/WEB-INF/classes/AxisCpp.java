import java.io.*;
import java.text.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;

/**
 * The AxisCpp that handles and delegate controles to JNI Axis C++ server
 *
 * @author Lilantha Darshana
 */

public class AxisCpp extends HttpServlet {


    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
        throws IOException, ServletException
    {
        response.setContentType("text/xml"); //change this according to the SOAP 1.2
		//request.getHeader
		//request.getMethod
		
		InputStream in = request.getInputStream;
        PrintWriter out = response.getWriter();
		
		AxisCppHandler.Delegate(in, out);
    }
	public void doPost(HttpServletRequest request,
                      HttpServletResponse response)
        throws IOException, ServletException
    {
        doGet(request, response);
    }
}



