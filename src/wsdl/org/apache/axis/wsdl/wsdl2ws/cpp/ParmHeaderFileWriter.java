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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;

public class ParmHeaderFileWriter extends ParamWriter{
	public ParmHeaderFileWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	public void writeSource()throws WrapperFault{
	   try{
			this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
			writeClassComment();
			// if this headerfile not defined define it 
			this.writer.write("#if !defined(__"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_)\n");
			this.writer.write("#define __"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_\n\n");
			writePreprocssorStatements();
			this.writer.write("class "+classname+"\n{\n");
			writeAttributes();
			writeConstructors();
			writeDistructors();
			this.writer.write("};\n\n");
			this.writer.write("#endif /* !defined(__"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_)*/\n");
			writer.flush();
			writer.close();
		    if (WSDL2Ws.verbose)
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
                                  //chek if attrib name is same as class name and if so change
                                  if (classname.equals(attribs[i].getParamName()))
                                      attribs[i].setParamName("m_" + attribs[i].getParamName());
				  writer.write("\t"+getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])+" "+attribs[i].getParamName()+";\n");
			  }    
		  } catch (IOException e) {
			   throw new WrapperFault(e);
		  }
	  }
	  
	protected void writeConstructors()throws WrapperFault{
		try{
			writer.write("\t"+classname+"();\n");
		} catch (IOException e) {
			 throw new WrapperFault(e);
		}
	}
	   
	protected void writeDistructors() throws WrapperFault {
		try{
			writer.write("\tvirtual ~"+classname+"();\n");//damitha added virtual
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
	protected File getFilePath(boolean useServiceName) throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();

		String fileName = targetOutputLocation + "/" + classname + ".h";
		
		if( useServiceName)
		{
			fileName = targetOutputLocation + "/" + this.wscontext.getSerInfo().getServicename() + "_" + classname + ".h";
		}
		
		return new File(fileName);
	}
	
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
	  try{
		Type atype;
		Iterator types = this.wscontext.getTypemap().getTypes().iterator();
		writer.write("#include <axis/server/AxisUserAPI.hpp>\n");
		writer.write("AXIS_CPP_NAMESPACE_USE \n\n");
		HashSet typeSet = new HashSet();
		for (int i=0;i<attribs.length; i++)
		{
			if ((attribs[i].isArray()) && (!attribs[i].isSimpleType()))
				typeSet.add(attribs[i].getTypeName()+"_Array");
			//if (!attribs[i].isSimpleType())
                        if (!(attribs[i].isSimpleType() || attribs[i].isAnyType()))
				typeSet.add(attribs[i].getTypeName());

		}
		Iterator itr = typeSet.iterator();
		while(itr.hasNext())
		{
			writer.write("#include \""+itr.next().toString()+".h\"\n");
		}		
			
		//Local name and the URI for the type
		writer.write("/*Local name and the URI for the type*/\n");
		writer.write("static const char* Axis_URI_"+classname+" = \""+type.getName().getNamespaceURI()+"\";\n");
		writer.write("static const char* Axis_TypeName_"+classname+" = \""+type.getName().getLocalPart()+"\";\n\n");

		// Define class to avoid compilation issue (cycle in includes).
		typeSet =  new HashSet();
		for (int i=0;i<attribs.length; i++)
		{
			//if (!attribs[i].isArray() && !attribs[i].isSimpleType())
			if (!attribs[i].isArray() && !attribs[i].isSimpleType() && !attribs[i].isAnyType())
				typeSet.add(attribs[i].getTypeName());
		}		
		itr = typeSet.iterator();
		while(itr.hasNext())
		{
			writer.write("class "+itr.next().toString()+";\n");
		}	
	  }catch(IOException e){
	  	throw new WrapperFault(e);
	  }
	}
	protected String getFileType()
	{
		return "Param";	
	}
}
