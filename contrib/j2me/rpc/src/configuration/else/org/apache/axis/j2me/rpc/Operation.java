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

package org.apache.axis.j2me.rpc;

import org.apache.axis.j2me.rpc.Base64;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Vector;

import javax.microedition.io.Connector;
import javax.microedition.io.HttpConnection;
import javax.microedition.xml.rpc.ComplexType;
import javax.microedition.xml.rpc.Element;
import javax.microedition.xml.rpc.FaultDetailException;
import javax.microedition.xml.rpc.FaultDetailHandler;
import javax.microedition.xml.rpc.Type;
import javax.xml.namespace.QName;
import javax.xml.rpc.JAXRPCException;
import javax.xml.rpc.Stub;

import org.kxml2.io.KXmlParser;
import org.kxml2.io.KXmlSerializer;
import org.kxml2.kdom.Node;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlSerializer;

/**
 * This is the implementation of javax.microedition.xml.rpc.Operation 
 * for CLDC 1.1 and CDC 1.0.
 * 
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class Operation extends javax.microedition.xml.rpc.Operation {

	/** header for security (username/password) */
	private static final String HEADER_AUTHORIZATION = "Authorization";

	/** Namespace constant: http://schemas.xmlsoap.org/soap/envelope/ */

	public static final String ENV =
		"http://schemas.xmlsoap.org/soap/envelope/";

	/** Namespace constant: http://schemas.xmlsoap.org/soap/encoding/ */

	public static final String ENC =
		"http://schemas.xmlsoap.org/soap/encoding/";

	/** Namespace constant: http://www.w3.org/2001/XMLSchema */

	public static final String XSD = "http://www.w3.org/2001/XMLSchema";

	/** Namespace constant: http://www.w3.org/2001/XMLSchema */

	public static final String XSI =
		"http://www.w3.org/2001/XMLSchema-instance";

	private String endpoint;
	private String soapAction;
	private String username;
	private String password;
	Element input;
	Element output;
	QName name;
	FaultDetailHandler faultDetailHandler;

	public Operation(
			QName name,
			Element input,
			Element output,
			FaultDetailHandler faultDetailHandler) {
		this.name = name;
		this.input = input;
		this.output = output;
		this.faultDetailHandler = faultDetailHandler;
	}

	/**
	 * Sets the property name to the value, value.
	 * 
	 * @param name -
	 *            the name of the property to be set
	 * @param value -
	 *            the value the property is to be set
	 * @throws java.lang.IllegalArgumentException -
	 *             if the property, name, is not recognized by the runtime.
	 *  
	 */
	public void setProperty(String name, String value)
		throws java.lang.IllegalArgumentException {
		if (name == null) {
			throw new IllegalArgumentException();
		}
		if (name.equals(Stub.ENDPOINT_ADDRESS_PROPERTY)) {
			endpoint = value;
		}
		if (name.equals(Stub.USERNAME_PROPERTY)) {
			username = value;
		}
		if (name.equals(Stub.PASSWORD_PROPERTY)) {
			password = value;
		}
		if (name.equals(SOAPACTION_URI_PROPERTY)) {
			soapAction = value;
		}

	}

	/**
	 * Invokes the wsdl:operation defined by this Operation and returns the
	 * result. The input parameters and return value are encoded such that
	 * primitive types are mapped to the equivalent object wrapper, for
	 * example, int is mapped to Integer, byte to Byte. arrays are an Object
	 * containing the array elements. complex types are represented by an array
	 * of objects mapped according to the above rules. Any additional elements,
	 * beyond those described by the description passed to
	 * Operation.newInstance, are ignored.
	 * 
	 * @param inParams -
	 *            an Object representing the input parameter value(s) to this
	 *            operation.
	 * @return a Object representing the output value(s) for this operation.
	 *         Can be null if this operation returns no value.
	 * @throws JAXRPCException-
	 *             if the runtime detects a type mismatch in input parameters
	 *             or return value. if an error occurs while excuting the
	 *             operation. Any exception corresponding to the error will be
	 *             attached, as the cause, to the JAXRPCException and can be
	 *             retrieved via the method getCause.
	 */
	public Object invoke(Object inParams) throws JAXRPCException {
		Object returnObject = null;
		HttpConnection connection = null;
		InputStream is = null;
		try {
			org.kxml2.kdom.Element inParamElement =
			new org.kxml2.kdom.Element();
			inParamElement.setNamespace(input.name.getNamespaceURI());
			inParamElement.setName(input.name.getLocalPart());
			serialize(inParamElement, input, inParams);

			if (soapAction == null) {
				// WS-I BP 1.0 R2745
				soapAction = "";
			}
			// WS-I BP 1.0 R2744
			soapAction = "\"" + soapAction + "\"";
			ByteArrayOutputStream bos = new ByteArrayOutputStream();
			XmlSerializer xw = new KXmlSerializer();
			xw.setOutput(bos, "EUC-KR");
			xw.startDocument(null, null);

			xw.setPrefix("i", XSI);
			xw.setPrefix("d", XSD);
			xw.setPrefix("c", ENC);
			xw.setPrefix("v", ENV);
			xw.startTag(ENV, "Envelope");
			xw.startTag(ENV, "Body");
			inParamElement.write(xw);
			xw.endTag(ENV, "Body");
			xw.endTag(ENV, "Envelope");
			xw.flush();
			bos.write('\r');
			bos.write('\n');
			byte[] requestData = bos.toByteArray();
			bos = null;
			xw = null;

			OutputStream os = null;
			connection =
				(HttpConnection) Connector.open(
					endpoint,
					Connector.READ_WRITE,
					true);

			connection.setRequestProperty("SOAPAction", soapAction);
			connection.setRequestProperty("Content-Type", "text/xml");
			connection.setRequestProperty(
				"Content-Length",
				"" + requestData.length);

			connection.setRequestProperty("User-Agent", "axis-j2me/1.0");
			if (username != null) {
				StringBuffer tmpBuf = new StringBuffer();

				tmpBuf.append(username).append(":").append(
					(password == null) ? "" : password);
				String value =
					" Basic " + Base64.encode(tmpBuf.toString().getBytes());
				connection.setRequestProperty(HEADER_AUTHORIZATION, value);
			}

			connection.setRequestMethod(HttpConnection.POST);

			os = connection.openOutputStream();
			os.write(requestData, 0, requestData.length);
			os.close();

			requestData = null;

			is = connection.openInputStream();

			XmlPullParser xp = new KXmlParser();
			xp.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, true);
			xp.setInput(is, null);

			xp.nextTag();
			xp.require(XmlPullParser.START_TAG, ENV, "Envelope");
			xp.nextTag();

			if (xp.getEventType() == XmlPullParser.START_TAG
				&& xp.getNamespace().equals(ENV)
				&& xp.getName().equals("Header")) {

				xp.require(XmlPullParser.END_TAG, ENV, "Header");
				xp.nextTag();
			}

			xp.require(XmlPullParser.START_TAG, ENV, "Body");
			xp.nextTag();

			Node responseRoot = new Node();

			if (xp.getEventType() == XmlPullParser.START_TAG
				&& xp.getNamespace().equals(ENV)
				&& xp.getName().equals("Fault")) {
				xp.require(XmlPullParser.START_TAG, ENV, "Fault");
				org.kxml2.kdom.Element detailElement = null;
				String faultcode = null;
				String faultstring = null;
				String faultactor;
				xp.nextTag();
				while (xp.getEventType() == XmlPullParser.START_TAG) {

					String name = xp.getName();

					if (name.equals("detail")) {
						Node detail = new Node();
						detail.parse(xp);
						for (int i = 0; i < detail.getChildCount(); i++) {
							if (detail.getType(i) == Node.ELEMENT) {
								detailElement = detail.getElement(i);
							}
						}
					} else if (name.equals("faultcode"))
						faultcode = xp.nextText();
					else if (name.equals("faultstring"))
						faultstring = xp.nextText();
					else if (name.equals("faultactor"))
						faultactor = xp.nextText();
					else
						throw new RuntimeException("unexpected tag:" + name);

					if (!name.equals("detail")) {
						xp.require(XmlPullParser.END_TAG, null, name);
						xp.nextTag();
					}
				}
				xp.require(XmlPullParser.END_TAG, ENV, "Fault");
				xp.nextTag();
				if (faultDetailHandler == null) {
					throw new JAXRPCException(
							faultcode + "\n" + faultstring);
				} else {
					QName faultDetailQName = null;
					faultDetailQName = new QName(detailElement.getNamespace(), detailElement.getName());
					Element detailSchemaElement =
					faultDetailHandler.handleFault(faultDetailQName);
					if (detailElement == null) {
						ByteArrayOutputStream detailBos = new ByteArrayOutputStream();
						XmlSerializer detailXw = new KXmlSerializer();
						detailXw.setOutput(detailBos, null);
						detailElement.write(detailXw);
						detailXw.flush();
						detailBos.write('\r');
						detailBos.write('\n');
						String message = detailBos.toString();
						detailBos = null;
						detailXw = null;
						throw new JAXRPCException(message);
					}
					else {
						throw new FaultDetailException(faultDetailQName, 
						deserialize(detailElement, detailSchemaElement));
					}
				}
			} else {
				responseRoot.parse(xp);
			}

			xp.require(XmlPullParser.END_TAG, ENV, "Body");

			xp.nextTag();
			xp.require(XmlPullParser.END_TAG, ENV, "Envelope");

			org.kxml2.kdom.Element outParamElement =
				responseRoot.getElement(
					output.name.getNamespaceURI(),
					output.name.getLocalPart());
			if (outParamElement == null) {
				throw new JAXRPCException("no response");
			}
			returnObject = deserialize(outParamElement, output);
		} catch (JAXRPCException jre) {
			throw jre;
		} catch (Exception e) {
			throw new JAXRPCException(e);
		} finally {
			if (is != null) {
				try {
					is.close();
				} catch (IOException e) {
				}
				is = null;
			}
			if (connection != null) {
				try {
					connection.close();
				} catch (IOException e) {
				}
				connection = null;
			}
		}
		return returnObject;
	}

	private void serialize(
		org.kxml2.kdom.Element targetElement,
		Element schemaElement,
		Object value) {
		if (schemaElement.isArray) {
			Object[] values = (Object[]) value;
			Element singleElement =
				new Element(schemaElement.name, schemaElement.contentType);
			for (int j = 0; j < values.length; j++) {
				org.kxml2.kdom.Element arrayElement =
					targetElement.createElement(
						schemaElement.name.getNamespaceURI(),
						schemaElement.name.getLocalPart());
				serialize(arrayElement, singleElement, values[j]);
				targetElement.addChild(Node.ELEMENT, arrayElement);
			}
		} else {
			Type type = schemaElement.contentType;
			if (type instanceof ComplexType) {
				ComplexType complexType = (ComplexType) type;
				Object[] values = (Object[]) value;
				for (int i = 0; i < complexType.elements.length; i++) {
					Element componentSchemaElement = complexType.elements[i];
					org.kxml2.kdom.Element componentTargetElement =
						targetElement.createElement(
							componentSchemaElement.name.getNamespaceURI(),
							componentSchemaElement.name.getLocalPart());
					if (componentSchemaElement.isArray) {
						serialize(
							targetElement,
							componentSchemaElement,
							values[i]);
					} else {
						serialize(
							componentTargetElement,
							componentSchemaElement,
							values[i]);
						targetElement.addChild(
							Node.ELEMENT,
							componentTargetElement);
					}
				}
			} else {
				if (type.value == Type.BOOLEAN.value) {
					value = (Boolean) value;
				}
				if (type.value == Type.BYTE.value) {
					value = (Byte) value;
				}
				if (type.value == Type.DOUBLE.value) {
					value = (Double) value;
				}
				if (type.value == Type.FLOAT.value) {
					value = (Float) value;
				}
				if (type.value == Type.INT.value) {
					value = (Integer) value;
				}
				if (type.value == Type.LONG.value) {
					value = (Long) value;
				}
				if (type.value == Type.SHORT.value) {
					value = (Short) value;
				}
				if (type.value == Type.STRING.value) {
					value = (String) value;
				}
				targetElement.addChild(Node.TEXT, value.toString());
			}
		}
	}

	private Object deserialize(
		org.kxml2.kdom.Element sourceElement,
		Element schemaElement)
		throws Exception {
		if (schemaElement.isArray) {
			Element singleElement =
				new Element(schemaElement.name, schemaElement.contentType);
			Vector arrayElements = new Vector();
			for (int i = 0; i < sourceElement.getChildCount(); i++) {
				int childType = sourceElement.getType(i);
				if (childType == Node.ELEMENT) {
					org.kxml2.kdom.Element subElement =
						(org.kxml2.kdom.Element) sourceElement.getChild(i);
					if (subElement
						.getNamespace()
						.equals(singleElement.name.getNamespaceURI())
						&& subElement.getName().equals(
							singleElement.name.getLocalPart())) {
						Object arrayValue =
							deserialize(subElement, singleElement);
						arrayElements.addElement(arrayValue);
					}
				}
			}
			Object[] values = new Object[arrayElements.size()];
			arrayElements.copyInto(values);
			return (Object) values;
		} else {
			Type type = schemaElement.contentType;
			if (type instanceof ComplexType) {
				ComplexType complexType = (ComplexType) type;
				int complexSize = complexType.elements.length;
				Object[] values = new Object[complexSize];
				for (int i = 0; i < complexSize; i++) {
					Element componentSchemaElement = complexType.elements[i];
					if (componentSchemaElement.isArray) {
						values[i] =
							deserialize(sourceElement, componentSchemaElement);
					} else {
						org.kxml2.kdom.Element componentSourceElement =
							sourceElement.getElement(
								componentSchemaElement.name.getNamespaceURI(),
								componentSchemaElement.name.getLocalPart());
						values[i] =
							deserialize(
								componentSourceElement,
								componentSchemaElement);
					}
				}
				return (Object) values;
			} else {
				Object value = null;
				for (int i = 0; i < sourceElement.getChildCount(); i++) {
					if (sourceElement.isText(i)) {
						String text = sourceElement.getText(i);
						if (type.value == Type.BOOLEAN.value) {
							if ("true".equals(text)) {
								value = Boolean.TRUE;
							}
							else if ("false".equals(text)) {
								value = Boolean.FALSE;
							}
						}
						if (type.value == Type.BYTE.value) {
							value = new Byte(Byte.parseByte(text));
						}
						if (type.value == Type.DOUBLE.value) {
							value = Double.valueOf(text);
						}
						if (type.value == Type.FLOAT.value) {
							value = Float.valueOf(text);
						}
						if (type.value == Type.INT.value) {
							value = Integer.valueOf(text);
						}
						if (type.value == Type.LONG.value) {
							value = new Long(Long.parseLong(text));
						}
						if (type.value == Type.SHORT.value) {
							value = new Short(Short.parseShort(text));
						}
						if (type.value == Type.STRING.value) {
							value = new String(text);
						}
					}
				}
				return value;
			}
		}
	}

}
