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

package org.apache.axis.utils ;

import org.apache.axis.Constants;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.w3c.dom.Attr;
import org.w3c.dom.CharacterData;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.XMLReader;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.rpc.namespace.QName;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Hashtable;
import java.util.Stack;

public class XMLUtils {
    protected static Log log =
        LogFactory.getLog(XMLUtils.class.getName());

    private static DocumentBuilderFactory dbf = initDOMFactory();
    private static SAXParserFactory       saxFactory;
    private static Stack                  saxParsers = new Stack();

    static {
        // Initialize SAX Parser factory defaults
        initSAXFactory(null, true, false);
    }

    /** Encode a string appropriately for XML.
     *
     * Lifted from ApacheSOAP 2.2 (org.apache.soap.Utils)
     *
     * @param orig the String to encode
     * @return a String in which XML special chars are repalced by entities
     */
    public static String xmlEncodeString(String orig)
    {
        if (orig == null)
        {
            return "";
        }

        StringBuffer strBuf = new StringBuffer();
        char[] chars = orig.toCharArray();

        for (int i = 0; i < chars.length; i++)
        {
            switch (chars[i])
            {
            case '&'  : strBuf.append("&amp;");
                        break;
            case '\"' : strBuf.append("&quot;");
                        break;
            case '\'' : strBuf.append("&apos;");
                        break;
            case '<'  : strBuf.append("&lt;");
                        break;
            case '\r' : strBuf.append("&#xd;");
                        break;
            case '>'  : strBuf.append("&gt;");
                        break;
            default   : 
                if (((int)chars[i]) > 127) {
                        strBuf.append("&#");
                        strBuf.append((int)chars[i]);
                        strBuf.append(";");
                } else {
                        strBuf.append(chars[i]);
                }
            }
        }

        return strBuf.toString();
    }

    /** Initialize the SAX parser factory.
     *
     * @param factoryClassName The class name of the desired SAXParserFactory
     *                         implementation.  Will be assigned to the system
     *                         property <b>javax.xml.parsers.SAXParserFactory</b>.
     * @param namespaceAware true if we want a namespace-aware parser (which we do)
     * @param validating true if we want a validating parser
     *
     */
    public static void initSAXFactory(String factoryClassName,
                                      boolean namespaceAware,
                                      boolean validating)
    {
        if (factoryClassName != null) {
            System.setProperty("javax.xml.parsers.SAXParserFactory",
                               factoryClassName);
        }
        saxFactory = SAXParserFactory.newInstance();
        saxFactory.setNamespaceAware(namespaceAware);
        saxFactory.setValidating(validating);
    }

    public static DocumentBuilderFactory initDOMFactory() {
        try {
            dbf = DocumentBuilderFactory.newInstance();
            dbf.setNamespaceAware(true);
        }
        catch( Exception e ) {
            log.error(JavaUtils.getMessage("exception00"), e );
        }
        return( dbf );
    }

    private static DefaultHandler doNothingContentHandler = new DefaultHandler(); //no events should h
    private static boolean tryReset= true;

    /** Get a SAX parser instance from the JAXP factory.
     *
     * @return a SAXParser instance.
     */
    public static SAXParser getSAXParser() {
        synchronized (XMLUtils.class ) {
          if(!saxParsers.empty()) 
                 return (SAXParser )saxParsers.pop();
         }
        try {
                return saxFactory.newSAXParser();
            
        } catch (ParserConfigurationException e) {
            log.error(JavaUtils.getMessage("parserConfigurationException00"), e);
            return null;
        } catch (SAXException se) {
            log.error(JavaUtils.getMessage("SAXException00"), se);
            return null;
        }
    }


    /** Return a SAX parser for reuse.
     * @param SAXParser A SAX parser that is available for reuse
     */
    public static void releaseSAXParser(SAXParser parser) {
        if(!tryReset) return;
       
        //Free up possible ref. held by past contenthandler.
        try{
            XMLReader xmlReader= parser.getXMLReader(); 
            if(null != xmlReader){
                xmlReader.setContentHandler(doNothingContentHandler); 
                xmlReader.setDTDHandler(doNothingContentHandler); 
                xmlReader.setEntityResolver(doNothingContentHandler);
                xmlReader.setErrorHandler(doNothingContentHandler);
                synchronized (XMLUtils.class ) {
                saxParsers.push(parser);
                }
            }    
            else     
             tryReset= false;
        }catch(org.xml.sax.SAXException e){ tryReset= false;}
    }

