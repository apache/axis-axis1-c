/*
 * Created on Jun 3, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.axis.wsdl.wsdl2ws.cpp;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.BasicFileWriter;

/**
 * @author nithya
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public abstract class CPPExceptionClassWriter extends BasicFileWriter{
	
	public CPPExceptionClassWriter(String classname) throws WrapperFault{
			super(classname);
		}
	public void writeSource()throws WrapperFault{
		   try{
		  this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
		   writeClassComment();
		   writePreprocssorStatements();
		   writeGlobalCodes();
		   writeAttributes();
		   writeConstructors();
		   writeDistructors();
		   writeMethods();
		   writer.flush();
		   writer.close();
		   System.out.println(getFilePath().getAbsolutePath() + " created.....");
		   } catch (IOException e) {
				e.printStackTrace();
				throw new WrapperFault(e);
			}
		}
		
      protected void writeGlobalCodes()throws WrapperFault{}
}
