/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee.parsers;

import java.io.InputStream;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.WebContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferanceContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani@opensource.lk
 */
public interface ParserFactory {
	public ServiceReferanceContext parseServiceReferance(J2EEWebServiceContext context,InputStream inputStream)throws GenerationFault;
	public WSCFContext parseWSCF(J2EEWebServiceContext context,InputStream inputStream)throws GenerationFault;
	public WebContext parseWebDD(J2EEWebServiceContext context,InputStream inputStream)throws GenerationFault;
	public EJBContext parseEJBDDContext(J2EEWebServiceContext context,InputStream inputStream)throws GenerationFault;
}
