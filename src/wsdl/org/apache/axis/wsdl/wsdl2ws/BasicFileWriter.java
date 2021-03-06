/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws;

import java.io.BufferedWriter;
import java.io.File;

import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Basic file writer.
 *
 */
public abstract class BasicFileWriter implements SourceWriter
{
	protected String c_classname;
	protected String c_fileExtension;
	protected BufferedWriter c_writer;
    protected WebServiceContext wscontext = null;
    
	public BasicFileWriter(String classname, String fileExtension) throws WrapperFault
	{
		c_classname     = classname;
		c_fileExtension = fileExtension;
	}
	public abstract void writeSource() throws WrapperFault;
	protected void writeClassComment() throws WrapperFault {}
	protected void writePreprocessorStatements() throws WrapperFault {}
	protected void writeAttributes() throws WrapperFault {}
	protected void writeConstructors() throws WrapperFault {};
	protected void writeDestructors() throws WrapperFault {};
	protected abstract void writeMethods() throws WrapperFault;
	
	protected File getFilePath(boolean useServiceName) throws WrapperFault
	{
	    if (wscontext == null)
	        throw new WrapperFault("Context not set.");
	    
        String targetOutputLocation = wscontext.getWrapperInfo().getTargetOutputLocation();
        new File(targetOutputLocation).mkdirs();
        
        String serviceName = "";
        if (useServiceName)
            serviceName = wscontext.getServiceInfo().getServicename() + "_";
        
        String fileName = targetOutputLocation + "/" + serviceName + c_classname + c_fileExtension;
        
        wscontext.addGeneratedFile(fileName);
        
        return new File(fileName);
	}
}
