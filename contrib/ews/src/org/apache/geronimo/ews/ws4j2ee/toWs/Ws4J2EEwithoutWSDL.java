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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.io.IOException;
import java.io.InputStream;
import java.util.Vector;

import org.apache.axis.components.logger.LogFactory;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.J2EEWebServiceContextImpl;
import org.apache.geronimo.ews.ws4j2ee.parsers.EJBDDParser;
import org.apache.geronimo.ews.ws4j2ee.toWs.wsdl.WSDLGenarator;

/**
 * <p>this class genarate the code when the WSDL presents.</p>
 */
public class Ws4J2EEwithoutWSDL implements Generator {
	protected static Log log =
			LogFactory.getLog(Ws4J2EEwithWSDL.class.getName());

    private Vector genarators;
    /*
     *  indiate wheather to use the SEI or the ejb to get the 
     * information about SEI and the custom types.
     */
    private boolean useSEI = true;
    private String[] args;
	private J2EEWebServiceContext wscontext;
	private boolean verbose = true;

    public Ws4J2EEwithoutWSDL(String[] args,boolean useSEI)throws GenerationFault {
        genarators = new Vector();
        
        this.args = args;
        
        //we may need to pass few parameters to the J2EEWebServiceContextImpl they are TODO
        this.wscontext = new J2EEWebServiceContextImpl(false);

        //when the WSDL is not present the the informatio to
        //create the WSDL can be found from SEI and types classes OR
        //ejb and type classes. useSEI show what is used. in each case
        //the EJB or the SEI (which is already exists) need not to be genarated   		
		this.useSEI = useSEI;
		this.wscontext.setMiscInfo(ContextFactory.createMiscInfo());
    }

    /**
     * genarate. what is genarated is depend on genarators included. 
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
     */
    public void genarate() throws GenerationFault {
    	
    	
    	try {
    	if(verbose)
    		log.info("calling Java2WSDL t genarated wsdl ...........");
    	
		WSDLGenarator wsdlgen = (WSDLGenarator)GeneratorFactory.createGenerator(
			wscontext,GenerationConstants.WSDL_GENERATOR);
		wsdlgen.setArgs(args);
		//other than genarating the WSDL file this will initaite all the contxt's
		//and validate the Context.	
		wsdlgen.genarate();
		
		EJBDDParser ejbDDparser = new EJBDDParser(wscontext);
		InputStream ejbddin = Ws4J2EEwithoutWSDL.class.getResourceAsStream("META-INF/ejb-jar.xml");
		if( ejbddin != null){
			ejbDDparser.parse(ejbddin); 
			ejbddin.close();	
		}
		
		
		if(verbose)
			log.info("genarating jaxrpc-mapper.xml ..............");
		GeneratorFactory.createGenerator(wscontext,
			GenerationConstants.JAXRPCMAPPER_GENERATOR).genarate();
		if(verbose)
			log.info("genarating webservice.xml .............");	
		GeneratorFactory.createGenerator(wscontext,
					GenerationConstants.WEBSERVICEDD_GENERATOR).genarate();	

		GeneratorFactory.createGenerator(
				wscontext,
				GenerationConstants.SEI_AND_TYPES_GENERATOR).genarate();
		} catch (IOException e) {
			throw GenerationFault.createGenerationFault(e);
        }
       
		


		
//		if (useSEI){
//		   genarators.add(
//			   GeneratorFactory.createGenerator(
//				   wscontext,
//				   GenerationConstants.EJB_GENERATOR));
//	   }else{
//		   genarators.add(
//			   GeneratorFactory.createGenerator(
//				   wscontext,
//				   GenerationConstants.SEI_AND_TYPES_GENERATOR));
//	   }           
//	   
//		GeneratorFactory.createGenerator(
//			   wscontext,
//			   GenerationConstants.AXIS_WEBSERVICE_WRAPPER_GENERATOR).genarate();
//        }
    }
    public static void main(String[] args)throws Exception{
		Ws4J2EEwithoutWSDL gen = new Ws4J2EEwithoutWSDL(args,false);
		gen.genarate();
    }
}
