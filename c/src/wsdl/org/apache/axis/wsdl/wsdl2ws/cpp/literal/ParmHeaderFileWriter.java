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

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;

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
			if (type.isSimpleType()){
				writeSimpleTypeWithEnumerations();
			}
			else{
				writePreprocssorStatements();
				this.writer.write("class "+classname+"\n{\n");
				writeAttributes();
				writeConstructors();
				writeDistructors();
				this.writer.write("};\n\n");
			}
			this.writer.write("#endif /* !defined(__"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_)*/\n");
			writer.flush();
			writer.close();
			System.out.println(getFilePath().getAbsolutePath() + " created.....");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
	
	protected void writeSimpleTypeWithEnumerations() throws WrapperFault{
		try{
			Vector restrictionData = type.getEnumerationdata();
			if ( restrictionData == null) return;
			TypeEntry baseEType = (TypeEntry)restrictionData.firstElement();
			QName baseType = baseEType.getQName();
			if (!CUtils.isSimpleType(baseType)) return;
			String langTypeName = CUtils.getclass4qname(baseType);
			writer.write("typedef ");
			if ("string".equals(baseType.getLocalPart())){
				writer.write(langTypeName + " " + classname + ";\n");
				for(int i=1; i<restrictionData.size();i++){
					QName value = (QName)restrictionData.elementAt(i);
					if ("enumeration".equals(value.getLocalPart())){
						writer.write("static const "+classname+" "+classname+"_"+value.getNamespaceURI()+" = \""+ value.getNamespaceURI()+"\";\n");
					}else if("maxLength".equals(value.getLocalPart())){
						writer.write("static const int "+classname+"_MaxLength = "+value.getNamespaceURI()+";\n");
					}else if("minLength".equals(value.getLocalPart())){
						writer.write("static const int "+classname+"_MinLength = "+value.getNamespaceURI()+";\n");
					}
				}
			}
			else if ("int".equals(baseType.getLocalPart())){
				if (restrictionData.size()>1){ //there are enumerations or min/maxInclusive
					boolean isEnum = false;
					boolean hasRestrictionItems = false;
					for(int i=1; i<restrictionData.size();i++){
						QName value = (QName)restrictionData.elementAt(i);
						if ("enumeration".equals(value.getLocalPart())){
							isEnum = true;
							if (i>1) writer.write(", "); else writer.write(" enum { ");
							writer.write("ENUM"+classname.toUpperCase()+"_"+value.getNamespaceURI()+"="+value.getNamespaceURI());		
						} else if("minInclusive".equals(value.getLocalPart())){
								hasRestrictionItems = true;
								if (i<=1) writer.write(langTypeName + " " + classname + ";\n");
								writer.write("static const int "+classname+"_MinInclusive = "+value.getNamespaceURI()+";\n");
						}else if("maxInclusive".equals(value.getLocalPart())){
								hasRestrictionItems=true;
								if (i<=1) writer.write(langTypeName + " " + classname + ";\n");
								writer.write("static const int "+classname+"_MaxInclusive = "+value.getNamespaceURI()+";\n");
						}									
					}
					if (isEnum )
						 writer.write("} "+classname+";\n");
					else if (!hasRestrictionItems) 
						writer.write(langTypeName + " " + classname + ";\n"); 
				}
			else
				writer.write(langTypeName + " " + classname + ";\n"); 
			}
			else{
				writer.write(langTypeName + " " + classname + ";\n");
				for(int i=1; i<restrictionData.size();i++){
					QName value = (QName)restrictionData.elementAt(i);
					if ("enumeration".equals(value.getLocalPart())){
						writer.write("static const "+classname+" "+classname+"_"+value.getNamespaceURI()+" = "+ value.getNamespaceURI()+";\n");
					}
				}
			}	
		} catch (IOException e) {
			 throw new WrapperFault(e);
		}
	}
	
	protected void writeAttributes()throws WrapperFault{
		  if(type.isArray()) return;
		  try{
			writer.write("public:\n");
			  for(int i=0;i<attribs.length;i++){
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
			writer.write("\t~"+classname+"();\n");
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
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.BasicFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
	  try{
		Type atype;
		Iterator types = this.wscontext.getTypemap().getTypes().iterator();
		writer.write("#include <axis/server/AxisUserAPI.h>\n\n");
		HashSet typeSet = new HashSet();
		for (int i=0;i<attribs.length; i++)
		{
			if ((attribs[i].isArray()) && (!attribs[i].isSimpleType()))
				typeSet.add(attribs[i].getTypeName()+"_Array");
			if (!attribs[i].isSimpleType())
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
		
		// Define class to avoid compilation issues (cycle in includes).
		// This is a must for complex wsdl files.
		typeSet =  new HashSet();
		for (int i=0;i<attribs.length; i++)
		{
			if (!attribs[i].isArray() && !attribs[i].isSimpleType())
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
