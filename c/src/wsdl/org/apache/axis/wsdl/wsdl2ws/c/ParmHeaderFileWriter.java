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

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

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
			this.writer.write("typedef struct "+classname+ "Tag {\n");
			writeAttributes();
			this.writer.write("} "+classname+";\n\n");
			this.writer.write("#endif /* !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)*/\n");
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
		  	  if ( attribs.length == 0 ) {
				  /* TODO : needed for Aix xlc */
				  writer.write("\t int emptyStruct;\n");
			  }			  	
			  for(int i=0;i<attribs.length;i++){
				  //if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()) continue;
		  	 	writer.write("\t"+getCHeaderFileCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])+" "+attribs[i].getParamName()+";\n");
			  }    
		  } catch (IOException e) {
			   throw new WrapperFault(e);
		  }
	  }
	  
	protected void writeConstructors()throws WrapperFault{}
	   
	protected void writeDistructors() throws WrapperFault {}

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
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
	  try{
		Type atype;
		Iterator types = this.wscontext.getTypemap().getTypes().iterator();
		writer.write("#include <axis/server/AxisUserAPI.h>\n\n");
		HashSet typeSet = new HashSet();
		String typeName = null;
		while(types.hasNext()){
			atype = (Type)types.next();
			if(!(atype.equals(this.type))){
				if (this.type.isContainedType(atype)){ 
					typeName = WrapperUtils.getLanguageTypeName4Type(atype);
					if (null != typeName) typeSet.add(typeName);
				}
			}
		}	
		Iterator itr = typeSet.iterator();
		while(itr.hasNext())
		{
			writer.write("#include \""+itr.next().toString()+".h\"\n");
		}
		writer.write("/*Local name and the URI for the type*/\n");
		writer.write("static const char* Axis_URI_"+classname+" = \""+type.getName().getNamespaceURI()+"\";\n");
		writer.write("static const char* Axis_TypeName_"+classname+" = \""+type.getName().getLocalPart()+"\";\n\n");
		
	  }catch(IOException e){
	  	throw new WrapperFault(e);
	  }
	}
}
