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
 
 package org.apache.geronimo.ews.ws4j2ee.toWs.dd.geronimo;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.AbstractWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public class GeronimoDDWriter extends AbstractWriter {
	public GeronimoDDWriter(J2EEWebServiceContext j2eewscontext) throws GenerationFault {
		super(j2eewscontext);
	}

	public String getFileName() {
		if(j2eewscontext.getMiscInfo().isImplwithEJB()){
			return j2eewscontext.getMiscInfo().getOutPutPath() +
						"/META-INF/"+ GenerationConstants.GERONIMO_DD;
		}else{
			return j2eewscontext.getMiscInfo().getOutPutPath() +
									"/META-INF/"+ GenerationConstants.GERONIMO_WEB_DD;
		}				
	}

	/* (non-Javadoc)
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.Writer#writeCode()
	 */
	public void writeCode() throws GenerationFault {
		super.writeCode();
		if(out == null)
			return;
		if(j2eewscontext.getMiscInfo().isImplwithEJB()){
			writeEJBDD();
		}else{
			writeCode();
		}	
	}
	
//	<?xml version="1.0"?>
//	<openejb-jar
//		xmlns="http://www.openejb.org/xml/ns/openejb-jar"
//		configId="your/domain/name/Example"
//		parentId="org/apache/geronimo/Server">
//
//		<enterprise-beans>
//			<session>
//				<ejb-name>SimpleStatelessSession</ejb-name>
//				<jndi-name>client/test/simple/SimpleStatelessSessionHome</jndi-name>
//			</session>
//		</enterprise-beans>
//	</openejb-jar>
	public void writeEJBDD(){		
		String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
			int index = ejbname.lastIndexOf(".");
			if(index>0){
			  ejbname = ejbname.substring(index+1);
		} 

		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<openejb-jar\n");
		out.write("    xmlns=\"http://www.openejb.org/xml/ns/openejb-jar\"\n");
		out.write("    configId=\"j2ee/geronimo/ews/"+ejbname+"\"\n");
		out.write("    parentId=\"org/apache/geronimo/Server\">\n");
		out.write("    <enterprise-beans>\n");
		out.write("        <session>\n");
		out.write("            <ejb-name>" + ejbname+ "</ejb-name>\n");
		String implStyle = j2eewscontext.getMiscInfo().getImplStyle();
		if( GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle)
					|| GenerationConstants.USE_REMOTE.equals(implStyle)){
			out.write("	  <jndi-name>" + "ejb/" +ejbname+ "</jndi-name>\n");
		}
		if(GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle) 
			|| GenerationConstants.USE_LOCAL.equals(implStyle)){
			out.write("	  <local-jndi-name>" + "ejb/" +ejbname+ "Local"+"</local-jndi-name>\n");
		}
		out.write("         </session>\n");
		out.write("     </enterprise-beans>\n");
		out.write("</openejb-jar>\n");
		out.close();
	}
	

//	<?xml version="1.0" encoding="UTF-8"?>
//	<web-app
//		xmlns="http://geronimo.apache.org/xml/ns/web/jetty"
//		configId="your/domain/name/Example"
//		parentId="org/apache/geronimo/Server"
//		>
//		<context-root>/debug-tool</context-root>
//		<context-priority-classloader>false</context-priority-classloader>
//	</web-app>
	public void writeWebDD(){		
		String ejbname = j2eewscontext.getMiscInfo().getTargetPortType().getName().toLowerCase();
			int index = ejbname.lastIndexOf(".");
			if(index>0){
			  ejbname = ejbname.substring(index+1);
		} 
		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<web-app\n");
		out.write("    xmlns=\"http://www.openejb.org/xml/ns/openejb-jar\"\n");
		out.write("    configId=\"j2ee/geronimo/ews/"+ejbname+"\"\n");
		out.write("    parentId=\"org/apache/geronimo/Server\">\n");
		out.write("    <context-root>/axis</context-root>");
		out.write("    <context-priority-classloader>false</context-priority-classloader>");
		out.write("</web-app>");
		out.close();
	}

}
