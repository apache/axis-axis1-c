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
 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws;

import java.io.BufferedWriter;
import java.io.File;

import org.apache.axis.wsdl.wsdl2ws.SourceWriter;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;

public abstract class BasicFileWriter implements SourceWriter{
	protected String classname;
	protected BufferedWriter writer;
	public BasicFileWriter(String classname)throws WrapperFault{
		this.classname = classname;
	}
	public abstract void writeSource()throws WrapperFault;
	protected void writeClassComment()throws WrapperFault{}
	protected void writePreprocssorStatements()throws WrapperFault{}
	protected void writeAttributes()throws WrapperFault{}
	protected void writeConstructors()throws WrapperFault {};
	protected void writeDistructors()throws WrapperFault {};
	protected abstract void writeMethods()throws WrapperFault;
	protected abstract File getFilePath()throws WrapperFault;
}
