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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.io.File;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;

/**
 * @author hemapani@opensource.lk
 */
public class Ws4J2eeEmitter {
	protected static Log log =
			LogFactory.getLog(Ws4J2eeEmitter.class.getName());
	protected Ws4J2eeFactory factory;
	protected J2EEWebServiceContext wscontext;
	private boolean ejbBased;
	private boolean verbose;
	
	public Ws4J2eeEmitter(J2EEWebServiceContext wscontext){
		this.wscontext = wscontext;
		this.factory = wscontext.getFactory();
		this.ejbBased = wscontext.getMiscInfo().isImplwithEJB();
		this.verbose = wscontext.getMiscInfo().isVerbose();
	}	

	public void prepareOutPutDir(){
		File file = new File(wscontext.getMiscInfo().getOutPutPath() + "/META-INF");
			if (!file.exists())
				file.mkdirs();
	}
	public void generatedSEIandtypes()throws GenerationFault{
		Generator seiAndTypegen =
		factory.getGenerationFactory().createServerSideWsGenerator(
				wscontext);
		seiAndTypegen.generate();
	}
	
	public void validateTheContext()throws GenerationFault{
		ContextValidator cvalidater = new ContextValidator(wscontext);
		cvalidater.validateWithWSDL();
	}
	
	public void generateEJB()throws GenerationFault{
		if (verbose){
			log.info("genarating ejb >>");
		}
		Generator ejbgen = factory.getGenerationFactory().createEJBGenerator(wscontext);
		ejbgen.generate();
		if (verbose){
			log.info("genarating j2ee dd >>");
		}
				Generator j2eeContainerDDGen =
		factory.getGenerationFactory()
			.createContainerSpecificDDGenerator(wscontext);
		j2eeContainerDDGen.generate();    
	}
	
	public void generateWrapperWs() throws GenerationFault{
		Generator wrapgen =
		factory.getGenerationFactory().createWrapperWsGenerator(
				wscontext);
		wrapgen.generate();
	}
	
	public void generatedHandlers()throws GenerationFault{
		Generator handlerGen =
		factory.getGenerationFactory().createHandlerGenerator(
				wscontext);
		handlerGen.generate();
	}
	public void generateBuildFile()throws GenerationFault{
		Generator buildFileGen =
		factory.getGenerationFactory().createBuildFileGenerator(
				wscontext);
		buildFileGen.generate();
	}
	
	public void executeAnt()throws GenerationFault{
        if(wscontext.getMiscInfo().isCompile()){
            org.apache.geronimo.ews.ws4j2ee.utils.AntExecuter executer 
                = new org.apache.geronimo.ews.ws4j2ee.utils.AntExecuter();
            executer.execute(wscontext.getMiscInfo().getOutPutPath() + "/build.xml");
        }
	}
	
	public void emmit()throws GenerationFault{
		prepareOutPutDir();
		generatedSEIandtypes();
		validateTheContext();
		if(ejbBased){
			generateEJB();
		}
		generateWrapperWs();
		generatedHandlers();
		generateBuildFile();
		executeAnt();
	}
}
