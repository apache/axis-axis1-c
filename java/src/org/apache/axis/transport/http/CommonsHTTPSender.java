/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
package org.apache.axis.transport.http;

import org.apache.axis.AxisFault;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.components.net.TransportClientProperties;
import org.apache.axis.components.net.TransportClientPropertiesFactory;
import org.apache.axis.encoding.Base64;
import org.apache.axis.handlers.BasicHandler;
import org.apache.axis.utils.Messages;
import org.apache.commons.httpclient.Credentials;
import org.apache.commons.httpclient.Header;
import org.apache.commons.httpclient.HostConfiguration;
import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpConnectionManager;
import org.apache.commons.httpclient.MultiThreadedHttpConnectionManager;
import org.apache.commons.httpclient.UsernamePasswordCredentials;
import org.apache.commons.httpclient.methods.PostMethod;
import org.apache.commons.logging.Log;

import java.io.ByteArrayOutputStream;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.util.Hashtable;
import java.util.StringTokenizer;

/**
 * This class uses Jakarta Commons's HttpClient to call a SOAP server.
 *
 * @author Davanum Srinivas (dims@yahoo.com)
 */
public class CommonsHTTPSender extends BasicHandler {

    /** Field log           */
    protected static Log log =
        LogFactory.getLog(CommonsHTTPSender.class.getName());

    private HttpConnectionManager connectionManager;
    
    public CommonsHTTPSender() {
        // should pull settings for pool size, timeouts from
        // declarative configuration
        connectionManager = new MultiThreadedHttpConnectionManager();
    }

    /**
     * invoke creates a socket connection, sends the request SOAP message and then
     * reads the response SOAP message back from the SOAP server
     *
     * @param msgContext the messsage context
     *
     * @throws AxisFault
     */
    public void invoke(MessageContext msgContext) throws AxisFault {
        PostMethod method = null;
        
        if (log.isDebugEnabled()) {
            log.debug(Messages.getMessage("enter00",
                                          "CommonsHTTPSender::invoke"));
        }
        try {
            URL targetURL =
                new URL(msgContext.getStrProp(MessageContext.TRANS_URL));

            // no need to retain these, as the cookies/credentials are
            // stored in the message context across multiple requests.
            // the underlying connection manager, however, is retained
            // so sockets get recycled when possible.
            HttpClient httpClient = new HttpClient(connectionManager);

            HostConfiguration hostConfiguration = getHostConfiguration(httpClient, targetURL);

            method = new PostMethod(targetURL.toString());

            addContextInfo(method, httpClient, msgContext, targetURL);
            Message reqMessage = msgContext.getRequestMessage();
            ByteArrayOutputStream baos = new ByteArrayOutputStream();

            reqMessage.writeTo(baos);
            method.setRequestBody(bytesAsString(baos.toByteArray()));
            method.setUseExpectHeader(false); // workaround for
                                              // outbound chunking bug
                                              // in httpclient
            
            int returnCode = httpClient.executeMethod(method);
            String contentType = null;
            String contentLocation = null;
            String contentLength = null;

            if (method.getResponseHeader(HTTPConstants.HEADER_CONTENT_TYPE)
                != null) {
                contentType = method.getResponseHeader(
                    HTTPConstants.HEADER_CONTENT_TYPE).getValue();
            }
            if (method.getResponseHeader(HTTPConstants.HEADER_CONTENT_LOCATION)
                != null) {
                contentLocation = method.getResponseHeader(
                    HTTPConstants.HEADER_CONTENT_LOCATION).getValue();
            }
            if (method.getResponseHeader(HTTPConstants.HEADER_CONTENT_LENGTH)
                != null) {
                contentLength = method.getResponseHeader(
                    HTTPConstants.HEADER_CONTENT_LENGTH).getValue();
            }
            contentType = (null == contentType)
                ? null
                : contentType.trim();
            if ((returnCode > 199) && (returnCode < 300)) {

                // SOAP return is OK - so fall through
            } else if ((contentType != null) && !contentType.equals("text/html")
                       && ((returnCode > 499) && (returnCode < 600))) {

                // SOAP Fault should be in here - so fall through
            } else {
                String statusMessage = method.getStatusText();
                AxisFault fault = new AxisFault("HTTP",
                                                "(" + returnCode + ")"
                                                + statusMessage, null,
                                                null);

                fault.setFaultDetailString(Messages.getMessage("return01",
                                                               "" + returnCode, method.getResponseBodyAsString()));
                throw fault;
            }
            Message outMsg = new Message(method.getResponseBodyAsStream(),
                                         false, contentType, contentLocation);
            // no need to invoke method.releaseConnection here, as that will
            // happen automatically when the response body is read.
            // issue: what if the stream is never closed?  Are we certain
            // that InputStream.close() always gets called?
            outMsg.setMessageType(Message.RESPONSE);
            msgContext.setResponseMessage(outMsg);
            if (log.isDebugEnabled()) {
                if (null == contentLength) {
                    log.debug("\n"
                              + Messages.getMessage("no00", "Content-Length"));
                }
                log.debug("\n" + Messages.getMessage("xmlRecd00"));
                log.debug("-----------------------------------------------");
                log.debug((String) outMsg.getSOAPPartAsString());
            }

            // if we are maintaining session state,
            // handle cookies (if any)
            if (msgContext.getMaintainSession()) {
                Header[] headers = method.getResponseHeaders();
                for (int i = 0; i < headers.length; i++) {
                    if (headers[i].getName().equalsIgnoreCase(HTTPConstants.HEADER_SET_COOKIE))
                        msgContext.setProperty(HTTPConstants.HEADER_COOKIE, cleanupCookie(headers[i].getValue()));
                    else if (headers[i].getName().equalsIgnoreCase(HTTPConstants.HEADER_SET_COOKIE2))
                        msgContext.setProperty(HTTPConstants.HEADER_COOKIE2, cleanupCookie(headers[i].getValue()));
                }
            }
        } catch (Exception e) {
            log.debug(e);
            throw AxisFault.makeFault(e);
        }
        
        if (log.isDebugEnabled()) {
            log.debug(Messages.getMessage("exit00",
                                          "CommonsHTTPSender::invoke"));
        }
    }

