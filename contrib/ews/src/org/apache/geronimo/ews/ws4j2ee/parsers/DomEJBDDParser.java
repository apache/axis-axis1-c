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

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.EJBDDContextImpl;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

/**
 * Parse the ejb-jar.xml file and get the name of the EJB
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class DomEJBDDParser {
	private J2EEWebServiceContext j2eewscontext;
	private String ejbName = null;
	private EJBContext context;

	public DomEJBDDParser(J2EEWebServiceContext j2eewscontext) {
		this.j2eewscontext = j2eewscontext;
	}

	public void parse(InputStream inputStream) throws GenerationFault {
			try {
				DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
				dbf.setNamespaceAware(true);
				Document doc = dbf.newDocumentBuilder().parse(inputStream);
				Element root =  doc.getDocumentElement();
				NodeList beaneles = root.getElementsByTagName("enterprise-beans");
				if(beaneles.getLength()>0){
					Element beanele = (Element)beaneles.item(0);
					NodeList sessionList = beanele.getElementsByTagName("session");
					if(sessionList.getLength()>0){
						Element session = (Element)sessionList.item(0);
						
						String ejbName = Utils.getElementValue(session.getElementsByTagName("ejb-name"));
						String home = Utils.getElementValue(session.getElementsByTagName("home"));
						String remote = Utils.getElementValue(session.getElementsByTagName("remote"));
						String ejbClass = Utils.getElementValue(session.getElementsByTagName("ejb-class"));

						context = new EJBDDContextImpl(
							ejbName,
							ejbClass,
							home,remote,null,null);
					}else{
						throw new GenerationFault("session tag not found");
				}
				}else{
					throw new GenerationFault("enterprise-beans tag not found");
				}
			} catch (Exception e) {
				throw GenerationFault.createGenerationFault(e);
			}
		}
    /**
     * @return
     */
    public EJBContext getContext() {
        return context;
    }

    /**
     * @param context
     */
    public void setContext(EJBContext context) {
        this.context = context;
    }

}