    public static Document newDocument() {
        try {
            return dbf.newDocumentBuilder().newDocument();
        } catch (Exception e) {
            return null;
        }
    }

    public static Document newDocument(InputSource inp) {
        try {
            DocumentBuilder db = dbf.newDocumentBuilder();
            db.setErrorHandler( new ParserErrorHandler() );
            return( db.parse( inp ) );
        }
        catch( Exception e ) {
            log.error(JavaUtils.getMessage("exception00"), e);
        }
        return( null );
    }

    public static Document newDocument(InputStream inp) {
        return XMLUtils.newDocument(new InputSource(inp));
    }

    public static Document newDocument(String uri) {
        return XMLUtils.newDocument(new InputSource(uri));
    }

    private static String privateElementToString(Element element,
                                                 boolean omitXMLDecl)
    {
        return DOM2Writer.nodeToString(element, omitXMLDecl);
    }

    public static String ElementToString(Element element) {
        return privateElementToString(element, true);
    }

    public static String DocumentToString(Document doc) {
        return privateElementToString(doc.getDocumentElement(), false);
    }

    public static void privateElementToWriter(Element element, Writer writer,
                                              boolean omitXMLDecl,
                                              boolean pretty) {
        DOM2Writer.serializeAsXML(element, writer, omitXMLDecl, pretty);
    }

    public static void ElementToStream(Element element, OutputStream out) {
        Writer writer = new OutputStreamWriter(out);
        privateElementToWriter(element, writer, true, false);
    }

    public static void PrettyElementToStream(Element element, OutputStream out) {
        Writer writer = new OutputStreamWriter(out);
        privateElementToWriter(element, writer, true, true);
    }

    public static void ElementToWriter(Element element, Writer writer) {
        privateElementToWriter(element, writer, true, false);
    }

    public static void PrettyElementToWriter(Element element, Writer writer) {
        privateElementToWriter(element, writer, true, true);
    }

    public static void DocumentToStream(Document doc, OutputStream out) {
        Writer writer = new OutputStreamWriter(out);
        privateElementToWriter(doc.getDocumentElement(), writer, false, false);
    }

    public static void PrettyDocumentToStream(Document doc, OutputStream out) {
        Writer writer = new OutputStreamWriter(out);
        privateElementToWriter(doc.getDocumentElement(), writer, false, true);
    }

    public static void DocumentToWriter(Document doc, Writer writer) {
        privateElementToWriter(doc.getDocumentElement(), writer, false, false);
    }

    public static void PrettyDocumentToWriter(Document doc, Writer writer) {
        privateElementToWriter(doc.getDocumentElement(), writer, false, true);
    }
    /**
     * Convert a simple string to an element with a text node
     * 
     * @param namespace - element namespace
     * @param name - element name
     * @param string - value of the text node
     * @return element - an XML Element
     */ 
    public static Element StringToElement(String namespace, String name, String string) {
        Document doc = XMLUtils.newDocument();
        Element element = doc.createElementNS(namespace, name);
        Text text = doc.createTextNode(string);
        element.appendChild(text);
        return element;
    }
    
    public static String getInnerXMLString(Element element) {
        String elementString = ElementToString(element);
        int start, end;
        start = elementString.indexOf(">") + 1;
        end = elementString.lastIndexOf("</");
        if (end > 0)
            return elementString.substring(start,end);
        else
            return null;
    }

    public static String getPrefix(String uri, Node e) {
        while (e != null && (e.getNodeType() == Element.ELEMENT_NODE)) {
            NamedNodeMap attrs = e.getAttributes();
            for (int n = 0; n < attrs.getLength(); n++) {
                Attr a = (Attr)attrs.item(n);
                String name;
                if ((name = a.getName()).startsWith("xmlns:") &&
                    a.getNodeValue().equals(uri)) {
                    return name.substring(6);
                }
            }
            e = e.getParentNode();
        }
        return null;
    }

    public static String getNamespace(String prefix, Node e) {
        while (e != null && (e.getNodeType() == Node.ELEMENT_NODE)) {
            Attr attr =
                ((Element)e).getAttributeNodeNS(Constants.NS_URI_XMLNS, prefix);
            if (attr != null) return attr.getValue();
            e = e.getParentNode();
        }
        return null;
    }

