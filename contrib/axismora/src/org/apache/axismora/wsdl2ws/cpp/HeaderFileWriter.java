package org.apache.axismora.wsdl2ws.cpp;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axismora.wsdl2ws.WrapperFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public abstract class HeaderFileWriter extends BasicFileWriter {
	public HeaderFileWriter(String classname)throws WrapperFault{
		super(classname);
	}
	public void writeSource()throws WrapperFault{
	   try{
	  this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
	   writeClassComment();
	   // if this headerfile not defined define it 
	   this.writer.write("#if !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)\n");
	   this.writer.write("#define __"+classname.toUpperCase()+"_H__INCLUDED_\n\n");
	   //includes
	   writePreprocssorStatements();
		//class
	   this.writer.write("class "+classname+getExtendsPart()+"\n{\n");
	   writeAttributes();
	   writeConstructors();
	   writeDistructors();
	   writeMethods();
	   this.writer.write("};\n\n");
	   this.writer.write("#endif // !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)\n");
	   //cleanup
	   writer.flush();
	   writer.close();
	   System.out.println(getFilePath().getAbsolutePath() + " created.....");

	   } catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}

	}
	protected String getExtendsPart(){return " ";}
	protected abstract File getFilePath()throws WrapperFault;

}
