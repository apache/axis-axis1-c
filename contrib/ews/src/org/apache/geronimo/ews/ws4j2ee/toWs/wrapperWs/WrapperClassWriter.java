/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002-2003 The Apache Software Foundation.  All rights
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
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "The Jakarta Project", "Commons", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
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
 *
 */
package org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.JavaClassWriter;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * This class genarate the wrapper Webservice.
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public abstract class WrapperClassWriter extends JavaClassWriter{
	protected static Log log =
						LogFactory.getLog(WrapperWsGenarator.class.getName());
	protected String seiName = null;
	/**
	 * @param j2eewscontext
	 * @param qulifiedName
	 * @throws GenerationFault
	 */
	public WrapperClassWriter(J2EEWebServiceContext j2eewscontext)
		throws GenerationFault {
		super(j2eewscontext, getName(j2eewscontext) +"Impl");
		seiName = j2eewscontext.getMiscInfo().getEjbsei();
	}
	
	private static String getName(J2EEWebServiceContext j2eewscontext){
		String name = j2eewscontext.getMiscInfo().gettargetBinding().getName();
		if(name == null){
			name = Utils.qName2JavaName(j2eewscontext.getMiscInfo().gettargetBinding().getQName());
		}
		return name;
	}

	protected String getimplementsPart() {
		return " implements "+ j2eewscontext.getMiscInfo().getJaxrpcSEI()+",org.apache.geronimo.ews.ws4j2ee.wsutils.ContextAccssible";
	}

	protected void writeAttributes() throws GenerationFault {
		
		out.write("private "+seiName+" ejb = null;\n");
		out.write("private org.apache.axis.MessageContext msgcontext;\n");
	}

	protected void writeConstructors() throws GenerationFault {
		out.write("\tpublic "+classname+"(){}\n");
	}


	public String getFileName() {
		String filename = j2eewscontext.getMiscInfo().getOutPutPath()+"/"+
				getName(j2eewscontext).replace('.','/') +"Impl.java";
				//j2eewscontext.getMiscInfo().getJaxrpcSEI().replace('.','/')+"BindingImpl.java";
		log.info(filename + " generating.....................");
		return filename;
	}
}