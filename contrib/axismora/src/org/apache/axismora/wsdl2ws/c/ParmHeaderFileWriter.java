package org.apache.axismora.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
public class ParmHeaderFileWriter extends ParamWriter{
	public ParmHeaderFileWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	public void writeSource()throws WrapperFault{
	   try{
			this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
			writeClassComment();
			// if this headerfile not defined define it 
			this.writer.write("#if !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)\n");
			this.writer.write("#define __"+classname.toUpperCase()+"_H__INCLUDED_\n\n");
			writePreprocssorStatements();
			this.writer.write("typedef struct {\n");
			writeAttributes();
			this.writer.write("} "+classname+";\n\n");
			//writeConstructors();
			//writeDistructors();
			//writeMethods();
			//cleanup
			this.writer.write("#endif // !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)\n");
			writer.flush();
			writer.close();
			System.out.println(getFilePath().getAbsolutePath() + " created.....");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

	protected void writeAttributes()throws WrapperFault{
		  if(type.isArray()) return;
		  try{
			writer.write("public:\n");
			  for(int i=0;i<attribs.length;i++){
				  //if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()) continue;
				  writer.write("\t"+getCrroectParmNameConsideringArrays(new QName(attribs[i][2],attribs[i][3]),attribs[i][1])+" "+attribs[i][0]+";\n");
			  }    
		  } catch (IOException e) {
			   throw new WrapperFault(e);
		  }
	  }
	  
	protected void writeConstructors()throws WrapperFault{
		   try{
			 writer.write("public:\n\t"+classname+"::" + classname + "();\n");
		   } catch (IOException e) {
				throw new WrapperFault(e);
		   }
	   }
	   
	protected void writeDistructors() throws WrapperFault {
		try{
		  writer.write("public:\n\t"+classname+"::~" + classname + "();\n");
		} catch (IOException e) {
			 throw new WrapperFault(e);
		}
	}
   
	   
	protected void writeMethods()throws WrapperFault{}

	protected File getFilePath() throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + this.classname + ".h";
		return new File(fileName);
	}
	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
	  try{
		Type atype;
		Iterator types = this.wscontext.getTypemap().getTypes().iterator();
		while(types.hasNext()){
			if(!(atype = (Type)types.next()).equals(this.type)){
				if (false){ //TODO check if this class has a member of the type in this include file. otherwise do not include
					writer.write("#include \""+atype.getLanguageSpecificName()+".h\"\n");
				}
			}
		}
	  }catch(IOException e){
	  	throw new WrapperFault(e);
	  }
	}
}
