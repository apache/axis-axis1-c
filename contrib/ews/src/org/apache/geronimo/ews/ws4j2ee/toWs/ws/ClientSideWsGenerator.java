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

package org.apache.geronimo.ews.ws4j2ee.toWs.ws;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * <p>This genarated the Client side SEI and other classes required in the
 * Axis.</p>
 * 
 * * <h3>Service Endpoint Interface</h3>
 *	<p>The JAX-RPC specification requires that a JAX-RPC service endpoint interface must
 *	follow the following rules:</p>
 *   <ol>
 *	    <li>Service endpoint interface must extend java.rmi.Remote either directly or indirectly</li>
 *	    <li>All methods in the interface must throw java.rmi.RemoteException. Methods may
 *			throw service specific exceptions in addition to the RemoteException.</li>
 *		<li>Method parameters and return types must be the JAX-RPC supported Java types
 *			(refer to the section 5.1, “JAX-RPC Supported Java Types”). At runtime, values of a
 *			supported Java type must be serializable to and from the corresponding XML
 *	        representation.
 *	    </li>
 *	    <li>Holder classes may be used as method parameters. These Holder classes are either
 *		generated or those packaged in the standard javax.xml.rpc.holders package.</li>
 *		<li>Service endpoint interface must not include constant (as public final static)
 *		declarations. WSDL 1.1 specification does not define any standard representation for
 *		constants in a wsdl:portType definition.</li>
 *	</ol>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ClientSideWsGenerator implements Generator {
	private J2EEWebServiceContext j2eewscontext;
	protected static Log log =
			LogFactory.getLog(ServerSideWsGenerator.class.getName());

	public ClientSideWsGenerator(J2EEWebServiceContext j2eewscontext) {
		this.j2eewscontext = j2eewscontext;
	}

	public void generate() throws GenerationFault {
		try {
			String confFileLocation =
					j2eewscontext.getMiscInfo().getWsConfFileLocation();
			WSCFWebserviceDescription wscfwsdis =
					j2eewscontext.getMiscInfo().getWscfdWsDesxription();
			String mappingfile =
					Utils.getAbsolutePath(j2eewscontext.getMiscInfo().getJaxrpcfile(),
							confFileLocation);
			String wsdlfile =
					Utils.getAbsolutePath(j2eewscontext.getMiscInfo().getWsdlFile(),
							confFileLocation);
			J2eeEmitter j2ee = new J2eeEmitter();

			if (j2eewscontext.getMiscInfo().isVerbose()) {
				log.info("wsdl file = " + wsdlfile);
				log.info("jaxrpc mapping file = " + mappingfile);
				log.info("calling the jaxrpcmapper >> ");
			}

			j2ee.setMappingFilePath(mappingfile);
			j2ee.setOutputDir(j2eewscontext.getMiscInfo().getOutPutPath());
			j2ee.setServerSide(false);
			j2ee.setVerbose(j2eewscontext.getMiscInfo().isVerbose());
			j2ee.setHelperWanted(true);
			j2ee.setTestCaseWanted(true);
			j2ee.run(wsdlfile);
			SymbolTable axisSymboltable = j2ee.getSymbolTable();
			j2eewscontext.setWSDLContext(ContextFactory.createWSDLContext(axisSymboltable));
			JaxRpcMapper mapper = j2ee.getJaxRpcMapper();
			j2eewscontext.setJAXRPCMappingContext(ContextFactory.createJaxRpcMapperContext(new Object[]{mapper,j2ee}));
           

		} catch (Exception e) {
			e.printStackTrace();
			throw GenerationFault.createGenerationFault(e);
		}
        
	}

}
