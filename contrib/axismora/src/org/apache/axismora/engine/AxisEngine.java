/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axismora.engine;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Writer;
import java.util.ArrayList;

import javax.servlet.ServletContext;
import javax.xml.namespace.QName;
import javax.xml.soap.SOAPException;

import org.apache.axismora.Constants;
import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.MessageContext;
import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.deployment.WebServiceNotFoundException;
import org.apache.axismora.deployment.wsdd.WSDDDeployment;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.provider.ProviderFactory;
import org.apache.axismora.soap.BasicMessageContext;
import org.apache.axismora.soap.SOAPNodeInfo;
import org.apache.axismora.util.AxisUtils;

import org.apache.axis.AxisFault;
import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.session.Session;
import org.apache.commons.logging.Log;

/**
 *  <code>AxisEngine</code>  drive the logic of the SOAP engine. There is only one axis
 *  engine exits in  the system. It is initialize once and will be serving all the 
 *  requests.
 * 
 *  This is the class that handle the execution of the framework
 * 
 *  TODO This class should be refctored by writing a AxisServer class and make this is
 *  the super class of that class.  
 * 
 *  @author Srianth (hemapani@opensource.lk)
 */
public class AxisEngine extends BasicHandler {
    protected static Log log = LogFactory.getLog(AxisEngine.class.getName());

    protected AxisDeployment deployment;
    protected HandlerPool pool;
    protected org.apache.axismora.ServicePool servicepool;
    protected Handler[] handlers;
    protected ServletContext servletcontext = null;

	public AxisEngine(String filename) throws Exception {
		this(filename,null);
	}

