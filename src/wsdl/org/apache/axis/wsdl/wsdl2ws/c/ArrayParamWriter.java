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


package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.ParamWriter;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.WSDL2Ws;

public class ArrayParamWriter extends ParamWriter{
	public ArrayParamWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	public boolean isSimpleTypeArray()throws WrapperFault{
		QName qname = WrapperUtils.getArrayType(type).getName(); 
		return CUtils.isSimpleType(qname);
	}
	public void writeSource()throws WrapperFault{
	   try{
			this.writer = new BufferedWriter(new FileWriter(getFilePath(), false));
			writeClassComment();
			// if this headerfile not defined define it 
			this.writer.write("#if !defined(__"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_)\n");
			this.writer.write("#define __"+classname.toUpperCase()+"_"+getFileType().toUpperCase()+"_H__INCLUDED_\n\n");
			if (attribs.length != 1){
				System.out.println("Array "+classname+" contains unexpected no of variables");
				throw new WrapperFault("Array type "+classname+" contain unexpected no of types");
			}
			//include header file for the contained type
			QName qname = WrapperUtils.getArrayType(type).getName(); 
			if (!CUtils.isSimpleType(qname)){
				writer.write("#include \""+attribs[0].getTypeName()+".h\"\n\n");
			}
			else{
				writer.write("#include <axis/server/AxisUserAPI.h>\n\n");
			}
			writeArrayStruct();
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
	
	protected void writeArrayStruct()throws WrapperFault{
		try{			
			writer.write("typedef struct "+classname+"Tag\n{\n");
			/*
			 * Needed for self referenced  array else compilation failed.
			* <xsd:complexType name="Type1">
			*	<xsd:sequence>
			*		<xsd:element name="followings" maxOccurs="unbounded" minOccurs="0" type="tns:Type1" />
			*		<xsd:element name="kind" type="xsd:string" />
			*		<xsd:element name="index" type="xsd:int" />
			*	</xsd:sequence>
			*	<xsd:attribute name="att_kind" type="tns:Kind" />
			* </xsd:complexType>
			*/					
			//writer.write("\t"+attribs[0].getTypeName()+"* m_Array;\n\tint m_Size;\n} "+classname+";\n\n");
			if(attribs[0].isSimpleType()){
				throw new WrapperFault("Error : no need to synthesis arrays for simple types");				
			}else{			
			writer.write("\tstruct "+attribs[0].getTypeName()+"Tag * m_Array;\n\tint m_Size;\n} "+classname+";\n\n");		
			}
		} catch (IOException e) {
			 throw new WrapperFault(e);
		}
	}
		
	protected void writeConstructors()throws WrapperFault{}
	   
	protected void writeDistructors() throws WrapperFault {}
	
	protected void writeMethods()throws WrapperFault{}
	
	protected String getFileType()
	{
		return "Array";	
	}
}