    private static String bytesAsString(byte[] b) {
        try {
            return new String(b, "UTF-8");
        } catch (UnsupportedEncodingException e) {
            // always supported
            throw new IllegalStateException(e.getMessage());
        } // end of try-catch
    }

    /**
     * cleanup the cookie value.
     *
     * @param cookie initial cookie value
     *
     * @return a cleaned up cookie value.
     */
    private String cleanupCookie(String cookie) {
        cookie = cookie.trim();
        // chop after first ; a la Apache SOAP (see HTTPUtils.java there)
        int index = cookie.indexOf(';');

        if (index != -1) {
            cookie = cookie.substring(0, index);
        }
        return cookie;
    }

    private HostConfiguration getHostConfiguration(HttpClient client, URL targetURL) {
        boolean isSecure = targetURL.getProtocol().equalsIgnoreCase("http");
        TransportClientProperties tcp = TransportClientPropertiesFactory.create(targetURL.getProtocol()); // http or https
        int port = targetURL.getPort();
        boolean hostInNonProxyList =
            isHostInNonProxyList(targetURL.getHost(), tcp.getNonProxyHosts());

        HostConfiguration config = new HostConfiguration();
        
        if (port == -1) {
            port = 80;          // even for https
        }
        if (tcp.getProxyHost().length() == 0 ||
            tcp.getProxyPort().length() == 0 ||
            hostInNonProxyList) {
            config.setHost(targetURL.getHost(), port, targetURL.getProtocol());
        } else {
            if (tcp.getProxyUser().length() != 0) {
                Credentials proxyCred =
                    new UsernamePasswordCredentials(tcp.getProxyUser(),
                                                    tcp.getProxyPassword());
                client.getState().setProxyCredentials(null, proxyCred);
            }
            int proxyPort = new Integer(tcp.getProxyPort()).intValue();
            config.setProxy(tcp.getProxyHost(), proxyPort);
        }
        return config;
    }

