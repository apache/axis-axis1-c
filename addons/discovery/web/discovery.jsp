<%@ page language="java"
    session="false" contentType="text/html;charset=iso-8859-1"
    import="org.apache.axis.discovery.client.Client,
                 java.util.List,
                 org.apache.axis.discovery.core.Const,
                 java.io.IOException,
                 java.io.PrintWriter,
                 java.io.StringWriter"%>
<html><head>
<title>Axis WS-Discovery</title>
</head><html>
<body bgcolor="#ffffff">
<h2>Axis Discovery</h2>

<%!
    public static final String uriParam="uri";
    public static final String ttlParam = "ttl";

    public void listEndpoints( String[] endpoints, JspWriter  out) throws IOException{
        int length = endpoints.length;
        out.write("Found "+length+" endpoint(s)");
        out.write("<p><table>");
        for (int i = 0; i < length; i++) {
            String endpoint = endpoints[i];
            out.write("<tr><td>");
            out.write(endpoint);
            out.write("</td></tr>\n");
        }
        out.write("</table >");
    }

    public void logException(JspWriter out, Throwable e) throws IOException {
        out.write("<h2>Exception ");
        out.write(e.toString());
        out.write("</h2>\n");
        if(e.getMessage()!=null) {
            out.write(e.getMessage());
        }
        out.write("\n<pre>\n");
        StringWriter sw = new StringWriter();
        e.printStackTrace(new PrintWriter(sw));
        out.write(sw.toString());
        out.write("</pre>");
    }

    public int getIntParam(HttpServletRequest request, String name, int defVal) {
        int result;
        try {
            result = Integer.parseInt(request.getParameter(name));
        } catch (NumberFormatException e) {
            result = defVal;
        }
        return result;
    }
%>

<%
    /*
     * demo page to use discovery to find and display services.
     * yes, jsps with code are ugly, but JSTL is even worse to debug
     */

    String uri=request.getParameter(uriParam);
    if(uri==null) {
        %>
<form method="get">
<table border="0">
<tr>
<td>url</td>
<td>
<input type="text" name="uri" size="80">
</td>
</tr>
<tr>
<tr>
<td>time to live (0-255)</td>
<td>
<input type="text" name="ttl" size="10">
</td>
</tr>
<tr>
    <td>timeout (seconds)</td>
    <td>
    <input type="text" name="timeout" size="10">
    </td>
</tr>
<tr>
    <td>max number to find</td>
    <td>
    <input type="text" name="limit" size="10">
    </td>
</tr>
<tr><td>
<input type="submit" name="locate" value="Submit">
</td>
</tr>
</table>
</form>
        <%
    } else {
        int ttl= getIntParam(request,"ttl",3);
        int timeout= getIntParam(request, "ttl", 1)*1000;
        int limit= getIntParam(request, "limit", 0);
        %>
        <p>Searching...<p>
        <%
        try {
            Client client;
            List responses;
            String[] endpoints;
            client = new Client();
            responses= client.findEndpoints(uri,
                    ttl,
                    timeout,
                    limit);
            endpoints = client.extractEndpointArray(responses);
            listEndpoints(endpoints,out);

        } catch (Throwable e) {
            logException(out,e);
        }
    }
%>

</body>
</html>
