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

import java.io.File;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;



/**
 * @author hemapani
 */
public class Ws4J2eeWtihoutWSDLCLOptionParser {
	private String wscfFileLocation;
	private String wjbConfFileLocation;
	private String webConfFileLocation;
	private String outPutLocation;
	private WSCFWebserviceDescription[] wscfwsdis;
	private String[] args;
	private int indexToChange = -1;
	
	public  Ws4J2eeWtihoutWSDLCLOptionParser(String[] args){
		this.args = args;
		wscfFileLocation = args[0];
		outPutLocation = Utils.getRootDirOfFile(wscfFileLocation);
		
		File file = new File(outPutLocation+"/META-INF");
		if (!file.exists())
			file.mkdirs();
			boolean found = false;		
			for(int i = 0;i<args.length;i++){
				if(args[i].startsWith("-o")){
					String output = args[i].substring(2);
					file = new File(output+"/META-INF");
					if (!file.exists())
						file.mkdirs();
					outPutLocation = output;
					//wsdlFile = Utils.getAbsolutePath(wscfwsdis.getWsdlFile(),output);
					//args[i] = "-o"+wsdlFile;
					indexToChange = i;
					found = true;
				}
			}
			if(!found){
				//wscontext.getMiscInfo().setOutputPath(wscontext.getMiscInfo().getWsConfFileLocation());
				//wsdlFile = Utils.getAbsolutePath(wscfwsdis.getWsdlFile(),wscontext.getMiscInfo().getWsConfFileLocation());
				String[] newArgs =  new String[args.length+1];
				for(int i = 0;i<args.length;i++){
					newArgs[i] = args[i];
				}
				//newArgs[args.length] = "-o"+wsdlFile;
				indexToChange = args.length;
				this.args = newArgs;
			}
		//the other two files are considered to be at the same directory as the 
		 //wscf file	
		wjbConfFileLocation = Utils.getRootDirOfFile(wscfFileLocation)+"/ejb-jar.xml";
		webConfFileLocation = Utils.getRootDirOfFile(wscfFileLocation)+"/web.xml";
	
	}
	 
	public String getWSCFFileLocation(){
		return wscfFileLocation;
	}
	public String getEjbConfFileLocation(){
		return wjbConfFileLocation;
	}
	public String getWebConfFileLocation(){
		return webConfFileLocation;
	}
	public String[] getArgsforJava2WSDLEmitter(String seiName,String wsdlfile){
		args[0] = seiName;
		if(indexToChange>0)
			args[indexToChange] = "-o"+wsdlfile;
		return args;
	}
    /**
     * @return
     */
    public String getOutPutLocation() {
        return outPutLocation;
    }

    /**
     * @param string
     */
    public void setOutPutLocation(String string) {
        outPutLocation = string;
    }

}
