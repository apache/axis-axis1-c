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
 
package org.apache.axis.wsdl.wsdl2ws;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * @author Susantha Kumara susantha@opensource.lk
 *
 */
public class BuildScriptWriter implements SourceWriter {
	private WebServiceContext wscontext = null;
	private String servicename = null;
	
	public BuildScriptWriter(WebServiceContext wscontext) throws WrapperFault {
		this.wscontext = wscontext;
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.SourceWriter#writeSource()
	 */
	public void writeSource() throws WrapperFault {
		try {
			servicename = wscontext.getSerInfo().getServicename();
			Iterator filelist = wscontext.getGeneratedFileList().iterator();
			BufferedWriter writer = new BufferedWriter(new FileWriter(getFilePath(), false));
			if(WrapperConstants.SERVER.equals(wscontext.getWrapInfo().getTargetEngine())){
				writer.write("lib_LTLIBRARIES = lib"+servicename+".la\n");
				writer.write("SUBDIRS =\n");
				writer.write("lib"+servicename+"_la_SOURCES =");
				while (filelist.hasNext()){
					writer.write(" "+(String)filelist.next());
				}
				writer.write("\nlib"+servicename+"_la_LIBADD = $(LDFLAGS)\n");
				writer.write("INCLUDES = -I$(AXISCPP_HOME)/include\n");			
			}
			else{
				writer.write("bin_PROGRAMS = "+servicename+"\n");
				writer.write("SUBDIRS =\n");
				writer.write("AM_CPPFLAGS = $(CPPFLAGS)\n");
				writer.write(servicename+"_SOURCES = ");
				while(filelist.hasNext()){
					writer.write(" "+(String)filelist.next());
				}
				writer.write("\n"+servicename+"_LDADD = $(LDFLAGS)\n");
				writer.write("INCLUDES = -I$(AXISCPP_HOME)/include\n");			
			}
			writer.flush();
			writer.close();
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	private File getFilePath() throws WrapperFault {
		String targetOutputLocation = wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + "Makefile.am";
		return new File(fileName);
	}
}