    /**
     * Return a QName when passed a string like "foo:bar" by mapping
     * the "foo" prefix to a namespace in the context of the given Node.
     *
     * @return a QName generated from the given string representation
     */
    public static QName getQNameFromString(String str, Node e) {
        if (str == null || e == null)
            return null;

        int idx = str.indexOf(':');
        if (idx > -1) {
            String prefix = str.substring(0, idx);
            String ns = getNamespace(prefix, e);
            if (ns == null)
                return null;
            return new QName(ns, str.substring(idx + 1));
        } else {
            return new QName("", str);
        }
    }

    /**
     * Return a string for a particular QName, mapping a new prefix
     * if necessary.
     */
    public String getStringForQName(QName qname, Element e)
    {
        String uri = qname.getNamespaceURI();
        String prefix = getPrefix(uri, e);
        if (prefix == null) {
            int i = 1;
            prefix = "ns" + i;
            while (getNamespace(prefix, e) != null) {
                i++;
                prefix = "ns" + i;
            }
            e.setAttributeNS(Constants.NS_URI_XMLNS,
                        "xmlns:" + prefix, uri);
        }
        return prefix + ":" + qname.getLocalPart();
    }

    /**
     * Gather all existing prefixes in use in this document
     *
     */
    private static Hashtable getPrefixes(Document d)
    {
        Hashtable result = new Hashtable();

        NodeList list = d.getElementsByTagName("*");

        for (int i=0; i<list.getLength(); i++)
        {
            Element e = (Element)list.item(i);
            NamedNodeMap attrs = e.getAttributes();
            for (int n = 0; n < attrs.getLength(); n++)
            {
                Attr a = (Attr)attrs.item(n);
                String name;
                if ((name = a.getName()).startsWith("xmlns:"))
                    {
                    // do *not* store nsUri for lookup, as a prefix might be
                    //   one-many in the document as a whole
                    result.put(name.substring(6), "");
                }
            }
        }
        return result;
    }

    /**
     * Take note of all existing prefixes in use in this document, and
     *  create a new one
     *
     */
    public static String getNewPrefix(Document d, String nsUri)
    {
        Hashtable extantPrefixes = getPrefixes(d);

        // Now try to pick one that isn't extant
        String winner = null;
        for (int j=0; winner == null; j++)
        {
                String candidate = "ns" + j;
                if (! extantPrefixes.containsKey(candidate))
                {
                        winner = candidate;
                }
        }

        // Install the winner at the top of the document
        d.getDocumentElement().setAttributeNS(
                        Constants.NS_URI_XMLNS,
                        "xmlns:" + winner,
                        nsUri);

        return winner;
    }

  /**
   * Concat all the text and cdata node children of this elem and return
   * the resulting text.
   *
   * @param parentEl the element whose cdata/text node values are to
   *                 be combined.
   * @return the concatanated string.
   * @author Matt Duftler
   */
  static public String getChildCharacterData (Element parentEl) {
    if (parentEl == null) {
      return null;
    }
    Node          tempNode = parentEl.getFirstChild();
    StringBuffer  strBuf   = new StringBuffer();
    CharacterData charData;

    while (tempNode != null) {
      switch (tempNode.getNodeType()) {
        case Node.TEXT_NODE :
        case Node.CDATA_SECTION_NODE : charData = (CharacterData)tempNode;
                                       strBuf.append(charData.getData());
                                       break;
      }
      tempNode = tempNode.getNextSibling();
    }
    return strBuf.toString();
  }
    
    public static class ParserErrorHandler implements ErrorHandler
    {
        protected static Log log =
            LogFactory.getLog(ParserErrorHandler.class.getName());
        /**
         * Returns a string describing parse exception details
         */
        private String getParseExceptionInfo(SAXParseException spe) {
            String systemId = spe.getSystemId();
            if (systemId == null) {
                systemId = "null";
            }
            String info = "URI=" + systemId +
                " Line=" + spe.getLineNumber() +
                ": " + spe.getMessage();
            return info;
        }

        // The following methods are standard SAX ErrorHandler methods.
        // See SAX documentation for more info.

        public void warning(SAXParseException spe) throws SAXException {
            if (log.isDebugEnabled())
                log.debug( JavaUtils.getMessage("warning00", getParseExceptionInfo(spe)));
        }
        
        public void error(SAXParseException spe) throws SAXException {
            String message = "Error: " + getParseExceptionInfo(spe);
            throw new SAXException(message);
        }

        public void fatalError(SAXParseException spe) throws SAXException {
            String message = "Fatal Error: " + getParseExceptionInfo(spe);
            throw new SAXException(message);
        }
    }
 }
