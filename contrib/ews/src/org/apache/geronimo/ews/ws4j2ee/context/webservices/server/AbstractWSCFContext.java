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

package org.apache.geronimo.ews.ws4j2ee.context.webservices.server;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;

/**
 * @author hemapani@opensource.lk
 */
public abstract class AbstractWSCFContext implements WSCFContext{
	protected WSCFWebserviceDescription wscfdWsDesxription;
	protected WSCFPortComponent wscfport;

	/**
	 * @return 
	 */
	public WSCFWebserviceDescription getWscfdWsDesxription() {
		return wscfdWsDesxription;
	}

	/**
	 * @return 
	 */
	public WSCFPortComponent getWscfport() {
		return wscfport;
	}

	/**
	 * @param description 
	 */
	public void setWscfdWsDescription(WSCFWebserviceDescription description) {
		wscfdWsDesxription = description;
	}

	/**
	 * @param component 
	 */
	public void setWscfport(WSCFPortComponent component) {
		wscfport = component;
	}


}