    public AxisEngine(String filename,ServletContext servletcontext) throws Exception {
		this.servletcontext = servletcontext;
        log.info("Axis Engine initializing");
		File file = null;
		
		// the logic is borrowed from 
		// 		org.apache.axis.configuration.EngineConfigurationFactoryServlet
		// LOGIC of the method
		// if(servlet)
		//		load file using servlet context
		// else
		//		load the file from .
		// if(file not exists)
		//	create file
		//load the WSDDDeployment	 	
		
        if(servletcontext != null){
        	//The accsess is from the servlet try to get it from the WEB-INF
			String appWebInfPath = "/WEB-INF";
			String realWebInfPath = servletcontext.getRealPath(appWebInfPath);

			   if (realWebInfPath != null)
			   	   System.out.println(realWebInfPath);	
				   file = new File(realWebInfPath, filename);
				   if(file == null || !file.exists()){
					/**
					 * If path/file doesn't exist, it may still be accessible
					 * as a resource-stream (i.e. it may be packaged in a JAR
					 * or WAR file).
					 */
				   //String name = appWebInfPath + "/" + filename;
				   //InputStream is = servletcontext.getResourceAsStream(name);
				   
				   //but the WSDDDeploymet accept only String in inputstreams ):
				   //SO above code is TODO  ... we will not support the file inside 
				   //JAR or WAR yet.
				   file = new File(filename);    
			   }else{
				System.out.println(realWebInfPath +" is null");	
			   }
        
        }else
        	//no servlets, try where u are.	
			file = new File(filename);        
        
        
        
        
        //if a configaration file does not exists create a file 
        if (!file.exists()) {
            file.createNewFile();
            PrintWriter w = new PrintWriter(new FileOutputStream(file));
            BufferedReader re =
                new BufferedReader(
                    new InputStreamReader(
                        this.getClass().getClassLoader().getResourceAsStream(
                            (Constants.CLIENT_CONFIG_FILE.equals(filename)
                                ? "org/apache/axismora/client/"
                                : "org/apache/axismora/server/")
                                + filename)));
            String line;
            while ((line = re.readLine()) != null) {
                w.write(line + "\n");
            }
            w.flush();
            w.close();
        }

        //create the deployment
        deployment = WSDDDeployment.getInstance(file.getAbsolutePath());
        pool = BasicHandlerPool.getInstance(deployment);
        servicepool = new SimpleServicePool();
        //initialize the handler pool
        pool.init();
        if (deployment == null) {
            log.fatal("Can't continue make sure the server-config.wsdd is wellformed and exist");
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                "Internal Server Error : configaration fails",
                deployment,
                this.getName(),
                null);
            //we cant continue
        }
    }

    public String getName() {
        return Constants.SERVER_ROLE;
    }

    /**
     *  The Code does not start a new thread, If used in simple manner the process method will not execute 
     *  In parellel, But the process method is thread safe. To make the code parellel what should be done is 
     *  Called the process() in new thread. That is what done by the TomCat by default.    
     * @param SOAPAction   is both service name and method name
     */
    public void process(
        String SOAPAction,
        InputStream in,
        OutputStream out,
        Session session,
        String usrname,
        char[] passwd,
        String encoding) {
    
       
    log.info("start processing service " + SOAPAction);
    // supporting both method name - Dimuthu.
	String methodName="";
	String serviceName="";   
   
	int index = SOAPAction.indexOf('$');
	  
		 if(index==-1){
		  serviceName=SOAPAction.trim();
		 }else{
		   serviceName=SOAPAction.substring(0,index).trim();
		   methodName=SOAPAction.substring(index+1).trim();
		 }
   
        MessageContext data = null;
        try {
            //create MessageData
            //*** this part should changed acording to actual implementation ****
            // to change here and message data

            WSDDService service = deployment.getService(new QName(serviceName));

            handlers = new Handler[7];
            /**
             * Load the Handlers to the engine
             */
            //finalize about protocol
            handlers[0] = pool.getTransportRequestFlowHandlers(Constants.HTTP);
            handlers[1] = pool.getGlobelRequestFlowHandlers();
            handlers[2] = pool.getServiceRequestFlowhandlers(service);

            handlers[3] = null;

            handlers[4] = pool.getServiceResponseFlowhandlers(service);
            handlers[5] = pool.getGlobelResponseFlowHandlers();
            handlers[6] = pool.getTransportResponseFlowHandlers(Constants.HTTP);

            /**
             * get the handler Information and create a SOAPNodeInfo
             */
            SOAPNodeInfo nodeinfo = new SOAPNodeInfo(deployment);
            ArrayList roles = new ArrayList();
            ArrayList headers = new ArrayList();
            for (int i = 0;(i < handlers.length); i++) {
                if (i != 3) {
                    roles.addAll(((HandlerChain) handlers[i]).getAllRoles());
                    headers.addAll(((HandlerChain) handlers[i]).getAllUnderStandQNames());
                }
            }
            for (int i = 0; i < roles.size(); i++) {
                nodeinfo.addRole((String) roles.get(i));
            }
            for (int i = 0; i < headers.size(); i++) {
                nodeinfo.addUnderstandHeader((QName) headers.get(i));
            }
            /**
             * Initalize the MessageData
             */
            data =
                new BasicMessageContext(in, out, nodeinfo, 
                			service, servicepool, session, encoding);
            
            if(!methodName.equals("")){
                data.setMethodName(new QName(serviceName,methodName));
            }
            
            //load the provider
            org.apache.axismora.provider.Provider provider 
            				= ProviderFactory.getProvider(data);
            handlers[3] = provider;

            data.parseAndValidateKnownTags();
            //set http user detail
            data.setUser(usrname);
            data.setPassword(passwd);

            /**
             * Invoke the Handlers
              */
            boolean hasfault = false;
            int i = 0;

            try {

                for (i = 0; i < handlers.length; i++) {
                    if (i == 3)
                        data.setAtPivot(true);
                    handlers[i].invoke(data);
                    if (i == 3) {
                        data.setAtPivot(false);
                        data.setPassPivot(true);
                    }
                    if (data.hasSoapFault()) {
                        hasfault = true;
                        break;
                    }
                }
            } catch (AxisFault e) {
                data.setSoapFault(new SOAPFault(e));
                hasfault = true;
            }
            //if faults are exits drive back the loop
            if (hasfault) {
                log.error("fault has occured stating driving handlers on onFault() back");
                for (int j = i - 1; j >= 0; j--) {
                    handlers[j].onFalult(data);
                }
                // run the fault flow
                pool.getSeriveFaultFlowHandlers(service).invoke(data);
            }

            //return the static Handlers
            pool.returnTransportRequestFlowHandlers(Constants.HTTP, (HandlerChain) handlers[0]);
            pool.returnGlobelRequestFlowHandlers((HandlerChain) handlers[1]);

            pool.returnGlobelResponseFlowHandlers((HandlerChain) handlers[5]);
            pool.returnTransportResponseFlowHandlers(Constants.HTTP, (HandlerChain) handlers[6]);

        } catch (Exception e) {
            log.error(e.getMessage(), e);
            QName faultCode = org.apache.axis.Constants.FAULT_SOAP12_RECEIVER;
            String message = e.getMessage();
            if (e instanceof WebServiceNotFoundException) {
                faultCode = org.apache.axis.Constants.FAULT_SOAP12_SENDER;
                message =
                    "Error occured Most probebly the Service "
                        + SOAPAction
                        + " does not exists in the engine please check your SOAPAction. Usage ServiceName$MethodName";
            }
            if (data != null)
                data.setSoapFault(
                    new SOAPFault(
                        AxisUtils.getTheAixsFault(
                            faultCode,
                            message,
                            deployment,
                            this.getName(),
                            e)));
            else {
                log.info("MessageContext is null sending error");
                sentTheSOAPFaultWhenMSGDataIsNull(e, out, faultCode);
            }
            e.printStackTrace();
        } finally {
            //code to write the result to the out put using out.
            try {
                if (data != null) {
                    data.serialize();
                    log.info("response written");
                }

            } catch (AxisFault e) {
                //oops there is not much we can do when the serialization failed 
            }
        }
    } //end of process

    public void sentTheSOAPFaultWhenMSGDataIsNull(Exception e, OutputStream out, QName faultcode) {
        try {
            Writer writer = new OutputStreamWriter(out);
            SOAPEnvelope env = new SOAPEnvelope(Constants.getSOAPConstants());
            AxisFault fault;

            if (e == null)
                e = new Exception("No message given");
            if (e instanceof AxisFault)
                fault = (AxisFault) e;
            else
                fault =
                    AxisUtils.getTheAixsFault(
                        faultcode,
                        e.getMessage(),
                        deployment,
                        this.getName(),
                        e);
            env.getBody().addChildElement(new SOAPFault(fault));
            env.output(new SerializationContextImpl(writer));
            writer.flush();
            log.info("response written");
        } catch (SOAPException e1) {
            //if you got error here too what u suppose to do ??????
            e1.printStackTrace();
        } catch (Exception e1) {
            //if you got error here too what u suppose to do ??????
            e1.printStackTrace();
        }

    }
    /* (non-Javadoc)
     * @see org.apache.axismora.Handler#invoke(org.apache.axismora.MessageContext)
     */
    public void invoke(MessageContext msgdata) throws AxisFault {
        //TODO this method will be filled in feauture refactoring
    }

} //end of class
