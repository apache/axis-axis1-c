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

package org.apache.axismora.encoding.ser;

import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;

import javax.xml.namespace.QName;

import org.apache.axis.Constants;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.encoding.TypeMapping;
import org.apache.axis.encoding.TypeMappingRegistry;
import org.apache.axis.utils.XMLUtils;
import org.apache.axismora.util.ByteArrayStack;
import org.apache.axismora.util.UtilityPool;
import org.w3c.dom.Attr;
import org.w3c.dom.CDATASection;
import org.w3c.dom.CharacterData;
import org.w3c.dom.Comment;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.Text;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.AttributesImpl;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class SerializationContext extends org.apache.axis.encoding.SerializationContextImpl implements  org.apache.axis.encoding.SerializationContext{
	private final byte[] GTB = ">\n".getBytes();
	private final byte[] LTB = "<".getBytes();
	private final byte[] ETB = "</".getBytes();
	private final byte[] WSB = " ".getBytes();
	
	private EnhancedWriter writer;

	private HashMap namespaces = new NSmap();
	
	private Stack sedStack = new Stack();
	private int namespaceIndex = 0;
	private StartElementData sed;
	private ByteArrayStack stack = new ByteArrayStack();
	
    /**
     * @param writer
     */
    public SerializationContext(EnhancedWriter writer) {
        super(writer);
		this.writer = writer;
        // TODO Auto-generated constructor stub
    }

    public void writeChars(char[] p1, int p2, int p3) throws IOException {
		writer.write(p1,p2,p3);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.encoding.SerializationContext#writeSafeString(java.lang.String)
     */
    public void writeSafeString(String string) throws IOException {
		writer.write(XMLUtils.xmlEncodeString(string));
    }

    /* (non-Javadoc)
     * @see org.apache.axis.encoding.SerializationContext#writeString(java.lang.String)
     */
    public void writeString(String string) throws IOException {
		writer.write(string);
    }
    
    public void writeByte(byte[] bbuf) throws IOException{
    	writer.write(bbuf);
    }
    
	/**
	 * Output a DOM representation to a SerializationContext
	 * @param el is a DOM Element
	 */
	public void writeDOMElement(Element el)
		throws IOException
	{
		AttributesImpl attributes = null;
		NamedNodeMap attrMap = el.getAttributes();
		sed = new StartElementData();

		if (attrMap.getLength() > 0) {
			attributes = new AttributesImpl();
			for (int i = 0; i < attrMap.getLength(); i++) {
				Attr attr = (Attr)attrMap.item(i);
				String tmp = attr.getNamespaceURI();
				if ( tmp != null && tmp.equals(Constants.NS_URI_XMLNS) ) {
					String prefix = attr.getLocalName();
					sed.newNs.append("xmlns");
					String newuri = attr.getValue();
					
					if(!prefix.equals("xmlns")){
						sed.newNs.append(":").append(prefix);
						namespaces.put(newuri,prefix);
					}else
					namespaces.put(newuri,"");
					
					sed.newNs.append(" = \"").append(newuri).append("\"").append(' ');
 					continue;
				}
				attributes.addAttribute(attr.getNamespaceURI(),
										attr.getLocalName(),
										attr.getName(),
										"CDATA", attr.getValue());
			}
		}

		String namespaceURI = el.getNamespaceURI();
		String localPart = el.getLocalName();
		if(namespaceURI == null || namespaceURI.length()==0)
			localPart = el.getNodeName();
		QName qName = new QName(namespaceURI, localPart);

		startElement(qName, attributes);

		NodeList children = el.getChildNodes();
		for (int i = 0; i < children.getLength(); i++) {
			Node child = children.item(i);
			if (child instanceof Element) {
				writeDOMElement((Element)child);
			} else if (child instanceof CDATASection) {
				writeString("<![CDATA[");
				writeString(((Text)child).getData());
				writeString("]]>");
			} else if (child instanceof Comment) {
				writeString("<!--");
				writeString(((CharacterData)child).getData());
				writeString("-->");
			} else if (child instanceof Text) {
				writeSafeString(((Text)child).getData());
			}
		}
		endElement();
	}
	
	public void endTag()throws IOException {
		writer.write(ETB);
		writer.write(stack.pop());
		writer.write(GTB);
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.encoding.SerializationContext#startTag(java.lang.String, java.lang.String)
	 */
	public void startTag(String prefixedName, String additional) throws IOException {
		byte[] prefixedB = prefixedName.getBytes();
		writer.write(LTB);
		writer.write(prefixedB);
		if(additional != null){
			writer.write(WSB);
			writer.write(additional);
		}
		
		writer.write(GTB);
		stack.push(prefixedB);
	}


    /* (non-Javadoc)
     * @see org.apache.axis.encoding.SerializationContext#endElement()
     */
    public void endElement() throws IOException {
		this.sed =  (StartElementData)sedStack.pop();
		writer.write("</");
		writer.write(sed.nwprefix);
		writer.write(">");
		int length = sed.localNs.size();
		for(int i = 0; i< length;i++){
			namespaces.remove(sed.localNs.get(i));
		}
		UtilityPool.returnArrayList(sed.localNs);
    }

    /* (non-Javadoc)
     * @see org.apache.axis.encoding.SerializationContext#startElement(javax.xml.namespace.QName, org.xml.sax.Attributes)
     */
    public void startElement(QName qName, Attributes attributes)
        throws IOException {
        	if(sed == null){
				sed = new StartElementData();
        	}
        	int pushNsCount = 0;
        	String uri = qName.getNamespaceURI();
			String prefix = "";
			if(uri == null || "".equals(uri) ||prefix.length() <1 ){
				writer.write("<");
				writer.write(qName.getLocalPart()); 
			}else{
				prefix = getPrefixForURI(uri,sed);
				writer.write("<");
				writer.write(prefix);writer.write(':');
				writer.write(qName.getLocalPart()); 
			}
			if (attributes != null) {
				for (int i = 0; i < attributes.getLength(); i++) {
					String qname = attributes.getQName(i);
					if(qname.startsWith("xmlns:")){
						String newprefix = attributes.getLocalName(i);
						String newuri = attributes.getValue(i);
						namespaces.put(newuri,newprefix);
						sed.newNs.append("xmlns").append(":").append(newprefix).append(" = \"").append(newuri).append("\"").append(' ');
						continue;
					}
					

					writer.write(' ');
					String Aturi = attributes.getURI(i);
					String Atprefix;
					if(Aturi != null && Aturi.length() > 0){
						writer.write(getPrefixForURI(uri,sed));
						writer.write(":");
					}	
					String localName = attributes.getLocalName(i);
					writer.write(localName);
					writer.write("=\"");
					writer.write(XMLUtils.xmlEncodeString(attributes.getValue(i)));
					writer.write('"');
				}
			}
			writer.write(' ');
			writer.write(sed.newNs.toString());
			writer.write('>');
			if(prefix.length() < 1)
				sed.nwprefix = qName.getLocalPart();
			else	
				sed.nwprefix = prefix + ':'+qName.getLocalPart();
			sedStack.push(sed);
    }
    
	public String getPrefixForURI(String uri,StartElementData sed){
		String prefix = (String)namespaces.get(uri);
		if(prefix == null){
			prefix = "ns"+namespaceIndex;
			namespaceIndex++;
			namespaces.put(uri,prefix);
			sed.newNs.append("xmlns").append(":").append(prefix).append(" = \"").append(uri).append("\"").append(' ');
		}
		return prefix;	
	}
	
	public class StartElementData{
		public String nwprefix;
		public ArrayList localNs = UtilityPool.getArrayList();
		StringBuffer newNs = new StringBuffer();
	}
	
	public String qName2String(QName qName) {
		String prefix = null;
		String namespaceURI = qName.getNamespaceURI();

		if (namespaceURI.length() == 0) {
		} else {
			prefix = getPrefixForURI(namespaceURI);
		}

		if ((prefix == null) || (prefix.length() == 0))
			return qName.getLocalPart();

		StringBuffer sb = new StringBuffer(prefix);
		sb.append(':');
		sb.append(qName.getLocalPart());
		return sb.toString();

	}

	
	//to make sure these are not supportted 

   public String attributeQName2String(QName qName) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public Message getCurrentMessage() {
		throw new UnsupportedOperationException("this is not supported at axismora");
	}

    public QName getCurrentXMLType() {
		throw new UnsupportedOperationException("this is not supported at axismora");
	}

    public MessageContext getMessageContext() {
		throw new UnsupportedOperationException("this is not supported at axismora");
	}

    public String getPrefixForURI(
        String uri,
        String defaultPrefix,
        boolean attribute) {
			throw new UnsupportedOperationException("this is not supported at axismora");
	}

    public String getPrefixForURI(String uri, String defaultPrefix) {
		throw new UnsupportedOperationException("this is not supported at axismora");
	}

    public String getPrefixForURI(String uri) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public boolean getPretty() {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public QName getQNameForClass(Class cls) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public TypeMapping getTypeMapping() {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public TypeMappingRegistry getTypeMappingRegistry() {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public String getValueAsString(Object value, QName xmlType)
        throws IOException {
			throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public boolean isPrimitive(Object value) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public void outputMultiRefs() throws IOException {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public String qName2String(QName qName, boolean writeNS) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }


    public void registerPrefixForURI(String prefix, String uri) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public void serialize(
        QName elemQName,
        Attributes attributes,
        Object value,
        QName xmlType,
        boolean sendNull,
        Boolean sendType)
        throws IOException {
			throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public void serialize(QName elemQName, Attributes attributes, Object value)
        throws IOException {
			throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public void setDoMultiRefs(boolean shouldDo) {
        // TODO Auto-generated method stub
        super.setDoMultiRefs(shouldDo);
    }

    public void setPretty(boolean pretty) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public void setShouldSendXSIType(boolean shouldSend) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

     public Attributes setTypeAttribute(Attributes attributes, QName type) {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }

    public boolean shouldSendXSIType() {
		throw new UnsupportedOperationException("this is not supported at axismora");
    }
}
