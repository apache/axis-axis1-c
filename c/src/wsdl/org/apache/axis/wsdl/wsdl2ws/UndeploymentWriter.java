/*
 * Created on Mar 19, 2004
 *
 */
package org.apache.axis.wsdl.wsdl2ws;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author Susantha Kumara
 *
 */
public class UndeploymentWriter extends WsddWriter {
	public UndeploymentWriter(WebServiceContext wscontext) throws WrapperFault {
		super(wscontext);
	}
	public void writeSource() throws WrapperFault {
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter(getFilePath(this.wscontext, "undeploy"), false));
			writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			writer.write("<undeployment xmlns=\"http://xml.apache.org/axis/wsdd/\""+
				" xmlns:"+this.providerLang+"=\"http://xml.apache.org/axis/wsdd/providers/"+this.providerLang+"\">\n");
			writer.write("\t<service name=\""+this.servicename+"\"/>\n");
			writer.write("</undeployment>\n");
			writer.flush();
			writer.close();
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
}
