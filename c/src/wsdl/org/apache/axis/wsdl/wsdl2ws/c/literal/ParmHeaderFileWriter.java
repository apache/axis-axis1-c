/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.c.literal;

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
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
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
			if (type.isSimpleType()){
				writeSimpleTypeWithEnumerations();
			}
			else{
				writePreprocssorStatements();
				this.writer.write("typedef struct "+classname+ "Tag {\n");
				writeAttributes();
				this.writer.write("} "+classname+";\n\n");
			}
			this.writer.write("#endif /* !defined(__"+classname.toUpperCase()+"_H__INCLUDED_)*/\n");
			writer.flush();
			writer.close();
			System.out.println(getFilePath().getAbsolutePath() + " created.....");
		} catch (IOException e){
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
						writer.write("static const "+classname+"_MaxLength = "+value.getNamespaceURI()+";\n");
					}else if("minLength".equals(value.getLocalPart())){
						writer.write("static const "+classname+"_MinLength = "+value.getNamespaceURI()+";\n");
					}
				}
			}
			else if ("int".equals(baseType.getLocalPart())){
				if (restrictionData.size()>1){ //there are enumerations
					writer.write("enum { ");
					for(int i=1; i<restrictionData.size();i++){
						QName value = (QName)restrictionData.elementAt(i);
						if ("enumeration".equals(value.getLocalPart())){
							if (i>1) writer.write(", ");
							writer.write("ENUM"+classname.toUpperCase()+"_"+value.getNamespaceURI()+"="+value.getNamespaceURI()); 
						}
					}
					writer.write("} "+classname+";\n");
				}
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
			  for(int i=0;i<attribs.length;i++){
			  	 if (  attribs[i].isArray() && !attribs[i].isSimpleType() )
			  	 	writer.write("\tstruct "+getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])+"Tag "+attribs[i].getParamName()+";\n");
			  	 else
			  	 	writer.write("\t"+getCorrectParmNameConsideringArraysAndComplexTypes(attribs[i])+" "+attribs[i].getParamName()+";\n");
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
		writer.write("#include <axis/common/AxisUserAPI.h>\n\n");
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
