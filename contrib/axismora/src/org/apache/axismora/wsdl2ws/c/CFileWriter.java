/*
 * Created on Sep 10, 2003
 */
package org.apache.axismora.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axismora.wsdl2ws.WrapperFault;

/**
 * @author administrator
 */
public abstract class CFileWriter extends BasicFileWriter{
	public CFileWriter(String classname)throws WrapperFault{
		super(classname);
	}
	public void writeSource()throws WrapperFault{
	   try{
	  this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
	   writeClassComment();
	   writePreprocssorStatements();
	   writeGlobalCodes();

	  // this.writer.write("public class "+servicename+getExtendsPart()+"{\n");

	   writeAttributes();
	   writeConstructors();
	   writeDistructors();
	   writeMethods();
	   //this.writer.write("}\n");
	   //cleanup
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



