package org.apache.axismora.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;

import org.apache.axismora.wsdl2ws.SourceWriter;
import org.apache.axismora.wsdl2ws.WrapperFault;

/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
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
	protected abstract void writeConstructors()throws WrapperFault;
	protected abstract void writeDistructors()throws WrapperFault;
	protected abstract void writeMethods()throws WrapperFault;
	protected abstract File getFilePath()throws WrapperFault;
}
