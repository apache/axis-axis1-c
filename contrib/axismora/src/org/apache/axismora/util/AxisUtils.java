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

package org.apache.axismora.util;

import java.util.ArrayList;
import java.util.Stack;
import java.util.Vector;

import javax.xml.namespace.QName;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.apache.axismora.Constants;
import org.apache.axismora.deployment.AxisDeployment;

import org.apache.axis.AxisFault;
import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xmlpull.v1.XmlPullParser;

public class AxisUtils {
    private static Document commonDoc;

    protected static Log log = LogFactory.getLog(AxisUtils.class.getName());

    public static String[] getStringArray(Vector str) {
        String[] strA = new String[str.size()];
        for (int i = 0; i < str.size(); i++)
            strA[i] = (String) str.get(i);
        return strA;
    }

    public static Class[] getClassArray(Vector str) {
        Class[] strA = new Class[str.size()];
        for (int i = 0; i < str.size(); i++)
            strA[i] = str.get(i).getClass();
        return strA;
    }

    public static String[] getStringArray(ArrayList str) {
        String[] strA = new String[str.size()];
        for (int i = 0; i < str.size(); i++)
            strA[i] = (String) str.get(i);
        return strA;
    }

    public static String[][] getStringArrayofArray(ArrayList str) {
        String[][] strA = new String[str.size()][];
        ArrayList inlist;
        for (int i = 0; i < str.size(); i++) {
            inlist = (ArrayList) str.get(i);
            String[] invals = new String[inlist.size()];
            for (int j = 0; j < inlist.size(); j++) {

                invals[j] = (String) inlist.get(j);
            }
            strA[i] = invals;
        }
        return strA;
    }

    public static AxisFault getTheAixsFault(
        QName faultCode,
        String readableDesc,
        AxisDeployment deployment,
        String role,
        Throwable e) {
        // get the axisFault 
        AxisFault axisFault = null;
        if (e == null)
            axisFault = new AxisFault();
        else if (e instanceof AxisFault)
            axisFault = (AxisFault) e;
        else
            axisFault = new AxisFault(readableDesc, e);

        //set the parameters
        if (faultCode != null)
            axisFault.setFaultCode(faultCode);
        if (readableDesc != null) {
            if (axisFault.getFaultReason() == null || axisFault.getFaultReason() == "")
                axisFault.setFaultReason(readableDesc);
            if (axisFault.getFaultString() == null || axisFault.getFaultString() == "")
                axisFault.setFaultString(readableDesc);
        }
        if (deployment != null) {
            String node =
                deployment.getGlobalInfo().getParameter(Constants.NODE_NAME_PARAMETER);
            if (node != null)
                axisFault.setFaultNode(node);
        }
        if (role != null)
            axisFault.setFaultRole(role);

        return axisFault;
    }

    /*
    * Given a pull parser with a string this method would return an Element.
    * The root of the Element would be the first start tag that comes in the stream.
    * 
    * @param XmlPullParser with a stream set into it
    * @return Element
    */
    public static Element make(XmlPullParser xpp) throws AxisFault {

        Stack stack = new Stack();
        String rootNameSpace = null;
        String rootLocalName = null;

        try {

            Document doc = getCommonDomDocument();
            Element ele;
            Node node;
            Object obj1 = null;
            Object obj2 = null;

            boolean isEndOfDoc = true;
            boolean isFirst = true;

            int state = xpp.getEventType();

            // Positions the cursor at a start tag 			
            while ((state != XmlPullParser.END_DOCUMENT)
                && (state != XmlPullParser.START_TAG)) {
                state = xpp.next();
            }

            while (state != XmlPullParser.END_DOCUMENT) {
                if (state == XmlPullParser.START_TAG) {

                    if (isFirst) {
                        rootNameSpace = xpp.getNamespace();

                        log.debug(rootNameSpace);
                        log.debug(xpp.getNamespace());

                        rootLocalName = xpp.getName();
                        isFirst = false;
                    }

                    ele = doc.createElementNS(xpp.getNamespace(), xpp.getName());
                    for (int i = 0; i < xpp.getAttributeCount(); i++) {
                        ele.setAttributeNS(
                            xpp.getAttributeNamespace(i),
                            xpp.getAttributeName(i),
                            xpp.getAttributeValue(i));
                    }
                    stack.push((Object) ele);
                } else if (state == XmlPullParser.TEXT) {
                    if (!xpp.isWhitespace()) {
                        node = (Node) stack.pop();
                        node.appendChild(doc.createTextNode(xpp.getText()));
                        stack.push((Object) node);
                    }
                } else if (state == XmlPullParser.END_TAG) {

                    if (!stack.isEmpty()) {
                        obj1 = stack.pop();
                        ele = (Element) obj1;
                    } else {
                        //	TODO :: Major fault create axis fault
                        System.out.println(
                            "Util.FromPullParserToDom Obj1 is null. Not valid xml");
                        return null; // throw fault and remove this
                    }

                    if (!stack.isEmpty()) {
                        obj2 = stack.pop();
                        ele = (Element) obj2;
                    } else {
                        obj2 = obj1;
                        isEndOfDoc = false;
                        break;
                    }
                    ((Node) obj2).appendChild((Node) obj1);
                    stack.push(obj2);
                } else {
                    // document tags are ignored
                    // do nothing   
                }

                state = xpp.next();

            } // end of while loop    

            if (isEndOfDoc) {
                throw AxisUtils.getTheAixsFault(
                    org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                    "End of Document is reached !!!",
                    null,
                    null,
                    null);
            } else {
                ele = (Element) obj2;

                if (log.isDebugEnabled()) {
                    log.debug(
                        "Element says nameSpace is ::"
                            + ele.getNamespaceURI()
                            + " varialbe-rootNameSpace says ::"
                            + rootNameSpace);
                    log.debug(
                        "Element says local name is ::"
                            + ele.getNodeName()
                            + "variable-rootLocalName says ::"
                            + rootLocalName);
                    log.debug("These has to be equal");
                }

                // before we return we have to check where is the cursor  

                //xpp.getNamespaceURI returns "" for no-namespace.
                //ele.getNamespceURI returns null for no-namespace.

                String eleNamespace = ele.getNamespaceURI();

                if (eleNamespace == null) {
                    eleNamespace = "";
                }

                if (eleNamespace == rootNameSpace
                    && ele.getNodeName() == rootLocalName) {
                    return ele;
                } else {
                    throw AxisUtils.getTheAixsFault(
                        org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                        "rootLocalName and rootElement name don't match",
                        null,
                        null,
                        null);
                }
            }
        } catch (Exception e1) {

            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e1.getMessage(),
                null,
                null,
                e1);
        }
    }

    public static Document getCommonDomDocument() throws ParserConfigurationException {
        if (commonDoc == null) {
            commonDoc =
                DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
        }
        return commonDoc;
    }
}
