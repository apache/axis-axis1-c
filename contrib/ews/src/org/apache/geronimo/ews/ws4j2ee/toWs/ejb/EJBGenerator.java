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
 
 package org.apache.geronimo.ews.ws4j2ee.toWs.ejb;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Writer;
import org.apache.geronimo.ews.ws4j2ee.toWs.WriterFactory;

/**
 * <p>This class crete the nessacsaary EJB artifacts</p>
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class EJBGenerator implements Generator {
	private J2EEWebServiceContext context;
	private Writer homewriter;
	private Writer remotewriter;
	private Writer beanwriter;
	private Writer ddwriter;
	private Writer localwriter;
	private Writer localhomewriter;

	public EJBGenerator(J2EEWebServiceContext context) throws GenerationFault {
		this.context = context;
		String implStyle = context.getMiscInfo().getImplStyle();
			if(GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle) 
				|| GenerationConstants.USE_REMOTE.equals(implStyle)){
				homewriter = WriterFactory.createWriter(context, GenerationConstants.EJB_HOME_INTERFACE_WRITER);
				remotewriter = WriterFactory.createWriter(context, GenerationConstants.EJB_REMOTE_INTERFACE_WRITER);
			}else if(GenerationConstants.USE_LOCAL_AND_REMOTE.equals(implStyle) 
				|| GenerationConstants.USE_LOCAL.equals(implStyle)){
				localhomewriter = WriterFactory.createWriter(context, GenerationConstants.EJB_LOCAL_HOME_INTERFACE_WRITER);
				localwriter = WriterFactory.createWriter(context, GenerationConstants.EJB_LOCAL_INTERFACE_WRITER);
			}else if(GenerationConstants.USE_INTERNALS.equals(implStyle)){
				//when we use the internals we do not want create anything   
			}
			if(!context.getMiscInfo().isImplAvalible()){
				beanwriter = WriterFactory.createWriter(context, GenerationConstants.EJB_IMPLEMENTATION_BEAN_WRITER);
			}	
		ddwriter = WriterFactory.createWriter(context, GenerationConstants.EJB_DD_WRITER);
	}

	public void generate() throws GenerationFault {
		if(homewriter != null)
			homewriter.writeCode();
		if(remotewriter != null)	
			remotewriter.writeCode();
		if(beanwriter != null)
			beanwriter.writeCode();
		if(ddwriter!=null)	
			ddwriter.writeCode();
		if(localwriter != null){
			localwriter.writeCode();
		}
		if(localhomewriter!=null){
			localhomewriter.writeCode();
		}
	}

}
