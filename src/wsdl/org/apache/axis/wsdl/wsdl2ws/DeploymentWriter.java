/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * Created on Mar 19, 2004
 *
 */
package org.apache.axis.wsdl.wsdl2ws;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author Susantha Kumara
 *
 */
public class DeploymentWriter extends WsddWriter {
	public DeploymentWriter(WebServiceContext wscontext) throws WrapperFault {
		super(wscontext);
	}
	public void writeSource() throws WrapperFault {
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter(getFilePath(this.wscontext, "deploy"), false));
			writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			writer.write("<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\""+
				" xmlns:"+this.providerLang+"=\"http://xml.apache.org/axis/wsdd/providers/"+this.providerLang+"\">\n");
			writer.write("\t<service name=\""+this.servicename+"\" provider=\""+this.providerLang+":"+this.providerStyle+"\" description=\""+this.description+"\">\n");
			writer.write("\t\t<parameter name=\"className\" value=\"/user/local/apache/axis/"+this.servicename+".so\"/>\n");
			writer.write("\t\t<parameter name=\"allowedMethods\" value=\"");
			Iterator it = this.allowedmethods.iterator();
			while (it.hasNext()){
				writer.write((String)it.next()+" ");
			}
			writer.write("\"/>\n");
			writer.write("\t</service>\n");
			writer.write("</deployment>\n");
			writer.flush();
			writer.close();
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
}
