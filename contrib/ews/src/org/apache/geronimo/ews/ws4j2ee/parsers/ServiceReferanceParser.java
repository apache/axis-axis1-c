/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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
 
 package org.apache.geronimo.ews.ws4j2ee.parsers;

import java.io.InputStream;

import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.ServiceReferanceImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * <service-ref>
 *     <service-ref-name>service/Joe</service-ref-name>
 *     <service-interface>javax.xml.rpc.Service</service-interface>
 *     <wsdl-file>WEB-INF/joe.wsdl</wsdl-file>
 *     <jaxrpc-mapping-file>WEB-INF/joe.xml</jaxrpc-mapping-file>
 *     <service-qname></service-qname>
 *     <port-component-ref>
 *         <service-endpoint-interface>sample.Joe</service-endpoint-interface>
 *         <port-component-link>JoePort</port-component-link>
 *     </port-component-ref>
 *     <handler>
 *         <handler-name></handler-name>
 *         <handler-class></handler-class>
 *     </handler>
 * </service-ref>
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ServiceReferanceParser {
	private ServiceReferance ref; 
	
	public ServiceReferanceParser(InputStream inputStream) throws GenerationFault{
		try {
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            dbf.setNamespaceAware(true);
            Document doc = dbf.newDocumentBuilder().parse(inputStream);
            Element root =  doc.getDocumentElement();
			Element serviceref = findServiceReferance(root);
			if(serviceref != null)
            	parse(serviceref);
            else
				throw new GenerationFault("No service Referance in the file");	
        } catch (Exception e) {
			throw GenerationFault.createGenerationFault(e);
        }
	}
	/**
	 * find the service-ref element from the xml file. 
	 * @param ele
	 * @return
	 */
	public Element findServiceReferance(Element ele){
		if("service-ref".equals((ele).getLocalName())){
			//System.out.println((ele).getLocalName());
			return ele;
		}else{
			NodeList nodes = ele.getChildNodes();
			for(int i=0;i<nodes.getLength();i++){
				Node node = nodes.item(i);
				if(node instanceof Element){ 
						return findServiceReferance((Element)node);
				}
			}
			return null;
		}
	} 
	public ServiceReferanceParser(Element refEle){
		parse(refEle);
	}	
		
	public void parse(Element refEle){	
		ref = new ServiceReferanceImpl();
		Element root = refEle; 

		NodeList sevlele = root.getElementsByTagName("service-ref-name");
		if(sevlele.getLength()>0){
			ref.setServicerefName(Utils.getElementValue(sevlele.item(0)));
		}
		
		sevlele = root.getElementsByTagName("service-interface");
		if(sevlele.getLength()>0){
			ref.setServiceInterface(Utils.getElementValue(sevlele.item(0)));
		}
		
		sevlele = root.getElementsByTagName("wsdl-file");
		if(sevlele.getLength()>0){
			ref.setWsdlFile(Utils.getElementValue(sevlele.item(0)));
		}

		sevlele = root.getElementsByTagName("jaxrpc-mapping-file");
		if(sevlele.getLength()>0){
			ref.setJaxrpcmappingFile(Utils.getElementValue(sevlele.item(0)));
		}
	}
	
    /**
     * @return
     */
    public ServiceReferance getRef() {
        return ref;
    }

}