    /**
     * Extracts info from message context.
     *
     * @param method Post method
     * @param httpClient The client used for posting
     * @param msgContext the message context
     * @param tmpURL the url to post to.
     *
     * @throws Exception
     */
    private void addContextInfo(
        PostMethod method, HttpClient httpClient, MessageContext msgContext, URL tmpURL)
        throws Exception {

        // optionally set a timeout for the request
        if (msgContext.getTimeout() != 0) {
            httpClient.setTimeout(msgContext.getTimeout());
        }

        // Get SOAPAction, default to ""
        String action = msgContext.useSOAPAction()
            ? msgContext.getSOAPActionURI()
            : "";

        if (action == null) {
            action = "";
        }
        Message msg = msgContext.getRequestMessage();
        method.setRequestHeader(new Header(HTTPConstants.HEADER_CONTENT_TYPE,
                                           msg.getContentType(msgContext.getSOAPConstants())));
        method.setRequestHeader(new Header(HTTPConstants.HEADER_SOAP_ACTION, "\"" + action + "\""));
        String userID = msgContext.getUsername();
        String passwd = msgContext.getPassword();

        // if UserID is not part of the context, but is in the URL, use
        // the one in the URL.
        if ((userID == null) && (tmpURL.getUserInfo() != null)) {
            String info = tmpURL.getUserInfo();
            int sep = info.indexOf(':');

            if ((sep >= 0) && (sep + 1 < info.length())) {
                userID = info.substring(0, sep);
                passwd = info.substring(sep + 1);
            } else {
                userID = info;
            }
        }
        if (userID != null) {
            Credentials cred = new UsernamePasswordCredentials(userID, passwd);
            httpClient.getState().setCredentials(null, cred);

            // The following 3 lines should NOT be required. But Our SimpleAxisServer fails
            // during all-tests if this is missing.
            StringBuffer tmpBuf = new StringBuffer();
            tmpBuf.append(userID).append(":").append((passwd == null) ? "" : passwd);
            method.addRequestHeader(HTTPConstants.HEADER_AUTHORIZATION, "Basic " + Base64.encode(tmpBuf.toString().getBytes()));
        }

        // don't forget the cookies!
        if (msgContext.getMaintainSession()) {
            String cookie =
                (String) msgContext.getProperty(HTTPConstants.HEADER_COOKIE);
            String cookie2 =
                (String) msgContext.getProperty(HTTPConstants.HEADER_COOKIE2);

            if (cookie != null) {
                method.addRequestHeader(HTTPConstants.HEADER_COOKIE, cookie);
            }
            if (cookie2 != null) {
                method.addRequestHeader(HTTPConstants.HEADER_COOKIE2, cookie2);
            }
        }

        // process user defined headers for information.
        Hashtable userHeaderTable =
            (Hashtable) msgContext.getProperty(HTTPConstants.REQUEST_HEADERS);

        if (userHeaderTable != null) {
            for (java.util.Iterator e = userHeaderTable.entrySet().iterator();
                 e.hasNext();) {
                java.util.Map.Entry me = (java.util.Map.Entry) e.next();
                Object keyObj = me.getKey();

                if (null == keyObj) {
                    continue;
                }
                String key = keyObj.toString().trim();
                String value = me.getValue().toString().trim();

                method.addRequestHeader(key, value);
            }
        }
    }

