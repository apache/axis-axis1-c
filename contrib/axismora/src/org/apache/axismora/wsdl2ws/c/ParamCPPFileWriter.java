package org.apache.axismora.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
public abstract class ParamCPPFileWriter extends ParamWriter{
	public ParamCPPFileWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	
	protected void writeConstructors()throws WrapperFault{}
	protected void writeDistructors() throws WrapperFault {}
   
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
	   		//cleanup
	   		writer.flush();
	   		writer.close();
	   		System.out.println(getFilePath().getAbsolutePath() + " created.....");
	    } catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
	   
	protected void writeMethods()throws WrapperFault{}
   protected  abstract void writeGlobalCodes()throws WrapperFault; 
   protected File getFilePath() throws WrapperFault {
	   String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
	   if(targetOutputLocation.endsWith("/"))
		   targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
	   new File(targetOutputLocation).mkdirs();
	   String fileName = targetOutputLocation + "/" + this.classname + ".cpp";
	   return new File(fileName);
   }
   
   protected void writePreprocssorStatements()throws WrapperFault{
	try {
		writer.write("#include \""+this.classname + ".h\"\n");
		writer.write("#include <IWrapperSoapDeSerializer.h>\n");
		writer.write("#include <IWrapperSoapSerializer.h>\n");
		writer.write("#include <IParam.h>\n\n");
	} catch (IOException e) {
		e.printStackTrace();
		throw new WrapperFault(e);
	}
   }
}
