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

import javax.xml.namespace.QName;

import org.apache.axis.AxisFault;
import org.apache.axis.Constants;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.soap.SOAPConstants;
import org.apache.axismora.encoding.Serializable;
import org.w3c.dom.Element;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.AttributesImpl;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class FaultSerializer implements Serializable{
	private SOAPFault soapfault;
	private SOAPConstants soapConstants;
	public FaultSerializer(SOAPFault soapfault,SOAPConstants soapConstants){
		this.soapfault = soapfault;
		this.soapConstants = soapConstants;
	}
    public void serialize(SerializationContext context) throws IOException {

		String namespaceURI = soapfault.getNamespaceURI();
		String name = Constants.ELEM_FAULT;
        Attributes  attributes = soapfault.getAttributes();
		
		context.startElement(new QName(namespaceURI,name),
							 attributes);
							 
        AxisFault fault = soapfault.getFault();
		// XXX - Can fault be anything but an AxisFault here?
		if (fault instanceof AxisFault) {
			AxisFault axisFault = fault;
			if (axisFault.getFaultCode() != null) {
				// Do this BEFORE starting the element, so the prefix gets
				// registered if needed.
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS) {
					String faultCode = context.qName2String(axisFault.getFaultCode());
					context.startElement(Constants.QNAME_FAULTCODE_SOAP12, null);
					context.startElement(Constants.QNAME_FAULTVALUE_SOAP12, null);
					context.writeSafeString(faultCode);
					context.endElement();
					QName[] subcodes = axisFault.getFaultSubCodes();
					if (subcodes != null) {
						for (int i = 0; i < subcodes.length; i++) {
							faultCode = context.qName2String(subcodes[i]);
							context.startElement(Constants.QNAME_FAULTSUBCODE_SOAP12, null);
							context.startElement(Constants.QNAME_FAULTVALUE_SOAP12, null);
							context.writeSafeString(faultCode);
							context.endElement();
						}

						for (int i = 0; i < subcodes.length; i++)
							context.endElement();

					}
					context.endElement();
				} else {
					String faultCode = context.qName2String(axisFault.getFaultCode());
					context.startElement(Constants.QNAME_FAULTCODE, null);
					context.writeSafeString(faultCode);
					context.endElement();
				}
			}
            
			if (axisFault.getFaultString() != null) {
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS) {
					context.startElement(Constants.QNAME_FAULTREASON_SOAP12, null);
					AttributesImpl attrs = new AttributesImpl();
					attrs.addAttribute("http://www.w3.org/XML/1998/namespace", "xml", "xml:lang", "CDATA", "en");
					context.startElement(Constants.QNAME_TEXT_SOAP12, attrs);
				} else
					context.startElement(Constants.QNAME_FAULTSTRING, null);
				context.writeSafeString(axisFault.getFaultString());
				context.endElement();
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS) {
					context.endElement();
				}
			}
            
			if (axisFault.getFaultActor() != null) {
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS)
					context.startElement(Constants.QNAME_FAULTROLE_SOAP12, null);
				else
					context.startElement(Constants.QNAME_FAULTACTOR, null);

				context.writeSafeString(axisFault.getFaultActor());
				context.endElement();
			}

			if (axisFault.getFaultNode() != null) {
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS) {
					context.startElement(Constants.QNAME_FAULTNODE_SOAP12, null);
					context.writeSafeString(axisFault.getFaultNode());
					context.endElement();
				}
			}
			QName qname = null;
//			// get the QName for this faults detail element
//			QName qname = getFaultQName(fault.getClass(), context);
//			if (qname == null && fault.detail != null) {
//				qname = getFaultQName(fault.detail.getClass(), context);
//			}
			if (qname == null) {
				// not the greatest, but...
				qname = new QName("", "faultData");
			}
			Element[] faultDetails = axisFault.getFaultDetails();
			if (faultDetails != null) {
				if (soapConstants == SOAPConstants.SOAP12_CONSTANTS)
					context.startElement(Constants.QNAME_FAULTDETAIL_SOAP12, null);
				else
					context.startElement(Constants.QNAME_FAULTDETAILS, null);

				// Allow the fault to write its data, if any
				//we are dropping this 
				//axisFault.writeDetails(qname, context);
				// Then output any other elements
				for (int i = 0; i < faultDetails.length; i++) {
					context.writeDOMElement(faultDetails[i]);
				}
				context.endElement();
			}
		}
        
		context.endElement();
    }

}