    /**
     * Check if the specified host is in the list of non proxy hosts.
     *
     * @param host host name
     * @param nonProxyHosts string containing the list of non proxy hosts
     *
     * @return true/false
     */
    protected boolean isHostInNonProxyList(String host, String nonProxyHosts) {

        if ((nonProxyHosts == null) || (host == null)) {
            return false;
        }

        /*
         * The http.nonProxyHosts system property is a list enclosed in
         * double quotes with items separated by a vertical bar.
         */
        StringTokenizer tokenizer = new StringTokenizer(nonProxyHosts, "|\"");

        while (tokenizer.hasMoreTokens()) {
            String pattern = tokenizer.nextToken();

            if (log.isDebugEnabled()) {
                log.debug(Messages.getMessage("match00",
                                              new String[]{"HTTPSender",
                                                           host,
                                                           pattern}));
            }
            if (match(pattern, host, false)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Matches a string against a pattern. The pattern contains two special
     * characters:
     * '*' which means zero or more characters,
     *
     * @param pattern the (non-null) pattern to match against
     * @param str     the (non-null) string that must be matched against the
     *                pattern
     * @param isCaseSensitive
     *
     * @return <code>true</code> when the string matches against the pattern,
     *         <code>false</code> otherwise.
     */
    protected static boolean match(String pattern, String str,
                                   boolean isCaseSensitive) {

        char[] patArr = pattern.toCharArray();
        char[] strArr = str.toCharArray();
        int patIdxStart = 0;
        int patIdxEnd = patArr.length - 1;
        int strIdxStart = 0;
        int strIdxEnd = strArr.length - 1;
        char ch;
        boolean containsStar = false;

        for (int i = 0; i < patArr.length; i++) {
            if (patArr[i] == '*') {
                containsStar = true;
                break;
            }
        }
        if (!containsStar) {

            // No '*'s, so we make a shortcut
            if (patIdxEnd != strIdxEnd) {
                return false;        // Pattern and string do not have the same size
            }
            for (int i = 0; i <= patIdxEnd; i++) {
                ch = patArr[i];
                if (isCaseSensitive && (ch != strArr[i])) {
                    return false;    // Character mismatch
                }
                if (!isCaseSensitive
                    && (Character.toUpperCase(ch)
                        != Character.toUpperCase(strArr[i]))) {
                    return false;    // Character mismatch
                }
            }
            return true;             // String matches against pattern
        }
        if (patIdxEnd == 0) {
            return true;    // Pattern contains only '*', which matches anything
        }

        // Process characters before first star
        while ((ch = patArr[patIdxStart]) != '*'
               && (strIdxStart <= strIdxEnd)) {
            if (isCaseSensitive && (ch != strArr[strIdxStart])) {
                return false;    // Character mismatch
            }
            if (!isCaseSensitive
                && (Character.toUpperCase(ch)
                    != Character.toUpperCase(strArr[strIdxStart]))) {
                return false;    // Character mismatch
            }
            patIdxStart++;
            strIdxStart++;
        }
        if (strIdxStart > strIdxEnd) {

            // All characters in the string are used. Check if only '*'s are
            // left in the pattern. If so, we succeeded. Otherwise failure.
            for (int i = patIdxStart; i <= patIdxEnd; i++) {
                if (patArr[i] != '*') {
                    return false;
                }
            }
            return true;
        }

        // Process characters after last star
        while ((ch = patArr[patIdxEnd]) != '*' && (strIdxStart <= strIdxEnd)) {
            if (isCaseSensitive && (ch != strArr[strIdxEnd])) {
                return false;    // Character mismatch
            }
            if (!isCaseSensitive
                && (Character.toUpperCase(ch)
                    != Character.toUpperCase(strArr[strIdxEnd]))) {
                return false;    // Character mismatch
            }
            patIdxEnd--;
            strIdxEnd--;
        }
        if (strIdxStart > strIdxEnd) {

            // All characters in the string are used. Check if only '*'s are
            // left in the pattern. If so, we succeeded. Otherwise failure.
            for (int i = patIdxStart; i <= patIdxEnd; i++) {
                if (patArr[i] != '*') {
                    return false;
                }
            }
            return true;
        }

        // process pattern between stars. padIdxStart and patIdxEnd point
        // always to a '*'.
        while ((patIdxStart != patIdxEnd) && (strIdxStart <= strIdxEnd)) {
            int patIdxTmp = -1;

            for (int i = patIdxStart + 1; i <= patIdxEnd; i++) {
                if (patArr[i] == '*') {
                    patIdxTmp = i;
                    break;
                }
            }
            if (patIdxTmp == patIdxStart + 1) {

                // Two stars next to each other, skip the first one.
                patIdxStart++;
                continue;
            }

            // Find the pattern between padIdxStart & padIdxTmp in str between
            // strIdxStart & strIdxEnd
            int patLength = (patIdxTmp - patIdxStart - 1);
            int strLength = (strIdxEnd - strIdxStart + 1);
            int foundIdx = -1;

            strLoop:
            for (int i = 0; i <= strLength - patLength; i++) {
                for (int j = 0; j < patLength; j++) {
                    ch = patArr[patIdxStart + j + 1];
                    if (isCaseSensitive
                        && (ch != strArr[strIdxStart + i + j])) {
                        continue strLoop;
                    }
                    if (!isCaseSensitive && (Character
                                             .toUpperCase(ch) != Character
                                             .toUpperCase(strArr[strIdxStart + i + j]))) {
                        continue strLoop;
                    }
                }
                foundIdx = strIdxStart + i;
                break;
            }
            if (foundIdx == -1) {
                return false;
            }
            patIdxStart = patIdxTmp;
            strIdxStart = foundIdx + patLength;
        }

        // All characters in the string are used. Check if only '*'s are left
        // in the pattern. If so, we succeeded. Otherwise failure.
        for (int i = patIdxStart; i <= patIdxEnd; i++) {
            if (patArr[i] != '*') {
                return false;
            }
        }
        return true;
    }
}

